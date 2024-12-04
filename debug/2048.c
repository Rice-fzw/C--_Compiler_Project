const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

const int MAP_LEN = 4;

const int POW2[20] = {1,     2,     4,     8,      16,     32,    64,
                      128,   256,   512,   1024,   2048,   4096,  8192,
                      16384, 32768, 65536, 131072, 262144, 524288};
const int LEN_OF_POW2[20] = {0, 1, 1, 1, 2, 2, 2, 3, 3, 3,
                             4, 4, 4, 4, 5, 5, 5, 6, 6, 6};

const int CHR_SPACE = 32;
const int CHR_ENTER = 10;

int map[MAP_LEN * MAP_LEN];  // 使用一维数组替代二维数组
int score;
int step;
int max_num_len;
int alive;
int seed;

// 获取一维数组中对应的位置
int get_index(int x, int y) {
    return x * MAP_LEN + y;
}

int rand() {
    seed = (seed * 214013 + 2531011) % 0x40000000;
    if (seed < 0)
        seed = -seed;
    return seed / 65536 % 0x8000;
}


void clear_map() {
    int i = 0;
    while (i < MAP_LEN * MAP_LEN) {
        map[i] = 0;
        i = i + 1;
    }
}

void init() {
    clear_map();
    score = 0;
    step = 0;
    max_num_len = 1;
    alive = 1;
}

void print_map() {
    putch(CHR_ENTER);
    puts("step: ");
    putint(step);
    putch(CHR_ENTER);
    puts("score: ");
    putint(score);
    putch(CHR_ENTER);
    
    int x = 0;
    while (x < MAP_LEN) {
        int y = 0;
        while (y < MAP_LEN) {
            int value = map[get_index(x, y)];
            if (value == 0) {
                int i = LEN_OF_POW2[value] + 1;
                while (i <= max_num_len) {
                    puts("_");
                    i = i + 1;
                }
                putch(CHR_SPACE);
            } else {
                putint(POW2[value]);
                int i = LEN_OF_POW2[value];
                while (i <= max_num_len) {
                    putch(CHR_SPACE);
                    i = i + 1;
                }
            }
            y = y + 1;
        }
        putch(CHR_ENTER);
        x = x + 1;
    }
}

int move_one_line(int line_idx, int direction) {
    int moved = 0;
    int val1, val2, val3, val4;
    int idx1, idx2, idx3, idx4;
    
    // 获取索引和值
    if (direction == UP || direction == DOWN) {
        idx1 = get_index(0, line_idx);
        idx2 = get_index(1, line_idx);
        idx3 = get_index(2, line_idx);
        idx4 = get_index(3, line_idx);
    } else {
        idx1 = get_index(line_idx, 0);
        idx2 = get_index(line_idx, 1);
        idx3 = get_index(line_idx, 2);
        idx4 = get_index(line_idx, 3);
    }
    
    val1 = map[idx1];
    val2 = map[idx2];
    val3 = map[idx3];
    val4 = map[idx4];
    
    // 合并逻辑
    if (direction == UP || direction == LEFT) {
        // 移动非零数到前面
        if (val1 == 0) {
            val1 = val2;
            val2 = val3;
            val3 = val4;
            val4 = 0;
            if (val1 != 0) moved = 1;
        }
        if (val2 == 0) {
            val2 = val3;
            val3 = val4;
            val4 = 0;
            if (val2 != 0) moved = 1;
        }
        if (val3 == 0) {
            val3 = val4;
            val4 = 0;
            if (val3 != 0) moved = 1;
        }
        
        // 合并相同数字
        if (val1 == val2 && val1 != 0) {
            val1 = val1 + 1;
            val2 = val3;
            val3 = val4;
            val4 = 0;
            moved = 1;
            score = score + POW2[val1];
            if (LEN_OF_POW2[val1] > max_num_len) {
                max_num_len = LEN_OF_POW2[val1];
            }
        }
        if (val2 == val3 && val2 != 0) {
            val2 = val2 + 1;
            val3 = val4;
            val4 = 0;
            moved = 1;
            score = score + POW2[val2];
            if (LEN_OF_POW2[val2] > max_num_len) {
                max_num_len = LEN_OF_POW2[val2];
            }
        }
        if (val3 == val4 && val3 != 0) {
            val3 = val3 + 1;
            val4 = 0;
            moved = 1;
            score = score + POW2[val3];
            if (LEN_OF_POW2[val3] > max_num_len) {
                max_num_len = LEN_OF_POW2[val3];
            }
        }
    } else {
        // 向下或向右的移动逻辑
        if (val4 == 0) {
            val4 = val3;
            val3 = val2;
            val2 = val1;
            val1 = 0;
            if (val4 != 0) moved = 1;
        }
        if (val3 == 0) {
            val3 = val2;
            val2 = val1;
            val1 = 0;
            if (val3 != 0) moved = 1;
        }
        if (val2 == 0) {
            val2 = val1;
            val1 = 0;
            if (val2 != 0) moved = 1;
        }
        
        // 合并相同数字
        if (val4 == val3 && val4 != 0) {
            val4 = val4 + 1;
            val3 = val2;
            val2 = val1;
            val1 = 0;
            moved = 1;
            score = score + POW2[val4];
            if (LEN_OF_POW2[val4] > max_num_len) {
                max_num_len = LEN_OF_POW2[val4];
            }
        }
        if (val3 == val2 && val3 != 0) {
            val3 = val3 + 1;
            val2 = val1;
            val1 = 0;
            moved = 1;
            score = score + POW2[val3];
            if (LEN_OF_POW2[val3] > max_num_len) {
                max_num_len = LEN_OF_POW2[val3];
            }
        }
        if (val2 == val1 && val2 != 0) {
            val2 = val2 + 1;
            val1 = 0;
            moved = 1;
            score = score + POW2[val2];
            if (LEN_OF_POW2[val2] > max_num_len) {
                max_num_len = LEN_OF_POW2[val2];
            }
        }
    }
    
    // 更新地图
    map[idx1] = val1;
    map[idx2] = val2;
    map[idx3] = val3;
    map[idx4] = val4;
    
    return moved;
}

