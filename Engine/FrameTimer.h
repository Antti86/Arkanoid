/*
 * FrameTimer.h
 * Copyright (C) 2026 Antti Parhiala
 * Licensed under GPL-3.0-or-later. See License.txt.
 */

#pragma once
#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float Mark();
private:
	std::chrono::steady_clock::time_point last;
};