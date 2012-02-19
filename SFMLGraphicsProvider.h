#pragma once

#include <map>
#include "SFML\Graphics.hpp"
#include "IGraphicsProvider.h"
#include "Vector2D.h"

namespace SpriteAnimationTest
{

	class SFMLGraphicsProvider : public IGraphicsProvider
	{
	public:
		SFMLGraphicsProvider(): _objectIdSequence(1) {}

		virtual size_t InitWindow( float pixelWidth, float pixelHeight, std::string title="" );
		virtual void PrepareWindowForDrawing( size_t windowId );
		virtual bool GetEvent( size_t windowId, WindowEvent &aEvent );
		virtual float GetFrameTime( size_t windowId );
		virtual void DisplayWindow( size_t windowId );

		virtual size_t InitMessage( std::string message );
		virtual size_t SetMessage( size_t drawableId, std::string message );
		virtual size_t InitDrawable( std::string imageFile );
		virtual size_t InitRectangle( const SpriteAnimationTest::Rectangle &rect, RGBColor color );
		virtual size_t InitRightTriangle( const RightTriangle &rightTriangle, RGBColor color);
		virtual void SetDrawablePosition( size_t drawableId, float x, float y );
		virtual Vector2D GetDrawablePosition( size_t drawableId );
		virtual void SetDrawableColor( size_t drawableId, RGBColor color );
		virtual void SetDrawableCenter( size_t drawableId, float x, float y );
		virtual void MoveDrawable( size_t drawableId, float x, float y );
		virtual void SetSubRectangle( size_t drawableId, IntRectangle rect );
		virtual IntRectangle GetSubRectangle( size_t drawableId );
		virtual void DrawDrawable( size_t drawableId, size_t windowId );
		virtual void DestroyDrawable( size_t drawableId );

	private:
		bool ValidWindowId( size_t windowId );
		bool ValidDrawableId( size_t drawableId );
		const sf::Input& GetInput( size_t windowId );

		std::map< size_t, sf::RenderWindow* > _renderWindows;
		std::map< size_t, sf::Drawable* > _drawables;
		std::map< std::string, sf::Image* > _images;
		size_t _objectIdSequence;

		friend class SFMLInputProvider;
	};

}