//	Ask the compiler to include minimal header files for our program.
#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES

#include "game.h"
#include "menu.h"

//
//#define WINDOW_CLASS_NAME "Ping Pang"
//#define WINDOWWIDTH 800
//#define WINDOWHEIGHT 600

using namespace std;

//	use int main if you want to have a console to print out message
//int main()

//	use WinMain if you don't want the console
//hInstance = ID number of the instance of this window
//hPrevInstance = ID number of the instance of the PARENT of this window (OBSOLETE)
//lp CmdLine = POINTER to a command line string
//nShowCmd = style

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	game pang;

	pang.init("Ping Pang", 800, 600);

	pang.changeState(menu::instance());

	while (pang.running()) {
		pang.getInput();
		pang.update();
		pang.render();
		pang.playSound();
	}

	pang.cleanup();
}