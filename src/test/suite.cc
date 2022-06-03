// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CRISP_TEST_SUITE_CC
#define CRISP_TEST_SUITE_CC

#include "suite_result.cc"
#include "unit.cc"

#include <algorithm>
#include <set>
#include <string>

namespace crisp::test
{
    class suite final
    {
        std::vector<unit>     tests;
        std::string           name;
        std::set<std::string> dependencies;

        public:

        suite(std::string name) noexcept
            : name(std::move(name))
        {
        }

        void depends(std::string suite) noexcept
        {
            dependencies.emplace(std::move(suite));
        }

        void add(unit const& test) noexcept
        {
            tests.push_back(test);
        }

        [[nodiscard]] constexpr auto get_name() const noexcept -> auto&
        {
            return name;
        }

        [[nodiscard]] auto
        operator()(std::set<std::string> const& suites) const noexcept
        {
            suite_result result;
            result.suite   = name;
            auto const run = std::ranges::includes(suites, dependencies);
            for (auto const& test : tests) {
                result.results.push_back(test(run));
            }
            return result;
        }
    };
} // namespace crisp::test

#endif // CRISP_TEST_SUITE_CC
