project ( CANDBCProcessor )

set( LOGGER_ENABLED true)

if ( LOGGER_ENABLED )
  add_compile_definitions(WITH_LOGGER)
endif()

add_library( CANDBCProcessor STATIC
  CMultiplexedMessageProcessor.cpp
  CMultiplexedMessageProcessor.h
  CSimpleMessageProcessor.cpp
  CSimpleMessageProcessor.h
  CCANMessageProcessor.cpp
  CCANMessageProcessor.h
  CDBCInfoBuilder.cpp
  CDBCInfoBuilder.h
  CDBCFileParser.cpp
  CDBCFileParser.h
  CMessageProcessor.cpp
  CMessageProcessor.h
  CMessageTemplate.cpp
  CMessageTemplate.h
  CMessage.cpp
  CMessage.h
  CSignal.cpp 
  CSignal.h
  CValueDictionary.cpp
  CValueDictionary.h
  CValueIntegrator.cpp
  CValueIntegrator.h
  CValue.cpp 
  CValue.h
  CSignalValueTemplate.cpp
  CSignalValueTemplate.h
  DBCInfo.h
  CSimpleLogger.cpp
  CSimpleLogger.h
  CLoggerMsg.cpp
  CLoggerMsg.h
  ILogger.h
  Logger.h
  CDBCVerifier.cpp
  CDBCVerifier.h
  CVerifySignalOverlay.cpp
  CVerifySignalOverlay.h
  CVerifyMultiplexIndexes.cpp
  CVerifyMultiplexIndexes.h
  CVerifyPositionLength.cpp
  CVerifyPositionLength.h
  CLowPassFilter.cpp
  CLowPassFilter.h
)
    
target_include_directories (CANDBCProcessor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})