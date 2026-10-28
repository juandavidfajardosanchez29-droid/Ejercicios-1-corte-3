cmake_minimum_required(VERSION 3.10)
project(InformeCorte3 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Un ejecutable por ejercicio; todos se compilan con un solo "cmake --build ."
add_executable(ej1_subasta  ej1_subasta/main.cpp)
add_executable(ej2_atm      ej2_atm/main.cpp)
add_executable(ej3_metro    ej3_metro/main.cpp)
add_executable(ej4_reloj    ej4_reloj/main.cpp)
add_executable(ej5_reunion  ej5_reunion/main.cpp)
