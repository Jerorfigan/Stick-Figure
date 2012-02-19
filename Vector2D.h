#pragma once

#include <iostream>

namespace SpriteAnimationTest
{

	struct Vector2D
	{
		Vector2D(): _x(0), _y(0) {}
		Vector2D( float x, float y ): _x(x), _y(y) {}
		Vector2D( const Vector2D &rhs )
		{
			this->_x = rhs._x;
			this->_y = rhs._y;
		}


		float Magnitude();
		
		// returns the angle (0 - 360) in degrees
		float Angle();

		// returns the unit vector representation of this vector
		Vector2D UnitVector();

		// operators
		Vector2D& operator+=( const Vector2D& );
		Vector2D operator+( const Vector2D& );
		Vector2D operator-( const Vector2D& );
		Vector2D operator/( float );

		Vector2D& operator=( const Vector2D& rhs )
		{
			this->_x = rhs._x;
			this->_y = rhs._y;
			return *this;
		}

		float _x;
		float _y;
	};

	std::ostream& operator<<( std::ostream &lhs, const Vector2D &rhs );

	Vector2D operator+( const Vector2D &lhs, const Vector2D &rhs );
	
	Vector2D operator*( float, const Vector2D& );
	Vector2D operator*( const Vector2D&, float );
	// dot product
	float operator*( const Vector2D&, const Vector2D& );
}