#include "StickFigure.h"
#include <cmath>

//#define STICK_STATE_DEBUGGER2

namespace SpriteAnimationTest
{

	/* Class constants */
	const float StickFigure::_jumpVelocity = 195.0f; // pixels per second  -- 115 is good
	const float StickFigure::_walkVelocity = 75.0f; // pixels per second  -- 75 is good
	const float StickFigure::_mass = 15.0f; // in kg

	StickFigure::StickFigure()
	{
		_renderObjectId = ServiceLocator::GetGraphicsProvider()->InitDrawable( "images/StickFigure/StickFigureSpriteSheet.png" );
		ServiceLocator::GetGraphicsProvider()->SetDrawableColor( _renderObjectId, IGraphicsProvider::RGBColor( 0, 0, 0 ) );
		ServiceLocator::GetGraphicsProvider()->SetDrawableCenter( _renderObjectId, _stickFigureWidth / 2.0f, _stickFigureHeight / 2.0f );

		_animationControl.LoadAnimationInfo( "images/StickFigure/AnimationInfo.txt" );

		SetInitialState();
	}

	void StickFigure::MoveTo( float x, float y ) 
	{ 
		ServiceLocator::GetGraphicsProvider()->SetDrawablePosition( _renderObjectId, x, y ); 
	}

	void StickFigure::Update( float elapsedTime )
	{
		StickFigureState *nextState = GetNextState( _currentState, elapsedTime );
		if( nextState == NULL )
		{
			/* If nextState comes back as null, then we're not transitioning to a new state yet, but we do need to update the dynamic members 
			   (position & velocity) of our current state. */
			UpdateCurrentState( elapsedTime );
		}
		else
		{	
			StickFigureState *oldState = _currentState;
			_currentState = nextState; 

#ifdef STICK_STATE_DEBUGGER
			// TEST CODE - log new state
			_stickFigureLogger.open( "stickStateOutput/statelog.txt", std::ofstream::app );
			if( _stickFigureLogger )
				_currentState->OutputState( _stickFigureLogger );
			_stickFigureLogger.clear();
			_stickFigureLogger.close();
			// TEST CODE
#endif

			delete oldState;
			DetermineAnimationToPlay();
		}

		ServiceLocator::GetGraphicsProvider()->SetDrawablePosition( _renderObjectId, _currentState->_position._x, _currentState->_position._y );

		_animationControl.UpdateAnimation( _renderObjectId, elapsedTime );
	}

	void StickFigure::Draw()
	{
		ServiceLocator::GetGraphicsProvider()->DrawDrawable( _renderObjectId, mainWindowId );
	}

	void StickFigure::DetermineAnimationToPlay()
	{
		switch( _currentState->_stateLabel ) 
		{
		case StickFigureState::StateLabel::Idle:
			_animationControl.PlayAnimation( _renderObjectId, "Idle" );
			break;
		case StickFigureState::StateLabel::WalkingRight:
			_animationControl.PlayAnimation( _renderObjectId, "WalkRight" );
			break;
		case StickFigureState::StateLabel::WalkingLeft:
			_animationControl.PlayAnimation( _renderObjectId, "WalkLeft" );
			break;
		case StickFigureState::StateLabel::Jumping:
			_animationControl.PlayAnimation( _renderObjectId, "Jump", false );
			break;
		case StickFigureState::StateLabel::Falling:
			_animationControl.PlayAnimation( _renderObjectId, "Idle" );
			break;
		case StickFigureState::StateLabel::Colliding:
			break;
		default:
			throw std::exception( "StickFigure::DetermineAnimationToPlay() - Unknown state label encountered." );
		}
	}

	void StickFigure::SetInitialState()
	{ 
		_currentState = new StickFigureState( StickFigureState::StateLabel::Falling, 
											  Vector2D( 75.0f, 65.0f) );

#ifdef STICK_STATE_DEBUGGER
		// TEST CODE - log new state
		_stickFigureLogger.open( "stickStateOutput/statelog.txt" );
		if( _stickFigureLogger )
			_currentState->OutputState( _stickFigureLogger );
		_stickFigureLogger.clear();
		_stickFigureLogger.close();
		// TEST CODE
#endif

		ServiceLocator::GetGraphicsProvider()->SetDrawablePosition( _renderObjectId, _currentState->_position._x, _currentState->_position._y ); 

		DetermineAnimationToPlay();
	}

