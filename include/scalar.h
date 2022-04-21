// k13
// Kyle J Burgess

#ifndef K13_SCALAR_H
#define K13_SCALAR_H

#include <string>
#include <cstdint>
#include <type_traits>
#include <stdexcept>

namespace k13
{
    class scalar_t
    {
    public:

        // Construct a scalar with a value of 0
        scalar_t();

        // Construct a scalar_t with a value of x
        template<class T>
        scalar_t(T x)
        {
            if constexpr (std::is_floating_point<T>::value)
            {
                m_type = type_real;
                m_data.real_val = x;
            }
            else
            {
                m_type = type_int;
                m_data.int_val = x;
            }
        }

        // Static-cast a scalar_t to type T
        template<class T>
        [[nodiscard]]
        operator T() const
        {
            switch(m_type)
            {
                case type_real:
                    return static_cast<T>(m_data.real_val);
                case type_int:
                    return static_cast<T>(m_data.int_val);
                default:
                    throw std::runtime_error("scalar_t unsupported type");
            }
        }

        // Comparison
        [[nodiscard]]
        bool operator==(const scalar_t& x) const;

        [[nodiscard]]
        bool operator!=(const scalar_t& x) const;

        [[nodiscard]]
        bool operator<(const scalar_t& x) const;

        [[nodiscard]]
        bool operator>(const scalar_t& x) const;

        [[nodiscard]]
        bool operator<=(const scalar_t& x) const;

        [[nodiscard]]
        bool operator>=(const scalar_t& x) const;

        // Math
        [[nodiscard]]
        scalar_t operator+(const scalar_t& x) const;

        scalar_t& operator++();

        scalar_t operator++(int);

        scalar_t& operator+=(const scalar_t& x);

        [[nodiscard]]
        scalar_t operator-(const scalar_t& x) const;

        scalar_t& operator--();

        scalar_t operator--(int);

        scalar_t& operator-=(const scalar_t& x);

        [[nodiscard]]
        scalar_t operator*(const scalar_t& x) const;

        scalar_t& operator*=(const scalar_t& x);

        [[nodiscard]]
        scalar_t operator/(const scalar_t& x) const;

        scalar_t& operator/=(const scalar_t& x);

        // Convert value into a string
        [[nodiscard]]
        std::string to_string() const;

        // True if the underlying value is a floating point number
        [[nodiscard]]
        bool is_floating_point() const;

        // True if the underlying value is an integer number
        [[nodiscard]]
        bool is_integer() const;

        // STL stream integration
        friend std::ostream& operator<<(std::ostream& os, const scalar_t& x);

        // Comparison friends
        template<class T>
        friend bool operator==(T lhs, const scalar_t& rhs);

        template<class T>
        friend bool operator==(const scalar_t& lhs, T rhs);

        template<class T>
        friend bool operator!=(T lhs, const scalar_t& rhs);

        template<class T>
        friend bool operator!=(const scalar_t& lhs, T rhs);

        template<class T>
        friend bool operator<(T lhs, const scalar_t& rhs);

        template<class T>
        friend bool operator<(const scalar_t& lhs, T rhs);

        template<class T>
        friend bool operator>(T lhs, const scalar_t& rhs);

        template<class T>
        friend bool operator>(const scalar_t& lhs, T rhs);

        template<class T>
        friend bool operator<=(T lhs, const scalar_t& rhs);

        template<class T>
        friend bool operator<=(const scalar_t& lhs, T rhs);

        template<class T>
        friend bool operator>=(T lhs, const scalar_t& rhs);

        template<class T>
        friend bool operator>=(const scalar_t& lhs, T rhs);

        // Math friends
        template<class T>
        friend scalar_t operator+(T lhs, const scalar_t& rhs);

        template<class T>
        friend scalar_t operator+(const scalar_t& lhs, T rhs);

        template<class T>
        friend scalar_t operator-(T lhs, const scalar_t& rhs);

        template<class T>
        friend scalar_t operator-(const scalar_t& lhs, T rhs);

