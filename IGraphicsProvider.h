#pragma once

#include <string>
#include "Vector2D.h"
#include "IntRectangle.h"
#include "Rectangle.h"
#include "RightTriangle.h"

namespace SpriteAnimationTest
{

	class IGraphicsProvider
	{
	public:
		struct RGBColor
		{ 
			RGBColor( unsigned char red, unsigned char blue, unsigned char green ): _red(red), _blue(blue), _green(green) {}
			unsigned char _red;
			unsigned char _blue;
			unsigned char _green;
		};
		struct WindowEvent
		{
			enum EventType {Closed, KeyPressed};
			EventType _event;
			std::string _keyPressed;
		};
		/* Window Logic */

		/* Initializes a window for rendering graphics.
		   Params:
			pixelWidth ~ A float representing the width of the window to create in pixels.
			pixelHeight ~ A float representing the height of the window to create in pixels.
			title ~ The title to give to the created window (optional).
		   Returns: A size_t containing the ID of the created window. */
		virtual size_t InitWindow( float pixelWidth, float pixelHeight, std::string title="" ) = 0;
		virtual void PrepareWindowForDrawing( size_t windowId ) = 0;
		virtual bool GetEvent( size_t windowId, WindowEvent &aEvent ) = 0;
		virtual float GetFrameTime( size_t windowId ) = 0;
		virtual void DisplayWindow( size_t windowId ) = 0;

		/* Drawable logic */
		virtual size_t InitMessage( std::string message ) = 0;
		virtual size_t SetMessage( size_t drawableId, std::string message ) = 0;
		virtual size_t InitDrawable( std::string imageFile ) = 0;
		virtual size_t InitRectangle( const SpriteAnimationTest::Rectangle &rectangle, RGBColor color ) = 0;
		virtual size_t InitRightTriangle( const RightTriangle &rightTriangle, RGBColor color ) = 0;
		virtual void SetDrawablePosition( size_t drawableId, float x, float y ) = 0;
		virtual Vector2D GetDrawablePosition( size_t drawableId ) = 0;
		virtual void SetDrawableColor( size_t drawableId, RGBColor color ) = 0;
		virtual void SetDrawableCenter( size_t drawableId, float x, float y ) = 0;
		virtual void MoveDrawable( size_t drawableId, float x, float y ) = 0;
		virtual void SetSubRectangle( size_t drawableId, IntRectangle rect ) = 0;
		virtual IntRectangle GetSubRectangle( size_t drawableId ) = 0;
		virtual void DrawDrawable( size_t drawableId, size_t windowId ) = 0;
		virtual void DestroyDrawable( size_t drawableId ) = 0;
	};

}