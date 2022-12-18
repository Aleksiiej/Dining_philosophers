#pragma once
#include <cstdint>

class Plate
{
public:
    Plate() = default;
    Plate(const Plate &other) = delete;
    Plate(const Plate &&other) = delete;
    ~Plate() = default;

    uint8_t getNumberOfPortions();

private:
    uint8_t numberOfPortions_{10};
};
