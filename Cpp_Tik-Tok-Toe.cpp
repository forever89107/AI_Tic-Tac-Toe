// Cpp_Tik-Tok-Toe.cpp: 定義主控台應用程式的進入點


#include "stdafx.h"
#include "PcMode.h"
#include<iostream> 
#include<iomanip> 
#include<cstdlib> 
#include<ctime> 
using namespace std;


bool user_play(char map[3][3], bool user_sign);//玩家遊戲  

bool pc_play(char map[3][3], bool pc_sign);//電腦遊戲  

void draw_prompt_map(char map[3][3]);//畫出提示圖，告訴使用者遊戲玩法          

bool judge_repeat(char map[3][3], int location, bool sign);//判斷是否有重複畫記號  

void draw_map(char map[3][3]);//畫出遊戲中的井字圖  

bool judge_line(char map[3][3], bool sign);//判斷各種連線狀況  

void clear_map(char map[3][3]);//將陣列中的字元全部指定成空白字元，以便重新遊戲  

bool full_map(char map[3][3]);//當表格全滿的時候，傳回true  



bool ready_hand(char map[3][3], bool sign);//判斷是否聽牌

int solution(char map[3][3], bool sign);//判斷要用哪種方法解決

int case_1st(char map[3][3], bool sign);//第1種聽牌情況回傳的值

int case_2nd(char map[3][3], bool sign);//第2種聽牌情況回傳的值

int case_3rd(char map[3][3], bool sign);//第3種聽牌情況回傳的值

int case_4th(char map[3][3], bool sign);//第4種聽牌情況回傳的值

bool cross_null(char map[3][3], bool sign);//判斷十字空白

bool corner_null(char map[3][3], bool sign);//判斷角落空白




int main()
{
	bool user_win = false;
	bool pc_win = false;
	bool user_sign, pc_sign;//判斷玩家的符號與電腦的符號  
	char map[3][3];
	char c;//判別玩家想要O or X的變數
	int location;



	cout << "*******************歡迎光臨井字遊戲******************\n" << endl;
	do {
		cout << "輸入1，可以使用o來畫記號。" << endl;
		cout << "輸入2，可以使用x來畫記號。" << endl;
		cin >> c;
		if (c == '1')
		{
			user_sign = true;
			pc_sign = false;
		}
		else if (c == '2')
		{
			user_sign = false;
			pc_sign = true;
		}
	} while (c != '1' && c != '2');//當使用輸入1或2以外的數字時，會要求使用重新輸入  



	draw_prompt_map(map);

	do {

		clear_map(map);//將陣列中的字元全部指定成空白字元  

		do {
			user_win = user_play(map, user_sign);
			if (full_map(map))
			{
				break;//表格全滿時，跳出迴圈    
			}
			pc_win = pc_play(map, pc_sign);
			if (full_map(map))
			{
				break;//表格全滿時，跳出迴圈  
			}

		} while (!user_win && !pc_win);//當雙方都還沒有贏的時候，繼續遊戲  
		if (user_win)
			cout << "恭喜你!!你贏了!!" << endl;
		else if (pc_win)
			cout << "真糟糕!!你輸了!!" << endl;
		else
			cout << "平手!!!" << endl;

		cout << "再來一場?(y)繼續或任意鍵結束" << endl;
		cin >> c;
		system("cls");//清除螢幕  
	} while (c == 'y' || c == 'Y');

	system("pause");
}




bool user_play(char map[3][3], bool user_sign)
{
	int location;//用來紀錄玩家輸入位置的數字
	bool user_or_pc = true;//判斷目前正在遊戲的一方，true為玩家 
	cout << "請選擇要畫記號的位置？" << endl;
	cin >> location;
	while (judge_repeat(map, location, user_sign))//當判斷位置重複時候，重新輸入位置(接收為true就接著做.false就畫圖) 
	{
		cout << "請輸入要畫記號的位置？" << endl;
		cin >> location;
	}
	draw_map(map);

	if (judge_line(map, user_sign))//當玩家贏的時候，傳回true  
	{
		return true;
	}
	return false;
}

