/*
 * FrameTimer.cpp
 * Copyright (C) 2026 Antti Parhiala
 * Licensed under GPL-3.0-or-later. See License.txt.
 */
#include "FrameTimer.h"

using namespace std::chrono;

FrameTimer::FrameTimer()
{
	last = steady_clock::now();
}

float FrameTimer::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}
