// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CRISP_TEST_OUTCOME_HH
#define CRISP_TEST_OUTCOME_HH

#include <fmt/format.h>
#include <string_view>

namespace crisp::test
{
    enum class outcome {
        NOT_RUN = -1,
        FAIL    = 0,
        PASS    = 1
    };

    [[nodiscard]] constexpr auto name(outcome const& outcome) noexcept
        -> std::string_view
    {
        switch (outcome) {
            case outcome::NOT_RUN:
                return "NOT RUN";
            case outcome::FAIL:
                return "FAIL";
            case outcome::PASS:
                return "PASS";
        }
        return "INVALID";
    }

    [[nodiscard]] constexpr auto severity(outcome const& outcome) noexcept
        -> std::string_view
    {
        switch (outcome) {
            case outcome::NOT_RUN:
                return "warning";
            case outcome::FAIL:
                return "error";
            case outcome::PASS:
                return "info";
        }
        return "debug";
    }

    [[nodiscard]] constexpr auto as_outcome(bool as_bool) noexcept
    {
        return as_bool ? outcome::PASS : outcome::FAIL;
    }

    [[nodiscard]] constexpr auto as_bool(outcome as_outcome) noexcept
    {
        return as_outcome != outcome::PASS;
    }
} // namespace crisp::test

template<>
struct fmt::formatter<crisp::test::outcome> {
    static constexpr auto NAME     = 'n';
    static constexpr auto SEVERITY = 's';

    char presentation = NAME;

    constexpr auto parse(format_parse_context const& ctx)
    {
        auto const* begin = ctx.begin();
        auto const* end   = ctx.end();

        if (begin != end && (*begin == NAME || *begin == SEVERITY)) {
            presentation = *begin++;
        }

        if (begin != end && *begin != '}') {
            throw format_error("invalid format");
        }

        return begin;
    }

    template<typename FormatContext>
    constexpr auto format(
        crisp::test::outcome const& outcome,
        FormatContext&              ctx) const noexcept
    {
        return format_to(
            ctx.out(),
            "{}",
            (presentation == NAME ? crisp::test::name
                                  : crisp::test::severity)(outcome));
    }
};

#endif // CRISP_TEST_OUTCOME_HH
