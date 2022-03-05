cmake_minimum_required( VERSION 3.10 )

option( USE_MSVC_RUNTIME_LIBRARY_DLL  ON )

add_subdirectory( googletest-main )
add_subdirectory( CANDBCProcessor )
add_subdirectory( test )