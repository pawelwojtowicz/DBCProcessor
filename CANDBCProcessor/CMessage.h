#pragma once
#include <tuple>
#include <string>
#include <map>
#include <list>
#include "DBCProcessor.h"
#include "CSignal.h"
#include "CSignalValueTemplate.h"

class ISignalListener;

class CMessage
{
public:
  CMessage( const unsigned int msgId, const std::string& name, size_t msgSize, const std::string& sender );
  virtual ~CMessage();

  const unsigned int GetMessageId() const;
  const std::string& GetMessageName() const;
  const std::string& GetMessageSender() const;
  const std::string& GetMessageDescription() const;

  const std::string GetMessageProperty( const std::string& name);

protected:
  unsigned int m_msgId;
  std::string m_name;
  size_t m_msgSize;
  std::string m_sender;
  std::string m_description;


  tPropertyMap m_messagePropertyMap;
};