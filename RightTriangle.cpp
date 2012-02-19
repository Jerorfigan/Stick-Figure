#include "RightTriangle.h"

namespace SpriteAnimationTest
{

	bool RightTriangle::Intersects( Shape* )
	{
		return false;
	}
	SpriteAnimationTest::Edge RightTriangle::GetIntersectedEdge( Shape* shape, std::string &side )
	{
		return SpriteAnimationTest::Edge();
	}

}