#pragma once
#include <map>
#include <memory>
#include "CMessageTemplate.h"

#define GET_PGN( x ) (x & 0x00FFFF00)>> 8

struct DBCInfo
{
  using tPropertyMap = std::map<std::string, std::string>;
  using tMsgId2Message = std::map<unsigned int, std::shared_ptr<CMessageTemplate>>;

  tMsgId2Message msgId2message;
  tMsgId2Message pgn2message;

  tPropertyMap processorPropertyMap;

  tPropertyMap propertyTypesMap;
};