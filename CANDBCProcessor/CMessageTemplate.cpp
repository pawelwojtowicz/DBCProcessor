#include "CMessageTemplate.h"
#include "ISignalListener.h"
#include <utility>
#include <algorithm>
#include <iostream>
CMessageTemplate::CMessageTemplate(const int msgId, const std::string& name, size_t msgSize, const std::string& sender)
: CMessage(msgId, name, msgSize, sender)
, m_signals()

{

}

CMessageTemplate::~CMessageTemplate()
{

}

void CMessageTemplate::SetDescription( const std::string& description)
{
  m_description = description;
}

void CMessageTemplate::AddSignal( const std::string& name,
                                  const int multiplexId,
                                  const unsigned int bitStart,
                                  const size_t size,
                                  const CSignal::eEndiannes endiannes,
                                  const tSignalValueProperties& valueProperties,
                                  const std::string& unit,
                                  const std::string& receiver)
{
  tSignalTuple signalTuple = std::make_tuple( multiplexId, 
                                              CSignal( bitStart,size,endiannes), 
                                              CSignalValueTemplate( name, valueProperties.offset,valueProperties.scale,valueProperties.min,valueProperties.max,unit,receiver ),
                                              tSignalListeners() );

  if ( cMultiplexerIndexField == multiplexId )
  {
    m_signals.push_front(signalTuple);
    m_multiplexingSignal = m_signals.begin(); 
  }
  else
  {
    m_signals.push_back(signalTuple);
  }    
}

void CMessageTemplate::SetSignalDescription( const std::string& signalName , const std::string& description)
{
  auto signalIter = std::find_if(m_signals.begin(), m_signals.end(), [signalName](const auto& signalTuple) { return signalName == std::get<2>(signalTuple).GetName();} );

  if (m_signals.end() != signalIter )
  {
    std::get<2>(*signalIter).SetDescription( description);
  }
}

void CMessageTemplate::AddMessageProperty( const std::string& name, const std::string& value)
{
  m_messagePropertyMap.insert( tPropertyMap::value_type(name, value));
}

void CMessageTemplate::ProcessMessage( const uint64_t& msg , size_t msgSize )
{
  int multiplexedId(cStaticIndexField);
  for( auto signal : m_signals)
  {
    const auto signalMultiplexId =  std::get<0>(signal);
    if (  signalMultiplexId < 0 || multiplexedId == signalMultiplexId )
    {
      std::get<2>(signal).UpdateValue( std::get<1>(signal).ExtractValue(msg,msgSize) );
      
      if ( signalMultiplexId == cMultiplexerIndexField)
      {
        multiplexedId = std::get<2>(signal).GetValueINT();
      }

      for( auto listener : std::get<3>(signal ) )
      {
        listener->NotifySignaReceived( m_msgId, std::get<2>(signal) );
      }
    }
  }
}

void CMessageTemplate::SetSignalProperty( const std::string& signalName, const std::string& propertyName, const std::string& propertyValue)
{
  auto signalIter = std::find_if(m_signals.begin(), m_signals.end(), [signalName](const auto& signalTuple) { return signalName == std::get<2>(signalTuple).GetName();} );

  if (m_signals.end() != signalIter )
  {
    std::get<2>(*signalIter).AddProperty( propertyName, propertyValue);
  }
}

bool CMessageTemplate::SubscribeCANSignal( const std::string& signalName, ISignalListener& signalListener)
{
  auto signalIter = std::find_if(m_signals.begin(), m_signals.end(), [signalName](const auto& signalTuple) { return signalName == std::get<2>(signalTuple).GetName();} );

  if (m_signals.end() != signalIter )
  {
    std::get<3>(*signalIter).push_back( &signalListener );
    return true;
  }
  return false;
}

void CMessageTemplate::SetSignalValueDictonary( const std::string& signalName, const std::string& initializerString)
{
  auto signalIter = std::find_if(m_signals.begin(), m_signals.end(), [signalName](const auto& signalTuple) { return signalName == std::get<2>(signalTuple).GetName();} );

  if (m_signals.end() != signalIter )
  {
    std::get<2>(*signalIter).SetValueDictionary(initializerString);
  }
}