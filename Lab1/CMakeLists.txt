project(Lab1 C CXX)
cmake_minimum_required(VERSION 3.3.2)

include(cmake/App.cmake)

set(SOURCES 
"src/MyApp.h"
"src/MyApp.cpp"
"src/main.cpp"
"src/Juce.cpp"
"src/Juce.h"
"src/JSHelper.h"
"src/JSHelper.cpp"
)

add_app("${SOURCES}")

message("Creating DataStructures Library...")

add_library(DataStructures SHARED 
${CMAKE_HOME_DIRECTORY}/src/data_structures/data_structures.cpp 
${CMAKE_HOME_DIRECTORY}/src/data_structures/data_structures.h
${CMAKE_HOME_DIRECTORY}/src/data_structures/pch.h
${CMAKE_HOME_DIRECTORY}/src/data_structures/pch.cpp)

message("Data Structures Library created.")
message("Linking DataStructures Library to the TARGET")

target_link_libraries(Lab1 DataStructures)
message("Linking DataStructures Library finished.")

message("Searching for required Boost packages...")
message("Scanning your environment for boostRoot environment variable...")
if($ENV{boostRoot} STREQUAL "")
  message(FATAL_ERROR "Your boostRoot environmental variable is not set. Create it and set it to the path to your boost folder.")
  else()
  message("boostRoot has value: $ENV{boostRoot}")
  # Set boost path
  # e:/С++ Networking/AddDataForNetPrograming/boost_1_87_0
  set(BOOST_ROOT "$ENV{boostRoot}")
  set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")
  set(Boost_USE_STATIC_LIBS OFF)
  set(Boost_USE_MULTITHREADED ON)

  # Searching for required components
  find_package(Boost 1.87.0 REQUIRED COMPONENTS system filesystem json)
  if(Boost_FOUND)
      message("Boost was found.")
      message("Boost include directories were found: ${Boost_INCLUDE_DIRS}")
      include_directories(${Boost_INCLUDE_DIRS})   
      message("Linking to the: ${Boost_LIBRARIES}") 
      target_link_libraries(Lab1 general ${Boost_LIBRARIES})
  else(Boost_FOUND)
      message(FATAL_ERROR "Boost was not found!")
  endif(Boost_FOUND)
endif()


