#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include<string.h>
#include<cstring>
#include<sstream>
#include <windows.h>
#pragma warning(disable:4996)
using namespace std;
string temp = "";//error count
string person = "";//player account
string job = " ";//job
string die = " ";
string idx_job[3] = { "法師","劍士","弓兵" };
int position = 0;//position 0 1 2 3 4
string idx_position[5] = { "城市","家","商店","海邊","森林" };
int Sundries[13];//Sundriesbag.txt
int shop[12] = { 99,99,99,99,99,99,99,99,99,99,99,99 };
int wshop[9] = { 99,99,99,99,99,99,99,99,99 };
string idx_Sundries[12] = { "低階HP藥水", "中階HP藥水", "高階HP藥水", "低階MP藥水", "中階MP藥水" ,"高階MP藥水" ,"中階魔石" ,"高階魔石" ,"龍牙" ,"中階星塵" ,"高階星塵" ,"輔助器" };										  																																											   
int ab[7];//ability.txt
int battle(int x, int lv, int hp, int atk, int ex);
int saveability();
int weapon[21];
int abw[3];
int exab[3];//裝備能力
int exaab;//套裝能力  
string wea[22] = { "未穿裝" , "初級法杖", "中級法杖", "高級法杖", "贗造魔女", "低級法袍" ,"高級法袍" ,"魔戒" ,"初級劍", "中級劍", "高級劍", "聖劍", "低級鎧甲" ,"高級鎧甲" ,"劍鞘","初級弓", "中級弓", "高級弓", "槍", "低級瞄準器" ,"高級瞄準器" ,"指虎"};
int wea_ab[22] = { 0,10,30,50,999,20,40,40,10,30,50,999,20,40,40,10,30,50,999,20,40,40};
int saveshop();
int savewshop();
int savemap();
int savewbag();
int savebag();
int saveweapon();
int saveability();
/// /////////////////////////////////////////////////
void tree()
{
	cout << endl << endl;
	cout << "                   　　　　　　　　　　　　　　		     期末 RPG" << endl;
	cout << "                   　　　　　　　　　　　　　　		請選擇 操作 方式" << endl;
}
/// ////////////////////////////////////////////////
int in() {
	int n = 0;
	int count = 0;
	int out = 0;
	cout << endl << endl << endl;
top:
	cout << endl;
	cout << "                   　　　　　　　　　　　　　　		1:註冊" << endl;
	cout << "                   　　　　　　　　　　　　　　		2:登入" << endl;
	cout << "                   　　　　　　　　　　　　　　		3:結束遊戲" << endl;
	cin >> n;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto top;
	}
top1:
	string account = " ";
	string password = " ";
	string line1;
	string line2;
	int asd = 0;
	if (n == 1) {
		count = 0;
		cout << "                   　　　　　　　　　　　　　　		請輸入帳號:";
		cin >> line1;
		cout << "                   　　　　　　　　　　　　　　		請輸入密碼:";
		cin >> line2;

		if (isalpha(line1[0]) != 0) {

			if (islower(line1[0]) != 0) {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		帳號開頭請使用英文大寫" << endl;
				goto top;
			}

		}

		if (isalpha(line1[0]) == 0) {
			cout << endl;
			cout << "                   　　　　　　　　　　　　　　		帳號開頭不能使用數字" << endl;
			goto top;
		}

		ifstream fin;
		fin.open("person.txt");
		while (fin >> account >> password) {

			if (line1 == account) {

				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		輸入帳號已註冊" << endl;
				goto top;
			}
		}
		fin.close();

		ofstream fout;
		fout.open("person.txt", ios::app);
		fout << line1 << " " << line2 << endl;
		cout << endl;
		cout << "                   　　　　　　　　　　　　　　		註冊成功" << endl;
		fout.close();
		goto top;

	}

	else if (n == 2)
	{
		cout << "                   　　　　　　　　　　　　　　		請輸入帳號:";
		cin >> line1;
		cout << "                   　　　　　　　　　　　　　　		請輸入密碼:";
		cin >> line2;

		ifstream fin;
		fin.open("person.txt");
		while (fin >> account >> password) {

			if (line1 == account && line2 == password) {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		登入成功" << endl;
				count = 0;
				asd = 1;
				out = 1;
				person = line1;
			}
		}
		fin.close();

		if (asd == 0) {
			int error1 = 0;
			int error2 = 0;
			ifstream fin;
			fin.open("person.txt");
			while (fin >> account >> password) {
				if (line1 == account && line2 != password) {
					error1 = 1;

				}
				else if (line1 != account) {
					error2 = 1;
					//cout << "not";
				}
			}
			fin.close();
			//cout << "temp=" << temp << endl;
			if (temp != line1) {
				count = 0;
			}
			if (error1 == 1) {
				count++;
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		密碼錯誤 " << " error " << count << endl;
				//cout << "line1=" << line1 << endl;
				temp = line1;
				if (count < 3) {
					goto top;
				}
				else {
					goto top2;
				}
			}

			if (error2 == 1) {
				count = 0;
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		未註冊" << endl;
				goto top;
			}
			/// 直接登入
			
			if (error2 == 0) {
				count = 0;
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		未註冊" << endl;
				goto top;
			}
			
			
		top2:
			n = 0;
			count = 0;
			cout << endl;
			cout << "                   　　　　　　　　　　　　　　		1:註冊" << endl;
			cout << "                   　　　　　　　　　　　　　　		2:登入" << endl;
			cout << "                   　　　　　　　　　　　　　　		3:結束遊戲" << endl;
			cout << "                   　　　　　　　　　　　　　　		4:重設密碼" << endl;
			cin >> n;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto top2;
			}
			if (n == 1) {
				goto top1;
			}
			if (n == 2) {
				goto top1;
			}
			if (n == 3) {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		感謝您的遊玩" << endl;
				return 0;
			}
			if (n == 4) {
			top3:
				//cout << "line1=" << line1 << endl;
				cout << endl;
				string input1;
				string input2;
				cout << "                   　　　　　　　　　　　　　　		輸入新密碼" << endl;
				cin >> input1;
				cout << "                   　　　　　　　　　　　　　　		再次輸入新密碼" << endl;
				cin >> input2;
				if (input1 != input2) {
					cout << "                   　　　　　　　　　　　　　　		密碼不一致" << endl;
					goto top3;
				}
				else {
					/////////////
					ifstream fin;
					fin.open("person.txt");
					while (fin >> account >> password) {
						if (line1 == account) {

							continue;
						}
						else {
							ofstream fout;
							fout.open("person101.txt", ios::app);
							fout << account << " " << password << endl;
							fout.close();
						}
					}
					fin.close();
					ofstream fout;
					fout.open("person101.txt", ios::app);
					fout << line1 << " " << input2 << endl;
					fout.close();
					remove("person.txt");
					rename("person101.txt", "person.txt");
				}
				goto top;
			}

			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效字元" << endl;
				goto top2;

			}
		}
	}
	else if (n == 3) {
	    system("cls");
		cout << endl;
		cout << "                   　　　　　　　　　　　　　　		感謝您的遊玩" << endl << endl;
		return 0;
	}

	else {
		cout << endl;
		cout << "                   　　　　　　　　　　　　　　		無效字元" << endl;
		goto top;
	}

	if (out == 1) {
		out = 0;
		int mod = 0;
	top4:
		cout << endl;
		cout << "                   　　　　　　　　　　　　　　		1---登出" << endl;
		cout << "                   　　　　　　　　　　　　　　		2---開始遊戲" << endl;
		cin >> mod;
		while (cin.fail()) {
			cout << "無效指令!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');
			goto top4;
		}
		if (mod == 1) {
			system("cls");
			cout << endl;
			cout << "                   　　　　　　　　　　　　　　		  已登出" << endl;
			cout << endl << endl;
			goto top;
		}
		if (mod == 2) {
			system("cls");
			cout << "                   　　　　　　　　　　　　　　		正在開始遊戲" << endl;
			return 1;
		}
		else {
			cout << endl;
			cout << "                   　　　　　　　　　　　　　　		無效字元" << endl;
			goto top4;
		}
	}
}
/// ////////////////////////////////////////////////
int text() {
	cout << endl << endl << endl;
begin2:
	cout << "                                 ------------------------歡迎RPG世界--------------------" << endl;
	cout << "             ________________________________________________________________________________________________________" << endl;
	cout << "                                　　　                   玩家名稱: ---" << person << endl << endl;
	cout << "					　1----進入職業:    " << "2----刪除職業:    "<< endl;
	int n = 0;
	cin >> n;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto begin2;
	}
	switch (n) {
		case 1:
			return 1;
		case 2:
			return 2;
		default:
			cout << endl;
			cout << "                   　　　　　　　　　　　　　　		無效字元" << endl;
			goto begin2;
	}

}
/// ////////////////////////////////////////////////

int ability() {
begin1:
	cout << "                                    　　　              請選擇職業" << endl << endl;
	cout << "					　1----法師:    " << "2----劍士:    " << "3----弓兵:    " << endl;
	int n = 0;
	cin >> n;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto begin1;
	}
	if (n == 1 || n == 2 || n == 3) {
		job = idx_job[n - 1];
	}
	else {
		cout << endl;
		cout << "                   　　　　　　　　　　　　　　		無效字元" << endl;
		goto begin1;
	}
	int ability[7] = { 0,0,0,0,0,0,0 };
	string account = " ";
	string profession = " ";
	ifstream fin;
	fin.open("ability.txt");
	while (fin >> account >> profession >> ability[0] >> ability[1] >> ability[2] >> ability[3] >> ability[4] >> ability[5] >> ability[6] ) {
		if (person == account && job == profession) {
			if(profession == "法師"){
				for (int i = 0; i < 7; i++) {
					ab[i] = ability[i];
				}
			}
			else if (profession == "劍士") {
				for (int i = 0; i < 7; i++) {
					ab[i] = ability[i];
				}
			}
			else if (profession == "弓兵") {
				for (int i = 0; i < 7; i++) {
					ab[i] = ability[i];
				}
			}
			return 0;
		}
	}
	//cout << endl;
	fin.close();

	ofstream fout;
	fout.open("ability.txt", ios::app);//初始值
	if (n == 1) {
		fout << person << " " << job << " " << "1" << " " << "100" << " " << "100" << " " << "0" << " " << "30" << " " << "30" << " " << "0" << endl;//lv hp maxhp atk mp maxmp ex
		ab[0] = 1;
		ab[1] = 100;
		ab[2] = 100;
		ab[3] = 0;
		ab[4] = 30;
		ab[5] = 30;
		ab[6] = 0;
	}
	else if (n == 2) {
		fout << person << " " << job << " " << "1" << " " << "100" << " " << "100" << " " << "30" << " " << "0" << " " << "0" << " " << "0" << endl;//lv hp maxhp atk mp maxmp ex
		ab[0] = 1;
		ab[1] = 100;
		ab[2] = 100;
		ab[3] = 30;
		ab[4] = 0;
		ab[5] = 0;
		ab[6] = 0;
	}
	else if (n == 3) {
		fout << person << " " << job << " " << "1" << " " << "100" << " " << "100" << " " << "15" << " " << "15" << " " << "15" << " " << "0" << endl;//lv hp maxhp atk mp maxmp ex
		ab[0] = 1;
		ab[1] = 100;
		ab[2] = 100;
		ab[3] = 15;
		ab[4] = 15;
		ab[5] = 15;
		ab[6] = 0;
	}
	fout.close();
	return 0;
}

