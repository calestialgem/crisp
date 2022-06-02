// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CRISP_UTIL_SRC_POS_HH
#define CRISP_UTIL_SRC_POS_HH

#include <cstddef>
#include <fmt/format.h>
#include <ostream>
#include <string>
#include <string_view>

namespace crisp
{
    struct src_pos final {
        std::string file;
        std::size_t line;
    };

#define CRISP_UTIL_SRC_POS \
    crisp::src_pos         \
    {                      \
        __FILE__, __LINE__ \
    }
} // namespace crisp

template<>
struct fmt::formatter<crisp::src_pos> : fmt::formatter<std::string_view> {
    template<typename FormatContext>
    auto format(crisp::src_pos const& src_pos, FormatContext& ctx)
    {
        auto out = fmt::formatter<std::string_view>::format(src_pos.file, ctx);
        return format_to(out, ":{}", src_pos.line);
    }
};

#endif // CRISP_UTIL_SRC_POS_HH
