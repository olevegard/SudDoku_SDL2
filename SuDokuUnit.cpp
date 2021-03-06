#include "SuDokuUnit.h"

#include <algorithm>

SuDokuUnit::SuDokuUnit()
	:	digits( { { 0, 0, 0, 0, 0, 0, 0, 0, 0 } } )
	,	usedDigits( { { false, false, false, false, false, false, false, false, false } } )
	,	unSolvedDigits( 9 )
	,	type( Type::Row )
	
{
}
SuDokuUnit::SuDokuUnit( const std::array< int32_t , 9 > &data )
:	SuDokuUnit( )
{
	type = Type::Row;
	for ( uint32_t i = 0 ; i < 9 ; ++i )
	{
		uint32_t currentDigit = static_cast< uint32_t > ( data[ i ] );
		if ( currentDigit != 0 )
		{
			digits[ i ] = static_cast< int32_t > ( currentDigit );
			usedDigits[ currentDigit - 1 ] = true;
			--unSolvedDigits;
		}
	}
}
bool SuDokuUnit::DoInsertionChecks( int32_t digit, uint32_t pos )
{
	if ( digits[ pos ] == digit )
	{
		std::cout << "NOTE : digit " << digit << " already set in pos " << pos << "\n";
		return false;
	}
	if ( IsAlreadyInUnit( digit ) )
	{
		std::cout << "ERROR : " << digit << " is already in unit!\n\n";
		return false;
	}

	if ( !IsDigitSet( pos ) )
	{
		std::cout << "OK\n";
		--unSolvedDigits;
	}
	else
		std::cout << "NOTE : pos " << pos << " was already set : " << digits[ pos ] << "\n";

	return true;
}
bool SuDokuUnit::Insert( int32_t digit, uint32_t pos )
{
	if ( digit == 0 )
		return false;

	std::string str;

	switch ( type )
	{
		case Type::Row:
			str = "row";
			break;
		case Type::Column:
			str = "column";
			break;
		case Type::Square:
			str = "square";
			break;
	}
	std::cout << "Inserting " << str << " - " << digit << " @ " << pos << " -> ";

	if ( DoInsertionChecks( digit, pos ) )
	{
		digits[ pos ] = digit;
		usedDigits[ static_cast< uint32_t > ( digit ) - 1 ] = true;
		return true;
	}

	return false;
}
SolveResult SuDokuUnit::Solve()
{
	if ( !IsOnlyMissingOneDigit() )
		return SolveResult( 0, 0 );

	return Solve( FindSingleUnsetDigitPos() );
}
SolveResult SuDokuUnit::Solve( uint32_t unsetDigitPos )
{
	SolveResult result( 0, unsetDigitPos );
	for ( uint32_t i = 0; i < 9 ; ++i )
	{
		if ( !usedDigits[ i ] )
		{
			int32_t digit = static_cast< int32_t > ( i + 1 );
			Insert( digit , unsetDigitPos );
			result.digit = digit;
			result.solved = true;
			return result;
		}
	}

	return result;
}
uint32_t SuDokuUnit::FindSingleUnsetDigitPos()
{
	for ( uint32_t i = 0; i < 9 ; ++i )
	{
		if ( digits[ i ] == 0 )
			return i;
	}

	return 0;
}
bool SuDokuUnit::GetCountUnSolvedDigits( ) const
{
	return unSolvedDigits;
}
int32_t SuDokuUnit::GetDigit( uint32_t pos ) const
{
	return digits[ pos ];
}
bool SuDokuUnit::IsDigitSet( uint32_t pos ) const
{
	return ( digits[ pos ] != 0 );
}
bool SuDokuUnit::IsSolved( ) const
{
	return unSolvedDigits == 0;
}
bool SuDokuUnit::IsOnlyMissingOneDigit() const
{
	return unSolvedDigits == 1;
}
bool SuDokuUnit::IsAlreadyInUnit( int32_t digit ) const
{
	return std::find( std::begin( digits ), std::end( digits ), digit ) != std::end( digits );
}
void SuDokuUnit::PrintRow() const
{
	for ( uint32_t i = 0; i < 9 ; ++i )
	{
		if ( i > 0 && ( i % 3 ) == 0 )
			std::cout << "| ";
		std::cout << digits[ i ] << "  ";
	}
	std::cout << std::endl;
}
void SuDokuUnit::PrintColumn() const
{
	for ( uint32_t i = 0; i < 9 ; ++i )
	{
		if ( i > 0 && ( i % 3 ) == 0 )
			std::cout << "\n";
		std::cout << digits[ i ] << "\n";
	}
	std::cout << std::endl;
}
void SuDokuUnit::PrintSquare() const
{
	for ( uint32_t i = 0; i < 9 ; ++i )
	{
		if ( i > 0 && ( i % 3 ) == 0 )
			std::cout << "\n";
		std::cout << digits[ i ] << "  ";
	}
	std::cout << std::endl;
}
void SuDokuUnit::Print( ) const
{
	if ( type == Type::Column )
		PrintColumn();
	else if ( type == Type::Row )
		PrintRow();
	else if ( type == Type::Square )
		PrintSquare();
}
void SuDokuUnit::SetType( Type type_ )
{
	type = type_;
}
