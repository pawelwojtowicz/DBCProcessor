#pragma once
#include <string>
#include <stdint.h>

class CSignal
{
public:
    using eEndiannes = enum { bigEndian, littleEndian };

public:
    CSignal( const int start, const int length, eEndiannes endian );
    virtual ~CSignal();


    void SetDescription( const std::string& description);
    // Adds signal property during initialization
    void AddProperty( const std::string& propertyName,  const std::string& propertyValue );

    uint64_t ExtractValue( const uint64_t& data , size_t dataLength);

private:
    int m_bitStart;
    int m_bitLength;
    eEndiannes m_endiannes;
    bool m_withSign;

    uint64_t m_canSignalMask;
    int m_byteCount;
    std::string m_unit;
    std::string receiver; 
};