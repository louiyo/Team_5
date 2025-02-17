cmake_minimum_required(VERSION 2.6)
project(Team_5)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif(NOT CMAKE_BUILD_TYPE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
option(test "Build tests." ON)

include_directories("/usr/local/include" ${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib "/usr/local/lib64")

find_package(Doxygen)
if (DOXYGEN_FOUND)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)

add_executable(Team_5 src/main.cpp src/Builder.cpp src/BedBuilder.cpp src/Sequence.cpp src/MatrixBuilder.cpp)

if (test)
  enable_testing()
  find_package(GTest)
  if (NOT GTEST_FOUND)
    SET(GTEST_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)
    SET(GTEST_BOTH_LIBRARIES libgtest.a libgtest_main.a)
  endif(NOT GTEST_FOUND)
  
  
include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)

add_executable(tests src/Genome_analyser.cpp src/Sequence.cpp src/test_main.cpp)
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} pthread)
add_test(Team_5 tests)

endif(test)

