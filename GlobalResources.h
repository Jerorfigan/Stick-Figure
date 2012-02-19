#pragma once

#include "Map.h"

namespace SpriteAnimationTest
{

	class GlobalResources
	{
	public:
		static Map* GetCurrentMap() { return _currentMap; }
		static void SetCurrentMap( Map* newMap ) { _currentMap = newMap; };

	private:
		static Map *_currentMap;
	};

}