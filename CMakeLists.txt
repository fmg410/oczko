cmake_minimum_required(VERSION 3.16.3)
project(oczko)

set(CMAKE_CXX_STANDARD 20)

add_executable(oczko Source.cpp Gracz.cpp Karta.cpp Bot.cpp Kasyno.cpp)
