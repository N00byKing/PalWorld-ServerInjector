cmake_minimum_required(VERSION 3.4)

project(PalServerInject)

# Language Settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_executable(PalServerInject Launcher.cpp)
