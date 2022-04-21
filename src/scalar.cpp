// k13
// Kyle J Burgess

#include "scalar.h"

#include <sstream>
#include <iomanip>

namespace k13
{
    scalar_t::scalar_t()
    {
        m_type = type_int;
        m_data.int_val = 0;
    }

    bool scalar_t::operator==(const scalar_t& x) const
    {
        if (m_type == type_real || x.m_type == type_real)
        {
            return static_cast<real_t>(*this) == static_cast<real_t>(x);
        }

        return static_cast<int_t>(*this) == static_cast<int_t>(x);
    }

    bool scalar_t::operator!=(const scalar_t& x) const
    {
        return !operator==(x);
    }

    bool scalar_t::operator<(const scalar_t& x) const
    {
        if (m_type == type_real || x.m_type == type_real)
        {
            return static_cast<real_t>(*this) < static_cast<real_t>(x);
        }

        return static_cast<int_t>(*this) < static_cast<int_t>(x);
    }

    bool scalar_t::operator>(const scalar_t& x) const
    {
        if (m_type == type_real || x.m_type == type_real)
        {
            return static_cast<real_t>(*this) > static_cast<real_t>(x);
        }

        return static_cast<int_t>(*this) > static_cast<int_t>(x);
    }

    bool scalar_t::operator<=(const scalar_t& x) const
    {
        return !operator>(x);
    }

    bool scalar_t::operator>=(const scalar_t& x) const
    {
        return !operator<(x);
    }

    scalar_t scalar_t::operator+(const scalar_t& x) const
    {
        if (m_type == type_real || x.m_type == type_real)
        {
            return static_cast<real_t>(*this) + static_cast<real_t>(x);
        }

        return static_cast<int_t>(*this) + static_cast<int_t>(x);
    }

    scalar_t& scalar_t::operator++()
    {
        switch(m_type)
        {
            case type_real:
                m_data.real_val += 1.0;
                break;
            case type_int:
                m_data.int_val += 1;
                break;
            default:
                throw std::runtime_error("scalar_t unsupported type");
        }

        return *this;
    }

    scalar_t scalar_t::operator++(int)
    {
        scalar_t tmp = *this;

        switch(m_type)
        {
            case type_real:
                m_data.real_val += 1.0;
                break;
            case type_int:
                m_data.int_val += 1;
                break;
            default:
                throw std::runtime_error("scalar_t unsupported type");
        }

        return tmp;
    }

    scalar_t& scalar_t::operator+=(const scalar_t& x)
    {
        switch(m_type)
        {
            case type_real:
                m_data.real_val += static_cast<real_t>(x);
                break;
            case type_int:
                m_data.int_val += static_cast<int_t>(x);
                break;
            default:
                throw std::runtime_error("scalar_t unsupported type");
        }

        return *this;
    }

    scalar_t scalar_t::operator-(const scalar_t& x) const
    {
        if (m_type == type_real || x.m_type == type_real)
        {
            return static_cast<real_t>(*this) - static_cast<real_t>(x);
        }

        return static_cast<int_t>(*this) - static_cast<int_t>(x);
    }

    scalar_t& scalar_t::operator--()
    {
        switch(m_type)
        {
            case type_real:
                m_data.real_val -= 1.0;
                break;
            case type_int:
                m_data.int_val -= 1;
                break;
            default:
                throw std::runtime_error("scalar_t unsupported type");
        }

        return *this;
    }

    scalar_t scalar_t::operator--(int)
    {
        scalar_t tmp = *this;

        switch(m_type)
        {
            case type_real:
                m_data.real_val -= 1.0;
                break;
            case type_int:
                m_data.int_val -= 1;
                break;
            default:
                throw std::runtime_error("scalar_t unsupported type");
        }

        return tmp;
    }

    scalar_t& scalar_t::operator-=(const scalar_t& x)
    {
        switch(m_type)
        {
            case type_real:
                m_data.real_val -= static_cast<real_t>(x);
                break;
            case type_int:
                m_data.int_val -= static_cast<int_t>(x);
                break;
            default:
                throw std::runtime_error("scalar_t unsupported type");
        }

        return *this;
    }

    scalar_t scalar_t::operator*(const scalar_t& x) const
    {
        if (m_type == type_real || x.m_type == type_real)
        {
            return static_cast<real_t>(*this) * static_cast<real_t>(x);
        }

        return static_cast<int_t>(*this) * static_cast<int_t>(x);
    }

    scalar_t& scalar_t::operator*=(const scalar_t& x)
    {
        switch(m_type)
        {
            case type_real:
                m_data.real_val *= static_cast<real_t>(x);
                break;
            case type_int:
                m_data.int_val *= static_cast<int_t>(x);
                break;
            default:
                throw std::runtime_error("scalar_t unsupported type");
        }

        return *this;
    }

    scalar_t scalar_t::operator/(const scalar_t& x) const
    {
        if (m_type == type_real || x.m_type == type_real)
        {
            return static_cast<real_t>(*this) / static_cast<real_t>(x);
        }

        return static_cast<int_t>(*this) / static_cast<int_t>(x);
    }

    scalar_t& scalar_t::operator/=(const scalar_t& x)
    {
        switch(m_type)
        {
            case type_real:
                m_data.real_val /= static_cast<real_t>(x);
                break;
            case type_int:
                m_data.int_val /= static_cast<int_t>(x);
                break;
            default:
                throw std::runtime_error("scalar_t unsupported type");
        }

        return *this;
    }

    std::string scalar_t::to_string() const
    {
        switch(m_type)
        {
            case type_real:
                {
                    std::stringstream ss;
                    ss  << std::setprecision(17)
                        << m_data.real_val;
                    return ss.str();
                }
            case type_int:
                return std::to_string(m_data.int_val);
            default:
                throw std::runtime_error("scalar_t unsupported type");
        }
    }

    bool scalar_t::is_floating_point() const
    {
        return m_type == type_real;
    }

    bool scalar_t::is_integer() const
    {
        return m_type == type_int;
    }
}
