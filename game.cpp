#include<iostream>
#include<Windows.h>
#include<cstdlib>
#include<conio.h>
#include<ctime>
using namespace std;
bool eatflag = false;
int fprex, fprey;
bool fprint = false;
int lastkey=4;
int snakex, snakey;
void gotoxy(int x,int y)
{
	COORD p;
	p.X = x;
	p.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
class node
{
public:
	string data;
	int datax, datay;
	node* next;
	node()
	{
		data = "o";
		datax = 52;
		datay = 5;
		next = NULL;
	}
	node(string d)
	{
		data = d;
		datax = 52;
		datay = 5;
		next = NULL;
	}
	node(int datx, int daty)
	{
		data = "o";
		datax = datx;
		datay = daty;
		next = NULL;
	}
};
class scoreboard
{
public:
	int counter;
	scoreboard()
	{
		counter = 0;
	}
	void displayscore()
	{
		cout << "\033[1;34m";
		cout << "Score : " << counter << endl;
		cout << "\033[0m";
	}
};

class snake:public scoreboard
{
public:
	node* head;
	snake()
	{
		head = new node("O");
	}
	bool opposite_key_press;
	void input()
	{
		 opposite_key_press = false;
		int preheadvaluex = head->datax;
		int preheadvaluey = head->datay;
		if (_kbhit())
		{
			char c = _getch();
			if (lastkey==1 && c=='s')
			{
				c = 'k';
				opposite_key_press = true;
			}
			else if (lastkey == 2 && c == 'w')
			{
				c = 'k';
				opposite_key_press = true;
			}
			else if (lastkey == 3 && c == 'd')
			{
				c = 'k';
				opposite_key_press = true;
			}
			else if (lastkey==4 && c=='a')
			{
				c = 'k';
				opposite_key_press = true;
			}

			switch (c)
			{
			case 'w':
			{
				head->datay--;
				lastkey = 1;
				break;
			}
			case 's':
			{
				head->datay++;
				lastkey = 2;
				break;
			}
			case 'a':
			{
				head->datax--;
				//head->datax = head->datax - 2;
				lastkey = 3;
				break;
			}
			case 'd':
			{
				head->datax++;
				//head->datax = head->datax + 2;
				lastkey = 4;
				break;
			}

			}

		}
		else
		{
			if (lastkey == 1)
			{
				head->datay--;
			}
			else if (lastkey == 2)
			{
				head->datay++;
			}
			else if (lastkey == 3)
			{
				//head->datax = head->datax - 2;
				head->datax--;
			}
			else
			{
				//head->datax = head->datax + 2;
				head->datax++;
			}
		}
		if (opposite_key_press == false)
		{
			snakex = head->datax;
			snakey = head->datay;
			node* temp = head->next;
			int tt1x;int tt1y;
			while (temp != NULL)
			{
				tt1x = temp->datax;
				tt1y = temp->datay;
				temp->datax = preheadvaluex;
				temp->datay = preheadvaluey;
				preheadvaluex = tt1x;
				preheadvaluey = tt1y;
				temp = temp->next;
			}
		}
		
	}

	bool snake_bite_check()
	{
		/*if (opposite_key_press == true)
		{
			return false;
		}*/
		node* temp = head->next;
		while (temp != NULL)
		{
			if (head->datax == temp->datax && head->datay == temp->datay)
			{
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	bool snake_collide_wall()
	{
		if (head->datax == 80 || head->datay == 22 || head->datax == 0 || head->datay == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void move(scoreboard &r)
	{
		input();
			if (snake_collide_wall()==true || snake_bite_check()==true)
			{
				//if (!opposite_key_press)
				//{
					gotoxy(35, 10);
					cout << "\033[1;31m";
					cout << "Game Over !!!" << endl;
					cout << "\033[0m";
					gotoxy(35,11);
					r.displayscore();
					gotoxy(35, 23);
					cout << "          ";
					gotoxy(0, 24);
					exit(0);
				//}
			}
			else
			{
				bool snake_head_color = false;
					node* temp = head;
					while (temp != NULL)
					{
						gotoxy(temp->datax, temp->datay);
						if (!snake_head_color)
						{
							cout << "\033[1;31m";
							cout << temp->data;
							cout << "\033[0m";
							snake_head_color = true;
						}
						else
						{
							cout << temp->data;
						}
						temp = temp->next;
					}
			}
	}
		
	bool eat(int &ffx,int &ffy)
	{
		if (head->datax == ffx && head->datay == ffy)
		{
			eatflag = true;
			return true;
		}
		else
		{
			eatflag = false;
			return false;
		}	
	}

	void grow()
	{
		node* temp = head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		node* newnode = new node(temp->datax,temp->datay);
		temp->next = newnode;
	}
};

void draw(snake& s)
{
	for (int x = 0;x <= 80;x++)
	{
		for (int y = 0;y <= 22;y++)
		{
			if (x == 0  || x == 80)
			{
				gotoxy(x, y);
				//cout << "\033[1;34m";
				cout << "*";
				//cout << "\033[0m";
			}
			else if (y == 0 || y == 22)
			{
				gotoxy(x, y);
				cout << "*";
			}
			else
			{
				if (!fprint)
				{
					gotoxy(x, y);
					cout << " ";
				}
			}
		}
	}
	node* temp = s.head;
	while (temp != NULL)
	{
		gotoxy(temp->datax, temp->datay);
		cout <<" ";
		temp = temp->next;
	}
	gotoxy(fprex, fprey);
	cout << " ";
}

class food :public scoreboard
{
public:
	string f;
	int fx, fy;
	food()
	{
		f = "@";
		fx = 66;
		fy = 5;
		fprex = 66;
		fprey = 5;
	}
	void foodmove(snake &s,scoreboard &t)
	{
		fprint = false;
		if (s.eat(fx,fy))
		{
			t.counter++;
			s.grow();
			gotoxy(fx, fy);
			cout << " ";
			fprint = true;
			do
			{
				fx = 1 + rand() % 79;
				fy = 1 + rand() % 21;
			} while (s.eat(fx,fy));
		}
		else
		{
			fprex = fx;
			fprey = fy;
			gotoxy(fx,fy);
			cout << "\033[1;32m";
			cout << f;
			cout << "\033[0m";
			fprint = true;
		}
	}
};

int main()
{
	food f;
	snake s;
	scoreboard b;
	
	cout << "\033[1;34m";
	string str = "WELCOME TO SNAKE GAME";

	cout << "             -------------------------------" << endl;
	cout << "             |                             |" << endl;
	cout << "             |                             |" << endl;
	cout << "             |                             |";
	int x = (60 - str.length()) / 2;
	int y = 5;
	gotoxy(x, y);
	cout << str << endl;
	cout << "             |                             | " << endl;
	cout << "             |                             |" << endl;
	cout << "             -------------------------------" << endl;
	cout << "\033[0m";
	Sleep(2000);
	system("cls");
	while (1)
	{
		draw(s);
		s.move(b);
		f.foodmove(s,b);
		gotoxy(35, 23);
		b.displayscore();
		Sleep(150);
		gotoxy(0,0);
	}
	
	return 0;	
}