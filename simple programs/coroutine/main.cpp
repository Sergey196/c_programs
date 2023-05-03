#include <iostream>
#include <coroutine>
#include <thread>
#include <unistd.h>
#include <queue>
#include <functional>

struct sleep_my {
    sleep_my(int n) : delay{ n } {}

    constexpr bool await_ready() const noexcept { return false; }

    void await_suspend(std::coroutine_handle<> h) const noexcept {
        std::thread([h, d = delay] { 
           usleep(d);
           h.resume();
        }).detach();
    }

    void await_resume() const noexcept {}

    int delay;
};


struct Task {
    struct promise_type {
        promise_type() = default;
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; } 
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
    };
};

Task foo1() noexcept {
    std::cout << "TEST foo1 start" << std::endl;
    for (int i = 0; i < 10; ++i) {
        co_await sleep_my { 100 };
        std::cout << "TEST foo1 end" << std::endl;
    }
}

Task foo2() noexcept {
    std::cout << "TEST foo2 start" << std::endl;
    for (int i = 0; i < 10; ++i) {
        co_await sleep_my { 100 };
        std::cout << "TEST foo2 end" << std::endl;
    }
}

//call foo
int main() {
    foo1();
    foo2();
    while(true) {}
}


