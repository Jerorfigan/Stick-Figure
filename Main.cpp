#include "SFMLGraphicsProvider.h"
#include "SFMLInputProvider.h"
#include "ServiceLocator.h"

#include "Map.h"
#include "StickFigure.h"
#include "GlobalResources.h"

#include "StickFigureState.h"

size_t mainWindowId;

int main()
{
	SpriteAnimationTest::SFMLGraphicsProvider graphicsSystem;
	SpriteAnimationTest::ServiceLocator::SetGraphicsProvider( &graphicsSystem );

	// IMPORTANT: doing input with SFML is contingent on doing graphics with SFML as well
	SpriteAnimationTest::SFMLInputProvider inputSystem;
	SpriteAnimationTest::ServiceLocator::SetInputProvider( &inputSystem );

	mainWindowId = SpriteAnimationTest::ServiceLocator::GetGraphicsProvider()->InitWindow( 800, 600, "Main Window" );

	SpriteAnimationTest::Map testMap( "maps/TestMap.txt" );
	SpriteAnimationTest::GlobalResources::SetCurrentMap( &testMap );

	SpriteAnimationTest::StickFigure stickman;

	bool quit = false;
	while( !quit )
	{
		SpriteAnimationTest::IGraphicsProvider::WindowEvent aEvent;
		while( SpriteAnimationTest::ServiceLocator::GetGraphicsProvider()->GetEvent( mainWindowId, aEvent ) )
		{
			if( aEvent._event == SpriteAnimationTest::IGraphicsProvider::WindowEvent::Closed ) quit = true;

			if( aEvent._event == SpriteAnimationTest::IGraphicsProvider::WindowEvent::KeyPressed)
			{
				if( aEvent._keyPressed == "escape" ) quit = true;
			}
		}
		// Update game state
		stickman.Update( SpriteAnimationTest::ServiceLocator::GetGraphicsProvider()->GetFrameTime( mainWindowId ) );

		// Draw game state
		SpriteAnimationTest::ServiceLocator::GetGraphicsProvider()->PrepareWindowForDrawing( mainWindowId );

		SpriteAnimationTest::GlobalResources::GetCurrentMap()->Draw();
		stickman.Draw();

		SpriteAnimationTest::ServiceLocator::GetGraphicsProvider()->DisplayWindow( mainWindowId );
	}

	return EXIT_SUCCESS;
}