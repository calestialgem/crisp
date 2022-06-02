// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CRISP_TEST_GROUP_HH
#define CRISP_TEST_GROUP_HH

#include "result.hh"
#include "suite.hh"

#include <set>
#include <unordered_map>

namespace crisp::test
{
    class group final
    {
        std::unordered_map<std::string, suite> suites;
        std::set<std::string>                  enabled;

        public:

        void add(suite&& suite) noexcept
        {
            suites.insert({suite.get_name(), std::move(suite)});
        }

        void enable(std::string name) noexcept
        {
            enabled.emplace(std::move(name));
        }

        void disable(std::string const& name) noexcept
        {
            enabled.erase(name);
        }

        void enable_all() noexcept
        {
            for (auto const& suite : suites) {
                enabled.emplace(suite.second.get_name());
            }
        }

        void disable_all() noexcept
        {
            enabled.clear();
        }

        [[nodiscard]] auto operator()() const noexcept
        {
            group_result result;
            for (auto const& name : enabled) {
                result.results[name] = suites.at(name)(enabled);
            }
            return result;
        }
    };
} // namespace crisp::test

#endif // CRISP_TEST_GROUP_HH
