#include "UtilityFunctions.h"
#include "GlobalConstants.h"

namespace SpriteAnimationTest
{

	float AngleToRadians( float degrees )
	{
		return degrees * ( PI / 180.0f );
	}

	float AngleToDegrees( float radians )
	{
		return radians * ( 180.0f / PI );
	}

	float Min( float x, float y )
	{
		return x <= y ? x : y;
	}

}