#ifndef		_SIGMA_API_CONTAINER_TRAITS_HPP_
#define		_SIGMA_API_CONTAINER_TRAITS_HPP_

#include <type_traits>

namespace sigma::meta
{
	template <typename Type_>
	struct Type
	{
		using type_t = Type_;

		template <typename Other_>
		constexpr bool operator == (Type<Other_>) const { return false; }
		constexpr bool operator == (Type<Type_>) const { return true; }
	};

	template <typename Type_>
	inline constexpr auto type_c = Type<Type_>{};

	namespace detail
	{
		template <typename Type_, char digit_>
		constexpr Type_ digit_parse(void)
		{
			static_assert(digit_ >= '0' && digit_ <= '9',
				"invalid digit to parse");
			return digit_ - '0';
		}

		template <typename Type_, typename ... Types_>
		constexpr Type_ parser(Type_ result, Type_ first, Types_... trail)
		{
			if constexpr (sizeof...(trail) == 0)
				return result * 10 + first;
			else
				return parser(result * 10 + first, trail...);
		}

		template <char... digits_>
		constexpr void assert_size(void)
		{
			static_assert(sizeof...(digits_) != 0,
				"cannot parse integer without characters");
		}

		template <typename Type_, char... digits_>
		constexpr auto integral_parse(void)
		{
			return parser<Type_>(0, digit_parse<Type_, digits_>()...);
		}

		template <typename Type_, char... digits_>
		constexpr auto make_constant(void)
		{
			return std::integral_constant<Type_, integral_parse<Type_, digits_...>()>{};
		}
	}

	inline namespace literals
	{	
		template <char... digits_>
		inline constexpr auto operator"" _i(void)
		{
			using namespace detail;
			assert_size<digits_...>();			
			return make_constant<int, digits_...>();
		}

		template <char... digits_>
		inline constexpr auto operator"" _u(void)
		{
			using namespace detail;
			assert_size<digits_...>();
			return make_constant<std::size_t, digits_...>();
		}
	}
}

#endif	//	_SIGMA_API_CONTAINER_TRAITS_HPP_