void move(int direction) {
    int moved = 0;
    int i = 0;
    
    while (i < MAP_LEN) {
        if (move_one_line(i, direction)) {
            moved = 1;
        }
        i = i + 1;
    }
    
    if (!moved) {
        puts("Invalid input. Try again.");
        putch(CHR_ENTER);
        return;
    }
    
    step = step + 1;
    generate();
    print_map();
}

void generate() {
    int empty = 0;
    int chosen_pos = 0;
    int i = 0;
    
    while (i < MAP_LEN * MAP_LEN) {
        if (map[i] == 0) {
            empty = empty + 1;
            if (rand() % empty == 0) {
                chosen_pos = i;
            }
        }
        i = i + 1;
    }
    
    int num;
    if (rand() % 2 < 1) {
        num = 1;
    } else {
        num = 2;
    }
    map[chosen_pos] = num;
}

int can_move() {
    int i = 0;
    
    // 检查是否有空格
    while (i < MAP_LEN * MAP_LEN) {
        if (map[i] == 0) {
            return 1;
        }
        i = i + 1;
    }
    
    // 检查相邻数字是否可以合并
    i = 0;
    while (i < MAP_LEN * MAP_LEN) {
        int x = i / MAP_LEN;
        int y = i % MAP_LEN;
        
        // 检查右边
        if (y < MAP_LEN - 1 && map[i] == map[i + 1]) {
            return 1;
        }
        // 检查下边
        if (x < MAP_LEN - 1 && map[i] == map[i + MAP_LEN]) {
            return 1;
        }
        i = i + 1;
    }
    
    return 0;
}

int main() {
    puts("Input a random number: \n");
    seed = getint();
    init();
    generate();
    print_map();
    
    while (alive) {
        int ch = getch();
        if (ch == 119) {
            move(UP);
        } else if (ch == 97) {
            move(LEFT);
        } else if (ch == 115) {
            move(DOWN);
        } else if (ch == 100) {
            move(RIGHT);
        } else if (ch == 104) {
            puts("w, a, s, d: move\nh: print this help\nq: quit\np: print the map\n");
        } else if (ch == 113 || ch == -1) {
            puts("Game over!\n");
            return 0;
        } else if (ch == 112) {
            putch(CHR_ENTER);
            print_map();
        } else if (ch == 32 || ch == 10 || ch == 13) {
            continue;
        } else {
            puts("Invalid input. Try again.");
            putch(CHR_ENTER);
            seed = (seed + ch) % 0x40000000;
        }
        
        if (!can_move()) {
            puts("Game over!\n");
            break;
        }
    }
    return 0;
}