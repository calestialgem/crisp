// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CRISP_UTIL_VERSION_HH
#define CRISP_UTIL_VERSION_HH

#include <fmt/format.h>
#include <ostream>

namespace dugum
{
    struct version final {
        unsigned short major;
        unsigned short minor;
        unsigned short patch;
    };

    auto constexpr VERSION = version{16, 1, 0};
} // namespace dugum

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

#endif // CRISP_UTIL_VERSION_HH
