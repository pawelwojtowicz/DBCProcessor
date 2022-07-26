#include <gtest/gtest.h>
#include <CSignal.h>

TEST( CSignal , BasicDeserialize_BigEndian )
{
    uint64_t candata = 0x1032547698BADCFE;
    CSignal signalProcessor(16,16, CSignal::bigEndian );

    EXPECT_EQ( static_cast<unsigned int> (signalProcessor.ExtractValue(candata, 8)) , 0xDCBAUL) ;
}

TEST( CSignal , BasicDeserialize_LittleEndian )
{
    uint64_t candata = 0x1032547698BADCFE;
    CSignal signalProcessor(16,16, CSignal::littleEndian );
    EXPECT_EQ( static_cast<unsigned int>(signalProcessor.ExtractValue(candata, 8)) , 0x98BAUL) ;
}

TEST( CSignal , ShortDeserialize_BigEndian )
{
    uint64_t candata = 0x1032547698BADCFE;
    CSignal signalProcessor(18,4, CSignal::bigEndian );
    EXPECT_EQ( static_cast<unsigned int> (signalProcessor.ExtractValue(candata, 8) ) , 0x0E) ;
}

TEST( CSignal , ShortDeserialize_LittleEndian )
{
    uint64_t candata = 0x1032547698BADCFE;
    CSignal signalProcessor(18,4, CSignal::littleEndian );    
    EXPECT_EQ( static_cast<unsigned int>(signalProcessor.ExtractValue(candata, 8)) , 0x0E) ;
}

TEST( CSignal , ShortDeserializeBetweenBytes_BigEndian )
{
    uint64_t candata = 0x1032547698BADCFE;
    CSignal signalProcessor(30,6, CSignal::bigEndian );
    EXPECT_EQ( static_cast<unsigned int> (signalProcessor.ExtractValue(candata, 8) ) , 0x2A) ;
}

TEST( CSignal , ShortDeserializeBetweenBytes_LittleEndian )
{
    uint64_t candata = 0x1032547698BADCFE;
    CSignal signalProcessor(30,6, CSignal::littleEndian );
    EXPECT_EQ( static_cast<unsigned int>(signalProcessor.ExtractValue(candata, 8)) , 0x1A) ;
}
