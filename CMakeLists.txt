cmake_minimum_required(VERSION 3.5)
project(diagblock VERSION 0.0.1)

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
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
find_package(BLAS REQUIRED)
find_package(GSL REQUIRED)

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

# Blaze
# ExternalProject_Add(Blaze
  # PREFIX blaze
  # GIT_REPOSITORY https://bitbucket.org/blaze-lib/blaze
  # CMAKE_CACHE_ARGS  "-DFMT_DOC:BOOL=OFF" "-DFMT_INSTALL:BOOL=ON" "-DFMT_TEST:BOOL=OFF"
  # CMAKE_ARGS
	# -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
# )
# set(BLAZE_INCLUDE_DIR "${CMAKE_BINARY_DIR}/blaze/include")
# set(BLAZE_LIB "${CMAKE_BINARY_DIR}/blaze/lib/")

add_executable(diagblock
    src/main.cc 
    src/eigenblock.cc
    src/gslblock.cc
    src/diagblock.cc
)

add_dependencies(diagblock Fmt)
target_include_directories(diagblock PUBLIC
    ${FMT_INCLUDE_DIR}
    ${BLAS_INCLUDE_DIR}
)
target_link_libraries(diagblock 
    Eigen3::Eigen
    ${FMT_LIB}
    blas
    gsl
)
