cmake_minimum_required(VERSION 3.10)

project(CORA VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar pacote ncurses
find_package(Curses REQUIRED)

# Arquivos fonte
set(SOURCES
    src/main.cpp
    src/ui/MainMenu.cpp
)

# Adicionar executável
add_executable(cora ${SOURCES})

# Incluir diretórios de cabeçalho
target_include_directories(cora PRIVATE include)

# Linkar com ncurses
target_link_libraries(cora PRIVATE ${CURSES_LIBRARIES})
