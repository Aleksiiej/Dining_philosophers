#include "Philosopher.cpp"

int main()
{
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_OF_PHILOSOPHERS; i++)
    {
        threads.push_back(std::thread(philosopher, i));
    }

    for (int i = 0; i < NUM_OF_PHILOSOPHERS; i++)
    {
        threads.at(i).join();
    }
}