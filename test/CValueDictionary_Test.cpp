#include <gtest/gtest.h>
#include <CValueDictionary.h>

TEST( CValueDictionary , Basic )
{
  CValueDictionary valueDict("0 \"Unknown\" 1 \"Inside\" 2 \"Outside\" ");

  EXPECT_EQ( valueDict.GetValueForInt(0) , "Unknown") ;
  EXPECT_EQ( valueDict.GetValueForInt(1) , "Inside") ;
  EXPECT_EQ( valueDict.GetValueForInt(2) , "Outside") ;
  EXPECT_EQ( valueDict.GetValueForInt(3) , "") ;

}

TEST( CValueDictionary , ComplexInitializerString )
{
  CValueDictionary valueDict("1 \"Open loop (insuff. eng. temp.)\" 2 \"Closed loop (oxy sens)\" 4 \"Open loop (eng. load, fuel cut)\" 8 \"Open loop (system failure)\" 16 \"Closed loop (feedback issue)\" ");

  EXPECT_EQ( valueDict.GetValueForInt(1) , "Open loop (insuff. eng. temp.)") ;
  EXPECT_EQ( valueDict.GetValueForInt(2) , "Closed loop (oxy sens)") ;
  EXPECT_EQ( valueDict.GetValueForInt(4) , "Open loop (eng. load, fuel cut)") ;
  EXPECT_EQ( valueDict.GetValueForInt(8) , "Open loop (system failure)") ;
  EXPECT_EQ( valueDict.GetValueForInt(16) , "Closed loop (feedback issue)") ;
  EXPECT_EQ( valueDict.GetValueForInt( 17) , "") ;
}



