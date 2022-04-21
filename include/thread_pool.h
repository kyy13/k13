// k13
// Kyle J Burgess

#ifndef K13_THREAD_POOL_H
#define K13_THREAD_POOL_H

#include <condition_variable>
#include <functional>
#include <optional>
#include <atomic>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>
#include <mutex>
#include <queue>

namespace k13
{
    // Thread Task Status
    enum thread_task_status
    {
        // New unassigned task
        thread_task_none,

        // Task in progress
        thread_task_progress,

        // Task completed
        thread_task_complete,

        // Task function threw an exception during progress
        thread_task_error,
    };

    // Holds state information about an asynchronous task
    class thread_task
    {
    public:

        // Constructor
        thread_task();

        // Wait for task to complete
        // passes task exceptions to main thread
        void wait();

        // Reset the thread task
        // passes task exceptions to main thread
        void reset();

        // Check if task is complete
        // passes task exceptions to main thread
        bool is_complete();

    protected:

        friend class thread_pool;

        struct impl_task_sync
        {
            impl_task_sync()
                : status(thread_task_none)
            {}

            thread_task_status status;
            std::condition_variable cv;
            std::mutex mtx;
            std::exception_ptr exception;
        };

        std::shared_ptr<impl_task_sync> m_sync;
    };

    // Thread Pool
    class thread_pool
    {
    public:

        // Constructor
        // num_threads: number of threads in thread pool
        // sleep_duration: time for each thread to sleep when no tasks are available
        thread_pool(size_t num_threads, std::chrono::milliseconds sleep_duration);

        // Copy Constructor
        thread_pool(const thread_pool&) = delete;

        // Copy-Assignment Operator
        const thread_pool& operator=(const thread_pool&) = delete;

        // Destructor
        ~thread_pool();

        // Run a new task
        void run(thread_task& task, std::function<void()> func);

    protected:

        std::mutex m_queue_mtx;
        std::queue<std::function<void()>> m_queue;
        std::vector<std::unique_ptr<std::thread>> m_threads;
        std::atomic_bool m_running;
        std::chrono::milliseconds m_sleep_duration;

        // Per-thread loop
        void thread_loop();
    };

}

#endif
