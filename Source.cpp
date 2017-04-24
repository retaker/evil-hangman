#include <iostream>
#include "SDL_Plotter.h"
#include "Graphics.h"

using namespace std;

int main(int argc, char **argv) 
{
	SDL_Plotter background;
	loadFont("font.txt");
	DefaultScreen(background);
	background.update();

	int level= 4;
	bool MusicOn = true;
	int mousePointer = 1;
	bool inMainMenu = false;
	bool GameStarted = false;
	bool InSubMenu = false;
	while (!background.getQuit()) {
		if (background.kbhit()) {
			background.getKey();

			if (background.getKey() != '\0')
			{
				if (inMainMenu == false) {
					background.clear();
					MainMenu(background, level, MusicOn, mousePointer);
					background.update();
					inMainMenu == true;
				}
				
				//mousepointer part
				if (background.getKey() == DOWN_ARROW)
				{
					if (mousePointer > 0 && mousePointer < 5) {
						mousePointer++;
						background.clear();
						MainMenu(background, level, MusicOn, mousePointer);
						background.update();
					}
					else 
					{
						background.clear();
						MainMenu(background, level, MusicOn, mousePointer);
						background.update();
					}
				}
				else if (background.getKey() == UP_ARROW) 
				{
					if (mousePointer > 1 && mousePointer < 6) {
						mousePointer--;
						background.clear();
						MainMenu(background, level, MusicOn, mousePointer);
						background.update();
					}
					else 
					{
						background.clear();
						MainMenu(background, level, MusicOn, mousePointer);
						background.update();
					}
				}
				//level control part
				else if (background.getKey()==LEFT_ARROW)
				{
					if (mousePointer == 2) 
					{
						if (level >=5) 
						{
							level--;
							background.clear();
							MainMenu(background, level, MusicOn, mousePointer);
							background.update();
						}
						else 
						{
							background.clear();
							MainMenu(background, level, MusicOn, mousePointer);
							background.update();
						}
					}
					//sound control
					else if (mousePointer == 3) 
					{
						if (MusicOn == true) {
							MusicOn = false;
							background.clear();
							MainMenu(background, level, MusicOn, mousePointer);
							background.update();
						}

						else if (MusicOn == false) {
							MusicOn = true;
							background.clear();
							MainMenu(background, level, MusicOn, mousePointer);
							background.update();
						}
					}
				}
				else if (background.getKey() == RIGHT_ARROW)
				{
					if (mousePointer == 2)
					{
						if (level < 6) 
						{
							level++;
							background.clear();
							MainMenu(background, level, MusicOn, mousePointer);
							background.update();
						}
					}
					//sound control
					else if (mousePointer == 3) 
					{
						if (MusicOn == true) {
							MusicOn = false;
							background.clear();
							MainMenu(background, level, MusicOn, mousePointer);
							background.update();
						}
						else if (MusicOn == false) {
							MusicOn = true;
							background.clear();
							MainMenu(background, level, MusicOn, mousePointer);
							background.update();
						}
					}
				}
				//if user typing enter at default window.
				else if (background.getKey() == SDL_SCANCODE_RETURN&&inMainMenu == false)
				{
					inMainMenu = true;
				}
				else if (background.getKey() == SDL_SCANCODE_RETURN&&inMainMenu == true)
				{
					if (mousePointer == 1) 
					{
						background.clear();
						GamingScreen(background,level);
						background.update();
						GameStarted = true;
					}
					else if (mousePointer == 4) 
					{
						background.clear();
						ScoreBoard(background);
						background.update();
						InSubMenu = true;
					}
					else if (mousePointer == 5) 
					{
						background.getQuit();
					}
					else {
					}
				}
				//back to mainMenu from gaming window
				else if (background.getKey() == '1') 
				{
					if (GameStarted == true||InSubMenu==true) 
					{
						background.clear();
						MainMenu(background, level, MusicOn, mousePointer);
						background.update();
						GameStarted == false;
						InSubMenu == false;
					}
					else {}
				}
			}
		}
	}
	return 0;
}

