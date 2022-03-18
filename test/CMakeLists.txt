project ( CANDBCProcessorUnitTest )

add_executable( dbcProcessorTests 
    CDBCFileParserTest.cpp 
    CSignalTest.cpp)

target_link_libraries( dbcProcessorTests gmock_main CANDBCProcessor )