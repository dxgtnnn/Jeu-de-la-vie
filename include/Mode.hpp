#pragma once

#include "Cell.hpp"

class Mode {
    public:
        virtual ~Mode() = default;
        virtual void run() = 0;
};