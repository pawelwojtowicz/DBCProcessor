#include <gtest/gtest.h>
#include <CSignal.h>

TEST( CSignal , BasicDeserialize_BigEndian )
{
    uint64_t candata = 0x1122334455667788;
    CSignal signalProcessor(16,16, CSignal::bigEndian );

    EXPECT_EQ( static_cast<unsigned int> (signalProcessor.ExtractValue(candata, 8)) , 0x6655UL) ;
}

TEST( CSignal , BasicDeserialize_LittleEndian )
{
    uint64_t candata = 0x1122334455667788;
    CSignal signalProcessor(16,16, CSignal::littleEndian );
    EXPECT_EQ( static_cast<unsigned int>(signalProcessor.ExtractValue(candata, 8)) , 0x5566UL) ;
}

TEST( CSignal , ShortDeserialize_BigEndian )
{
    uint64_t candata = 0x1122334455667788;
    CSignal signalProcessor(18,4, CSignal::bigEndian );
    EXPECT_EQ( static_cast<unsigned int> (signalProcessor.ExtractValue(candata, 8) ) , 0x24UL) ;
}

TEST( CSignal , ShortDeserialize_LittleEndian )
{
    uint64_t candata = 0x1122334455667788;
    CSignal signalProcessor(18,4, CSignal::littleEndian );
    EXPECT_EQ( static_cast<unsigned int>(signalProcessor.ExtractValue(candata, 8)) , 0x24UL) ;
}
