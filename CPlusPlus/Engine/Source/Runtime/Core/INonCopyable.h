#pragma once



namespace Engine
{
	// Disable class's copy/move constructors and copy/move assignment operators
	struct INonCopyable
	{
		INonCopyable(const INonCopyable&) = delete;
		INonCopyable(INonCopyable&&) = delete;
		INonCopyable& operator=(const INonCopyable&) = delete;
		INonCopyable& operator=(INonCopyable&&) = delete;
	protected:
		INonCopyable() {}
	};
}