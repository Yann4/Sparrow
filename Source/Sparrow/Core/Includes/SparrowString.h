#pragma once

#include <string>
#include <ostream>
#include <istream>

namespace Sparrow
{
	class String
	{
	public:
		String();
		String(const String& other);
		String(String&& other) noexcept;

		//Copies contents of string into internal representation
		String(const char* str);

		//Copies contents of string into internal representation
		String(const char* str, uint32_t length);

		~String();

		const char* c_str() const;
		uint32_t Length() const;
		
		uint32_t Compare(const String& other) const;
		bool Contains(const String& other) const;
		bool IsEmpty() const { return Compare(Empty) == 0; }

		String& operator+=(const String& rhs);
		String& operator=(const String& rhs);
		String& operator=(String&& rhs) noexcept;

		friend std::ostream& operator<<(std::ostream& os, const String& rhs);
		friend std::istream& operator>>(std::istream& os, String& rhs);

		static const String Empty;
	private:
		std::string m_Data;
	};

	inline bool operator==(const String& lhs, const String& rhs);
	inline bool operator!=(const String& lhs, const String& rhs);
	inline bool operator<(const String& lhs, const String& rhs);
	inline bool operator>(const String& lhs, const String& rhs);
	inline bool operator<=(const String& lhs, const String& rhs);
	inline bool operator>=(const String& lhs, const String& rhs);

	String operator+(String lhs, const String& rhs);

	std::ostream& operator<<(std::ostream& os, const String& obj);
	std::istream& operator>>(std::istream& is, String& obj);
}