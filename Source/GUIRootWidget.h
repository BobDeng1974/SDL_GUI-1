#pragma once

//#include "Texture.h"
//#include "Font_TTF.h"

//#include "Common.h"
//
#include "GUIWidget.h"
#include "TimeKeeper.h"
#include "TextObject.h"
#include "Common.h"

namespace SGUI
{
	class RootWidget : public Widget
	{
	public:
		RootWidget();
		~RootWidget() { StopUnicodeEvents(); }

		bool GUIEventHandler(SDL_Event& Event);

		virtual void Render(Renderer& renderer, Point& offset) override;

		virtual bool mouseButtonEvent(const Point& p, MouseBut button, bool down, Keymod modifiers) override;

		void updateFocus(Widget* widget);

		bool keyboardEvent(Scancode scan, Keycode key, bool down, Keymod modifiers) override;

		bool keyboardCharacterEvent(const std::string& codepoint) override;

		bool mouseMotionEvent(const Point& p, const Point& rel, MouseButStatus buttons, Keymod modifiers) override;

		void DrawFocusedWidgetTooltip(Renderer& renderer, double elapsed, Point& offset);

	private:
		Widget* mDragWidget{ nullptr };
		Widget* mFocusWidget{ nullptr };
		bool	mDragActive{ false };

		TextObject mTooltipText;

		std::vector<Widget*> mFocusPath;

		double mLastInteraction{ 0.0 };
		TimeKeeper mTimer;
	};

}

