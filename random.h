#pragma once
#include <random>

namespace saheki
{
    class random_generator
    {
    public: // pub type
        using num_type = u_int64_t;

    private: // pri data
        std::mt19937_64 mt;

    public: // fn
        template <typename min_type, typename max_type>
        static num_type number(const min_type &_min, const max_type &_max)
        {
            return Get()._generate(static_cast<num_type>(_min), static_cast<num_type>(_max));
        }
        template <typename max_type>
        static num_type number(const max_type &_max)
        {
            return Get()._generate(static_cast<num_type>(0), static_cast<num_type>(_max));
        }

    private: // pri fn
        num_type _generate(const num_type &&min, const num_type &&max)
        {
            std::uniform_int_distribution<num_type> dist(min, max);
            return dist(mt);
        }

    private: // constructors
        random_generator() : mt()
        {
            std::random_device rd;
            mt.seed(rd());
        }
        static random_generator &Get()
        {
            static random_generator instance;
            return instance;
        }

    public: // operators
        random_generator(const random_generator &) = delete;
    };
} // namespace end