bool pc_play(char map[3][3], bool pc_sign)
{
	int location;
	bool user_or_pc = false;//判斷目前正在遊戲的一方，false為電腦
	bool player_sign = !pc_sign;
	do {
		int work_step = 1;

		//1st_判斷電腦是否聽牌，如果聽牌照傳回值下，沒聽牌往下一個方法做
		if (work_step == 1) {

			while (ready_hand(map, pc_sign))
			{
				int solution_ans;
				//用ans呼叫解決辦法，用哪種?
				solution_ans = solution(map, pc_sign);
				//cout << "solution_ans傳回值是:" << solution_ans << endl;
				switch (solution_ans)
				{
					int ans;
				case 1:
					ans = case_1st(map, pc_sign);//第1種聽牌情況回傳的值
					cout << "列聽牌了傳回值是:" << ans << endl;
					location = ans;
					break;
				case 2:
					ans = case_2nd(map, pc_sign);//第2種聽牌情況回傳的值
					cout << "行聽牌了傳回值是:" << ans << endl;
					location = ans;
					break;
				case 3:
					ans = case_3rd(map, pc_sign);//第3種聽牌情況回傳的值
					//cout << "左上~右下斜線聽牌了傳回值是:" << ans << endl;
					location = ans;
					break;
				case 4:
					ans = case_4th(map, pc_sign);//第4種聽牌情況回傳的值
					//cout << "左下~右上聽牌了傳回值是:" << ans << endl;
					location = ans;
					break;
				}
				break;
			}
			//if while=1 有執行 work_step=0  else work_step++;
			bool value = false;
			value = ready_hand(map, pc_sign);
			//cout << "電腦ready_hand判斷完了value是:" << value << endl;
			if (value == true)
			{
				work_step = 0;
			}
			else
			{
				work_step++;
			}
			//cout << "ready_hand判斷完了work_step是:" << work_step << endl;
		}

		//2nd_判斷玩家是否聽牌，如果聽牌照傳回值下，沒聽牌往下一個方法做
		if (work_step == 2) {

			while (ready_hand(map, player_sign))
			{
				int solution_ans;
				//用ans呼叫解決辦法，用哪種?
				solution_ans = solution(map, player_sign);
				//cout << "solution_ans傳回值是:" << solution_ans << endl;
				switch (solution_ans)
				{
					int ans;
				case 1:
					ans = case_1st(map, player_sign);//第1種聽牌情況回傳的值
					//cout << "玩家列聽牌了傳回值是:" << ans << endl;
					location = ans;
					break;
				case 2:
					ans = case_2nd(map, player_sign);//第2種聽牌情況回傳的值
					//cout << "玩家行聽牌了傳回值是:" << ans << endl;
					location = ans;
					break;
				case 3:
					ans = case_3rd(map, player_sign);//第3種聽牌情況回傳的值
					//cout << "玩家左上~右下斜線聽牌了傳回值是:" << ans << endl;
					location = ans;
					break;
				case 4:
					ans = case_4th(map, player_sign);//第4種聽牌情況回傳的值
					//cout << "玩家左下~右上聽牌了傳回值是:" << ans << endl;
					location = ans;
					break;
				}
				break;
			}
			//if while=1 有執行 work_step=0  else work_step++;
			bool value = false;
			value = ready_hand(map, player_sign);
			//cout << "玩家ready_hand判斷完了value是:" << value << endl;
			if (value == true)
			{
				work_step = 0;
			}
			else
			{
				work_step++;
			}
			//cout << "ready_hand判斷完了work_step是:" << work_step << endl;
		}

		//3rd_如果沒聽牌且中間位置空白搶中間位置
		if (work_step == 3)
		{
			if (map[1][1] == ' ')
			{
				location = 5;
				work_step = 0;
			}
			else if (map[1][1] != ' ')
			{
				work_step++;
			}
			//cout << "中間空白判斷完了work_step是:" << work_step << endl;
		}

		//4th_判斷4個角落是否有空位(OK)

		if (work_step == 4)
		{
			//cout << "while corner_null要執行了" << endl;
			while (corner_null(map, pc_sign)) //while值faulse跳出回圈(沒重複)往下做，是true就會圈內繼續做)
			{
				//如果4角有空位，就隨機選個空位
				int corner[4];
				if (map[0][0] == ' ') { corner[0] = 1; }
				else { corner[0] = 0; }
				if (map[0][2] == ' ') { corner[1] = 3; }
				else { corner[1] = 0; }
				if (map[2][0] == ' ') { corner[2] = 7; }
				else { corner[2] = 0; }
				if (map[2][2] == ' ') { corner[3] = 9; }
				else { corner[3] = 0; }

				srand(time(0));
				int i = rand() % 4;
				//cout << "corner[i]是:" << corner[i] << endl;
				if (corner[i] != 0)
				{
					location = corner[i];
					//cout << "while corner_null有執行(break前1)" << endl;
					break;//不會跳出do
				}
				else if (corner[0] == 0 && corner[1] == 0 && corner[2] == 0 && corner[3] == 0)
				{
					location = ' ';
					//cout << "while corner_null有執行(break前2)" << endl;
					break;//不會跳出do
				}
				//cout << "while corner_null有執行(break後)" << endl;
			}
			//if while=1 有執行 work_step=0  else work_step++;
			bool value = false;
			value = corner_null(map, pc_sign);
			//cout << "while corner_null判斷完了value是:" << value << endl;
			if (value == true)
			{
				work_step = 0;
			}
			else
			{
				work_step++;
			}
			//cout << "while corner_null判斷完了work_step是:" << work_step << endl;

		}
		//5th_判斷十字方向是否空白(OK)
		if (work_step == 5)
		{
			//cout << "while cross_null要執行了" << endl;
			while (cross_null(map, pc_sign))
			{
				//如果十字有空位，就隨機選個空位
				int corner[4];
				if (map[0][1] == ' ') { corner[0] = 2; }
				else { corner[0] = 0; }
				if (map[1][0] == ' ') { corner[1] = 4; }
				else { corner[1] = 0; }
				if (map[1][2] == ' ') { corner[2] = 6; }
				else { corner[2] = 0; }
				if (map[2][1] == ' ') { corner[3] = 8; }
				else { corner[3] = 0; }

				srand(time(0));
				int i = rand() % 4;
				//cout << "corner[i]是:" << corner[i] << endl;
				if (corner[i] != 0)
				{
					location = corner[i];
					break;
				}
				else if (corner[0] == 0 && corner[1] == 0 && corner[2] == 0 && corner[3] == 0)
				{
					location = ' ';
					break;
				}
			}
		}

	} while (judge_repeat(map, location, pc_sign));//while值faulse跳出回圈(沒重複)往下做，是true就會圈繼續做，

	draw_map(map);
	if (judge_line(map, pc_sign))//當電腦贏的時候，傳回true  
	{
		return true;
	}
	return false;
}

