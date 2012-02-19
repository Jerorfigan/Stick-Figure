#include "Rectangle.h"
#include <stdexcept>
#include <vector>
#include <string>

namespace SpriteAnimationTest
{

	bool SpriteAnimationTest::Rectangle::Intersects( Shape* shape )
	{
		// right now, can only compute intersection with another rectangle
		SpriteAnimationTest::Rectangle *thatRect = dynamic_cast< SpriteAnimationTest::Rectangle* >( shape );

		if( thatRect == NULL )
			throw std::exception("Rectangle::Intersects - called with argument that is not a rectangle");

		// Check if any vertices from this rectangle fall within area of thatRect or if any of thatRect's vertices
		// fall within the area of this rectangle
		std::vector< Vector2D > theseVertices;
		theseVertices.push_back( this->_topLeft );
		theseVertices.push_back( this->_topRight );
		theseVertices.push_back( this->_bottomRight );
		theseVertices.push_back( this->_bottomLeft );

		std::vector< Vector2D > thoseVertices;
		thoseVertices.push_back( thatRect->_topLeft );
		thoseVertices.push_back( thatRect->_topRight );
		thoseVertices.push_back( thatRect->_bottomRight );
		thoseVertices.push_back( thatRect->_bottomLeft );

		for( std::vector< Vector2D >::const_iterator theseVerticesIterator = theseVertices.begin(), 
			 thoseVerticesIterator = thoseVertices.begin();
			 theseVerticesIterator != theseVertices.end(); ++theseVerticesIterator, ++thoseVerticesIterator )
		{
			 if( this->Contains( *thoseVerticesIterator ) )
			 {
				 return true;
			 }
			 if( thatRect->Contains( *theseVerticesIterator ) )
			 {
				 return true;
			 }
		}

		return false;
	}

