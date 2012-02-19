#include "SFMLGraphicsProvider.h"

namespace SpriteAnimationTest
{

	size_t SFMLGraphicsProvider::InitWindow( float pixelWidth, float pixelHeight, std::string title )
	{
		sf::RenderWindow *newRenderWnd = new sf::RenderWindow( sf::VideoMode( pixelWidth, pixelHeight ), title );
		_renderWindows[ _objectIdSequence ] = newRenderWnd;

		return _objectIdSequence++;
	}

	void SFMLGraphicsProvider::PrepareWindowForDrawing( size_t windowId )
	{
		std::map< size_t, sf::RenderWindow*>::iterator findResult = _renderWindows.find( windowId );
		if( findResult != _renderWindows.end() )
		{
			// Clear window to white background
			_renderWindows[ windowId ]->Clear( sf::Color(255,255,255) );
		}
	}

	bool SFMLGraphicsProvider::GetEvent( size_t windowId, WindowEvent &aEvent )
	{
		bool foundEvent = false;
		if( ValidWindowId( windowId ) )
		{
			sf::Event currentEvent;
			if( _renderWindows[ windowId ]->GetEvent( currentEvent ) )
			{
				foundEvent = true;
				if( currentEvent.Type == sf::Event::Closed )
				{
					aEvent._event = IGraphicsProvider::WindowEvent::EventType::Closed;
				}
				if( currentEvent.Type == sf::Event::KeyPressed && currentEvent.Key.Code == sf::Key::Escape )
				{
					aEvent._event = IGraphicsProvider::WindowEvent::EventType::KeyPressed;;
					aEvent._keyPressed = "escape";
				}
			}
		}
		return foundEvent;
	}

	float SFMLGraphicsProvider::GetFrameTime( size_t windowId )
	{
		if( ValidWindowId( windowId ) )
		{
			return _renderWindows[ windowId ]->GetFrameTime();
		}
	}

	void SFMLGraphicsProvider::DisplayWindow( size_t windowId )
	{
		if( ValidWindowId( windowId ) )
		{
			_renderWindows[ windowId ]->Display();
		}
	}

	size_t SFMLGraphicsProvider::InitMessage( std::string message )
	{
		sf::String *newMessage = new sf::String( message );
		_drawables[ _objectIdSequence ] = newMessage;

		return _objectIdSequence++;
	}

	size_t SFMLGraphicsProvider::SetMessage( size_t drawableId, std::string message )
	{
		if( ValidDrawableId( drawableId ) )
		{
			sf::String *message = dynamic_cast< sf::String* >( _drawables[ drawableId ] );
			if( message != NULL )
			{
				message->SetText( message );
			}
		}
	}

	size_t SFMLGraphicsProvider::InitDrawable( std::string imageFile )
	{
		sf::Image *sourceImage;
		std::map< std::string, sf::Image* >::iterator findResult = _images.find( imageFile );
		
		if( findResult != _images.end() )
		{
			sourceImage = findResult->second;
		}
		else
		{
			sourceImage = new sf::Image();
			if( !sourceImage->LoadFromFile( imageFile ) )
			{
				// failed to load image file, so return 0 as the object id to indicate failure
				delete sourceImage;
				return 0;
			}
			_images[ imageFile ] = sourceImage;
		}

		sf::Sprite *newSprite = new sf::Sprite( *sourceImage );
		_drawables[ _objectIdSequence ] = newSprite;

		return _objectIdSequence++;
	}

	size_t SFMLGraphicsProvider::InitRectangle( const SpriteAnimationTest::Rectangle &rect, RGBColor color )
	{
		sf::Shape *newRectangle = new sf::Shape();
		newRectangle->AddPoint( rect._topLeft._x, rect._topLeft._y, sf::Color( color._blue, color._green, color._red ) );
		newRectangle->AddPoint( rect._topRight._x, rect._topRight._y, sf::Color( color._blue, color._green, color._red ) );
		newRectangle->AddPoint( rect._bottomRight._x, rect._bottomRight._y, sf::Color( color._blue, color._green, color._red ) );
		newRectangle->AddPoint( rect._bottomLeft._x, rect._bottomLeft._y, sf::Color( color._blue, color._green, color._red ) );

		_drawables[ _objectIdSequence ] = newRectangle;
		
		return _objectIdSequence++;
	}

