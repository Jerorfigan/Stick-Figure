#pragma once

#include <map>
#include <vector>
#include <string>
#include <utility>
#include "IntRectangle.h"

namespace SpriteAnimationTest
{

class AnimationSystem
{
public:
	AnimationSystem() : _currentFrameDuration(0), _currentAnimation("None"), _loopCurrentAnimation(false) {}

	void LoadAnimationInfo( std::string animationFile );
	void PlayAnimation( size_t renderObjectId, std::string animationName, bool loopIt = true );
	void UpdateAnimation( size_t renderObjectId, float elapsedTime );

private:
	std::map< std::string, std::vector< std::pair< float, IntRectangle > > > _spriteRects;
	float _currentFrameDuration;
	std::string _currentAnimation;
	bool _loopCurrentAnimation;
};

}