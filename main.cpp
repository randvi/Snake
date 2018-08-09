// Snake Game console Windows

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

using namespace std; 

enum class Direction {RIGHT, LEFT, UP, DOWN};

enum colors {Black, Blue, Green, Aqua, Red, Purple, Yellow, White , Gray,
	    LightBlue, LightGreen, LightAqua, LightRed, LightPurple, LightYellow, BrightWhite};

const short MAX_SNAKE  = 10;
const int width = 77;
const int hight = 20;
int score = 0;
bool game_over = false;
Direction dir = Direction::UP;
// delay im ms
int speed = 200; 

void set_text_color(int font, int bgr = -1);
void goto_xy(short x, short y);
void setup();
class Snake;
class Fruit;

class GameBoard {
public:
    static char board[hight][width];
    const int board_bg = Black;
    GameBoard(){
        for(int i = 0; i < hight; ++i)
            for(int j = 0; j < width; ++j)
                board[i][j] = ' ';
    }
    
    void paint();
    void print_score(int sc) {
        goto_xy(73,25);
        set_text_color(LightRed, Gray);
        cout << sc*10;
    }

    void print_status(const char *s,  short c = LightGreen) {
        goto_xy(71,27);
        set_text_color(c, Gray);
        cout << s;
        for(int i = strlen(s) ; i < 8; ++i)
            cout << (" ");
    }

private:
    void draw_fruit();
    void draw_snake_item();
} snake_board;

char GameBoard::board[hight][width] = {};

class Fruit {
public:
    int x, y;
    static const char fruit_symbol = '@';
    void New() {
        x = rand() % width;
        y = rand() % hight;
    }
    void draw() {
        GameBoard::board[y][x] = Fruit::fruit_symbol;
    }
} fruit;


class Snake {
public:
    static const char snake_symbol = '$';
    Snake() {
        snake_size = 4;
        s[0].x = width / 2;
        s[0].y = hight / 2;
        for (int i = 1; i < snake_size; ++i){
            s[i].x = s[0].x;
            s[i].y = s[i-1].y + 1;
        }
    }
    
    void move(Direction dir){
        clear_tail();
        for (int i = snake_size; i > 0; i--) {
            s[i].x = s[i-1].x;
            s[i].y = s[i-1].y;
        }
        switch (dir) {
            case Direction::UP:
                if (s[0].y != 0) {
                    s[0].y--; 
                } else {
                    s[0].y = hight - 1;
                    // clear();
                    // snake_size = 2;
                    // s[0].y = 1;
                    // s[1].y = 0;
                    // s[1].x = s[0].x;
                    // dir = Direction::DOWN;
                }
                break;
            case Direction::DOWN:
                s[0].y++; 
                break;
            case Direction::LEFT:
                s[0].x--; 
                break; 
            case Direction::RIGHT:
                s[0].x++; 
                break;
        }
        // if (snake[0].x < 0) { 
        //     clear();
        //     dir =  Direction::RIGHT;
        //     return;
        // }
        // // if (snake[0].y < 0) dir =  Direction::DOWN;
        // if (snake[0].x > width) dir =  Direction::LEFT;
        // if (snake[0].y > hight) dir =  Direction::UP;
 
    } 
    void draw() {
        for (int i = 0; i < snake_size; ++i){
            int x = s[i].x;
            int y = s[i].y;
            GameBoard::board[y][x] = snake_symbol;
        }
    }
private:
    int snake_size;
    struct coord {
        int x;
        int y;
    } s[MAX_SNAKE];
    
    void clear_tail() {
        int x = s[snake_size-1].x;
        int y = s[snake_size-1].y;
        GameBoard::board[y][x] = ' ';
    }
    void clear() {
        for (int i = 0; i < snake_size; ++i){
            int x = s[i].x;
            int y = s[i].y;
            GameBoard::board[y][x] = ' ';
        }
    }

} snake;

void GameBoard::paint() {
    set_text_color(Gray, Gray);
    for (int i = 0; i < hight; ++i) {
        for (int j = 0 ; j < width; j++) {
            goto_xy(3 + j, 2 + i);
            char ch = board[i][j];
            if (ch == ' ') {
                cout << ' ';
            } else if (ch == Snake::snake_symbol) { 
                draw_snake_item();
            } else if (ch == Fruit::fruit_symbol) {
                draw_fruit();
            }
        }
    }
}

void GameBoard::draw_fruit() {
        set_text_color(LightGreen, Gray);
        cout << Fruit::fruit_symbol; 
        set_text_color(Black, Gray); 

    }
void GameBoard::draw_snake_item() {
    set_text_color(LightYellow, Gray);
    cout << Snake::snake_symbol;
    set_text_color(Black, Gray);
}

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
    // setup screen mode
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

    snake_board.print_score(score);
    snake_board.print_status("Playing");
     // randomize
    srand(time(NULL));
   
    snake.draw();
    fruit.New();
    fruit.draw();
    snake_board.paint();
    
}

void check_kbd() {
    if (kbhit()) {
        char ch = getch();
        goto_xy(10,29);
        cout << "ch = " << (int)ch;
        if (ch == -32) {
            switch (getch()) {
                case 72:
                    if (dir != Direction::DOWN)
                        dir = Direction::UP;
                    break;
                case 80:
                    if (dir !=Direction::UP)
                        dir = Direction::DOWN;
                    break;
                case 75:
                    if (dir != Direction::RIGHT) 
                        dir = Direction::LEFT;
                    break; 
                case 77:
                    if (dir != Direction::LEFT)
                        dir = Direction::RIGHT;
                    break;
            }
        } else {
            if (ch == 'q' or ch == 'Q') 
                game_over = true;
            else if (ch == ' ') {
                snake_board.print_status("Pause");
                while(1) {
                    char z=getch();
                    if(z == 'q') {
                        game_over = true;
                        return;
                    }
                    if(z == ' ')
                        break;
                }
                snake_board.print_status("Playing");
            }
        }
    }
}

void tick() {
    snake.move(dir);
}

int main() {
    setup();
    // goto_xy(20, 10);
    // cout << "x = " << fruit.x << " " << "y = " << fruit.y;
    // char ch = getch();

	while (!game_over) {

        check_kbd();
        //char ch = getch();
        tick();
        snake.draw();
        snake_board.paint();
    
        Sleep(100);//speed
    }
	
    return 0;
}
