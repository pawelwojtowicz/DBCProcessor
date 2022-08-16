#pragma once
#include <map>
#include <memory>
#include "CMessage.h"

#define GET_PGN( x ) (x & 0x00FFFF00)>> 8

struct DBCInfo
{
    using tMsgId2Message = std::map<unsigned int, std::shared_ptr<CMessage>>;

    tMsgId2Message m_msgId2message;
    tMsgId2Message m_pgn2message;
};