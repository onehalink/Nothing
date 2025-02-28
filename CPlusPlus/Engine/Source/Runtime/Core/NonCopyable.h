#pragma once



namespace Engine
{
	// Disable class's move/copy constructors and move/copy assignment operators
	struct NonCopyable
	{
		NonCopyable(NonCopyable&&) = delete;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(NonCopyable&&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
	protected:
		NonCopyable() {}
	};
}