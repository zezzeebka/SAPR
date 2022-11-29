cmake_minimum_required(VERSION 3.14)

project(SAPR LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SFML_DIR SFML-2.5.1/lib/cmake/SFML)

find_package(SFML COMPONENTS graphics audio window system network REQUIRED)

include_directories(SFML-2.5.1/include)

file(GLOB_RECURSE PROJECT_SOURCE src/*.cpp src/*.h data/*.txt data/*.json)

add_executable(SAPR ${PROJECT_SOURCE})

target_link_libraries(SAPR sfml-graphics sfml-system sfml-window sfml-audio sfml-network)

add_custom_command(TARGET SAPR PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/SFML-2.5.1/bin $<TARGET_FILE_DIR:SAPR>)

add_custom_command(TARGET SAPR PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:SAPR>/data)

