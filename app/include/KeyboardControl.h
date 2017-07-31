#pragma once
#include <GL/glew.h>

static void InitializeGlutCallbacks();
static void InitGLContext();

class KeyboardControl
{
private:
	bool keyup;
	bool keydown;
	bool keyleft;
	bool keyright;
	bool windowed;
public:
	KeyboardControl()
	{
		keyup = false;
		keydown = false;
		keyleft = false;
		keyright = false;
		windowed = true;
	}

	bool KeyUp()
	{
		return keyup;
	}
	bool KeyDown()
	{
		return keydown;
	}
	bool KeyLeft()
	{
		return keyleft;
	}
	bool KeyRight()
	{
		return keyright;
	}
	bool Windowed()
	{
		return windowed;
	}

	void SpecialKeyboard_KeyDown(int Key, int x, int y)
	{
		switch (Key)
		{
		case GLUT_KEY_UP:
		{
			keyup = true;
			break;
		}
		case GLUT_KEY_DOWN:
		{
			keydown = true;
			break;
		}
		case GLUT_KEY_LEFT:
		{
			keyleft = true;
			break;
		}
		case GLUT_KEY_RIGHT:
		{
			keyright = true;
			break;
		}
		}
	}

	void SpecialKeyboard_KeyUp(int Key, int x, int y)
	{
		switch (Key)
		{
		case GLUT_KEY_UP:
		{
			keyup = false;
			break;
		}
		case GLUT_KEY_DOWN:
		{
			keydown = false;
			break;
		}
		case GLUT_KEY_LEFT:
		{
			keyleft = false;
			break;
		}
		case GLUT_KEY_RIGHT:
		{
			keyright = false;
			break;
		}
		}
	}

	void Keyboard_KeyDown(unsigned char Key, int x, int y)
	{
		switch (Key)
		{
		case 'W':
		case 'w':
		{
			keyup = true;
			break;
		}
		case 'S':
		case 's':
		{
			keydown = true;
			break;
		}
		case 'A':
		case 'a':
		{
			keyleft = true;
			break;
		}
		case 'D':
		case 'd':
		{
			keyright = true;
			break;
		}
		case 13:
		{

			if (windowed)
			{
				//fullscreen
				glutGameModeString("1280x1024:32@60");
				if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
				{
					windowed = false;
					glutEnterGameMode();
					InitializeGlutCallbacks();
					InitGLContext();
				}
			}
			else
			{
				//windowed
				windowed = true;
				glutLeaveGameMode();
				glutSetWindow(1);
				glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
			}
			break;
		}
		case 27:
		{
			exit(0);
		}
		}
	}

	void Keyboard_KeyUp(unsigned char Key, int x, int y)
	{
		switch (Key) {
		case 'W':
		case 'w':
		{
			keyup = false;
			break;
		}
		case 'S':
		case 's':
		{
			keydown = false;
			break;
		}
		case 'A':
		case 'a':
		{
			keyleft = false;
			break;
		}
		case 'D':
		case 'd':
		{
			keyright = false;
			break;
		}
		}
	}
};