int asd(char map[3][3], bool sign)
{
	if (map[1][1] = ' ')
	{
		return 7;
	}
}





//畫出提示圖，告訴使用者遊戲玩法    
void draw_prompt_map(char map[3][3])
{
	int num = 1;
	cout << "\n格子中的數字代表輸入代號！" << endl;
	for (int row = 0; row < 3; row++)//利用迴圈來畫出井字表格  
	{
		for (int column = 0; column < 3; column++, num++)
		{
			//int的整數值加上48之後，等於char的同等整數(由ascii表得知)  
			map[row][column] = num + 48;
			cout << "  " << map[row][column] << setw(3);
			if (column <= 1)cout << "|";
			map[row][column] = ' ';//num設為空白重新輸入數字
		}
		cout << endl;
		if (row <= 1)cout << "-----------------";
		cout << endl;
	}
}
//判斷是否有重複畫記號  
bool judge_repeat(char map[3][3], int location, bool sign)
{
	int row, column;
	//由於陣列索引值是從0開始，但是位置的數字是從1開始，所以要減1才能符合陣列索引規則  
	location--;//位置1~9 --> 0~8

	row = location / 3;//將輸入的數字換成表格 列 座標  
	column = location % 3;//將輸入的數字換成表格 行 座標    
	if (map[row][column] == ' ')
	{
		if (sign == true)//判斷傳入的sign是true就畫上O  
		{
			map[row][column] = 'O';//畫上記號 
		}
		else //反之，就畫上X  
		{
			map[row][column] = 'X';//畫上記號    
		}
		return false;//代表沒有重複  
	}
	else
	{
		return  true;
	}

}

