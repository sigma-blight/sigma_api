#include <sigma/meta/container/vector.hpp>
#include <sigma/meta/algorithm/transform.hpp>

using namespace sigma::meta;

void tvector(void)
{
	TVector<int, char, int> v;

	auto nv1 = v.push_back(type_c<int *>);
	auto nv2 = nv1.pop_front();

	static_assert(nv1 == TVector<int, char, int, int *>{});
	static_assert(nv2 == TVector<char, int, int *>{});

	auto nv3 = apply(nv2, [](auto type) {
		if constexpr (is_pointer(type))
			return add_lvalue_reference(remove_pointer(type));
		else
			return type;
	});

	static_assert(nv3 == TVector<char, int, int &>{});

	struct UDT {};
	TVector<int *, void, char &&, UDT, char> v2;

	auto nv4 = filter(v2, [](auto type) {
		return is_pointer(type) || is_reference(type);
	});

	static_assert(nv4 == TVector<void, UDT, char>{});
}

int main(void)
{
	tvector();
}