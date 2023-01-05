#include "Philosopher.cpp"

std::vector<std::thread> threads;
std::atomic<bool> dinnerReady{true};

void dine(std::chrono::milliseconds time = 15s)
{
    std::this_thread::sleep_for(1s);

    for (int i = 0; i < NUM_OF_PHILOSOPHERS; i++)
    {
        threads.push_back(std::thread(philosopher, i, std::ref(dinnerReady)));
    }

    std::this_thread::sleep_for(time);

    dinnerReady = false;
    for (int i = 0; i < NUM_OF_PHILOSOPHERS; i++)
    {
        threads.at(i).join();
    }
}

int main()
{
    dine();
}
