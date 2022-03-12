project ( CANDBCProcessor )

add_library( CANDBCProcessor STATIC 
    CDBCFileParser.cpp
    CDBCFileParser.h
    CSignal.cpp 
    CSignal.h )
    
target_include_directories (CANDBCProcessor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})