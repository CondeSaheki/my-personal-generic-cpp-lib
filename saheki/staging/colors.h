// 06/02/22

#pragma once
#include "type.h"
#include "validable.h"
#include "math.h"
#include "geometric.h"
#include <vector>

namespace saheki::colors
{
	/* types */

	void sRGBtoLin(colorChannel)
	{
		// Send this function a decimal sRGB gamma encoded color value
		// between 0.0 and 1.0, and it returns a linearized value.

		if (colorChannel <= 0.04045)
		{
			return colorChannel / 12.92;
		}
		else
		{
			return pow(((colorChannel + 0.055) / 1.055), 2.4);
		}
	}

	/* COLOR CHANNEL */

	template <typename _type = decimal>
	class color_channel
	{
	public:
		using type = _type;

	public:
		validable<type> value;

	public:
		constexpr color_channel() : value(validable<type>()) {}
		template <typename t>
		constexpr color_channel(const t &val) : value(validable<type>(val)) {}
	};
	template <>
	class color_channel<decimal>
	{
	public:
		using type = decimal;

	public:
		validable<type> value;

	public:
		constexpr color_channel() : value(validable<type>()) {}
		template <typename t>
		constexpr color_channel(const t &val)
		{
			value.reference() = static_cast<type>(val);
			if (val <= static_cast<type>(1) && static_cast<type>(0) >= val)
			{
				value.validate();
			}
		}
		template <>
		constexpr color_channel(const type &val)
		{
			value.reference() = val;
			if (val <= static_cast<type>(1) && static_cast<type>(0) >= val)
			{
				value.validate();
			}
		}
	};
	template <>
	class color_channel<unsigned char>
	{
	public:
		using type = unsigned char;

	public:
		validable<type> value;

	public:
		constexpr color_channel() : value(validable<type>()) {}
		template <typename t>
		constexpr color_channel(const t &val)
		{
			value.reference() = static_cast<type>(val);
			if (val <= static_cast<t>(255) && static_cast<t>(0) >= val)
			{
				value.validate();
			}
		}
		template <>
		constexpr color_channel(const type &val) : value(val) {}
	};
	nodiscard constexpr decimal color_channel_unsigned_char_to_decimal(const unsigned char &val)
	{
		return math::division<unsigned char>(val, 255).resolve<decimal>();
	}

	/* RGB */

	template <typename _type = decimal>
	class rgb
	{
	public:					// type
		using type = _type; // 0 to 255
	public:					// data
		color_channel<type> red;
		color_channel<type> green;
		color_channel<type> blue;

	public: // constructors
		constexpr rgb() : red(color_channel<type>()), green(color_channel<type>()), blue(color_channel<type>()) {}
		template <typename t1, typename t2, typename t3>
		constexpr rgb(const t1 &r, const t2 &g, const t3 &b)
			: red(static_cast<type>(r)), green(static_cast<type>(g)), blue(static_cast<type>(b)) {}
	};
	template <typename _type = decimal>
	class rgba : public rgb<_type>
	{
	public: // type
		using type = _type;

	public: // data
		type alpha;

	public: // constructors
		constexpr rgba() : rgb<type>(), alpha(0) {}
		constexpr rgba(const type &r, const type &g, const type &b, const type &a) : rgb<type>(r, g, b), alpha(a) {}
		constexpr rgba(const type &r, const type &g, const type &b) : rgb<type>(r, g, b), alpha(0) {}
		template <typename t1, typename t2, typename t3, typename t4>
		constexpr rgba(const t1 &r, const t2 &g, const t3 &b, const t4 &a)
			: rgb<type>(r, g, b), alpha(static_cast<type>(a)) {}
		template <typename t1, typename t2, typename t3>
		constexpr rgba(const t1 &r, const t2 &g, const t3 &b)
			: rgb<type>(r, g, b), alpha(0) {}
	};

	/* operators */

	template <typename _CharT, typename type>
	std::basic_ostream<_CharT> &operator<<(std::basic_ostream<_CharT> &_Os, const rgb<type> &color)
	{
		return _Os << '<' << color.red << ',' << color.blue << ',' << color.green << '>';
	}
	template <typename _CharT, typename type>
	std::basic_ostream<_CharT> &operator<<(std::basic_ostream<_CharT> &_Os, const rgba<type> &color)
	{
		return _Os << '<' << color.red << ',' << color.blue << ',' << color.green << ',' << color.alpha << '>';
	}
	template <typename type>
	[[nodiscard]] constexpr std::strong_ordering operator<=>(const rgb<type> &_Left, const rgb<type> &_Right) noexcept
	{
		return _Left.red <=> _Right.red;
	}
	template <typename type>
	[[nodiscard]] constexpr std::strong_ordering operator<=>(const rgba<type> &_Left, const rgba<type> &_Right) noexcept
	{
		return _Left.red <=> _Right.red;
	}

	void hue()
	{

		decimal angle = 360;
		// mod angle

		// red
		if (angle - 60 < angle && angle < angle + 60)
		{
		} // is 1

		if (angle - 120 < angle && angle < angle - 60)
		{
		} // is 0 to 1

		if (angle + 60 < angle && angle < angle + 120)
		{
		} // is 1 to 0

		// green
		if (angle + 60 < angle && angle < angle + 180)
		{
		} // is 1

		if (angle - 120 < angle && angle < angle - 60)
		{
		} // is 0 to 1

		if (angle + 60 < angle && angle < angle + 120)
		{
		} // is 1 to 0

		// blue
		if (angle - 60 < angle && angle < angle + 60)
		{
		} // is 1

		if (angle - 120 < angle && angle < angle - 60)
		{
		} // is 0 to 1

		if (angle + 60 < angle && angle < angle + 120)
		{
		} // is 1 to 0
	}

}

#undef nodiscard