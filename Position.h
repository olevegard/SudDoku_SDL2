#pragma once

#include <array>
#include <ostream>

#include "Texture_Text.h"

struct Position// : Texture_Text
{
	int32_t value;
	bool locked;
	std::array< bool, 9 > possible;
	Texture_Text mainNumber;
	std::array< Texture_Text, 9 > smallNumbers;

	SDL_Rect rect;

	Position()
		:	rect( { 10, 10, 80, 80 } )
	{
		mainNumber.SetPos( { rect.x + 10, rect.y + 10 } );
		locked = false;
		std::fill( std::begin( possible ), std::end( possible ), true );
		value = 0;
	}
	void SetPos( SDL_Point p )
	{
		rect.x = p.x;
		rect.y = p.y;

		SDL_Rect digitRect = mainNumber.GetRect();
		SDL_Point sizeDiff
		{
			( rect.w - digitRect.w ) / 2,
			( rect.h - digitRect.h ) / 2
		};

		mainNumber.SetPos( { rect.x + sizeDiff.x,  rect.y + sizeDiff.y } );
	}
	void InitMainNumber( TTF_Font *font, const SDL_Color &bgColor, const SDL_Color &fgColor )
	{
		mainNumber.Init( font, bgColor, fgColor );

	}
	void InitSmallNumber( TTF_Font *font, const SDL_Color &bgColor, const SDL_Color &fgColor )
	{
		SDL_Point pos{ 5, 5 };
		SDL_Rect r = smallNumbers[ 0 ].GetRect();
		for ( auto i = 0; i < 9 ; ++i )
		{
			smallNumbers[ i ].Init( font, bgColor, fgColor );
			smallNumbers[ i ].SetPos( { rect.x + pos.x, rect.y + pos.y } );

			pos.x += 5 + r.w;
		}
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
	void Refresh( SDL_Renderer* renderer )
	{
		if ( value == 0 )
			mainNumber.RenderText_Solid( renderer, "-" );
		else
			mainNumber.RenderNumber( renderer, value );

		for ( auto i = 0 ; i < 9 ; ++i )
			smallNumbers[ i ].RenderNumber( renderer,  i + 1);

		PositionSmallNumbers();
	}
	void PositionSmallNumbers()
	{
		SDL_Rect size = smallNumbers[ 0 ].GetRect();
		SDL_Point totalSize = { size.w * 3, size.h * 3 };
		SDL_Point totalMargin = { rect.w - totalSize.x, rect.h - totalSize.y };
		SDL_Point margin = { totalMargin.x / 4, totalMargin.y / 4 };

		SDL_Point pos{ margin.x, margin.y };

		for ( auto i = 0 ; i < 9 ; ++i )
		{
			if ( i > 0 && ( ( i % 3 ) == 0 ) )
			{
				pos.x = margin.x;
				pos.y += size.h + margin.y;
			}

			smallNumbers[ i ].SetPos( { rect.x + pos.x, rect.y + pos.y } );

			pos.x += ( size.w + margin.x );
		}
	}
	inline void operator=( int32_t value_ )
	{
		if ( value_ != 0 )
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
	void Render( SDL_Renderer* renderer )
	{
		Refresh( renderer );
		SDL_SetRenderDrawColor( renderer, 0,0, 0, 255 );
		mainNumber.Render( renderer );
		SDL_SetRenderDrawColor( renderer, 0,0, 255, 255 );

		SDL_RenderDrawRect( renderer, &rect );

		SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );


		for ( auto i = 0; i < 9 ; ++i )
		{
			SDL_Rect r = smallNumbers[ i ].GetRect();
			r.w = r.h;
			r.x = rect.x + 5;
			r.y = rect.y + 5;

			SDL_RenderDrawRect( renderer, &r );
			smallNumbers[ i ].Render( renderer );
			SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		}
	}
};
