#pragma once
#include <map>
#include <memory>
#include <tuple>
#include "CMessageTemplate.h"
#include "IMessageListener.h"


#define MESSAGE 0
#define MSG_LISTENERS 1

struct DBCInfo
{
  using tMessageListeners = std::list<IMessageListener*>;
  using tMessageMapEntry = std::tuple<std::shared_ptr<CMessageTemplate>,tMessageListeners>;
  using tMsgId2Message = std::map<unsigned int, tMessageMapEntry>;


  tMsgId2Message msgId2message;
  tMsgId2Message pgn2message;

  std::shared_ptr<CMessageTemplate> genericMessagePtr;

  tMessageListeners allMessageListeners;

  tPropertyMap processorPropertyMap;

  tPropertyMap propertyTypesMap;

  std::string dbcVersion;
};