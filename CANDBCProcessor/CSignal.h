#pragma once
#include <string>
#include <stdint.h>

class CSignal
{
    using eEndiannes = enum { bigEndian, littleEndian };

public:
    CSignal( const int start, const int length);
    ~CSignal();

    bool ExtractValue( const uint64_t& data , size_t dataLength);

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
    std::string unit;
    std::string receiver;
};