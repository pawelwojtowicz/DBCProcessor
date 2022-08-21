#include "CMessageTemplate.h"
#include "ISignalListener.h"

CMessageTemplate::CMessageTemplate(const std::string& name, size_t msgSize, const std::string& sender)
: CMessage(name, msgSize, sender)
{

}

CMessageTemplate::~CMessageTemplate()
{

}

void CMessageTemplate::SetDescription( const std::string& description)
{
  m_description = description;
}

void CMessageTemplate::AddSignal(   const std::string& name,
                            const unsigned int bitStart,
                            const size_t size,
                            const CSignal::eEndiannes endiannes,
                            const tSignalValueProperties& valueProperties,
                            const std::string& unit,
                            const std::string& receiver)
{
  tSignalTuple signalTuple = std::make_tuple<CSignal,CSignalValueTemplate>( CSignal( bitStart,size,endiannes), 
                                                              CSignalValueTemplate( name,valueProperties.offset,valueProperties.scale,valueProperties.min,valueProperties.max,unit,receiver ),
                                                              tSignalListeners() );
  m_signals.insert( tSignalList::value_type( name, signalTuple));
}

void CMessageTemplate::AddMultiplexedSignal(    const std::string& name,
                                        const int multiplexId,
                                        const unsigned int bitStart,
                                        const size_t size,
                                        const CSignal::eEndiannes endiannes,
                                        const tSignalValueProperties& valueProperties,
                                        const std::string& unit,
                                        const std::string& receiver)
{
  tSignalTuple signalTuple = std::make_tuple<CSignal,CSignalValueTemplate>( CSignal( bitStart,size,endiannes), 
                                                              CSignalValueTemplate( name, valueProperties.offset,valueProperties.scale,valueProperties.min,valueProperties.max,unit,receiver ),
                                                              tSignalListeners() );
    
  m_signals.insert( tSignalList::value_type( name, signalTuple) );
  m_multiplexingSignal = m_signals.find(  name );
}


void CMessageTemplate::SetSignalDescription( const std::string& signalName , const std::string& description)
{
  auto signalIter = m_signals.find(signalName);

  if (m_signals.end() != signalIter )
  {
    std::get<1>(signalIter->second).SetDescription( description);
  }
}

void CMessageTemplate::AddMessageProperty( const std::string& name, const std::string& value)
{
  m_messagePropertyMap.insert( tMessagePropertyMap::value_type(name, value));
}

void CMessageTemplate::ProcessMessage( const uint64_t& msg , size_t msgSize )
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

void CMessageTemplate::SetSignalProperty( const std::string& signalName, const std::string& propertyName, const std::string& propertyValue)
{
  auto signalIter = m_signals.find(signalName);

  if (m_signals.end() != signalIter )
  {
    std::get<1>(signalIter->second).AddProperty( propertyName, propertyValue);
  }
}

bool CMessageTemplate::SubscribeCANSignal( const std::string& signalName, ISignalListener& signalListener)
{
  auto signalIter = m_signals.find(signalName);

  if (m_signals.end() != signalIter )
  {
    std::get<2>(signalIter->second).push_back( &signalListener );
    return true;
  }
  return false;
}