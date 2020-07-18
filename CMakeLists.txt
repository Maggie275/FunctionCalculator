 
cmake_minimum_required(VERSION 3.8)  
project(Evaluator)
set(CMAKE_CXX_STANDARD 14)           

file(GLOB SOURCES "src/*.cpp")

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(evaluator ${SOURCES})