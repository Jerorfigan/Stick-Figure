#pragma once

#include <vector>
#include "Vector2D.h"

namespace SpriteAnimationTest
{

	struct IntRectangle
	{
		IntRectangle(): _left(0), _top(0), _right(0), _bottom(0) {}
		IntRectangle( int left, int top, int right, int bottom ): _left(left), _top(top), _right(right), _bottom(bottom) {}
		
		bool Intersects( const IntRectangle &rhs )
		{
			// first check if any vertex of rhs is inside lhs
			std::vector< Vector2D > vertices;
			vertices.push_back( Vector2D( rhs._left, rhs._top ) );
			vertices.push_back( Vector2D( rhs._right, rhs._top ) );
			vertices.push_back( Vector2D( rhs._right, rhs._bottom ) );
			vertices.push_back( Vector2D( rhs._left, rhs._bottom ) );

			for( std::vector< Vector2D >::const_iterator citr = vertices.begin();
				 citr != vertices.end(); ++citr )
			{
				if( citr->_x >= this->_left && citr->_x <= this->_right && 
					citr->_y >= this->_top && citr->_y <= this->_bottom )
					return true;
			}

			// now check if any vertex of lhs is inside rhs
			vertices.clear();

			// first check if any vertex of rhs is inside lhs
			vertices.push_back( Vector2D( this->_left, this->_top ) );
			vertices.push_back( Vector2D( this->_right, this->_top ) );
			vertices.push_back( Vector2D( this->_right, this->_bottom ) );
			vertices.push_back( Vector2D( this->_left, this->_bottom ) );

			for( std::vector< Vector2D >::const_iterator citr = vertices.begin();
				 citr != vertices.end(); ++citr )
			{
				if( citr->_x >= rhs._left && citr->_x <= rhs._right && 
					citr->_y >= rhs._top && citr->_y <= rhs._bottom )
					return true;
			}

			return false;
		}

		int _left;
		int _top;
		int _right;
		int _bottom;
	};

}