#include "CMessage.h"
#include "ISignalListener.h"
#include <algorithm>

CMessage::CMessage(  const std::string& name, size_t msgSize, const std::string& sender )
: m_name(name)
, m_msgSize(msgSize)
, m_sender(sender)
, m_description("")
, m_signals()
, m_multiplexingSignal(m_signals.end())
{

}

CMessage::~CMessage()
{

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
