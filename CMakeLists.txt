# SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(crisp)

# Library
add_library(${PROJECT_NAME} STATIC src/lib.cc)

# Includes
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt-header-only)

# Warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /Wall)
else(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif(MSVC)

# {fmt}
add_subdirectory(fmt EXCLUDE_FROM_ALL)