	StickFigureState* StickFigure::GetNextState( StickFigureState* currentState, float elapsedTime )
	{
		/* State transition logic*/

		StickFigureState *nextState;

		switch( currentState->_stateLabel )
		{
			/* IDLE STATE */
		case StickFigureState::StateLabel::Idle:
			{
				/* Check for transition to player movement state */ 
				if( ServiceLocator::GetInputProvider()->IsKeyDown( "right", mainWindowId ) )
				{
					nextState = new StickFigureState( StickFigureState::StateLabel::WalkingRight, currentState->_position, Vector2D( _walkVelocity, 0.0f ) );
					return nextState;
				}
				else if( ServiceLocator::GetInputProvider()->IsKeyDown( "left", mainWindowId ) )
				{
					nextState = new StickFigureState( StickFigureState::StateLabel::WalkingLeft, currentState->_position, Vector2D( -_walkVelocity, 0.0f ) );
					return nextState;
				}
				else if( ServiceLocator::GetInputProvider()->IsKeyDown( "up", mainWindowId ) )
				{
					nextState = new StickFigureState( StickFigureState::StateLabel::Jumping, currentState->_position, 
						currentState->_velocity + Vector2D(0.0f, -_jumpVelocity ) );
					return nextState;
				}
				break;
			}
			/* WALKING RIGHT STATE */
		case StickFigureState::StateLabel::WalkingRight:
			{
				/* Check if we're falling */
				if( CanFall( elapsedTime ) )
				{
					nextState = new StickFigureState( StickFigureState::StateLabel::Falling, currentState->_position, 
						currentState->_velocity / 3.0f );
					return nextState;	
				}

				/* Check if we're hitting a wall */
				if( !CanMoveRight( elapsedTime ) )
				{
					nextState = new StickFigureState( StickFigureState::StateLabel::Idle, currentState->_position );
					return nextState;
				}

				/* Check for transition to idle state */ 
				if( !ServiceLocator::GetInputProvider()->IsKeyDown( "right", mainWindowId ) )
				{
					nextState = new StickFigureState( StickFigureState::StateLabel::Idle, currentState->_position );
					return nextState;
				}

				/* Check if jumping */
				if( ServiceLocator::GetInputProvider()->IsKeyDown( "up", mainWindowId ) )
				{
					nextState = new StickFigureState( StickFigureState::StateLabel::Jumping, currentState->_position, 
						currentState->_velocity + Vector2D(0.0f, -_jumpVelocity ) );
					return nextState;
				}
				break;
			}
			/* WALKING LEFT STATE */
		case StickFigureState::StateLabel::WalkingLeft:
			{
				/* Check if we're falling */
				if( CanFall( elapsedTime ) )
				{
					nextState = new StickFigureState( StickFigureState::StateLabel::Falling, currentState->_position, 
						currentState->_velocity / 3.0f );
					return nextState;	
				}

				/* Check if we're hitting a wall */
				if( !CanMoveLeft( elapsedTime ) )
				{
					nextState = new StickFigureState( StickFigureState::StateLabel::Idle, currentState->_position );
					return nextState;
				}

				/* Check for transition to idle state */ 
				if( !ServiceLocator::GetInputProvider()->IsKeyDown( "left", mainWindowId ) )
				{
					nextState = new StickFigureState( StickFigureState::StateLabel::Idle, currentState->_position );
					return nextState;
				}
				
				/* Check if jumping */
				if( ServiceLocator::GetInputProvider()->IsKeyDown( "up", mainWindowId ) )
				{
					nextState = new StickFigureState( StickFigureState::StateLabel::Jumping, currentState->_position, 
						currentState->_velocity + Vector2D(0.0f, -_jumpVelocity ) );
					return nextState;
				}

				break;
			}
			/* JUMPING STATE */
		case StickFigureState::StateLabel::Jumping:
			{
				/* Check for collision */
				Vector2D newVelocity, newAcceleration;
				bool collisionOccurred = CheckForCollision( elapsedTime, newVelocity, newAcceleration );

				if( collisionOccurred )
				{
					nextState = new StickFigureState( StickFigureState::StateLabel::Colliding, currentState->_position, 
						newVelocity, newAcceleration );
					return nextState;
				}

				/* Check if we've reached the top of the jump arc, in which case we'll transition to the falling state */
				if( CalculateFuturePosition( elapsedTime )._y > _currentState->_position._y )
				{
					nextState = new StickFigureState( StickFigureState::StateLabel::Falling, currentState->_position, 
						currentState->_velocity);
					return nextState;
				}

				ApplyForwardMomentum( elapsedTime );

				//ApplyReverseMomentum( elapsedTime );

				break;
			}
			/* FALLING STATE */
		case StickFigureState::StateLabel::Falling:
			{
				/* Check for collision */
				Vector2D newVelocity, newAcceleration;
				bool collisionOccurred = CheckForCollision( elapsedTime, newVelocity, newAcceleration );

				if( collisionOccurred )
				{
					nextState = new StickFigureState( StickFigureState::StateLabel::Colliding, currentState->_position, 
						newVelocity, newAcceleration );
					return nextState;
				}

#ifdef STICK_STATE_DEBUGGER2
		// TEST CODE - log new state
		_stickFigureLogger.open( "stickStateOutput/statelog.txt", std::ofstream::app );
		if( _stickFigureLogger )
			_currentState->OutputState( _stickFigureLogger );
		_stickFigureLogger.clear();
		_stickFigureLogger.close();
		// TEST CODE
#endif

				//ApplyReverseMomentum( elapsedTime );

				break;
			}
			/* COLLIDING STATE */
		case StickFigureState::StateLabel::Colliding:
			{
				if( _currentState->_acceleration.Magnitude() == 0 )
				{
					/* We collided with a flat surface and now we're stationary, so transition to idle state */
					nextState = new StickFigureState( StickFigureState::StateLabel::Idle, currentState->_position );
					return nextState;
				} 
				else if( _currentState->_acceleration.Magnitude() == ACCELERATION_OF_GRAVITY )
				{
					/* We collided with a vertical or overhead surface, and now we're falling again */
					nextState = new StickFigureState( StickFigureState::StateLabel::Falling, currentState->_position, 
						currentState->_velocity);
					return nextState;
				}
				break;
			}
		default:
			throw std::exception( "StickFigure::GetNextState() - Unknown state label encountered." );
		}

		/* No state transition found so return NULL (indicating we'll remain on the current state) */
		return NULL;
	}

