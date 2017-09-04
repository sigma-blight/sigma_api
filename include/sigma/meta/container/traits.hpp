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

	//*******************************************
	//			type_traits recreation
	//*******************************************

	//		**	PRIMARY CATEGORIES **

	template <typename Type_>
	inline constexpr bool is_void(Type<Type_>) { return std::is_void_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_null_pointer(Type<Type_>) { return std::is_null_pointer_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_integral(Type<Type_>) { return std::is_integral_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_floating_point(Type<Type_>) { return std::is_floating_point_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_array(Type<Type_>) { return std::is_array_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_enum(Type<Type_>) { return std::is_enum_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_union(Type<Type_>) { return std::is_union_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_class(Type<Type_>) { return std::is_class_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_function(Type<Type_>) { return std::is_function_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_pointer(Type<Type_>) { return std::is_pointer_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_lvalue_reference(Type<Type_>) { return std::is_lvalue_reference_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_rvalue_reference(Type<Type_>) { return std::is_rvalue_reference_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_member_object_pointer(Type<Type_>) { return std::is_member_object_pointer_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_member_function_pointer(Type<Type_>) { return std::is_member_function_pointer_v<Type_>; }

	//		**	COMPOSITE TYPE CATEGORIES **

	template <typename Type_>
	inline constexpr bool is_fundamental(Type<Type_>) { return std::is_fundamental_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_arithmetic(Type<Type_>) { return std::is_arithmetic_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_scalar(Type<Type_>) { return std::is_scalar_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_object(Type<Type_>) { return std::is_object_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_compound(Type<Type_>) { return std::is_compound_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_reference(Type<Type_>) { return std::is_reference_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_member_pointer(Type<Type_>) { return std::is_member_pointer_v<Type_>; }

	//		**	TYPE PROPERTIES **

	template <typename Type_>
	inline constexpr bool is_const(Type<Type_>) { return std::is_const_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_volatile(Type<Type_>) { return std::is_volatile_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_trivial(Type<Type_>) { return std::is_trivial_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_trivially_copyable(Type<Type_>) { return std::is_trivially_copyable_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_standard_layout(Type<Type_>) { return std::is_standard_layout_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_pod(Type<Type_>) { return std::is_pod_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_literal_type(Type<Type_>) { return std::is_literal_type_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_empty(Type<Type_>) { return std::is_empty_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_polymorphic(Type<Type_>) { return std::is_polymorphic_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_abstract(Type<Type_>) { return std::is_abstract_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_final(Type<Type_>) { return std::is_final_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_aggregate(Type<Type_>) { return std::is_aggregate_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_signed(Type<Type_>) { return std::is_signed_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_unsigned(Type<Type_>) { return std::is_unsigned_v<Type_>; }

	//		**	SUPPORTED OPERATIONS **

	template <typename Type_, typename... Args_>
	inline constexpr bool is_constructible(Type<Type_>, Type<Args_>...) 
	{ return std::is_constructible_v<Type_, Args_...>; }

	template <typename Type_, typename... Args_>
	inline constexpr bool is_trivially_constructible(Type<Type_>, Type<Args_>...) 
	{ return std::is_trivially_constructible_v<Type_, Args_...>; }

	template <typename Type_, typename... Args_>
	inline constexpr bool is_nothrow_consructible(Type<Type_>, Type<Args_>...) 
	{ return std::is_nothrow_constructible_v<Type_, Args_...>; }

	template <typename Type_>
	inline constexpr bool is_default_constructible(Type<Type_>) { return std::is_default_constructible_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_trivially_default_constructible(Type<Type_>) 
	{ return std::is_trivially_default_constructible_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_nothrow_default_constructible(Type<Type_>) 
	{ return std::is_nothrow_default_constructible_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_copy_constructible(Type<Type_>) { return std::is_copy_constructible_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_trivially_copy_constructible(Type<Type_>) 
	{ return std::is_trivially_copy_constructible_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_nothrow_copy_constructible(Type<Type_>) 
	{ return std::is_nothrow_copy_constructible_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_move_constructible(Type<Type_>) { return std::is_move_constructible_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_trivially_move_constructible(Type<Type_>) 
	{ return std::is_trivially_move_constructible_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_nothrow_move_constructible(Type<Type_>) 
	{ return std::is_nothrow_move_constructible_v<Type_>; }

	template <typename LHS_, typename RHS_>
	inline constexpr bool is_assignable(Type<LHS_>, Type<RHS_>) { return std::is_assignable_v<LHS_, RHS_>; }

	template <typename LHS_, typename RHS_>
	inline constexpr bool is_trivially_assignable(Type<LHS_>, Type<RHS_>) 
	{ return std::is_trivially_assignable_v<LHS_, RHS_>; }

	template <typename LHS_, typename RHS_>
	inline constexpr bool is_nothrow_assignable(Type<LHS_>, Type<RHS_>) 
	{ return std::is_nothrow_assignable_v<LHS_, RHS_>; }

	template <typename Type_>
	inline constexpr bool is_copy_assignable(Type<Type_>) { return std::is_copy_assignable_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_trivially_copy_assignable(Type<Type_>) { return std::is_trivially_copy_assignable_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_nothrow_copy_assignable(Type<Type_>) { return std::is_nothrow_copy_assignable_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_move_assignable(Type<Type_>) { return std::is_move_assignable_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_trivially_move_assignable(Type<Type_>) { return std::is_trivially_move_assignable_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_nothrow_move_assignable(Type<Type_>) { return std::is_nothrow_move_assignable_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_destructible(Type<Type_>) { return std::is_destructible_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_trivially_destructible(Type<Type_>) { return std::is_trivially_destructible_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_nothrow_destructible(Type<Type_>) { return std::is_nothrow_destructible_v<Type_>; }

	template <typename Type_>
	inline constexpr bool has_virtual_destructor(Type<Type_>) { return std::has_virtual_destructor_v<Type_>; }

	template <typename Type_>
	inline constexpr bool is_swappable(Type<Type_>) { return std::is_swappable_v<Type_>; }

	template <typename LHS_, typename RHS_>
	inline constexpr bool is_swappable_with(Type<LHS_>, Type<RHS_>) { return std::is_swappable_with_v<LHS_, RHS_>; }

	template <typename Type_>
	inline constexpr bool is_nothrow_swappable(Type<Type_>) { return std::is_nothrow_swappable_v<Type_>; }

	template <typename LHS_, typename RHS_>
	inline constexpr bool is_nothrow_swappable_with(Type<LHS_>, Type<RHS_>) { return std::is_nothrow_swappable_with_v<LHS_, RHS_>; }

	//		**	PROPERTY QUERIES **

	template <typename Type_>
	inline constexpr std::size_t alignment_of(Type<Type_>) { return std::alignment_of_v<Type_>; }

	template <typename Type_>
	inline constexpr std::size_t rank(Type<Type_>) { return std::rank_v<Type_>; }

	template <typename Type_>
	inline constexpr std::size_t extent(Type<Type_>) { return std::extent_v<Type_>; }

	//		**	TYPE RELATIONSHIPS **

	template <typename LHS_, typename RHS_>
	inline constexpr bool is_same(Type<LHS_>, Type<RHS_>) { return std::is_same_v<LHS_, RHS_>; }

	template <typename Base_, typename Derived_>
	inline constexpr bool is_base_of(Type<Base_>, Type<Derived_>) { return std::is_base_of_v<Base_, Derived_>; }

	template <typename From_, typename To_>
	inline constexpr bool is_convertible(Type<From_>, Type<To_>) { return std::is_convertible_v<From_, To_>; }

	template <typename Function_, typename... ArgTypes_>
	inline constexpr bool is_invocable(Type<Function_>, Type<ArgTypes_>...) 
	{ return std::is_invocable_v<Function_, ArgTypes_...>; }

	template <typename Return_, typename Function_, typename... ArgTypes_>
	inline constexpr bool is_invocable_r(Type<Return_>, Type<Function_>, Type<ArgTypes_>...)
	{ return std::is_invocable_r_v<Return_, Function_, ArgTypes_...>; }

	template <typename Function_, typename... ArgTypes_>
	inline constexpr bool is_nothrow_invocable(Type<Function_>, Type<ArgTypes_>...) 
	{ return std::is_nothrow_invocable_v<Function_, ArgTypes_...>; }

	template <typename Return_, typename Function_, typename... ArgTypes_>
	inline constexpr bool is_nothrow_invocable_r(Type<Return_>, Type<Function_>, Type<ArgTypes_>...)
	{ return std::is_nothrow_invocable_r_v<Return_, Function_, ArgTypes_...>; }

	//		**	CONST-VOLATILITY SPECIFIES **

	template <typename Type_>
	inline constexpr auto remove_cv(Type<Type_>) { return type_c<std::remove_cv_t<Type_>>; }

	template <typename Type_>
	inline constexpr auto remove_const(Type<Type_>) { return type_c<std::remove_const_t<Type_>>; }

	template <typename Type_>
	inline constexpr auto remove_volatile(Type<Type_>) { return type_c<std::remove_volatile_t<Type_>>; }

	template <typename Type_>
	inline constexpr auto add_cv(Type<Type_>) { return type_c<std::add_cv_t<Type_>>; }

	template <typename Type_>
	inline constexpr auto add_const(Type<Type_>) { return type_c<std::add_const_t<Type_>>; }

	template <typename Type_>
	inline constexpr auto add_volatile(Type<Type_>) { return type_c<std::add_volatile_t<Type_>>; }

	//		**	REFERENCES **

	template <typename Type_>
	inline constexpr auto remove_reference(Type<Type_>) { return type_c<std::remove_reference_t<Type_>>; }

	template <typename Type_>
	inline constexpr auto add_lvalue_reference(Type<Type_>) { return type_c<std::add_lvalue_reference_t<Type_>>; }

	template <typename Type_>
	inline constexpr auto add_rvalue_reference(Type<Type_>) { return type_c<std::add_rvalue_reference_t<Type_>>; }

	//		**	POINTERS **

	template <typename Type_>
	inline constexpr auto remove_pointer(Type<Type_>) { return type_c<std::remove_pointer_t<Type_>>; }

	template <typename Type_>
	inline constexpr auto add_pointer(Type<Type_>) { return type_c<std::add_pointer_t<Type_>>; }

	//		**	SIGNED MODIFIERS **

	template <typename Type_>
	inline constexpr auto make_signed(Type<Type_>) { return type_c<std::make_signed_t<Type_>>; }

	template <typename Type_>
	inline constexpr auto make_unsigned(Type<Type_>) { return type_c<std::make_unsigned_t<Type_>>; }

	//		**	ARRAYS **

	template <typename Type_>
	inline constexpr auto remove_extent(Type<Type_>) { return type_c<std::remove_extent_t<Type_>>; }

	template <typename Type_>
	inline constexpr auto remove_all_extents(Type<Type_>) { return type_c<std::remove_all_extents_t<Type_>>; }

	//		**	MICELLANEOUS TRANSFORMATIONS **

	template <std::size_t len_, std::size_t align_>
	inline constexpr auto aligned_storage(std::integral_constant<std::size_t, len_>,
										  std::integral_constant<std::size_t, align_>) 
	{ return type_c<std::aligned_storage_t<len_, align_>>; }

	template <std::size_t len_, typename... Types_>
	inline constexpr auto aligned_union(std::integral_constant<std::size_t, len_>,
										Type<Types_>...)
	{ return type_c<std::aligned_union_t<len_, Types_...>>; }

	template <typename Type_>
	inline constexpr auto decay(Type<Type_>) { return type_c<std::decay_t<Type_>>;}

	template <typename... Types_>
	inline constexpr auto common_type(Type<Types_>...) { return type_c<std::common_type_t<Types_...>>; }

	template <typename Type_>
	inline constexpr auto underlying_type(Type<Type_>) { return type_c<std::underlying_type_t<Type_>>; }

	//		**	OPERATIONS ON TRAITS **

	template <typename... Types_>
	inline constexpr bool conjunction(Type<Types_>...) { return std::conjunction_v<Types_...>; }

	template <typename... Types_>
	inline constexpr bool disjunction(Type<Types_>...) { return std::disjunction_v<Types_...>; }

	template <typename Type_>
	inline constexpr bool negation(Type<Type_>) { return std::negation_v<Type_>; }
}
#endif	//	_SIGMA_API_CONTAINER_TRAITS_HPP_