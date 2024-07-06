#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include<graphics.h>//ͼ�ο�ͷ�ļ�
#include<iostream>
#include<easyx.h>//���
#include<conio.h>//ʹ��getch()
#include<stdio.h>
#include<time.h> 
#include <stdlib.h>  
const int game_area_x = 10;//�����ܷŵķ�����
const int game_area_y = 15;//�����ܷŵķ�����
const int Block_Area_x = 4;//�������������ܷŵķ������
const int Block_Area_y = 4;//����������������ܷŵķ������
//����Ķ���
const int Occupied_Part_Length = 36;//ռ�ݲ���
const int Inner_Margin = 2;//�ڱ߾�
const int Border_Fillet = 6;//�߿�Բ��
const int Really_length = 32;//ʵ��߳�
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
	void Block_Copy(int x[4][4]);//��������
	void Block_Array_Refresh(int x);//ֻˢ�����飬����id
	void Block_Group_Refresh(int x);//ˢ��x,y,��ά����
};
class Game  {
	private:
	Block_Group C_Board_Group;//��ǰ
	Block_Group N_Board_Group;//��һ��
	int score = 0;
	int game_area[game_area_y][game_area_x] = { 0 };//0,1�����ȶ�����ɫ��,2(�ȶ�����ɫ)
public:
	Game() {
		C_Board_Group.Block_Group_Refresh(Get_Random_Number());
		N_Board_Group.Block_Group_Refresh(Get_Random_Number());
	}
	void Paint_Warn_Line();
	void Paint();//ȫ������
	void Paint_BackGround_Window();//��������
	void Request_Window();//ѯ���Ƿ�Ҫ����Ϸ
	void Paint_Game_Area();//������Ϸ�����ϸ�����״̬�ķ���
	void Paint_Pre_Game_Area();//����id������һ��Ԥ�淽����
	void Next_Trans_Current_And_Next_Refresh();//N-��C
	void Key_Press();//��������Ϣ
	bool IsCollide_Up();
	bool IsCollide_Down();//�ܹ��½���
	int IsCollide_Left();//�ܹ�������
	int IsCollide_Right();//�ܹ�������
	void To_Stable();//ֱ����C_Board_Group�е�1����λ����2�����ݴ���game_area
	bool Block_Move_DOWN();//�������½�ָ���C_Board_GroupҪ�����½���Block_Position_y�ᷢ���ı�,����ֱ�ӻ���
	void Block_Move_LEFT();//����������ָ���C_Board_GroupҪ�������ƣ�Block_Position_x�ᷢ���ı�,����ֱ�ӻ���
	void Block_Move_RIGHT();//����������ָ���C_Board_GroupҪ�������ƣ�Block_Position_x�ᷢ���ı�,����ֱ�ӻ���
	void Block_Move_UP();
	void Block_Move_SPACE();
	void Check_game_area_And_Clear_All_Line_And_Change_Score();//�������̣���������2ɾ�������Ҽ�¼ɾ�����������з�������
	bool IsOver();//��Ϸ�������𣺽����˷���true
	bool Over_Service();//�������棬����false
};
int Get_N_ID();

