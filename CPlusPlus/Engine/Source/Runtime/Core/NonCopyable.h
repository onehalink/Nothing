#pragma once



// Disable class's copy/move constructors and copy/move assignment operators
#define NONCOPYABLE(Type)					\
		Type(Type&&)			= delete;	\
		Type(const Type&)		= delete;	\
Type&	operator=(Type&&)		= delete;	\
Type&	operator=(const Type&)	= delete;