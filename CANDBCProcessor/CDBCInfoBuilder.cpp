#include "CDBCInfoBuilder.h"
#include "DBCInfo.h"
#include "CDBCFileParser.h"
#include "CMultiplexedMessageProcessor.h"
#include "CSimpleMessageProcessor.h"
#include <iostream>

CDBCInfoBuilder::CDBCInfoBuilder( DBCInfo& dbcInfo)
: m_dbcInfo(dbcInfo)
{    
}

bool CDBCInfoBuilder::BuildDBCInfo(const std::vector<std::string>& dbcList)
{
  m_dbcInfo.dbcVersion = "";

  //adding default message
  AddMessage( 0 , "Unknown",  8, "-" );

  CDBCFileParser fileParser(*this);
  for( const auto& fileName : dbcList )
  {
      fileParser.ReadDBCFile(fileName);
  }

  FinalizeBuildingParserInfo();

  return true;
}

void CDBCInfoBuilder::SetVersionInfo( const std::string& versionInfo)
{
  if (!m_dbcInfo.dbcVersion.empty() )
  { 
    m_dbcInfo.dbcVersion = m_dbcInfo.dbcVersion + "//"+ versionInfo;
  }
  else
  {
    m_dbcInfo.dbcVersion = versionInfo;
  }
}


void CDBCInfoBuilder::AddMessage( const unsigned int canId , const std::string& name,  size_t size, const std::string& sender )
{
  m_currentMessage = std::make_shared<CMessageTemplate>( canId,name, size, sender);
  DBCInfo::tMessageMapEntry entry = std::make_tuple(m_currentMessage,std::shared_ptr<CMessageProcessor>(),DBCInfo::tMessageListeners());

  m_dbcInfo.msgId2message.insert( DBCInfo::tMsgId2Message::value_type(canId,entry) );
  m_dbcInfo.pgn2message.insert( DBCInfo::tMsgId2Message::value_type( GET_PGN( canId ) , entry));

  if ( 0 == canId )
  {
    m_dbcInfo.genericMessagePtr = m_currentMessage;
  }
}

void CDBCInfoBuilder::AddSignal( const std::string& name,
                    const unsigned int bitStart,
                    const size_t size,
                    const int endiannes,
                    const tSignalValueProperties& valueProperties,
                    const std::string& unit,
                    const std::string& receiver )
{
  CSignal::eEndiannes sgEndiannes = ( endiannes != 1 ) ? CSignal::bigEndian : CSignal::littleEndian;

  if (m_currentMessage)
  {
      m_currentMessage->AddSignal( name,cStaticIndexField,bitStart,size,sgEndiannes,valueProperties,unit,receiver);
  }
}

void CDBCInfoBuilder::AddMultiplexedSignal( const std::string& name,
                            const unsigned int bitStart,
                            const size_t size,
                            const int endiannes,
                            const tSignalValueProperties& valueProperties,
                            const std::string& unit,
                            const std::string& receiver,
                            const int multiplexId )
{
  CSignal::eEndiannes sgEndiannes = ( endiannes != 1 ) ? CSignal::bigEndian : CSignal::littleEndian;

  if (m_currentMessage)
  {
    m_currentMessage->AddSignal( name,multiplexId,bitStart,size,sgEndiannes ,valueProperties,unit,receiver);
  }
}

void CDBCInfoBuilder::AddMessageDescription( unsigned int msgId, const std::string& description)
{
  const auto messageIter = m_dbcInfo.msgId2message.find( msgId );
  if (m_dbcInfo.msgId2message.end() != messageIter )
  {
      std::get<MESSAGE>(messageIter->second)->SetDescription(description);
  }
}

void CDBCInfoBuilder::AddSignalDescription( unsigned int msgId, const std::string& valueName, const std::string& description)
{
  const auto messageIter = m_dbcInfo.msgId2message.find( msgId );
  if (m_dbcInfo.msgId2message.end() != messageIter )
  {
    std::get<MESSAGE>(messageIter->second)->SetSignalDescription(valueName,description);
  }
}

void CDBCInfoBuilder::SetSignalPropertyType( const std::string& valueName, const std::string& type )
{

}

void CDBCInfoBuilder::SetMessagePropertyType( const std::string& propertyName, const std::string& propertyValue)
{

}

void CDBCInfoBuilder::SetGeneralPropertyType( const std::string& propertyName, const std::string& propertyType)
{
  m_dbcInfo.propertyTypesMap.insert( tPropertyMap::value_type(propertyName,propertyType));
}

void CDBCInfoBuilder::SetDefaultPropertyValue( const std::string& propertyName, const std::string& defaultValue )
{
  m_dbcInfo.processorPropertyMap.insert(tPropertyMap::value_type(propertyName,defaultValue));
}

void CDBCInfoBuilder::SetMessageProperty( const std::string& propertyName, const unsigned int msgId, const std::string& propertyValue )
{
  const auto messageIter = m_dbcInfo.msgId2message.find( msgId );
  if (m_dbcInfo.msgId2message.end() != messageIter )
  {
    std::get<MESSAGE>(messageIter->second)->AddMessageProperty(propertyName,propertyValue);
  }
}

void CDBCInfoBuilder::SetSignalProperty( const std::string& propertyName, const unsigned int msgId, const std::string& signalName, const std::string& propertyValue)
{
    const auto messageIter = m_dbcInfo.msgId2message.find( msgId );
    if (m_dbcInfo.msgId2message.end() != messageIter )
    {
        std::get<MESSAGE>(messageIter->second)->SetSignalProperty(signalName, propertyName,propertyValue);
    }
}

void CDBCInfoBuilder::SetSignalValueDictionary( const int msgId, const std::string& signalName, const std::string& initlizerString)
{
  const auto messageIter = m_dbcInfo.msgId2message.find( msgId );

  if (m_dbcInfo.msgId2message.end() != messageIter )
  {
    std::get<MESSAGE>(messageIter->second)->SetSignalValueDictonary(signalName, initlizerString);
  }  
}

void CDBCInfoBuilder::FinalizeBuildingParserInfo()
{
  std::shared_ptr<CMessageProcessor> simpleMessageProcessor(  std::make_shared<CSimpleMessageProcessor>() );
  std::shared_ptr<CMessageProcessor> multiplexedMessageProcessor( std::make_shared<CMultiplexedMessageProcessor>() );

  for ( auto& messageEntry: m_dbcInfo.msgId2message)
  {
    auto& processorPtr = std::get<PROCESSOR>(messageEntry.second);
    if ( !std::get<MESSAGE>(messageEntry.second)->IsMultiplexedMessage(  ) )
    {
      processorPtr = simpleMessageProcessor;
    }
    else
    {
      processorPtr =  multiplexedMessageProcessor;
    }

    std::get<MESSAGE>(messageEntry.second)->BuildDefaultValueMap();
  }

  for ( auto& messageEntry: m_dbcInfo.pgn2message)
  {
    auto& processorPtr = std::get<PROCESSOR>(messageEntry.second);
    if ( !std::get<MESSAGE>(messageEntry.second)->IsMultiplexedMessage(  ) )
    {
      processorPtr = simpleMessageProcessor;
    }
    else
    {
      processorPtr =  multiplexedMessageProcessor;
    }

    std::get<MESSAGE>(messageEntry.second)->BuildDefaultValueMap();
  }


  if ( m_dbcInfo.genericMessagePtr)
  {
    m_dbcInfo.genericMessagePtr = std::make_shared<CMessageTemplate>( 0, "Generic", 8, "-" );
  }
}