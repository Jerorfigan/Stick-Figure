#pragma once

#include <string>

namespace SpriteAnimationTest
{

	class IRealTimeInputProvider
	{
	public:
		virtual bool IsKeyDown( std::string key, size_t windowId = 0 ) = 0;
	};

}