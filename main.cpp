#include <iostream>
#include "snake.h"
#include <vector>
#include <random>
#define INIT_LENGHT 2
#define INIT_LOCATION_X 10
#define INIT_LOCATION_Y 7
#define INT_HIGH 10
#define INT_WIGHT 60
#define SET_FOOD_NUMBER 4
class snake;
class Canvas;
class food;
class snake_xy;
bool operator==(const snake_xy &s1, const snake_xy &s2);
enum Direction{
    Up,Down,Right,Left
};
class Canvas{
private:
    int c_high, c_wight;
public:
    Canvas(int l,int w)
            :c_high(l),c_wight(w){}
    void PrintCanvas()const{
        for (int i = 1; i < c_wight + 1; ++i) {
            goto_xy(i,1);
            std::cout<< "|";
            goto_xy(i,c_high);
            std::cout<< "|";
        }
        for (int i = 2; i < c_high; ++i) {
            goto_xy(1,i);
            std::cout<<"|";
            goto_xy(c_wight,i);
            std::cout<<"|";
        }
        std::cout<<std::endl;//猜测：c++里只会打印光标之前的内容
    }

};

struct snake_xy{
    int x,y;
};




class snake{
private:
    std::vector<snake_xy>snakexy;
    int lenght;


public:
    snake_xy *h_snakexy;
    Direction dir;

    snake(){
        dir = Up;
        lenght = INIT_LENGHT;
//        snakexy[0].x = INIT_LOCATION_X;
//        snakexy[0].y = INIT_LOCATION_Y;
        snakexy.push_back({INIT_LOCATION_X,INIT_LOCATION_Y});
//        snakexy.push_back({11,7});
        h_snakexy = &snakexy.front();
    }
    ~snake() {
        ClearDisplay();
        goto_xy(0,0);
        std::cout<<"the game is destroyed"<<std::endl;
    }

//    ~snake(){
//        goto_xy(1,INT_HIGH);//将光标移动到开始的位置
//    }
    void SnakeClear() {
        int m_x,m_y;
        m_x = snakexy.back().x;//保存最后一个位置的坐标
        m_y = snakexy.back().y;
        goto_xy(m_x,m_y);//清除最后一个位置的坐标
        std::cout<< ' ';
    }
    void SnakeMove(){//移动和清除最后的一个坐标


//         assert(status);
        //让蛇的身体跟着头走一个接着一个，这样可以省去很多麻烦
        for(int i = snakexy.size() - 1;i > 0;i--){
            snakexy[i] = snakexy[i - 1];
        }


        // 移动头的位置
        // 只需要改变头的值就可以实现移动
        if(this->dir == Right){
            h_snakexy->x++;
        }
        else if(this->dir == Left){
            h_snakexy->x--;
        }
        else if(this->dir == Up){
            h_snakexy->y--;
        }
        else if(this->dir == Down){
            h_snakexy->y++;
        }

        //sleep写在这里是因为需要画出来显示以下再执行清除

    }

    void SnakePrint(){
//        for(std::vector<snake_xy>::iterator it = snakexy.begin(); it != snakexy.end();++it){
//            goto_xy(it->x,it->y);
//            std::cout<< '0';
//        }c++11新加入的循环方式->
//        for(auto itr: snakexy){
//
//            goto_xy(itr.x,itr.y);
//
//                std::cout<< "0";
//        }
        for (int i = (int) snakexy.size() - 1; i >= 0; i--) {

            goto_xy(snakexy[i].x, snakexy[i].y);

            std::cout << "0";
        }
        sleep_for(700);
    }

    void AddSnakeBody(){
        if(dir == Up)
            snakexy.push_back({snakexy.back().x,snakexy.back().y + 1});
        else if(dir == Down)
            snakexy.push_back({snakexy.back().x,snakexy.back().y - 1});
        else if(dir == Right)
            snakexy.push_back({snakexy.back().x - 1,snakexy.back().y});
        else if(dir == Left)
            snakexy.push_back({snakexy.back().x + 1,snakexy.back().y});
        h_snakexy = &snakexy.front();
    }
    bool SnakeEatMyself(){
        for(int i = 1;i < snakexy.size() ;i++){
            if(*(h_snakexy) == snakexy[i]){
                return false;
            }
        }
        return true;
    }

