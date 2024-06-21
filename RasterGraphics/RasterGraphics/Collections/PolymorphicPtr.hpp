#pragma once
#include <utility>

template<typename T>
class PolymorphicPtr {
private:
	T* ptr = nullptr;
public:
	PolymorphicPtr() = default;
	PolymorphicPtr(T* ptr);
	PolymorphicPtr(const PolymorphicPtr<T>& other);
	PolymorphicPtr(PolymorphicPtr<T>&& other) noexcept;
	PolymorphicPtr<T>& operator=(const PolymorphicPtr<T>& other);
	PolymorphicPtr<T>& operator=(PolymorphicPtr<T>&& other) noexcept;
	~PolymorphicPtr();

	T* operator->();
	const T* operator->() const;
	T& operator*();
	const T& operator*() const;

	T* get();
	const T* get() const;
	void reset(T* ptr);
	T* release();

private:
	void free();
	void copyFrom(const PolymorphicPtr& other);
	void moveFrom(PolymorphicPtr&& other);
};


template<typename T>
PolymorphicPtr<T>::PolymorphicPtr(T* ptr) : ptr(ptr)
{ }

template<typename T>
PolymorphicPtr<T>::PolymorphicPtr(const PolymorphicPtr<T>& other) {
	copyFrom(other);
}

template<typename T>
PolymorphicPtr<T>::PolymorphicPtr(PolymorphicPtr<T>&& other) noexcept {
	moveFrom(std::move(other));
}

template<typename T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(const PolymorphicPtr<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(PolymorphicPtr<T>&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
PolymorphicPtr<T>::~PolymorphicPtr() {
	free();
}

template<typename T>
T* PolymorphicPtr<T>::operator->() {
	return ptr;
}

template<typename T>
const T* PolymorphicPtr<T>::operator->() const {
	return ptr;
}

template<typename T>
T& PolymorphicPtr<T>::operator*() {
	return *ptr;
}

template<typename T>
const T& PolymorphicPtr<T>::operator*() const {
	return *ptr;
}

template<typename T>
T* PolymorphicPtr<T>::get() {
	return ptr;
}

template<typename T>
const T* PolymorphicPtr<T>::get() const {
	return ptr;
}

template<typename T>
void PolymorphicPtr<T>::reset(T* ptr) {
	free();
	this->ptr = ptr;
}

template<typename T>
T* PolymorphicPtr<T>::release() {
	T* temp = ptr;
	ptr = nullptr;
	return temp;
}

template<typename T>
void PolymorphicPtr<T>::free() {
	delete ptr;
}

template<typename T>
void PolymorphicPtr<T>::copyFrom(const PolymorphicPtr& other) {
	ptr = other.ptr->clone();
}

template<typename T>
void PolymorphicPtr<T>::moveFrom(PolymorphicPtr&& other) {
	ptr = other.ptr;
	other.ptr = nullptr;
}