#include "sat.h"
#include"twoeasyx.h"
extern int twodoku[15][15];
extern int gameboard[15][15];
extern int holes;

//把用到的游戏数据全部初始化
void InitDataSet()
{
	process = 0;
	restart = 0;
	pause = 0;
	faults = 0;
	endGame = 0;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			gameBoardCopy[i][j] = holeBoard[i][j] = highLightBoard[i][j] = wrongHoleBoard[i][j] = 0;
}

int sudoku_easyx(){
	initgraph(900,620);
	//画一下游戏格局
	while (1)
	{
		InitDataSet();
		while (process < 2)
			fun[process++]();
		//用于界面的前进与回退
		t1 = clock();
		GameInit(twodoku);
		while (1)
		{
			if (peekmessage(&msg, EM_MOUSE, true))
				msg = getmessage();
			GameUpdate();
			
			GameDraw();
			allDone = HoleCheck(); 
			if (allDone) {
				allRight = AnswerCheck();
				Sleep(1000);
				break;
			}
			else if (restart) {
				Sleep(1000);
				break;
			}
			if (endGame)
				break;
		}
		if (allRight)
			end();
		else
			JudgeInterface();
		if (endGame)
			break;
	}
	closegraph();
	return 0;
}



void interface1()
{
	BeginBatchDraw();
	setbkcolor(WHITE);  
	settextcolor(BLACK);
	setbkmode(1);  
	cleardevice();
	TCHAR s[5];
	_stprintf_s(s, _T("%d/2"), process);
	outtextxy(0, 0, s);
	LOGFONT f;
	gettextstyle(&f);                   
	f.lfHeight = 70;              
	wcscpy_s(f.lfFaceName, _T("隶书"));     
	f.lfQuality = ANTIALIASED_QUALITY;    
	settextstyle(&f);                      
	outtextxy(100, 100, _T("基于DPLL的SAT求解程序"));
	
	settextstyle(40, 0, _T("微软雅黑"));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);


	rectangle(340, 290, 560, 360);
	if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>290 && currentPos.Y < 360)
	{
		settextcolor(BLUE);
		line(370, 350, 530, 350);
	}
	else
		settextcolor(BLACK);
	outtextxy(350, 305, L"TWODOKU！");
	

	EndBatchDraw();

}
void func1()
{
	int post = 1;
	while (post)
	{
		interface1();
		ExMessage msg = getmessage(); 
		int x = msg.x;
		int y = msg.y;
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			currentPos.X = x;
			currentPos.Y = y;
			break;
		case WM_LBUTTONUP:
			if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>290 && currentPos.Y < 360)
				post = 0;
			break;
		default:
			break;
		}
	}


}
void interface2()
{
	BeginBatchDraw();
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(1);  
	cleardevice();
	TCHAR s[5];
	_stprintf_s(s, _T("%d/3"), process);
	outtextxy(0, 0, s);
	settextstyle(40, 0, _T("隶书"));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);

	if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>90 && currentPos.Y < 160)
	{
		settextcolor(BLUE);
		line(370, 150, 530, 150);
	}

	EndBatchDraw();
}
void func2()
{
	int post = 1;
	while (post)
	{
		interface2();
		ExMessage msg = getmessage();  
		int x = msg.x;
		int y = msg.y;
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			currentPos.X = x;
			currentPos.Y = y;
			break;
		case WM_LBUTTONUP:
			 

			if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>390 && currentPos.Y < 460)
			{
				post = 0;
				process -= 2;
			}
			break;
		default:
			break;
		}
	}


}
void interface3()
{
	BeginBatchDraw();
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(1);  
	cleardevice();
	TCHAR s[5];
	_stprintf_s(s, _T("%d/2"), process);
	outtextxy(0, 0, s);
	settextstyle(40, 0, _T("隶书"));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);


	rectangle(340, 190, 560, 260);
	if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>190 && currentPos.Y < 260)
	{
		settextcolor(BLUE);
		line(370, 250, 530, 250);
	}
	else
		settextcolor(BLACK);
	outtextxy(370, 205, L"开始游戏");


	rectangle(340, 390, 560, 460);
	if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>390 && currentPos.Y < 460)
	{
		settextcolor(BLUE);
		line(370, 450, 530, 450);
	}
	else
		settextcolor(BLACK);
	outtextxy(370, 405, L"返    回");
	 
	EndBatchDraw();
}
void func3()
{
	int post = 1;
	while (post)
	{
		interface3();
		
		ExMessage msg = getmessage();  
		int x = msg.x;
		int y = msg.y;
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			currentPos.X = x;
			currentPos.Y = y;
			break;
		case WM_LBUTTONUP:
			if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>190 && currentPos.Y < 260)
				post = 0;
			if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>390 && currentPos.Y < 460)
			{
				post = 0;
				process -= 2;
			}
			break;
		default:
			break;
		}
	}


}


