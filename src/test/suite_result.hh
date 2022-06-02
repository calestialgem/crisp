// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CRISP_TEST_SUITE_RESULT_HH
#define CRISP_TEST_SUITE_RESULT_HH

#include "unit_result.hh"

#include <cstddef>
#include <fmt/format.h>
#include <string>
#include <vector>

namespace crisp::test
{
    struct suite_result final {
        std::string              suite;
        std::vector<unit_result> results;
    };
} // namespace crisp::test

template<>
struct fmt::formatter<crisp::test::suite_result> {
    static constexpr auto parse(format_parse_context const& ctx)
    {
        auto const* begin = ctx.begin();
        auto const* end   = ctx.end();

        if (begin != end && *begin != '}') {
            throw format_error("invalid format");
        }

        return begin;
    }

    template<typename FormatContext>
    constexpr auto format(
        crisp::test::suite_result const& results,
        FormatContext&                   ctx) const noexcept
    {
        auto out = format_to(ctx.out(), "\n{}\n", results.suite);
        for (std::size_t count{0}; auto const& result : results.results) {
            out = format_to(out, "[{}] {}\n", count++, result);
        }
        return out;
    }
};

#endif // CRISP_TEST_SUITE_RESULT_HH