//畫出遊戲中的井字圖 
void draw_map(char map[3][3])
{
	int row, column;

	for (row = 0; row < 3; row++)//利用迴圈來設置表格  
	{
		for (column = 0; column < 3; column++)
		{	//每6個 - 給一個 |
			cout << setw(3) << map[row][column] << setw(3);
			if (column <= 1)cout << "|";
		}
		cout << endl;
		if (row <= 1)cout << "-----------------";//17個 - 
		cout << endl;
	}
}

//將陣列中的字元全部指定成空白字元  
void clear_map(char map[3][3])
{
	for (int row = 0; row < 3; row++)
	{
		for (int column = 0; column < 3; column++)
		{
			map[row][column] = ' ';
		}
	}
}
//檢查表格是否全滿  
bool full_map(char map[3][3])
{
	int no_white_space = 0;
	for (int row = 0; row < 3; row++)
	{
		for (int column = 0; column < 3; column++)
		{
			if (map[row][column] != ' ')
			{
				no_white_space++;
			}
		}
	}
	//當表格沒有任何的white space 時，代表全滿，並且傳回true  
	if (no_white_space == 9)
	{
		return true;
	}
	else
		return false;
}

//判斷各種連線狀況   
bool judge_line(char map[3][3], bool sign)
{
	int counter = 0, row, column;
	char process_sign;//用來接收 user_sign或pc_sign的bool
	if (sign == true)
	{
		process_sign = 'O';//決定要判斷是否連線的符號  
	}
	else
	{
		process_sign = 'X';//決定要判斷是否連線的符號  
	}

	for (row = 0; row < 3; row++)//1st_判斷每列是否有連線  
	{
		for (column = 0; column < 3; column++)
		{
			if (map[row][column] == process_sign)
				counter++;
			if (counter == 3)/*連線成功*/
				return true;
		}
		counter = 0;//那行檢查完歸0，在檢查下一行
	}
	for (column = 0; column < 3; column++) //2nd_判斷每行是否有連線  
	{
		for (row = 0; row < 3; row++)
		{
			if (map[row][column] == process_sign)
				counter++;
			if (counter == 3)/*連線成功*/
				return true;
		}
		counter = 0;//那列檢查完歸0，在檢查下一列
	}
	if (map[0][0] == map[1][1] && map[1][1] == map[2][2] && map[2][2] == process_sign)
	{
		return true;/*連線成功*/
	}
	//4th_判斷左下~右上方向對角線是否有連線  
	if (map[0][2] == map[1][1] && map[1][1] == map[2][0] && map[2][0] == process_sign)
	{
		return true;/*連線成功*/
	}

	return false;
}


bool ready_hand(char map[3][3], bool sign)//判斷是否聽牌
{
	int counter = 0, null = 0, row, column;
	char process_sign;//用來接收pc_sign的bool
	if (sign == true)
	{
		process_sign = 'O';//決定要判斷是否連線的符號  
	}
	else
	{
		process_sign = 'X';//決定要判斷是否連線的符號  
	}
	//1st_判斷每列是否有聽牌  
	for (row = 0; row < 3; row++)
	{
		for (column = 0; column < 3; column++)
		{

			if (map[row][column] == ' ')
				null++;
			if (map[row][column] == process_sign)
				counter++;
			if (counter == 2 && null == 1)/*聽牌*/
			{
				return true;
			}

		}
		null = 0;//那行檢查完歸0，在檢查下一行
		counter = 0;//那行檢查完歸0，在檢查下一行
	}

	//2nd_判斷每行是否有聽牌 
	for (column = 0; column < 3; column++)
	{
		for (row = 0; row < 3; row++)
		{
			if (map[row][column] == ' ')
				null++;
			if (map[row][column] == process_sign)
				counter++;
			if (counter == 2 && null == 1)/*聽牌*/
			{
				return true;
			}
		}
		null = 0;//那列檢查完null歸0，再檢查下一列
		counter = 0;//那列檢查完counter歸0，再檢查下一列
	}

	//3rd_判斷左上~右下方向對角線是否有聽牌  
	if ((map[0][0] == map[1][1] && map[1][1] == process_sign && map[2][2] == ' ') ||//這項OK
		(map[0][0] == map[2][2] && map[2][2] == process_sign && map[1][1] == ' ') ||
		(map[1][1] == map[2][2] && map[2][2] == process_sign && map[0][0] == ' '))//這項OK
	{
		return true;//左上~右下方向聽牌了
	}
	
	//4th_判斷最右上~左下到最左下是否有聽牌  
	if ((map[0][2] == map[1][1] && map[1][1] == process_sign && map[2][0] == ' ') ||//這條沒有
		(map[0][2] == map[2][0] && map[2][0] == process_sign && map[1][1] == ' ') ||
		(map[1][1] == map[2][0] && map[2][0] == process_sign && map[0][2] == ' '))//這條沒有
	{
		return true;/*最右上到最左下聽牌了*/
	}
	
		return false;
}

