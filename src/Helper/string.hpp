#ifndef STRING_HPP
#define STRING_HPP

#include <qstring.h>	// for QString

#include <list>		  // for list
#include <string>	  // for string
#include <string_view>	  // for string_view
#include <type_traits>	  // for is_same

namespace string {

template<typename T>
concept FromStringView = std::is_same<T, std::string_view>::value;

template<typename T>
QString toqstring( T sv )
	requires FromStringView<T>
{
	return QString::fromLocal8Bit( sv.data(), (int)sv.size() );
}

template<typename T>
	requires std::is_same<T, std::string>::value
QString toqstring( T str )
{
	return QString::fromStdString( str );
}

template<typename T>
concept FromQString = std::is_same<T, QString>::value;

template<typename T>
std::string tostring( const T& qs )
	requires FromQString<T>
{
	return qs.toStdString();
}

template<typename T>
std::string tostring( T sv )
	requires FromStringView<T>
{
	return static_cast<std::string>( sv );
}

template<typename T>
concept StringViewList =
	std::is_same<T, std::string>::value || std::is_same<T, std::string_view>::value;

template<typename T>
bool comparelists( const std::list<T>& lista, const std::list<T>& listb )
	requires StringViewList<T>
{
	auto margsIter{ lista.begin() };
	auto fargsIter{ listb.begin() };

	bool is_equal = true;

	while ( margsIter != lista.end() && fargsIter != listb.end() )
	{
		if ( *margsIter != *fargsIter )
		{
			is_equal = false;
			break;
		}

		// Increment
		std::advance( margsIter, 1 );
		std::advance( fargsIter, 1 );
	}

	return is_equal;
}

template<typename T> std::list<T> create_list( const T& v )
{
	return std::list<T>{ v };
}

template<typename T>
concept StringConcatenate =
	std::is_same<T, std::string>::value || std::is_same<T, QString>::value;

template<typename T> T adder( const T& s ) { return s; }

template<typename T, typename... ARGS>
std::string concatenate( T first, const ARGS&... args )
	requires StringConcatenate<T>
{
	return first + adder( args... );
}

std::string join_string_list( std::list<std::string_view> string_list );

std::list<std::string_view> split_string_list( std::string_view str,
					       std::string_view delimiter );

};    // namespace string
#endif
