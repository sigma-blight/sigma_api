#ifndef		_SIGMA_API_META_TESTING_CONTAINER_TEST_HPP_
#define		_SIGMA_API_META_TESTING_CONTAINER_TEST_HPP_

#include <type_traits>
#include <limits>

#include <sigma/meta/container/traits.hpp>
#include <sigma/meta/container/vector.hpp>

using namespace sigma::meta;

// trivial sanity tests
void type_test(void)
{
	//	Test no abstract types break template paramater

	using t1 = typename Type<int>::type_t;
	using t2 = typename Type<int *>::type_t;
	using t3 = typename Type<int *******>::type_t;
	using t4 = typename Type<const int * const (* const &) []>::type_t;

	static_assert(std::is_same_v<t1, int>);
	static_assert(std::is_same_v<t2, int *>);
	static_assert(std::is_same_v<t3, int *******>);
	static_assert(std::is_same_v<t4, const int * const (* const &) []>);

	//	Test constant inline variable type_c

	auto c1 = type_c<int[]>;
	auto c2 = type_c<void(int *, const void * (*&)[5])>;

	static_assert(std::is_same_v<decltype(c1), Type<int[]>>);
	static_assert(std::is_same_v<decltype(c2), Type<void(int *, const void * (*&)[5])>>);

	//	Test equality operator

	auto a = type_c<int>;
	auto b = type_c<const int>;
	auto c = type_c<void * const>;
	auto d = type_c<char (&) []>;

	static_assert(a != b);
	static_assert(a != c);
	static_assert(a != d);
	static_assert(b != c);
	static_assert(b != d);
	static_assert(c != d);

	static_assert(a == type_c<int>);
	static_assert(b == type_c<const int>);
	static_assert(c == type_c<void * const>);
	static_assert(d == type_c<char(&)[]>);
}

// constexpr UDL for integrals tests
void literal_operators_test(void)
{
	// Test <int> literal operator

	auto i1 = 1_i;
	auto i2 = 100_i;
	auto i3 = 534220831_i;

	static_assert(i1 == 1);
	static_assert(i2 == 100);
	static_assert(i3 == 534220831);

	// Test <std::size_t> literal operator

	auto s1 = 1_u;
	auto s2 = 33801_u;
	auto s3 = 10000000000_u; // 10 billion > int max

	static_assert(s1 == 1);
	static_assert(s2 == 33801);
	static_assert(s3 == 10000000000);
}

// TVector tests
void type_vector_test(void)
{
	//	Test size
	{
		TVector<> v1;
		TVector<int> v2;
		TVector<int, int, int> v3;
		TVector<int, char, int *, const void *> v4;

		static_assert(v1.size() == 0);
		static_assert(v2.size() == 1);
		static_assert(v3.size() == 3);
		static_assert(v4.size() == 4);
	}

	//	Test indexing - get methods
	{
		TVector<int> v1;
		TVector<int *, void> v2;
		TVector<int, int, char, int[], void *, char &&, short> v3;

		static_assert(v1.get<0>() == type_c<int>);
		static_assert(v2.get<0>() == type_c<int *>);
		static_assert(v2.get<1>() == type_c<void>);
		static_assert(v3.get<0>() == type_c<int>);
		static_assert(v3.get<1>() == type_c<int>);
		static_assert(v3.get<2>() == type_c<char>);
		static_assert(v3.get<3>() == type_c<int[]>);
		static_assert(v3.get<4>() == type_c<void *>);
		static_assert(v3.get<5>() == type_c<char &&>);
		static_assert(v3.get<6>() == type_c<short>);

		static_assert(v1.get<0>() == v1.get(0_u));
		static_assert(v1.get<0>() == v1[0_u]);
		static_assert(v2.get<1>() == v2.get(1_u));
		static_assert(v2.get<1>() == v2[1_u]);
		static_assert(v3.get<4>() == v3.get(4_u));
		static_assert(v3.get<4>() == v3[4_u]);

		static_assert(v1.front() == type_c<int>);
		static_assert(v1.back() == type_c<int>);
		static_assert(v2.front() == type_c<int *>);
		static_assert(v2.back() == type_c<void>);
		static_assert(v3.front() == type_c<int>);
		static_assert(v3.back() == type_c<short>);
	}

	//	Test pushing and popping
	{
		TVector<int> v1;
		TVector<void, int *> v2;
		TVector<> v3;

		{
			auto r1 = v1.push_back(type_c<int *>);
			auto r2 = v1.push_front(type_c<int *>);
			auto r3 = v1.pop_back();
			auto r4 = v1.pop_front();

			static_assert(r1 == TVector<int, int *>{});
			static_assert(r2 == TVector<int *, int>{});
			static_assert(r3 == TVector<>{});
			static_assert(r4 == TVector<>{});
		}
		
		{
			auto r1 = v2.push_back(type_c<int[]>);
			auto r2 = v2.push_front(type_c<char * const (&&)[]>);
			auto r3 = v2.pop_back();
			auto r4 = v2.pop_front();

			static_assert(r1 == TVector<void, int *, int[]>{});
			static_assert(r2 == TVector<char * const (&&)[], void, int *>{});
			static_assert(r3 == TVector<void>{});
			static_assert(r4 == TVector<int *>{});
		}

		{
			auto r1 = v3.push_back(type_c<int *>);
			auto r2 = v3.push_front(type_c<int * const>);
			auto r3 = v3.push_back(type_c<int>).push_back(type_c<const int>).push_front(type_c<int **>);

			static_assert(r1 == TVector<int *>{});
			static_assert(r2 == TVector<int * const>{});
			static_assert(r3 == TVector<int **, int, const int>{});
		}
	}
}

