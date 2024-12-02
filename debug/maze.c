// Maze configurations
const int WIDTH = 100, HEIGHT = 100;
const int VISITED = 0;
const int NO_LEFT_WALL = 1;
const int NO_TOP_WALL = 2;
const int LEFT = 0, RIGHT = 1, TOP = 2, DOWN = 3;

int map[30000];   // 一维数组模拟地图，最大可支持100x100迷宫
int image[30000]; // 一维数组模拟图像
int seed;         // 随机数种子

// 伪随机数生成器
int rand() {
    seed = (seed * 214013 + 2531011) % 0x40000000;
    if (seed < 0) seed = -seed;
    return seed / 65536 % 0x8000;
}

// 获取邻居的有效性
int get_neighbor(int x, int y, int dir) {
    if (dir == LEFT) {
        if (x == 0) return 0;
        return 1;
    } else if (dir == RIGHT) {
        if (x == WIDTH - 1) return 0;
        return 1;
    } else if (dir == TOP) {
        if (y == 0) return 0;
        return 1;
    } else if (dir == DOWN) {
        if (y == HEIGHT - 1) return 0;
        return 1;
    }
    return 0;
}

// 移除墙壁
void remove_wall(int x, int y, int dir) {
    if (dir == LEFT) {
        map[y * WIDTH + x] = 1;  // 左墙去掉
    } else if (dir == RIGHT) {
        map[y * WIDTH + (x + 1)] = 1;  // 右墙去掉
    } else if (dir == TOP) {
        map[(y - 1) * WIDTH + x] = 1;  // 上墙去掉
    } else if (dir == DOWN) {
        map[(y + 1) * WIDTH + x] = 1;  // 下墙去掉
    }
}

// 深度优先生成迷宫
void gen_maze(int x, int y) {
    map[y * WIDTH + x] = VISITED;
    int dirs[4] = {LEFT, RIGHT, TOP, DOWN};
    
    // 随机打乱方向
    int i = 0;
    while (i < 4) {
        int r = rand() % 4;
        int temp = dirs[i];
        dirs[i] = dirs[r];
        dirs[r] = temp;
        i = i + 1;
    }

    int j = 0;
    while (j < 4) {
        int new_x = x, new_y = y;
        if (get_neighbor(new_x, new_y, dirs[j]) && map[new_y * WIDTH + new_x] != VISITED) {
            remove_wall(x, y, dirs[j]);
            if (dirs[j] == LEFT) new_x = new_x - 1;
            else if (dirs[j] == RIGHT) new_x = new_x + 1;
            else if (dirs[j] == TOP) new_y = new_y - 1;
            else if (dirs[j] == DOWN) new_y = new_y + 1;
            
            gen_maze(new_x, new_y);
        }
        j = j + 1;
    }
}

// 渲染迷宫
void render() {
    int y = 0;
    while (y < HEIGHT) {
        int x = 0;
        while (x < WIDTH) {
            if (map[y * WIDTH + x] == 1) {
                image[(y * 2 + 1) * (WIDTH * 2 + 1) + (x * 2)] = 1;  // 标记墙壁
                image[(y * 2) * (WIDTH * 2 + 1) + (x * 2 + 1)] = 1;
            }
            image[(y * 2) * (WIDTH * 2 + 1) + (x * 2)] = 1;  // 填充迷宫边界
            x = x + 1;
        }
        y = y + 1;
    }

    y = 0;
    while (y < HEIGHT * 2 + 1) {
        image[y * (WIDTH * 2 + 1) + WIDTH * 2] = 1;  // 渲染右边界
        y = y + 1;
    }
    
    int x = 0;
    while (x < WIDTH * 2 + 1) {
        image[(HEIGHT * 2) * (WIDTH * 2 + 1) + x] = 1;  // 渲染下边界
        x = x + 1;
    }
}

int main() {
    seed = 12345678;  // 初始化随机数种子
    int zoom = 2;     // 缩放因子

    // 生成迷宫
    gen_maze(rand() % WIDTH, rand() % HEIGHT);
    render();

    // 输出图片信息
    putch(80); putch(51); putch(10);  // 输出初始文本（可以根据实际需要修改）
    putint((WIDTH * 2 + 1) * zoom); putch(32);
    putint((HEIGHT * 2 + 1) * zoom); putch(10);
    putint(255); putch(10);  // 输出最大颜色值255

    // 输出每个像素的颜色值
    int y = 0;
    while (y < (HEIGHT * 2 + 1) * zoom) {
        int x = 0;
        while (x < (WIDTH * 2 + 1) * zoom) {
            int xx = x / zoom, yy = y / zoom;
            int r = image[yy * (WIDTH * 2 + 1) + xx] * 255 * x / ((WIDTH * 2 + 1) * zoom);
            int g = image[yy * (WIDTH * 2 + 1) + xx] * 255 * y / ((HEIGHT * 2 + 1) * zoom);
            int b = image[yy * (WIDTH * 2 + 1) + xx] * 255;
            
            putint(r); putch(32); putint(g); putch(32); putint(b); putch(32);
            x = x + 1;
        }
        putch(10);  // 换行
        y = y + 1;
    }

    return 0;
}
