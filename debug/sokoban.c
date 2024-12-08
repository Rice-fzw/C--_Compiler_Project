const int ROW=10; // 游戏区行数
const int COL = 10; // 游戏区列数

const int CHR_SPACE = 32;
const int CHR_ENTER = 10;


int manx=1,many=1,manv=1;
 

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

int get_index(int x,int y){return x*COL+y;}

void print(){
    int mani=get_index(manx,many);
    int x = 0;
    while (x < ROW) {
        int y = 0;
        while (y < COL) {
            int index=get_index(x,y);
            if(index==mani){
                putch(64);
            }else if (Map[index]==0){
                putch(46);
            }else if(Map[index]==1){
                putch(35);//墙
            }else if(Map[index]==2){
                putch(33);//目的地
            }else{
                putch(98);//箱子
            }
            y = y + 1;
        }
        putch(CHR_ENTER);
        x = x + 1;
    }
    int y = 0;
    putint((COL<<1));
//    putch(CHR_ENTER);
}
/*初始化游戏角色*/

int main()
{
    puts("w, a, s, d: move\n");
    puts("h: print this help\n");
    puts("q: quit\np: print the map\n");
    puts("You are int the position '@', and you need to push b into the !\n");
    /*打印地图*/
    print();
    /*游戏逻辑主体*/
    while (1)
    {
        /*获取角色控制指令*/
        int willx = 0;      // 暂存角色移动后的横坐标
        int willy = 0;      // 暂存角色移动后的纵坐标
        int bx = 0;      // 暂存角色移动后的横坐标
        int by = 0;      // 暂存角色移动后的纵坐标

        int ch = getch();
        if (ch == 119) {
            willx = manx- manv;
            willy = many ;
            bx=willx-manv;
            by=willy;
        } else if (ch == 97) {
            willx = manx ;
            willy = many- manv;
            bx=willx;
            by=willy-manv;
        } else if (ch == 100) {
            willx = manx;
            willy = many +manv;
            bx=willx;
            by=willy+manv;
        } else if (ch == 115) {
            willx = manx+ manv;
            willy = many;
            bx=willx+manv;
            by=willy;
        } else if (ch == 104) {
            puts("w, a, s, d: move\n");
            puts("h: print this help\n");
            puts("q: quit\np: print the map\n");
        } else if (ch == 113 || ch == -1) {
            puts("Game over!\n");
            return 0;
        } else if (ch == 112) {
            putch(CHR_ENTER);
            print();
        } else if (ch == 32 || ch == 10 || ch == 13) {
            continue;
        } else {
            puts("Invalid input. Try again.\n");
        //    putch(CHR_ENTER);
            // seed = (seed + ch) % 0x40000000;
        }
 
        /*判断交互条件*/
        int index=get_index(willx,willy);
        if(Map[index]==0)// 在通道中移动
        {
            manx = willx; // 传递移动后的横坐标
            many = willy; // 传递移动后的纵坐标
            print();
        }else if(Map[index]==1){//墙
            puts("Can not enter into the wall. Try again.");
            putch(CHR_ENTER);
        }else if(Map[index]==3){// 箱子
            int bindex=get_index(bx,by);
            if(Map[bindex]==2){//goal
                Map[index]=0;
                Map[bindex]=3;
                manx = willx; // 传递移动后的横坐标
                many = willy; // 传递移动后的纵坐标
                print();
                puts("Win!");
                putch(CHR_ENTER);
                break;
            }else if(Map[bindex]==0){// 在通道中移动
                Map[index]=0;
                Map[bindex]=3;
                manx = willx; // 传递移动后的横坐标
                many = willy; // 传递移动后的纵坐标
                print();
            }else{// 墙
                puts("Unvalid move. Try again.");
                putch(CHR_ENTER);
            }
        }
    }
}