// VVector tests
void value_vector_test(void)
{
	//	Test size
	{
		VVector<> v1;
		VVector<1> v2;
		VVector<1, 5, '2', 3, 0> v3;

		static_assert(v1.size() == 0);
		static_assert(v2.size() == 1);
		static_assert(v3.size() == 5);
	}

	//	Test indexing - get methods
	{
		VVector<1> v1;
		VVector<0, 'a', 10> v2;
		VVector<0, 0, 0, 'a', 5, 7u> v3;

		static_assert(v1.get<0>() == 1);
		static_assert(v2.get<0>() == 0);
		static_assert(v2.get<1>() == 'a');
		static_assert(v2.get<2>() == 10);
		static_assert(v3.get<0>() == 0);
		static_assert(v3.get<1>() == 0);
		static_assert(v3.get<2>() == 0);
		static_assert(v3.get<3>() == 'a');
		static_assert(v3.get<4>() == 5);
		static_assert(v3.get<5>() == 7u);

		static_assert(v1.get<0>() == v1.get(0_u));
		static_assert(v1.get<0>() == v1[0_u]);
		static_assert(v2.get<1>() == v2.get(1_u));
		static_assert(v2.get<1>() == v2[1_u]);
		static_assert(v3.get<4>() == v3.get(4_u));
		static_assert(v3.get<4>() == v3[4_u]);

		static_assert(v1.front() == 1);
		static_assert(v1.back() == 1);
		static_assert(v2.front() == 0);
		static_assert(v2.back() == 10);
		static_assert(v3.front() == 0);
		static_assert(v3.back() == 7u);
	}

	//	Test pushing and popping
	{
		VVector<0> v1;
		VVector<10, -10> v2;
		VVector<> v3;

		{
			auto r1 = v1.push_back<1>();
			auto r2 = v1.push_front<-1>();
			auto r3 = v1.pop_back();
			auto r4 = v1.pop_front();

			static_assert(r1 == VVector<0, 1>{});
			static_assert(r2 == VVector<-1, 0>{});
			static_assert(r3 == VVector<>{});
			static_assert(r4 == VVector<>{});
		}

		{
			auto r1 = v2.push_back<'-'>();
			auto r2 = v2.push_front<'+'>();
			auto r3 = v2.pop_back();
			auto r4 = v2.pop_front();

			static_assert(r1 == VVector<10, -10, '-'>{});
			static_assert(r2 == VVector<'+', 10, -10>{});
			static_assert(r3 == VVector<10>{});
			static_assert(r4 == VVector<-10>{});
		}

		{
			auto r1 = v3.push_back<10>();
			auto r2 = v3.push_front<-10>();
			auto r3 = v3.push_back<1>().push_back<2>().push_front<0>();

			static_assert(r1 == VVector<10>{});
			static_assert(r2 == VVector<-10>{});
			static_assert(r3 == VVector<0, 1, 2>{});
		}
	}
}

void container_test_main(void)
{
	type_test();
	literal_operators_test();

	// assume that type_traits are functional
	//	as they are just a wrapper 
	//	around the std:: type_traits

	type_vector_test();
	value_vector_test();
}

#endif	//	_SIGMA_API_META_TESTING_CONTAINER_TEST_HPP_