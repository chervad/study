#pragma once

template <typename T>
class TT {
public:
	TT(T a);
	const T& getA() const;
private:
	T _a;
};
