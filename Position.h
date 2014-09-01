#pragma once

#include <array>
#include <ostream>

struct Position
{
	int32_t value;
	bool locked;
	std::array< bool, 9 > possible;

	Position()
	{
		locked = false;
		std::fill( std::begin( possible ), std::end( possible ), true );
		value = 0;
	}
	void SetValue( int32_t value_ )
	{
		value = value_;
		locked = true;

		std::fill( std::begin( possible ), std::end( possible ), false );
		possible[ static_cast< uint32_t > ( value ) - 1 ] = true;
	}
	int32_t GetValue() const
	{
		return value;
	}
	bool IsSet() const
	{
		return locked;
	}
	inline void operator=( int32_t value_ )
	{
		SetValue( value_ );
	}
	inline bool operator==( int32_t value_ ) const
	{
		return ( value == value_ );
	}
	std::ostream& operator<<( std::ostream &os ) const
	{
		return os << value;
	}
};
