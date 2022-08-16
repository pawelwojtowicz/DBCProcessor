#include "CDBCInfoBuilder.h"
#include "DBCInfo.h"
#include "CDBCFileParser.h"

CDBCInfoBuilder::CDBCInfoBuilder( DBCInfo& dbcInfo)
: m_dbcInfo(dbcInfo)
{    
}

bool CDBCInfoBuilder::BuildDBCInfo(const std::vector<std::string>& dbcList)
{

    CDBCFileParser fileParser(*this);
    for( const auto& fileName : dbcList )
    {
        fileParser.ReadDBCFile(fileName);
    }

    return true;
}

void CDBCInfoBuilder::AddMessage( const unsigned int canId , const std::string& name,  size_t size, const std::string& sender )
{
  m_currentMessage = std::make_shared<CMessage>( name, size, sender);
  m_dbcInfo.m_msgId2message.insert( DBCInfo::tMsgId2Message::value_type(canId,m_currentMessage) );
  m_dbcInfo.m_pgn2message.insert( DBCInfo::tMsgId2Message::value_type( GET_PGN( canId ) , m_currentMessage));
}

void CDBCInfoBuilder::AddSignal( const std::string& name,
                    const unsigned int bitStart,
                    const size_t size,
                    const int endiannes,
                    const float scale,
                    const float offset,
                    const float min,
                    const float max,
                    const std::string& unit,
                    const std::string& receiver )
{
    tValueProperties signalValueProperties;
    signalValueProperties.min = min;
    signalValueProperties.max = max;
    signalValueProperties.offset = offset;
    signalValueProperties.scale = scale;

    CSignal::eEndiannes sgEndiannes = ( endiannes != 1 ) ? CSignal::bigEndian : CSignal::littleEndian;

    if (m_currentMessage)
    {
        m_currentMessage->AddSignal( name,bitStart,size,sgEndiannes,signalValueProperties,unit,receiver);
    }
}

void CDBCInfoBuilder::AddMultiplexedSignal( const std::string& name,
                            const unsigned int bitStart,
                            const size_t size,
                            const int endiannes,
                            const float scale,
                            const float offset,
                            const float min,
                            const float max,
                            const std::string& unit,
                            const std::string& receiver )
{
    tValueProperties signalValueProperties;
    signalValueProperties.min = min;
    signalValueProperties.max = max;
    signalValueProperties.offset = offset;
    signalValueProperties.scale = scale;

    CSignal::eEndiannes sgEndiannes = ( endiannes != 1 ) ? CSignal::bigEndian : CSignal::littleEndian;

    if (m_currentMessage)
    {
        m_currentMessage->AddMultiplexedSignal( name,bitStart,size,sgEndiannes ,signalValueProperties,unit,receiver);
    }
}

void CDBCInfoBuilder::AddMessageDescription( unsigned int msgId, const std::string& description)
{
    const auto messageIter = m_dbcInfo.m_msgId2message.find( msgId );
    if (m_dbcInfo.m_msgId2message.end() != messageIter )
    {
        messageIter->second->SetDescription(description);
    }
}

void CDBCInfoBuilder::AddSignalDescription( unsigned int msgId, const std::string& valueName, const std::string& description)
{
    const auto messageIter = m_dbcInfo.m_msgId2message.find( msgId );
    if (m_dbcInfo.m_msgId2message.end() != messageIter )
    {
        messageIter->second->SetSignalDescription(valueName,description);
    }
}

void CDBCInfoBuilder::SetSignalPropertyType( const std::string& valueName, const std::string& type )
{

}

void CDBCInfoBuilder::SetMessagePropertyType( const std::string& propertyName, const std::string& propertyValue)
{

}

void CDBCInfoBuilder::SetGeneralPropertyType( const std::string& propertyName, const std::string& propertyValue)
{

}

void CDBCInfoBuilder::SetDefaultPropertyValue( const std::string& propertyName, const std::string& defaultValue )
{

}

void CDBCInfoBuilder::SetMessageProperty( const std::string& propertyName, const unsigned int msgId, const std::string& propertyValue )
{
    const auto messageIter = m_dbcInfo.m_msgId2message.find( msgId );
    if (m_dbcInfo.m_msgId2message.end() != messageIter )
    {
        messageIter->second->AddMessageProperty(propertyName,propertyValue);
    }

}

void CDBCInfoBuilder::SetSignalProperty( const std::string& propertyName, const unsigned int msgId, const std::string& signalName, const std::string& propertyValue)
{
    const auto messageIter = m_dbcInfo.m_msgId2message.find( msgId );
    if (m_dbcInfo.m_msgId2message.end() != messageIter )
    {
        messageIter->second->SetSignalProperty(signalName, propertyName,propertyValue);
    }
}