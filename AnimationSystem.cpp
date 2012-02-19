#include "AnimationSystem.h"
#include "ServiceLocator.h"
#include <fstream>
#include <sstream>

namespace SpriteAnimationTest
{

	void AnimationSystem::LoadAnimationInfo( std::string animationFile )
	{
		std::ifstream input( animationFile.c_str() );
		if( !input )
		{
			throw std::exception("AnimationSystem::LoadSpriteSheet - Sprite sheet file could not be opened");
		}

		std::string lineBuffer;
		std::string animationName;
		float duration;
		int left, top, right, bottom;
		std::vector< std::pair< float, IntRectangle > > animationRects;

		while( getline( input, lineBuffer) )
		{
			if( lineBuffer[0] == '#' )
				continue;

			std::istringstream tokens( lineBuffer );
			tokens >> animationName >> duration >> left >> top >> right >> bottom;

			if( !tokens ) 
			{
				throw std::exception("AnimationSystem::LoadSpriteSheet - Bad format encountered in sprite sheet");
			}

			animationRects.push_back( std::make_pair( duration, IntRectangle( left, top, right, bottom ) ) ); 
			while( tokens >> duration )
			{
				tokens >> left >> top >> right >> bottom;

				if( !tokens ) 
				{
					throw std::exception("AnimationSystem::LoadSpriteSheet - Bad format encountered in sprite sheet");
				}

				animationRects.push_back( std::make_pair( duration, IntRectangle( left, top, right, bottom ) ) ); 
			}

			_spriteRects[ animationName ] = animationRects;
			animationRects.clear();
		}
	}

	void AnimationSystem::PlayAnimation( size_t renderObjectId, std::string animationName, bool loopIt )
	{ 
		if( _currentAnimation != animationName )
		{
			// Set animationState
			_currentAnimation = animationName; 

			// Set sub rect for sprite to first frame of animation
			ServiceLocator::GetGraphicsProvider()->SetSubRectangle( renderObjectId, (_spriteRects[ _currentAnimation ])[0].second );

			_currentFrameDuration = (_spriteRects[ _currentAnimation ])[0].first;

			_loopCurrentAnimation = loopIt;
		}
	}

	void AnimationSystem::UpdateAnimation( size_t renderObjectId, float elapsedTime )
	{
		_currentFrameDuration -= elapsedTime;

		if( _currentFrameDuration <= 0 )
		{
			// time to update animation frame to new frame, so get vector of sprite rects for this animation
			std::vector< std::pair< float, IntRectangle> > currentAnimationRects = _spriteRects[ _currentAnimation ];

			// Find the current sprite rectangle being used and update it to the next one (also handle wrap around if looping)
			for( std::vector< std::pair< float, IntRectangle> >::iterator citr = currentAnimationRects.begin(); 
				 citr != currentAnimationRects.end(); ++citr )
			{
				if( (*citr).second._left == ServiceLocator::GetGraphicsProvider()->GetSubRectangle( renderObjectId )._left && 
					(*citr).second._right == ServiceLocator::GetGraphicsProvider()->GetSubRectangle( renderObjectId )._right &&
					(*citr).second._top == ServiceLocator::GetGraphicsProvider()->GetSubRectangle( renderObjectId )._top && 
					(*citr).second._bottom == ServiceLocator::GetGraphicsProvider()->GetSubRectangle( renderObjectId )._bottom )
				{
					if( citr + 1 == currentAnimationRects.end() )
					{
						if( _loopCurrentAnimation )
						{
							ServiceLocator::GetGraphicsProvider()->SetSubRectangle( renderObjectId, currentAnimationRects[0].second );
							_currentFrameDuration = currentAnimationRects[0].first;
						}
					}
					else
					{
						ServiceLocator::GetGraphicsProvider()->SetSubRectangle( renderObjectId, (citr + 1)->second );
						_currentFrameDuration = (citr + 1)->first;
					}
					break;
				}
			}
		}
	}

}