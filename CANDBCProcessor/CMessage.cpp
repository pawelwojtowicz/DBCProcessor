#include "CMessage.h"

CMessage::CMessage()
{

}

CMessage::~CMessage()
{

}

void CMessage::AddMessageProperty( const std::string& name, const std::string& value)
{
    m_messagePropertyMap.insert( tMessagePropertyMap::value_type(name, value));
}

const std::string CMessage::GetMessageProperty( const std::string& name)
{
    const auto propertyIter = m_messagePropertyMap.find(name);
    if ( m_messagePropertyMap.end() != propertyIter )
    {
        return propertyIter->second;
    }
    return std::string();
}

tValues CMessage::ProcessMessage( const uint64_t& msg , size_t msgSize )
{
    tValues extractedValues;
    for( auto signal : m_signalList)
    {
        extractedValues.push_back(signal.ExtractValue(msg,msgSize));
    }

    return extractedValues;
}