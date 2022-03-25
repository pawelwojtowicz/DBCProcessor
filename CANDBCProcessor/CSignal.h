#pragma once
#include <string>
#include <stdint.h>
#include <memory>
#include <map>
#include "ISignalInfo.h"
#include "CValue.h"

class CSignal : public ISignalInfo
{
public:
    using eEndiannes = enum { bigEndian, littleEndian };
    using tSignalPropertyMap = std::map<std::string, std::string>;

public:
    CSignal( const int start, const int length, eEndiannes endian);
    virtual ~CSignal();


    void SetDescription( const std::string& description);
    // Adds signal property during initialization
    void AddProperty( const std::string& propertyName,  const std::string& propertyValue );

    std::unique_ptr<CValue> ExtractValue( const uint64_t& data , size_t dataLength);

    /** ISignalInfo */
    const std::string& GetName() const override;
    const std::string& GetUnit() const override;
    const std::string GetProperty( const std::string& propertyName ) const override;

private:
    std::unique_ptr<CValue> CreateValue( const uint64_t);

private:
    std::string m_signalName;
    std::string m_description;
    int m_bitStart;
    int m_bitLength;
    eEndiannes m_endiannes;
    bool m_withSign;
    float m_scale;
    float m_offset;
    float m_min;
    float m_max;


    uint64_t m_canSignalMask;
    int m_byteCount;
    std::string m_unit;
    std::string receiver;

     tSignalPropertyMap m_signalPropertyMap; 
};