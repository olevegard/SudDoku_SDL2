#pragma once

#include <array>
#include <iostream>
#include <algorithm>

enum class Type
{
	Row,
	Column,
	Square
};

// A single row/column/square
class SuDokuUnit
{
	public:
	SuDokuUnit();
	SuDokuUnit( const std::array< int32_t , 9 > &data );
	
	bool Insert( int32_t digit, uint32_t pos );
	void Solve();

	uint32_t FindSingleUnsetDigitPos();
	bool DoInsertionChecks( int32_t digit, uint32_t pos );

	bool GetCountUnSolvedDigits( ) const;
	int32_t GetDigit( uint32_t pos ) const;

	bool IsSolved( ) const;
	bool IsDigitSet( uint32_t pos ) const;
	bool IsAlreadyInUnit( int32_t digit ) const;
	bool IsOnlyMissingOneDigit() const;

	void Print( ) const;
	void PrintRow() const;
	void PrintColumn() const;
	void PrintSquare() const;

	private:
	void Solve( uint32_t unsetDigitPos );

	std::array< int32_t , 9 > digits;
	std::array< bool, 9 > usedDigits;

	int32_t unSolvedDigits;
	Type type;
};

