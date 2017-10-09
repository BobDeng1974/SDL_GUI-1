#ifndef Texture_h__
#define Texture_h__
#pragma once

#include <string>
#include <memory>
#include <SDL.h>

class Renderer;
class FontTTF;

class Texture
{
public:
	Texture();
	~Texture() noexcept;

	void Release();
	SDL_Texture* GetPtr() { return m_pTexture; }
	bool isNull() const { return m_pTexture == nullptr; }

	void Render(Renderer& renderer, int x, int y) const;
	void RenderStretch(Renderer& renderer, SDL_Rect* pDestRect = nullptr) const;

	void SetClipRect(const SDL_Rect& rect) { m_ClipRect = rect; }
	void SetDefaultClipRect() { m_ClipRect = SDL_Rect{0,0,m_Width,m_Height}; }

	bool Create(Renderer& renderer, Uint32 format, int access, int w, int h);

	bool CreateFromFile(Renderer& renderer, std::string filename);

	bool CreateFromText(Renderer& renderer, std::string text, FontTTF& font);
	bool CreateFromText_Fast(Renderer& renderer, std::string text, FontTTF& font);

	bool CreateFromSurface(SDL_Surface* textSurface, Renderer &renderer);

	void SetAlphaBlend() { SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND); }

	int GetHeight() const { return m_Height; }
	int GetWidth() const { return m_Width; }

private:
	SDL_Texture*	m_pTexture = nullptr;
	SDL_Rect		m_ClipRect{0,0,0,0};
	int m_Width = 0;
	int m_Height = 0;
};

#endif // Texture_h__