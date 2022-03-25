#pragma once
#include "CSignal.h"
#include <string>

class IDBCEngineInit
{
public:
    virtual void AddMessage( const unsigned int canId , const std::string& name,  size_t size, const std::string& sender ) = 0;

    virtual void AddSignal( const std::string& name,
                            const unsigned int bitStart,
                            const size_t size,
                            const CSignal::eEndiannes endiannes,
                            const float scale,
                            const float offset,
                            const float min,
                            const float max,
                            const std::string& unit,
                            const std::string& receiver ) = 0;

    virtual void AddMultiplexedSignal( const std::string& name,
                            const unsigned int bitStart,
                            const size_t size,
                            const CSignal::eEndiannes endiannes,
                            const float scale,
                            const float offset,
                            const float min,
                            const float max,
                            const std::string& unit,
                            const std::string& receiver ) = 0;

    virtual void AddMessageDescription( unsigned int msgId, const std::string& description) = 0;

    virtual void AddSignalDescription( unsigned int msgId, const std::string& valueName, const std::string& description) = 0;

    virtual void SetSignalPropertyType( const std::string& valueName, const std::string& type ) = 0;
    virtual void SetMessagePropertyType( const std::string& propertyName, const std::string& propertyValue) = 0;
    virtual void SetGeneralPropertyType( const std::string& propertyName, const std::string& propertyValue) = 0;

    virtual void SetDefaultPropertyValue( const std::string& propertyName, const std::string& defaultValue ) = 0;

    virtual void SetMessageProperty( const std::string& propertyName, const unsigned int msgId, const std::string& propertyValue ) = 0;
    virtual void SetSignalProperty( const std::string& propertyName, const unsigned int msgId, const std::string& signalName, const std::string& propertyValue) = 0;
};