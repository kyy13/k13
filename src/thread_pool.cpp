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
}
