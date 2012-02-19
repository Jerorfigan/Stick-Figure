#pragma once

#include <vector>
#include "Edge.h"

namespace SpriteAnimationTest
{

	class Surface
	{
	public:

		static const float coefficientOfSlidingFriction;
		static const float coefficientOfStaticFriction;

		/* Initializes a surface from an edge */
		Surface( SpriteAnimationTest::Edge );

		Surface( const Surface& rhs )
		{
			this->_surfaceEdge = rhs._surfaceEdge;
		}

		Vector2D GetTangentialForceOfGravity( Vector2D velocity, float mass );
		Vector2D GetForceOfFriction( float mass, Vector2D velocity );
		Vector2D GetTangentialVelocity( Vector2D velocityTowardsSurface );

		float GetSurfaceAngle();

		SpriteAnimationTest::Edge Edge();

		bool OnSurface( Vector2D point );

		SpriteAnimationTest::Edge _surfaceEdge;
	};

}