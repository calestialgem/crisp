// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CRISP_TEST_SUITE_HH
#define CRISP_TEST_SUITE_HH

#include "result.hh"
#include "src_pos.hh"

#include <algorithm>
#include <functional>
#include <set>

namespace crisp::test
{
    struct test final {
        src_pos               position;
        std::function<bool()> body;

        [[nodiscard]] auto operator()(bool run) const noexcept
        {
            return result{
                position,
                run ? as_outcome(body()) : outcome::NOT_RUN};
        }
    };

    class suite final
    {
        std::vector<test>     tests;
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

        void add(test const& test) noexcept
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

#endif // CRISP_TEST_SUITE_HH
