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
  using tSignalListeners = std::list<ISignalListener*>;
  using tSignalTuple = std::tuple<CSignal, CSignalValueTemplate, tSignalListeners>;
  using tSignalList = std::list<tSignalTuple>;
  using tMessagePropertyMap = std::map<std::string, std::string>;
public:
  CMessage( const std::string& name, size_t msgSize, const std::string& sender );
  virtual ~CMessage();

  const std::string GetMessageProperty( const std::string& name);

protected:
  std::string m_name;
  size_t m_msgSize;
  std::string m_sender;
  std::string m_description;

  tSignalList m_signals;
  tSignalList::iterator m_multiplexingSignal;

  tMessagePropertyMap m_messagePropertyMap;
};