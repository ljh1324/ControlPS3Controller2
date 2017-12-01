#include <iostream>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;

/* PS3 Contoller
X : dwButtons = 1
O : dwButtons = 2
¡à : dwButtons = 4
¡â : dwButtons = 8
L1 : dwButtons = 16
R1 : dwButtons = 32

Range X Joystick: 1(left) ~ 65535, middle : 32767
Range Y Joystick: 1200(up) ~ 65534, middle : 32250
*/

const int MIDDLE = 32000;
const int THETA = 10000;

enum { X_BUTTON = 1, CIRCLE_BUTTON = 2, SQUARE_BUTTON = 4, TRIANGLE_BUTTON = 8, L1_BUTTON = 16, R1_BUTTON = 32 };
enum { X_INDEX = 0, CIRCLE_INDEX, SQUARE_INDEX, TRIANGLE_INDEX, L1_INDEX, R1_INDEX, UP_INDEX, DOWN_INDEX, LEFT_INDEX, RIGHT_INDEX };

int interval;

int mapping(string key)
{
	if (key.size() == 1)
	{
		if ('a' <= key[0] && key[0] <= 'z')
			key[0] = key[0] - 'a' + 'A';

		return (int)key[0];
	}

	if (key == "LEFT")
		return 37;
	else if (key == "UP")
		return 38;
	else if (key == "RIGHT")
		return 39;
	else if (key == "DOWN")
		return 40;
	else if (key == "SPACE")
		return 32;
	else if (key == "CTRL")
		return 17;
	else if (key == "ALT")
		return 18;
	else if (key == "ENTER")
		return 13;

	return 0;
}

bool inputButton(int* buttons)
{
	string input;

	cout << " -- Please Input Keyboard Key!" << endl;

	cout << endl;
	cout << " LEFT Arrow Key = LEFT" << endl;
	cout << " UP Arrow Key = UP" << endl;
	cout << " RIGHT Arrow Key = RIGHT" << endl;
	cout << " DOWN Arrow Key = DOWN" << endl;
	cout << " CTRL Key = CTRL" << endl;
	cout << " ALT Key = ALT" << endl;
	cout << " SPACE BAR Key = SPACE" << endl;
	cout << " ENTER Key = ENTER" << endl;
	
	cout << endl;

	cout << "X Button Key: ";
	cin >> input;
	buttons[X_INDEX] = mapping(input);

	cout << "O Button Key: ";
	cin >> input;
	buttons[CIRCLE_INDEX] = mapping(input);

	cout << "¡à Button Key: ";
	cin >> input;
	buttons[SQUARE_INDEX] = mapping(input);

	cout << "¡â Button Key: ";
	cin >> input;
	buttons[TRIANGLE_INDEX] = mapping(input);

	cout << "L1 Button Key: ";
	cin >> input;
	buttons[L1_INDEX] = mapping(input);

	cout << "R1 Button Key: ";
	cin >> input;
	buttons[R1_INDEX] = mapping(input);

	cout << "UP Button Key: ";
	cin >> input;
	buttons[UP_INDEX] = mapping(input);

	cout << "DOWN Button Key: ";
	cin >> input;
	buttons[DOWN_INDEX] = mapping(input);

	cout << "LEFT Button Key: ";
	cin >> input;
	buttons[LEFT_INDEX] = mapping(input);

	cout << "RIGHT Button Key: ";
	cin >> input;
	buttons[RIGHT_INDEX] = mapping(input);

	cout << "Interval Time(ms): ";
	cin >> interval;

	return true;
}

bool inputButton(int* buttons, char* file_name)
{
	ifstream is(file_name);
	string input;

	if (!is)
		return false;

	for (int i = X_INDEX; i <= RIGHT_INDEX; ++i)
	{
		is >> input;
		buttons[i] = mapping(input);
	}
	is >> interval;

	is.close();

	return true;
}

