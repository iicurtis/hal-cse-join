cmake_minimum_required(VERSION 3.5)
project(eigenblock VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(ExternalProject)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# FMT
ExternalProject_Add(Fmt
  PREFIX fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG 4.0.0
  CMAKE_CACHE_ARGS  "-DFMT_DOC:BOOL=OFF" "-DFMT_INSTALL:BOOL=ON" "-DFMT_TEST:BOOL=OFF"
  CMAKE_ARGS
	-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
)
set(FMT_INCLUDE_DIR "${CMAKE_BINARY_DIR}/fmt/include")
if (WIN32)
   set(FMT_LIB "${CMAKE_BINARY_DIR}/fmt/lib/fmt.lib")
else()
   set(FMT_LIB "${CMAKE_BINARY_DIR}/fmt/lib/libfmt.a")
endif()

add_executable(eigenblock src/eigenblock.cc)
add_dependencies(eigenblock Fmt)
target_include_directories(eigenblock PUBLIC
    ${FMT_INCLUDE_DIR}
)
target_link_libraries(eigenblock 
    Eigen3::Eigen
    ${FMT_LIB}
)
