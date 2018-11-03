#include<stdio.h>
#include<graphics.h>
#include<time.h>
#include<string.h>
#include <fstream>
#define MIN_X 10
#define MIN_Y 10
#define MAX_X 500
#define MAX_Y 300
#define level 100

enum TrangThai{
	DOWN, UP, LEFT, RIGHT, ENTER
};

struct ToaDo{
	int x, y;
};

struct Snake{
	ToaDo dot[31];
	int n;
	TrangThai tt;
};

struct HoaQua{
	ToaDo td;
};

void KhoiTao(Snake &snake, HoaQua &hq);
void Menu();
void VeGiaoDien(Snake snake);
void VeRan(Snake snake);
void VeHoaQua(HoaQua hq);
void HienThi(Snake snake, HoaQua hq);
void DieuKhien(Snake &snake);
int GetHightScore();
void ChechHighScore();
void ShowHighScore();
void XuLy(Snake &snake, HoaQua &hq);
void run();
void drawcircle(int x0, int y0, int radius,  int color);

void drawcircle(int x0, int y0, int radius, int color)
{
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        putpixel(x0 + x, y0 + y, color);
        putpixel(x0 + y, y0 + x, color);
        putpixel(x0 - y, y0 + x, color);
        putpixel(x0 - x, y0 + y, color);
        putpixel(x0 - x, y0 - y, color);
        putpixel(x0 - y, y0 - x, color);
        putpixel(x0 + y, y0 - x, color);
        putpixel(x0 + x, y0 - y, color);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void KhoiTao(Snake &snake, HoaQua &hq){
	snake.n = 3;
	snake.dot[0].x = 20;
	snake.dot[0].y = 20;
	snake.dot[1].x = 10;
	snake.dot[1].y = 20;
	snake.dot[2].x = 10;
	snake.dot[2].y = 20;
	snake.tt = RIGHT;
	
	hq.td.x = 40;
	hq.td.y = 40;
}

void VeGiaoDien(Snake snake){	
	char score_str[10];
	setcolor(GREEN);
	outtextxy(550, 10, "YOURSCORE: ");		
	sprintf(score_str,"%d",snake.n*10 - 30);
	setcolor(WHITE);
	outtextxy(650, 10, score_str);
	setcolor(GREEN);
	outtextxy (70,340,"Right: D");
	outtextxy (70,400,"Left: A");
	outtextxy (265,340,"Up: W");
	outtextxy (265,400,"Down: S");
	outtextxy(70,450,"Pause/Resum: Space");	
	rectangle(MIN_X, MIN_Y, MAX_X, MAX_Y);
}

void VeRan(Snake snake){
	for(int i = 0; i < snake.n; i++){
		drawcircle(snake.dot[i].x, snake.dot[i].y, 3, WHITE);
		setcolor(WHITE);
	}
}

void VeHoaQua(HoaQua hq){		
	drawcircle(hq.td.x, hq.td.y, 3, YELLOW);
}

void HienThi(Snake snake, HoaQua hq){
	cleardevice();
	settextstyle(0,0,1);
	VeRan(snake);
	VeGiaoDien(snake);
	VeHoaQua(hq);		
}
			

void DieuKhien(Snake &snake){     
	for(int i = snake.n - 1; i > 0; i--){
		snake.dot[i] = snake.dot[i - 1];
	}
	
	if(snake.tt == UP){
		snake.dot[0].y -= 10;
		if(kbhit()){
			int key = getch();
			if(key == 'A' || key == 'a')
				snake.tt = LEFT;
			if(key == 'D' || key == 'd')
				snake.tt = RIGHT;
			if (key == 32){
				outtextxy (100,100,"Game Pause/Resume");
				key = getch();
				while (key != 32){
					key = getch();
					delay(0);
				}
				outtextxy (100,100,"Game Pause/Resume");
				delay(1000);
				key = 'W';
			}
		}
	}		
	else if(snake.tt == DOWN){
		snake.dot[0].y += 10;
		if(kbhit()){
			int key = getch();
			if(key == 'A' || key == 'a')
				snake.tt = LEFT;
			if(key == 'D' || key == 'd')
				snake.tt = RIGHT;
			if (key == 32){
				outtextxy (100,100,"Game Pause/Resume");
				key = getch();
				while (key != 32){
					key = getch();
					delay(0);
				}
				outtextxy (100,100,"Game Pause/Resume");
				delay(1000);
				key = 'S';
			}
		}
	}			
	else if(snake.tt == LEFT){
		snake.dot[0].x -= 10;
		if(kbhit()){
			int key = getch();
			if(key == 'W' || key == 'w')
				snake.tt = UP;
			if(key == 'S' || key == 's')
				snake.tt = DOWN;
			if (key == 32){
				outtextxy (100,100,"Game Pause/Resume");
				key = getch();
				while (key != 32){
					key = getch();
					delay(0);
				}
				outtextxy (100,100,"Game Pause/Resume");
				delay(1000);
				key = 'A';
			}
		}
	}			
	else if(snake.tt == RIGHT){
		snake.dot[0].x += 10;
		if(kbhit()){
			int key = getch();
			if(key == 'S' || key == 's')
				snake.tt = DOWN;
			if(key == 'W' || key == 'w')
				snake.tt = UP;
			if (key == 32){
				outtextxy (100,100,"Game Pause/Resume");
				key = getch();
				while (key != 32){
					key = getch();
					delay(0);
				}
				outtextxy (100,100,"Game Pause/Resume");
				delay(1000);
				key = 'D';
			}
		}
	}
			
}

int GetHightScore(){
	FILE *fp;
	fp = fopen("ListHighScore.txt", "r");
	int temp = 0;
	char _temp[25];
	fscanf(fp, "%s %d", _temp, &temp);
	return temp;
}

void CheckHighScore(int _score){	
	if(_score > GetHightScore()){
		FILE *fp;
		fp = fopen("ListHighScore.txt", "w+");
		outtextxy(540,130,"Nhap ten: ");
		char _name[20]={""};
		char ch1;
		int x = 0;
		char str[2];
		str[1] = 0;
		while (ch1 != 13 && x < 10){
			do{
				ch1 = getch();
			}while (ch1 < 65 && ch1 >90 || ch1 < 97 && ch1 > 132);
			x++;
			str[0] = ch1;
			strcat(_name,str);
			outtextxy(540,150,_name);
			if(ch1 == 13){
				fputs(_name, fp);
				fprintf(fp, " %d", _score);
				exit(0);
			}					
		}		
	}		
}

void ShowHighScore(){
	cleardevice();
	int temp_score = 0;
	char key, score_str[10], temp_name[25];
	FILE *fp = fopen("ListHighScore.txt", "r");
	fscanf(fp, "%s %d", temp_name, &temp_score);
	sprintf(score_str,"%d",temp_score);
	outtextxy(10,10, "Nhan ESC de tro lai menu!");
	setcolor(YELLOW);
	settextstyle(1,0,2);
	outtextxy(250,200, "Ten");
	outtextxy(370,200, "Diem");
	outtextxy(250,250, temp_name);
	outtextxy(370,250, score_str);
	key = getch();
	if(key == 27){
		Menu();
	}
}	

void XuLy(Snake &snake, HoaQua &hq){
	if (snake.dot[0].x >= 500) snake.dot[0].x = 10;
    else if (snake.dot[0].x <= 10) snake.dot[0].x = 500 - 10;
    else if (snake.dot[0].y >= 300) snake.dot[0].y = 10;
    else if (snake.dot[0].y <= 10) snake.dot[0].y = 300 - 10;
    
    for (int i = 1; i < snake.n; i++)
		if (snake.dot[0].x == snake.dot[i].x &&	snake.dot[0].y == snake.dot[i].y){
			outtextxy(250,250,"Thua roi!");	
			CheckHighScore((snake.n*10 - 30));			
			while (getch() != 13);
		}
    
	if(snake.dot[0].x == hq.td.x && snake.dot[0].y == hq.td.y){	
		for(int i = snake.n; i > 0; i--)
			snake.dot[i] = snake.dot[i - 1];
			
			snake.n++;
			
			if(snake.tt == UP)
				snake.dot[0].y -= 10;
			else if(snake.tt == DOWN)
				snake.dot[0].y += 10;
			else if(snake.tt == LEFT)
				snake.dot[0].x -= 10;
			else if(snake.tt == RIGHT)
				snake.dot[0].x += 10;
				
			hq.td.x = (rand() % (39) + 3)*10;
			hq.td.y = (rand() % (19) + 3)*10;
	}
}

void run(){
	Snake snake;
	HoaQua hq;
	FILE *fp;
	KhoiTao(snake, hq);
	
	while(1){				
		HienThi(snake, hq);
		
		DieuKhien(snake);
		
		XuLy(snake, hq);
		
		delay(level);				
	}
}

void Menu(){
	cleardevice();
	int y = 200;	
	char ch;
	do
	{
		if(y == 200){
			cleardevice();
			settextstyle(1,0,2);
			setcolor (10);
			outtextxy(120,70,"GAME MENU");
			setcolor(YELLOW);
			outtextxy (220,200,"NEW GAME");
			setcolor(WHITE);
			outtextxy (220,270,"HIGH SCORE");
			outtextxy (220,340,"ABOUT");
			outtextxy (220,410,"QUIT GAME");
		}
		
		if(y == 270){
			cleardevice();
			settextstyle(1,0,2);
			setcolor (10);
			outtextxy(120,70,"GAME MENU");
			setcolor(WHITE);			
			outtextxy (220,200,"NEW GAME");
			setcolor(YELLOW);
			outtextxy (220,270,"HIGH SCORE");
			setcolor(WHITE);
			outtextxy (220,340,"ABOUT");
			outtextxy (220,410,"QUIT GAME");
		}
		
		if(y == 340){
			cleardevice();
			settextstyle(1,0,2);
			setcolor (10);
			outtextxy(120,70,"GAME MENU");
			setcolor(WHITE);			
			outtextxy (220,200,"NEW GAME");
			outtextxy (220,270,"HIGH SCORE");			
			setcolor(YELLOW);
			outtextxy (220,340,"ABOUT");
			setcolor(WHITE);
			outtextxy (220,410,"QUIT GAME");
		}
		if(y == 410){
			cleardevice();
			settextstyle(1,0,2);
			setcolor (10);
			outtextxy(120,70,"GAME MENU");
			setcolor(WHITE);			
			outtextxy (220,200,"NEW GAME");
			outtextxy (220,270,"HIGH SCORE");			
			outtextxy (220,340,"ABOUT");
			setcolor(YELLOW);
			outtextxy (220,410,"QUIT GAME");
		}
		ch = getch();
		if(ch==(char)80)//xuong
		{
			y+=70;
		}
		else if (ch==(char)72)//len
		{
			y-=70;
		}
		if(y>410)y=200;
		if(y<200)y=410;
	}while(ch!=(char)13);//enter
	
	if(y == 200){
		run();
	}
	else if(y == 270){
		ShowHighScore();
	}
	else if(y == 340){
		cleardevice();
		settextstyle(0,0,1);
		setcolor(WHITE);
		outtextxy(10,10, "Nhan ESC de tro lai menu!");
		settextstyle(1,0,6);
		setcolor(GREEN);
		outtextxy(260,20,"ABOUT");
		settextstyle(1,0,2);
		setcolor(WHITE);
		outtextxy(170,100,"TRUONG DAI HOC DIEN LUC");
		setcolor(BLUE);
		outtextxy(170,150,"DE TAI");
		setcolor(WHITE);
		outtextxy(170,200,"TRO CHOI: RAN SAN MOI");
		setcolor(BLUE);
		outtextxy(170,270,"NGUOI THUC HIEN");
		setcolor(WHITE);
		outtextxy(170,320,"NGUYEN VAN DUNG - 1681310021");
		setcolor(BLUE);
		outtextxy(170,390,"GIANG VIEN HUONG DAN");
		setcolor(WHITE);
		outtextxy(170,440,"CU VIET DUNG");
		char key = getch();
		if(key == 27){
			Menu();
		}
	}
	else if(y == 410){
		exit(0);
	}
}

int main(){
	srand(time(NULL));
	initwindow(800,500);
	Menu();
	getch();
}
