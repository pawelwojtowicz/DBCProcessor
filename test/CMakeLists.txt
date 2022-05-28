project ( CANDBCProcessorUnitTest )

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable( dbcProcessorTests 
    CDBCFileParserTest.cpp 
    # CSignalTest.cpp
    )

target_link_libraries( dbcProcessorTests CANDBCProcessor ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} GTest::gtest_main  pthread)
add_dependencies( dbcProcessorTests CANDBCProcessor)