int solution(char map[3][3], bool sign)
{
	int counter = 0, null = 0, row, column;
	char process_sign;//用來接收 user_sign或pc_sign的bool
	if (sign == true)
	{
		process_sign = 'O';//決定要判斷是否連線的符號  
	}
	else
	{
		process_sign = 'X';//決定要判斷是否連線的符號  
	}

	//1st_判斷每列是否有聽牌
	for (row = 0; row < 3; row++)
	{
		for (column = 0; column < 3; column++)
		{
			if (map[row][column] == ' ')
				null++;
			if (map[row][column] == process_sign)
				counter++;
			if (counter == 2 && null == 1)/*聽牌*/
			{
				return 1;
			}

		}
		null = 0;//檢查完歸0，在檢查下一行
		counter = 0;//檢查完歸0，在檢查下一行
	}

	//2nd_//判斷每行是否有聽牌 
	for (column = 0; column < 3; column++)
	{
		for (row = 0; row < 3; row++)
		{
			if (map[row][column] == ' ')
				null++;
			if (map[row][column] == process_sign)
				counter++;
			if (counter == 2 && null == 1)/*聽牌*/
			{
				return 2;
			}
		}
		null = 0;//檢查完null歸0，再檢查下一列
		counter = 0;//檢查完counter歸0，再檢查下一列
	}

	//3rd_判斷左上~右下方向對角線是否有聽牌  
	if ((map[0][0] == map[1][1] && map[1][1] == process_sign && map[2][2] == ' ') ||//這項OK
		(map[0][0] == map[2][2] && map[2][2] == process_sign && map[1][1] == ' ') ||
		(map[1][1] == map[2][2] && map[2][2] == process_sign && map[0][0] == ' '))//這項OK
	{
		return 3;//左上~最右下到最左下聽牌了
	}
	//4th_判斷最右上到最左下是否有聽牌  
	else if((map[0][2] == map[1][1] && map[1][1] == process_sign && map[2][0] == ' ') ||//這條沒有
		(map[0][2] == map[2][0] && map[2][0] == process_sign && map[1][1] == ' ') ||
		(map[1][1] == map[2][0] && map[2][0] == process_sign && map[0][2] == ' '))//這條沒有
	{
		return 4;/*最左下~右上到最左下聽牌了*/
	}

	return false;



}


int case_1st(char map[3][3], bool sign)//第1種聽牌情況回傳的值
{
	char process_sign;//用來接收 user_sign或pc_sign的bool
	if (sign == true)
	{
		process_sign = 'O';//決定要判斷是否連線的符號  
	}
	else
	{
		process_sign = 'X';//決定要判斷是否連線的符號  
	}

	//第一列聽牌的可能性
	if (map[0][0] == map[0][1] && map[0][0] == process_sign)
	{
		return 3;
	}
	else if (map[0][0] == map[0][2] && map[0][0] == process_sign)
	{
		return 2;
	}
	else if (map[0][1] == map[0][2] && map[0][1] == process_sign)
	{
		return 1;

	}

	//第二列聽牌的可能性
	else if (map[1][0] == map[1][1] && map[1][0] == process_sign)
	{
		return 6;
	}
	else if (map[1][0] == map[1][2] && map[1][0] == process_sign)
	{
		return 5;
	}
	else if (map[1][1] == map[1][2] && map[1][1] == process_sign)
	{
		return 4;
	}

	//第三列聽牌的可能性
	else if (map[2][0] == map[2][1] && map[2][0] == process_sign)
	{
		return 9;
	}
	else if (map[2][0] == map[2][2] && map[2][0] == process_sign)
	{
		return 8;
	}
	else if (map[2][1] == map[2][2] && map[2][1] == process_sign)
	{
		return 7;
	}
}

