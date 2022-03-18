#pragma once
#include <string>
#include <list>
#include <map>
#include "CSignal.h"

class CMessage
{
    using tSignalList = std::list<CSignal>;
    using tMessagePropertyMap = std::map<std::string, std::string>;
public:
    CMessage();
    ~CMessage();

    void AddMessageProperty( const std::string& name, const std::string& value);
    const std::string GetMessageProperty( const std::string& name);

    tValues ProcessMessage( const uint64_t& msg , size_t msgSize );

private:
    tSignalList m_signalList;

    tMessagePropertyMap m_messagePropertyMap;
};