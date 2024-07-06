#include"game.h"
int N_ID;
int Get_Random_Number()
{
	return rand() % 7 + 1;
}//返回1~7的随机数
void Game::Paint_BackGround_Window() {

	//色彩
	for (int i = 0; i < 541; ++i)
	{
		setlinecolor(RGB(135, 206, 250 - i / 5));
		line(0, 540 - i, 360, 540 - i);
	}
	for (int i = 0; i < 541; ++i)
	{
		setlinecolor(RGB(224, 178, 220 - i / 15));
		line(361, i, 600, i);
	}
	//文字
	//得分
	char str[50];
	settextstyle(30, 0, "楷体");//字体大小
	settextcolor(BLUE);//字体颜色
	setbkmode(TRANSPARENT);//不叠加，透过
	sprintf(str, "score:%d", score);
	outtextxy(360 + 48, 200, str);
	//按键提示
	outtextxy(360 + 48, 300 + 30 * 0, "左移 ←");
	outtextxy(360 + 48, 300 + 30 * 1, "右移 →");
	outtextxy(360 + 48, 300 + 30 * 2, "旋转 ↑");
	outtextxy(360 + 48, 300 + 30 * 3, "下落 ↓");
	//侧边预览框
	setlinecolor(RED);//边线颜色
	setlinestyle(0, 5);
	rectangle(360 + 36, 36, 600 - 48 - 12, 36 + 144);
}
bool Game::Over_Service() {
	//设置窗口标题
	HWND hnd = GetHWnd();
	SetWindowText(hnd, "俄罗斯方块");
	//弹出窗口
	int isok = MessageBox(NULL,
		"\t  LOSE！\n       DO YOU WANGT TO PALY AGAIN?",
		"俄罗斯方块",
		MB_OKCANCEL);
	if (isok != IDOK) {
		return false;
	}
}
void Game::Request_Window() {
	//设置窗口标题
	HWND hnd = GetHWnd();
	SetWindowText(hnd, "俄罗斯方块");
	//弹出窗口
	int isok = MessageBox(NULL,
		"\t  WELCOME！\n        DO YOU WANT TO PLAY?",
		"俄罗斯方块",
		MB_OKCANCEL);
	if (isok != IDOK) {
		exit(0);
	}
}
//方块x为36，y为36
void  Draw_Block_RED(int x, int y) {
	setlinecolor(BLACK);
	setfillcolor(RED);
	fillroundrect(x * Occupied_Part_Length, y * Occupied_Part_Length,
		x * Occupied_Part_Length + Occupied_Part_Length,
		y * Occupied_Part_Length + Occupied_Part_Length, Border_Fillet, Border_Fillet);
}
void  Draw_Block_GREEN(int x, int y) {
	setlinecolor(BLACK);
	setfillcolor(GREEN);
	fillroundrect(x * Occupied_Part_Length, y * Occupied_Part_Length,
		x * Occupied_Part_Length + Occupied_Part_Length,
		y * Occupied_Part_Length + Occupied_Part_Length, Border_Fillet, Border_Fillet);
}
void Game::Paint_Game_Area() {

	for (int i = 0; i < game_area_x; i++) {
		for (int j = 0; j < game_area_y; j++) {
			if (game_area[j][i] == 1) {
				Draw_Block_RED(i, j);
			}
			else if (game_area[j][i] == 2) {
				Draw_Block_GREEN(i, j);
			}

		}
	}
}
void Block_Group::Block_Copy(int tmp[4][4]) {
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			Block_Area[i][j] = tmp[i][j];
		}
	}
}


void Block_Group::Block_Array_Refresh(int x) {
	switch (x) {
	case 1: {
		Block_Copy(tmp1);
		break;
	}
	case 2: {
		Block_Copy(tmp2);
		break;
	}
	case 3: {
		Block_Copy(tmp3);
		break;
	}
	case 4: {
		Block_Copy(tmp4);
		break;
	}
	case 5: {
		Block_Copy(tmp5);
		break;
	}
	case 6: {
		Block_Copy(tmp6);
		break;
	}
	case 7: {
		Block_Copy(tmp7);
		break;
	}
	default:
		break;
	}
}
void Block_Group::Block_Group_Refresh(int x)//刷新
{
	N_ID = x;
	Block_Array_Refresh(x);
	Block_Position_x = 3;
	Block_Position_y = 0;

}



