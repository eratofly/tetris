cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(tetris)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

add_executable(tetris main.cpp)

target_include_directories(tetris PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(tetris PUBLIC cxx_std_17)
target_compile_definitions(tetris PRIVATE SFML_STATIC)

target_link_libraries(tetris ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})