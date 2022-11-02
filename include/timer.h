//
// Created by XDD on 2022/11/2.
//

#ifndef TCP_CLIENT_TIMER_H
#define TCP_CLIENT_TIMER_H

#include <iostream>
#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>
#include <atomic>

using namespace std;

class Timer {

public:

    void start(int interval, std::function<void()> task) {

        std::thread([this, interval, task]() {

            while (true) {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                task();
            }

        }).detach();
    }


private:
    condition_variable cv;
};

#endif //TCP_CLIENT_TIMER_H
