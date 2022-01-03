// Kyle J Burgess

#ifndef K13_EVENT_H
#define K13_EVENT_H

#include <vector>
#include <functional>
#include <memory>

namespace k13
{
    // Persist Callback
    enum event_callback_persistence
    {
        event_delete_callback,
        event_persist_callback,
    };

    // Event
    template<class... Args>
    class event
    {
    public:

        // Function & Lambda binding
        using callback_cpp = std::function<event_callback_persistence(Args...)>;

        // Member function binding
        template<class T>
        using callback_c = event_callback_persistence(T::*)(Args...);

        // Member function binding (const)
        template<class T>
        using callback_c_const = event_callback_persistence(T::*)(Args...) const;

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
                    if (std::invoke(*it, args...) == event_persist_callback)
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
            subscribe(std::move(e), &event::forward_invoke);
        }

        // Forward this event's invoke once to another event
        void forward_once(std::shared_ptr<event_type> e)
        {
            subscribe(std::move(e), &event::forward_invoke_once);
        }

        // Subscribe to the event with a callback_cpp function
        void subscribe(callback_cpp func)
        {
            m_subscribers.push_back(std::move(func));
        }

        // Subscribe to the event with a member callback_cpp function (const)
        template<class T>
        void subscribe(std::shared_ptr<T> object, callback_c_const<T> mem_func)
        {
            m_subscribers.push_back([object = std::weak_ptr<T>(std::move(object)), mem_func](Args... args) -> event_callback_persistence
            {
                if (object.expired())
                {
                    return event_delete_callback;
                }

                return std::invoke(mem_func, object.lock().get(), args...);
            });
        }

        // Subscribe to the event with a member callback_cpp function
        template<class T>
        void subscribe(std::shared_ptr<T> object, callback_c<T> mem_func)
        {
            m_subscribers.push_back([object = std::weak_ptr<T>(std::move(object)), mem_func](Args... args) -> event_callback_persistence
            {
                if (object.expired())
                {
                    return event_delete_callback;
                }

                return std::invoke(mem_func, object.lock().get(), args...);
            });
        }

    protected:

        // Subscribing functions
        std::vector<callback_cpp> m_subscribers;

        // Forward invoke a forwarded event
        event_callback_persistence forward_invoke(Args... args)
        {
            invoke(args...);
            return event_persist_callback;
        }

        // Forward invoke a forwarded event once
        event_callback_persistence forward_invoke_once(Args... args)
        {
            invoke(args...);
            return event_delete_callback;
        }

    };
}

#endif
