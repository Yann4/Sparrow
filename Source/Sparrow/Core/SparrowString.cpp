#include "pch.h"

namespace Sparrow
{
	const String String::Empty = String("");

	String::String() : 
		m_Data() 
	{}

	//Copies contents of string into internal representation
	String::String(const char* str) :
		m_Data(str) 
	{}

	//Copies contents of string into internal representation
	String::String(const char* str, uint32_t length) : 
		m_Data(str, length) 
	{}

	String::String(const String& other) :
		m_Data(other.m_Data)
	{}

	String::String(String&& other) noexcept :
		m_Data(std::move(other.m_Data))
	{}

	String::~String()
	{}

	const char* String::c_str() const
	{
		return m_Data.c_str();
	}

	uint32_t String::Length() const 
	{ 
		return static_cast<uint32_t>(m_Data.length()); 
	}

	uint32_t String::Compare(const String& other) const 
	{
		return m_Data.compare(other.m_Data);
	}

	bool String::Contains(const String& other) const
	{
		return m_Data.find(other.m_Data) != m_Data.npos;
	}

	String& String::operator+=(const String& rhs)
	{
		m_Data += rhs.c_str();
		return *this;
	}

	String& String::operator=(const String& rhs)
	{
		return *this = String(rhs);
	}

	String& String::operator=(String&& rhs) noexcept
	{
		std::swap(m_Data, rhs.m_Data);
		return *this;
	}

	inline bool operator==(const String& lhs, const String& rhs) { return lhs.Compare(rhs) == 0; }
	inline bool operator!=(const String& lhs, const String& rhs) { return !operator==(lhs, rhs); }
	inline bool operator<(const String& lhs, const String& rhs) { return lhs.Compare(rhs) < 0; }
	inline bool operator>(const String& lhs, const String& rhs) { return operator<(rhs, lhs); }
	inline bool operator<=(const String& lhs, const String& rhs) { return !operator>(rhs, lhs); }
	inline bool operator>=(const String& lhs, const String& rhs) { return !operator<(rhs, lhs); }

	String operator+(String lhs, const String& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	std::ostream& operator<<(std::ostream& os, const String& obj)
	{
		os << obj.Length() << " ";
		os << obj.c_str();
		return os;
	}

	std::istream& operator>>(std::istream& is, String& obj)
	{
		uint32_t length;
		is >> length;

		char* str = new char[length];
		is.seekg(1, std::ios::cur); //Consume space
		is.read(str, length);

		obj = String(str, length);

		delete[] str;

		return is;
	}
}