#include "CMessageTemplate.h"
#include "ISignalListener.h"
#include <utility>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>

CMessageTemplate::CMessageTemplate(const unsigned int msgId, const std::string& name, size_t msgSize, const std::string& sender)
: CMessage(msgId, name, msgSize, sender)
, m_signals()

{

}

CMessageTemplate::~CMessageTemplate()
{

}

void CMessageTemplate::SetMessageId( const unsigned int msgId)
{
  m_msgId = msgId;
  m_pgn = GET_PGN(msgId);
}

void CMessageTemplate::SetPGN( const unsigned int pgn)
{
  m_msgId = 0;
  m_pgn = pgn;
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
  }
  else
  {
    m_signals.push_back(signalTuple);
  }    
}

void CMessageTemplate::SetSignalDescription( const std::string& signalName , const std::string& description)
{
  auto signalIter = std::find_if(m_signals.begin(), m_signals.end(), [signalName](const auto& signalTuple) { return signalName == std::get<VALUE>(signalTuple).GetName();} );

  if (m_signals.end() != signalIter )
  {
    std::get<VALUE>(*signalIter).SetDescription( description);
  }
}

void CMessageTemplate::AddMessageProperty( const std::string& name, const std::string& value)
{
  m_messagePropertyMap.insert( tPropertyMap::value_type(name, value));
}

void CMessageTemplate::SetRawData( const uint64_t& rawData)
{
  std::stringstream rawDataBuilder;
  int msgSize = 8;//think how to set up the value in a correct way (dynamically)
  rawDataBuilder << std::hex << std::setfill('0') << std::setw( msgSize*2) << rawData;
  m_rawData = rawDataBuilder.str();
}

void CMessageTemplate::SetSignalProperty( const std::string& signalName, const std::string& propertyName, const std::string& propertyValue)
{
  auto signalIter = std::find_if(m_signals.begin(), m_signals.end(), [signalName](const auto& signalTuple) { return signalName == std::get<VALUE>(signalTuple).GetName();} );

  if (m_signals.end() != signalIter )
  {
    std::get<VALUE>(*signalIter).AddProperty( propertyName, propertyValue);
  }
}

bool CMessageTemplate::SubscribeCANSignal( const std::string& signalName, ISignalListener& signalListener)
{
  auto signalIter = std::find_if(m_signals.begin(), m_signals.end(), [signalName](const auto& signalTuple) { return signalName == std::get<VALUE>(signalTuple).GetName();} );

  if (m_signals.end() != signalIter )
  {
    std::get<LISTENERS>(*signalIter).push_back( &signalListener );
    return true;
  }
  return false;
}

void CMessageTemplate::SetSignalValueDictonary( const std::string& signalName, const std::string& initializerString)
{
  auto signalIter = std::find_if(m_signals.begin(), m_signals.end(), [signalName](const auto& signalTuple) { return signalName == std::get<VALUE>(signalTuple).GetName();} );

  if (m_signals.end() != signalIter )
  {
    std::get<VALUE>(*signalIter).SetValueDictionary(initializerString);
  }
}

bool CMessageTemplate::IsMultiplexedMessage()
{
  for ( const auto& signal: m_signals)
  {
    if ( cMultiplexerIndexField == std::get<MULTIPLEXERID>(signal) )
    {
      return true;
    }
  }
  return false;
}

void  CMessageTemplate::BuildDefaultValueMap()
{
  for ( auto& signal: m_signals)
  {
    m_values.insert(std::map<std::string, CValue&>::value_type(std::get<VALUE>(signal).GetName(),std::get<VALUE>(signal)));
  }
}

const CMessageTemplate::tSignalList& CMessageTemplate::GetMessageSignals() const
{
  return m_signals;
}

CMessageTemplate::tSignalList& CMessageTemplate::GetMessageSignals()
{
  return m_signals;
}