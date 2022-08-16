#pragma once
#include "DBCInfo.h"
#include <vector>

class ISignalListenerl;

class CCANMessageProcessor
{
public:
    void Initialize(  const std::vector<std::string>& dbcList );
    void Shutdown();

    bool ProcessCANMessage( const unsigned int, const uint64_t& data);
    bool ProcessCANMessageByPGN( const unsigned int, const uint64_t& data);

    bool SubscribeCANSignal( const unsigned int msgId, const std::string& signalName, ISignalListener& listener );

private:
    DBCInfo m_dbcInfo;
};