#pragma once

#include <fstream> 
#include <map>
#include <vector>
#include "AnimationSystem.h"
#include "GlobalConstants.h"
#include "GlobalResources.h"
#include "IntRectangle.h"
#include "IStateTracking.h"
#include "ServiceLocator.h"
#include "State.h"
#include "StickFigureState.h"
#include "Surface.h"
#include "Vector2D.h"

extern size_t mainWindowId;

namespace SpriteAnimationTest
{

	class StickFigure //: public IStateTracking
	{
	public: 
		/* Class constants */
		static const float _jumpVelocity; // pixels per second
		static const float _walkVelocity; // pixels per second
		static const float _mass; // in kg
		static const int _stickFigureWidth = 64; // width in pixels
		static const int _stickFigureHeight = 64; // height in pixels

	public:
		StickFigure();

		void MoveTo( float x, float y );

		//void Update( float elapsedTime )
		//{
		//	/* Update stick figure position */

		//	std::vector< Vector2D > forces;

		//	if( _contactSurface == NULL ) /* In air */
		//	{
		//		// factor in force of gravity
		//		forces.push_back( Vector2D( 0.0f, _mass * ACCELERATION_OF_GRAVITY ) );

		//			if( ServiceLocator::GetInputProvider()->IsKeyDown( "right", mainWindowId ) )
		//			{
		//				/* Calculate move right force tangent to surface */
		//				Vector2D moveRight = ( Vector2D(_contactSurface->Edge()._point2 - _contactSurface->Edge()._point1) ).UnitVector() * 
		//					( _moveAcceleration * _mass );

		//				forces.push_back( moveRight );
		//			}
		//			if( ServiceLocator::GetInputProvider()->IsKeyDown( "left", mainWindowId ) )
		//			{
		//				/* Calculate move left force tangent to surface */
		//				Vector2D moveLeft = ( Vector2D(_contactSurface->Edge()._point1 - _contactSurface->Edge()._point2) ).UnitVector() * 
		//					( _moveAcceleration * _mass );
		//				forces.push_back( moveLeft );
		//			}
		//	}
		//	else /* On a surface */
		//	{
		//		// factor in tangential force of gravity
		//		forces.push_back( _contactSurface->GetTangentialForceOfGravity( _mass ) );

		//		// factor in friction
		//		forces.push_back( _contactSurface->GetForceOfFriction( _mass, _velocity ) );

		//		// factor in player controlled movement in the up direction
		//		if( ServiceLocator::GetInputProvider()->IsKeyDown( "up", mainWindowId ) )
		//		{
		//			Vector2D jumping( 0.0f, - 1200 * _moveAcceleration * _mass ); 
		//			forces.push_back( jumping );

		//			delete _contactSurface;
		//			_contactSurface = NULL;
		//		} 

		//		/* If tangential gravity & friction cancel out, then the stick figure is done falling/sliding, so we're going to allow
		//		   player controlled movement to the right & left at this point. This means we need to add in forces from player holding down move keys */
		//		if( ( forces[0] + forces[1] ).Magnitude() == 0 )
		//		{
		//			if( ServiceLocator::GetInputProvider()->IsKeyDown( "right", mainWindowId ) )
		//			{
		//				/* Calculate move right force tangent to surface */
		//				Vector2D moveRight = ( Vector2D(_contactSurface->Edge()._point2 - _contactSurface->Edge()._point1) ).UnitVector() * 
		//					( _moveAcceleration * _mass );

		//				forces.push_back( moveRight );
		//			}
		//			if( ServiceLocator::GetInputProvider()->IsKeyDown( "left", mainWindowId ) )
		//			{
		//				/* Calculate move left force tangent to surface */
		//				Vector2D moveLeft = ( Vector2D(_contactSurface->Edge()._point1 - _contactSurface->Edge()._point2) ).UnitVector() * 
		//					( _moveAcceleration * _mass );
		//				forces.push_back( moveLeft );
		//			}
		//		}
		//	}

		//	// Sum forces to find net force / acceleration
		//	Vector2D sum(0.0f, 0.0f);
		//	for( std::vector< Vector2D >::const_iterator citr = forces.begin(); 
		//		 citr != forces.end(); ++citr )
		//	{
		//		sum += *citr;
		//	}

		//	Vector2D acceleration = sum / _mass;

		//	if( _contactSurface && acceleration.Magnitude() == 0 )
		//	{
		//		// if on the ground and experiencing no acceleration from player movement, then add artificial acceleration to slow u down
		//		if( _velocity._x > 30 || _velocity._x < -30) acceleration = _velocity * -1;
		//		else 
		//		{
		//			_velocity._x = 0;
		//			_velocity._y = 0;
		//		}
		//	}

