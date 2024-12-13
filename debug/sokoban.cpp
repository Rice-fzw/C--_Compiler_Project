#include <iostream>
using namespace std;

const int ROW = 10; // 游戏区行数
const int COL = 10; // 游戏区列数

const char CHR_SPACE = 32;
const char CHR_ENTER = 10;

int manx = 1, many = 1, manv = 1;

/*初始化地图信息，墙壁为1，通道为0*/
int Map[10010] =
{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 2, 1,
    1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 1, 1, 1, 1, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 0, 1, 1,
    1, 0, 1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 1, 1, 3, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

int get_index(int x, int y) { return x * COL + y; }

void print() {
    int mani = get_index(manx, many);
    int x = 0;
    while (x < ROW) {
        int y = 0;
        while (y < COL) {
            int index = get_index(x, y);
            if (index == mani) {
                cout << '@';
            }
            else if (Map[index] == 0) {
                cout << '.';
            }
            else if (Map[index] == 1) {
                cout << '#'; //墙
            }
            else if (Map[index] == 2) {
                cout << '!'; //目的地
            }
            else {
                cout << 'b'; //箱子
            }
            y = y + 1;
        }
        cout << CHR_ENTER;
        x = x + 1;
    }
}

int main()
{
    cout << "w, a, s, d: move\n";
    cout << "h: print this help\n";
    cout << "q: quit\np: print the map\n";
    cout << "You are int the position '@', and you need to push b into the !\n";
    /*打印地图*/
    print();
    /*游戏逻辑主体*/
    
    char ch;
    while (cin.get(ch))
    {
        /*获取角色控制指令*/
        int willx = 0;      // 暂存角色移动后的横坐标
        int willy = 0;      // 暂存角色移动后的纵坐标
        int bx = 0;      // 暂存角色移动后的横坐标
        int by = 0;      // 暂存角色移动后的纵坐标

        if (ch == 'w') {
            willx = manx - manv;
            willy = many;
            bx = willx - manv;
            by = willy;
        }
        else if (ch == 'a') {
            willx = manx;
            willy = many - manv;
            bx = willx;
            by = willy - manv;
        }
        else if (ch == 'd') {
            willx = manx;
            willy = many + manv;
            bx = willx;
            by = willy + manv;
        }
        else if (ch == 's') {
            willx = manx + manv;
            willy = many;
            bx = willx + manv;
            by = willy;
        }
        else if (ch == 'h') {
            cout << "w, a, s, d: move\n";
            cout << "h: print this help\n";
            cout << "q: quit\np: print the map\n";
        }
        else if (ch == 'q') {
            cout << "Game over!\n";
            return 0;
        }
        else if (ch == 'p') {
            cout << CHR_ENTER;
            print();
        }
        else if (ch == ' ' || ch == '\n' || ch == '\r') {
            continue;
        }
        else {
            cout << "Invalid input. Try again.\n";
        }

        /*判断交互条件*/
        int index = get_index(willx, willy);
        if (Map[index] == 0)// 在通道中移动
        {
            manx = willx; // 传递移动后的横坐标
            many = willy; // 传递移动后的纵坐标
            print();
        }
        else if (Map[index] == 1) {//墙
            cout << "Can not enter into the wall. Try again." << CHR_ENTER;
        }
        else if (Map[index] == 3) {// 箱子
            int bindex = get_index(bx, by);
            if (Map[bindex] == 2) {//goal
                Map[index] = 0;
                Map[bindex] = 3;
                manx = willx; // 传递移动后的横坐标
                many = willy; // 传递移动后的纵坐标
                print();
                cout << "Win!" << CHR_ENTER;
                break;
            }
            else if (Map[bindex] == 0) {// 在通道中移动
                Map[index] = 0;
                Map[bindex] = 3;
                manx = willx; // 传递移动后的横坐标
                many = willy; // 传递移动后的纵坐标
                print();
            }
            else {// 墙
                cout << "Unvalid move. Try again." << CHR_ENTER;
            }
        }
    }
    return 0;
}
