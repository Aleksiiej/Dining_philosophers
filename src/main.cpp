#include "Philosopher.cpp"

constexpr uint8_t N = 5;

std::vector<State> states{N, State::THINKING};

int main()
{
    std::vector<std::thread> threads;
    std::thread t;

    for (int i = 0; i < N; i++)
    {
        threads.push_back(std::thread(philosopher, i, std::ref(states)));
    }

    for (int i = 0; i < N; i++)
    {
        threads.at(i).join();
    }
}