#pragma once

#include <string>
#include "State.h"
#include "Vector2D.h"

namespace SpriteAnimationTest
{

	class StickFigureState : public State
	{
	public:
		enum StateLabel { Idle, WalkingRight, WalkingLeft, Jumping, Falling, Colliding };

		StickFigureState( StateLabel, Vector2D position, Vector2D velocity = Vector2D(), Vector2D acceleration = Vector2D() );

		virtual void OutputState( std::ostream& outputStream );  

		StateLabel _stateLabel;
		Vector2D _position;
		Vector2D _velocity;
		Vector2D _acceleration;
		bool _facingRight;
		bool _isDying;

	private:
		/* Auxiliary function called from main constructor */
		void StickFigureStateInitializer( StateLabel stateLabel, Vector2D position, Vector2D velocity, Vector2D acceleration, 
										bool facingRight, bool isDying );
	};

}