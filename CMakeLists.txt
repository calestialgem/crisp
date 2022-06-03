# SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(crisp)

# Library
add_library(${PROJECT_NAME} STATIC
    inc/crisp.hh

    inc/crisp/test.hh
    src/test/group_result.cc
    src/test/group.cc
    src/test/outcome.cc
    src/test/suite_result.cc
    src/test/suite.cc
    src/test/unit_result.cc
    src/test/unit.cc

    inc/crisp/src_pos.hh
    src/src_pos.cc

    inc/crisp/version.hh
    src/version.cc
)

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