	/* Updates dynamic members (position & velocity) of current state */
	void StickFigure::UpdateCurrentState( float elapsedTime )
	{
		_currentState->_position = _currentState->_position + _currentState->_velocity * elapsedTime + 0.5f * _currentState->_acceleration * pow( elapsedTime, 2 );
		_currentState->_velocity = _currentState->_velocity + _currentState->_acceleration * elapsedTime;
	}

	Rectangle StickFigure::GetBoundingRect( Vector2D position )
	{
		return Rectangle( Vector2D( position._x - _stickFigureWidth / 16.0f, position._y - _stickFigureHeight / 2.0f),
						  Vector2D( position._x + _stickFigureWidth / 16.0f, position._y - _stickFigureHeight / 2.0f),
						  Vector2D( position._x + _stickFigureWidth / 16.0f, position._y + _stickFigureHeight / 2.0f),
						  Vector2D( position._x - _stickFigureWidth / 16.0f, position._y + _stickFigureHeight / 2.0f) );
	}

	bool StickFigure::CheckForCollision( float elapsedTime, Vector2D &newVelocity, Vector2D &newAcceleration )
	{
		float collisionOccurred = false;

		/* Compute future location after this next update and test it to see if it will cause a collision */
		Vector2D newPosition = CalculateFuturePosition( elapsedTime );
		newVelocity = _currentState->_velocity;

		int collisionCount = 0;
		while( GlobalResources::GetCurrentMap()->ResolveMapCollision( GetBoundingRect( newPosition ), _mass, newVelocity, newAcceleration ) && collisionCount < 10 )
		{
			newPosition = _currentState->_position + ( newVelocity * elapsedTime ) + 0.5f * newAcceleration * pow( elapsedTime, 2 );;
			collisionOccurred = true;
			++collisionCount;
		}

		if( collisionCount == 10 )
		{
			std::string message = "Max collisions encountered";
			LogMessage( message );
			//throw std::exception( message.c_str() );
			newVelocity = Vector2D();
		}

		return collisionOccurred;
	}

	Vector2D StickFigure::CalculateFuturePosition( float elapsedTime )
	{
		Vector2D newPosition = _currentState->_position + _currentState->_velocity * elapsedTime 
		+ 0.5f * _currentState->_acceleration * pow( elapsedTime, 2 );
		
		return newPosition;
	}


	/* Check for user pressing directional key opposite direction of travel. We're going to allow this action
	   to decrease the current velocity (i.e. allow stick figure to use reverse momentum to slow down in mid air). */
	void StickFigure::ApplyReverseMomentum( float elapsedTime )
	{
		// safety check, since we're calling surface::Angle() below, and that will throw an error if we call it with a 0 vector
		if( _currentState->_velocity.Magnitude() != 0 )
		{		
			static float momentumSlowCooldown = 0.25f;
			momentumSlowCooldown -= elapsedTime;

			if( _currentState->_velocity.Angle() > 310 && ServiceLocator::GetInputProvider()->IsKeyDown( "left", mainWindowId ) &&
				momentumSlowCooldown < 0 )
			{
				_currentState->_velocity = _currentState->_velocity + Vector2D( -10.0f, 0.0f );
				momentumSlowCooldown = 0.25f;
			} else if( _currentState->_velocity.Angle() < 230 && ServiceLocator::GetInputProvider()->IsKeyDown( "right", mainWindowId ) &&
				momentumSlowCooldown < 0 )
			{
				_currentState->_velocity = _currentState->_velocity + Vector2D( 10.0f, 0.0f );
				momentumSlowCooldown = 0.25f;
			}
		}
	}

