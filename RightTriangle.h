#pragma once

#include "Shape.h"
#include "Vector2D.h"

namespace SpriteAnimationTest
{

	struct RightTriangle : public Shape
	{
		RightTriangle() {}
		RightTriangle( Vector2D verticalEndVertex, Vector2D ninetyDegreeVertex, Vector2D horizontalEndVertex ) : 
				_verticalEndVertex(verticalEndVertex), _ninetyDegreeVertex(ninetyDegreeVertex), _horizontalEndVertex(horizontalEndVertex) {}

		virtual bool Intersects( Shape* );
		virtual SpriteAnimationTest::Edge GetIntersectedEdge( Shape* shape, std::string &side );

		Vector2D _verticalEndVertex;
		Vector2D _ninetyDegreeVertex;
		Vector2D _horizontalEndVertex;
	};

}