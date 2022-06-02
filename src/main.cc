// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include <cstddef>
#include <iostream>
#include <string_view>
#include <vector>

using args = char const* const*;

[[nodiscard]] auto get_arguments(int const argc, args const argv)
{
    std::vector<std::string_view> result;
    result.reserve(argc);
    for (int i = 0; i < argc; i++) {
        result.emplace_back(argv[i]);
    }
    return result;
}

void print_arguments(std::vector<std::string_view> const& arguments)
{
    std::cout << "Running with arguments:";
    for (std::size_t index{0}; auto const& argument : arguments) {
        std::cout << "\n[" << index++ << "]: " << argument;
    }
    std::cout << std::endl;
}

auto main(int const argc, args const argv) -> int
{
    auto const arguments = get_arguments(argc, argv);
    print_arguments(arguments);

    return EXIT_SUCCESS;
}
