# SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(sablon)

function(calestialgem_set_warnings_includes target)
    # Includes
    target_include_directories(${target} PRIVATE ${PROJECT_SOURCE_DIR}/src)
    # Warnings
    if(MSVC)
        target_compile_options(${target} PRIVATE /Wall)
    else(MSVC)
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif(MSVC)
endfunction(calestialgem_set_warnings_includes target)

# Executable
add_executable(${PROJECT_NAME} src/main.cc)
calestialgem_set_warnings_includes(${PROJECT_NAME})
