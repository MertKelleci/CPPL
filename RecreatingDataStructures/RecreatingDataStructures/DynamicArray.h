#pragma once
#include <iostream>

template <typename T>
class Vector
{
public:
	Vector() { ReAlloc(2); }

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

	T& operator[](size_t index)
	{
		return m_Data[index];
	}

	template<typename... Args>
	T& EmplaceBack(Args&&... args)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity / 2);

		m_Data[m_Size] = T(std::forward<Args>(args)...);
		return m_Data[m_Size++];
	}
	~Vector() { delete[] m_Data; }

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