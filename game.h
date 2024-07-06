#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include<graphics.h>//图形库头文件
#include<iostream>
#include<easyx.h>//鼠标
#include<conio.h>//使用getch()
#include<stdio.h>
#include<time.h> 
#include <stdlib.h>  
const int game_area_x = 10;//横着能放的方块数
const int game_area_y = 15;//竖着能放的方块数
const int Block_Area_x = 4;//方块组对象横着能放的方块个数
const int Block_Area_y = 4;//方块组对象竖着着能放的方块个数
//方块的定义
const int Occupied_Part_Length = 36;//占据部分
const int Inner_Margin = 2;//内边距
const int Border_Fillet = 6;//边框圆角
const int Really_length = 32;//实体边长
using namespace std;
static int tmp1[4][4] = { 
	{0,0,0,0}, 
	{0,1,1,0} ,
	{0,1,1,0} ,
	{0,0,0,0} };
static int tmp2[4][4] = {
	{0,1,0,0},
	{0,1,0,0} ,
	{0,1,0,0} ,
	{0,1,0,0} };
static int tmp3[4][4] = {
	{0,0,1,0},
	{0,0,1,0} ,
	{0,1,1,0} ,
	{0,0,0,0} };
static int tmp4[4][4] = {
	{0,1,0,0},
	{0,1,0,0} ,
	{0,1,1,0} ,
	{0,0,0,0} };
static int tmp5[4][4] = {
	{0,1,0,0},
	{0,1,1,0} ,
	{0,0,1,0} ,
	{0,0,0,0} };
static int tmp6[4][4] = {
	{0,0,1,0},
	{0,1,1,0} ,
	{0,1,0,0} ,
	{0,0,0,0} };
static int tmp7[4][4] = {
	{0,1,0,0},
	{1,1,1,0} ,
	{0,0,0,0} ,
	{0,0,0,0} };

int Get_Random_Number();


class Block_Group {
	friend class Game;
private:
	int Block_Position_x = 0;
	int Block_Position_y = 0;
	int Block_Area[Block_Area_y][Block_Area_x] = { 0 };
public:
	void Block_Copy(int x[4][4]);//复制数组
	void Block_Array_Refresh(int x);//只刷新数组，传入id
	void Block_Group_Refresh(int x);//刷新x,y,二维数组
};
class Game  {
	private:
	Block_Group C_Board_Group;//当前
	Block_Group N_Board_Group;//下一个
	int score = 0;
	int game_area[game_area_y][game_area_x] = { 0 };//0,1（不稳定，红色）,2(稳定，绿色)
public:
	Game() {
		C_Board_Group.Block_Group_Refresh(Get_Random_Number());
		N_Board_Group.Block_Group_Refresh(Get_Random_Number());
	}
	void Paint_Warn_Line();
	void Paint();//全部绘制
	void Paint_BackGround_Window();//背景绘制
	void Request_Window();//询问是否要玩游戏
	void Paint_Game_Area();//绘制游戏区域上个各种状态的方块
	void Paint_Pre_Game_Area();//根据id画出下一个预告方块组
	void Next_Trans_Current_And_Next_Refresh();//N-》C
	void Key_Press();//检测键盘信息
	bool IsCollide_Up();
	bool IsCollide_Down();//能够下降吗
	int IsCollide_Left();//能够左移吗
	int IsCollide_Right();//能够右移吗
	void To_Stable();//直接让C_Board_Group中的1按照位置以2的内容传给game_area
	bool Block_Move_DOWN();//接受了下降指令后，C_Board_Group要进行下降，Block_Position_y会发生改变,并且直接绘制
	void Block_Move_LEFT();//接受了左移指令后，C_Board_Group要进行左移，Block_Position_x会发生改变,并且直接绘制
	void Block_Move_RIGHT();//接受了右移指令后，C_Board_Group要进行右移，Block_Position_x会发生改变,并且直接绘制
	void Block_Move_UP();
	void Block_Move_SPACE();
	void Check_game_area_And_Clear_All_Line_And_Change_Score();//遍历棋盘，所有整行2删除，并且记录删除次数，进行分数计算
	bool IsOver();//游戏结束了吗：结束了返回true
	bool Over_Service();//不想重玩，返回false
};
int Get_N_ID();

