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
	void Init( TTF_Font *font, const SDL_Color &bgColor, const SDL_Color &fgColor )
	{
		mainNumber.Init( font, bgColor, fgColor );
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
		SDL_SetRenderDrawColor( renderer, 0,0, 255, 255 );
		SDL_RenderDrawRect( renderer, &rect );
		Refresh( renderer );
		mainNumber.Render( renderer );
	}
};
