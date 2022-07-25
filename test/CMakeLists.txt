project ( CANDBCProcessorUnitTest )

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable( dbcProcessorTests 
    CDBCFileParserTest.cpp 
    CSignalTest.cpp
    )

target_link_libraries( dbcProcessorTests CANDBCProcessor gtest gmock gtest_main pthread)
add_dependencies( dbcProcessorTests CANDBCProcessor)