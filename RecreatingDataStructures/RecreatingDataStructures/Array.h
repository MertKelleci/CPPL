#pragma once

template<typename T, size_t S>
class Array
{
public:
	//This 'constexpr' keyword specifies that this line of code can be evaluated at compiletime. Allowing us to use it in various places, creating a stack allocated array with this size is one example.
	constexpr size_t Size() const { return S; }

	T& operator[](size_t index) { return m_Data[index]; }
	const T& operator[](size_t index) const { return m_Data[index]; }

	T* Data() { return m_Data; }
	const T* Data() const { return m_Data; }
private:
	T m_Data[S];
};