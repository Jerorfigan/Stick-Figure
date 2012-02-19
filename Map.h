#pragma once

#include <map>
#include <vector>
#include <string>
#include "Rectangle.h"
#include "Surface.h"

namespace SpriteAnimationTest
{

	class Map
	{
	public:
		Map( std::string mapFile );

		void Draw();
		// Tests for a collision between the object bounding rectangle and any of the map elements (if there are multiple colliding 
		// map elements, only the first one to be checked is processed during collision logic). If a collision is detected, 
		// the object velocity is redirected tangential to the collision surface, with a new lesser magnitude that is inversely 
		// proportional to its mass. In addition, the rotation and contact surface information for the object are updated.
		// Returns: true if a collision was detected and resolved.
		bool Map::ResolveMapCollision( SpriteAnimationTest::Rectangle objectBoundingRectangle, float objectMass, 
									   Vector2D &objectVelocity, Vector2D &objectAcceleration );

		// Checks for but does not resolve a map collision
		bool Map::CheckForMapCollision( SpriteAnimationTest::Rectangle objectBoundingRectangle );

	private:
		std::map< size_t, Shape* > _elementBoundingShapes; // used for collision detection
		std::vector< size_t > _elements; // ids to graphics resources used by elements
	};

}