        template<class T>
        friend scalar_t operator*(T lhs, const scalar_t& rhs);

        template<class T>
        friend scalar_t operator*(const scalar_t& lhs, T rhs);

        template<class T>
        friend scalar_t operator/(T lhs, const scalar_t& rhs);

        template<class T>
        friend scalar_t operator/(const scalar_t& lhs, T rhs);

    protected:

        using int_t = int64_t;
        using real_t = double;

        enum Type
        {
            type_int,
            type_real,
        } m_type;

        union
        {
            int_t int_val;
            real_t real_val;
        } m_data;

    };

    std::ostream& operator<<(std::ostream& os, const scalar_t& x)
    {
        os << x.to_string();
        return os;
    }

    // Math

    template<class T>
    [[nodiscard]]
    scalar_t operator+(T lhs, const scalar_t& rhs)
    {
        if (std::is_floating_point<T>::value || rhs.m_type == scalar_t::type_real)
        {
            return static_cast<scalar_t::real_t>(lhs) + static_cast<scalar_t::real_t>(rhs);
        }

        return static_cast<scalar_t::int_t>(lhs) + static_cast<scalar_t::int_t>(rhs);
    }

    template<class T>
    [[nodiscard]]
    scalar_t operator+(const scalar_t& lhs, T rhs)
    {
        if (lhs.m_type == scalar_t::type_real || std::is_floating_point<T>::value)
        {
            return static_cast<scalar_t::real_t>(lhs) + static_cast<scalar_t::real_t>(rhs);
        }

        return static_cast<scalar_t::int_t>(lhs) + static_cast<scalar_t::int_t>(rhs);
    }

    template<class T>
    [[nodiscard]]
    scalar_t operator-(T lhs, const scalar_t& rhs)
    {
        if (std::is_floating_point<T>::value || rhs.m_type == scalar_t::type_real)
        {
            return static_cast<scalar_t::real_t>(lhs) - static_cast<scalar_t::real_t>(rhs);
        }

        return static_cast<scalar_t::int_t>(lhs) - static_cast<scalar_t::int_t>(rhs);
    }

    template<class T>
    [[nodiscard]]
    scalar_t operator-(const scalar_t& lhs, T rhs)
    {
        if (lhs.m_type == scalar_t::type_real || std::is_floating_point<T>::value)
        {
            return static_cast<scalar_t::real_t>(lhs) - static_cast<scalar_t::real_t>(rhs);
        }

        return static_cast<scalar_t::int_t>(lhs) - static_cast<scalar_t::int_t>(rhs);
    }

    template<class T>
    [[nodiscard]]
    scalar_t operator*(T lhs, const scalar_t& rhs)
    {
        if (std::is_floating_point<T>::value || rhs.m_type == scalar_t::type_real)
        {
            return static_cast<scalar_t::real_t>(lhs) * static_cast<scalar_t::real_t>(rhs);
        }

        return static_cast<scalar_t::int_t>(lhs) * static_cast<scalar_t::int_t>(rhs);
    }

    template<class T>
    [[nodiscard]]
    scalar_t operator*(const scalar_t& lhs, T rhs)
    {
        if (lhs.m_type == scalar_t::type_real || std::is_floating_point<T>::value)
        {
            return static_cast<scalar_t::real_t>(lhs) * static_cast<scalar_t::real_t>(rhs);
        }

        return static_cast<scalar_t::int_t>(lhs) * static_cast<scalar_t::int_t>(rhs);
    }

    template<class T>
    [[nodiscard]]
    scalar_t operator/(T lhs, const scalar_t& rhs)
    {
        if (std::is_floating_point<T>::value || rhs.m_type == scalar_t::type_real)
        {
            return static_cast<scalar_t::real_t>(lhs) / static_cast<scalar_t::real_t>(rhs);
        }

        return static_cast<scalar_t::int_t>(lhs) / static_cast<scalar_t::int_t>(rhs);
    }

