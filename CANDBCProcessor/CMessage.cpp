#include "CMessage.h"
#include <algorithm>

CMessage::CMessage(  const std::string& name, size_t msgSize, const std::string& sender )
: m_name(name)
, m_msgSize(msgSize)
, m_sender(sender)
, m_description("")
{

}

CMessage::~CMessage()
{

}

void CMessage::SetDescription( const std::string& description)
{
    m_description = description;
}

void CMessage::AddSignalDescription( const std::string& signalName , const std::string& description)
{
    auto signalIter = std::find_if( m_signalList.begin(), 
                                    m_signalList.end(), 
                                    [signalName]( auto signal ) { return signal.GetName() == signalName; } );
    if (m_signalList.end() != signalIter )
    {
        signalIter->SetDescription( description);
    }
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