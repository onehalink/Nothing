#include "Directory.h"



namespace Engine
{
	Void Directory::Copy(const U8String& from, const U8String& to)
	{
		if ( !Exist(to) )
			Create(to);

		for ( auto& entry : EnumerateEntries(from) )
		{
			U8String combinedFrom	= Path::Combine(from, entry);
			U8String combinedTo		= Path::Combine(to, entry);

			if ( File::Exist(combinedFrom) )
				File::Copy(combinedFrom, combinedTo);

			if ( Exist(combinedFrom) )
				Copy(combinedFrom, combinedTo);
		}
	}

	Void Directory::Move(const U8String& from, const U8String& to)
	{
		if ( !Exist(to) )
			Create(to);

		for ( auto& entry : EnumerateEntries(from) )
		{
			U8String combinedFrom	= Path::Combine(from, entry);
			U8String combinedTo		= Path::Combine(to, entry);

			if ( File::Exist(combinedFrom) )
				File::Move(combinedFrom, combinedTo);

			if ( Exist(combinedFrom) )
				Move(combinedFrom, combinedTo);
		}

		Delete(from);
	}
}