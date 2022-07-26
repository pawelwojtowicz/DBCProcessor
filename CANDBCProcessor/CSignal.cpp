#include "CSignal.h"
#include <iostream>
#include <bitset>

CSignal::CSignal( const int start, const int length, eEndiannes endian )
: m_bitStart(start)
, m_bitLength(length)
, m_canSignalMask ( (0x1ULL << m_bitLength ) -1 )
, m_endiannes( endian )
{
    if ( bigEndian == m_endiannes )
    {
        m_bitStart = (7 - (m_bitStart/8 ) ) * 8 + m_bitStart%8 ;  
    }
}

CSignal::~CSignal()
{
}

uint64_t CSignal::ExtractValue( const uint64_t& canData , size_t dataLength)
{
    uint64_t rawValue(canData);

    if ( bigEndian == m_endiannes ) 
    {
        rawValue = 0;
        uint64_t workingCopy(canData);
        for ( int i = 0 ; i < 8 ; ++i )
        {
            rawValue <<= 8;
            rawValue |= ( workingCopy & 0xFFULL );
            workingCopy >>= 8;
        }
    }
    
    return m_canSignalMask & ( rawValue >> m_bitStart );
}