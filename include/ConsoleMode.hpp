#pragma once

#include "Mode.hpp"

class ConsoleMode : public Mode {
    public:
        ConsoleMode() = default;
        ~ConsoleMode() = default;
        void run() override;
};
