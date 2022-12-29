#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

enum class State
{
    THINKING,
    EATING
};

std::mutex mt;

bool checkIfForksAreFree(const int i, std::vector<State> &states)
{
    std::lock_guard lg{mt};
    if (states.size() == 2 and i == 0)
    {
        return (states.at(1) == State::THINKING);
    }
    else if (states.size() == 2 and i == 1)
    {
        return (states.at(0) == State::THINKING);
    }
    else if (i == 0)
    {
        return (states.at(1) == State::THINKING and states.at(states.size() - 1) == State::THINKING) ? true : false;
    }
    else if (static_cast<unsigned int>(i) == states.size() - 1)
    {
        return (states.at(i - 1) == State::THINKING and states.at(0) == State::THINKING) ? true : false;
    }
    else
        return (states.at(i - 1) == State::THINKING and states.at(i + 1) == State::THINKING) ? true : false;
}

void think(const int i, std::vector<State> &states)
{
    {
        std::lock_guard lg{mt};
        std::cout << "Philosopher nr: " << i << " thinking..." << std::endl;
    }
    while (!checkIfForksAreFree(i, states))
    {
    }
}

void takeFork(const int i, std::vector<State> &states)
{
    std::lock_guard<std::mutex> lg{mt};
    std::cout << "Philosopher nr: " << i << " taking fork..." << std::endl;
    states.at(i) = State::EATING;
}

void eat(const int i)
{
    {
        std::lock_guard lg{mt};
        std::cout << "Philosopher nr: " << i << " eating..." << std::endl;
    }
    std::this_thread::sleep_for(1s);
}

void putFork(const int i, std::vector<State> &states)
{
    std::lock_guard<std::mutex> lg{mt};
    std::cout << "Philosopher nr: " << i << " putting fork down..." << std::endl;
    states.at(i) = State::THINKING;
}

auto philosopher = [remainingPortion = 5](const auto i, auto states) mutable
{
    while (remainingPortion != 0)
    {
        think(i, states);
        takeFork(i, states);
        eat(i);
        remainingPortion--;
        putFork(i, states);
    }
    {
        std::lock_guard lg{mt};
        std::cout << "Philosopher nr: " << i << " finished dinner" << std::endl;
    }
};