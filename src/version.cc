// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CRISP_VERSION_CC
#define CRISP_VERSION_CC

#include <fmt/format.h>
#include <ostream>

namespace crisp
{
    struct version final {
        unsigned short major;
        unsigned short minor;
        unsigned short patch;
    };

    auto constexpr VERSION = version{0, 1, 0};
} // namespace crisp

template<>
struct fmt::formatter<crisp::version> {
    static constexpr auto parse(format_parse_context& ctx)
    {
        auto const* begin = ctx.begin();
        auto const* end   = ctx.end();

        if (begin != end && *begin != '}') {
            throw format_error("invalid format");
        }

        return begin;
    }

    template<typename FormatContext>
    auto format(crisp::version const& version, FormatContext& ctx)
    {
        return format_to(
            ctx.out(),
            "{}.{}.{}",
            version.major,
            version.minor,
            version.patch);
    }
};

#endif // CRISP_VERSION_CC
