#include "StickFigureState.h"
#include "GlobalConstants.h"

namespace SpriteAnimationTest
{

	/* Initializes StickFigureState from a pre-defined label. Only dynamic state info (velocity/position/acceleration) need be passed. */
	StickFigureState::StickFigureState( StateLabel stateLabel, Vector2D position, Vector2D velocity, Vector2D acceleration )
	{
		switch( stateLabel )
		{
		case Idle:
			StickFigureStateInitializer( Idle, position, velocity, acceleration, true, false );
			break;
		case WalkingRight:
			StickFigureStateInitializer( WalkingRight, position, velocity, acceleration, true, false );
			break;
		case WalkingLeft:
			StickFigureStateInitializer( WalkingLeft, position, velocity, acceleration, false, false );
			break;
		case Jumping:
			StickFigureStateInitializer( Jumping, position, velocity, Vector2D( 0.0f, ACCELERATION_OF_GRAVITY ) , false, false );
			break;
		case Falling:
			StickFigureStateInitializer( Falling, position, velocity, Vector2D( 0.0f, ACCELERATION_OF_GRAVITY ) , false, false );
			break;
		case Colliding:
			StickFigureStateInitializer( Colliding, position, velocity, acceleration , false, false );
			break;
		default:
			throw std::exception( "StickFigureState::StickFigureState() - Unknown state label passed." );
		}
	}

	/* Auxiliary initializer for StickFigureState */
	void StickFigureState::StickFigureStateInitializer( StateLabel stateLabel, Vector2D position, Vector2D velocity, Vector2D acceleration, 
										bool facingRight, bool isDying ) 
	{
	    _stateLabel = stateLabel; 
		_position = position;
		_velocity = velocity; 
		_acceleration = acceleration;
		_facingRight = facingRight;
		_isDying = isDying; 
	}

	void StickFigureState::OutputState( std::ostream& outputStream )
	{
		std::string stateLabelString;
		switch( _stateLabel )
		{
		case 0:
			stateLabelString = "Idle";
			break;
		case 1:
			stateLabelString = "WalkingRight";
			break;
		case 2:
			stateLabelString = "WalkingLeft";
			break;
		case 3:
			stateLabelString = "Jumping";
			break;
		case 4:
			stateLabelString = "Falling";
			break;
		case 5:
			stateLabelString = "Colliding";
			break;
		}
		outputStream << "State label: " << stateLabelString << std::endl;
		outputStream << "Position: " << _position << std::endl;
		outputStream << "Velocity: " << _velocity << std::endl;
		outputStream << "Acceleration: " << _acceleration << std::endl;
		outputStream << "Facing Right? " << _facingRight << std::endl;
		outputStream << "Is Dying? " << _isDying << std::endl;
	}

}