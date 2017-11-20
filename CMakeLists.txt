cmake_minimum_required(VERSION 3.0)
project(examples)

file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/src)
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/tst)
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})

file(GLOB_RECURSE srcs ${PROJECT_SOURCE_DIR}/src/*.c*)
file(GLOB_RECURSE tsts ${PROJECT_SOURCE_DIR}/tst/*.c*)

configure_file(cmake/doctestDownload.cmake doctest/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR} .
   RESULT_VARIABLE err
   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doctest)
if(err)
   message(FATAL_ERROR "doctest prepare failed: ${err}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
   RESULT_VARIABLE err
   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doctest)
if(err)
   message(FATAL_ERROR "doctest clone failed: ${err}")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/doctest/src/doctest)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -Werror -O3")
set(CMAKE_C_FLAGS_DEBUG "-g3")
set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")

add_executable(${PROJECT_NAME} ${srcs} ${tsts})
add_test(${PROJECT_NAME} ${PROJECT_NAME})
enable_testing()
