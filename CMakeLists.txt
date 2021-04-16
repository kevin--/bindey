cmake_minimum_required( VERSION 3.12 )

project( bindey LANGUAGES CXX )

### Options
option( BINDEY_BUILD_TESTS           "Build Tests"             OFF )
option( BINDEY_USE_BUNDLED_NODSIGNAL "Use Bundled nod::signal" ON  )
set( BINDEY_NODSIGNAL_TARGET         "nod-signal" CACHE STRING
     "If your build system supplies nod signal as a CMake Target override this with your library name" )

### Find nod-signal
if( BINDEY_USE_BUNDLED_NODSIGNAL )
  list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake )
  find_package( nod-signal REQUIRED )
endif()

### Library

list( APPEND FILES_source include/bindey/property.h )
source_group( TREE include FILES ${FILES_source} )

add_library( bindey INTERFACE ${FILES_source} )
target_include_directories(
  bindey
  INTERFACE
    include
)

target_link_libraries(
  bindey
  INTERFACE
    ${BINDEY_NODSIGNAL_TARGET}
)

set_target_properties(
  bindey
  PROPERTIES
    CXX_STANDARD 11
    CXX_EXTENSIONS off
)

### Tests

if ( BINDEY_BUILD_TESTS )
  add_subdirectory( lib/Catch2 )
  add_subdirectory( test )
endif()