	SpriteAnimationTest::Edge SpriteAnimationTest::Rectangle::GetIntersectedEdge( Shape* shape, std::string &side )
	{
		if( !this->Intersects( shape ) )
			throw std::exception("Rectangle::GetIntersectedEdge was called with 2 rectangles that don't intersect");

		// right now, can only compute intersection with another rectangle
		SpriteAnimationTest::Rectangle *thatRect = dynamic_cast< SpriteAnimationTest::Rectangle* >( shape );

		if( thatRect == NULL )
			throw std::exception("Rectangle::GetIntersectedEdge - called with argument that is not a rectangle");

		// Check if any vertices from this rectangle fall within area of thatRect or if any of thatRect's vertices
		// fall within the area of this rectangle
		std::vector< Vector2D > theseVerticesAll;
		theseVerticesAll.push_back( this->_topLeft );
		theseVerticesAll.push_back( this->_topRight );
		theseVerticesAll.push_back( this->_bottomRight );
		theseVerticesAll.push_back( this->_bottomLeft );

		std::vector< Vector2D > theseVertices;

		std::vector< Vector2D > thoseVerticesAll;
		thoseVerticesAll.push_back( thatRect->_topLeft );
		thoseVerticesAll.push_back( thatRect->_topRight );
		thoseVerticesAll.push_back( thatRect->_bottomRight );
		thoseVerticesAll.push_back( thatRect->_bottomLeft );

		std::vector< Vector2D > thoseVertices;

		for( std::vector< Vector2D >::const_iterator theseVerticesIterator = theseVerticesAll.begin(), 
			 thoseVerticesIterator = thoseVerticesAll.begin();
			 theseVerticesIterator != theseVerticesAll.end(); ++theseVerticesIterator, ++thoseVerticesIterator )
		{
			 if( this->Contains( *thoseVerticesIterator ) )
			 {
				 thoseVertices.push_back( *thoseVerticesIterator );
			 }
			 if( !thatRect->Contains( *theseVerticesIterator ) )
			 {
				 theseVertices.push_back( *theseVerticesIterator );
			 } 
		}

		if( thoseVertices.size() > 0 )
		{
			/* At least one vertex from that rectangle lies within the area of this rectangle. To compute which edge 
			   of this rectangle is intersected, we'll find the average position of all vertices from that rectangle that
			   lie within this one and then compute the perpendicular distance from that point to all edges of this 
			   rectangle. The edge with the minimum corresponding distance will be considered the intersected edge. */
			Vector2D sum;
			size_t count = 0;
			for( std::vector< Vector2D >::const_iterator thoseVerticesIterator = thoseVertices.begin();
				 thoseVerticesIterator != thoseVertices.end(); ++thoseVerticesIterator )
			{
				sum += *thoseVerticesIterator;
				++count;
			}
			Vector2D avgPosition = sum / count;

			std::vector< std::string > sides;
			sides.push_back("top");
			sides.push_back("right");
			sides.push_back("bottom");

			std::string intersectedSide = "left";
			float minDist = abs(this->_topLeft._x - avgPosition._x);
			float dist;
			for( std::vector< std::string >::const_iterator sideIterator = sides.begin();
				sideIterator != sides.end(); ++sideIterator )
			{
				if( *sideIterator == "top" )
					dist = abs(avgPosition._y - this->_topLeft._y);
				if( *sideIterator == "right" )
					dist = abs(this->_bottomRight._x - avgPosition._x);
				if( *sideIterator == "bottom" )
					dist = abs(this->_bottomRight._y - avgPosition._y);
				if( dist < minDist )
				{
					minDist = dist;
					intersectedSide = *sideIterator;
				}
			}

			side = intersectedSide;
			if( intersectedSide == "left" )
				return Edge( this->_topLeft, this->_bottomLeft );
			else if( intersectedSide == "top" ) 
				return Edge( this->_topLeft, this->_topRight );
			else if( intersectedSide == "right" )
				return Edge( this->_topRight, this->_bottomRight );
			else
				return Edge( this->_bottomLeft, this->_bottomRight );
		}
		else
		{
			   /* At least one vertex from this rectangle lies within the area of that rectangle (but not vice versa). In this case, 
				  we'll define the "intersected" edge of this rectangle as the edge whose midpoint is closest to the center of that rectangle. */

			Vector2D midpointOfThatRect( (thatRect->_bottomLeft._x + thatRect->_bottomRight._x) / 2.0f, 
										 (thatRect->_bottomLeft._y + thatRect->_topLeft._y) / 2.0f );

			std::string intersectedSide = "left";
			Vector2D midPointOfThisLeftSide( (this->_topLeft + this->_bottomLeft) / 2.0f ); 
			float minDist = ( midpointOfThatRect - midPointOfThisLeftSide ).Magnitude();
			float dist;
			
			std::vector< std::string > sides;
			sides.push_back("top");
			sides.push_back("right");
			sides.push_back("bottom");

			for( std::vector< std::string >::const_iterator sideIterator = sides.begin();
				 sideIterator != sides.end(); ++sideIterator )
			{
				if( *sideIterator == "top" )
				{
					Vector2D midPointOfThisTopSide( (this->_topLeft + this->_topRight) / 2.0f );
					dist = ( midpointOfThatRect - midPointOfThisTopSide ).Magnitude();
				}
				if( *sideIterator == "right" )
				{
					Vector2D midPointOfThisRightSide( (this->_topRight + this->_bottomRight) / 2.0f );
					dist = ( midpointOfThatRect - midPointOfThisRightSide ).Magnitude();
				}
				if( *sideIterator == "bottom" )
				{
					Vector2D midPointOfThisBottomSide( (this->_bottomLeft + this->_bottomRight) / 2.0f );
					dist = ( midpointOfThatRect - midPointOfThisBottomSide ).Magnitude();
				}
				if( dist < minDist )
				{
					minDist = dist;
					intersectedSide = *sideIterator;
				}
			}

			side = intersectedSide;
			if( intersectedSide == "left" )
				return Edge( this->_topLeft, this->_bottomLeft );
			else if( intersectedSide == "top" ) 
				return Edge( this->_topLeft, this->_topRight );
			else if( intersectedSide == "right" )
				return Edge( this->_topRight, this->_bottomRight );
			else
				return Edge( this->_bottomLeft, this->_bottomRight );
		}
	}

	bool SpriteAnimationTest::Rectangle::Contains( Vector2D testPoint )
	{
		if( testPoint._x > this->_topLeft._x && testPoint._y > this->_topLeft._y &&
			testPoint._x < this->_bottomRight._x && testPoint._y < this->_bottomRight._y )
			return true;
		else
			return false;
	}

}