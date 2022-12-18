#pragma once

class Fork
{
public:
    Fork() = default;
    Fork(const Fork &other) = delete;
    Fork(const Fork &&other) = delete;
    ~Fork() = default;

    bool isOccupied_{false};
};