cmake_minimum_required( VERSION 3.12 )

project( bindey LANGUAGES CXX )

if( ${CMAKE_PROJECT_NAME} STREQUAL bindey )
  set( CMAKE_CXX_STANDARD          14  ) 
  set( CMAKE_CXX_STANDARD_REQUIRED ON  )
  set( CMAKE_CXX_EXTENSIONS        OFF )
endif()

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
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR}/include FILES ${FILES_source} )

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

target_compile_features(
  bindey
  INTERFACE
    cxx_std_14
)

### Tests

if ( BINDEY_BUILD_TESTS )
  enable_testing()
  add_subdirectory( lib/Catch2 )
  list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/Catch2/contrib )
  add_subdirectory( test )
endif()
