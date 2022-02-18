// k13
// Kyle J Burgess

#ifndef K13_ALIGNED_POD_VECTOR_H
#define K13_ALIGNED_POD_VECTOR_H

#include "pod_vector.h"

namespace k13
{
    template<class T, size_t align_size>
    class aligned_pod_vector
    {
    public:

        using iterator = basic_iterator<T>;
        using const_iterator = basic_iterator<const T>;
        using reverse_iterator = basic_reverse_iterator<T>;
        using const_reverse_iterator = basic_reverse_iterator<const T>;

        aligned_pod_vector() : m_size(0)
        {
            static_assert(align_size != 0, "can't align on size of 0 bytes!");
            static_assert(sizeof(T) < align_size, "impossible alignment!");
            static_assert((align_size % sizeof(T)) == 0, "impossible alignment!");
        }

        // Returns const value at i
        template<class U>
        const T& operator[](U i) const
        {
            assert(static_cast<size_t>(i) < m_size);
            return reinterpret_cast<T*>(m_data.data())[i];
        }

        // Returns const value at i
        template<class U>
        const T& at(U i) const
        {
            assert(static_cast<size_t>(i) < m_size);
            return reinterpret_cast<T*>(m_data.data())[i];
        }

        // Returns value at i
        template<class U>
        T& operator[](U i)
        {
            assert(static_cast<size_t>(i) < m_size);
            return reinterpret_cast<T*>(m_data.data())[i];
        }

        // Returns value at i
        template<class U>
        T& at(U i)
        {
            assert(static_cast<size_t>(i) < m_size);
            return reinterpret_cast<T*>(m_data.data())[i];
        }

        // Reserves memory equal to n elements
        void reserve(size_t n)
        {
            m_data.reserve(impl_align_convert_n(n));
        }

        // Resizes the vector to n elements without initializing them
        void resize(size_t n)
        {
            m_size = n;
            m_data.resize(impl_align_convert_n(n));
        }

        // Sets size to 0
        void clear()
        {
            m_size = 0;
            m_data.clear();
        }

        // Shrink capacity to fit size
        void shrink_to_fit()
        {
            m_data.shrink_to_fit();
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
            return m_data.capacity();
        }

        // Returns pointer to data
        T* data()
        {
            return reinterpret_cast<T*>(m_data.data());
        }

        // Returns const pointer to data
        const T* data() const
        {
            return reinterpret_cast<T*>(m_data.data());
        }

        // Returns iterator to the beginning of the data
        iterator begin()
        {
            return iterator(reinterpret_cast<T*>(m_data.data()));
        }

        // Returns iterator to the end of the data
        iterator end()
        {
            return iterator(reinterpret_cast<T*>(m_data.data()) + m_size);
        }

        // Returns const iterator to the beginning of the data
        const_iterator cbegin() const
        {
            return const_iterator(reinterpret_cast<T*>(m_data.data()));
        }

        // Returns const iterator to the end of the data
        const_iterator cend() const
        {
            return const_iterator(reinterpret_cast<T*>(m_data.data()) + m_size);
        }

        // Returns iterator to the reverse beginning of the data
        reverse_iterator rbegin()
        {
            return reverse_iterator(reinterpret_cast<T*>(m_data.data()) + m_size - 1);
        }

        // Returns iterator to the reverse end of the data
        reverse_iterator rend()
        {
            return reverse_iterator(reinterpret_cast<T*>(m_data.data()) - 1);
        }

        // Returns iterator to the reverse beginning of the data
        const_reverse_iterator crbegin() const
        {
            return const_reverse_iterator(reinterpret_cast<T*>(m_data.data()) + m_size - 1);
        }

        // Returns iterator to the reverse end of the data
        const_reverse_iterator crend() const
        {
            return const_reverse_iterator(reinterpret_cast<T*>(m_data.data()) - 1);
        }

        // Returns reference to the first element
        T& front()
        {
            assert(m_size > 0u);
            return reinterpret_cast<T*>(m_data.data())[0];
        }

        // Returns const reference to the first element
        const T& front() const
        {
            assert(m_size > 0u);
            return reinterpret_cast<T*>(m_data.data())[0];
        }

        // Returns reference to the last element
        T& back()
        {
            assert(m_size > 0u);
            return reinterpret_cast<T*>(m_data.data())[m_size - 1u];
        }

        // Returns const reference to the last element
        const T& back() const
        {
            assert(m_size > 0u);
            return reinterpret_cast<T*>(m_data.data())[m_size - 1u];
        }

    protected:

        template<size_t align_size>
        struct impl_align_type
        {};

        template<> struct impl_align_type<1U>
        {
            using type = uint8_t;
        };

        template<> struct impl_align_type<2U>
        {
            using type = uint16_t;
        };

        template<> struct impl_align_type<4U>
        {
            using type = uint32_t;
        };

        template<> struct impl_align_type<8U>
        {
            using type = uint64_t;
        };

        using align_type = impl_align_type<align_size>::type;

        std::pod_vector<align_type> m_data;
        size_t m_size;

        size_t impl_align_convert_n(size_t n)
        {
            constexpr size_t m = align_size / sizeof(T);

            size_t r;

            if constexpr (m == 2)
            {
                r = byteCount & 1;
                byteCount >>= 1;
            }
            else if constexpr (m == 4)
            {
                r = byteCount & 3;
                byteCount >>= 2;
            }
            else if constexpr (m == 8)
            {
                r = byteCount & 7;
                byteCount >>= 3;
            }

            if (r != 0) ++byteCount;
            return byteCount;
        }
    };
}

#endif
