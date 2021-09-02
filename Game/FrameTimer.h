#include <Windows.h>

#pragma once

class FrameTimer
{
	public:
		void init(int);
		int framesToUpdate();
	
	private:		
		LARGE_INTEGER timerFreq;
		LARGE_INTEGER timeNow;
		LARGE_INTEGER timePrevious;
		int requestedFPS;
		int numFramesToUpdate;
		float intervalsPerFrame;
		float intervalsSinceLastUpdate;
	
};

