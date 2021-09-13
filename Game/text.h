#pragma once
#include <d3d9.h>
#include <d3dx9.h>
class text
{
public:
	RECT rect;
	LPD3DXFONT d3dFont = NULL;
	LPD3DXLINE line = NULL;
	int fontSize = 1;
	int textSize = 1;

	LPCSTR fontStyle; 
	LPCSTR content;

	int red = 255;
	int green = 255;
	int blue = 255;

	
};

