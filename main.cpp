
#include"game.h"


int main() {
    srand(time(NULL));
		clock_t starttime, endtime = 0;

		initgraph(600, 540, 1);
		while (1) {
			Game tmp;
			tmp.Paint_BackGround_Window();
			tmp.Request_Window();
			tmp.Paint_Pre_Game_Area();
			starttime = clock();
			while (1) {
				BeginBatchDraw();
				/* ���ƺ���*/
				tmp.Paint();
				endtime = clock();
				if (endtime - starttime > 1000) {
					starttime = clock();
					BeginBatchDraw();
					/* ���ƺ���*/
					tmp.Block_Move_DOWN();
					//���Ƶ����ݣ����ÿ�����½�һ��
					FlushBatchDraw();
				}
				FlushBatchDraw();
				tmp.Key_Press();
				tmp.Check_game_area_And_Clear_All_Line_And_Change_Score();
				if (tmp.IsOver()) {
					if (!tmp.Over_Service()) {
						closegraph();
						return 0;
					}
					break;
				}
				cleardevice();
			}
			cleardevice();
		}
		
}


