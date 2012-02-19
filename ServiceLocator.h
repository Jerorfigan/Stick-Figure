#pragma once

#include "IGraphicsProvider.h"
#include "IRealTimeInputProvider.h"

namespace SpriteAnimationTest
{

	class ServiceLocator
	{
	public:
		static void SetGraphicsProvider( IGraphicsProvider* aGraphicsProvider ) { _graphicsProvider = aGraphicsProvider; }
		static IGraphicsProvider* GetGraphicsProvider() { return _graphicsProvider; }

		static void SetInputProvider( IRealTimeInputProvider* aInputProvider ) { _inputProvider = aInputProvider; }
		static IRealTimeInputProvider* GetInputProvider() { return _inputProvider; }

	private:
		static IGraphicsProvider *_graphicsProvider;
		static IRealTimeInputProvider *_inputProvider;
	};

}
