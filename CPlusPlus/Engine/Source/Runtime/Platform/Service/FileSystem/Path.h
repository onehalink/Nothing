#pragma once

#include "../../../Core.h"



namespace Engine
{
	class ENGINE_API Path
	{
	public:
		/**
		* @remark
		* File extension should be leading with a period(".")
		*/
		static U8String ChangeFileExtension(U8StringView path, U8StringView newFileExtension);
		template<typename ...StringViews>
		static U8String Combine(StringViews... paths);
		static U8StringView GetDirectoryName(U8StringView path);
		static U8StringView GetFileExtension(U8StringView path);
		static U8StringView GetFileName(U8StringView path);
		static U8StringView GetFileNameWithoutExtension(U8StringView path);
		// Return the absolute path for the specific path
		static U8String GetFullQualifiedPathName(U8StringView path);
		static Bool HasFileExtension(U8StringView path);
	};


#pragma region Details

	namespace Private
	{
		template<typename ...StringViews>
		Void PathCombineHelper(StringBuilder<Char8>& output, U8StringView path, StringViews... paths)
		{
			using namespace PredefinedAsciiSet;


			const Char8* input	= path.GetBuffer();
			SizeType size		= path.GetCount();

			Char8 first	= *input;
			Char8 last	= input[ size - 1 ];

			if ( Slashes.Contain(first) )
			{
				++input;
				--size;
			}
					
			if ( Slashes.Contain(last) )
				--size;

			output.Append( U8StringView(input, size) );

			if constexpr ( sizeof...(paths) > 0 )
			{
				output.Append('/');

				PathCombineHelper( output, paths... );
			}
		}
	}


	template<typename ...StringViews>
	static U8String Path::Combine(StringViews... paths)
	{
		static_assert( sizeof...(paths) >= 2 );
		static_assert( And<IsConvertible<StringViews, U8StringView> ...>::Value );


		StringBuilder<Char8> builder;
		Private::PathCombineHelper( builder, paths... );

		return builder.ToString();
	}

#pragma endregion
}