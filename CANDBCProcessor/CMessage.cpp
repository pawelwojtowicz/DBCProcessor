#include "CMessage.h"
#include <algorithm>

CMessage::CMessage( const int unsigned msgId, const std::string& name, size_t msgSize, const std::string& sender )
: m_msgId(msgId)
, m_name(name)
, m_msgSize(msgSize)
, m_rawData("")
, m_sender(sender)
, m_description("")
{

}

CMessage::~CMessage()
{

}

const unsigned int CMessage::GetMessageId() const
{
  return m_msgId;
}

const unsigned int CMessage::GetPGN() const
{
  return GET_PGN(m_msgId);
}

const std::string& CMessage::GetMessageName() const
{
  return m_name;
}

const std::string& CMessage::GetRawData() const
{
  return m_rawData;
}

const std::map<std::string, CValue&>& CMessage::GetSignalValue() const
{
  return m_values;
}


const std::string& CMessage::GetMessageSender() const
{
  return m_sender;
}

const std::string& CMessage::GetMessageDescription() const
{
  return m_description;
}


const std::string CMessage::GetMessageProperty( const std::string& name) const
{
  const auto propertyIter = m_messagePropertyMap.find(name);
  if ( m_messagePropertyMap.end() != propertyIter )
  {
    return propertyIter->second;
  }
  return std::string();
}