	/* Check for user pressing directional key in direction of travel. We're going to allow this action
	   to increase the current velocity (i.e. allow stick figure to use forward momentum to speed up in mid air). */
	void StickFigure::ApplyForwardMomentum( float elapsedTime )
	{
		// safety check, since we're calling surface::Angle() below, and that will throw an error if we call it with a 0 vector
		if( _currentState->_velocity.Magnitude() != 0 )
		{		
			static float momentumThrustCooldown = 0.25f;
			momentumThrustCooldown -= elapsedTime;

			if( ServiceLocator::GetInputProvider()->IsKeyDown( "right", mainWindowId ) &&
				momentumThrustCooldown < 0 )
			{
				_currentState->_velocity = _currentState->_velocity + Vector2D( 10.0f, 0.0f );
				momentumThrustCooldown = 0.25f;
			} else if( ServiceLocator::GetInputProvider()->IsKeyDown( "left", mainWindowId ) &&
				momentumThrustCooldown < 0 )
			{
				_currentState->_velocity = _currentState->_velocity + Vector2D( -10.0f, 0.0f );
				momentumThrustCooldown = 0.25f;
			}
		}
	}

	/* Checks to see if the stick figure can fall. It determines this by accelerating the stick by gravity for the next 5 frames and then checking for a collision.
	   If no collision is found it means it can fall. */
	bool StickFigure::CanFall( float elapsedTime )
	{
		bool canFall = false;

		Vector2D newPosition = _currentState->_position + 0.5f * Vector2D( 0.0f, ACCELERATION_OF_GRAVITY ) * pow( 5 * elapsedTime, 2 );
		
		if( !GlobalResources::GetCurrentMap()->CheckForMapCollision( GetBoundingRect(newPosition) ) )
		{
			canFall = true;
		}

		return canFall;
	}

	/* Checks to see if the stick figure can move right. It determines this by moving stick figure right 1 frame and then checking for a collision.
	   If no collision is found it means it can move right. */
	bool StickFigure::CanMoveRight( float elapsedTime )
	{
		bool canMoveRight = false;

		Vector2D newPosition = _currentState->_position + Vector2D( _walkVelocity, 0.0f) * elapsedTime;
		
		if( !GlobalResources::GetCurrentMap()->CheckForMapCollision( GetBoundingRect(newPosition) ) )
		{
			canMoveRight = true;
		}

		return canMoveRight;
	}

	/* Checks to see if the stick figure can move left. It determines this by moving stick figure left 1 frame and then checking for a collision.
	   If no collision is found it means it can move left. */
	bool StickFigure::CanMoveLeft( float elapsedTime )
	{
		bool canMoveLeft = false;

		Vector2D newPosition = _currentState->_position + Vector2D( -_walkVelocity, 0.0f) * elapsedTime;
		
		if( !GlobalResources::GetCurrentMap()->CheckForMapCollision( GetBoundingRect(newPosition) ) )
		{
			canMoveLeft = true;
		}

		return canMoveLeft;
	}

	void StickFigure::LogMessage( std::string message )
	{
		static bool firstTime = true;
		if( firstTime )
		{
			_stickFigureLogger.open( "logs/log.txt" );
			firstTime = false;
		}
		else
		{
			_stickFigureLogger.open( "logs/log.txt", std::ofstream::app );
		}

		if( _stickFigureLogger )
			_stickFigureLogger << message;
		_stickFigureLogger.close();
	}

	void StickFigure::DrawPosition()
	{
		std::stringstream buffer;
		buffer << "<" << _currentState->_position._x << ", " << _currentState->_position._y << ">";
		
		static size_t positionMessageId = ServiceLocator::GetGraphicsProvider()->InitMessage( buffer.str() );
		ServiceLocator::GetGraphicsProvider()->SetMessage( positionMessageId, buffer.str() );

		ServiceLocator::GetGraphicsProvider()->SetDrawablePosition( positionMessageId, 100.0f, 100.0f );
		
		ServiceLocator::GetGraphicsProvider()->DrawDrawable( positionMessageId );
	}
}