inline void processPS3Input(JOYINFOEX joyinfoex, int* buttons)
{
	switch (joyinfoex.dwButtons)
	{
	case X_BUTTON:
		// keybd_event('A', 0, 0, 0);
		// keybd_event('A', 0, KEYEVENTF_KEYUP, 0);
		keybd_event(buttons[X_INDEX], 0, 0, 0);
		Sleep(interval);
		keybd_event(buttons[X_INDEX], 0, KEYEVENTF_KEYUP, 0);
		break;

	case CIRCLE_BUTTON:
		keybd_event(buttons[CIRCLE_INDEX], 0, 0, 0);
		Sleep(interval);
		 keybd_event(buttons[CIRCLE_INDEX], 0, KEYEVENTF_KEYUP, 0);
		break;

	case SQUARE_BUTTON:
		keybd_event(buttons[SQUARE_INDEX], 0, 0, 0);
		Sleep(interval);
		keybd_event(buttons[SQUARE_INDEX], 0, KEYEVENTF_KEYUP, 0);
		break;

	case TRIANGLE_BUTTON:
		keybd_event(buttons[TRIANGLE_INDEX], 0, 0, 0);
		Sleep(interval);
		 keybd_event(buttons[TRIANGLE_INDEX], 0, KEYEVENTF_KEYUP, 0);
		break;

	case L1_BUTTON:
		keybd_event(buttons[L1_INDEX], 0, 0, 0);
		Sleep(interval);
		keybd_event(buttons[L1_INDEX], 0, KEYEVENTF_KEYUP, 0);
		break;

	case R1_BUTTON:
		keybd_event(buttons[R1_INDEX], 0, 0, 0);
		Sleep(interval);
		keybd_event(buttons[R1_INDEX], 0, KEYEVENTF_KEYUP, 0);
		break;
	}

	int x = joyinfoex.dwXpos - MIDDLE;
	int y = joyinfoex.dwYpos - MIDDLE;

	if (x < -THETA)
	{
		keybd_event(buttons[LEFT_INDEX], 0, 0, 0);
		Sleep(interval);
		keybd_event(buttons[LEFT_INDEX], 0, KEYEVENTF_KEYUP, 0);
	}
	else if (x > THETA)
	{
		keybd_event(buttons[RIGHT_INDEX], 0, 0, 0);
		Sleep(interval);
		keybd_event(buttons[RIGHT_INDEX], 0, KEYEVENTF_KEYUP, 0);
	}

	if (y < -THETA)
	{
		keybd_event(buttons[UP_INDEX], 0, 0, 0);
		Sleep(interval);
		keybd_event(buttons[UP_INDEX], 0, KEYEVENTF_KEYUP, 0);
	}
	else if (y > THETA)
	{
		keybd_event(buttons[DOWN_INDEX], 0, 0, 0);
		Sleep(interval);
		keybd_event(buttons[DOWN_INDEX], 0, KEYEVENTF_KEYUP, 0);
	}
}

int main(int argc, char* argv[])
{
	int buttons[10];
	bool flag;

	if (argc == 1)
	{
		flag = inputButton(buttons);
	}
	else if (argc == 2)
	{
		flag = inputButton(buttons, argv[1]);
	}
	else
	{
		cout << "ControlPS3Controller.exe [filename]" << endl;
	}

	if (!flag)
		cout << "[Error] Input Wrong!" << endl;

	cout << " Start To Control PS3 Controller!!" << endl;

	while (true)
	{
		// Sleep(interval);
		unsigned int num_dev = joyGetNumDevs();

		if (0 == num_dev)
		{
			cout << "[ERROR ] num_dev == 0" << endl;
		}


		/* JOYINFOEX */
		// retreiving the joystick values
		JOYINFOEX joyinfoex;
		joyinfoex.dwSize = sizeof(joyinfoex);
		joyinfoex.dwFlags = JOY_RETURNALL;

		MMRESULT joygetposex_result = joyGetPosEx(JOYSTICKID1, &joyinfoex);


		// error always produced
		if (joygetposex_result == JOYERR_PARMS)
		{
			cout << "[ERROR ] JOYERR_PARMS" << endl;
		}

		processPS3Input(joyinfoex, buttons);
		// if (joyinfoex.dwButtons == 1)
		//	cout << "Button" << joyinfoex.dwButtons << endl;
		// if (joyinfoex.dwButtons == 2)
		// {
		//	keybd_event('A', 0, 0, 0);
		//	keybd_event('A', 0, KEYEVENTF_KEYUP, 0);
		//}
		//if (joyinfoex.dwXpos)
		//	cout << "X Pos" << joyinfoex.dwXpos << endl;
		//if (joyinfoex.dwYpos)
		//	std::cout << "Y Pos" << joyinfoex.dwYpos << std::endl;

		// values does not change when playing with the stick
		// std::cout << "joinfoex.dwXpos = " << joyinfoex.dwXpos << std::endl;
		// std::cout << "joinfoex.dwYpos = " << joyinfoex.dwYpos << std::endl;
		// std::cout << "joinfoex.dwButtonNumber = " << joyinfoex.dwButtonNumber << std::endl;
	}
}