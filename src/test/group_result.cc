// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CRISP_TEST_GROUP_RESULT_CC
#define CRISP_TEST_GROUP_RESULT_CC

#include "suite_result.cc"

#include <fmt/format.h>
#include <string>
#include <unordered_map>

namespace crisp::test
{
    struct group_result final {
        std::unordered_map<std::string, suite_result> results;
    };
} // namespace crisp::test

template<>
struct fmt::formatter<crisp::test::group_result> {
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
    auto format(crisp::test::group_result const& results, FormatContext& ctx)
        const noexcept
    {
        auto out = ctx.out();
        for (auto const& [suite, result] : results.results) {
            out = format_to(out, "{}\n", result);
        }
        return out;
    }
};

#endif // CRISP_TEST_GROUP_RESULT_CC