void block_copy_Two(int Ablock[4][4], int Bblock[4][4]) {
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			Ablock[i][j] = Bblock[i][j];
		}
	}

}
void Game::Paint_Pre_Game_Area()//已经获取了id
{
	int t[4][4];
	switch (N_ID) {
	case 1: {
		block_copy_Two(t, tmp1);
		break;
	}
	case 2: {
		block_copy_Two(t, tmp2);
		break;
	}
	case 3: {
		block_copy_Two(t, tmp3);
		break;
	}
	case 4: {
		block_copy_Two(t, tmp4);
		break;
	}
	case 5: {
		block_copy_Two(t, tmp5);
		break;
	}
	case 6: {
		block_copy_Two(t, tmp6);
		break;
	}
	case 7: {
		block_copy_Two(t, tmp7);
		break;
	}
	default:
		break;
	}

	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			if (t[j][i] == 1) {
				Draw_Block_RED(i + 11, j + 1);
			}
		}
	}
}

int Get_N_ID() {
	return N_ID;
}
void Game::Paint_Warn_Line() {
	setlinecolor(BROWN);
	setlinestyle(PS_SOLID,2);
	line(0,36*4,360,36*4);
}

void Game::Next_Trans_Current_And_Next_Refresh()
{
	block_copy_Two(C_Board_Group.Block_Area, N_Board_Group.Block_Area);
	N_Board_Group.Block_Group_Refresh(Get_Random_Number());
}


void Game::To_Stable() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (C_Board_Group.Block_Area[j][i] == 1) {
				game_area[j + C_Board_Group.Block_Position_y][i + C_Board_Group.Block_Position_x] = 2;
			}
		}
	}
}

bool Game::IsCollide_Down() {
	int dbound;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (C_Board_Group.Block_Area[i][j] == 1)
			{
				dbound = i;
				break;
			}
	int y = C_Board_Group.Block_Position_y;
	y++;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (dbound + y > game_area_y - 1 || (C_Board_Group.Block_Area[i][j] == 1 && game_area[i + y][j + C_Board_Group.Block_Position_x] == 2)) {
				return true;
			}
		}
	}
	return false;
}
bool Game::Block_Move_DOWN() {

	if (IsCollide_Down()) {
		To_Stable();
		Next_Trans_Current_And_Next_Refresh();
		C_Board_Group.Block_Position_x = 3;
		C_Board_Group.Block_Position_y = 0;
		return false;
	}
	else {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (C_Board_Group.Block_Area[j][i] == 1)
					game_area[j + C_Board_Group.Block_Position_y][i + C_Board_Group.Block_Position_x] = 0;
			}
		}
		C_Board_Group.Block_Position_y++;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (game_area[j + C_Board_Group.Block_Position_y][i + C_Board_Group.Block_Position_x] != 2 && (j + C_Board_Group.Block_Position_y) <= game_area_y - 1)
					game_area[j + C_Board_Group.Block_Position_y][i + C_Board_Group.Block_Position_x] = C_Board_Group.Block_Area[j][i];
			}
		}
	}
	return true;
}

void Game::Paint() {
	Paint_BackGround_Window();
	Paint_Game_Area();
	Paint_Pre_Game_Area();
	Paint_Warn_Line();
}
bool Game::IsCollide_Up() {
	int temp_block[4][4];int nums = 0;
	for (int i = 0;i < 4;i++)
		for (int j = 0;j < 4;j++)
		{
			temp_block[3 - j][i] = C_Board_Group.Block_Area[i][j];
			if (temp_block[3 - j][i] == 1) {
				nums++;
			}
		}
	int lbound = 10, rbound=-1;
	int ubound = 10, dbound = -1;
	for (int j = 0;j < 4;j++) {
		for (int i = 0;i < 4;i++) {
			if(temp_block[i][j] == 1)
			lbound = min(lbound, j);
			rbound = max(rbound, j);
			ubound = min(ubound, i);
			dbound = max(dbound, i);
		}
	}
	if (C_Board_Group.Block_Position_x + lbound >= 0&&
		C_Board_Group.Block_Position_x + rbound < 10&&
		C_Board_Group.Block_Position_y+dbound<=14)
	{
		for (int i = C_Board_Group.Block_Position_y + ubound;i <= C_Board_Group.Block_Position_y + dbound;i++) {
			for (int j = C_Board_Group.Block_Position_x + lbound;j <= C_Board_Group.Block_Position_x + rbound;j++) {
				if (temp_block[i- C_Board_Group.Block_Position_y][j- C_Board_Group.Block_Position_x] == 1) {
					if (game_area[i ][j] == 2) {
						return true;
					}
				}
			}
		}
		return false;
	}
	return true;
}

