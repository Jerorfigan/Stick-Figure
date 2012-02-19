#pragma once

#include <string>
#include "Edge.h"

namespace SpriteAnimationTest
{

	class Shape
	{
	public:
		virtual bool Intersects( Shape* ) = 0;
		virtual SpriteAnimationTest::Edge GetIntersectedEdge( Shape* shape, std::string &side ) = 0;
	};

}