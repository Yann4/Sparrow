#pragma once
#include <functional>
#include <vector>

namespace Sparrow
{
	template< class Result, class... Args>
	class Callback
	{
	public:
		template<class... Args>
		void Invoke(Args... args)
		{
			for (auto function : m_Callbacks)
			{
				function(args);
			}
		}

		template< class Result, class... Args>
		void Invoke(Result result, Args... args)
		{
			for (auto function : m_Callbacks)
			{
				function(result, args...);
			}
		}

		Callback& operator+=(const std::function<Result(Args...)>& rhs)
		{
			m_Callbacks.push_back(rhs);
			return *this;
		}

		Callback& operator-=(const std::function<Result(Args...)>& rhs)
		{
			m_Callbacks.erase(std::find(m_Callbacks.begin(), m_Callbacks.end(), rhs));
			return *this;
		}

	private:
		std::vector<std::function<Result(Args...)>> m_Callbacks;
	};
}