int case_2nd(char map[3][3], bool sign)//第2種聽牌情況回傳的值
{
	char process_sign;//用來接收 user_sign或pc_sign的bool
	if (sign == true)
	{
		process_sign = 'O';//決定要判斷是否連線的符號  
	}
	else
	{
		process_sign = 'X';//決定要判斷是否連線的符號  
	}

	//第一行聽牌的可能性
	if (map[0][0] == map[1][0] && map[0][0] == process_sign)
	{
		return 7;
	}
	else if (map[0][0] == map[2][0] && map[0][0] == process_sign)
	{
		return 4;
	}
	else if (map[1][0] == map[2][0] && map[1][0] == process_sign)
	{
		return 1;

	}

	//第二行聽牌的可能性
	else if (map[0][1] == map[1][1] && map[0][1] == process_sign)
	{
		return 8;
	}
	else if (map[0][1] == map[2][1] && map[0][1] == process_sign)
	{
		return 5;
	}
	else if (map[1][1] == map[2][1] && map[1][1] == process_sign)
	{
		return 2;
	}

	//第三行聽牌的可能性
	else if (map[0][2] == map[1][2] && map[0][2] == process_sign)
	{
		return 9;
	}
	else if (map[0][2] == map[2][2] && map[0][2] == process_sign)
	{
		return 6;
	}
	else if (map[1][2] == map[2][2] && map[1][2] == process_sign)
	{
		return 3;
	}
}

int case_3rd(char map[3][3], bool sign)//第3種聽牌情況回傳的值
{
	char process_sign;//用來接收 user_sign或pc_sign的bool
	if (sign == true)
	{
		process_sign = 'O';//決定要判斷是否連線的符號  
	}
	else
	{
		process_sign = 'X';//決定要判斷是否連線的符號  
	}


	if (map[0][0] == map[1][1] && map[0][0] == process_sign)
	{
		return 9;
	}
	else if (map[1][1] == map[2][2] && map[1][1] == process_sign)
	{
		return 1;
	}
	else if (map[0][0] == map[2][2] && map[0][0] == process_sign)
	{
		return 5;
	}
}

int case_4th(char map[3][3], bool sign)//第4種聽牌情況回傳的值
{
	char process_sign;//用來接收 user_sign或pc_sign的bool
	if (sign == true)
	{
		process_sign = 'O';//決定要判斷是否連線的符號  
	}
	else
	{
		process_sign = 'X';//決定要判斷是否連線的符號  
	}


	if (map[0][2] == map[1][1] && map[0][2] == process_sign)
	{
		return 7;
	}
	else if (map[1][1] == map[2][0] && map[1][1] == process_sign)
	{
		return 3;
	}
	else if (map[0][2] == map[2][0] && map[0][2] == process_sign)
	{
		return 5;
	}
}


//判斷十字是否空白，並給數字
bool cross_null(char map[3][3], bool sign)
{
	char process_sign;//用來接收 user_sign或pc_sign的bool
	if (map[0][1] == ' ' || map[1][0] == ' ' || map[1][2] == ' ' || map[2][1] == ' ')
	{
		return true;
	}
	else
	{
		return false;
	}
}
//判斷角落是否空白
bool corner_null(char map[3][3], bool sign)
{
	char process_sign;//用來接收 user_sign或pc_sign的bool
	if (sign == true)
	{
		process_sign = 'O';//決定要判斷是否連線的符號  
	}
	else
	{
		process_sign = 'X';//決定要判斷是否連線的符號  
	}
	if (map[0][0] == ' ' || map[0][2] == ' ' || map[2][0] == ' ' || map[2][2] == ' ')
	{
		return true;
	}
	else
	{
		return false;
	}
}
