#include <cmath>
#include "Surface.h"
#include "GlobalConstants.h"

namespace SpriteAnimationTest
{

	const float Surface::coefficientOfSlidingFriction = 0.2f;
	const float Surface::coefficientOfStaticFriction = 0.8f;

	Surface::Surface( SpriteAnimationTest::Edge e )
	{
		// make sure leftmost vertex in Edge is assigned to Surface::Edge._point1
		if( e._point1._x <  e._point2._x )
		{
			_surfaceEdge._point1._x = e._point1._x;
			_surfaceEdge._point1._y = e._point1._y;
			_surfaceEdge._point2._x = e._point2._x;
			_surfaceEdge._point2._y = e._point2._y;
		}
		else
		{
			_surfaceEdge._point1._x = e._point2._x;
			_surfaceEdge._point1._y = e._point2._y;
			_surfaceEdge._point2._x = e._point1._x;
			_surfaceEdge._point2._y = e._point1._y;
		}
	}

	Vector2D Surface::GetTangentialForceOfGravity( Vector2D velocity, float mass )
	{
		if( _surfaceEdge._point1._x == _surfaceEdge._point2._x )
		{
			/* Surface is vertical, tangential force of acceleration is just gravity */
			return Vector2D( 0, ACCELERATION_OF_GRAVITY );
		}
		else if( _surfaceEdge._point1._y == _surfaceEdge._point2._y )
		{
			/* Surface is horizontal, need to determine whether we hit the top or bottom using angle of velocity */
			if( velocity.Angle() >= 0 && velocity.Angle() <= 180 )
			{
				/* Hit bottom of surface bottom */
				return Vector2D( 0, ACCELERATION_OF_GRAVITY );
			}
			else
			{
				/* Hit top of surface */
				return Vector2D();
			}
		}
		else
		{
			/* Surface is skewed */
			return Vector2D();
		}
	}

	Vector2D Surface::GetForceOfFriction( float mass, Vector2D velocity )
	{
		return Vector2D(0,0);
	}

	Vector2D Surface::GetTangentialVelocity( Vector2D velocityTowardsSurface )
	{
		/* We need to find the projection of the velocity vector in the direction of the surface vector. To start, we'll 
		   need to compute the surface vector in both directions. We'll use the dot product to find the angle between each 
		   of them, and use the one with the smaller angle for the remaining calculation, since we know the angle between 
		   surface and velocity should be between 0 and 90. */
		Vector2D surfaceVector1 = _surfaceEdge._point1 - _surfaceEdge._point2;
		Vector2D surfaceVector2 = _surfaceEdge._point2 - _surfaceEdge._point1;

		/* Use the dot product to get the angle between velocity and surface for each surface vector and save minimum angle */
		float angle1 = acos( ( velocityTowardsSurface * surfaceVector1 ) / ( velocityTowardsSurface.Magnitude() * surfaceVector1.Magnitude() ) );
		float angle2 = acos( ( velocityTowardsSurface * surfaceVector2 ) / ( velocityTowardsSurface.Magnitude() * surfaceVector2.Magnitude() ) );

		float finalAngle = 0;
		Vector2D projectionUnitVector;
		if( angle1 < angle2 )
		{
			finalAngle = angle1;
			projectionUnitVector = surfaceVector1.UnitVector();
		}
		else
		{
			finalAngle = angle2;
			projectionUnitVector = surfaceVector2.UnitVector();
		}
		
		float projectionMagnitude = velocityTowardsSurface.Magnitude() * cos( finalAngle );

		return projectionUnitVector * projectionMagnitude;
	}

	float Surface::GetSurfaceAngle()
	{
		return 0.0f;
	}

	SpriteAnimationTest::Edge Surface::Edge()
	{
		return _surfaceEdge;
	}

	bool Surface::OnSurface( Vector2D point )
	{
		if( point._x < _surfaceEdge._point1._x || point._x > _surfaceEdge._point2._x ) 
			return false;
		else
			return true;
	}

}