int monster() {
RF:
	int n = 0;
	cout << "                   　　　　　　　　　　1---戰鬥" << "    　　　		2---離開" << endl;
	cin >> n;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto RF;
	}
	if (n == 1) {
		srand((unsigned)time(NULL));//not in while
		while (1) {
		fish11:
			int x = rand() % 10;
			if (x == 0) {
				cout << "出現了小狗狗" << endl;
				int lv = rand() % 10 + 1;
				int hp = rand() % 140 + 1;
				int atk = rand() % 25 + 1;
				int ex = rand() % 30 + 1;
				battle(x, lv, hp, atk, ex);
			}
			else if (x == 1) {
				cout << "出現了月月" << endl;
				int lv = rand() % 10 + 11;
				int hp = rand() % 210 + 1;
				int atk = rand() % 33 + 1;
				int ex = rand() % (50 - 29) + 30;
				battle(x, lv, hp, atk, ex);
			}
			else if (x == 2) {
				cout << "出現了殭屍" << endl;
				int lv = rand() % 10 + 21;
				int hp = rand() % 280 + 1;
				int atk = rand() % 50 + 1;
				int ex = rand() % (70 - 49) + 50;
				battle(x, lv, hp, atk, ex);
			}
			else if (x == 3) {
				cout << "出現了惡魔" << endl;
				int lv = rand() % 10 + 31;
				int hp = rand() % 200 + 1;
				int atk = rand() % 35 + 1;
				int ex = rand() % (90 - 69) + 70;
				battle(x, lv, hp, atk, ex);
			}
			else if (x == 4) {
				cout << "出現了龍" << endl;
				int lv = rand() % 10 + 41;
				int hp = rand() % 300 + 1;
				int atk = rand() % 46 + 1;
				int ex = rand() % (110 - 89) + 90;
				battle(x, lv, hp, atk, ex);
			}
			else if (x == 5) {
				cout << "出現了小狗狗2" << endl;
				int lv = rand() % 10 + 51;
				int hp = rand() % 400 + 1;
				int atk = rand() % 70 + 1;
				int ex = rand() % (130 - 109) + 110;
				battle(x, lv, hp, atk, ex);
			}
			else if (x == 6) {
				cout << "出現了月月2" << endl;
				int lv = rand() % 10 + 61;
				int hp = rand() % 590 + 1;
				int atk = rand() % 50 + 1;
				int ex = rand() % (150 - 129) + 130;
				battle(x, lv, hp, atk, ex);
			}
			else if (x == 7) {
				cout << "出現了殭屍2" << endl;
				int lv = rand() % 10 + 71;
				int hp = rand() % 885 + 1;
				int atk = rand() % 66 + 1;
				int ex = rand() % (170 - 149) + 150;
				battle(x, lv, hp, atk, ex);
			}
			else if (x == 8) {
				cout << "出現了惡魔2" << endl;
				int lv = rand() % 10 + 81;
				int hp = rand() % 1180 + 1;
				int atk = rand() % 100 + 1;
				int ex = rand() % (190 - 169) + 170;
				battle(x, lv, hp, atk, ex);
			}
			else if (x == 9) {
				cout << "出現了龍2" << endl;
				int lv = rand() % 10 + 91;
				int hp = rand() % 1288 + 1;
				int atk = rand() % 100 + 1;
				int ex = rand() % (210 - 189) + 190;
				battle(x, lv, hp, atk, ex);
			}
			cout << endl;
		fish00:
			saveshop();
			savewshop();
			savemap();
			savewbag();
			savebag();
			saveweapon();
			saveability();
			int m = 0;
			cout << "                   　　　　　　　　　　1---繼續戰鬥" << "    　　　		2---離開" << endl;
			cin >> m;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto fish00;
			}
			if (m == 1) {
				system("cls");
				goto fish11;
			}
			else if (m == 2) {
				system("cls");
				return 0;
			}
			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
				goto fish00;
			}
		}
	}
	else if (n == 2) {
		return 0;
	}
	else {
		cout << endl;
		cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
		goto RF;
	}
	return 0;
}

