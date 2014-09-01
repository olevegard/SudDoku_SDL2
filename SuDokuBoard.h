#pragma once

#include "SuDokuUnit.h"

#include <algorithm>
#include <memory>

class SuDokuBoard
{
	public:
		SuDokuBoard()
		{
			std::for_each( std::begin( rows    ), std::end( rows    ), []( SuDokuUnit &unit ){ unit.SetType( Type::Row ); } );
			std::for_each( std::begin( columns ), std::end( columns ), []( SuDokuUnit &unit ){ unit.SetType( Type::Column ); } );
			std::for_each( std::begin( squares ), std::end( squares ), []( SuDokuUnit &unit ){ unit.SetType( Type::Square ); } );

			// Row 1
			Set( 5, 0, 0 ); 
			Set( 3, 1, 0 ); 
			Set( 8, 2, 0 ); 
			Set( 0, 3, 0 ); 
			Set( 1, 4, 0 ); 
			Set( 6, 5, 0 ); 
			Set( 0, 6, 0 ); 
			Set( 7, 7, 0 ); 
			Set( 9, 8, 0 ); 

			// Row 2
			Set( 0, 0, 1 ); 
			Set( 0, 1, 1 ); 
			Set( 0, 2, 1 ); 
			Set( 3, 3, 1 ); 
			Set( 8, 4, 1 ); 
			Set( 0, 5, 1 ); 
			Set( 5, 6, 1 ); 
			Set( 4, 7, 1 ); 
			Set( 1, 8, 1 ); 

			// Row 3
			Set( 2, 0, 2 ); 
			Set( 4, 1, 2 ); 
			Set( 1, 2, 2 ); 
			Set( 5, 3, 2 ); 
			Set( 0, 4, 2 ); 
			Set( 0, 5, 2 ); 
			Set( 0, 6, 2 ); 
			Set( 0, 7, 2 ); 
			Set( 0, 8, 2 ); 

			// Row 4
			Set( 0, 0, 3 ); 
			Set( 6, 1, 3 ); 
			Set( 0, 2, 3 ); 
			Set( 9, 3, 3 ); 
			Set( 0, 4, 3 ); 
			Set( 0, 5, 3 ); 
			Set( 0, 6, 3 ); 
			Set( 0, 7, 3 ); 
			Set( 0, 8, 3 ); 

			// Row 5
			Set( 0, 0, 4 ); 
			Set( 0, 1, 4 ); 
			Set( 0, 2, 4 ); 
			Set( 0, 3, 4 ); 
			Set( 3, 4, 4 ); 
			Set( 5, 5, 4 ); 
			Set( 0, 6, 4 ); 
			Set( 9, 7, 4 ); 
			Set( 0, 8, 4 ); 

			// Row 6
			Set( 0, 0, 5 ); 
			Set( 9, 1, 5 ); 
			Set( 0, 2, 5 ); 
			Set( 0, 3, 5 ); 
			Set( 0, 4, 5 ); 
			Set( 4, 5, 5 ); 
			Set( 0, 6, 5 ); 
			Set( 0, 7, 5 ); 
			Set( 2, 8, 5 ); 

			// Row 7
			Set( 6, 0, 6 ); 
			Set( 8, 1, 6 ); 
			Set( 7, 2, 6 ); 
			Set( 2, 3, 6 ); 
			Set( 0, 4, 6 ); 
			Set( 0, 5, 6 ); 
			Set( 9, 6, 6 ); 
			Set( 3, 7, 6 ); 
			Set( 0, 8, 6 ); 

			// Row 8
			Set( 1, 0, 7 ); 
			Set( 2, 1, 7 ); 
			Set( 9, 2, 7 ); 
			Set( 0, 3, 7 ); 
			Set( 4, 4, 7 ); 
			Set( 0, 5, 7 ); 
			Set( 0, 6, 7 ); 
			Set( 5, 7, 7 ); 
			Set( 0, 8, 7 ); 

			// Row 9
			Set( 0, 0, 8 ); 
			Set( 5, 1, 8 ); 
			Set( 4, 2, 8 ); 
			Set( 6, 3, 8 ); 
			Set( 9, 4, 8 ); 
			Set( 0, 5, 8 ); 
			Set( 0, 6, 8 ); 
			Set( 0, 7, 8 ); 
			Set( 8, 8, 8 ); 

			Print();
			SolveSquare( 6 );
		}
		void SolveSquare( uint32_t squareIndex )
		{
			SolveResult result = squares[ CalculateSquareIndex( 0, squareIndex ) ].Solve();

			uint32_t rowIndex = ( ( squareIndex / 3 ) * 3 ) + ( result.position / 3 );
			uint32_t columnIndex = ( ( squareIndex % 3 ) * 3 ) + ( result.position % 3 );

			rows[ rowIndex ].Insert( result.digit, columnIndex );
			columns[ columnIndex ].Insert( result.digit, rowIndex );

			std::cout << "Inserted into column " << columnIndex << " and row : " << rowIndex << std::endl;
			squares[squareIndex].Print();
			std::cout << std::endl;
			columns[columnIndex].Print();
			std::cout << std::endl;
			rows[rowIndex].Print();
			std::cout << std::endl;

		}
		void Print()
		{
			for ( uint32_t i = 0 ; i < 9 ; ++i )
			{
				if ( i > 0 && ( ( i % 3 ) == 0 ) )
					std::cout << std::endl;
				rows[i].Print();
			}
		}
		void Set( int32_t digit, uint32_t column, uint32_t row )
		{
			auto squarePos = CalculateSquarePos( column, row );

			rows   [ row    ].SetType( Type::Row );
			rows   [ row    ].Insert( digit, column ); 

			columns[ column ].SetType( Type::Column );
			columns[ column ].Insert( digit, row ); 

			squares[ squarePos.first ].SetType( Type::Square );
			squares[ squarePos.first ].Insert( digit, squarePos.second );

			board[ column ][ row ] = digit;
		}
		void PrintInsertInfo( int32_t digit, uint32_t column, uint32_t row, std::pair< uint32_t, uint32_t > squarePos )
		{
			std::cout << "Insert " << digit 
				<< "\n\tColumn : " << column
				<< "\n\tRow : " << row
				<< "\n\tSquare : " << squarePos.first << ", " << squarePos.second
				<< std::endl;
		}
		std::pair< uint32_t, uint32_t > CalculateSquarePos( uint32_t column, uint32_t row )
		{
			std::pair< uint32_t, uint32_t > pos;

			pos.first  = CalculateSquareIndex( column, row );
			pos.second = CalculatePosInSquare( column, row );

			return pos;
		}
		uint32_t CalculateSquareIndex( uint32_t column, uint32_t row ) 
		{
			return ( column / 3 ) + ( ( row / 3 )  * 3 );
		}
		uint32_t CalculatePosInSquare( uint32_t column, uint32_t row ) 
		{
			return ( column % 3 ) + ( ( row % 3 )  * 3 );
		}

		std::array< SuDokuUnit, 9 > rows;
		std::array< SuDokuUnit, 9 > columns;
		std::array< SuDokuUnit, 9 > squares;
		std::array< std::array< int32_t, 9 >, 9 > board;
};