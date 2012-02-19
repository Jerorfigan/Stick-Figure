#pragma once

#include <vector>
#include "State.h"

namespace SpriteAnimationTest
{

	class IStateTracking
	{
	public:
		virtual void SetInitialState() = 0;
		virtual State* GetNextState( State* currentState ) = 0;
	};

}