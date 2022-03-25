#include "CCANMessageProcessor.h"
#include "CDBCFileParser.h"

#define GET_PGN( x ) (x & 0x00FFFF00)>> 8

void CCANMessageProcessor::Initialize(  const std::vector<std::string>& dbcList )
{
    CDBCFileParser fileParser(*this);
    for ( const auto& fileName : dbcList )
    {
        fileParser.ReadDBCFile(fileName);
    }
}

void CCANMessageProcessor::Shutdown()
{

}

tValues&& CCANMessageProcessor::ProcessCANMessage( const unsigned int msgId, const uint64_t& data)
{
    tValues extractedValues;
    const auto messageIter = m_msgId2message.find( msgId );
    if (m_msgId2message.end() != messageIter )
    {
        extractedValues = messageIter->second->ProcessMessage(data,8);
    }

    return std::move(extractedValues);
}

tValues&& CCANMessageProcessor::ProcessCANMessageByPGN( const unsigned int msgId, const uint64_t& data)
{
    tValues extractedValues;
    const auto messageIter = m_pgn2message.find( GET_PGN(msgId) );
    if (m_pgn2message.end() != messageIter )
    {
        extractedValues = messageIter->second->ProcessMessage(data,8);
    }

    return std::move(extractedValues);
}


void CCANMessageProcessor::AddMessage( const unsigned int canId , const std::string& name,  size_t size, const std::string& sender )
{
    m_currentMessage = std::make_shared<CMessage>( name, size, sender);
    m_msgId2message.insert( tMsgId2Message::value_type(canId,m_currentMessage) );
    m_pgn2message.insert( tMsgId2Message::value_type( GET_PGN( canId ) , m_currentMessage));
}

void CCANMessageProcessor::AddSignal( const std::string& name,
                    const unsigned int bitStart,
                    const size_t size,
                    const CSignal::eEndiannes endiannes,
                    const float scale,
                    const float offset,
                    const float min,
                    const float max,
                    const std::string& unit,
                    const std::string& receiver )
{
    if (m_currentMessage)
    {
        m_currentMessage->AddSignal();
    }
}

void CCANMessageProcessor::AddMultiplexedSignal( const std::string& name,
                            const unsigned int bitStart,
                            const size_t size,
                            const CSignal::eEndiannes endiannes,
                            const float scale,
                            const float offset,
                            const float min,
                            const float max,
                            const std::string& unit,
                            const std::string& receiver )
{
    if (m_currentMessage)
    {
        m_currentMessage->AddMultiplexedSignal();
    }
}

void CCANMessageProcessor::AddMessageDescription( unsigned int msgId, const std::string& description)
{
    const auto messageIter = m_msgId2message.find( msgId );
    if (m_msgId2message.end() != messageIter )
    {
        messageIter->second->SetDescription(description);
    }
}

void CCANMessageProcessor::AddSignalDescription( unsigned int msgId, const std::string& valueName, const std::string& description)
{
    const auto messageIter = m_msgId2message.find( msgId );
    if (m_msgId2message.end() != messageIter )
    {
        messageIter->second->SetDescription(description);
    }
}

void CCANMessageProcessor::SetSignalPropertyType( const std::string& valueName, const std::string& type )
{

}

void CCANMessageProcessor::SetMessagePropertyType( const std::string& propertyName, const std::string& propertyValue)
{

}

void CCANMessageProcessor::SetGeneralPropertyType( const std::string& propertyName, const std::string& propertyValue)
{

}

void CCANMessageProcessor::SetDefaultPropertyValue( const std::string& propertyName, const std::string& defaultValue )
{

}

void CCANMessageProcessor::SetMessageProperty( const std::string& propertyName, const unsigned int msgId, const std::string& propertyValue )
{

}

void CCANMessageProcessor::SetSignalProperty( const std::string& propertyName, const unsigned int msgId, const std::string& signalName, const std::string& propertyValue)
{

}