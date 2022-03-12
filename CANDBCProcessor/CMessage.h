#pragma once
#include <string>
#include <list>
#include "CSignal.h"

class CMessage
{
    using tSignalList = std::list<CSignal>;
public:
    CMessage();
    ~CMessage();

    bool ProcessMessage( const uint64_t& msg , size_t msgSize );

private:
    tSignalList m_signalList;
};