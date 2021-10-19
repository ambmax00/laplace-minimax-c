cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(laplace)
enable_language(CXX)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

add_compile_options(-Wall -Wextra -pedantic)

find_package(Eigen3 REQUIRED NO_MODULE)
find_package(QUADMATH)

set(LAPLACE_INSTALL ${CMAKE_INSTALL_PREFIX})
set(LAPLACE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/minimax_read.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/minimax_read.cpp @ONLY
)

add_executable(
	laplace
	main.cpp
	minimax.cpp
	minimax_maehly.cpp
	minimax_paraopt.cpp
	${CMAKE_CURRENT_BINARY_DIR}/minimax_read.cpp
)

target_link_libraries(
	laplace
	quadmath
	Eigen3::Eigen
)
