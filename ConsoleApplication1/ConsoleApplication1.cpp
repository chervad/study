#include <iostream>
#include <string>
#include "templ.h"

class A {
public:
	void f0() {
		std::cout << "A.f0()" << std::endl;
	}

	virtual void f1() {
		std::cout << "A.f1()" << std::endl;
	}

	void f2() {
		std::cout << "A.f2()" << std::endl;
	}
};

class B : public A {
public:
	virtual void f1() {
		std::cout << "B.f1() overload virtual A.f1()" << std::endl;
	}

	virtual void f2() {
		std::cout << "B.f2() overload A.f2()" << std::endl;
	}

	void f3() {
		std::cout << "B.f3()" << std::endl;
	}
};

class C : public B {
public:
	virtual void f1() {
		std::cout << "C.f1() overload virtual B.f1()" << std::endl;
	}

	virtual void f2() {
		std::cout << "C.f2() overload virtual B.f2()" << std::endl;
	}
};

class zz {
public:
	void copy(const zz &_zz) {
		this->a = _zz.a;
	}
private:
	int a;
};

int main()
{
	A a;
	A &a_link = a;
	A *a_pointer = &a;

	B b;
	B &b_link = b;
	B *b_pointer = &b;

	C c;

	A &c_link = b;
	A *c_pointer = &b;

	A *d_pointer = &c;
	B *e_pointer = &c;

	std::cout << "Test A a:" << std::endl;
	a.f0();
	a.f1();
	a.f2();

	std::cout << "Test A &a_link = a:" << std::endl;
	a_link.f0();
	a_link.f1();
	a_link.f2();

	std::cout << "Test A *a_pointer = &a:" << std::endl;
	a_pointer->f0();
	a_pointer->f1();
	a_pointer->f2();

	std::cout << "Test B b:" << std::endl;
	b.f0();
	b.f1();
	b.f2();
	b.f3();

	std::cout << "Test B &b_link = b:" << std::endl;
	b_link.f0();
	b_link.f1();
	b_link.f2();
	b_link.f3();

	std::cout << "Test B *b_pointer = &b:" << std::endl;
	b_pointer->f0();
	b_pointer->f1();
	b_pointer->f2();
	b_pointer->f3();

	std::cout << "Test C c:" << std::endl;
	c.f0();
	c.f1();
	c.f2();
	c.f3();

	std::cout << "Test A &c_link = b:" << std::endl;
	c_link.f0();
	c_link.f1();
	c_link.f2();

	std::cout << "Test A *c_pointer = &b:" << std::endl;
	c_pointer->f0();
	c_pointer->f1();
	c_pointer->f2();

	std::cout << "Test A *d_pointer = &c:" << std::endl;
	d_pointer->f0();
	d_pointer->f1();
	d_pointer->f2();

	std::cout << "Test B *e_pointer = &c:" << std::endl;
	e_pointer->f0();
	e_pointer->f1();
	e_pointer->f2();
	e_pointer->f3();

	TT<int> intT(1234);
	std::cout << intT.getA() << std::endl;

	system("PAUSE");

	return 0;
}