/// ////////////////////////////////////////////////
int battle(int x, int lv, int hp, int atk, int ex) {
	srand((unsigned)time(NULL));//not in while
	string monster[10] = { "小狗狗", "月月", "殭屍", "惡魔", "龍" ,"小狗狗2", "月月2", "殭屍2", "惡魔2", "龍2" };
	cout << monster[x] << "   lv:" << lv << "   hp:" << hp << "   atk:" << atk << endl;
	int abillty[7] = { 0,0,0,0,0,0,0};
	string account = " ";
	string profession = " ";
	ifstream fin;
	fin.open("ability.txt");
	while (fin >> account >> profession >> abillty[0] >> abillty[1] >> abillty[2] >> abillty[3] >> abillty[4] >> abillty[5] >> abillty[6]) {
		if (person == account && job == profession) {
			if (profession == "法師") {
				for (int i = 0; i < 7; i++) {
					ab[i] = abillty[i];
				}
			}
			else if (profession == "劍士") {
				for (int i = 0; i < 7; i++) {
					ab[i] = abillty[i];
				}
			}
			else if (profession == "弓兵") {
				for (int i = 0; i < 7; i++) {
					ab[i] = abillty[i];
				}
			}
		}
	}
	fin.close();
GG:	if (ab[1] == 0) {
		cout << "你已經死了" << endl;
		cout << "回復?" << endl;
		cout << "1---yes    2---no" << endl;
		int aa;
		cin >> aa;
		while (cin.fail()) {
			cout << "無效指令!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');
			goto GG;
		}
		if (aa == 1) {
			cout << ". ";
			Sleep(430);
			cout << ".. ";
			Sleep(420);
			cout << "... ";
			Sleep(400);
			ab[1] = ab[2] + exab[1] + exaab;
			ab[4] = ab[5] + exab[0] + exab[2] + exaab;
			cout << "恢復了" << endl;
		}
		else if(aa == 2){
			system("cls");
			return 0;
		}
		else {
			cout << endl;
			cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
			goto GG;
		}
	}
	int aatk = 0;
RF:
	int n = 0;
	cout << "1---攻擊\t2---技能\t3---回復\t4---逃跑" << endl;
	cin >> n;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto RF;
	}
	if (n == 1) {
		cout << ". ";
		Sleep(430);
		cout << ".. ";
		Sleep(420);
		cout << "... ";
		Sleep(400);
		if (job == "法師") {
			if (ab[0] < 20) {
				hp -= 0;
				cout << "造成了" << ab[3] << "傷害" << endl;
			}
			else {
				hp -= ab[3];
				cout << "造成了" << ab[3] << "傷害" << endl;
			}
		}
		else {
			hp -= (ab[3] + aatk + exab[0] + exab[2] + exaab);
			cout << "造成了" << ab[3] + aatk + exab[0] + exab[2] + exaab << "傷害" << endl;
		}
		if(hp <= 0){
			if ((lv / ab[0]) >= 2) {
				ex *= 2;
				cout << "獲得經驗:" << ex << endl;
				ab[6] += ex;
				int money;
				money = rand() % 20 + 10;
				Sundries[12] += money;
				cout << "獲得金錢:" << money << endl;
				return 0;

			}
			else {
				cout << "獲得經驗:" << ex << endl;
				int money;
				money = rand() % 20 + 10;
				Sundries[12] += money;
				cout << "獲得金錢:" << money << endl;
				ab[6] += ex;
			}
		}
		else {	
			cout << "... ";
			Sleep(400);
			ab[1] -= atk;
			if (ab[1] <= 0) {
				ab[1] = 0;
				cout << "你已經死了" << endl;
				return 0;
			}
			cout << monster[x] << "hp剩下" << hp << endl;
			cout << "我方hp:" << ab[1] << endl;
			goto RF;
		}
	}
	else if (n == 2) {
		if (profession == "法師") {
			if (ab[0] < 20) {
			sk: cout << "1---火球lv1:5mp\t2---冰椎lv1:10mp" << endl;
				int a;
				cin >> a;
				while (cin.fail()) {
					cout << "無效指令!" << "\n";
					cin.clear();
					cin.ignore(100, '\n');
					goto sk;
				}
				if (a == 1) {
					if (ab[4] <= 0) {
						cout << "沒魔" << endl;
						goto RF;
					}
					else if (ab[4] < 5) {
						cout << "魔力不夠" << endl;
						goto RF;
					}
					srand((unsigned)time(NULL));//not in while
					cout << ". ";
					Sleep(430);
					cout << ".. ";
					Sleep(420);
					cout << "... ";
					Sleep(400);
					int matk = rand() % 30 + 20;
					hp -= matk;
					ab[4] -= 5;
					if (ab[4] <= 0) {
						ab[4] = 0;
					}
					cout << "造成了" << matk << "傷害" << endl;
					if (hp <= 0) {
						if ((lv / ab[0]) >= 2) {
							ex *= 2;
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
						else {
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
					}
					else {
						cout << "... ";
						Sleep(400);
						ab[1] -= atk;
						if (ab[1] <= 0) {
							ab[1] = 0;
							cout << "你已經死了" << endl;
							return 0;
						}
						cout << monster[x] << "hp剩下" << hp << endl;
						cout << "我方hp:" << ab[1] << endl;
						goto RF;
					}
				}
				else if (a == 2) {
					if (ab[4] <= 0) {
						cout << "沒魔" << endl;
						goto RF;
					}
					else if (ab[4] < 10) {
						cout << "魔力不夠" << endl;
						goto RF;
					}
					srand((unsigned)time(NULL));//not in while
					cout << ". ";
					Sleep(430);
					cout << ".. ";
					Sleep(420);
					cout << "... ";
					Sleep(400);
					int matk = rand() % 60 + 40;
					hp -= matk;
					ab[4] -= 10;
					if (ab[4] <= 0) {
						ab[4] = 0;
					}
					cout << "造成了" << matk << "傷害" << endl;
					if (hp <= 0) {
						if ((lv / ab[0]) >= 2) {
							ex *= 2;
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
							}
						else {
							cout << "獲得經驗:" << ex << endl;	
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
					}
					else {
						cout << "... ";
						Sleep(400);
						ab[1] -= atk;
						if (ab[1] <= 0) {
							ab[1] = 0;
							cout << "你已經死了" << endl;
							return 0;
						}
						cout << monster[x] << "hp剩下" << hp << endl;
						cout << "我方hp:" << ab[1] << endl;
						goto RF;
					}
				}
				else {
					cout << endl;
					cout << " 　　　　　無效指令" << endl;
					goto RF;
				}
			}
			else if (ab[0] >= 20) {
			sk2:cout << "1---火球lv10:20mp\t2---冰椎lv10:30mp\t3---大爆炸:100mp" << endl;
				int a;
				cin >> a;
				while (cin.fail()) {
					cout << "無效指令!" << "\n";
					cin.clear();
					cin.ignore(100, '\n');
					goto sk2;
				}
				if (a == 1) {
					if (ab[4] <= 0) {
						cout << "沒魔" << endl;
						goto RF;
					}
					else if (ab[4] < 20) {
						cout << "魔力不夠" << endl;
						goto RF;
					}
					srand((unsigned)time(NULL));//not in while
					cout << ". ";
					Sleep(430);
					cout << ".. ";
					Sleep(420);
					cout << "... ";
					Sleep(400);
					int matk = rand() % 50 + 40;
					hp -= matk;
					ab[4] -= 20;
					if (ab[4] <= 0) {
						ab[4] = 0;
					}
					cout << "造成了" << matk << "傷害" << endl;
					if (hp <= 0) {
						if ((lv / ab[0]) >= 2) {
							ex *= 2;
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
						else {
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
					}
					else {
						cout << "... ";
						Sleep(400);
						ab[1] -= atk;
						if (ab[1] <= 0) {
							ab[1] = 0;
							cout << "你已經死了" << endl;
							return 0;
						}
						cout << monster[x] << "hp剩下" << hp << endl;
						cout << "我方hp:" << ab[1] << endl;
						goto RF;
					}
				}
				else if (a == 2) {
					if (ab[4] <= 0) {
						cout << "沒魔" << endl;
						goto RF;
					}
					else if (ab[4] < 30) {
						cout << "魔力不夠" << endl;
						goto RF;
					}
					srand((unsigned)time(NULL));//not in while
					cout << ". ";
					Sleep(430);
					cout << ".. ";
					Sleep(420);
					cout << "... ";
					Sleep(400);
					int matk = rand() % 120 + 80;
					hp -= matk;
					ab[4] -= 30;
					if (ab[4] <= 0) {
						ab[4] = 0;
					}
					cout << "造成了" << matk << "傷害" << endl;
					if (hp <= 0) {
						if ((lv / ab[0]) >= 2) {
							ex *= 2;
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
						else {
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
					}
					else {
						cout << "... ";
						Sleep(400);
						ab[1] -= atk;
						if (ab[1] <= 0) {
							ab[1] = 0;
							cout << "你已經死了" << endl;
							return 0;
						}
						cout << monster[x] << "hp剩下" << hp << endl;
						cout << "我方hp:" << ab[1] << endl;
						goto RF;
					}
				}
				else if (a == 3) {
					if (ab[4] <= 0) {
						cout << "沒魔" << endl;
						goto RF;
					}
					else if (ab[4] < 100) {
						cout << "魔力不夠" << endl;
						goto RF;
					}
					srand((unsigned)time(NULL));//not in while
					cout << ". ";
					Sleep(430);
					cout << ".. ";
					Sleep(420);
					cout << "... ";
					Sleep(400);
					int matk = rand() % 250 + 150;
					hp -= matk;
					ab[4] -= 100;
					if (ab[4] <= 0) {
						ab[4] = 0;
					}
					cout << "造成了" << matk << "傷害" << endl;
					if (hp <= 0) {
						if ((lv / ab[0]) >= 2) {
							ex *= 2;
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
						else {
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
					}
					else {
						cout << "... ";
						Sleep(400);
						ab[1] -= atk;
						if (ab[1] <= 0) {
							ab[1] = 0;
							cout << "你已經死了" << endl;
							return 0;
						}
						cout << monster[x] << "hp剩下" << hp << endl;
						cout << "我方hp:" << ab[1] << endl;
						goto RF;
					}
				}
				else {
					cout << endl;
					cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
					goto RF;
				}
			}
		}
		else if (profession == "劍士") {
			if (ab[0] < 20) {
			sk3:cout << "1---鼓舞lv1:0mp" << endl;
				int a;
				cin >> a;
				while (cin.fail()) {
					cout << "無效指令!" << "\n";
					cin.clear();
					cin.ignore(100, '\n');
					goto sk3;
				}
				if (a == 1) {
					srand((unsigned)time(NULL));//not in while
					cout << ". ";
					Sleep(430);
					cout << ".. ";
					Sleep(420);
					cout << "... ";
					Sleep(400);
					aatk = rand() % 30 + 10;
					cout << "提升了" << aatk << "傷害" << endl;
					cout << "... ";
					Sleep(400);
					ab[1] -= atk;
					if (ab[1] <= 0) {
						ab[1] = 0;
						cout << "你已經死了" << endl;
						return 0;
					}
					cout << monster[x] << "hp剩下" << hp << endl;
					cout << "我方hp:" << ab[1] << endl;
					goto RF;
				}
				else {
					cout << endl;
					cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
					goto RF;
				}
			}
			else if (ab[0] >= 20) {
			sk4:cout << "1---鼓舞lv10:0mp\t2---光炮:50mp" << endl;
				int a;
				cin >> a;
				while (cin.fail()) {
					cout << "無效指令!" << "\n";
					cin.clear();
					cin.ignore(100, '\n');
					goto sk4;
				}
				if (a == 1) {
					srand((unsigned)time(NULL));//not in while
					cout << ". ";
					Sleep(430);
					cout << ".. ";
					Sleep(420);
					cout << "... ";
					Sleep(400);
					aatk = rand() % 60 + 20;
					cout << "提升了" << aatk << "傷害" << endl;
					cout << "... ";
					Sleep(400);
					ab[1] -= atk;
					if (ab[1] <= 0) {
						ab[1] = 0;
						cout << "你已經死了" << endl;
						return 0;
					}
					cout << monster[x] << "hp剩下" << hp << endl;
					cout << "我方hp:" << ab[1] << endl;
					goto RF;
				}
				else if (a == 2) {
					if (ab[4] <= 0) {
						cout << "沒魔" << endl;
						goto RF;
					}
					else if (ab[4] < 50) {
						cout << "魔力不夠" << endl;
						goto RF;
					}
					srand((unsigned)time(NULL));//not in while
					cout << ". ";
					Sleep(430);
					cout << ".. ";
					Sleep(420);
					cout << "... ";
					Sleep(400);
					int matk = rand() % 120 + 80;
					hp -= matk;
					ab[4] -= 50;
					if (ab[4] <= 0) {
						ab[4] = 0;
					}
					cout << "造成了" << matk << "傷害" << endl;
					if (hp <= 0) {
						if ((lv / ab[0]) >= 2) {
							ex *= 2;
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
						else {
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
					}
					else {
						cout << "... ";
						Sleep(400);
						ab[1] -= atk;
						if (ab[1] <= 0) {
							ab[1] = 0;
							cout << "你已經死了" << endl;
							return 0;
						}
						cout << monster[x] << "hp剩下" << hp << endl;
						cout << "我方hp:" << ab[1] << endl;
						goto RF;
					}
				}
				else {
					cout << endl;
					cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
					goto RF;
				}
			}
		}
		else if (profession == "弓兵") {
			if (ab[0] < 20) {
			sk5:cout << "1---鼓舞lv1:0mp\t2---狙擊lv1:5mp" << endl;
				int a;
				cin >> a;
				while (cin.fail()) {
					cout << "無效指令!" << "\n";
					cin.clear();
					cin.ignore(100, '\n');
					goto sk5;
				}
				if (a == 1) {
					srand((unsigned)time(NULL));//not in while
					cout << ". ";
					Sleep(430);
					cout << ".. ";
					Sleep(420);
					cout << "... ";
					Sleep(400);
					aatk = rand() % 30 + 5;
					cout << "提升了" << aatk << "傷害" << endl;
					cout << "... ";
					Sleep(400);
					ab[1] -= atk;
					if (ab[1] <= 0) {
						ab[1] = 0;
						cout << "你已經死了" << endl;
						return 0;
					}
					cout << monster[x] << "hp剩下" << hp << endl;
					cout << "我方hp:" << ab[1] << endl;
					goto RF;
				}
				else if (a == 2) {
					if (ab[4] <= 0) {
						cout << "沒魔" << endl;
						goto RF;
					}
					else if (ab[4] < 5) {
						cout << "魔力不夠" << endl;
						goto RF;
					}
					srand((unsigned)time(NULL));//not in while
					cout << ". ";
					Sleep(430);
					cout << ".. ";
					Sleep(420);
					cout << "... ";
					Sleep(400);
					int matk = rand() % 40 + 30;
					hp -= matk;
					ab[4] -= 5;
					if (ab[4] <= 0) {
						ab[4] = 0;
					}
					cout << "造成了" << matk << "傷害" << endl;
					if (hp <= 0) {
						if ((lv / ab[0]) >= 2) {
							ex *= 2;
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
						else {
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
					}
					else {
						cout << "... ";
						Sleep(400);
						ab[1] -= atk;
						if (ab[1] <= 0) {
							ab[1] = 0;
							cout << "你已經死了" << endl;
							return 0;
						}
						cout << monster[x] << "hp剩下" << hp << endl;
						cout << "我方hp:" << ab[1] << endl;
						goto RF;
					}
				}
				else {
					cout << endl;
					cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
					goto RF;
				}
			}
			else if (ab[0] >= 20) {
			sk6:cout << "1---鼓舞lv10:0mp\t2---狙擊lv10:20mp\t3---近身攻擊:75mp" << endl;
				int a;
				cin >> a;
				while (cin.fail()) {
					cout << "無效指令!" << "\n";
					cin.clear();
					cin.ignore(100, '\n');
					goto sk6;
				}
				if (a == 1) {
					srand((unsigned)time(NULL));//not in while
					cout << ". ";
					Sleep(430);
					cout << ".. ";
					Sleep(420);
					cout << "... ";
					Sleep(400);
					aatk = rand() % 50 + 20;
					cout << "提升了" << aatk << "傷害" << endl;
					cout << "... ";
					Sleep(400);
					ab[1] -= atk;
					if (ab[1] <= 0) {
						ab[1] = 0;
						cout << "你已經死了" << endl;
						return 0;
					}
					cout << monster[x] << "hp剩下" << hp << endl;
					cout << "我方hp:" << ab[1] << endl;
					goto RF;
				}
				else if (a == 2) {
					if (ab[4] <= 0) {
						cout << "沒魔" << endl;
						goto RF;
					}
					else if (ab[4] < 20) {
						cout << "魔力不夠" << endl;
						goto RF;
					}
					srand((unsigned)time(NULL));//not in while
					cout << ". ";
					Sleep(430);
					cout << ".. ";
					Sleep(420);
					cout << "... ";
					Sleep(400);
					int matk = rand() % 100 + 70;
					hp -= matk;
					ab[4] -= 20;
					if (ab[4] <= 0) {
						ab[4] = 0;
					}
					cout << "造成了" << matk << "傷害" << endl;
					if (hp <= 0) {
						if ((lv / ab[0]) >= 2) {
							ex *= 2;
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
						else {
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
					}
					else {
						cout << "... ";
						Sleep(400);
						ab[1] -= atk;
						if (ab[1] <= 0) {
							ab[1] = 0;
							cout << "你已經死了" << endl;
							return 0;
						}
						cout << monster[x] << "hp剩下" << hp << endl;
						cout << "我方hp:" << ab[1] << endl;
						goto RF;
					}
				}
				else if (a == 3) {
					if (ab[4] <= 0) {
						cout << "沒魔" << endl;
						goto RF;
					}
					else if (ab[4] < 75) {
						cout << "魔力不夠" << endl;
						goto RF;
					}
					srand((unsigned)time(NULL));//not in while
					cout << ". ";
					Sleep(430);
					cout << ".. ";
					Sleep(420);
					cout << "... ";
					Sleep(400);
					int matk = rand() % 150 + 90;
					hp -= matk;
					ab[4] -= 75;
					if (ab[4] <= 0) {
						ab[4] = 0;
					}
					cout << "造成了" << matk << "傷害" << endl;
					if (hp <= 0) {
						if ((lv / ab[0]) >= 2) {
							ex *= 2;
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
						else {
							cout << "獲得經驗:" << ex << endl;
							ab[6] += ex;
							int money;
							money = rand() % 20 + 10;
							Sundries[12] += money;
							cout << "獲得金錢:" << money << endl;
							return 0;
						}
					}
					else {
						cout << "... ";
						Sleep(400);
						ab[1] -= atk;
						if (ab[1] <= 0) {
							ab[1] = 0;
							cout << "你已經死了" << endl;
							return 0;
						}
						cout << monster[x] << "hp剩下" << hp << endl;
						cout << "我方hp:" << ab[1] << endl;
						goto RF;
					}
				}
				else {
					cout << endl;
					cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
					goto RF;
				}
			}
		}
		goto RF;
	}
	else if (n == 3) {
		if (ab[0] < 20) {
			srand((unsigned)time(NULL));//not in while
			cout << "回復" << endl;
			cout << ". ";
			Sleep(430);
			cout << ".. ";
			Sleep(420);
			cout << "... ";
			Sleep(400);
			int nhp = rand() % 50 + 10;
			int nmp = rand() % 15 + 5;
			ab[1] += nhp;
			ab[4] += nmp;
			cout << "恢復了" << nhp << "點生命" << endl;
			cout << "恢復了" << nmp << "點魔力" << endl;
			if (ab[1] >= ab[2] + exab[1] + exaab) {
				ab[1] = ab[2] + exab[1] + exaab;
			}
			if (ab[4] >= ab[5] + exab[0] + exab[2] + exaab) {
				ab[4] = ab[5];
			}
			cout << "我方hp:" << ab[1] << endl;
			cout << "我方mp:" << ab[4] << endl;
		}
		else if (ab[0] >= 20) {
			srand((unsigned)time(NULL));//not in while
			cout << "回復" << endl;
			cout << ". ";
			Sleep(430);
			cout << ".. ";
			Sleep(420);
			cout << "... ";
			Sleep(400);
			int nhp = rand() % 100 + 50;
			int nmp = rand() % 50 + 25;
			ab[1] += nhp;
			ab[4] += nmp;
			cout << "恢復了" << nhp << "點生命" << endl;
			cout << "恢復了" << nmp << "點魔力" << endl;
			if (ab[1] >= ab[2] + exab[1] + exaab) {
				ab[1] = ab[2] + exab[1] + exaab;
			}
			if (ab[4] >= ab[5] + exab[0] + exab[2] + exaab) {
				ab[4] = ab[5];
			}
			cout << "我方hp:" << ab[1] << endl;
			cout << "我方mp:" << ab[4] << endl;
		}
		goto RF;
	}
	else if (n == 4) {
		system("cls");
		cout << "順利逃跑了" << endl;
		return 0;
	}
	else {
		cout << endl;
		cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
		goto RF;
	}
	return 0;
}

int saveability() {
	int abillty[7] = { 0,0,0,0,0,0,0 };
	string account = " ";
	string profession = " ";
	ifstream fin;
	fin.open("ability.txt");
	while (fin >> account >> profession >> abillty[0] >> abillty[1] >> abillty[2] >> abillty[3] >> abillty[4] >> abillty[5] >> abillty[6]) {
		if (person == account && job == profession) {
			continue;
		}
		else {
			ofstream fout;
			fout.open("ability101.txt", ios::app);
			fout << account << " " << profession << " " << abillty[0] << " " << abillty[1] << " " << abillty[2] << " " << abillty[3] << " " << abillty[4] << " " << abillty[5] << " " << abillty[6] << endl;
			fout.close();
		}
	}
	fin.close();

	ofstream fout;
	fout.open("ability101.txt", ios::app);
	fout << person << " " << job << " " << ab[0] << " " << ab[1] << " " << ab[2] << " " << ab[3] << " " << ab[4] << " " << ab[5] << " " << ab[6] << endl;
	fout.close();
	remove("ability.txt");
	rename("ability101.txt", "ability.txt");
	return 0;
}
/// ////////////////////////////////////////////////
int fishing() {
RF:
	int n = 0;
	cout << "                   　　　　　　　　　　1---開始釣魚" << "    　　　		2---離開" << endl;
	cin >> n;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto RF;
	}
	if (n == 1) {
		srand((unsigned)time(NULL));//not in while
		while (1) {
		fish11:
			int x = rand() % 100 + 1;
			if (x > 0 && x < 61) {
				int y = rand() % 2 + 1;
				if (y == 1) {
					int z = rand() % 100 + 1;
					if (z > 0 && z < 51) {
						cout << "... ";
						Sleep(400);
						cout << "____釣到了 " << idx_Sundries[0] << " +1" << endl;
						Sundries[0]++;
					}
					else if (z > 50 && z < 81) {
						cout << "... ";
						Sleep(400);
						cout << "____釣到了 " << idx_Sundries[1] << " +1" << endl;
						Sundries[1]++;
					}
					else {
						cout << "... ";
						Sleep(400);
						cout << "____釣到了 " << idx_Sundries[2] << " +1" << endl;
						Sundries[2]++;
					}
				}
				else {
					int z = rand() % 100 + 1;
					if (z > 0 && z < 51) {
						cout << "... ";
						Sleep(400);
						cout << "____釣到了 " << idx_Sundries[3] << " +1" << endl;
						Sundries[3]++;
					}
					else if (z > 50 && z < 81) {
						cout << "... ";
						Sleep(400);
						cout << "____釣到了 " << idx_Sundries[4] << " +1" << endl;
						Sundries[4]++;
					}
					else {
						cout << "... ";
						Sleep(400);
						cout << "____釣到了 " << idx_Sundries[5] << " +1" << endl;
						Sundries[5]++;
					}
				}
			}
			else if(x == 69){
				cout << "... ";
				Sleep(400);
				cout << "!!!釣到了傳說的 " << endl;
				cout << "... ";
				Sleep(400);
				cout << wea[11] << " +1";
				weapon[10]++;
			}
			else {
				int y = rand() % 2 + 1;
				if (y == 1) {
					int z = rand() % 100 + 1;
					if (z > 0 && z < 51) {
						cout << "... ";
						Sleep(400);
						cout << "____釣到了 " << idx_Sundries[6] << " +1" << endl;
						Sundries[6]++;
					}
					else if (z > 50 && z < 81) {
						cout << "... ";
						Sleep(400);
						cout << "____釣到了 " << idx_Sundries[7] << " +1" << endl;
						Sundries[7]++;
					}
					else {
						cout << "... ";
						Sleep(400);
						cout << "____釣到了 " << idx_Sundries[8] << " +1" << endl;
						Sundries[8]++;
					}
				}
				else {
					int z = rand() % 100 + 1;
					if (z > 0 && z < 51) {
						cout << "... ";
						Sleep(400);
						cout << "____釣到了 " << idx_Sundries[9] << " +1" << endl;
						Sundries[9]++;
					}
					else if (z > 50 && z < 81) {
						cout << "... ";
						Sleep(400);
						cout << "____釣到了 " << idx_Sundries[10] << " +1" << endl;
						Sundries[10]++;
					}
					else {
						cout << "... ";
						Sleep(400);
						cout << "____釣到了 " << idx_Sundries[11] << " +1" << endl;
						Sundries[11]++;
					}
				}
			}
			cout << endl;
			fish00:
			int m = 0;
			cout << "                   　　　　　　　　　　1---繼續釣魚" << "    　　　		2---離開" << endl;
			cin >> m;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto fish00;
			}
			if (m == 1) {
				system("cls");
				goto fish11;
			}
			else if (m == 2) {
				system("cls");
				return 0;
			}
			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
				goto fish00;
			}
		}
	}
	else if (n == 2) {
		return 0;
	}
	else {
		cout << endl;
		cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
		goto RF;
	}

	return 0;
}
/// ////////////////////////////////////////////////
int mapmove() {
	int path = 0;
	int num = 0;
	num = position;
mo:cout << endl << "                                                      　　 移動方向:  " << endl << endl;
	cout << "                                 8---上" << "    　　		2---下" << "    　　		4---左" << "    　　		6---右" << endl;
	cin >> path;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto mo;
	}
	if (path == 8) {
		if (num == 0) {
			num = 2;
			system("cls");
		}
		else if (num == 4) {
			num = 0;
			system("cls");
		}
		else {
			system("cls");
			cout << "                                                        在最北邊了!!!" << endl;
		}
	}
	else if (path == 2) {
		if (num == 0) {
			num = 4;
			system("cls");
		}
		else if (num == 2) {
			num = 0;
			system("cls");
		}
		else {
			system("cls");
			cout << "                                                        在最南邊了!!!" << endl;
		}
	}
	else if(path == 4) {
		if (num == 0) {
			num = 3;
			system("cls");
		}
		else if (num == 1) {
			num = 0;
			system("cls");
		}
		else {
			system("cls");
			cout << "                                                        在最左邊了!!!" << endl;
		}
	}
	else if (path == 6) {
		if (num == 0) {
			num = 1;
			system("cls");
		}
		else if (num == 3) {
			num = 0;
			system("cls");
		}
		else {
			system("cls");
			cout << "                                                        在最右邊了!!!" << endl;
		}
	}
	else {
		cout << "                                                   　　    無效指令" << endl;
	}
	position = num;
	return 0;
}
/// ////////////////////////////////////////////////
int teleport() {
	int num = 0;
	string mod = " ";
	string place = " ";
mo:num = position;
	cin >> mod >> place;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto mo;
	}
	if (mod == "move") {
		if (place == "城市") {
			num = 0;
		}
		else if (place == "家") {
			num = 1;
		}
		else if (place == "商店") {
			num = 2;
		}
		else if (place == "海邊") {
			num = 3;
		}
		else if (place == "森林") {
			num = 4;
		}
		else {
			system("cls");
			cout << "                                                   　　    無效地點" << endl;
		}
	}
	else {
		cout << "                                                   　　    無效指令" << endl;
	}
	position = num;
	system("cls");
	return 0;
}
/// ////////////////////////////////////////////////
int mapRW() {
	int locate = 0;
	string account = " ";
	string profession = " ";
	ifstream fin;
	fin.open("locate.txt");
	while (fin >> account >> profession >> locate) {
		if (person == account && job == profession) {
			position = locate;
			return 0;
		}
	}
	fin.close();
	ofstream fout;
	fout.open("locate.txt", ios::app);
	fout << person << " " << job << " " << "0" << endl;
	fout.close();
}
/// ////////////////////////////////////////////////
int maplocate() {
	system("cls");
	cout << endl << "                                                        目前位置:  ";
	switch (position) {
	case 0:
		cout << idx_position[position] << endl;
		break;
	case 1:
		cout << idx_position[position] << endl;
		break;
	case 2:
		cout << idx_position[position] << endl;
		break;
	case 3:
		cout << idx_position[position] << endl;
		break;
	case 4://4
		cout << idx_position[position] << endl;
		break;
	}
	cout << endl;
	return 0;
}
/// ////////////////////////////////////////////////
int  mapopen() {
RP:
	cout << "                                                        ══════════" << endl;
	cout << "                                                        | 世界地圖 |" << endl;
	cout << "                                                        ══════════" << endl;
	cout << "                                                            商店" << endl;
	cout << "                                                              |" << endl;
	cout << "                                                              |" << endl;
	cout << "                                                              |" << endl;
	cout << "                                                              |" << endl;
	cout << "                                             海邊------------城市------------家" << endl;
	cout << "                                                              |" << endl;
	cout << "                                                              |" << endl;
	cout << "                                                              |" << endl;
	cout << "                                                              |" << endl;
	cout << "                                                             森林" << endl << endl;
	int n = 0;
	cout << "                   　　　1---所在位置" << "    　　　		2---角色移動" << "    　　　		3---傳送" << endl << endl;
	cin >> n;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto RP;
	}
	switch (n) {
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 3;
	default:
		cout << endl;
		cout << "                   　　　　　　　　　　　　　　	無效指令" << endl;
		goto RP;
	}
	return 0;
}
/// ////////////////////////////////////////////////
int bagopen() {
BP:
	int n = 0;
	cout << "                   　　　1---雜物背包" << "    　　　		2---裝備背包"<< endl << endl;
	cin >> n;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto BP;
	}
	switch (n) {
	case 1:
		return 1;
	case 2:
		return 2;
	default:
		cout << endl;
		cout << "                   　　　　　　　　　　　　　　	無效指令" << endl;
		goto BP;
	}
	return 0;
}
/// ////////////////////////////////////////////////
int bagRW() {
	int items[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
	string account = " ";
	string profession = " ";
	ifstream fin;
	fin.open("Sundriesbag.txt");
	while (fin >> account >> profession >> items[0] >> items[1] >> items[2] >> items[3] >> items[4] >> items[5] >> items[6] >> items[7] >> items[8] >> items[9] >> items[10] >> items[11] >> items[12]) {
		if (person == account && job == profession) {
			for (int i = 0; i < 13; i++) {
				Sundries[i] = items[i];
			}
			return 0;
		}
	}
	//cout << endl;
	fin.close();
	ofstream fout;
	fout.open("Sundriesbag.txt", ios::app);
	fout << person << " " << job << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << endl;
	fout.close();

	return 0;
}

int wbagRW() {
	int items[21] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	string account = " ";
	string profession = " ";
	ifstream fin;
	fin.open("Sundrieswbag.txt");
	while (fin >> account >> profession >> items[0] >> items[1] >> items[2] >> items[3] >> items[4] >> items[5] >> items[6] >> items[7] >> items[8] >> items[9] >> items[10] >> items[11] >> items[12] >> items[13] >> items[14] >> items[15] >> items[16] >> items[17] >> items[18] >> items[19] >> items[20]) {
		if (person == account && job == profession) {
			for (int i = 0; i < 21; i++) {
				weapon[i] = items[i];
			}
			return 0;
		}
	}
	//cout << endl;
	fin.close();
	ofstream fout;
	fout.open("Sundrieswbag.txt", ios::app);
	fout << person << " " << job << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << " " << "0" << endl;
	fout.close();

	return 0;
}
/// ////////////////////////////////////////////////
int Sundries_bag() {
bag:	
	cout << "                   　　　　　－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－" << endl;
	cout << "                   　　　　　|　　　１：低階HP藥水:X " << Sundries[0] <<"　　４：低階MP藥水: X " << Sundries[3] <<"　　７：中階魔石: X " << Sundries[6] <<"　　１０：中階星塵: X " << Sundries[9] << "\t|" << endl << endl;
	cout << "                   　　　　　|　　　２：中階HP藥水:X " << Sundries[1] <<"　　５：中階MP藥水: X " << Sundries[4] <<"　　８：高階魔石: X " << Sundries[7] <<"　　１１：高階星塵: X " << Sundries[10] << "\t|" << endl << endl;
	cout << "                   　　　　　|　　　３：高階HP藥水:X " << Sundries[2] <<"　　６：高階MP藥水: X " << Sundries[5] <<"　　９：    龍牙: X " << Sundries[8] <<"　　１２：  輔助器: X " << Sundries[11] << "\t|" << endl << endl;
	cout << "                   　　　　　－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－" << endl;																																																			  
	cout << "                                                         money = " << Sundries[12] << endl;
	cout << "1---使用道具\t2---離開" << endl;
	int n;
	cin >> n;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto bag;
	}
	if (n == 1) {
		cout << "請選擇道具" << endl;
		int m;
		cin >> m;
		while (cin.fail()) {
			cout << "無效指令!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');
			goto bag;
		}
		if (m == 1) {
			system("cls");
			if (Sundries[0] <= 0) {
				cout << "道具不足" << endl;
				goto bag;
			}
			else {
				if(ab[1] == ab[2] + exab[1] + exaab){
					cout << "目前hp全滿" << endl;
					goto bag;
				}
				else {
					Sundries[0]--;
					int aa = ab[1];
					ab[1] += 20;
					if (ab[1] >= ab[2] + exab[1] + exaab) {
						ab[1] = ab[2] + exab[1] + exaab;
						cout << "hp回復了" <<  ab[1] - aa << "點" << endl;
					}
					else {
						cout << "hp回復了20點" << endl;
					}
				}
			}
		}
		else if (m == 2) {
			system("cls");
			if (Sundries[1] <= 0) {
				cout << "道具不足" << endl;
				goto bag;
			}
			else {
				if (ab[1] == ab[2] + exab[1] + exaab) {
					cout << "目前hp全滿" << endl;
					goto bag;
				}
				else {
					Sundries[1]--;
					int aa = ab[1];
					ab[1] += 40;
					if (ab[1] >= ab[2] + exab[1] + exaab) {
						ab[1] = ab[2] + exab[1] + exaab;
						cout << "hp回復了" << ab[1] - aa << "點" << endl;
					}
					else {
						cout << "hp回復了40點" << endl;
					}
				}
			}
		}
		else if (m == 3) {
			system("cls");
			if (Sundries[2] <= 0) {
				cout << "道具不足" << endl;
				goto bag;
			}
			else {
				if (ab[1] == ab[2] + exab[1] + exaab) {
					cout << "目前hp全滿" << endl;
					goto bag;
				}
				else {
					Sundries[2]--;
					int aa = ab[1];
					ab[1] += 60;
					if (ab[1] >= ab[2] + exab[1] + exaab) {
						ab[1] = ab[2] + exab[1] + exaab;
						cout << "hp回復了" << ab[1] - aa << "點" << endl;
					}
					else {
						cout << "hp回復了60點" << endl;
					}
				}
			}
		}
		else if (m == 4) {
			system("cls");
			if (Sundries[3] <= 0) {
				cout << "道具不足" << endl;
				goto bag;
			}
			else {
				if (ab[4] == ab[5] + exab[0] + exab[2] + exaab) {
					cout << "目前mp全滿" << endl;
					goto bag;
				}
				else {
					Sundries[3]--;
					int aa = ab[4];
					ab[4] += 20;
					if (ab[4] >= ab[5] + exab[0] + exab[2] + exaab) {
						ab[4] = ab[5] + exab[0] + exab[2] + exaab;
						cout << "mp回復了" << ab[4] - aa << "點" << endl;
					}
					else {
						cout << "mp回復了20點" << endl;
					}
				}
			}
		}
		else if (m == 5) {
			system("cls");
			if (Sundries[4] <= 0) {
				cout << "道具不足" << endl;
				goto bag;
			}
			else {
				if (ab[4] == ab[5] + exab[0] + exab[2] + exaab) {
					cout << "目前mp全滿" << endl;
					goto bag;
				}
				else {
					Sundries[4]--;
					int aa = ab[4];
					ab[4] += 40;
					if (ab[4] >= ab[5] + exab[0] + exab[2] + exaab) {
						ab[4] = ab[5] + exab[0] + exab[2] + exaab;
						cout << "mp回復了" << ab[4] - aa << "點" << endl;
					}
					else {
						cout << "mp回復了40點" << endl;
					}
				}
			}
		}
		else if (m == 6) {
			system("cls");
			if (Sundries[5] <= 0) {
				cout << "道具不足" << endl;
				goto bag;
			}
			else {
				if (ab[4] == ab[5] + exab[0] + exab[2] + exaab) {
					cout << "目前mp全滿" << endl;
					goto bag;
				}
				else {
					Sundries[5]--;
					int aa = ab[4];
					ab[4] += 60;
					if (ab[4] >= ab[5] + exab[0] + exab[2] + exaab) {
						ab[4] = ab[5] + exab[0] + exab[2] + exaab;
						cout << "mp回復了" << ab[4] - aa << "點" << endl;
					}
					else {
						cout << "mp回復了60點" << endl;
					}
				}
			}
		}
		else if (m >= 7 || m <= 12) {
			system("cls");
			cout << idx_Sundries[m-1] << "為強化素材" << endl;
		}
		else {
			cout << endl;
			system("cls");
			cout << "                   　　　　　　　　　　　　　　	無效指令" << endl;
			goto bag;
		}
	}
	else if (n == 2) {
		system("cls");
		return 0;
	}
	else {
		cout << endl;
		system("cls");
		cout << "                   　　　　　　　　　　　　　　	無效指令" << endl;
	}
	goto bag;
}

int RWweapon() {
	int we[3] = { 0,0,0 };
	string account = " ";
	string profession = " ";
	ifstream fin;
	fin.open("RWweabag.txt");
	while (fin >> account >> profession >> we[0] >> we[1] >> we[2]) {
		if (person == account && job == profession) {
			for (int i = 0; i < 3; i++) {
				abw[i] = we[i];
			}
			return 0;
		}
	}
	//cout << endl;
	fin.close();
	ofstream fout;
	fout.open("RWweabag.txt", ios::app);
	fout << person << " " << job << " " << "0" << " " << "0" << " " << "0" << endl;
	fout.close();

	return 0;
}

int saveweapon() {
	int we[3] = { 0,0,0 };
	string account = " ";
	string profession = " ";
	ifstream fin;
	fin.open("RWweabag.txt");
	while (fin >> account >> profession >> we[0] >> we[1] >> we[2]) {
		if (person == account && job == profession) {
			continue;
		}
		else {
			ofstream fout;
			fout.open("RWweabag101.txt", ios::app);
			fout << account << " " << profession << " " << we[0] << " " << we[1] << " " << we[2] << endl;
			fout.close();
		}
	}
	fin.close();

	ofstream fout;
	fout.open("RWweabag101.txt", ios::app);
	fout << person << " " << job << " " << abw[0] << " " << abw[1] << " " << abw[2]  << endl;
	fout.close();
	remove("RWweabag.txt");
	rename("RWweabag101.txt", "RWweabag.txt");
	return 0;
}
//lv hp maxhp atk mp maxmp ex
int raiseability(int m) {
	if ((m >= 1 && m <= 4) || (m >= 8 && m <= 11) || (m >= 15 && m <= 18)) {
		if (abw[0] >= 1 && abw[0] <= 4) {
			exab[0] = wea_ab[abw[0]];
		}
		else if (m >= 8 && m <= 11) {
			exab[0] = wea_ab[abw[0]];
		}
		else if (m >= 15 && m <= 18) {
			exab[0] = wea_ab[abw[0]];
		}
	}
	else if (m == 5 || m == 6 || m == 12 || m == 13 || m == 19 || m == 20) {
		if (abw[1] == 5 || abw[1] == 6) {
			exab[1] = wea_ab[abw[1]];
		}
		else if (abw[1] == 12 || abw[1] == 13) {
			exab[1] = wea_ab[abw[1]];
		}
		else if (abw[1] == 19 || abw[1] == 20) {
			exab[1] = wea_ab[abw[1]];
		}
	}
	else if (m == 7 || m == 14 || m == 21) {
		if (abw[2] == 7) {
			exab[2] = wea_ab[abw[2]];
		}
		else if (abw[2] == 14) {
			exab[2] = wea_ab[abw[2]];
		}
		else if (abw[2] == 21) {
			exab[2] = wea_ab[abw[2]];
		}
	}
	else {
		if (abw[0] == 0) {
			exab[0] = wea_ab[abw[0]];
		}
		if (abw[1] == 0) {
			exab[1] = wea_ab[abw[1]];
		}
		if (abw[2] == 0) {
			exab[2] = wea_ab[abw[2]];
		}
	}
	if (abw[1] == 6 && abw[2] == 7) {
		exaab = 10;
	}
	else if (abw[1] != 6 || abw[2] != 7) {
		exaab = 0;
	}
	else if (abw[1] == 13 && abw[2] == 14) {
		exaab = 10;
	}
	else if (abw[1] != 13 || abw[2] != 14) {
		exaab = 0;
	}
	else if (abw[1] == 20 && abw[2] == 21) {
		exaab = 10;
	}
	else if (abw[1] != 20 && abw[2] != 21) {
		exaab = 0;
	}
	else {
		exaab = 0;
	}
	return(0);
}

int weapon_bag() {
wbag:
	cout << "                   　　　　　－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－" << endl;
	cout << "                   　　　　　|　　　１：初級法杖:X " << weapon[0] << "\t" << "  ８：  初級劍: X " << weapon[7] << "\t" << "１５：    初級弓: X " << weapon[14] << "\t|" << endl << endl;
	cout << "                   　　　　　|　　　２：中級法杖:X " << weapon[1] << "\t" << "  ９：  中級劍: X " << weapon[8] << "\t" << "１６：    中級弓: X " << weapon[15] << "\t|" << endl << endl;
	cout << "                   　　　　　|　　　３：高級法杖:X " << weapon[2] << "\t" << "１０：  高級劍: X " << weapon[9] << "\t" << "１７：    高級弓: X " << weapon[16] << "\t|" << endl << endl;
	cout << "                   　　　　　|　　　４：贗造魔女:X " << weapon[3] << "\t" << "１１：    聖劍: X " << weapon[10] << "\t" << "１８：        槍: X " << weapon[17] << "\t|" << endl << endl;
	cout << "                   　　　　　|　　　５：低級法袍:X " << weapon[4] << "\t" << "１２：低級鎧甲: X " << weapon[11] << "\t" << "１９：低級瞄準器: X " << weapon[18] << "\t|" << endl << endl;
	cout << "                   　　　　　|　　　６：高級法袍:X " << weapon[5] << "\t" << "１３：高級鎧甲: X " << weapon[12] << "\t" << "２０：高級瞄準器: X " << weapon[19] << "\t|" << endl << endl;
	cout << "                   　　　　　|　　　７：    魔戒:X " << weapon[6] << "\t" << "１４：    劍鞘: X " << weapon[13] << "\t" << "２１：      指虎: X " << weapon[20] << "\t|" << endl << endl;
	cout << "                   　　　　　－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－" << endl;
	cout << "1---裝備/更換裝備\t2---脫下裝備\t3---離開" << endl;
	int n;
	cin >> n;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto wbag;
	}
	if (n == 1) {
		cout << "請選擇裝備" << endl;
		int m;
		cin >> m;
		while (cin.fail()) {
			cout << "無效指令!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');
			goto wbag;
		}
		if (m >= 1 || m <= 21) {
			if (weapon[m - 1] > 0) {
				if ((m >= 1 && m <= 4) || (m >= 8 && m <= 11) || (m >= 15 && m <= 18)) {
					if (job == "法師") {
						if (abw[0] != 0) {
							if (m >= 1 && m <= 4) {
								weapon[abw[0]-1] ++;
								weapon[m - 1] --;
								abw[0] = 0;
								raiseability(abw[0]);
								system("cls");
								abw[0] = m;
								cout << "帶上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
						else {
							if (m >= 1 && m <= 4) {
								weapon[m - 1] --;
								abw[0] = m;
								system("cls");
								cout << "帶上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
					}
					else if (job == "劍士") {
						if (abw[0] != 0) {
							if (m >= 8 && m <= 11) {
								weapon[abw[0] - 1] ++;
								weapon[m - 1] --;
								abw[0] = 0;
								raiseability(abw[0]);
								abw[0] = m;
								system("cls");
								cout << "帶上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
						else {
							if (m >= 8 && m <= 11) {
								weapon[m - 1] --;
								abw[0] = m;
								system("cls");
								cout << "帶上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
					}
					else if (job == "弓兵") {
						if (abw[0] != 0) {
							if (m >= 15 && m <= 18) {
								weapon[abw[0] - 1] ++;
								weapon[m - 1] --;
								abw[0] = 0;
								raiseability(abw[0]);
								abw[0] = m;
								system("cls");
								cout << "帶上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
						else {
							if (m >= 15 && m <= 18) {
								weapon[m - 1] --;
								abw[0] = m;
								system("cls");
								cout << "帶上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
					}
				}
				else if (m == 5 || m == 6 || m == 12 || m == 13 || m == 19 || m == 20) {
					if (job == "法師") {
						if (abw[1] != 0) {
							if (m == 5 || m == 6) {
								weapon[abw[1] - 1] ++;
								weapon[m - 1] --;
								abw[1] = 0;
								raiseability(abw[1]);
								abw[1] = m;
								system("cls");
								cout << "穿上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
						else {
							if (m == 5 || m == 6) {
								weapon[m - 1] --;
								abw[1] = m;
								system("cls");
								cout << "穿上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
					}
					else if (job == "劍士") {
						if (abw[1] != 0) {
							if (m == 12 || m == 13) {
								weapon[abw[1] - 1] ++;
								weapon[m - 1] --;
								abw[1] = 0;
								raiseability(abw[1]);
								abw[1] = m;
								system("cls");
								cout << "穿上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
						else {
							if (m == 12 || m == 13) {
								weapon[m - 1] --;
								abw[1] = m;
								system("cls");
								cout << "穿上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
					}
					else if (job == "弓兵") {
						if (abw[1] != 0) {
							if (m == 19 || m == 20) {
								weapon[abw[1] - 1] ++;
								weapon[m - 1] --;
								abw[1] = 0;
								raiseability(abw[1]);
								abw[1] = m;
								system("cls");
								cout << "穿上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
						else {
							if (m == 19 || m == 20) {
								weapon[m - 1] --;
								abw[1] = m;
								system("cls");
								cout << "穿上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
					}
				}
				else if (m == 7 || m == 14 || m == 21) {
					if (job == "法師") {
						if (abw[2] != 0) {
							if (m == 7) {
								weapon[abw[2] - 1] ++;
								weapon[m - 1] --;
								abw[2] = 0;
								raiseability(abw[2]);
								abw[2] = m;
								system("cls");
								cout << "配戴上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
						else {
							if (m == 7) {
								weapon[m - 1] --;
								abw[2] = m;
								system("cls");
								cout << "配戴上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
					}
					else if (job == "劍士") {
						if (abw[2] != 0) {
							if (m == 14) {
								weapon[abw[2] - 1] ++;
								weapon[m - 1] --;
								abw[2] = 0;
								raiseability(abw[2]);
								abw[2] = m;
								system("cls");
								cout << "配戴上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
						else {
							if (m == 14) {
								weapon[m - 1] --;
								abw[2] = m;
								system("cls");
								cout << "配戴上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
					}
					else if (job == "弓兵") {
						if (abw[2] != 0) {
							if (m == 21) {
								weapon[abw[2] - 1] ++;
								weapon[m - 1] --;
								int b = abw[0];
								abw[2] = 0;
								raiseability(abw[2]);
								abw[2] = m;
								system("cls");
								cout << "配戴上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
						else {
							if (m == 21) {
								weapon[m - 1] --;
								abw[2] = m;
								system("cls");
								cout << "配戴上了" << wea[m] << endl;
							}
							else {
								system("cls");
								cout << "此為別職業裝備" << endl;
							}
						}
					}
				}
			}
			else {
				cout << endl;
				system("cls");
				cout << "沒有" << wea[m] << endl;
				goto wbag;
			}
		}
		else {
			cout << endl;
			system("cls");
			cout << "                   　　　　　　　　　　　　　　	無效指令" << endl;
			goto wbag;
		}
		raiseability(m);
	}
	else if (n == 2) {
		if (abw[0] == 0 && abw[1] == 0 && abw[2] == 0) {
			cout << endl;
			system("cls");
			cout << "目前沒有穿裝備" << endl;
			goto wbag;
		}
		else {
			cout << "1---武器\t2---服飾\t3---飾品" << endl;
			int a;
			cin >> a;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto wbag;
			}
			if (a == 1) {
				if (abw[0] == 0) {
					system("cls");
					cout << "目前沒裝備武器" << endl;
					goto wbag;
				}
				else {
					int b;
					b = abw[0];
					abw[0] = 0;
					weapon[b - 1] ++;
					raiseability(abw[0]);
				}
			}
			else if (a == 2) {
				if (abw[1] == 0) {
					system("cls");
					cout << "目前沒裝備服飾" << endl;
					goto wbag;
				}
				else {
					int b;
					b = abw[1];
					abw[1] = 0;
					weapon[b - 1] ++;
					raiseability(abw[1]);
					if (ab[1] >= ab[2]) {
						ab[1] = ab[2];
					}
				}
			}
			else if (a == 3) {
				if (abw[2] == 0) {
					system("cls");
					cout << "目前沒裝備飾品" << endl;
					goto wbag;
				}
				else {
					int b;
					b = abw[2];
					abw[2] = 0;
					weapon[b - 1] ++;
					raiseability(abw[2]);
					if (ab[4] >= ab[5]) {
						ab[4] = ab[5];
					}
				}
			}
			else {
				cout << endl;
				system("cls");
				cout << "                   　　　　　　　　　　　　　　	無效指令" << endl;
				goto wbag;
			}
		}
	}
	else if (n == 3) {
		system("cls");
		return 0;
	}
	else {
		cout << endl;
		system("cls");
		cout << "                   　　　　　　　　　　　　　　	無效指令" << endl;
	}
	goto wbag;
}
/// ////////////////////////////////////////////////
int out() {
	system("cls");
	cout << endl;
	cout << "                   　　　　　　　　　　　　　　		感謝您的遊玩" << endl;
	return 0;
}
/// ////////////////////////////////////////////////
int savemap() {
	ifstream fin;
	int locate = 0;
	string account = " ";
	string profession = " ";
	fin.open("locate.txt");
	while (fin >> account >> profession >> locate) {
		if (person == account && job == profession) {
			continue;
		}
		else {
			ofstream fout;
			fout.open("locate101.txt", ios::app);
			fout << account << " " << profession << " " << locate << endl;
			fout.close();
		}
	}
	fin.close();
	ofstream fout;
	fout.open("locate101.txt", ios::app);
	fout << person << " " << job << " " << position << endl;
	fout.close();
	remove("locate.txt");
	rename("locate101.txt", "locate.txt");
	return 0;
}
/// ////////////////////////////////////////////////
int savebag() {
	ifstream fin;
	int items[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0};
	string account = " ";
	string profession = " ";
	fin.open("Sundriesbag.txt");
	while (fin >> account >> profession >> items[0] >> items[1] >> items[2] >> items[3] >> items[4] >> items[5] >> items[6] >> items[7] >> items[8] >> items[9] >> items[10] >> items[11] >> items[12]) {
		if (person == account && job == profession) {
			continue;
		}
		else {
			ofstream fout;
			fout.open("Sundriesbag101.txt", ios::app);
			fout << account << " " << profession <<" "<< items[0] << " " << items[1] << " " << items[2] << " " << items[3] << " " << items[4] << " " << items[5] << " " << items[6] << " " << items[7] << " " << items[8] << " " << items[9] << " " << items[10] << " " << items[11] << " " << items[12] <<endl;
		    fout.close();
		}
	}
	fin.close();

	ofstream fout;
	fout.open("Sundriesbag101.txt", ios::app);
	fout << person << " " << job << " " << Sundries[0] << " " << Sundries[1] << " " << Sundries[2] << " " << Sundries[3] << " " << Sundries[4] << " " << Sundries[5] << " " << Sundries[6] << " " << Sundries[7] << " " << Sundries[8] << " " << Sundries[9] << " " << Sundries[10] << " " << Sundries[11] << " " << Sundries[12]  <<endl;
	fout.close();
	remove("Sundriesbag.txt");
	rename("Sundriesbag101.txt", "Sundriesbag.txt");
	return 0;
}

int savewbag() {
	ifstream fin;
	int items[21] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	string account = " ";
	string profession = " ";
	fin.open("Sundrieswbag.txt");
	while (fin >> account >> profession >> items[0] >> items[1] >> items[2] >> items[3] >> items[4] >> items[5] >> items[6] >> items[7] >> items[8] >> items[9] >> items[10] >> items[11] >> items[12] >> items[13] >> items[14] >> items[15] >> items[16] >> items[17] >> items[18] >> items[19] >> items[20]) {
		if (person == account && job == profession) {
			continue;
		}
		else {
			ofstream fout;
			fout.open("Sundrieswbag101.txt", ios::app);
			fout << account << " " << profession << " " << items[0] << " " << items[1] << " " << items[2] << " " << items[3] << " " << items[4] << " " << items[5] << " " << items[6] << " " << items[7] << " " << items[8] << " " << items[9] << " " << items[10] << " " << items[11] << " " << items[12] << " " << items[13] << " " << items[14] << " " << items[15] << " " << items[16] << " " << items[17] << " " << items[18] << " " << items[19] << " " << items[20] << endl;
			fout.close();
		}
	}
		
	fin.close();

	ofstream fout;
	fout.open("Sundrieswbag101.txt", ios::app);
	fout << person << " " << job << " " << weapon[0] << " " << weapon[1] << " " << weapon[2] << " " << weapon[3] << " " << weapon[4] << " " << weapon[5] << " " << weapon[6] << " " << weapon[7] << " " << weapon[8] << " " << weapon[9] << " " << weapon[10] << " " << weapon[11] << " " << weapon[12] << " " << weapon[13] << " " << weapon[14] << " " << weapon[15] << " " << weapon[16] << " " << weapon[17] << " " << weapon[18] << " " << weapon[19] << " " << weapon[20] << endl;
	fout.close();
	remove("Sundrieswbag.txt");
	rename("Sundrieswbag101.txt", "Sundrieswbag.txt");
	return 0;
}

int getmoney() {
RF:
	int n = 0;
	cout << "                   　　　　　　　　　　1---賺錢" << "    　　　		2---離開" << endl;
	cin >> n;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto RF;
	}
	if (n == 1) {
		srand((unsigned)time(NULL));//not in while
		while (1) {
		fish11:
			int x = rand() % 100 + 1;
			if (x >= 1 && x <= 20) {
				Sundries[12]++;
				cout << "賺了1塊錢" << endl;
				cout << endl;
			}
			else if (x >= 21 && x <= 40) {
				int y = rand() % 10 + 1;
				Sundries[12] += y;
				cout << "賺了" << y << "塊錢" << endl;
				cout << endl;
			}
			else if ((x >= 41 && x <= 48) || (x >= 50 && x <= 60)) {
				int y = rand() % 10 + 11;
				Sundries[12] += y;
				cout << "賺了" << y << "塊錢" << endl;
				cout << endl;
			}
			else if (x >= 61 && x <= 80) {
				int y = rand() % 10 + 21;
				Sundries[12] += y;
				cout << "賺了" << y << "塊錢" << endl;
				cout << endl;
			}
			else if (x == 49) {
				Sundries[12] += 100;
				cout << "賺了100塊錢" << endl;
				weapon[3]++;
				cout << "運氣好，獲得了" << wea[4] << endl;
				cout << endl;
			}
			else {
				int y = rand() % 10 + 31;
				Sundries[12] += y;
				cout << "賺了" << y << "塊錢" << endl;
				cout << endl;
			}
		fish00:
			int m = 0;
			cout << "                   　　　　　　　　　　1---繼續賺錢" << "    　　　		2---離開" << endl;
			cin >> m;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto fish00;
			}
			if (m == 1) {
				system("cls");
				goto fish11;
			}
			else if (m == 2) {
				system("cls");
				return 0;
			}
			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
				goto fish00;
			}
		}
	}
	else if (n == 2) {
		system("cls");
		return 0;
	}
	else {
		cout << endl;
		cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
		goto RF;
	}

	return 0;
}
/// ////////////////////////////////////////////////
int ashop() {
	int items[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	string account = " ";
	string profession = " ";
	ifstream fin;
	fin.open("shop.txt");
	while (fin >> account >> profession >> items[0] >> items[1] >> items[2] >> items[3] >> items[4] >> items[5] >> items[6] >> items[7] >> items[8] >> items[9] >> items[10] >> items[11]) {
		if (person == account && job == profession) {
			for (int i = 0; i < 12; i++) {
				shop[i] = items[i];
			}
			cout << endl;
			return 0;
		}
	}
	//cout << endl;
	fin.close();
	ofstream fout;
	fout.open("shop.txt", ios::app);//初始值
	fout << person << " " << job << " " << "99" << " " << "99" << " " << "99" << " " << "99" << " " << "99" << " " << "99" << " " << "99" << " " << "99" << " " << "99" << " " << "99" << " " << "99" << " " << "99" << endl;
	fout.close();

	int wea[9] = { 0,0,0,0,0,0,0,0,0 };
	ifstream fjn;
	fjn.open("wshop.txt");
	while (fjn >> account >> profession >> wea[0] >> wea[1] >> wea[2] >> wea[3] >> wea[4] >> wea[5] >> wea[6] >> wea[7] >> wea[8]) {
		if (person == account && job == profession) {
			for (int i = 0; i < 9; i++) {
				wshop[i] = wea[i];
			}
			cout << endl;
			return 0;
		}
	}
	//cout << endl;
	fjn.close();
	ofstream fuut;
	fuut.open("wshop.txt", ios::app);//初始值
	fuut << person << " " << job << " " << "99" << " " << "99" << " " << "99" << " " << "99" << " " << "99" << " " << "99" << " " << "99" << " " << "99" << " " << "99" << endl;
	fuut.close();
	return 0;
}

int buy() {
RF:
	int n = 0;
	cout << "                   　　　　　　　　　　1---購買物品" << "    　　　		2---離開" << endl;
	cin >> n;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto RF;
	}
	if (n == 1) {
		while (1) {
		fish11:
			cout << "                   　　　　　－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－" << endl;
			cout << "                   　　　　　|　　　１：低階HP藥水: 10 $ X " << shop[0] << "　　４：低階MP藥水: 10 $ X " << shop[3] << "　　７：  中階魔石: 15 $ X " << shop[6] << "　　１０：中階星塵: 15 $ X " << shop[9] << "\t|" << endl << endl;
			cout << "                   　　　　　|　　　２：中階HP藥水: 20 $ X " << shop[1] << "　　５：中階MP藥水: 20 $ X " << shop[4] << "　　８：  高階魔石: 55 $ X " << shop[7] << "　　１１：高階星塵: 55 $ X " << shop[10] << "\t|" << endl << endl;
			cout << "                   　　　　　|　　　３：高階HP藥水: 40 $ X " << shop[2] << "　　６：高階MP藥水: 40 $ X " << shop[5] << "　　９：      龍牙: 55 $ X " << shop[8] << "　　１２：  輔助器: 55 $ X " << shop[11] << "\t|" << endl << endl;
			cout << "                   　　　　　－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－" << endl;
			cout << "                   　　　　　|　　１３：  初級法杖: 10 $ X " << wshop[0] << " １６：    初級劍: 10 $ X " << wshop[3] << " １９：    初級弓: 10 $ X " << wshop[6] << "\t\t\t\t\t|" << endl << endl;
			cout << "                   　　　　　|　　１４：  低級法袍: 10 $ X " << wshop[1] << " １７：  低級鎧甲: 10 $ X " << wshop[4] << " ２０：低級瞄準器: 10 $ X " << wshop[7] << "\t\t\t\t\t|" << endl << endl;
			cout << "                   　　　　　|　　１５：      魔戒: 60 $ X " << wshop[2] << " １８：      劍鞘: 60 $ X " << wshop[5] << " ２１：      指虎: 60 $ X " << wshop[8] << "\t\t\t\t\t|" << endl << endl;
			cout << "                   　　　　　－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－" << endl;
			cout << "\t\t\t\t\t\t\t\tmoney = " << Sundries[12] << endl;
			int k;
			cin >> k;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto fish11;
			}
			if (k <= 0 || k > 21) {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
				goto fish11;
			}
			if (k < 13) {
				if (shop[k - 1] == 0) {
					cout << "商品售完" << endl;
					break;
				}
				if (Sundries[12] < 10) {
					cout << "金錢不足" << endl;
					break;
				}
				cout << idx_Sundries[k-1] << " +1";
				shop[k-1]--;
				Sundries[k - 1]++;
				Sundries[12] -= 10;
			}
			else {
				if (wshop[k - 13] == 0) {
					cout << "商品售完" << endl;
					break;
				}
				if (Sundries[12] < 10) {
					cout << "金錢不足" << endl;
					break;
				}
				if (k - 13 == 0) {
					wshop[k - 13]--;
					cout << wea[1] << " +1";
					weapon[0]++;
					Sundries[12] -= 10;
				}
				else if (k - 13 == 1) {
					wshop[k - 13]--;
					cout << wea[5] << " +1";
					weapon[4]++;
					Sundries[12] -= 10;
				}
				else if (k - 13 == 2) {
					wshop[k - 13]--;
					cout << wea[7] << " +1";
					weapon[6]++;
					Sundries[12] -= 60;
				}
				else if (k - 13 == 3) {
					wshop[k - 13]--;
					cout << wea[8] << " +1";
					weapon[7]++;
					Sundries[12] -= 10;
				}
				else if (k - 13 == 4) {
					wshop[k - 13]--;
					cout << wea[12] << " +1";
					weapon[11]++;
					Sundries[12] -= 10;
				}
				else if (k - 13 == 5) {
					wshop[k - 13]--;
					cout << wea[14] << " +1";
					weapon[13]++;
					Sundries[12] -= 60;
				}
				else if (k - 13 == 6) {
					wshop[k - 13]--;
					cout << wea[15] << " +1";
					weapon[14]++;
					Sundries[12] -= 10;
				}
				else if (k - 13 == 7) {
					wshop[k - 13]--;
					cout << wea[19] << " +1";
					weapon[18]++;
					Sundries[12] -= 10;
				}
				else if (k - 13 == 8) {
					wshop[k - 13]--;
					cout << wea[21] << " +1";
					weapon[20]++;
					Sundries[12] -= 60;
				}
			}
			break;
			}
		fish00:
			int m = 0;
			cout << "                   　　　　　　　　　　1---繼續購買" << "    　　　		2---離開" << endl;
			cin >> m;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto fish00;
			}
			if (m == 1) {
				system("cls");
				goto fish11;
			}
			else if (m == 2) {
				system("cls");
				return 0;
			}
			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
				goto fish00;
			}
	}
	else if (n == 2) {
		return 0;
	}
	else {
		cout << endl;
		cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
		goto RF;
	}

	return 0;
}

int saveshop() {
	ifstream fin;
	int items[12] = { 0,0,0,0,0,0,0,0,0,0,0,0};
	string account = " ";
	string profession = " ";
	fin.open("shop.txt");
	while (fin >> account >> profession >> items[0] >> items[1] >> items[2] >> items[3] >> items[4] >> items[5] >> items[6] >> items[7] >> items[8] >> items[9] >> items[10] >> items[11]) {
		if (person == account && job == profession) {
			continue;
		}
		else {
			ofstream fout;
			fout.open("shop101.txt", ios::app);
			fout << account << " " << profession << " " << items[0] << " " << items[1] << " " << items[2] << " " << items[3] << " " << items[4] << " " << items[5] << " " << items[6] << " " << items[7] << " " << items[8] << " " << items[9] << " " << items[10] << " " << items[11] << endl;
			fout.close();
		}
	}
	fin.close();

	ofstream fout;
	fout.open("shop101.txt", ios::app);
	fout << person << " " << job << " " << shop[0] << " " << shop[1] << " " << shop[2] << " " << shop[3] << " " << shop[4] << " " << shop[5] << " " << shop[6] << " " << shop[7] << " " << shop[8] << " " << shop[9] << " " << shop[10] << " " << shop[11] << endl;
	fout.close();
	remove("shop.txt");
	rename("shop101.txt", "shop.txt");
	return 0;
}

int savewshop(){
	ifstream fin;
	int wea[9] = { 0,0,0,0,0,0,0,0,0 };
	string account = " ";
	string profession = " ";
	fin.open("wshop.txt");
	while (fin >> account >> profession >> wea[0] >> wea[1] >> wea[2] >> wea[3] >> wea[4] >> wea[5] >> wea[6] >> wea[7] >> wea[8]) {
		if (person == account && job == profession) {
			continue;
		}
		else {
			ofstream fout;
			fout.open("wshop101.txt", ios::app);
			fout << account << " " << profession << " " << wea[0] << " " << wea[1] << " " << wea[2] << " " << wea[3] << " " << wea[4] << " " << wea[5] << " " << wea[6] << " " << wea[7] << " " << wea[8] << endl;
			fout.close();
		}
	}
	fin.close();

	ofstream fout;
	fout.open("wshop101.txt", ios::app);
	fout << person << " " << job << " " << wshop[0] << " " << wshop[1] << " " << wshop[2] << " " << wshop[3] << " " << wshop[4] << " " << wshop[5] << " " << wshop[6] << " " << wshop[7] << " " << wshop[8] << endl;
	fout.close();
	remove("wshop.txt");
	rename("wshop101.txt", "wshop.txt");
	return 0;
}
int info() {
	cout << "玩家:" << person << "\t" << "職業:" << job << endl;
	cout << "武器:" << wea[abw[0]] << "\t" << "" << wea[abw[1]] << "\t" << " " << wea[abw[2]] << endl;
	if (job == "法師") {
		if (ab[0] < 20) {
			cout << "技能:\t1.火球lv1\t2.冰椎lv1" << endl;
		}
		else {
			cout << "技能:\t1.火球lv10\t2.冰椎lv10\t3.大爆炸" << endl;
		}
		cout << "Lv:" << ab[0] << "\t";
		cout << "Hp:" << ab[1] << "/" << ab[2] + exab[1] + exaab << endl;
		cout << "Atk:" << ab[3] << "\t" << "Mp:" << ab[4] << "/" << ab[5] + exab[0] + exaab + exab[2] << endl;
	}
	else if (job == "劍士") {
		if (ab[0] < 20) {
			cout << "技能:\t1.鼓舞lv1" << endl;
		}
		else {
			cout << "技能:\t1.鼓舞lv10\t2.光炮" << endl;
		}
		cout << "Lv:" << ab[0] << "\t";
		cout << "Hp:" << ab[1] << "/" << ab[2] + exab[1] + exaab << endl;
		cout << "Atk:" << ab[3] + exab[0] + exaab + exab[2] << "\t" << "Mp:" << ab[4] << "/" << ab[5] << endl;
	}
	else if (job == "弓兵") {
		if (ab[0] < 20) {
			cout << "技能:\t1.鼓舞lv1\t2.狙擊lv1" << endl;
		}
		else {
			cout << "技能:\t1.鼓舞lv10\t2.狙擊lv10\t3.近身攻擊" << endl;
		}
		cout << "Lv:" << ab[0] << "\t";
		cout << "Hp:" << ab[1] << "/" << ab[2] + exab[1] + exaab << endl;
		cout << "Atk:" << ab[3] + exab[0] + exaab + exab[2] << "\t" << "Mp:" << ab[4] << "/" << ab[5] + exab[0] + exaab + exab[2] << endl;
	}
	cout << "Exp:" << ab[6] << endl;
	return 0;
}

int raiseweapon() {
rw:
	cout << "                   　　　　　　　　　　1---強化裝備" << "    　　　		2---離開" << endl;
	int n;
	cin >> n;
	while (cin.fail()) {
		cout << "無效指令!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');
		goto rw;
	}
	if (n == 1) {
	rr:cout << "選擇要強化的裝備" << endl;
		cout << "1---中級法杖\t4---中級劍\t7---中級弓" << endl;
		cout << "2---高級法杖\t5---高級劍\t8---高級弓" << endl;
		cout << "3---高級法袍\t6---高級鎧甲\t9---高級瞄準器" << endl;
		int m;
		cin >> m;
		while (cin.fail()) {
			cout << "無效指令!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');
			goto rr;
		}
		if (m == 1) {
			cout << "所需素材:" << wea[1] << "、" << idx_Sundries[6] << "、金錢:20" << endl;
		ww:cout << "是否強化?\t1---是\t2---否" << endl;
			int o;
			cin >> o ;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto ww;
			}
			if (o == 1) {
				if (weapon[0] == 0 || Sundries[6] == 0 || Sundries[12] < 20) {
					system("cls");
					cout << "素材不足" << endl;
					goto rw;
				}
				else {
					system("cls");
					weapon[0]--;
					Sundries[6]--;
					Sundries[12] -= 20;
					cout << "強化成功" << endl;
					weapon[1]++;
				}
			}
			else if(o == 2){
				system("cls");
				goto rw;
			}
			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
				goto rw;
			}
		}
		else if (m == 2) {
			cout << "所需素材:" << wea[2] << "、" << idx_Sundries[7] << "、金錢:60" << endl;
		ww1:cout << "是否強化?\t1---是\t2---否" << endl;
			int o;
			cin >> o;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto ww1;
			}
			if (o == 1) {
				if (weapon[1] == 0 || Sundries[7] == 0 || Sundries[12] < 60) {
					system("cls");
					cout << "素材不足" << endl;
					goto rw;
				}
				else {
					system("cls");
					weapon[1]--;
					Sundries[7]--;
					Sundries[12] -= 60;
					cout << "強化成功" << endl;
					weapon[2]++;
				}
			}
			else if (o == 2) {
				system("cls");
				goto rw;
			}
			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
				goto rw;
			}
		}
		else if (m == 3) {
			cout << "所需素材:" << wea[5] << "、" << idx_Sundries[8] << "、金錢:60" << endl;
		ww2:cout << "是否強化?\t1---是\t2---否" << endl;
			int o;
			cin >> o;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto ww2;
			}
			if (o == 1) {
				if (weapon[4] == 0 || Sundries[8] == 0 || Sundries[12] < 60) {
					system("cls");
					cout << "素材不足" << endl;
					goto rw;
				}
				else {
					system("cls");
					weapon[4]--;
					Sundries[8]--;
					Sundries[12] -= 60;
					cout << "強化成功" << endl;
					weapon[5]++;
				}
			}
			else if (o == 2) {
				system("cls");
				goto rw;
			}
			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
				goto rw;
			}
		}
		else if (m == 4) {
			cout << "所需素材:" << wea[8] << "、" << idx_Sundries[6] << "、金錢:20" << endl;
		ww3:cout << "是否強化?\t1---是\t2---否" << endl;
			int o;
			cin >> o;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto ww3;
			}
			if (o == 1) {
				if (weapon[7] == 0 || Sundries[6] == 0 || Sundries[12] < 20) {
					system("cls");
					cout << "素材不足" << endl;
					goto rw;
				}
				else {
					system("cls");
					weapon[7]--;
					Sundries[6]--;
					Sundries[12] -= 20;
					cout << "強化成功" << endl;
					weapon[8]++;
				}
			}
			else if (o == 2) {
				system("cls");
				goto rw;
			}
			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
				goto rw;
			}
		}
		else if (m == 5) {
			cout << "所需素材:" << wea[9] << "、" << idx_Sundries[7] << "、金錢:60" << endl;
		ww4:cout << "是否強化?\t1---是\t2---否" << endl;
			int o;
			cin >> o;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto ww4;
			}
			if (o == 1) {
				if (weapon[8] == 0 || Sundries[7] == 0 || Sundries[12] < 60) {
					system("cls");
					cout << "素材不足" << endl;
					goto rw;
				}
				else {
					system("cls");
					weapon[8]--;
					Sundries[7]--;
					Sundries[12] -= 60;
					cout << "強化成功" << endl;
					weapon[9]++;
				}
			}
			else if (o == 2) {
				system("cls");
				goto rw;
			}
			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
				goto rw;
			}
		}
		else if (m == 6) {
			cout << "所需素材:" << wea[12] << "、" << idx_Sundries[8] << "、金錢:60" << endl;
		ww5:cout << "是否強化?\t1---是\t2---否" << endl;
			int o;
			cin >> o;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto ww5;
			}
			if (o == 1) {
				if (weapon[11] == 0 || Sundries[8] == 0 || Sundries[12] < 60) {
					system("cls");
					cout << "素材不足" << endl;
					goto rw;
				}
				else {
					system("cls");
					weapon[11]--;
					Sundries[6]--;
					Sundries[12] -= 60;
					cout << "強化成功" << endl;
					weapon[12]++;
				}
			}
			else if (o == 2) {
				system("cls");
				goto rw;
			}
			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
				goto rw;
			}
		}
		else if (m == 7) {
			cout << "所需素材:" << wea[15] << "、" << idx_Sundries[9] << "、金錢:20" << endl;
		ww6:cout << "是否強化?\t1---是\t2---否" << endl;
			int o;
			cin >> o;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto ww6;
			}
			if (o == 1) {
				if (weapon[14] == 0 || Sundries[9] == 0 || Sundries[12] < 20) {
					system("cls");
					cout << "素材不足" << endl;
					goto rw;
				}
				else {
					system("cls");
					weapon[14]--;
					Sundries[9]--;
					Sundries[12] -= 20;
					cout << "強化成功" << endl;
					weapon[15]++;
				}
			}
			else if (o == 2) {
				system("cls");
				goto rw;
			}
			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
				goto rw;
			}
		}
		else if (m == 8) {
			cout << "所需素材:" << wea[16] << "、" << idx_Sundries[10] << "、金錢:60" << endl;
		ww7:cout << "是否強化?\t1---是\t2---否" << endl;
			int o;
			cin >> o;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto ww7;
			}
			if (o == 1) {
				if (weapon[15] == 0 || Sundries[10] == 0 || Sundries[12] < 60) {
					system("cls");
					cout << "素材不足" << endl;
					goto rw;
				}
				else {
					system("cls");
					weapon[15]--;
					Sundries[10]--;
					Sundries[12] -= 60;
					cout << "強化成功" << endl;
					weapon[16]++;
				}
			}
			else if (o == 2) {
				system("cls");
				goto rw;
			}
			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
				goto rw;
			}
		}
		else if (m == 9) {
			cout << "所需素材:" << wea[19] << "、" << idx_Sundries[11] << "、金錢:60" << endl;
		ww8:cout << "是否強化?\t1---是\t2---否" << endl;
			int o;
			cin >> o;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto ww8;
			}
			if (o == 1) {
				if (weapon[18] == 0 || Sundries[11] == 0 || Sundries[12] < 60) {
					system("cls");
					cout << "素材不足" << endl;
					goto rw;
				}
				else {
					system("cls");
					weapon[18]--;
					Sundries[11]--;
					Sundries[12] -= 60;
					cout << "強化成功" << endl;
					weapon[19]++;
				}
			}
			else if (o == 2) {
				system("cls");
				goto rw;
			}
			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
				goto rw;
			}
		}
		else {
			cout << endl;
			cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
			goto rw;
		}
	}
	else if (n == 2) {
		system("cls");
		return 0;
	}
	else {
		cout << endl;
		cout << "                   　　　　　　　　　　　　　　		無效指令" << endl;
		goto rw;
	}
	return 0;
}

int deletshop() {
	ifstream fin;
	int items[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	string account = " ";
	string profession = " ";
	fin.open("shop.txt");
	while (fin >> account >> profession >> items[0] >> items[1] >> items[2] >> items[3] >> items[4] >> items[5] >> items[6] >> items[7] >> items[8] >> items[9] >> items[10] >> items[11]) {
		if (person == account && die == profession) {
			continue;
		}
		else {
			ofstream fout;
			fout.open("shop101.txt", ios::app);
			fout << account << " " << profession << " " << items[0] << " " << items[1] << " " << items[2] << " " << items[3] << " " << items[4] << " " << items[5] << " " << items[6] << " " << items[7] << " " << items[8] << " " << items[9] << " " << items[10] << " " << items[11] << endl;
			fout.close();
		}
	}
	fin.close();
	remove("shop.txt");
	rename("shop101.txt", "shop.txt");
	return 0;
}

int deletwshop() {
	ifstream fin;
	int wea[9] = { 0,0,0,0,0,0,0,0,0 };
	string account = " ";
	string profession = " ";
	fin.open("wshop.txt");
	while (fin >> account >> profession >> wea[0] >> wea[1] >> wea[2] >> wea[3] >> wea[4] >> wea[5] >> wea[6] >> wea[7] >> wea[8]) {
		if (person == account && die == profession) {
			continue;
		}
		else {
			ofstream fout;
			fout.open("wshop101.txt", ios::app);
			fout << account << " " << profession << " " << wea[0] << " " << wea[1] << " " << wea[2] << " " << wea[3] << " " << wea[4] << " " << wea[5] << " " << wea[6] << " " << wea[7] << " " << wea[8] << endl;
			fout.close();
		}
	}
	fin.close();
	remove("wshop.txt");
	rename("wshop101.txt", "wshop.txt");
	return 0;
}

int deletmap() {
	ifstream fin;
	int locate = 0;
	string account = " ";
	string profession = " ";
	fin.open("locate.txt");
	while (fin >> account >> profession >> locate) {
		if (person == account && die == profession) {
			continue;
		}
		else
		{
			ofstream fout;
			fout.open("locate101.txt", ios::app);
			fout << account << " " << profession << " " << locate << endl;
			fout.close();
		}
	}
	fin.close();
	remove("locate.txt");
	rename("locate101.txt", "locate.txt");
	return 0;
}

int deletwbag() {
	ifstream fin;
	int items[21] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	string account = " ";
	string profession = " ";
	fin.open("Sundrieswbag.txt");
	while (fin >> account >> profession >> items[0] >> items[1] >> items[2] >> items[3] >> items[4] >> items[5] >> items[6] >> items[7] >> items[8] >> items[9] >> items[10] >> items[11] >> items[12] >> items[13] >> items[14] >> items[15] >> items[16] >> items[17] >> items[18] >> items[19] >> items[20]) {
		if (person == account && die == profession) {
			continue;
		}
		else {
			ofstream fout;
			fout.open("Sundrieswbag101.txt", ios::app);
			fout << account << " " << profession << " " << items[0] << " " << items[1] << " " << items[2] << " " << items[3] << " " << items[4] << " " << items[5] << " " << items[6] << " " << items[7] << " " << items[8] << " " << items[9] << " " << items[10] << " " << items[11] << " " << items[12] << " " << items[13] << " " << items[14] << " " << items[15] << " " << items[16] << " " << items[17] << " " << items[18] << " " << items[19] << " " << items[20] << endl;
			fout.close();
		}
	}

	fin.close();
	remove("Sundrieswbag.txt");
	rename("Sundrieswbag101.txt", "Sundrieswbag.txt");
	return 0;
}

int deletbag() {
	ifstream fin;
	int items[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	string account = " ";
	string profession = " ";
	fin.open("Sundriesbag.txt");
	while (fin >> account >> profession >> items[0] >> items[1] >> items[2] >> items[3] >> items[4] >> items[5] >> items[6] >> items[7] >> items[8] >> items[9] >> items[10] >> items[11] >> items[12]) {
		if (person == account && die == profession) {
			continue;
		}
		else {
			ofstream fout;
			fout.open("Sundriesbag101.txt", ios::app);
			fout << account << " " << profession << " " << items[0] << " " << items[1] << " " << items[2] << " " << items[3] << " " << items[4] << " " << items[5] << " " << items[6] << " " << items[7] << " " << items[8] << " " << items[9] << " " << items[10] << " " << items[11] << " " << items[12] << endl;
			fout.close();
		}
	}
	fin.close();
	remove("Sundriesbag.txt");
	rename("Sundriesbag101.txt", "Sundriesbag.txt");
	return 0;
}

int deletweapon() {
	int we[3] = { 0,0,0 };
	string account = " ";
	string profession = " ";
	ifstream fin;
	fin.open("RWweabag.txt");
	while (fin >> account >> profession >> we[0] >> we[1] >> we[2]) {
		if (person == account && die == profession) {
			continue;
		}
		else {
			ofstream fout;
			fout.open("RWweabag101.txt", ios::app);
			fout << account << " " << profession << " " << we[0] << " " << we[1] << " " << we[2] << endl;
			fout.close();
		}
	}
	fin.close();
	remove("RWweabag.txt");
	rename("RWweabag101.txt", "RWweabag.txt");
	return 0;
}

int deletability() {
	int abillty[7] = { 0,0,0,0,0,0,0 };
	string account = " ";
	string profession = " ";
	ifstream fin;
	fin.open("ability.txt");
	while (fin >> account >> profession >> abillty[0] >> abillty[1] >> abillty[2] >> abillty[3] >> abillty[4] >> abillty[5] >> abillty[6]) {
		if (person == account && die == profession) {
			continue;
		}
		else {
			ofstream fout;
			fout.open("ability101.txt", ios::app);
			fout << account << " " << profession << " " << abillty[0] << " " << abillty[1] << " " << abillty[2] << " " << abillty[3] << " " << abillty[4] << " " << abillty[5] << " " << abillty[6] << endl;
			fout.close();
		}
	}
	fin.close();
	remove("ability.txt");
	rename("ability101.txt", "ability.txt");
	return 0;
}

int main()
{
	system("color 0a");//綠色
	tree();
	int sign = in();
	if (sign == 1) {//登入了
	kk:
		int soul=text();
		if (soul == 1) {
			ability();
			mapRW();
			bagRW();
			ashop();
			RWweapon();
			wbagRW();
			system("cls");
		}
		else if (soul == 2) {//刪除job
		begin1:
			cout << "                                    　　　              請選擇要刪除的職業" << endl << endl;
			cout << "					　1----法師:    " << "2----劍士:    " << "3----弓兵:    " << endl;
			int n = 0;
			cin >> n;
			while (cin.fail()) {
				cout << "無效指令!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');
				goto begin1;
			}
			if (n == 1 || n == 2 || n == 3) {
				die = idx_job[n - 1];
			}
			else {
				cout << endl;
				cout << "                   　　　　　　　　　　　　　　		無效字元" << endl;
				goto begin1;
			}
			deletshop();
			deletwshop();
			deletmap();
			deletwbag();
			deletbag();
			deletweapon();
			deletability();
			system("cls");
			cout << "已刪除" << endl;
		goto kk;
		}

	}
	else if (sign == 0) {//登出了
		return 0;
	}

	while (1)//控制介面
	{
		GG:
		string window;
		raiseability(abw[0]);
		raiseability(abw[1]);
		raiseability(abw[2]);
		if (position == 0) {
			cout << "城市:這裡是唯一賺錢的地方。" << endl;
		}
		else if (position == 1) {
			cout << "家:這裡可以強化裝備。" << endl;
		}
		else if (position == 2) {
			cout << "商店:這裡可以購買物品。" << endl;
		}
		else if (position == 3) {
			cout << "海邊:試試手氣釣個魚吧!" << endl;
		}
		else if (position == 4) {
			cout << "森林:來進行戰鬥吧!" << endl;
		}
		cout << endl << "                                                         玩家:" << person << "\t職業:" << job << endl << endl;
		cout << "                     save----存檔:    " << "map----地圖:    " << "bag----背包:    " << "ability---狀態:    " << "action----操作:    " << "quit----存檔並退出遊戲:    " << endl;
		cin >> window;
		while (cin.fail()) {
			cout << "無效指令!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');
			goto GG;
		}
		if (window == "save")//save ALL
		{
			saveshop();
			savewshop();
			savemap();
			savewbag();
			savebag();
			saveweapon();
			saveability();
			system("cls");
			cout << "已存檔" << endl << endl;
		}

		else if (window == "map")//map
		{
			system("cls");
			int m = mapopen();
			if (m == 1) {
				maplocate();
			}
			else if (m == 2) {
				mapmove();
				cout << "移動到了" << idx_position[position] << endl;
			}
			else if (m == 3) {
				cout << "move ..." << endl;
				teleport();
				cout << "傳送到了" << idx_position[position] << endl; 
			}
		}
		
		else if (window == "bag")//bag
		{
			system("cls");
			int b=	bagopen();
			if (b == 1) {
				Sundries_bag();
			}
			else if (b == 2) {
				weapon_bag();
			}
		}
		else if (window == "ability")//map
		{
			system("cls");
			info();
		}

		else if (window == "action")//map
		{
			system("cls");
			int p= position;
			if (p == 0) {//position 0
				getmoney();
			}
			else if (p == 1) {//position 1
				raiseweapon();
			}
			else if (p == 2) {//position 2
				buy();
			}
			else if (p == 3) {//position 3
				fishing();
			}
			else if (p == 4) {//position 4
				monster();
				if (ab[6] < 1000) {
					ab[0] = 1;
				}
				else if (ab[6] >= 1000 && ab[6] < 3300) {
					ab[0] = 20;
					if (job == "法師") {
						ab[2] = 140;
						ab[3] = 30;
						ab[5] = 100;
					}
					else if(job == "劍士") {
						ab[2] = 140;
						ab[3] = 100;
						ab[5] = 50;
					}
					else if (job == "弓兵") {
						ab[2] = 140;
						ab[3] = 50;
						ab[5] = 75;
					}
				}
				else if (ab[6] >= 3300 && ab[6] < 10000) {
					ab[0] = 50;
					if (job == "法師") {
						ab[2] = 200;
						ab[3] = 60;
						ab[5] = 200;
					}
					else if (job == "劍士") {
						ab[2] = 200;
						ab[3] = 170;
						ab[5] = 100;
					}
					else if (job == "弓兵") {
						ab[2] = 200;
						ab[3] = 85;
						ab[5] = 150;
					}
				}
				else  {
					ab[0] = 99;
					if (job == "法師") {
						ab[2] = 300;
						ab[3] = 100;
						ab[5] = 300;
					}
					else if (job == "劍士") {
						ab[2] = 300;
						ab[3] = 250;
						ab[5] = 150;
					}
					else if (job == "弓兵") {
						ab[2] = 300;
						ab[3] = 150;
						ab[5] = 225;
					}
				}
				if (ab[6] < 1000) {
					cout << "Lv1，多打怪升級吧" << endl;
				}
				else if (ab[6] >= 1000 && ab[6] < 3300) {
					cout << "恭喜升至Lv20，有新技能可使用" << endl;
				}
				else if (ab[6] >= 3300 && ab[6] < 10000) {
					cout << "恭喜升至Lv50，整體能力值提升了" << endl;
				}
				else {
					cout << "恭喜升至Lv99，已封頂" << endl;
				}
				saveshop();
				savewshop();
				savemap();
				savewbag();
				savebag();
				saveweapon();
				saveability();
			}
		}

		else if (window == "quit")//map
		{
			saveshop();
			savewshop();
			savemap();
			savewbag();
			savebag();
			saveweapon();
			saveability();
			out();
			break;
		}
		else if (window == "archer") {
			weapon[17]++;
			cout << "獲得了" << wea[18] << endl;
		}
		else {
			cout << endl;
			cout << "                   　　　　　　　　　　　　　　	無效指令" << endl;
			goto GG;
		}
	}

	return 0;
}

