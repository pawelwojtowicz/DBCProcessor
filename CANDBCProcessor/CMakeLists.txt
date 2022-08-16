project ( CANDBCProcessor )

add_library( CANDBCProcessor STATIC 
    CCANMessageProcessor.cpp
    CCANMessageProcessor.h
    CDBCInfoBuilder.cpp
    CDBCInfoBuilder.h
    CDBCFileParser.cpp
    CDBCFileParser.h
    CMessage.cpp
    CMessage.h
    CSignal.cpp 
    CSignal.h 
    CValue.cpp 
    CValue.h
    ISignalInfo.h
    DBCInfo.h
    )
    
target_include_directories (CANDBCProcessor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})