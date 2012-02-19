#pragma once

#include "Shape.h"
#include "Edge.h"
#include "Vector2D.h"

namespace SpriteAnimationTest
{
	struct Rectangle : public Shape
	{
		Rectangle() {}
		Rectangle( Vector2D topLeft, Vector2D topRight, Vector2D bottomRight, Vector2D bottomLeft ) : 
		_topLeft(topLeft), _topRight(topRight), _bottomRight(bottomRight), _bottomLeft(bottomLeft) {}

		virtual bool Intersects( Shape* );
		virtual Edge GetIntersectedEdge( Shape* shape, std::string &side );

		bool Contains( Vector2D ); 

		Vector2D _topLeft;
		Vector2D _topRight;
		Vector2D _bottomRight;
		Vector2D _bottomLeft;
	};
}