		//	Vector2D previousVelocity = _velocity;
		//	_velocity += acceleration * elapsedTime;

		//	if( _contactSurface && (_velocity.Magnitude() > _maxMoveVelocity || _velocity.Magnitude() < -_maxMoveVelocity) ) _velocity = previousVelocity;

		//	/* If velocity becomes inverted, which will happen when the stick figure slides up a slope a ways and then back down, make sure it 
		//	   becomes 0 at least once so that static friction has a chance to take effect */
		//	//if( abs(previousVelocity.Angle - _velocity.Angle) == 180 )
		//	//{
		//	//	_velocity = Vector2D(0.0f, 0.0f);
		//	//}

		//	Vector2D newPosition = _position + (_velocity * elapsedTime);

		//	while( GlobalResources::GetCurrentMap()->ResolveMapCollision( 
		//		SpriteAnimationTest::Rectangle( Vector2D(newPosition._x - _stickFigureWidth / 16.0f, newPosition._y - _stickFigureHeight / 2.0f),
		//										Vector2D(newPosition._x + _stickFigureWidth / 16.0f, newPosition._y - _stickFigureHeight / 2.0f),
		//								        Vector2D(newPosition._x + _stickFigureWidth / 16.0f, newPosition._y + _stickFigureHeight / 2.0f),
		//										Vector2D(newPosition._x - _stickFigureWidth / 16.0f, newPosition._y + _stickFigureHeight / 2.0f) ),
		//		_mass, _velocity, &_contactSurface ) )
		//	{
		//		newPosition = _position + (_velocity * elapsedTime);
		//	}

		//	_position = newPosition;

		//	ServiceLocator::GetGraphicsProvider()->SetDrawablePosition( _renderObjectId, _position._x, _position._y );

		//	// Check to see if we've left prior surface
		//	if( _contactSurface && !_contactSurface->OnSurface( Vector2D(_position._x - _stickFigureWidth / 16.0f, _position._y + _stickFigureHeight / 2.0f) ) &&
		//		                   !_contactSurface->OnSurface( Vector2D(_position._x + _stickFigureWidth / 16.0f, _position._y + _stickFigureHeight / 2.0f) ) )
		//	{
		//		delete _contactSurface;
		//		_contactSurface = NULL;
		//	}

		//	// Determine animation
		//	DetermineAnimationToPlay();

		//	// Update animation
		//	_animationControl.UpdateAnimation( _renderObjectId, elapsedTime );
		//}

		void Update( float elapsedTime );
		void Draw();

	private:
		void DetermineAnimationToPlay();
		virtual void SetInitialState();
		virtual StickFigureState* GetNextState( StickFigureState* currentState, float elapsedTime );
		/* Updates dynamic members (position & velocity) of current state */
		void UpdateCurrentState( float elapsedTime );
		/* Get bounding rectangle for the stick figure for given position (don't just want to use current position, 
		   because we use this for collision detection and that logic needs to detect collisions BEFORE they actually
		   occur. */
		Rectangle GetBoundingRect( Vector2D position );
		/* Wraps the call to Map::ResolveMapCollision which does the collision checking. Need to pass elapsedTime so we can determine the position we'll
		   be after this update, which is the position we need to check (hence, we're doing collision prevention rather than detection). Returns true if 
		   a collision occurred. In addition, if there was a collision, the new velocity and acceleration for the stick figure are computed and returned, 
		   which allows us to determine if we're still falling, sliding down a slope, or have become stationary. */
		bool CheckForCollision( float elapsedTime, Vector2D &newVelocity, Vector2D &newAcceleration );
		/* Computes the future position of the stick figure for the next frame given the current state's velocity & acceleration */
		Vector2D CalculateFuturePosition( float elapsedTime );
		/* Used during falling state to decrease forward velocity to account for reverse momentum */
		void ApplyReverseMomentum( float elapsedTime );
		void ApplyForwardMomentum( float elapsedTime );
		/* Check if stick figure can fall (i.e. is walking on air) */
		bool CanFall( float elapsedTime );

		bool CanMoveRight( float elapsedTime );
		bool CanMoveLeft( float elapsedTime );
		void LogMessage( std::string message );

		void DrawPosition();

		/* State info */
		size_t _renderObjectId;
		AnimationSystem _animationControl;
		Vector2D _renderObjectOffset;
		StickFigureState *_currentState;
		std::ofstream _stickFigureLogger;

		/* Friend declarations */
		friend class AnimationSystem;
	};

}