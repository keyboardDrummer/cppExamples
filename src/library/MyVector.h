#pragma once
#include <algorithm> 

template<typename T>
class MyVector
{
	typedef T          value_type;
	typedef T         *pointer;
	typedef const T   *const_pointer;
	typedef T         &reference;
	typedef const T   &const_reference;
	typedef size_t     size_type;
	typedef ptrdiff_t  difference_type;

	typedef T* iterator;
	typedef const T* const_iterator;

private:
	T* elements = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void checkRange(size_t index) const {
		if (size <= index || index < 0)
			throw out_of_range("out of range");
	}

public:
	
	MyVector<T>() {

	}

	MyVector<T>(const MyVector<T>& other)
	{
		size = other.size;
		capacity = size;
		elements = static_cast<pointer>(malloc(capacity*t_size)); //I'm using malloc/free so that I have total control over when destructors get called.
		std::copy(other.cbegin(), other.cend(), elements);
	}

	~MyVector<T>()
	{
		for (auto& t : *this)
			t.~T();
		free(elements);
	}


	MyVector<T>(MyVector<T>&& other)
		: MyVector<T>()
	{
		swap(*this, other);
	}

	MyVector<T> operator=(MyVector<T> other)
	{
		swap(*this, other); //using the copy and swap idiom.
		return *this;
	}

	friend void swap(MyVector<T> other)
	{
		using std::swap;

		swap(this.size, other.size);
		swap(this.elements, other.elements);
		swap(this.capacity, other.capacity);
	}

	T& at(size_t index) const {
		checkRange(index);
		return elements[index];
	}

	iterator begin(){
		return elements;
	}
	iterator end() {
		return elements + size;
	}

	const_iterator cend() {
		return end();
	}

	const_iterator cbegin() const {
		return elements;
	}

	const_iterator cend() const {
		return elements + size;
	}

	void clear() {
		size = 0;
	}

	reference operator[] (size_type index) {
		checkRange(index);
		return elements[index];
	}

	iterator erase(const_iterator position) {
		size_t right = end() - position;
		position->~T(); //destruct the value to be erased.
		memcpy(const_cast<iterator>(position), position + 1, right * t_size); //shift the right neighbors one position to the left.
		--size;
		return const_cast<iterator>(position);
	}

	size_t t_size = sizeof(T);
	iterator insert(const_iterator position, value_type&& val) {
		auto itemsBeforePosition = position - begin();
		T* newElements;
		if (capacity == size)
		{
			capacity = std::max(static_cast<size_t>(1), capacity * 2);
			newElements = static_cast<pointer>(malloc(capacity*t_size));
			memcpy(newElements, cbegin(), itemsBeforePosition * t_size); //copy the old left to the new left.
		}
		else
		{
			newElements = elements;
		}
		T* newPosition = newElements + itemsBeforePosition;
		auto itemsAfterPosition = cend() - position;
		memcpy(newPosition + 1, position, itemsAfterPosition * t_size); //copy the old right to the new right.
		new (newPosition)value_type(std::move(val)); //move the insert value into place using the move constructor at the right position.
		
		if (newElements != elements)
		{
			free(elements); //don't call any destructors cause we're not losing ownership.
			elements = newElements;
		}
		++size;
		return newPosition;
	}

	void push_back(value_type val) {
		insert(cend(), std::move(val));
	}
};

