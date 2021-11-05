cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(laplace)

enable_language(CXX)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

add_library(laplace_lib)
add_compile_options(-Wall -Wextra -pedantic)

find_package(Eigen3 REQUIRED NO_MODULE)
find_package(QUADMATH)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
	add_definitions(-DGNU_CXX)
	message(STATUS "Using quad type __float128 (GNU)")
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Intel")
	add_definitions(-DINTEL_CXX)
	target_compile_options(laplace_lib PUBLIC "-Qoption,cpp,--extended_float_type")
	message(STATUS "Using quad type _Quad (Intel)")
endif()	

set(LAPLACE_INSTALL ${CMAKE_INSTALL_PREFIX})
set(LAPLACE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/src/minimax_read.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/src/minimax_read.cpp @ONLY
)

target_sources(
	laplace_lib
	PUBLIC
	src/minimax.cpp
        src/minimax_maehly.cpp
        src/minimax_paraopt.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/src/minimax_read.cpp
)

target_link_libraries(
	laplace_lib
	quadmath
	Eigen3::Eigen
)

add_executable(
	laplace
	src/main.cpp
)

target_link_libraries(
	laplace
	laplace_lib
)
