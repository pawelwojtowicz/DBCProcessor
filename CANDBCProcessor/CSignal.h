#pragma once
#include <string>
#include <stdint.h>

class CSignal
{
    using eEndiannes = enum { bigEndian, littleEndian };

public:
    CSignal( const int start, const int length);
    ~CSignal();

    bool ExtractValue( uint64_t data , size_t dataLength);

private:
    std::string signalName;
    int m_bitStart;
    int m_bitLength;
    eEndiannes m_endiannes;
    bool withSign;
    float scale;
    float offset;
    float min;
    float max;
    std::string unit;
    std::string receiver;
};