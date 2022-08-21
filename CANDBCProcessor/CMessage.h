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
protected:
  using tMessagePropertyMap = std::map<std::string, std::string>;
public:
  CMessage( const int msgId, const std::string& name, size_t msgSize, const std::string& sender );
  virtual ~CMessage();

  const std::string GetMessageProperty( const std::string& name);

protected:
  int m_msgId;
  std::string m_name;
  size_t m_msgSize;
  std::string m_sender;
  std::string m_description;


  tMessagePropertyMap m_messagePropertyMap;
};