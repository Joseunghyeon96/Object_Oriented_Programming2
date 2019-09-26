// Screen.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.

//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <conio.h>

#include <Windows.h>
#include <time.h>
#include "Utils.h"
using namespace std;

struct gameObject {
	char shape = '.';
	char mineShape = 'X';
	int mineCount = 0;
	bool mine=false;
	bool open=false;
};

class Screen {

	int width;
	int height;
	gameObject* canvas;
	static Screen* instance;

	Screen(int width = 70, int height = 25)

		: width(width), height(height)

		,canvas(new  gameObject[(width + 1)*height])



	{

		Borland::initialize();

	}

public:

	static Screen& getInstance() {

		if (instance == nullptr) {

			instance = new Screen();

		}

		return *instance;

	}

	~Screen() {

		if (instance) {

			delete[] canvas;

			instance = nullptr;

		}

	}

	void render()

	{

		Borland::gotoxy(0, 0);

		for (int i = 0; i < (width + 1)*height; i++) {

			if (canvas[i].shape == '0') canvas[i].shape = ' ';
			cout << canvas[i].shape;

		}

	}

	void clear()

	{

		memset(canvas, ' ', (width + 1)*height);

		canvas[width + (height - 1)*(width + 1)].shape = '\0';

	}

	void mapCreate()

	{
		srand((unsigned)time(NULL));
		int num = 0;

		for (int i = 0; i < height; i++) {

			canvas[width + i * (width + 1)].shape = '\n';

		}

		for (int i = 0; i < (width + 1)*height; i++)

		{

			if (canvas[i].shape == '\n') continue;

			num = rand() % 7;

			if (num == 0) {
				canvas[i].mine = true; // ���ڼ��� ����
			}
		}

		num = 0;

		if (canvas[1].mine ==true) num++;

		if (canvas[width+1].mine == true)num++;

		if (canvas[width+2].mine == true)num++;

		canvas[0].mineCount = num + 48;
		for (int i = 1; i < (width + 1)*height; i++)
		{
			num = 0;
			if (canvas[i].mine != true && canvas[i].shape != '\n')
			{
				if (canvas[i - 1].mine == true) num++;

				if (canvas[i + 1].mine == true) num++;

				if (i > width && i < (width + 1)*(height - 1)) {

					if (canvas[i - (width + 1)].mine == true)num++;

					if (canvas[i - (width + 2)].mine == true)num++;

					if (canvas[i - (width)].mine == true)num++;

					if (canvas[i + (width + 1)].mine == true)num++;

					if (canvas[i + (width + 2)].mine == true)num++;

					if (canvas[i + width].mine == true)num++;

				}
				else if (i < width)
				{

					if (canvas[i + (width + 1)].mine == true)num++;

					if (canvas[i + (width + 2)].mine == true)num++;

					if (canvas[i + (width)].mine == true)num++;
				}
				else if (i > ((width + 1)*(height - 1)) - 1)
				{
					if (canvas[i - (width + 1)].mine == true)num++;

					if (canvas[i - (width + 2)].mine == true)num++;

					if (canvas[i - width].mine == true)num++;

				}
				canvas[i].mineCount = num;
			}
		}
	}

