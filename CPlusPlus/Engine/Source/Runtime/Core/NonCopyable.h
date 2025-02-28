#pragma once



namespace Engine
{
	// Disable class's copy/move constructors and copy/move assignment operators
	struct NonCopyable
	{
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable(NonCopyable&&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
		NonCopyable& operator=(NonCopyable&&) = delete;
	protected:
		NonCopyable() {}
	};
}