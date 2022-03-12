#include "CSignal.h"
#include <iostream>
#include <bitset>

CSignal::CSignal( const int start, const int length)
: m_bitStart(start)
, m_bitLength(length)
, m_endiannes( bigEndian )
{
}

CSignal::~CSignal()
{
}

bool CSignal::ExtractValue( uint64_t canData , size_t dataLength)
{
    uint64_t canSignalMask(0x0);
    for (int i = 0; i < m_bitLength ; ++i)
    {   
        canSignalMask <<= 1;
        canSignalMask|= 0x1;
    }

    std::cout << std::bitset<64>(canSignalMask) << std::endl <<  std::bitset<64>(canData >> m_bitStart) << std::endl << std::bitset<64>( (canData >> m_bitStart ) & canSignalMask) << std::endl;

    uint64_t rawValue = canSignalMask & ( canData >> m_bitStart );

    std::cout << "rawValue" << std::endl;

    if ( bigEndian == m_endiannes ) 
    {
        std::cout << "if" << std::endl;

        int byteCount( m_bitLength / 8 );

        std::cout << "byte count " << byteCount << std::endl;

        if ( m_bitLength != ( byteCount * 8 ) )
        {
            ++byteCount;
        }

        std::cout << "byte count corrected " << byteCount << std::endl;

        uint64_t workingCopy(rawValue);
        rawValue = 0;

        std::cout << "workingCopy " << workingCopy << std::endl;

        for ( int i = 0 ; i < byteCount ; ++i )
        {
            rawValue <<= 8;
            std::cout << "workingCopyLoop " << std::hex << workingCopy << std::endl;
            std::cout << "rawValue   Loop " << std::hex << rawValue << std::endl;
            rawValue |= workingCopy & 0xFFULL;
            workingCopy >>= 8;
        }
    }

    std::cout << "-------------------" << std::hex << rawValue << std::endl;

    return true;
}