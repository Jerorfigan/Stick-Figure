#pragma once

#include "Vector2D.h"

namespace SpriteAnimationTest
{
	struct Edge
	{
		Edge() {}
		Edge( Vector2D point1, Vector2D point2 ) : _point1(point1), _point2(point2) {}

		Edge( const Edge &rhs )
		{
			this->_point1 = rhs._point1;
			this->_point2 = rhs._point2;
		}

		Edge& operator=( const Edge &rhs )
		{
			this->_point1 = rhs._point1;
			this->_point2 = rhs._point2;
			return *this;
		}

		Vector2D _point1;
		Vector2D _point2;
	};
}