    bool BumpDetection(){//碰撞检测碰到画布边缘退出游戏
        if (h_snakexy->x >= INT_WIGHT || h_snakexy->x <= 1) {
            return false;
        }

        if(h_snakexy->y >= INT_HIGH || h_snakexy->y <= 1)
            return false;
        return true;
    }

    void KeyBoardControl(){
        if(keyboard_hit()){
            int ch = getch();
            if(ch == 119 && dir != Down)//'w'
                dir = Up;
            else if(ch == 115 && dir != Up)//‘s’
                dir = Down;
            else if(ch == 97 && dir != Right)//'a'
                dir = Left;
            else if(ch == 100 && dir != Left)//'d'
                dir = Right;
        }
    }


};

bool operator==(const snake_xy &s1, const snake_xy &s2) {
    if(s1.x == s2.x && s1.y == s2.y){
        return true;
    }
    return false;
}



struct food_xy{
    int x,y;
};


class food{
private:

    char symbol = '*';

public:
    int amount ;
    std::vector<food_xy> foodxy;
    food(){amount = SET_FOOD_NUMBER;}
    void CreateFood(){
        if (!foodxy.size()) {//如果没有食物再创建食物，正好可以当做初始化的程序
            std::uniform_int_distribution<unsigned> uw(02, INT_WIGHT - 1);//随机数生成范围
            std::uniform_int_distribution<unsigned> uh(02, INT_HIGH - 1);
            std::default_random_engine RandomEngine;//随机数生成器
            for (int i = 0; i < SET_FOOD_NUMBER; ++i) {
                foodxy.push_back({(int) uw(RandomEngine), (int) uh(RandomEngine)});
            }

        }
    }


    void FoodPrint(){
//        for(auto itr : foodxy){
//            goto_xy(itr.x,itr.y);
//            std::cout<<symbol;
//        }
        for(int i = 0;i < foodxy.size();i++){
            goto_xy(foodxy[i].x,foodxy[i].y);
            std::cout<<symbol;
        }
    }
};

//bool operator==( food_xy foodXy, snake_xy snakeXy){
//    if(snakeXy.x == foodXy.x && snakeXy.y == foodXy.y)
//        return true;
//    else
//        return false;
//}
//void SnakeBumpFood(snake &snake,food &food){
//    snake_xy snakehead = *(snake.h_snakexy);
//    for(auto itr :food.foodxy){
//        if(snakehead == itr)
//    }
//}两种不同的类好像不可以进行重载
bool FoodXyComparisonSnakeXy(snake_xy snakeXy, food_xy foodXy) {
    if(snakeXy.x == foodXy.x && snakeXy.y == foodXy.y){

        return true;
    }

    return false;
}
void SnakeBumpFood(snake &snake, food &food) {
    for(int i = 0;i < food.foodxy.size();i++){
        if (FoodXyComparisonSnakeXy(*(snake.h_snakexy), food.foodxy[i])) {
            snake.AddSnakeBody();
            food.foodxy.erase(food.foodxy.begin() + i);

        }
    }


}
std::ostream& operator<<( std::ostream &out, snake &s){
    out<<s.h_snakexy->x<<s.h_snakexy->y;
    return out;
}

int main() {
    Canvas c(INT_HIGH,INT_WIGHT);
    snake s,s1;

    food f;
    ClearDisplay();
    c.PrintCanvas();

    while(1){
        f.CreateFood();

        f.FoodPrint();

        s.SnakePrint();


        bool Bstatus = s.BumpDetection();
        bool Sstatus = s.SnakeEatMyself();
        if (!Bstatus || !Sstatus) {
            break;
        }

        s.KeyBoardControl();
        s.SnakeClear();
        s.SnakeMove();
        SnakeBumpFood(s,f);

    }


    return 0;
}
