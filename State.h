#pragma once

#include <iostream>
#include <string>

namespace SpriteAnimationTest
{

	class State
	{
	public:
		virtual void OutputState( std::ostream& outputStream ) = 0;  
	};

}