#pragma once

#include <PCH.h>


namespace QPP {
    class StateArray {
    public:
        StateArray();

    private:
        std::vector<std::vector<char>> matrix;
    };
}