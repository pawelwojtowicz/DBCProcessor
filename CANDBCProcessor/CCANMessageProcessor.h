#pragma once
#include <vector>
#include <memory>
#include "CMessage.h"
#include "IDBCEngineInit.h"

class CCANMessageProcessor : public IDBCEngineInit
{
    using tMsgId2Message = std::map<unsigned int, std::unique_ptr<CMessage>>;

public:
    void Initialize(  const std::vector<std::string>& dbcList );
    void Shutdown();

    tValues&& ProcessCANMessage( const unsigned int, const uint64_t& data);

private:
    // IDBCEngineInit
    void AddMessage( const unsigned int canId , const std::string& name,  size_t size, const std::string& sender ) override;

    void AddSignal( const std::string& name,
                    const unsigned int bitStart,
                    const size_t size,
                    const CSignal::eEndiannes endiannes,
                    const float scale,
                    const float offset,
                    const float min,
                    const float max,
                    const std::string& unit,
                    const std::string& receiver ) override;

    void AddMultiplexedSignal( const std::string& name,
                            const unsigned int bitStart,
                            const size_t size,
                            const CSignal::eEndiannes endiannes,
                            const float scale,
                            const float offset,
                            const float min,
                            const float max,
                            const std::string& unit,
                            const std::string& receiver ) override;

    void AddMessageDescription( unsigned int msgId, const std::string& description) override;

    void AddSignalDescriptin( unsigned int msgId, const std::string& valueName, const std::string& description) override;

    void SetSignalPropertyType( const std::string& valueName, const std::string& type ) override;
    void SetMessagePropertyType( const std::string& propertyName, const std::string& propertyValue) override;
    void SetGeneralPropertyType( const std::string& propertyName, const std::string& propertyValue) override;

    void SetDefaultPropertyValue( const std::string& propertyName, const std::string& defaultValue ) override;

    void SetMessageProperty( const std::string& propertyName, const unsigned int msgId, const std::string& propertyValue ) override;
    void SetSignalProperty( const std::string& propertyName, const unsigned int msgId, const std::string& signalName, const std::string& propertyValue) override;

private:
    tMsgId2Message m_messages;
};