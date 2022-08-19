#pragma once
#include <tuple>
#include <string>
#include <map>
#include <list>
#include "DBCProcessor.h"
#include "CSignal.h"
#include "CValue.h"

class ISignalListener;

class CMessage
{
    using tSignalListeners = std::list<ISignalListener*>;
    using tSignalTuple = std::tuple<CSignal, CValue, tSignalListeners>;
    using tSignalList = std::map<std::string, tSignalTuple>;
    using tMessagePropertyMap = std::map<std::string, std::string>;
public:
    CMessage( const std::string& name, size_t msgSize, const std::string& sender );
    virtual ~CMessage();

    void AddSignal( const std::string& name,
                    const unsigned int bitStart,
                    const size_t size,
                    const CSignal::eEndiannes endiannes,
                    const tValueProperties& tValueProperties,
                    const std::string& unit,
                    const std::string& receiver);
    void AddMultiplexedSignal(  const std::string& name,
                                const unsigned int bitStart,
                                const size_t size,
                                const CSignal::eEndiannes endiannes,
                                const tValueProperties& tValueProperties,
                                const std::string& unit,
                                const std::string& receiver);

    void SetDescription( const std::string& description );
    void SetSignalDescription( const std::string& signalName , const std::string& description);
    void SetSignalProperty( const std::string& signalName, const std::string& propertyName, const std::string& propertyValue);
    void AddMessageProperty( const std::string& name, const std::string& value);
    const std::string GetMessageProperty( const std::string& name);

    bool SubscribeCANSignal( const std::string& signalName, ISignalListener& signalListener);

    void ProcessMessage( const uint64_t& msg , size_t msgSize );

private:
    std::string m_name;
    size_t m_msgSize;
    std::string m_sender;
    std::string m_description;

    tSignalList m_signals;

    tMessagePropertyMap m_messagePropertyMap;
};