
set(NOD_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/lib/nod")

add_library(nod-signal INTERFACE)
target_include_directories(
  nod-signal
  INTERFACE
    ${NOD_ROOT}/include
)

set_target_properties(
  nod-signal
  PROPERTIES
    CXX_STANDARD 11
    CXX_EXTENSIONS off
)
