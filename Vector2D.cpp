#include <cmath>
#include <stdexcept>
#include "Vector2d.h"
#include "UtilityFunctions.h"

namespace SpriteAnimationTest
{

	float Vector2D::Magnitude()
	{
		return sqrt( pow( _x, 2) + pow(_y, 2) );
	}
		
	float Vector2D::Angle()
	{
		float angle = 0;

		if( _x == 0 && _y == 0 ) 
		{
			throw std::exception("Vector2D::Angle called with vector <0,0>");
		}

		if( _x >= 0 && _y >= 0 )
		{
			// fourth quadrant
			if( _x == 0 ) 
			{
				angle = 270;
			}
			else
			{
				angle = 360 - AngleToDegrees( atan( abs( _y / _x ) ) ); 
			}
		}
		else if( _x < 0 && _y >= 0 )
		{
			// third quadrant
			angle = 180 + AngleToDegrees( atan( abs( _y / _x ) ) ); 
		} 
		else if( _x < 0 && _y < 0 )
		{
			// second quadrant	
			angle = 180 - AngleToDegrees( atan( abs( _y / _x ) ) ); 
		} 
		else
		{
			// first quadrant
			if( _x == 0 ) 
			{
				angle = 90;
			}
			else
			{
				angle = AngleToDegrees( atan( abs( _y / _x ) ) ); 
			}
		}

		return angle;
	}


	Vector2D Vector2D::UnitVector()
	{
		return *this / this->Magnitude();
	}

	Vector2D operator*( float scalar, const Vector2D& vector )
	{
		Vector2D result( vector._x * scalar, vector._y * scalar);
		return result;
	}

	Vector2D operator*( const Vector2D& vector, float scalar )
	{
		Vector2D result( vector._x * scalar, vector._y * scalar);
		return result;
	}

	Vector2D& Vector2D::operator+=( const Vector2D &rhs )
	{
		this->_x += rhs._x;
		this->_y += rhs._y;
		return *this;
	}

	Vector2D Vector2D::operator/( float divisor )
	{
		Vector2D result( _x / divisor, _y / divisor );
		return result;
	}

	Vector2D Vector2D::operator+( const Vector2D& rhs )
	{
		Vector2D result( this->_x + rhs._x, this->_y + rhs._y);
		return result;
	}

	Vector2D Vector2D::operator-( const Vector2D& rhs )
	{
		Vector2D result( this->_x - rhs._x, this->_y - rhs._y);
		return result;
	}

	std::ostream& operator<<( std::ostream &lhs, const Vector2D &rhs )
	{
		lhs << "<" << rhs._x << ", " << rhs._y << ">"; 
		return lhs;
	}

	Vector2D operator+( const Vector2D &lhs, const Vector2D &rhs )
	{
		Vector2D temp;
		temp._x = lhs._x + rhs._x;
		temp._y = lhs._y + rhs._y;
		return temp;
	}

	// dot product
	float operator*( const Vector2D& lhs, const Vector2D& rhs )
	{
		return lhs._x * rhs._x + lhs._y * rhs._y;
	}

}