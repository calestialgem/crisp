// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CRISP_TEST_UNIT_RESULT_HH
#define CRISP_TEST_UNIT_RESULT_HH

#include "outcome.hh"
#include "src_pos.hh"

#include <fmt/format.h>

namespace crisp::test
{
    struct unit_result final {
        src_pos position;
        outcome success{outcome::NOT_RUN};
    };
} // namespace crisp::test

template<>
struct fmt::formatter<crisp::test::unit_result> {
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
        crisp::test::unit_result const& result,
        FormatContext&                  ctx) const noexcept
    {
        return format_to(
            ctx.out(),
            "{0:}: {1:s}: {1:}",
            result.position,
            result.success);
    }
};

#endif // CRISP_TEST_UNIT_RESULT_HH
