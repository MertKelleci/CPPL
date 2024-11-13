#pragma once
#include <iostream>

template<typename Vector>
class VectorIterator
{
public:
	using ValueType = typename Vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	VectorIterator(PointerType ptr) : m_Ptr(ptr) {}

	VectorIterator& operator++()
	{
		m_Ptr++;
		return *this;
	}

	VectorIterator operator++(int)
	{
		VectorIterator iterator = *this;
		++(*this);
		return iterator;
	}

	VectorIterator& operator--()
	{
		m_Ptr--;
		return *this;
	}

	VectorIterator operator--(int)
	{
		VectorIterator iterator = *this;
		--(*this);
		return iterator;
	}

	ReferenceType operator[](int index) { return *(m_Ptr + index); }

	PointerType operator->() { return m_Ptr; }

	ReferenceType operator*() { return *m_Ptr; }

	bool operator==(const VectorIterator& other) const { return m_Ptr == other.m_Ptr; }

	bool operator!=(const VectorIterator& other) const { return m_Ptr != other.m_Ptr; }

private:
	PointerType m_Ptr;
};

template <typename T>
class Vector
{
public:
	using ValueType = T;
	using Iterator = VectorIterator<Vector<T>>;
	Vector() { ReAlloc(2); }

	size_t Size() const { return m_Size; }

	void PushBack(const T& value)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity / 2);

		m_Data[m_Size] = value;
		m_Size++;
	}

	const T& operator[](size_t index) const
	{
		return m_Data[index];
	}

	Iterator begin()
	{
		return Iterator(m_Data);
	}

	Iterator end()
	{
		return Iterator(m_Data + m_Size);
	}

	T& operator[](size_t index)
	{
		return m_Data[index];
	}

	template<typename... Args>
	T& EmplaceBack(Args&&... args)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity / 2);

		// This for creating the object on stack in this method and then move it to the array.
		// m_Data[m_Size] = T(std::forward<Args>(args)...);
		// The following code helps us directly create the object where we need it to be.
		new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
		return m_Data[m_Size++];
	}
	~Vector() { delete[] m_Data; }
	void PopBack()
	{
		if (m_Size > 0)
		{
			m_Size--;
			m_Data[m_Size].~T();
		}
	}

	void Clear()
	{
		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();

		m_Size = 0;
	}
private:
	void ReAlloc(size_t newCapacity)
	{
		T* newBlock = new T[newCapacity];

		if (newCapacity < m_Size)
			m_Size = newCapacity;

		for (size_t i = 0; i < m_Size; i++)
			newBlock[i] = std::move(m_Data[i]);

		delete[] m_Data;
		m_Data = newBlock;
		m_Capacity = newCapacity;
	}

	T* m_Data = nullptr;

	size_t m_Size = 0;
	size_t m_Capacity = 0;
};