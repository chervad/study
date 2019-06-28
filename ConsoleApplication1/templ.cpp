#include "templ.h"


template<typename T>
TT<T>::TT(T a) 
	:_a(a)
{}
/**
* tst_02 
*/
template<typename T>
const T& TT<T>::getA() const {
	return _a;
}