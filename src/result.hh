// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CRISP_TEST_RESULT_HH
#define CRISP_TEST_RESULT_HH

#include "src_pos.hh"

#include <cstddef>
#include <fmt/format.h>
#include <ostream>
#include <string_view>
#include <unordered_map>
#include <vector>

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

    struct result final {
        src_pos position;
        outcome success{outcome::NOT_RUN};
    };

    struct suite_result final {
        std::string         suite;
        std::vector<result> results;
    };

    struct group_result final {
        std::unordered_map<std::string, suite_result> results;
    };
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

template<>
struct fmt::formatter<crisp::test::result> {
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
    constexpr auto
    format(crisp::test::result const& result, FormatContext& ctx) const noexcept
    {
        return format_to(
            ctx.out(),
            "{0:}: {1:s}: {1:}",
            result.position,
            result.success);
    }
};

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

#endif // CRISP_TEST_RESULT_HH
