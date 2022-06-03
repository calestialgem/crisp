// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CRISP_TEST_UNIT_CC
#define CRISP_TEST_UNIT_CC

#include "src_pos.cc"
#include "unit_result.cc"

#include <functional>

namespace crisp::test
{
    struct unit final {
        src_pos               position;
        std::function<bool()> body;

        [[nodiscard]] auto operator()(bool run) const noexcept
        {
            return unit_result{
                position,
                run ? as_outcome(body()) : outcome::NOT_RUN};
        }
    };
} // namespace crisp::test

#endif // CRISP_TEST_UNIT_CC
