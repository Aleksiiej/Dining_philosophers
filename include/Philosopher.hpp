#pragma once

class Philosopher
{
public:
    Philosopher() = default;
    Philosopher(const Philosopher &other) = delete;
    Philosopher(const Philosopher &&other) = delete;
    ~Philosopher() = default;

    void eat();
    void think();
};