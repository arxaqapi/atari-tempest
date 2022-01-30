	
cmake_minimum_required(VERSION 3.13.0)
project(tempest-atari VERSION 0.1.0)


find_package(SDL2 REQUIRED)

include_directories(include)
 
#set(SOURCES src/mainapp.cpp src/Student.cpp)
file(GLOB SOURCES "src/*.cpp")
 
add_executable(tempest ${SOURCES})

set_property(TARGET tempest PROPERTY CXX_STANDARD 20)
target_link_libraries(tempest ${SDL2_LIBRARIES})

target_compile_options(tempest PRIVATE -Wall -Wpedantic -g)