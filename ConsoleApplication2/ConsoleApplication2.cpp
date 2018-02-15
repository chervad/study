#include <iosfwd>
#include <iostream>
#include <vector>

struct test {
	int i;
	char c;
	bool operator==(const test &rhs) const {
		return i == rhs.i && c == rhs.c;
	}
};

unsigned int fib(unsigned int n) {
	if (n == 0) return 0;
	if (n <= 2) return 1;
	return fib(n - 2) + fib(n - 1);
}

template <typename T>
class C0 {
public:
	C0(int f, T t) 
		: f0(f), t0(t)
	{}
private:
	int f0;
	T t0;
};

template <>
class C0<bool> {
public:
	C0(int f, bool b) 
		: f1(f), b1(b)
	{}
private:
	int f1;
	bool b1;
};

template <typename D, typename T>
class C1 : public C0<T> {
public:
	C1(int f, D d, T t)
		: C0(f, t), d1(d)
	{}
private:
	D d1;
};

template <typename T, template <typename E, typename Allocator = std::allocator<E>> class Container = std::vector >
class D {
public:
	D(T initv) 
		: _data(10)
	{
		_data.push_back(initv);
	}
private:
	Container<T> _data;
};

template <typename T, const T EMPTY>
class E {
public:
	E() : f(EMPTY)
	{}
private:
	T f;
};

int main()
{
	C0<char> c1(1, 'a');
	C0<bool> c2(1, true);
	C1<float, double> cc(10, 11.0, 123.45);

	D<int> d1(128);

	E<char, '0'> e;

	test t1{ 1025, 'A' };
	test t2{ 1025, 'A' };

	std::cout << memcmp(&t1, &t2, sizeof(test)) << std::endl << (t1 == t2) << std::endl;
	for (int a = 0; a <= 20; a++) {
		std::cout << "fib(" << a << ") = " << fib(a) << std::endl;
	}
	system("PAUSE");
    return 0;
}

