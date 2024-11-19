# CMake version mínima requerida
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(project)

# Incluye el directorio de cabeceras (headers)
include_directories(include)
include_directories(./lib/prom/include)
include_directories(./lib/promhttp/include)

# Define el ejecutable principal con los archivos .c
add_executable(main_executable src/expose_metrics.c src/metrics.c src/main.c)

add_subdirectory(./lib/prom)
add_subdirectory(./lib/promhttp)

link_directories(${CMAKE_SOURCE_DIR}/lib/prom/build)
link_directories(${CMAKE_SOURCE_DIR}/lib/promhttp/build)

target_link_libraries(main_executable prom promhttp)

