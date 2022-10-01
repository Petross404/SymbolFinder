#include "string.hpp"

#include <cstddef>    // for size_t

std::string string::join_string_list( std::list<std::string_view> string_list )
{
	std::string str;

	for ( const auto& s : string_list ) { str += s; }

	return str;
}

std::list<std::string_view> string::split_string_list( std::string_view str,
						       std::string_view delimiter )
{
	std::list<std::string_view> list{};

	std::size_t pos = 0;
	std::string token;
	while ( ( pos = str.find( delimiter ) ) != std::string::npos )
	{
		token = str.substr( 0, pos );
		list.push_back( token );
	}

	return list;
}
