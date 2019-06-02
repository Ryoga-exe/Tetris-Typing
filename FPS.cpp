#include <math.h>
#include "DxLib.h"

static int mStartTime;
static int mCount;
static float mFps;
static const int N = 60;
static const int FPS = 60;

bool FPSUpdate() {
	if (mCount == 0)
		mStartTime = GetNowCount();
	if (mCount == N) {
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void DrawFPSRate(int x, int y, unsigned int _font_color) {
	DrawFormatString(x, y, _font_color, "%.1f", mFps);
}

void Wait() {
	int tookTime = GetNowCount() - mStartTime;
	int waitTime = mCount * 1000 / FPS - tookTime;
	if (waitTime > 0)
		Sleep(waitTime);
}