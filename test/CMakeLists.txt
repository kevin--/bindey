
list( APPEND SOURCE_tests property.test.cpp )
list( APPEND SOURCE_tests main.cpp )

add_executable( bindey-test ${SOURCE_tests} )
target_link_libraries(
  bindey-test
  PRIVATE
    bindey
    Catch2::Catch2
)

if( UNIX AND (CMAKE_CXX_COMPILER_ID STREQUAL "Clang") )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -v")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
endif()

### add tests to CTest
include(CTest)
include(Catch)
catch_discover_tests(bindey-test)
