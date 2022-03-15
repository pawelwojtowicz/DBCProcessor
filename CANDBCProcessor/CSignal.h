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
    ~CSignal();

    std::unique_ptr<CValue> ExtractValue( const uint64_t& data , size_t dataLength);

private:
    /** ISignalInfo */
    const std::string& GetName() override;
    const std::string& GetUnit() override;
    const std::string GetProperty( const std::string& propertyName ) override;

private:
    std::unique_ptr<CValue> CreateValue( const uint64_t);

private:
    std::string m_signalName;
    int m_bitStart;
    int m_bitLength;
    uint64_t m_canSignalMask;
    int m_byteCount;
    eEndiannes m_endiannes;
    bool withSign;
    float scale;
    float offset;
    float min;
    float max;
    std::string m_unit;
    std::string receiver;

     tSignalPropertyMap m_signalPropertyMap; 
};