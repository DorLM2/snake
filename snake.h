//
// Created by Dlam on 2024/3/22.
//

#ifndef S_SNAKE_H
#define S_SNAKE_H
void mode_raw(int);
void _fflush();
void underline(int);
char read_key();
int key_pressed();
void get_pass(char *, char *);
int getche();
int getch();
int where_x();
int where_y();
int keyboard_hit();
void line(int, char, char);
void goto_xy(int, int);
void sleep_for(int);
void bold(int);
void text_color(int);
void test_background(int);
void clear_eol();
void clear_screen();
void clear_win(int, int, int, int);
void ClearDisplay();
#endif //S_SNAKE_H