	void click(const Position pos) {



		int clickPos = pos.x + (pos.y * (width+1)); // Ŭ���ϴ°��� �������迭���� index�� ����
		if (pos.x > width || pos.y > height||canvas[clickPos].shape=='\n') return; //�������� �ƴ� �ٸ����� Ŭ���ϰų� ���๮���϶�
		if (canvas[clickPos].mine == true) {
			for (int i = 0; i < (width + 1)*height; i++)
			{
				if(canvas[i].mine)
				canvas[i].shape = canvas[i].mineShape;
				//game = false;
			}
			return;
		}; // ���ڸ� Ŭ���Ұ��
		if (canvas[clickPos].open==true) return; // ����� x
		canvas[clickPos].open = true;
		canvas[clickPos].shape = canvas[clickPos].mineCount+48;

		// Ŭ���Ѱ��� ù��°�� ���������� �ƴ� ��
		if (clickPos > width && clickPos < ((width + 1)*(height - 1)))
		{
			if ((canvas[clickPos - 1].mine==false) && (canvas[clickPos + 1].mine == false) &&
				(canvas[clickPos - (width + 1)].mine == false) && (canvas[clickPos - width-2].mine == false) && (canvas[clickPos - width].mine == false) &&
				(canvas[clickPos + (width + 1)].mine == false) && (canvas[clickPos + width+2].mine == false) && (canvas[clickPos + width].mine == false))
			{
				Position open1, open2, open3, open4, open5, open6, open7, open8;
					open1.x = pos.x - 1; open1.y = pos.y; //����ĭ
					open2.x = pos.x + 1; open2.y = pos.y; //������ĭ
					open3.x = pos.x; open3.y = pos.y - 1; //��ĭ
					open4.x = pos.x; open4.y = pos.y + 1; //�Ʒ�ĭ
					open5.x = pos.x - 1; open5.y = pos.y - 1; //�� ��
				open6.x = pos.x - 1; open6.y = pos.y + 1; // �Ʒ� ��
				open7.x = pos.x + 1; open7.y = pos.y - 1; // �� ��
				open8.x = pos.x + 1; open8.y = pos.y + 1;// �Ʒ� ��
				click(open1); click(open2); click(open3); click(open4); click(open5); click(open6); click(open7); click(open8);  // ���� 8ĭ �� Ŭ��
			}
		}

		//Ŭ���Ѱ��� ù��° ���� ���
		else if (clickPos < (width))
		{ 
			if (clickPos == 0)//�迭�� 0��°�� ��� 
			{
				if (canvas[clickPos + 1].mine == false && canvas[clickPos + width + 1].mine == false && canvas[clickPos + width + 2].mine == false)
				{
					Position open1, open2, open3;
					open1.x = pos.x + 1; open1.y = pos.y;
					open2.x = pos.x + 1; open2.y = pos.y+1;
					open3.x = pos.x; open3.y = pos.y + 1;
					click(open1); click(open2); click(open3);
				}
			}
			else
			{
				if ((canvas[clickPos - 1].mine == false) && (canvas[clickPos + 1].mine == false)
					&& (canvas[clickPos + (width + 1)].mine == false) && (canvas[clickPos + width + 2].mine == false) && (canvas[clickPos + width].mine == false))
				{

					Position open1, open2, open4, open6, open8;
					open1.x = pos.x - 1; open1.y = pos.y; //����ĭ
					open2.x = pos.x + 1; open2.y = pos.y; //������ĭ
					open4.x = pos.x; open4.y = pos.y + 1; //�Ʒ�ĭ
					open6.x = pos.x - 1; open6.y = pos.y + 1; // �Ʒ� ��
					open8.x = pos.x + 1; open8.y = pos.y + 1;// �Ʒ� ��
					click(open1); click(open2); click(open4); click(open6); click(open8);

				}
			}
		}

		//Ŭ���Ѱ��� �������� �ϰ��
		else if (clickPos > ((width + 1)*(height - 1))-1)
		{
			if (clickPos == (width + 1)*(height - 1)) //�������� ù°ĭ
			{
				if ((canvas[clickPos + 1].mine == false) && (canvas[clickPos - (width + 1)].mine == false) && (canvas[clickPos - width].mine == false))
				{
					Position open2, open3, open7;
					open2.x = pos.x + 1; open2.y = pos.y; //������ĭ
					open3.x = pos.x; open3.y = pos.y - 1; //��ĭ
					open7.x = pos.x + 1; open7.y = pos.y - 1; // �� ��

					click(open2); click(open3); click(open7);
				}
			}

			else
			{
				if ((canvas[clickPos - 1].mine == false) && (canvas[clickPos + 1].mine == false) &&
					(canvas[clickPos - (width + 1)].mine == false) && (canvas[clickPos - width - 2].mine == false) && (canvas[clickPos - width].mine == false))
				{
					Position open1, open2, open3,open5,open7;
					open1.x = pos.x - 1; open1.y = pos.y; //����ĭ
					open2.x = pos.x + 1; open2.y = pos.y; //������ĭ
					open3.x = pos.x; open3.y = pos.y - 1; //��ĭ
					open5.x = pos.x - 1; open5.y = pos.y - 1; //�� ��
					open7.x = pos.x + 1; open7.y = pos.y - 1; // �� ��

					click(open1); click(open2); click(open3); click(open5); click(open7);
				}
			}

		}

	}
};
///////////////////////////////////////////
Screen* Screen::instance = nullptr;
//////////////////////////////////////////
void gameStart()

{

	Screen& screen = Screen::getInstance();



	screen.mapCreate(); // �ʻ���

}
/////////////////////////////////////////
int main()
{
	Screen&	 screen = Screen::getInstance();
	INPUT_RECORD InputRecord;
	DWORD Events;
	gameStart();
	while (true)
	{

		screen.render();
		Sleep(30);
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &InputRecord, 1, &Events);

		if (InputRecord.EventType == MOUSE_EVENT) {

			if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {

				COORD coord;
				coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
				coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				Position pos;
				pos.x = InputRecord.Event.MouseEvent.dwMousePosition.X;
				pos.y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
				screen.click(pos);
			}
		}
	}

	system("pause");
	return 0;
}