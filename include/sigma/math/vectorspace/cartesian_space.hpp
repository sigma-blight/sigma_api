#ifndef		_SIGMA_API_MATH_VECTORSPACE_CARTESIAN_SPACE_HPP_
#define		_SIGMA_API_MATH_VECTORSPACE_CARTESIAN_SPACE_HPP_

#include "basic_vectorspace.hpp"
#include <utility>
#include <functional>

namespace sigma::math
{
	template <std::size_t dimensions_, typename Field_>
	class CartesianSpace : public BasicVectorSpace<dimensions_, Field_>
	{
		using vectorspace_t = BasicVectorSpace<dimensions_, Field_>;
		using element_t = typename vectorspace_t::element_t;
		using iterator_t = decltype(std::declval<element_t &>().begin());
		using field_t = Field_;

	public:

		//	Inherit Common Constructors

		using vectorspace_t::BasicVectorSpace;

		//	Inherit Common Assignment Operators

		using vectorspace_t::operator=;

	protected:

		//	VectorSpace Axiom Requirements

		//	Element Addition

		element_t element_addition(element_t rhs) const
		{
			element_t result;

			merge_apply(
				vectorspace_t::element().begin(),
				vectorspace_t::element().end(),
				rhs.begin(), result.begin(),
				std::plus<>());

			return result;
		}

		//	Scalar Multiplication to Element

		element_t scalar_multiplication(field_t scalar)
		{
			element_t result;

			std::transform(
				vectorspace_t::element().begin(),
				vectorspace_t::element().end(),
				result.begin(), [&scalar](auto value)
			{
				return value * scalar;
			});

			return result;
		}

	public:

		//	CartesianSpace specific properties

		//	Data Access

		field_t & operator[] (std::size_t index) { return vectorspace_t::element()[index]; }
		const field_t & operator[] (std::size_t index) const { return vectorspace_t::element()[index]; }

		//	Dot Product

		field_t dot(const CartesianSpace & rhs) const
		{
			field_t result;			
			
			merge_apply(
				vectorspace_t::element().begin(),
				vectorspace_t::element().end(),
				rhs.begin(), [&result](auto lhs, auto rhs)
			{
				result += lhs * rhs;
			});

			return result;
		}

		//	Cross Product

		CartesianSpace cross(const CartesianSpace & rhs) const
		{
			static_assert(dimensions_ == 3, 
				"cross product only applicable in 3 dimensions");
			return CartesianSpace
			{
				((*this)[1] * rhs[2]) - ((*this)[2] * rhs[1]),
				((*this)[2] * rhs[0]) - ((*this)[0] * rhs[2]), // swapped for negative
				((*this)[0] * rhs[1]) - ((*this)[1] * rhs[0])
			};
		}

	private:

		template <typename Function_>
		void merge_apply(iterator_t lhs, iterator_t lhs_end, 
			iterator_t rhs, iterator_t res, Function_ function)
		{
			for (; lhs != lhs_end; ++lhs, ++rhs, ++res)
				*res = function(*lhs, *rhs);
		}

		template <typename Function_>
		void merge_apply(iterator_t lhs, iterator_t lhs_end,
			iterator_t rhs, Function_ function)
		{
			for (; lhs != lhs_end; ++lhs, ++rhs)
				function(*lhs, *rhs);
		}
	};	
}

//	Short Hand Vector Spaces

namespace sigma::math::vectorspace
{
	template <std::size_t dimensions_, typename Field_ = double>
	using R = CartesianSpace<dimensions_, Field_>;

	template <std::size_t dimensions_, typename Field_ = int>
	using Z = CartesianSpace<dimensions_, Field_>;
}

#endif	//	_SIGMA_API_MATH_VECTORSPACE_CARTESIAN_SPACE_HPP_