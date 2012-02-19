#include "SFMLInputProvider.h"
#include "SFMLGraphicsProvider.h"
#include "ServiceLocator.h"

namespace SpriteAnimationTest
{

	bool SFMLInputProvider::IsKeyDown( std::string key, size_t windowId )
	{
		SFMLGraphicsProvider *graphicsProvider = dynamic_cast< SFMLGraphicsProvider* >( ServiceLocator::GetGraphicsProvider() );
		if( key == "right" )
		{

			return graphicsProvider->GetInput( windowId ).IsKeyDown( sf::Key::Right );
		}
		else if( key == "left" )
		{
			return graphicsProvider->GetInput( windowId ).IsKeyDown( sf::Key::Left );
		}
		else if( key == "up" )
		{
			return graphicsProvider->GetInput( windowId ).IsKeyDown( sf::Key::Up );
		}
		else if( key == "down" )
		{
			return graphicsProvider->GetInput( windowId ).IsKeyDown( sf::Key::Down );
		}

		return false;
	}

}