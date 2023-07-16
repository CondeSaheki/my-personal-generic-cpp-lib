#pragma once
#include <chrono>

#include "log.h"

namespace saheki
{
	namespace sch = std::chrono;
	class benchmark
	{
	private: // type
		using duration_type = sch::milliseconds;

	private: // data
		sch::time_point<sch::steady_clock> begin;

	public: // construction
		benchmark() : begin(sch::steady_clock::now()) {}
		~benchmark()
		{
			now();
		}

	public: // fn
		inline duration_type reset() noexcept
		{
			duration_type total = now();
			begin = sch::steady_clock::now();
			return total;
		}
		inline duration_type now() noexcept
		{
			duration_type total = sch::duration_cast<duration_type>(sch::steady_clock::now() - begin);
			log::debug("[ben] ", total.count());
			return total;
		}
	};
} // namespace end
