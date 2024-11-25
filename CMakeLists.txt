cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(GameOfLife)

find_package(nlohmann_json 3.11.3 REQUIRED)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/src/game.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/engine.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/config.cpp
)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/include/engine.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/state.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/config.hpp
)

configure_file(
   ${CMAKE_CURRENT_SOURCE_DIR}/assets/config.json
   ${CMAKE_CURRENT_BINARY_DIR}/config.json
   COPYONLY)

add_executable(GameOfLife ${SOURCE} ${HEADERS})
target_link_libraries(GameOfLife ${SDL2_LIBRARIES} nlohmann_json::nlohmann_json)
