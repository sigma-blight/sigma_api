/*
	File:			vectorspace/basic_vectorspace.hpp
	Namespace:		sigma::math

	Encapsulate common vectorspace properties
	between all other vectorspaces
*/

#ifndef		_SIGMA_API_MATH_VECTORSPACE_BASIC_VECTORSPACE_HPP_
#define		_SIGMA_API_MATH_VECTORSPACE_BASIC_VECTORSPACE_HPP_

#include <array>

namespace sigma::math
{
	//	Axioms for a VectorSpace Field

	template <typename Field_>
	concept bool FieldType = requires(Field_ scalar)
	{
		// Closed under Addition
		static_cast<Field_>(scalar + scalar);

		// Closed under Multiplication
		static_cast<Field_>(scalar * scalar);

		// Contains 0 element
		static_cast<Field_>(0);
	};

	template <std::size_t n_, FieldType Field_>
	class BasicVectorSpace
	{
	public:

		using field_t = Field_;
		using element_t = std::array<field_t, n_>;

	private:

		element_t _data;

	public:

		//	Default Constructors

		BasicVectorSpace(void) = default;
		BasicVectorSpace(const BasicVectorSpace &) = default;
		BasicVectorSpace(BasicVectorSpace &&) = default;

		//	Default Assignment Operators

		BasicVectorSpace & operator = (const BasicVectorSpace &) = default;
		BasicVectorSpace & operator = (BasicVectorSpace &&) = default;

		//	Variadic Constructor

		template <typename... Types_>
		BasicVectorSpace(Types_... data) :
			_data{ static_cast<field_t>(data)... }
		{}

		//	Element Constructor

		BasicVectorSpace(const element_t & data) :
			_data{ data }
		{}

		//	Element Access

		element_t & element(void) { return BasicVectorSpace::_data; }
		const element_t & element(void) const { return BasicVectorSpace::_data; }

		//	Size

		static constexpr const std::size_t size(void) { return n_; }
	};
}

#endif	//	_SIGMA_API_MATH_VECTORSPACE_BASIC_VECTORSPACE_HPP_