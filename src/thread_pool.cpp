// k13
// Kyle J Burgess

#include "thread_pool.h"

namespace k13
{
    thread_task::thread_task()
        : m_sync(std::make_shared<impl_task_sync>())
    {}

    void thread_task::wait()
    {
        // Wait on task to complete without busy-waiting main thread
        // or sleeping for set time
        std::unique_lock<std::mutex> lk(m_sync->mtx);

        const auto& status = m_sync->status;
        m_sync->cv.wait(lk, [&]()
        {
            return status != thread_task_progress;
        });

        // Throw exceptions if caught on worker thread
        if (status == thread_task_error)
        {
            std::rethrow_exception(m_sync->exception);
        }
    }

    void thread_task::reset()
    {
        wait();

        std::lock_guard<std::mutex> lg(m_sync->mtx);

        m_sync->status = thread_task_none;
    }

    bool thread_task::is_complete()
    {
        std::lock_guard<std::mutex> lg(m_sync->mtx);

        // Throw exceptions if caught on worker thread
        auto& status = m_sync->status;
        if (status == thread_task_error)
        {
            status = thread_task_none;
            std::rethrow_exception(m_sync->exception);
        }

        return status != thread_task_progress;
    }

    thread_pool::thread_pool(size_t num_threads, std::chrono::milliseconds sleep_duration)
        : m_running(true)
        , m_sleep_duration(sleep_duration)
    {
        // Launch and store thread handles
        m_threads.reserve(num_threads);
        for (size_t i = 0; i != num_threads; ++i)
        {
            m_threads.push_back(std::make_unique<std::thread>(&thread_pool::thread_loop, this));
        }
    }

    thread_pool::~thread_pool()
    {
        // Stop threads
        m_running = false;
        for (auto& pthread : m_threads)
        {
            pthread->join();
        }
    }

    void thread_pool::run(thread_task& task, std::function<void()> func)
    {
        // Create a pointer to task synchronization variables
        auto& sync = task.m_sync;

        if (!m_threads.empty())
        {
            std::lock_guard<std::mutex> lock(m_queue_mtx);

            // Add task to queue
            m_queue.push([sync = sync, func = std::move(func)]
            {
                // Call the embedded function
                try
                {
                    func();
                }
                catch(...)
                {
                    sync->exception = std::current_exception();
                }

                // Tell main thread that the task has been processed
                sync->mtx.lock();
                sync->status = thread_task_complete;

                // Manual unlocking is done before notifying, to avoid waking up
                // the waiting thread only to block again (see notify_one for details)
                sync->mtx.unlock();
                sync->cv.notify_one();
            });
        }
        else
        {
            // No threads in thread pool, call function immediately,
            // and return completed thread_task
            func();
            sync->status = thread_task_complete;
        }
    }

    void thread_pool::thread_loop()
    {
        while (m_running)
        {
            std::function<void()> func;

            // Get next task
            m_queue_mtx.lock();
            if (!m_queue.empty())
            {
                func = std::move(m_queue.front());
                m_queue.pop();
            }
            m_queue_mtx.unlock();

            // Run function, or sleep if there is no task
            if (func)
            {
                func();
            }
            else
            {
                std::this_thread::sleep_for(m_sleep_duration);
            }
        }
    }
}