    template<class T>
    [[nodiscard]]
    scalar_t operator/(const scalar_t& lhs, T rhs)
    {
        if (lhs.m_type == scalar_t::type_real || std::is_floating_point<T>::value)
        {
            return static_cast<scalar_t::real_t>(lhs) / static_cast<scalar_t::real_t>(rhs);
        }

        return static_cast<scalar_t::int_t>(lhs) / static_cast<scalar_t::int_t>(rhs);
    }

    template<class T>
    [[nodiscard]]
    bool operator==(T lhs, const scalar_t& rhs)
    {
        if (std::is_floating_point<T>::value || rhs.m_type == scalar_t::type_real)
        {
            return static_cast<scalar_t::real_t>(lhs) == static_cast<scalar_t::real_t>(rhs);
        }

        return static_cast<scalar_t::int_t>(lhs) == static_cast<scalar_t::int_t>(rhs);
    }

    template<class T>
    [[nodiscard]]
    bool operator==(const scalar_t& lhs, T rhs)
    {
        if (lhs.m_type == scalar_t::type_real || std::is_floating_point<T>::value)
        {
            return static_cast<scalar_t::real_t>(lhs) == static_cast<scalar_t::real_t>(rhs);
        }

        return static_cast<scalar_t::int_t>(lhs) == static_cast<scalar_t::int_t>(rhs);
    }

    template<class T>
    [[nodiscard]]
    bool operator!=(T lhs, const scalar_t& rhs)
    {
        return !operator==(lhs, rhs);
    }

    template<class T>
    [[nodiscard]]
    bool operator!=(const scalar_t& lhs, T rhs)
    {
        return !operator==(lhs, rhs);
    }

    template<class T>
    [[nodiscard]]
    bool operator<(T lhs, const scalar_t& rhs)
    {
        if (std::is_floating_point<T>::value || rhs.m_type == scalar_t::type_real)
        {
            return static_cast<scalar_t::real_t>(lhs) < static_cast<scalar_t::real_t>(rhs);
        }

        return static_cast<scalar_t::int_t>(lhs) < static_cast<scalar_t::int_t>(rhs);
    }

    template<class T>
    [[nodiscard]]
    bool operator<(const scalar_t& lhs, T rhs)
    {
        if (lhs.m_type == scalar_t::type_real || std::is_floating_point<T>::value)
        {
            return static_cast<scalar_t::real_t>(lhs) < static_cast<scalar_t::real_t>(rhs);
        }

        return static_cast<scalar_t::int_t>(lhs) < static_cast<scalar_t::int_t>(rhs);
    }

    template<class T>
    [[nodiscard]]
    bool operator>(T lhs, const scalar_t& rhs)
    {
        if (std::is_floating_point<T>::value || rhs.m_type == scalar_t::type_real)
        {
            return static_cast<scalar_t::real_t>(lhs) > static_cast<scalar_t::real_t>(rhs);
        }

        return static_cast<scalar_t::int_t>(lhs) > static_cast<scalar_t::int_t>(rhs);
    }

    template<class T>
    [[nodiscard]]
    bool operator>(const scalar_t& lhs, T rhs)
    {
        if (lhs.m_type == scalar_t::type_real || std::is_floating_point<T>::value)
        {
            return static_cast<scalar_t::real_t>(lhs) > static_cast<scalar_t::real_t>(rhs);
        }

        return static_cast<scalar_t::int_t>(lhs) > static_cast<scalar_t::int_t>(rhs);
    }

    template<class T>
    [[nodiscard]]
    bool operator<=(T lhs, const scalar_t& rhs)
    {
        return !operator>(lhs, rhs);
    }

    template<class T>
    [[nodiscard]]
    bool operator<=(const scalar_t& lhs, T rhs)
    {
        return !operator>(lhs, rhs);
    }

    template<class T>
    [[nodiscard]]
    bool operator>=(T lhs, const scalar_t& rhs)
    {
        return !operator<(lhs, rhs);
    }

    template<class T>
    [[nodiscard]]
    bool operator>=(const scalar_t& lhs, T rhs)
    {
        return !operator<(lhs, rhs);
    }
}

#endif
