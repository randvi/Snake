// Snake Game console Windows

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

using namespace std; 

enum Diraction {RIGHT, LEFT, UP, DOWN};

enum colors {Black, Blue, Green, Aqua, Red, Purple, Yellow, White , Gray,
	    LightBlue, LightGreen, LightAqua, LightRed, LightPurple, LightYellow, BrightWhite};

const short MAX_SNAKE  = 10;
const int width = 77;
const int hight = 20;
int score = 0;
bool game_over = false;
Diraction dir = UP;
int snake_size = 4;

struct coord {
    short x;
    short y;
};

coord snake[MAX_SNAKE];
coord fruit;
int speed = 200; // delay im ms

void print_score(int sc); 
void print_status(const char *s, short c = LightGreen);
void set_text_color(int font, int bgr = -1);
void goto_xy(short x, short y);
void setup();
void draw_field();
void draw_snake();

void set_text_color(int font, int bgr) {
    if (font < 0 || font > 15)
        return;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if(bgr >= 0 && bgr < 16)
        SetConsoleTextAttribute(h, font | bgr * 16);
    else
        SetConsoleTextAttribute(h, font);
}

void goto_xy(short x, short y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {x, y});
} 

void setup() {
    // disable cousor
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize=1;
    cursor.bVisible=false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
   
    system("mode con:cols=83 lines=30");
    system("title Snake Game - www.pinmode.by");
    set_text_color(Gray, Gray);
    system("cls");
    
    // draw field for game 
    set_text_color(LightBlue,Gray);
    cout << "\n  " << char(218);
    for(int x = 0; x < 77; ++x)
        cout << char(196);
    cout << char(191);
    for(int x = 0; x < 20; ++x) {
        goto_xy(2, x+2);
        cout << char(179);
        goto_xy(80, x+2);
        cout << char(179);
    }
    cout << "\n  " << char(192);
    for( int x = 0; x < 77; ++x)
        cout << char(196);
    cout << char(217);
    // footer
    // left area
    set_text_color(Red,Gray);
    cout << "\n\n";
    cout << "  " << char(218);
    for(int x = 0; x < 21; x++)
        cout << char(196);
    cout << char (191) << "\n  ";
    cout << char(179) << " S N A K E   G A M E " << char(179);
    cout << "\n  " << char(192);
    for(int x = 0; x < 21; ++x)
        cout << char(196);
    cout << char(217);
    // center area
    goto_xy(27,25);
    cout << "Press 'q' to Quit";
    goto_xy(27,26);
    cout << "Press Space to Pause and Play";
    //right area
    goto_xy(58,24);
    cout << char(218);
    for(int x = 0; x < 21; ++x)
        cout << char(196);
    cout << char(191);
    goto_xy(58, 25);
    cout << char(179) << "  SCORE  :           " << char(179);
    goto_xy(58, 26);
    cout << char(179);
    goto_xy(80, 26);
    cout << char(179);
    goto_xy(58, 27);
    cout << char(179) << "  STATUS :           " << char(179);
    goto_xy(58, 28);
    cout << char(192);
    for(int x = 0; x < 21; ++x)
        cout << char(196);
    cout << char(217);
    goto_xy(5, 28);
    set_text_color(LightBlue, Gray);
    cout << "www.pinMode.by";

    print_score(score);
    print_status("Playing");
     // randomize
    srand(time(NULL));
    fruit.x = rand() % width;
    fruit.y = rand() % hight;
    // init snake;
    snake[0].x = width / 2;
    snake[0].y = hight / 2;
    for (int i = 1; i < snake_size; ++i){
        snake[i].x = snake[0].x;
        snake[i].y = snake[i-1].y + 1;;
    }
    draw_field();
    draw_snake();
}

void print_score(int sc) {
    goto_xy(73,25);
    set_text_color(LightRed, Gray);
    cout << sc*10;
}

void print_status(const char *s, short c) {
    goto_xy(71,27);
    set_text_color(c, Gray);
    cout << s;
    for(int i = strlen(s) ; i < 8; ++i)
        cout << (" ");
} 

void check_kbd() {
    if (kbhit()) {
        char ch = getch();
        goto_xy(10,29);
        cout << "ch = " << (int)ch;
        if (ch == -32) {
            switch (getch()) {
                case 72:
                    if (dir != DOWN)
                        dir = UP;
                    break;
                case 80:
                    if (dir != UP)
                        dir = DOWN;
                    break;
                case 75:
                    if (dir != RIGHT) 
                        dir = LEFT;
                    break; 
                case 77:
                    if (dir != LEFT)
                        dir = RIGHT;
                    break;
            }
        } else {
            if (ch == 'q' or ch == 'Q') 
                game_over = true;
            else if (ch == ' ') {
                print_status("Pause");
                while(1) {
                    char z=getch();
                    if(z == 'q') {
                        game_over = true;
                        return;
                    }
                    if(z == ' ')
                        break;
                }
                print_status("Playing");
            }
        }
    }
}


void draw_fruit() {
    set_text_color(LightGreen, Gray);
    cout << "@"; 
    set_text_color(Black, Gray); 
}

void draw_snake_element() {
    set_text_color(LightYellow, Gray);
    cout << "$"; 
    set_text_color(Black, Gray); 
}

void draw_field() {
    set_text_color(Gray, Gray);
    for (int i = 0; i < hight; ++i) {
        for (int j = 0 ; j < width; j++) {
            goto_xy(3 + j, 2 + i);
            if (j == fruit.x && i == fruit.y)
                draw_fruit();
            else if ((j == snake[0].x) && (i == snake[0].y))
                draw_snake_element();
            else 
                cout << ' ';
        } 
    }  
} 

void draw_snake() {
    set_text_color(LightYellow, Gray);
    for (int i = 0; i < snake_size; ++i) {
        goto_xy(3 + snake[i].x, 2 + snake[i].y);
        cout << "$";
    } 
    set_text_color(Black, Gray);
}

void tick() {
    for (int i = snake_size; i > 0; i--) {
        snake[i].x = snake[i-1].x;
        snake[i].y = snake[i-1].y;
    }
    switch (dir) {
        case UP:
            snake[0].y--; 
            break;
        case DOWN:
            snake[0].y++; 
            break;
        case LEFT:
            snake[0].x--; 
            break; 
        case RIGHT:
            snake[0].x++; 
            break;
    }
}

int main() {
    setup();
    // goto_xy(20, 10);
    // cout << "x = " << fruit.x << " " << "y = " << fruit.y;
    char ch = getch();

	while (!game_over) {

        check_kbd();
        // char ch = getch();
        tick();
        draw_field();
        draw_snake();
        Sleep(300);//speed
    }
	
    return 0;
}
