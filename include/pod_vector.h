// Kyle J Burgess

#ifndef K13_POD_VECTOR_H
#define K13_POD_VECTOR_H

#include "basic_iterator.h"
#include "basic_reverse_iterator.h"

#include <cstring>
#include <cstdint>
#include <cassert>
#include <type_traits>

namespace k13
{
    template<class T>
    class pod_vector
    {
    public:

        using iterator = basic_iterator<T>;
        using const_iterator = basic_iterator<const T>;
        using reverse_iterator = basic_reverse_iterator<T>;
        using const_reverse_iterator = basic_reverse_iterator<const T>;

        // Constructor
        pod_vector() : m_data(nullptr), m_size(0), m_capacity(0)
        {
            static_assert(std::is_pod<T>::value, "pod_vector template type T must be a POD type");
        }

        // Constructor
        explicit pod_vector(size_t size) : m_data(nullptr), m_size(size), m_capacity(size)
        {
            static_assert(std::is_pod<T>::value, "pod_vector template type T must be a POD type");
            
            if (size > 0u)
            {
                m_data = new T[size];
            }
        }

        // Constructor
        pod_vector(size_t size, T value) : m_data(nullptr), m_size(size), m_capacity(size)
        {
            static_assert(std::is_pod<T>::value, "pod_vector template type T must be a POD type");
            
            if (size > 0u)
            {
                m_data = new T[size];

                if constexpr (sizeof(T) == 1u)
                {
                    memset(m_data, *reinterpret_cast<uint8_t*>(&value), size);
                }
                else
                {
                    T* end = m_data + size;
                    for (T* ptr = m_data; ptr != end; ++ptr)
                    {
                        *ptr = value;
                    }
                }
            }
        }

        // Copy Constructor
        pod_vector(const pod_vector& o) : m_data(nullptr), m_size(o.m_size), m_capacity(o.m_size)
        {
            if (m_size > 0)
            {
                m_data = new T[m_capacity];
                memcpy(m_data, o.m_data, m_size * sizeof(T));
            }
        }

        // Move Constructor
        pod_vector(pod_vector&& o) noexcept : m_data(o.m_data), m_size(o.m_size), m_capacity(o.m_capacity)
        {
            o.m_data = nullptr;
            o.m_size = 0;
            o.m_capacity = 0;
        }

        // Copy-Assignment Operator
        pod_vector& operator=(const pod_vector& o)
        {
            if (this == &o)
            {
                return *this;
            }

            m_data = nullptr;
            m_size = o.m_size;
            m_capacity = o.m_size;

            if (m_size > 0)
            {
                m_data = new T[m_capacity];
                memcpy(m_data, o.m_data, m_size * sizeof(T));
            }

            return *this;
        }

        // Move-Assignment Operator
        pod_vector& operator=(pod_vector&& o) noexcept
        {
            if (this != &o)
            {
                delete[] m_data;

                m_data = o.m_data;
                m_size = o.m_size;
                m_capacity = o.m_capacity;

                o.m_data = nullptr;
                o.m_size = 0;
                o.m_capacity = 0;
            }

            return *this;
        }

        // Destructor
        ~pod_vector()
        {
            delete[] m_data;
        }

        // Returns const value at i
        template<class U>
        const T& operator[](U i) const
        {
            assert(static_cast<size_t>(i) < m_size);
            return m_data[i];
        }

        // Returns const value at i
        template<class U>
        const T& at(U i) const
        {
            assert(static_cast<size_t>(i) < m_size);
            return m_data[i];
        }

        // Returns value at i
        template<class U>
        T& operator[](U i)
        {
            assert(static_cast<size_t>(i) < m_size);
            return m_data[i];
        }

        // Returns value at i
        template<class U>
        T& at(U i)
        {
            assert(static_cast<size_t>(i) < m_size);
            return m_data[i];
        }

        // Reserves memory equal to n elements
        void reserve(size_t n)
        {
            if (n > m_capacity)
            {
                T* data = new T[n];
                if (m_size > 0)
                {
                    memcpy(data, m_data, m_size * sizeof(T));
                    delete[] m_data;
                }
                m_data = data;
                m_capacity = n;
            }
        }

        // Resizes the vector to n elements without initializing them
        void resize(size_t n)
        {
            reserve(n);
            m_size = n;
        }

        // Sets size to 0
        void clear()
        {
            m_size = 0;
        }

        // Returns true if the vector is empty (size = 0)
        [[nodiscard]]
        bool empty() const
        {
            return m_size == 0u;
        }

        // Returns the number of elements in the vector
        [[nodiscard]]
        size_t size() const
        {
            return m_size;
        }

        // Returns the element capacity of the vector
        [[nodiscard]]
        size_t capacity() const
        {
            return m_capacity;
        }

        // Returns pointer to data
        T* data()
        {
            return m_data;
        }

        // Returns const pointer to data
        const T* data() const
        {
            return m_data;
        }

        // Returns iterator to the beginning of the data
        iterator begin()
        {
            return iterator(m_data);
        }

        // Returns iterator to the end of the data
        iterator end()
        {
            return iterator(m_data + m_size);
        }

        // Returns const iterator to the beginning of the data
        const_iterator cbegin() const
        {
            return const_iterator(m_data);
        }

        // Returns const iterator to the end of the data
        const_iterator cend() const
        {
            return const_iterator(m_data + m_size);
        }

        // Returns iterator to the reverse beginning of the data
        reverse_iterator rbegin()
        {
            return reverse_iterator(m_data + m_size - 1);
        }

        // Returns iterator to the reverse end of the data
        reverse_iterator rend()
        {
            return reverse_iterator(m_data - 1);
        }

        // Returns iterator to the reverse beginning of the data
        const_reverse_iterator crbegin() const
        {
            return const_reverse_iterator(m_data + m_size - 1);
        }

        // Returns iterator to the reverse end of the data
        const_reverse_iterator crend() const
        {
            return const_reverse_iterator(m_data - 1);
        }

        // Pushes an element to the end of the data
        void push_back(const T& o)
        {
            // vector is full
            if (m_size == m_capacity)
            {
                // 1.5x capacity
                reserve((m_capacity < 4u)
                    ? (m_capacity + 1u)
                    : (m_capacity + (m_capacity >> 1u)));
            }

            m_data[m_size] = o;
            ++m_size;
        }

        // Pushes an array of n elements to the end of the data
        void push_back(const T* o, size_t n)
        {
            size_t targetSize = m_size + n;

            // vector is full
            if (targetSize > m_capacity)
            {
                // 1.5x capacity
                size_t newCap = m_capacity;

                while (newCap < targetSize)
                {
                    newCap = (newCap < 4u)
                        ? (newCap + 1u)
                        : (newCap + (newCap >> 1u));
                }

                reserve(newCap);
            }

            memcpy(&m_data[m_size], o, n * sizeof(T));
            m_size = targetSize;
        }

        // Pops an element from the end of the data
        void pop_back()
        {
            assert(m_size > 0u);
            --m_size;
        }

        // Returns reference to the first element
        T& front()
        {
            assert(m_size > 0u);
            return m_data[0];
        }

        // Returns const reference to the first element
        const T& front() const
        {
            assert(m_size > 0u);
            return m_data[0];
        }

        // Returns reference to the last element
        T& back()
        {
            assert(m_size > 0u);
            return m_data[m_size - 1u];
        }

        // Returns const reference to the last element
        const T& back() const
        {
            assert(m_size > 0u);
            return m_data[m_size - 1u];
        }

    protected:
        T* m_data;
        size_t m_size;
        size_t m_capacity;
    };
}

#endif