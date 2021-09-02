#include "FrameTimer.h"

void FrameTimer::init(int fps)
{
	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&timeNow);
	QueryPerformanceCounter(&timePrevious);

	//init fps time info
	requestedFPS = fps;

	//The number of intervals in the given timer, per frame at the requested rate.
	intervalsPerFrame = ((float)timerFreq.QuadPart / requestedFPS);
}

int FrameTimer::framesToUpdate()
{
	numFramesToUpdate = 0;
	QueryPerformanceCounter(&timeNow);

	//getting the delta time
	intervalsSinceLastUpdate = (float)timeNow.QuadPart - (float)timePrevious.QuadPart;
	numFramesToUpdate = (int)( intervalsSinceLastUpdate / intervalsPerFrame );

	//If we are not updating any frames, 
    //keep the old previous timer count

	if (numFramesToUpdate != 0){
		QueryPerformanceCounter(&timePrevious);
	} 

	return numFramesToUpdate;
}
