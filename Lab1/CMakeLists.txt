project(Lab1 C CXX)
cmake_minimum_required(VERSION 3.3.2)

include(cmake/App.cmake)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
set(Boost_NO_SYSTEM_PATHS TRUE) 

if (Boost_NO_SYSTEM_PATHS)
  set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../3p/boost")
  set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
  set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
endif (Boost_NO_SYSTEM_PATHS)

find_package(Boost 1.87 COMPONENTS filesystem)

if(BOOST_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})    
    target_link_libraries(${TARGET} ${Boost_LIBRARIES})
endif(BOOST_FOUND)

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