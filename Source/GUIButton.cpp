#include "GUIButton.h"

#include "Renderer.h"
#include "GUITheme.h"

namespace SGUI
{
	void Button::CleanUp()
	{
		mImageNormal.Release();
		mImagePushed.Release();
		mImageFocus.Release();
		mImageText.Release();
	}

	void Button::PreRender(Renderer& renderer, TextObject::CLIPALIGN align /*= TextObject::CLIPCENTRE*/)
	{
		if (mSize.isZero())
			setSize(preferredSize(renderer));

		mImageNormal.Create(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width(), height());
		renderer.SetRenderTexture(mImageNormal);
		renderer.FillRect(Rect{ Point{0,0}, size() }, mTheme->mButtonGradientTopUnfocused);
		Rect lightRect{ 0, 1, mSize.x, mSize.y - 1 };
		Rect darkRect{ 0, 0, mSize.x, mSize.y - 1 };
		renderer.OutlineRect(lightRect, mTheme->mBorderLight);
		renderer.OutlineRect(darkRect, mTheme->mBorderDark);
		renderer.SetRenderFrameBuffer();

		// Pushed
		mImagePushed.Create(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width(), height());
		renderer.SetRenderTexture(mImagePushed);
		renderer.FillRect(Rect{ Point{ 0,0 }, size() }, mTheme->mButtonGradientTopPushed);
		lightRect = Rect{ 0, 0, mSize.x, mSize.y };
		darkRect = Rect{ 0, 0, mSize.x, mSize.y - 1 };
		renderer.OutlineRect(lightRect, mTheme->mBorderLight);
		renderer.OutlineRect(darkRect, mTheme->mBorderDark);
		renderer.SetRenderFrameBuffer();

		// Focused
		mImageFocus.Create(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width(), height());
		renderer.SetRenderTexture(mImageFocus);
		renderer.FillRect(Rect{ Point{ 0,0 }, size() }, mTheme->mButtonGradientTopFocused);
		lightRect = Rect{ 0, 0, mSize.x, mSize.y };
		darkRect = Rect{ 0, 0, mSize.x, mSize.y - 1 };
		renderer.OutlineRect(lightRect, mTheme->mBorderLight);
		renderer.OutlineRect(darkRect, mTheme->mBorderDark);
		renderer.SetRenderFrameBuffer();


		mImageText.Create(renderer, mTheme->mFontNormal, fontSize(), mTheme->mTextColor);
		mImageText.TextAlign(align, Point{ mImageNormal.GetWidth(), mImageNormal.GetHeight() });
	}

	bool Button::mouseButtonEvent(const Point& p, MouseBut button, bool down, SDL_Keymod modifiers)
	{
		Widget::mouseButtonEvent(p, button, down, modifiers);

		if (button == SGUI::MouseBut::LEFT && mEnabled)
		{
			bool pushedBackup = mPushed;
			if (down)
			{
				mPushed = true;
			}
			else if (mPushed)
			{
				mPushed = false;
				if (contains(p) && mCallback)
					mCallback();
			}
			if (pushedBackup != mPushed && mChangeCallback)
				mChangeCallback(mPushed);

			return true;
		}
		return false;
	}

	void Button::Render(Renderer& renderer, Point& offset)
	{
		if (mImageText.NeedsCreation())
			PreRender(renderer);

		if (mPushed)
			mImagePushed.Render(renderer, 0, 0);
		else if (mMouseFocus && mEnabled)
			mImageFocus.Render(renderer, 0, 0);
		else
			mImageNormal.Render(renderer, 0, 0);

		mImageText.Render(renderer);

		Widget::Render(renderer, offset);
	}

	Point Button::preferredSize(Renderer& renderer) const
	{
		int fontSize = (mFontSize == -1) ? mTheme->mButtonFontSize : mFontSize;
		Point textBounds = TextBounds(mTheme->mFontNormal, fontSize, mImageText.GetText());

		return Point{ textBounds.x + 20, textBounds.y + 10 };
	}
}