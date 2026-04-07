/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
// Edited by Antti Parhiala, 2026
#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"
#include "Rect.h"
#include "Vec2.h"
#include "Surface.h"
#include <cassert>

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel( int x,int y,Color c );
	Color GetPixel(int x, int y) const;
	template<typename E>
	void DrawSprite(Vei2& pos, const Surface& s, E effect)
	{
		DrawSprite(pos, s.GetRect(), s, effect);
	}
	template<typename E>
	void DrawSprite(Vei2& pos, const RectI& srcRect, const Surface& s, E effect)
	{
		DrawSprite(pos, srcRect, GetScreenRect(), s, effect);
	}
	template<typename E>
	void DrawSprite(Vei2& pos, RectI srcRect, const RectI& clip, const Surface& s, E effect)
	{
		assert(srcRect.left >= 0);
		assert(srcRect.right <= s.GetWidth());
		assert(srcRect.top >= 0);
		assert(srcRect.bottom <= s.GetHeight());

		if (pos.x < clip.left)
		{
			srcRect.left += clip.left - pos.x;
			pos.x = clip.left;
		}
		if (pos.y < clip.top)
		{
			srcRect.top += clip.top - pos.y;
			pos.y = clip.top;
		}
		if (pos.x + srcRect.GetWidth() > clip.right)
		{
			srcRect.right -= pos.x + srcRect.GetWidth() - clip.right;
		}
		if (pos.y + srcRect.GetHeight() > clip.bottom)
		{
			srcRect.bottom -= pos.y + srcRect.GetHeight() - clip.bottom;
		}

		for (int sy = srcRect.top; sy < srcRect.bottom; sy++)
		{
			for (int sx = srcRect.left; sx < srcRect.right; sx++)
			{
				effect
				(
					s.GetPixel(sx, sy),
					Vei2((pos.x + sx - srcRect.left),
					(pos.y + sy - srcRect.top)),
					*this
				);
			}
		}
	}

	void DrawRect(int x0,int y0,int x1,int y1,Color c );
	void DrawRect(const RectF& rect, Color c);

	template<typename S>
	void DrawRectSpacec(S x0, S y0, S x1, S y1, Color c)
	{
		for (auto y = y0; y < y1; y++)
		{
			for (auto x = x0; x < x1; x++)
			{
				PutPixel((int)x, (int)y, c);
				x++;
			}
		}
	}
	template<typename S>
	void DrawRectSpacec(const Rect_<S>& rect, Color c)
	{
		DrawRectSpacec(rect.left, rect.top, rect.right, rect.bottom, c);
	}

	void DrawCircle( int x,int y,int radius,Color c );
	void DrawCircle(const Vec2& pos, int radius, Color c);

	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;
public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
	static RectI GetScreenRect();
};