void GameDraw()
{
	BeginBatchDraw();
	
	setbkcolor(WHITE);  
	setbkmode(1);
	cleardevice();
	 
	LOGFONT f;
	gettextstyle(&f);                    
	f.lfHeight = 20;                     
	wcscpy_s(f.lfFaceName, _T("楷体"));     
	f.lfQuality = ANTIALIASED_QUALITY;    
	settextstyle(&f);
	outtextxy(350, 30, _T("EasyX鼠标活动检验不灵敏"));
	outtextxy(350, 60, _T("点快了容易被误判为双击"));
	outtextxy(350, 90, _T("点不动时烦请隔一秒再试"));
	outtextxy(350, 120, _T("亦可先点击其他数字"));
	outtextxy(350, 150, _T("点击数字中心则更准确"));
	setlinecolor(BLACK);
	f.lfHeight = 15;
	//下面用于画双数独的棋盘
	for (int row = 1; row <= 6; row++) 
	{
		if ((row - 1) % 3 == 0)
			setlinestyle(PS_SOLID, 3);
		else
			setlinestyle(PS_DASH, 1);
		line(30, row * 30, 300, row * 30);
	}
	for (int col = 1; col <= 6; col++)  
	{
		if ((col - 1) % 3 == 0)
			setlinestyle(PS_SOLID, 3);
		else
			setlinestyle(PS_DASH, 1);
		line(col * 30, 30, col * 30, 300);
	}
	for (int row = 7; row <= 10; row++)  
	{
		if ((row - 1) % 3 == 0)
			setlinestyle(PS_SOLID, 3);
		else
			setlinestyle(PS_DASH, 1);
		line(30, row * 30, 480, row * 30);
	}
	for (int col = 7; col <= 10; col++)  
	{
		if ((col - 1) % 3 == 0)
			setlinestyle(PS_SOLID, 3);
		else
			setlinestyle(PS_DASH, 1);
		line(col * 30, 30, col * 30, 480);
	}
	for (int row = 11; row <= 16; row++)  
	{
		if ((row - 1) % 3 == 0)
			setlinestyle(PS_SOLID, 3);
		else
			setlinestyle(PS_DASH, 1);
		line(210, row * 30, 480, row * 30);
	}
	for (int col = 11; col <= 16; col++)  
	{
		if ((col - 1) % 3 == 0)
			setlinestyle(PS_SOLID, 3);
		else
			setlinestyle(PS_DASH, 1);
		line(col * 30, 210, col * 30, 480);
	}
	 
	 //下面进行高亮标记

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			if (highLightBoard[i][j])
			{
				if (highLightBoard[i][j] == 1)
					setfillcolor(RGB(85, 242, 85)); 
				else
					setfillcolor(RGB(174, 174, 174));//同行列宫用浅灰色显示
				solidrectangle((j + 1) * 30 + 2, (i + 1) * 30 + 2, (j + 2) * 30 - 2, (i + 2) * 30 - 2);
			}
	setfillcolor(RGB(99, 99, 99));
	if (index && ((waitPos.X>=0 && waitPos.X<=8 && waitPos.Y >= 0 && waitPos.Y <= 8)|| (waitPos.X >= 6 && waitPos.X <= 14 && waitPos.Y >= 6 && waitPos.Y <= 14)))
		solidrectangle((waitPos.X + 1) * 30 + 2, (waitPos.Y + 1) * 30 + 2, (waitPos.X + 2) * 30 - 2, (waitPos.Y + 2) * 30 - 2);
	//高亮错误数字所在的框格
	setfillcolor(RGB(250, 44, 20));
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			if (wrongHoleBoard[i][j])
				solidrectangle((j + 1) * 30 + 1, (i + 1) * 30 + 1, (j + 2) * 30 - 1, (i + 2) * 30 - 1);


	 
	TCHAR str[10];
	if (showanswer == 0) {
		for (int row = 0; row < 15; row++)
		{
			for (int col = 0; col < 15; col++)
			{
				 
				if (gameBoardCopy[row][col] != 0 && gameBoardCopy[row][col] != -1)
				{
					if (holeBoard[row][col] == 1)
						settextcolor(BLUE);
					else if (highLightBoard[row][col] || wrongHoleBoard[row][col])
						settextcolor(WHITE);
					else
						settextcolor(RGB(61, 61, 61));
					 
						_stprintf_s(str, _T("%d"), gameBoardCopy[row][col]);
						outtextxy((col + 1) * 30 + 10, (row + 1) * 30 + 5, str);
					
				}
			}
		}
	}
	else {//如果投降，选择显示答案的话
		for (int row = 0; row < 15; row++)
		{
			for (int col = 0; col < 15; col++)
			{
				 
				if (gameBoardCopy[row][col] != 0 && gameBoardCopy[row][col] != -1)
				{
					if (holeBoard[row][col] == 1)
						settextcolor(BLUE);
					else if (highLightBoard[row][col] || wrongHoleBoard[row][col])
						settextcolor(WHITE);
					else
						settextcolor(RGB(61, 61, 61));
					_stprintf_s(str, _T("%d"), gameBoardCopy[row][col]);
					outtextxy((col + 1) * 30 + 10, (row + 1) * 30 + 5, str);
				}
				else {
					settextcolor(RED);
					if ((row >= 0 && row <= 8 && col >= 0 && col <= 8) || (row >= 6 && row <= 14 && col >= 6 && col <= 14))
					{
						_stprintf_s(str, _T("%d"), twodoku[row][col]);
						outtextxy((col + 1) * 30 + 10, (row + 1) * 30 + 5, str);
					}
				}
			}
		}
	}


	 
	setlinestyle(PS_SOLID, 1);
	 
	 
	settextcolor(RGB(9, 74, 247));
	setlinestyle(PS_SOLID, 3);
	t2 = clock();
	seconds = (int)(double)(t2 - t1) / CLOCKS_PER_SEC;

	//计算游戏时间
	seconds -= pause;
	minutes = seconds / 60;
	seconds %= 60;
	_stprintf_s(str, _T("%02d:%02d"), minutes, seconds);
	outtextxy(0, 0, str);





	int n = 1;
	settextstyle(30, 10, _T("微软雅黑"));
	outtextxy(730, 250, _T("删除"));
	for (int col = 0; col <= 2; col++)
	{
		for (int row = 10; row <= 12; row++)
		{
			_stprintf_s(str, _T("%d"), n++);
			outtextxy((row + 1) * 60 + 25, (col + 1) * 60 + 15, str);
		}
	}
	 
	
	setlinecolor(RGB(128,0,128));
	setlinestyle(PS_SOLID, 5);
	rectangle((numPos.X + 1) * 60, (numPos.Y + 1) * 60, (numPos.X + 2) * 60, (numPos.Y + 2) * 60);
	setfillcolor(RGB(249, 247, 176));

	 
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	settextstyle(30, 0, _T("微软雅黑"));
	setfillcolor(RGB(158, 160, 169));

	//画一下四个按钮
	if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 350 && currentPos.Y < 400)
	{
		solidrectangle(660, 350, 840, 400);
		settextcolor(WHITE);
	}
	else
		settextcolor(BLUE);
	outtextxy(715, 360, _T("PAUSE"));


	if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 420 && currentPos.Y < 470)
	{
		solidrectangle(660, 420, 840, 470);
		settextcolor(WHITE);
	}
	else
		settextcolor(BLUE);
	outtextxy(700, 430, _T("RESTART"));
	if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 490 && currentPos.Y < 540)
	{
		solidrectangle(660, 490, 840, 540);
		settextcolor(WHITE);
	}
	else
		settextcolor(BLUE);
	outtextxy(725, 500, _T("EXIT"));
	if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 560 && currentPos.Y < 610)
	{
		solidrectangle(660, 560, 840, 610);
		settextcolor(WHITE);
	}
	else
		settextcolor(BLUE);
	outtextxy(680, 570, _T("SURRENDER"));
	setfillcolor(BLACK);
	 
	EndBatchDraw();
}
void GameUpdate()
{
	if (peekmessage(&msg, EM_MOUSE, true))
		msg = getmessage();

	int x = msg.x;
	int y = msg.y;
	switch (msg.message)
	{
	case WM_MOUSEMOVE:
		if (x > 30 && x < 480 && y > 30 && y < 480)
		{
			index = 1;
			waitPos.X = (x - 30) / 30;
			waitPos.Y = (y - 30) / 30;
			coord.X = waitPos.Y;
			coord.Y = waitPos.X;
			coord = FindLeftUpperCorner(coord);
			if (gameBoardCopy[waitPos.Y][waitPos.X])
				HighLight(1);
			else
				HighLight(0);
		}
		else
		{
			 
			index = 0;
			 
			for (int i = 0; i < 15; i++)
				for (int j = 0; j < 15; j++)
					highLightBoard[i][j] = 0;
		}
		currentPos.X = x;
		currentPos.Y = y;
		break;
		//对笛卡尔坐标进行计算用于获取选择填入的数字
	case WM_LBUTTONUP:
		if (x > 660 && x < 840 && y>60 && y < 240)
		{
			numPos.X = (x - 60) / 60;
			numPos.Y = (y - 60) / 60;
			pickednum = 3 * numPos.Y + (numPos.X - 10) + 1;
		}
		else if (x > 720 && y > 240 && x < 780 && y < 300)
		{
			numPos.X = (x - 60) / 60;
			numPos.Y = (y - 60) / 60;
			pickednum = 0;
		}
		else if ((x > 30 && x < 300 && y > 30 && y < 300) || (x>210&&x<480&&y>210&&y<480))
		{
			if (holeBoard[waitPos.Y][waitPos.X] == 1)
				gameBoardCopy[waitPos.Y][waitPos.X] = pickednum;
			else
			{
				clock_t t3, t4;
				t3 = clock();
				MessageBox(GetHWnd(), L"提示：给定数字不可修改", L"注意", 0);
				t4 = clock();
				pause += (int)(double)(t4 - t3) / CLOCKS_PER_SEC;
			}
			noError = FindMistake();
			faults += noError;
		}
		else if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 350 && currentPos.Y < 400)
		{
			clock_t t3, t4;
			t3 = clock();
			MessageBox(GetHWnd(), L"暂停中...", L"提示", 0);
			t4 = clock();
			pause += (int)(double)(t4 - t3) / CLOCKS_PER_SEC;
		}
		else if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 420 && currentPos.Y < 470)
		{
			clock_t t3, t4;
			t3 = clock();
			int result = MessageBox(GetHWnd(), _T("重新开始?"), _T("hello"), MB_YESNO);
			switch (result)
			{
			case IDNO:
				break;
			case IDYES:
				restart = 1;
				break;
			}
			t4 = clock();
			pause += (int)(double)(t4 - t3) / CLOCKS_PER_SEC;
		}
		else if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 490 && currentPos.Y < 540)
		{
			int result = MessageBox(GetHWnd(), L"确认退出？", L"提示", MB_YESNO);
			switch (result)
			{
			case IDNO:
				break;
			case IDYES:
				endGame = 1;
				break;
			}

		}
		else if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 560 && currentPos.Y < 610)
		{
			int result = MessageBox(GetHWnd(), L"显示答案", L"提示", MB_YESNO);
			switch (result)
			{
			case IDNO:
				break;
			case IDYES:
			{
				showanswer = 1;
				break;
			}
			}

		}
		break;
	default:
		break;
	}
	 
	msg.message = WM_MBUTTONUP;
}
void HighLight(int post)
{
	int i, j;
	//清除上次的高亮数据
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
			highLightBoard[i][j] = 0;
	if (waitPos.Y >= 0 && waitPos.Y <= 14 && waitPos.X >= 0 && waitPos.X <= 14)
	{
		/*两种高亮模式*/
		if (post)//1.高亮相同的数字
		{
			for (i = 0; i < 9; i++)
				for (j = 0; j < 9; j++)
					if (gameBoardCopy[i][j] == gameBoardCopy[waitPos.Y][waitPos.X] && waitPos.Y >= 0 && waitPos.Y <= 8 && waitPos.X >= 0 && waitPos.X <= 8)
						highLightBoard[i][j] = 1;
			for (i = 6; i < 15; i++)
				for (j = 6; j < 15; j++)
					if (gameBoardCopy[i][j] == gameBoardCopy[waitPos.Y][waitPos.X] && waitPos.Y >= 6 && waitPos.Y <= 14 && waitPos.X >= 6 && waitPos.X <= 14)
						highLightBoard[i][j] = 1;

		}
		else//2.高亮同行、同列、同宫
		{
			if (waitPos.X <= 8 && waitPos.X >= 0 && waitPos.Y <= 8 && waitPos.Y >= 0)
			{
				for (i = 0; i < 9; i++)
					highLightBoard[i][waitPos.X] = 2;
				for (i = 0; i < 9; i++)
					highLightBoard[waitPos.Y][i] = 2;
			}
			if (waitPos.X <= 14 && waitPos.X >= 6 && waitPos.Y <= 14 && waitPos.Y >= 6)
			{
				for (i = 6; i < 15; i++)
					highLightBoard[i][waitPos.X] = 2;
				for (i = 6; i < 15; i++)
					highLightBoard[waitPos.Y][i] = 2;
			}
			//2.1根据每一宫的左上角的行列来高亮对应的那一宫
			for (i = coord.X; i < coord.X + 3; i++)
				for (j = coord.Y; j < coord.Y + 3; j++)
					if( (i >= 0 && i <= 8 && j >= 0 && j <= 8) || (i >= 6 && i <= 14 && j >= 6 && j <= 14))
						highLightBoard[i][j] = 2;
			 
		}
	}


}
COORD FindLeftUpperCorner(COORD c1)
{
	//找到每一个小九宫格左上角的数字，便于同宫的高亮标记
	COORD c2;
	if (c1.X >= 0 && c1.X <= 8 && c1.X >= 0 && c1.Y <= 8) {
		for (int i = 0; i <= 6; i += 3)
		{
			c2.X = i;
			for (int j = 0; j <= 6; j += 3)
			{
				c2.Y = j;
				if (c1.X >= c2.X && c1.X <= c2.X + 2 && c1.Y >= c2.Y && c1.Y <= c2.Y + 2)
					return c2;
			}
		}
	}
	if (c1.X >= 6 && c1.X <= 14 && c1.X >= 6 && c1.Y <= 14) {
		for (int i = 6; i <= 12; i += 3)
		{
			c2.X = i;
			for (int j = 6; j <= 12; j += 3)
			{
				c2.Y = j;
				if (c1.X >= c2.X && c1.X <= c2.X + 2 && c1.Y >= c2.Y && c1.Y <= c2.Y + 2)
					return c2;
			}
		}
	}
}
int FindMistake()
{
	int i, j, r, c, post = 0;
	//清除上次的错误数据
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
			wrongHoleBoard[i][j] = 0;
	//对每列检查错误
	for (i = 0; i < 9; i++)
	{
		int arr[10] = { 0 };
		for (j = 0; j < 9; j++)
			arr[gameBoardCopy[i][j]]++;
		for (j = 0; j < 9; j++)
			if (arr[gameBoardCopy[i][j]] >= 2 && gameBoardCopy[i][j] != 0)
			{
				wrongHoleBoard[i][j] = 1;
				post = 1;
			}
	}
	for (i = 6; i < 15; i++)
	{
		int arr[10] = { 0 };
		for (j = 6; j < 15; j++)
			arr[gameBoardCopy[i][j]]++;
		for (j = 6; j < 15; j++)
			if (arr[gameBoardCopy[i][j]] >= 2 && gameBoardCopy[i][j] != 0)
			{
				wrongHoleBoard[i][j] = 1;
				post = 1;
			}
	}
	//对每行检查错误
	for (i = 0; i < 9; i++)
	{
		int arr[10] = { 0 };
		for (j = 0; j < 9; j++)
			arr[gameBoardCopy[j][i]]++;
		for (j = 0; j < 9; j++)
			if (arr[gameBoardCopy[j][i]] >= 2 && gameBoardCopy[j][i] != 0)
			{
				post = 1;
				wrongHoleBoard[j][i] = 1;
			}
	}
	for (i = 6; i < 15; i++)
	{
		int arr[10] = { 0 };
		for (j = 6; j < 15; j++)
			arr[gameBoardCopy[j][i]]++;
		for (j = 6; j < 15; j++)
			if (arr[gameBoardCopy[j][i]] >= 2 && gameBoardCopy[j][i] != 0)
			{
				post = 1;
				wrongHoleBoard[j][i] = 1;
			}
	}
	//对每宫检查错误
	for (i = 0; i <= 6; i += 3)
	{
		for (j = 0; j <= 6; j += 3)
		{
			int arr[10] = { 0 };
			for (r = i; r <= i + 2; r++)
				for (c = j; c <= j + 2; c++)
					arr[(gameBoardCopy[r][c])]++;
			for (r = i; r <= i + 2; r++)
				for (c = j; c <= j + 2; c++)
					if (arr[gameBoardCopy[r][c]] >= 2 && gameBoardCopy[r][c] != 0)
					{
						wrongHoleBoard[r][c] = 1;
						post = 1;
					}
		}
	}
	for (i = 6; i <= 12; i += 3)
	{
		for (j = 6; j <= 12; j += 3)
		{
			int arr[10] = { 0 };
			for (r = i; r <= i + 2; r++)
				for (c = j; c <= j + 2; c++)
					arr[(gameBoardCopy[r][c])]++;
			for (r = i; r <= i + 2; r++)
				for (c = j; c <= j + 2; c++)
					if (arr[gameBoardCopy[r][c]] >= 2 && gameBoardCopy[r][c] != 0)
					{
						wrongHoleBoard[r][c] = 1;
						post = 1;
					}
		}
	}
	return post;
}
int HoleCheck()//看看玩家是不是填满了
{
	int post = 1, P = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			if (gameBoardCopy[i][j] == 0)
			{
				post = 0;
				P = 1;
				break;
			}
		if (P)
			break;
	}
	for (int i = 6; i < 15; i++)
	{
		for (int j = 6; j < 15; j++)
			if (gameBoardCopy[i][j] == 0)
			{
				post = 0;
				P = 1;
				break;
			}
		if (P)
			break;
	}
	return post;
}
int AnswerCheck() {//看看玩家有没有填错（实际上除非只挖了一个洞，不然不会走到这一步）
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			if (gameBoardCopy[i][j] != twodoku[i][j])
			{
				return 0;

			}
	}
	for (int i = 6; i < 15; i++)
	{
		for (int j = 6; j < 15; j++)
			if (gameBoardCopy[i][j] != twodoku[i][j])
			{
				return 0;
			}
	}
	return 1;
}
void GameInit(int a[][15])
{


	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			gameBoardCopy[i][j] = a[i][j];


	Dig();
}
void Dig()
{

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (gameboard[i][j] == 0)
				holeBoard[i][j] = 1;
			if (holeBoard[i][j])
				gameBoardCopy[i][j] = 0;
		}

	}
}
void JudgeInterface() {
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(1);
	setfillcolor(RGB(158, 160, 169));
	cleardevice();
	IMAGE img;
	loadimage(&img, _T("cy.jpg"));
	putimage(0, 0, &img);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 100;
	wcscpy_s(f.lfFaceName, _T("楷体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	outtextxy(30, 200, _T("挑战失败"));
	 
	settextstyle(20, 0, _T("宋体"));


	outtextxy(650, 60, _T("TIME"));
	 
	//outtextxy(550, 190, _T("错误次数："));
	//solidrectangle(550, 240, 850, 290);
	outtextxy(680, 120, _T("MARKS"));
	 
	TCHAR str[20];
	settextcolor(WHITE);
	_stprintf_s(str, _T("%02d分%02d秒"), minutes, seconds);
	outtextxy(700, 60, str);
	//_stprintf_s(str, _T("%d"), faults);
	//outtextxy(680, 240, str);
	float a = (1 - (minutes + (float)seconds / 60) / ((1) * 100)) * 20;
	float b = (float)(80 - faults) / 800 * 80;
	if ((minutes * 60 + seconds) > (600 * (1)))
		a = 0;
	if (faults >= 30)
		b = 0;
	float scores = a + b;
	_stprintf_s(str, _T("%.2f"), scores);
	outtextxy(750, 120, str);
	Sleep(1000);
	int result = MessageBox(GetHWnd(), _T("再来一局?"), _T("hello"), MB_YESNO);
	switch (result)
	{
	case IDNO:
		endGame = 1;
		break;
	case IDYES:
		break;
	}
}
void end()
{
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(1);
	setfillcolor(RGB(158, 160, 169));
	cleardevice();
	IMAGE img;
	loadimage(&img, _T("cy.jpg"));
	putimage(0, 0, &img);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 100;
	wcscpy_s(f.lfFaceName, _T("楷体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	
	outtextxy(30, 100, _T("挑战成功!"));
	settextstyle(20, 0, _T("宋体"));
	 
	outtextxy(650, 60, _T("TIME"));
	
	outtextxy(720, 100, _T("MARKS"));
	 


	TCHAR str[20];
	settextcolor(WHITE);
	_stprintf_s(str, _T("%02d分%02d秒"), minutes, seconds);
	outtextxy(700, 60, str);
	//_stprintf_s(str, _T("%d"), faults);
	//outtextxy(680, 240, str);
	float a = (1 - (minutes + (float)seconds / 60) / ((1) * 10)) * 20;
	float b = (float)(80 - faults) / 80 * 80;
	if ((minutes * 60 + seconds) > (600 * (1)))
		a = 0;
	if (faults >= 30)
		b = 0;
	float scores = a + b;
	_stprintf_s(str, _T("%.2f"), scores);
	outtextxy(750, 130, str);
	Sleep(1000);
	int result = MessageBox(GetHWnd(), _T("再来一局?"), _T("hello"), MB_YESNO);
	switch (result)
	{
	case IDNO:
		endGame = 1;
		break;
	case IDYES:
		break;
	}

}
