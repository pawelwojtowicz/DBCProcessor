cmake_minimum_required( VERSION 3.10 )
project ( CANDBCProcessor )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/CANDBCProcessor )
#option( USE_MSVC_RUNTIME_LIBRARY_DLL  ON )

add_subdirectory( CANDBCProcessor )
add_subdirectory( test )