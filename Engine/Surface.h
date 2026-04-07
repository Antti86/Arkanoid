/*
 * Surface.h
 * Copyright (C) 2026 Antti Parhiala
 * Licensed under GPL-3.0-or-later. See License.txt.
 */

#pragma once
#include "Colors.h"
#include <string>
#include "Rect.h"

class Surface
{
public:
	Surface(const std::string& filename);
	Surface(int width, int height);
	Surface(const Surface&);
	Surface& operator=(const Surface&);
	~Surface();
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
	RectI GetRect() const;
private:
	Color* pPixels = nullptr;
	int width;
	int height;

};