#pragma once
#include <string>
#include <memory>
#include <map>
#include "ISignalInfo.h"

class CValue
{
  using tSignalPropertyMap = std::map<std::string, std::string>;
public:
    CValue( float offset , float scale, float min, float max , const std::string& unit, const std::string& receiver);
    virtual ~CValue();

    void AddProperty( const std::string& propertyName,  const std::string& propertyValue );
    void UpdateValue( const uint64_t rawValue );

    const ISignalInfo& GetSignalInfo();
    const uint64_t& GetRawValue() const;
    virtual bool GetValue( int& value ) const;
    virtual bool GetValue( float& value) const ;
    virtual bool GetValue( std::string& value ) const;
private:
    uint64_t m_rawValue;

    float m_offset;
    float m_scale;
    float m_min;
    float m_max;

    std::string m_name;
    std::string m_receiver;
    std::string m_unit;
    std::string m_description;

    tSignalPropertyMap m_signalPropertyMap;
};