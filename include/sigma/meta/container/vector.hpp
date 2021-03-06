#ifndef		_SIGMA_API_META_CONTINER_VECTOR_HPP_
#define		_SIGMA_API_META_CONTINER_VECTOR_HPP_

#include <type_traits>
#include "traits.hpp"

namespace sigma::meta
{
	template <typename... Types_>
	class TVector
	{
		template <std::size_t index_, typename First_, typename... Trail_>
		static constexpr auto get_impl(void)
		{
			if constexpr (index_ == 0) return type_c<First_>;
			else return get_impl<index_ - 1, Trail_...>();
		}

	public:

		static constexpr std::size_t size(void) { return sizeof...(Types_); }

		template <std::size_t index_>
		static constexpr auto get(std::integral_constant<std::size_t, index_>)
		{
			static_assert(index_ < size(), "index is out of bounds");
			return get_impl<index_, Types_...>();
		}

		template <std::size_t index_>
		static constexpr auto get(void) { return get(std::integral_constant<std::size_t, index_>{}); }

		template <std::size_t index_>
		constexpr auto operator[] (std::integral_constant<std::size_t, index_> index) const
		{ return get(index); }

		static constexpr auto front(void) { return get<0>(); }
		static constexpr auto back(void) { return get<size() - 1>(); }

	private:

		static constexpr void assert_safe_pop(void)
		{ static_assert(size() != 0, "cannot pop from no elements"); }

		template <typename, typename... Trail_>
		static constexpr auto pop_front_impl(void) { return TVector<Trail_...>{}; }

		template <typename Vector_, typename First_, typename... Trail_>
		static constexpr auto pop_back_impl(void) 
		{
			if constexpr (TVector<Trail_...>::size() == 0) return Vector_{};
			else
			{
				using tvector_t = decltype(Vector_::push_back(type_c<First_>));
				return pop_back_impl<tvector_t, Trail_...>();
			}
		};

	public:

		template <typename Type_>
		static constexpr auto push_back(Type<Type_>) { return TVector<Types_..., Type_>{}; }

		template <typename Type_>
		static constexpr auto push_front(Type<Type_>) { return TVector<Type_, Types_...>{}; }

		static constexpr auto pop_front(void)
		{
			assert_safe_pop();
			return pop_front_impl<Types_...>();
		}

		static constexpr auto pop_back(void)
		{
			assert_safe_pop();
			return pop_back_impl<TVector<>, Types_... >();
		}

		template <typename... Others_>
		constexpr bool operator == (TVector<Others_...>) const { return false; }
		constexpr bool operator == (TVector<Types_...>) const { return true; }

		template <typename... Others_>
		constexpr bool operator != (TVector<Others_...> other) const { return !(*this == other); }
	};



	template <auto... values_>
	class VVector
	{
		template <std::size_t index_, auto first_, auto... trail_>
		static constexpr auto get_impl(void)
		{
			if constexpr (index_ == 0) return first_;
			else return get_impl<index_ - 1, trail_...>();
		}

	public:

		static constexpr std::size_t size(void) { return sizeof...(values_); }

		template <std::size_t index_>
		static constexpr auto get(std::integral_constant<std::size_t, index_>)
		{
			static_assert(index_ < size(), "index is out of bounds");
			return get_impl<index_, values_...>();
		}

		template <std::size_t index_>
		static constexpr auto get(void) { return get(std::integral_constant<std::size_t, index_>{}); }

		template <std::size_t index_>
		constexpr auto operator[] (std::integral_constant<std::size_t, index_> index) const
		{
			return get(index);
		}

		static constexpr auto front(void) { return get<0>(); }
		static constexpr auto back(void) { return get<size() - 1>(); }

	private:

		static constexpr void assert_safe_pop(void)
		{
			static_assert(size() != 0, "cannot pop from no elements");
		}

		template <auto, auto... trail_>
		static constexpr auto pop_front_impl(void) { return VVector<trail_...>{}; }

		template <typename Vector_, auto first_, auto... trail_>
		static constexpr auto pop_back_impl(void)
		{
			if constexpr (VVector<trail_...>::size() == 0) return Vector_{};
			else
			{
				using vvector_t = decltype(Vector_::template push_back<first_>());
				return pop_back_impl<vvector_t, trail_...>();
			}
		}

	public:

		template <auto value_>
		static constexpr auto push_back(std::integral_constant<decltype(value_), value_>)
		{ return VVector<values_..., value_>{}; }
		
		template <auto value_>
		static constexpr auto push_back(void) { return VVector<values_..., value_>{}; }

		template <auto value_>
		static constexpr auto push_front(std::integral_constant<decltype(value_), value_>)
		{ return VVector<value_, values_...>{}; }

		template <auto value_>
		static constexpr auto push_front(void) { return VVector<value_, values_...>{}; }

		static constexpr auto pop_front(void)
		{
			assert_safe_pop();
			return pop_front_impl<values_...>();
		}

		static constexpr auto pop_back(void)
		{
			assert_safe_pop();
			return pop_back_impl<VVector<>, values_...>();
		}

		template <auto... others_>
		constexpr bool operator == (VVector<others_...>) const { return false; }
		constexpr bool operator == (VVector<values_...>) const { return true; }

		template <auto... others_>
		constexpr bool operator != (VVector<others_...> other) const { return !(*this == other); }
	};
}

#endif	//	_SIGMA_API_META_CONTINER_VECTOR_HPP_