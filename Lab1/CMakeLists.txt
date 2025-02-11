project(Lab1 C CXX)
cmake_minimum_required(VERSION 3.3.2)

include(cmake/App.cmake)

set(BOOST_ROOT ${CMAKE_HOME_DIRECTORY}/src/boost/filesystem)
set(BOOST_INCLUDEDIR ${CMAKE_HOME_DIRECTORY}/src/boost/filesystem)

find_package(Boost 1.82 REQUIRED COMPONENTS system filesystem)

set(SOURCES 
"src/MyApp.h"
"src/MyApp.cpp"
"src/main.cpp"
"src/Juce.cpp"
"src/Juce.h"
"src/data_structures/data_structures.h"
"src/data_structures/data_structures.cpp"
"src/data_structures/pch.h"
"src/data_structures/pch.cpp"
)

message("Creating DataStructures Library...")

add_library(DataStructures SHARED 
${CMAKE_HOME_DIRECTORY}/src/data_structures/data_structures.cpp 
${CMAKE_HOME_DIRECTORY}/src/data_structures/data_structures.h
${CMAKE_HOME_DIRECTORY}/src/data_structures/pch.h
${CMAKE_HOME_DIRECTORY}/src/data_structures/pch.cpp)

message("Data Structures Library created.")
message("Linking DataStructures Library to the = ${TARGET}")

target_link_libraries(${TARGET} DataStructures)
message("Linking DataStructures Library finished.")

add_app("${SOURCES}")