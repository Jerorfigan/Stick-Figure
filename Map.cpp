#include "Map.h"
#include "Surface.h"
#include "Edge.h"
#include "RightTriangle.h"
#include "ServiceLocator.h"
#include <fstream>
#include <sstream>

extern size_t mainWindowId;

namespace SpriteAnimationTest
{

	Map::Map( std::string mapFile )
	{
		std::ifstream input( mapFile.c_str() );

		std::string lineBuffer;

		while( getline( input, lineBuffer ) )
		{
			std::string shape;

			if( lineBuffer[0] == '#' )
				continue;

			std::istringstream tokens( lineBuffer );

			tokens >> shape;
			if( !tokens ) throw std::exception("Map::Map - Map file has bad format"); 

			if( shape == "Rectangle" )
			{
				std::string junk;
				int p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y;

				tokens >> junk >> p1x >> junk >> p1y >> junk >> junk >> p2x >> junk >> p2y >> junk >> junk 
					   >> p3x >> junk >> p3y >> junk >> junk >> p4x >> junk >> p4y >> junk;
				if( !tokens ) throw std::exception("Map::Map - Map file has bad format"); 

				SpriteAnimationTest::Rectangle *newRectangle = new SpriteAnimationTest::Rectangle( Vector2D(p1x,p1y), Vector2D(p2x,p2y), Vector2D(p3x,p3y), Vector2D(p4x,p4y) );
				

				size_t elementId = ServiceLocator::GetGraphicsProvider()->InitRectangle( *newRectangle, 
																						 IGraphicsProvider::RGBColor( 0, 0, 0 ) );
				_elements.push_back( elementId );
				_elementBoundingShapes[ elementId ] = newRectangle;
			}
			else if( shape == "Triangle" )
			{
				std::string junk;
				int p1x, p1y, p2x, p2y, p3x, p3y;

				tokens >> junk >> p1x >> junk >> p1y >> junk >> junk >> p2x >> junk >> p2y >> junk >> junk 
					   >> p3x >> junk >> p3y >> junk;
				if( !tokens ) throw std::exception("Map::Map - Map file has bad format"); 

				RightTriangle *newRightTriangle = new RightTriangle( Vector2D(p1x,p1y), Vector2D(p2x,p2y), Vector2D(p3x,p3y) );

				size_t elementId = ServiceLocator::GetGraphicsProvider()->InitRightTriangle( *newRightTriangle, 
																				IGraphicsProvider::RGBColor( 0, 0, 0 ) );
				_elements.push_back( elementId );
				_elementBoundingShapes[ elementId ] = newRightTriangle;
			}
			else
			{
				throw std::exception("Map::Map - Unknown shape type encountered in map file"); 
			}
		}
	}

	void Map::Draw()
	{
		for( std::vector< size_t >::const_iterator citr = _elements.begin();
			 citr != _elements.end(); ++citr )
		{
			ServiceLocator::GetGraphicsProvider()->DrawDrawable( *citr, mainWindowId );
		}
	}

	// Tests for a collision between the object bounding rectangle and any of the map elements (if there are multiple colliding 
	// map elements, only the first one to be checked is processed during collision logic). If a collision is detected, 
	// the object velocity is redirected tangential to the collision surface, with a new lesser magnitude that is inversely 
	// proportional to its mass. In addition, the contact surface information for the object is updated.
	// Returns: true if a collision was detected and resolved.
	bool Map::ResolveMapCollision( SpriteAnimationTest::Rectangle objectBoundingRectangle, float objectMass, 
									   Vector2D &objectVelocity, Vector2D &objectAcceleration )
	{
		for( std::vector< size_t >::const_iterator elementIterator = _elements.begin(); elementIterator != _elements.end(); ++elementIterator )
		{
				Shape *mapElementBoundingShape = _elementBoundingShapes[ *elementIterator ];

				if( mapElementBoundingShape->Intersects( &objectBoundingRectangle ) )
				{
					// Get the edge of the bounding shape for the map element that intersects the object bounding rectangle
					std::string side;
					SpriteAnimationTest::Edge intersectedEdge = mapElementBoundingShape->GetIntersectedEdge( &objectBoundingRectangle, side );

					Surface *collisionSurface = new Surface( intersectedEdge );
					objectAcceleration = collisionSurface->GetTangentialForceOfGravity( objectVelocity, objectMass );
					objectVelocity = collisionSurface->GetTangentialVelocity( objectVelocity );
					
					return true;
				}
		}

		return false;
	}

	bool Map::CheckForMapCollision( SpriteAnimationTest::Rectangle objectBoundingRectangle )
	{
		for( std::vector< size_t >::const_iterator elementIterator = _elements.begin(); elementIterator != _elements.end(); ++elementIterator )
		{
				Shape *mapElementBoundingShape = _elementBoundingShapes[ *elementIterator ];

				if( mapElementBoundingShape->Intersects( &objectBoundingRectangle ) )
				{	
					return true;
				}
		}

		return false;
	}

}