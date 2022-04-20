// k13
// Kyle J Burgess

#ifndef K13_EVENT_H
#define K13_EVENT_H

#include <vector>
#include <functional>
#include <memory>

namespace k13
{
    enum callback_persistence
    {
        persist_callback,
        remove_callback,
    };

    // Event
    template<class... Args>
    class event
    {
    public:

        // Function & Lambda binding
        using func = std::function<callback_persistence(Args...)>;

        // Member function binding
        template<class T>
        using pfunc = callback_persistence(T::*)(Args...);

        // Member function binding (const)
        template<class T>
        using cpfunc = callback_persistence(T::*)(Args...) const;

        // Type of event
        using event_type = event<Args...>;

        // Constructor
        event() = default;

        // Copy Constructor
        event(const event&) = delete;

        // Copy-Assignment Operator
        event& operator=(const event&) = delete;

        // Destructor
        ~event() = default;

        // Invokes the event with args
        // calling all subscriber callbacks
        void invoke(Args... args)
        {
            if (!m_subscribers.empty())
            {
                for (auto it = m_subscribers.begin(); it != m_subscribers.end();)
                {
                    if (std::invoke(*it, args...) == persist_callback)
                    {
                        ++it;
                    }
                    else
                    {
                        it = m_subscribers.erase(it);
                    }
                }
            }
        }

        // Forward this event's invoke to another event
        void forward(std::shared_ptr<event_type> e)
        {
            add_callback(std::move(e), &event::forward_invoke);
        }

        // Forward this event's invoke once to another event
        void forward_once(std::shared_ptr<event_type> e)
        {
            add_callback(std::move(e), &event::forward_invoke_once);
        }

        // Subscribe to the event with a std::function
        void add_callback(func func)
        {
            m_subscribers.push_back(std::move(func));
        }

        // Subscribe to the event with an object and a c-style function pointer (const)
        template<class T>
        void add_callback(std::shared_ptr<T> object, cpfunc<T> mem_func)
        {
            m_subscribers.push_back([object = std::weak_ptr<T>(std::move(object)), mem_func](Args... args) -> callback_persistence
            {
                if (object.expired())
                {
                    return remove_callback;
                }

                return std::invoke(mem_func, object.lock().get(), args...);
            });
        }

        // Subscribe to the event with a c-style function pointer
        template<class T>
        void add_callback(std::shared_ptr<T> object, pfunc<T> mem_func)
        {
            m_subscribers.push_back([object = std::weak_ptr<T>(std::move(object)), mem_func](Args... args) -> callback_persistence
            {
                if (object.expired())
                {
                    return remove_callback;
                }

                return std::invoke(mem_func, object.lock().get(), args...);
            });
        }

    protected:

        // Subscribing functions
        std::vector<func> m_subscribers;

        // Forward invoke a forwarded event
        callback_persistence forward_invoke(Args... args)
        {
            invoke(args...);
            return persist_callback;
        }

        // Forward invoke a forwarded event once
        callback_persistence forward_invoke_once(Args... args)
        {
            invoke(args...);
            return remove_callback;
        }

    };
}

#endif