void Game::Block_Move_UP() {
	if (IsCollide_Up()) {
	}
	else {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (C_Board_Group.Block_Area[j][i] == 1)
					game_area[j + C_Board_Group.Block_Position_y][i + C_Board_Group.Block_Position_x] = 0;
			}
		}//擦除
		int temp_block[4][4];
		for (int i = 0;i < 4;i++)
			for (int j = 0;j < 4;j++)
					temp_block[3 - j][i] = C_Board_Group.Block_Area[i][j];
		for (int i = 0;i < 4;i++)
			for (int j = 0;j < 4;j++)
				C_Board_Group.Block_Area[i][j] = temp_block[i][j];
		//方块组变形
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (game_area[j + C_Board_Group.Block_Position_y][i + C_Board_Group.Block_Position_x] != 2 && (j + C_Board_Group.Block_Position_y) <= game_area_y - 1)
					game_area[j + C_Board_Group.Block_Position_y][i + C_Board_Group.Block_Position_x] = C_Board_Group.Block_Area[j][i];
			}
		}
		//游戏区域数组更新
	}
}


void Game::Key_Press() {
	if (GetAsyncKeyState(VK_UP)) {
		Sleep(100);
		Block_Move_UP();
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		Sleep(100);
		Block_Move_RIGHT();
	}
	else if (GetAsyncKeyState(VK_LEFT)) {
		Sleep(100);
		Block_Move_LEFT();
	}
	else if (GetAsyncKeyState(VK_DOWN)) {
		Sleep(100);
		Block_Move_DOWN();
	}
	else if (GetAsyncKeyState(VK_SPACE)) {
		Sleep(100);
		Block_Move_SPACE();
	}
}




int Game::IsCollide_Left() {
	int lbound, rbound, ubound, dbound;
	for (int i = 3; i >= 0; i--)
		for (int j = 0; j < 4; j++)
			if (C_Board_Group.Block_Area[i][j] == 1)
			{
				ubound = i;
				break;
			}
	for (int j = 3; j >= 0; j--)
		for (int i = 0; i < 4; i++)
			if (C_Board_Group.Block_Area[i][j] == 1)
			{
				lbound = j;
				break;
			}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (C_Board_Group.Block_Area[i][j] == 1)
			{
				dbound = i;
				break;
			}
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			if (C_Board_Group.Block_Area[i][j] == 1)
			{
				rbound = j;
				break;
			}
	int x = C_Board_Group.Block_Position_x;
	x--;
	if (lbound + x < 0) {
		return 1;
	}
	for (int i = lbound; i <= rbound; i++) {
		for (int j = ubound; j <= dbound; j++) {
			if (x + lbound == i + x && game_area[j + C_Board_Group.Block_Position_y][i + x] == 2) {
				return 1;
			}
		}
	}
	for (int i = lbound; i <= rbound; i++) {
		for (int j = ubound; j <= dbound; j++) {
			if (x + lbound<0 || x + rbound>game_area_x - 1 || (C_Board_Group.Block_Area[j][i] == 1 && game_area[j + C_Board_Group.Block_Position_y][i + x] == 2)) {
				return 2;
			}
		}
	}
	return 3;

}//能够左移吗
int Game::IsCollide_Right() {
	int lbound, rbound, ubound, dbound;
	for (int i = 3; i >= 0; i--)
		for (int j = 0; j < 4; j++)
			if (C_Board_Group.Block_Area[i][j] == 1)
			{
				ubound = i;
				break;
			}
	for (int j = 3; j >= 0; j--)
		for (int i = 0; i < 4; i++)
			if (C_Board_Group.Block_Area[i][j] == 1)
			{
				lbound = j;
				break;
			}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (C_Board_Group.Block_Area[i][j] == 1)
			{
				dbound = i;
				break;
			}
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			if (C_Board_Group.Block_Area[i][j] == 1)
			{
				rbound = j;
				break;
			}
	int x = C_Board_Group.Block_Position_x;
	x++;
	if (rbound + x > game_area_x - 1) {
		return 1;
	}
	for (int i = lbound; i <= rbound; i++) {
		for (int j = ubound; j <= dbound; j++) {
			if (x + rbound == x + i && game_area[j + C_Board_Group.Block_Position_y][i + x] == 2) {
				return 1;
			}
		}
	}
	for (int i = lbound; i <= rbound; i++) {
		for (int j = ubound; j <= dbound; j++) {
			if (x + lbound<0 || x + rbound>game_area_x - 1 || (C_Board_Group.Block_Area[j][i] == 1 && game_area[j + C_Board_Group.Block_Position_y][i + x] == 2)) {
				return 2;
			}
		}
	}
	return 3;


}//能够右移吗

