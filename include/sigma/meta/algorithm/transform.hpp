#ifndef		_SIGMA_API_META_ALGORITHM_TRANSFORM_HPP_
#define		_SIGMA_API_META_ALGORITHM_TRANSFORM_HPP_

#include "../container/vector.hpp"

namespace sigma::meta
{
	//		**	APPLY **

	template <typename... Types_, typename Function_>
	inline constexpr auto apply(TVector<Types_...>, Function_ function)
	{
		return TVector<typename decltype(function(type_c<Types_>))::type_t...>{};
	}

	template <auto... values_, typename Function_>
	inline constexpr auto apply(VVector<values_...>, Function_ function)
	{
		return VVector<function(values_)...>{};
	}

	//		**	FILTER **

	template <typename... Types_, typename Predicate_, typename... Results_>
	inline constexpr auto filter(TVector<Types_...> input, Predicate_ pred, 
		TVector<Results_...> result = TVector<>{})
	{
		if constexpr (input.size() == 0) return result;
		else if constexpr (pred(input.front()))
			return filter(input.pop_front(), pred, result);
		else
			return filter(input.pop_front(), pred, result.push_back(input.front()));			
	}

	template <auto... values_, typename Predicate_, auto... results_>
	inline constexpr auto filter(VVector<values_...> input, Predicate_ pred,
		VVector<results_...> result = VVector<>{})
	{
		if constexpr (input.size() == 0) return result;
		else if constexpr (pred(input.front()))
			return filter(input.pop_front(), pred, result);
		else
			return filter(input.pop_front(), pred, result.push_back(input.front()));
	}

	//		**	MERGE **

	template <typename... LHS_, typename... RHS_, typename Function_>
	inline constexpr auto merge(TVector<LHS_...> lhs, TVector<RHS_...> rhs, Function_ function)
	{
		static_assert(lhs.size() == rhs.size(), "requires equal sizes");
		return TVector<typename decltype(function(type_c<LHS_>, type_c<RHS_>))::type_t...>{};
	}

	template <auto... lhs_, auto... rhs_, typename Function_>
	inline constexpr auto merge(VVector<lhs_...> lhs, VVector<rhs_...> rhs, Function_ function)
	{
		static_assert(lhs.size() == rhs.size(), "requires equal sizes");
		return VVector<function(lhs_, rhs_)...>{};
	}
}

#endif	//	_SIGMA_API_META_ALGORITHM_TRANSFORM_HPP_