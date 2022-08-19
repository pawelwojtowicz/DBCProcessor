#include "CMessage.h"
#include "ISignalListener.h"
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

void CMessage::AddSignal(   const std::string& name,
                            const unsigned int bitStart,
                            const size_t size,
                            const CSignal::eEndiannes endiannes,
                            const tValueProperties& valueProperties,
                            const std::string& unit,
                            const std::string& receiver)
{
  tSignalTuple signalTuple = std::make_tuple<CSignal,CValue>( CSignal( bitStart,size,endiannes), 
                                                              CValue( valueProperties.offset,valueProperties.scale,valueProperties.min,valueProperties.max,unit,receiver ),
                                                              tSignalListeners() );
  m_signals.insert( tSignalList::value_type( name, signalTuple));
}

void CMessage::AddMultiplexedSignal(    const std::string& name,
                                        const unsigned int bitStart,
                                        const size_t size,
                                        const CSignal::eEndiannes endiannes,
                                        const tValueProperties& tValueProperties,
                                        const std::string& unit,
                                        const std::string& receiver)
{
    
}


void CMessage::SetSignalDescription( const std::string& signalName , const std::string& description)
{
  auto signalIter = m_signals.find(signalName);

  if (m_signals.end() != signalIter )
  {
    std::get<1>(signalIter->second).SetDescription( description);
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

void CMessage::ProcessMessage( const uint64_t& msg , size_t msgSize )
{
  for( auto signal : m_signals)
  {
    const auto value = std::get<0>(signal.second).ExtractValue(msg,msgSize); 
    std::get<1>(signal.second).UpdateValue(value);
    for( auto listener : std::get<2>(signal.second ) )
    {
      listener->NotifySignaReceived( 0x0F004, std::get<1>(signal.second) );
    }
  }
}

void CMessage::SetSignalProperty( const std::string& signalName, const std::string& propertyName, const std::string& propertyValue)
{
  auto signalIter = m_signals.find(signalName);

  if (m_signals.end() != signalIter )
  {
    std::get<1>(signalIter->second).AddProperty( propertyName, propertyValue);
  }
}

bool CMessage::SubscribeCANSignal( const std::string& signalName, ISignalListener& signalListener)
{
  auto signalIter = m_signals.find(signalName);

  if (m_signals.end() != signalIter )
  {
    std::get<2>(signalIter->second).push_back( &signalListener );
    return true;
  }
  return false;
}