void Game::Block_Move_LEFT() {


	if (IsCollide_Left() == 2) {
		To_Stable();
		Next_Trans_Current_And_Next_Refresh();
		C_Board_Group.Block_Position_x = 3;
		C_Board_Group.Block_Position_y = 0;
	}
	else if (IsCollide_Left() == 1) {
	}
	else {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (C_Board_Group.Block_Area[j][i] == 1)
					game_area[j + C_Board_Group.Block_Position_y][i + C_Board_Group.Block_Position_x] = 0;
			}
		}
		C_Board_Group.Block_Position_x--;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (game_area[j + C_Board_Group.Block_Position_y][i + C_Board_Group.Block_Position_x] != 2 && (j + C_Board_Group.Block_Position_y) <= game_area_y - 1
					&& (i + C_Board_Group.Block_Position_x) >= 0)
					game_area[j + C_Board_Group.Block_Position_y][i + C_Board_Group.Block_Position_x] = C_Board_Group.Block_Area[j][i];
			}
		}
	}

}
void Game::Block_Move_RIGHT() {

	if (IsCollide_Right() == 2) {
		To_Stable();
		Next_Trans_Current_And_Next_Refresh();
		C_Board_Group.Block_Position_x = 3;
		C_Board_Group.Block_Position_y = 0;
	}
	else if (IsCollide_Right() == 1) {
	}
	else {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (C_Board_Group.Block_Area[j][i] == 1)
					game_area[j + C_Board_Group.Block_Position_y][i + C_Board_Group.Block_Position_x] = 0;
			}
		}
		C_Board_Group.Block_Position_x++;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (game_area[j + C_Board_Group.Block_Position_y][i + C_Board_Group.Block_Position_x] != 2 && (j + C_Board_Group.Block_Position_y) <= game_area_y - 1
					&& (i + C_Board_Group.Block_Position_x) <= game_area_x - 1)
					game_area[j + C_Board_Group.Block_Position_y][i + C_Board_Group.Block_Position_x] = C_Board_Group.Block_Area[j][i];
			}
		}
	}


}

void Game::Check_game_area_And_Clear_All_Line_And_Change_Score(){
	int line = 0;
	for (int i = 14;i >= 0;i--) {
		int flag = 1;
		
		for (int j = 0;j < 10;j++) {
			if (game_area[i][j] != 2) {

				flag = 0;
				break;
			}
		}
		if (flag == 1) {
			for(int k = i;k>0;k--)
			for (int j = 0;j < 10;j++) {
				game_area[k][j] = 0;
				swap(game_area[k][j], game_area[k-1][j]);
			}
			line++;
		}

	}
	while (line--) {
		score += (10 * (line+1));
	}


}


void Game::Block_Move_SPACE() {
	for (int i = 0;i < 15;i++) {
		if (!Block_Move_DOWN()) {
			return;
		}
	}
}

bool Game::IsOver() {
	for (int i = 0;i < 10;i++) {
		if (game_area[1][i] == 2) {
			cout << 1;
			return true;
		}
	}
	return false;

}