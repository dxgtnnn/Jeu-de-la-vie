#pragma once

#include "Mode.hpp"

class GUI : public Mode {
    public:
        GUI() = default;
        ~GUI() = default;
        void run() override;
};
