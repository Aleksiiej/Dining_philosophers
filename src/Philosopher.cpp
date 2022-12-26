#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

enum class State
{
    THINKING,
    EATING
};

using namespace std::chrono_literals;

void think(const int i, std::mutex& mt)
{
    mt.lock();
    std::cout << "Philosopher nr: " << i << " thinking..." << std::endl;
    mt.unlock();
    std::this_thread::sleep_for(1s);
}

void takeFork(const int i, std::vector<State>& states, std::mutex& mt)
{
    std::lock_guard<std::mutex> lg{mt};
    std::cout << "Philosopher nr: " << i << " taking fork..." << std::endl;
    states.at(i) = State::EATING;
}

void eat(const int i, std::mutex& mt)
{
    mt.lock();
    std::cout << "Philosopher nr: " << i << " eating..." << std::endl;
    mt.unlock();
    std::this_thread::sleep_for(1s);
    
}

void putFork(const int i, std::vector<State>& states, std::mutex& mt)
{
    std::lock_guard<std::mutex> lg{mt};
    std::cout << "Philosopher nr: " << i << " puting fork down..." << std::endl;
    states.at(i) = State::THINKING;
}

bool checkIfForksAreFree(const int i, std::vector<State>& states)
{
    if(states.size() == 2 and i == 0)
    {
        return (states.at(1) == State::THINKING);
    }
    else if(states.size() == 2 and i == 1)
    {
        return (states.at(0) == State::THINKING);
    }
    else if(i == 0)
    {
        return (states.at(1) == State::THINKING and states.at(states.size() - 1) == State::THINKING) ? true : false;
    }
    else if(static_cast<unsigned int>(i) == states.size() - 1)
    {
        return (states.at(i - 1) == State::THINKING and states.at(0) == State::THINKING) ? true : false;
    }
    else return (states.at(i - 1) == State::THINKING and states.at(i + 1) == State::THINKING) ? true : false;
}

auto philosopher = [remainingPortion = 5] (const auto i, auto states, auto mt) mutable
{
    while (remainingPortion != 0)
    {
        think(i, mt);
        takeFork(i, states, mt);
        eat(i, mt);
        remainingPortion--;
        putFork(i, states, mt);
    }
    std::cout << "Philosopher nr: " << i << " finished dinner" << std::endl;
};