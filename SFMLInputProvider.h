#pragma once

#include "IRealTimeInputProvider.h"

namespace SpriteAnimationTest
{

	/* IMPORTANT: SFML input provider utilizes the SFML graphics provider window, which means SFML wont work for doing input if graphics
	   are being done with something else. */
	class SFMLInputProvider : public IRealTimeInputProvider
	{
	public:
		virtual bool IsKeyDown( std::string key, size_t windowId = 0 );
	};

}