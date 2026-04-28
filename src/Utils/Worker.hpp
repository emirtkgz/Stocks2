#pragma once

#include <chrono>
#include <future>

class Worker {
public:
    template<class F, class ...Args>
    Worker(std::chrono::duration<uint64_t> duration, F&& f, Args&&... args)
        : duration(duration), is_running(true)
    {
        // Launch an async task
        result = std::async([this, f = std::forward<F>(f), ...args = std::forward<Args>(args)]{
              auto next_tick = std::chrono::steady_clock::now() + this->duration;

              // Check if worker should run
              while(is_running) {
                  // Invoke the function
                  std::invoke(f, args...);

                  // Wait until the next tick
                  {
                      std::unique_lock<std::mutex> lock(mutex);
                      cv.wait_until(lock, next_tick);
                  }

                  next_tick += this->duration;
              }
          });
    }

    ~Worker() {
        // Terminate the main loop
        is_running = false;
        // Notify the thread so when app is closed we wouldn't wait for the duration to pass
        cv.notify_one();
        // Wait for the thread to close
        result.wait();
    }

private:
    std::chrono::duration<uint64_t> duration;
    std::condition_variable cv;
    std::future<void> result;
    std::mutex mutex;
    bool is_running;
};
