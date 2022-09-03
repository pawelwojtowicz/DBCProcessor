#pragma once
#include <map>
#include <memory>
#include "CMessageTemplate.h"
#include "IMessageListener.h"

#define GET_PGN( x ) (x & 0x00FFFF00)>> 8

struct DBCInfo
{
  using tMsgId2Message = std::map<unsigned int, std::shared_ptr<CMessageTemplate>>;
  using tMessageListeners = std::list<IMessageListener*>;

  tMsgId2Message msgId2message;
  tMsgId2Message pgn2message;

  tMessageListeners allMessageListeners;

  tPropertyMap processorPropertyMap;

  tPropertyMap propertyTypesMap;

  std::string dbcVersion;
};