	size_t SFMLGraphicsProvider::InitRightTriangle( const RightTriangle &rightTriangle, RGBColor color)
	{
		sf::Shape *newRightTriangle = new sf::Shape();
		newRightTriangle->AddPoint( rightTriangle._verticalEndVertex._x, rightTriangle._verticalEndVertex._y, sf::Color( color._blue, color._green, color._red ) );
		newRightTriangle->AddPoint( rightTriangle._ninetyDegreeVertex._x, rightTriangle._ninetyDegreeVertex._y, sf::Color( color._blue, color._green, color._red ) );
		newRightTriangle->AddPoint( rightTriangle._horizontalEndVertex._x, rightTriangle._horizontalEndVertex._y, sf::Color( color._blue, color._green, color._red ) );

		_drawables[ _objectIdSequence ] = newRightTriangle;
		
		return _objectIdSequence++;
	}

	void SFMLGraphicsProvider::SetDrawablePosition( size_t drawableId, float x, float y )
	{
		if( ValidDrawableId( drawableId ) )
		{
			_drawables[ drawableId ]->SetPosition( x, y );
		}
	}	

	Vector2D SFMLGraphicsProvider::GetDrawablePosition( size_t drawableId )
	{
		Vector2D vec;
		if( ValidDrawableId( drawableId ) )
		{
			sf::Vector2f pos = _drawables[ drawableId ]->GetPosition();
			vec._x = pos.x;
			vec._y = pos.y;
		}
		return vec;
	}

	void SFMLGraphicsProvider::SetDrawableColor( size_t drawableId, RGBColor color )
	{
		if( ValidDrawableId( drawableId ) )
		{
			_drawables[ drawableId ]->SetColor( sf::Color( color._red, color._blue, color._green ) );
		}
	}

	void SFMLGraphicsProvider::SetDrawableCenter( size_t drawableId, float x, float y )
	{
		if( ValidDrawableId( drawableId ) )
		{
			_drawables[ drawableId ]->SetCenter( x, y );
		}
	}

	void SFMLGraphicsProvider::MoveDrawable( size_t drawableId, float x, float y )
	{
		if( ValidDrawableId( drawableId ) )
		{
			_drawables[ drawableId ]->Move( x, y );
		}
	}

	void SFMLGraphicsProvider::SetSubRectangle( size_t drawableId, IntRectangle rect )
	{
		if( ValidDrawableId( drawableId ) )
		{
			// Only valid for Sprites, so verify _drawables[ drawableId ] is a pointer to a sprite
			sf::Sprite *temp = dynamic_cast<sf::Sprite*>(_drawables[ drawableId ]);
			if( temp != NULL )
			{
				temp->SetSubRect( sf::IntRect( rect._left, rect._top, rect._right, rect._bottom) );
			}
		}
	}

	IntRectangle SFMLGraphicsProvider::GetSubRectangle( size_t drawableId )
	{
		IntRectangle intRect;
		if( ValidDrawableId( drawableId ) )
		{
			// Only valid for Sprites, so verify _drawables[ drawableId ] is a pointer to a sprite
			sf::Sprite *temp = dynamic_cast<sf::Sprite *>(_drawables[ drawableId ]);
			if( temp != NULL )
			{
				sf::IntRect tempRect = temp->GetSubRect();
				intRect = IntRectangle( tempRect.Left, tempRect.Top, tempRect.Right, tempRect.Bottom );
			}
		}
		return intRect;
	}

	void SFMLGraphicsProvider::DrawDrawable( size_t drawableId, size_t windowId )
	{
		if( ValidDrawableId( drawableId ) && ValidWindowId( windowId ) )
		{
			_renderWindows[ windowId ]->Draw( *_drawables[ drawableId ] );
		}
	}

	virtual void SFMLGraphicsProvider::DestroyDrawable( size_t drawableId )
	{
		if( ValidDrawableId( drawableId ) )
		{
			delete _drawables[ drawableId ];
			_drawables.erase( drawableId );
		}
	}

	bool SFMLGraphicsProvider::ValidWindowId( size_t windowId )
	{
		std::map< size_t, sf::RenderWindow* >::iterator findResult = _renderWindows.find( windowId );
		return findResult != _renderWindows.end();
	}

	bool SFMLGraphicsProvider::ValidDrawableId( size_t drawableId )
	{
		std::map< size_t, sf::Drawable* >::iterator findResult = _drawables.find( drawableId );
		return findResult != _drawables.end();
	}

	const sf::Input& SFMLGraphicsProvider::GetInput( size_t windowId )
	{
		if( ValidWindowId( windowId) )
		{
			return _renderWindows[ windowId ]->GetInput();
		}
	}

}