#include "CCANMessageProcessor.h"

void CCANMessageProcessor::Initialize(  const std::vector<std::string>& dbcList )
{

}

void CCANMessageProcessor::Shutdown()
{

}

tValues&& CCANMessageProcessor::ProcessCANMessage( const unsigned int msgId, const uint64_t& data)
{
    tValues extractedValues;

    const auto messageIter = m_messages.find( msgId );

    if (m_messages.end() != messageIter )
    {
        extractedValues = messageIter->second->ProcessMessage(data,8);
    }

    return std::move(extractedValues);
}

void CCANMessageProcessor::AddMessage( const unsigned int canId , const std::string& name,  size_t size, const std::string& sender )
{

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

}

void CCANMessageProcessor::AddMessageDescription( unsigned int msgId, const std::string& description)
{

}

void CCANMessageProcessor::AddSignalDescriptin( unsigned int msgId, const std::string& valueName, const std::string& description)
{

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
