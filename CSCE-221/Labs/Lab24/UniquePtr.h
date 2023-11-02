#ifndef UNIQUEPTR_H
#define UNIQUEPTR_H

template <typename T> struct UniquePtr
{
	T* holder;
	UniquePtr();
	UniquePtr(T val);
	~UniquePtr();
	UniquePtr(const UniquePtr& lhs);
	UniquePtr& operator=(const UniquePtr& lhs);
	const T& operator*();
	const UniquePtr& operator->();
};

using namespace std;

template <typename T> UniquePtr<T>::UniquePtr() {}

template <typename T> UniquePtr<T>::UniquePtr(T val)
{
	holder = new T(val);
}

template <typename T> UniquePtr<T>::~UniquePtr()
{
	delete holder;
}

template <typename T> UniquePtr<T>::UniquePtr(const UniquePtr& lhs)
{
	holder=*lhs;
}

template <typename T> UniquePtr<T>& UniquePtr<T>::operator=(const UniquePtr& lhs)
{
	holder=*lhs;
	return *this;

}
template <typename T> const T& UniquePtr<T>::operator*()
{
	return *holder;
}

template <typename T> const UniquePtr<T>& UniquePtr<T>::operator->()
{
	return *this;
}
#endif