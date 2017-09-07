#include <gtest/gtest.h>
#include <sigma/math/vectorspace/basic_vectorspace.hpp>

#define TAG basic_vectorspace

template <std::size_t n_, typename Field_>
void generate_default(std::array<Field_, n_> & element)
{
	int n = 0;
	std::generate(element.begin(), element.end(), [&n] {return n++; });
}

template <std::size_t n_, typename Field_>
void test_generate_default(const std::array<Field_, n_> & element)
{
	for (std::size_t i = 0; i != element.size(); ++i)
		ASSERT_EQ(i, element[i]);
}

TEST(TAG, no_fail_with_0_size_construction)
{
	sigma::math::BasicVectorSpace<0, int> vs{};
}

TEST(TAG, arithmetic_types_meet_axioms)
{
	sigma::math::BasicVectorSpace<0, bool>{};
	sigma::math::BasicVectorSpace<0, std::uint8_t>{};
	sigma::math::BasicVectorSpace<0, std::uint16_t>{};
	sigma::math::BasicVectorSpace<0, std::uint32_t>{};
	sigma::math::BasicVectorSpace<0, std::uint64_t>{};
	sigma::math::BasicVectorSpace<0, std::int8_t>{};
	sigma::math::BasicVectorSpace<0, std::int16_t>{};
	sigma::math::BasicVectorSpace<0, std::int32_t>{};
	sigma::math::BasicVectorSpace<0, std::int64_t>{};
	sigma::math::BasicVectorSpace<0, char>{};
	sigma::math::BasicVectorSpace<0, unsigned char>{};
	sigma::math::BasicVectorSpace<0, char16_t>{};
	sigma::math::BasicVectorSpace<0, char32_t>{};
	sigma::math::BasicVectorSpace<0, wchar_t>{};
	sigma::math::BasicVectorSpace<0, short>{};
	sigma::math::BasicVectorSpace<0, int>{};
	sigma::math::BasicVectorSpace<0, long>{};
	sigma::math::BasicVectorSpace<0, long long>{};
	sigma::math::BasicVectorSpace<0, unsigned short>{};
	sigma::math::BasicVectorSpace<0, unsigned>{};
	sigma::math::BasicVectorSpace<0, unsigned long>{};
	sigma::math::BasicVectorSpace<0, unsigned long long>{};
	sigma::math::BasicVectorSpace<0, float>{};
	sigma::math::BasicVectorSpace<0, double>{};
	sigma::math::BasicVectorSpace<0, long double>{};
}

TEST(TAG, valid_sizing)
{
	sigma::math::BasicVectorSpace<0, int> v0;
	sigma::math::BasicVectorSpace<1, int> v1;
	sigma::math::BasicVectorSpace<2, int> v2;
	sigma::math::BasicVectorSpace<10, int> v10;
	sigma::math::BasicVectorSpace<100, int> v100;
	sigma::math::BasicVectorSpace<(1 << 8), int> v1_8;
	sigma::math::BasicVectorSpace<(1 << 16), int> v1_16;

	static_assert(v0.size() == 0);
	static_assert(v1.size() == 1);
	static_assert(v2.size() == 2);
	static_assert(v10.size() == 10);
	static_assert(v100.size() == 100);
	static_assert(v1_8.size() == 1 << 8);
	static_assert(v1_16.size() == 1 << 16);

	static_assert(sigma::math::BasicVectorSpace<0, int>::size() == 0);
	static_assert(sigma::math::BasicVectorSpace<1, int>::size() == 1);
	static_assert(sigma::math::BasicVectorSpace<2, int>::size() == 2);
	static_assert(sigma::math::BasicVectorSpace<10, int>::size() == 10);
	static_assert(sigma::math::BasicVectorSpace<100, int>::size() == 100);
	static_assert(sigma::math::BasicVectorSpace<(1 << 8), int>::size() == 1 << 8);
	static_assert(sigma::math::BasicVectorSpace<(1 << 16), int>::size() == 1 << 16);
}

TEST(TAG, default_0_construction_with_brackets)
{
	sigma::math::BasicVectorSpace<1, int> vs{};

	for (auto && e : vs.element())
		ASSERT_EQ(e, 0);	

	sigma::math::BasicVectorSpace<(1 << 16), double> big_fp_vs{};

	for (auto && e : big_fp_vs.element())
		ASSERT_EQ(e, 0.0);
}

TEST(TAG, element_access)
{
	sigma::math::BasicVectorSpace<10, int> vs;
	generate_default(vs.element());
	test_generate_default(vs.element());	
}

TEST(TAG, copy_construction)
{
	sigma::math::BasicVectorSpace<10, double> vs;
	generate_default(vs.element());

	sigma::math::BasicVectorSpace<10, double> cpy1 = vs;
	sigma::math::BasicVectorSpace<10, double> cpy2(vs);
	sigma::math::BasicVectorSpace<10, double> cpy3{ vs };

	test_generate_default(cpy1.element());
	test_generate_default(cpy2.element());
	test_generate_default(cpy3.element());
}

TEST(TAG, move_construction)
{
	sigma::math::BasicVectorSpace<100, short> vs;

	generate_default(vs.element());
	sigma::math::BasicVectorSpace<100, short> mv1 = std::move(vs);
	test_generate_default(mv1.element());

	generate_default(vs.element());
	sigma::math::BasicVectorSpace<100, short> mv2(std::move(vs));
	test_generate_default(mv2.element());

	generate_default(vs.element());
	sigma::math::BasicVectorSpace<100, short> mv3{ std::move(vs) };
	test_generate_default(mv3.element());
}

TEST(TAG, variadic_constructor)
{
	sigma::math::BasicVectorSpace<1, int> v1{ 12 };
	ASSERT_EQ(v1.element()[0], 12);

	sigma::math::BasicVectorSpace<1, double> v2{ 12 };
	ASSERT_EQ(v2.element()[0], 12);

	sigma::math::BasicVectorSpace<1, int> v3{ 12.0 };
	ASSERT_EQ(v3.element()[0], 12);

	sigma::math::BasicVectorSpace<5, double> v4{ 12, 5, 3, 2, -7.2 };
	ASSERT_EQ(v4.element()[0], 12);
	ASSERT_EQ(v4.element()[1], 5);
	ASSERT_EQ(v4.element()[2], 3);
	ASSERT_EQ(v4.element()[3], 2);
	ASSERT_EQ(v4.element()[4], -7.2);
}

TEST(TAG, element_constructor)
{
	sigma::math::BasicVectorSpace<100, int> v;
	generate_default(v.element());
	sigma::math::BasicVectorSpace<100, int> copy = v.element();
	test_generate_default(v.element());
}

TEST(TAG, assignment)
{
	sigma::math::BasicVectorSpace<5, int> original, copy, move;
	generate_default(original.element());
	
	copy = original;
	test_generate_default(copy.element());

	move = std::move(original);
	test_generate_default(move.element());

	original = { 5, -1, 3, 4, -8 };
	ASSERT_EQ(original.element()[0], 5);
	ASSERT_EQ(original.element()[1], -1);
	ASSERT_EQ(original.element()[2], 3);
	ASSERT_EQ(original.element()[3], 4);
	ASSERT_EQ(original.element()[4], -8);
}