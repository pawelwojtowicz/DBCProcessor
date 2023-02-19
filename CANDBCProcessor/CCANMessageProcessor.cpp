#include "CCANMessageProcessor.h"
#include "CDBCInfoBuilder.h"
#include "ISignalListener.h"
#include "DBCProcessor.h"
#include "CDBCVerifier.h"
#include "Logger.h"
#ifdef WITH_LOGGER
#include "CSimpleLogger.h"
#endif

const std::string& CCANMessageProcessor::GetDBCVersion() const
{
  return m_dbcInfo.dbcVersion;
}

void CCANMessageProcessor::Initialize( const std::string& dbcFilePath, const bool verifyDBC,std::shared_ptr<Logger::ILogger> pLogger )
{
  std::vector<std::string> dbcList = { dbcFilePath } ;
  Initialize(dbcList, verifyDBC,pLogger);
}

void CCANMessageProcessor::Initialize(  const std::vector<std::string>& dbcList,const bool verifyDBC , std::shared_ptr<Logger::ILogger> pLogger )
{ 
#ifdef WITH_LOGGER
  if ( !pLogger )
  {
    m_pLogger =  std::make_shared<Logger::CSimpleLogger>();
  }
  else
  {
    m_pLogger = pLogger;
  }
#endif
  CDBCInfoBuilder dbcBuilder(m_dbcInfo);
  dbcBuilder.BuildDBCInfo(dbcList);

  if ( verifyDBC )
  {
    CDBCVerifier dbcInfoVerifier(m_dbcInfo);
    if (dbcInfoVerifier.VerifyDBCInfo())
    {
      LOG(INFO, ("DBC stack initialized correctly ") )
    }
    else
    {
      LOG(ERROR, ( "DBC stack verification detected logical errors") )
    }
  }


}

void CCANMessageProcessor::Shutdown()
{

}

bool CCANMessageProcessor::DispatchCANSignal( const unsigned int msgId, const uint64_t& data)
{
  const auto messageIter = m_dbcInfo.msgId2message.find( msgId );
  if (m_dbcInfo.msgId2message.end() != messageIter )
  {
    std::get<PROCESSOR>(messageIter->second)->ProcessMessage(*(std::get<MESSAGE>(messageIter->second)),data,8);
  
    auto specificMessageListeners = std::get<MSG_LISTENERS>(messageIter->second);
    for (auto& listener: specificMessageListeners)
    {
      listener->NotifyMessageReceived(*(std::get<MESSAGE>(messageIter->second)));
    }

    for ( auto& listener: m_dbcInfo.allMessageListeners)
    {
      listener->NotifyMessageReceived(*(std::get<MESSAGE>(messageIter->second)));
    }
    return true;
  }

  return false;
}

const CMessage& CCANMessageProcessor::ProcessMessage( const unsigned int msgId, const uint64_t& data)
{
  auto messageIter = m_dbcInfo.msgId2message.find( msgId );

  if (m_dbcInfo.msgId2message.end() != messageIter )
  {
    std::get<PROCESSOR>(messageIter->second)->ProcessMessage(*(std::get<MESSAGE>(messageIter->second)),data,8);
    return *(std::get<MESSAGE>(messageIter->second));
  }

  m_dbcInfo.genericMessagePtr->SetMessageId( msgId);
  m_dbcInfo.genericMessagePtr->SetRawData( ReverseBytes(data) );
  return *(m_dbcInfo.genericMessagePtr);
}

const CMessage& CCANMessageProcessor::ProcessMessageByPGN( const unsigned int pgn, const uint64_t& data)
{
  auto messageIter = m_dbcInfo.pgn2message.find( pgn );

  if (m_dbcInfo.pgn2message.end() != messageIter )
  {
    std::get<PROCESSOR>(messageIter->second)->ProcessMessage(*(std::get<MESSAGE>(messageIter->second)),data,8);
    return *(std::get<MESSAGE>(messageIter->second));
  }
  m_dbcInfo.genericMessagePtr->SetPGN( pgn );
  m_dbcInfo.genericMessagePtr->SetRawData( ReverseBytes(data) );
  return *(m_dbcInfo.genericMessagePtr);
}

bool CCANMessageProcessor::DispatchCANSignalByPGN( const unsigned int msgId, const uint64_t& data)
{
  const auto messageIter = m_dbcInfo.pgn2message.find( msgId );
  if (m_dbcInfo.pgn2message.end() != messageIter )
  {
    std::get<PROCESSOR>(messageIter->second)->ProcessMessage(*(std::get<MESSAGE>(messageIter->second)),data,8);
    return true;
  }

  return false;
}

bool CCANMessageProcessor::SubscribeCANSignal( const unsigned int msgId, const std::string& signalName, ISignalListener& listener )
{
  const auto messageIter = m_dbcInfo.msgId2message.find( msgId );

  if (m_dbcInfo.msgId2message.end() != messageIter )
  {
    return std::get<MESSAGE>(messageIter->second)->SubscribeCANSignal(signalName,listener);
  }

  return false;
}

bool CCANMessageProcessor::SubscribeCANSignalByPGN( const unsigned int msgId, const std::string& signalName, ISignalListener& listener )
{
  const auto messageIter = m_dbcInfo.pgn2message.find( msgId );
  if (m_dbcInfo.pgn2message.end() != messageIter )
  {
    return std::get<MESSAGE>(messageIter->second)->SubscribeCANSignal(signalName,listener);
  }

  return false;
}

void CCANMessageProcessor::SubscribeAllMessages( IMessageListener& listener )
{
  m_dbcInfo.allMessageListeners.push_back(&listener);
}

bool CCANMessageProcessor::SubscribeCANMessage( const unsigned int msgId, IMessageListener& listener)
{
  const auto messageIter = m_dbcInfo.msgId2message.find( msgId );
  if (m_dbcInfo.msgId2message.end() != messageIter )
  {
    std::get<MSG_LISTENERS>(messageIter->second).push_back(&listener);
    return true;
  }

  return false;
}


const std::string& CCANMessageProcessor::GetProperty( const std::string& propertyName)
{
  const auto propertyIter = m_dbcInfo.processorPropertyMap.find(propertyName);
  if (m_dbcInfo.processorPropertyMap.end() != propertyIter )
  {
    return propertyIter->second;
  }
  return emptyString;
}

const std::string& CCANMessageProcessor::GetPropertyType( const std::string& propertyName)
{
  const auto propertyTypeIter = m_dbcInfo.propertyTypesMap.find(propertyName);
  if (m_dbcInfo.propertyTypesMap.end() != propertyTypeIter )
  {
    return propertyTypeIter->second;
  }
  return emptyString;
}

uint64_t CCANMessageProcessor::ReverseBytes( uint64_t canData)
{
  uint64_t reversedValue = 0;
  for ( int i = 0 ; i < 8 ; ++i )
  {
    reversedValue <<= 8;
    reversedValue |= ( canData & 0xFFULL );
    canData >>= 8;
  }
  return reversedValue;
}