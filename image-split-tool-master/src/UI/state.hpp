#pragma once

namespace UI
{
    enum Windows
    {
        NONE = 0,
        CROP = 1,
        CONCAT = 2
    };

    struct AppState
    {
        Windows active = NONE;
    };
} // namespace UI
