const int MAP_LEN = 4;
const int POW2[20] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
const int LEN_OF_POW2[20] = {0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4};
int map[16];  // 一维数组模拟二维
int score = 0, step = 0, seed = 0;

int rand() {
    seed = (seed * 214013 + 2531011) % 0x40000000;
    if (seed < 0) seed = -seed;
    return seed / 65536 % 0x8000;
}

void clear_map() {
    int i = 0;
    while (i < 16) {
        map[i] = 0;
        i++;
    }
}

void generate() {
    int empty = 0, chosen = -1, i = 0;
    while (i < 16) {
        if (map[i] == 0) {
            empty++;
            if (rand() % empty == 0) chosen = i;
        }
        i++;
    }
    map[chosen] = (rand() % 2) + 1;
}

void print_map() {
    putch(115); putch(116); putch(101); putch(112); putch(58); putch(32); // step:
    putint(step);
    putch(10); // 换行
    putch(115); putch(99); putch(111); putch(114); putch(101); putch(58); putch(32); // score:
    putint(score);
    putch(10); // 换行

    int i = 0;
    while (i < 16) {
        if (map[i] == 0) {
            putch(95); // '_'
        } else {
            putint(POW2[map[i]]);
        }
        putch(32); // 空格
        if ((i + 1) % 4 == 0) {
            putch(10); // 换行
        }
        i++;
    }
}


int move_line(int start, int inc) {
    int merged = 0, moved = 0, i = start, j;
    while (i >= 0 && i < 16) {
        if (map[i] != 0) {
            j = i - inc;
            while (j >= 0 && j < 16 && map[j] == 0) j -= inc;
            if (j >= 0 && j < 16 && map[j] == map[i] && !merged) {
                map[j]++;
                score += POW2[map[j]];
                map[i] = 0;
                merged = 1;
                moved = 1;
            } else if (j + inc != i) {
                map[j + inc] = map[i];
                map[i] = 0;
                moved = 1;
            }
        }
        i += inc;
    }
    return moved;
}

int move(int dir) {
    int moved = 0, i = 0;
    while (i < 4) {
        if (dir == 0) moved |= move_line(i * 4 + 3, -1); // 向左
        else if (dir == 1) moved |= move_line(i * 4, 1); // 向右
        else if (dir == 2) moved |= move_line(12 + i, -4); // 向上
        else if (dir == 3) moved |= move_line(i, 4); // 向下
        i++;
    }
    return moved;
}

int try_move() {
    int i = 0, backup[16];
    while (i < 16) {
        backup[i] = map[i];
        i++;
    }
    int result = move(0) || move(1) || move(2) || move(3);
    i = 0;
    while (i < 16) {
        map[i] = backup[i];
        i++;
    }
    return result;
}

void init() {
    clear_map();
    score = 0;
    step = 0;
    generate();
  //  generate();
}

int main() {
    putch(73);  // 'I'
    putch(110); // 'n'
    putch(112); // 'p'
    putch(117); // 'u'
    putch(116); // 't'
    putch(32);  // ' ' (空格)
    putch(97);  // 'a'
    putch(32);  // ' ' (空格)
    putch(114); // 'r'
    putch(97);  // 'a'
    putch(110); // 'n'
    putch(100); // 'd'
    putch(111); // 'o'
    putch(109); // 'm'
    putch(32);  // ' ' (空格)
    putch(110); // 'n'
    putch(117); // 'u'
    putch(109); // 'm'
    putch(98);  // 'b'
    putch(101); // 'e'
    putch(114); // 'r'
    putch(58);  // ':'
    putch(10);  // '\n'
    seed = getint();
    init();
    print_map();
    while (1) {
        int ch = getint();
        if (ch == 1) step += move(2);
        else if (ch == 2) step += move(0);
        else if (ch == 3) step += move(3);
        else if (ch == 4) step += move(1);
        else if (ch == 5) break;
        else continue;
        if (step > 0) generate();
        print_map();
        if (!try_move()) {
            putch(71);  // 'G'
            putch(97);  // 'a'
            putch(109); // 'm'
            putch(101); // 'e'
            putch(32);  // ' ' (空格)
            putch(79);  // 'O'
            putch(118); // 'v'
            putch(101); // 'e'
            putch(114); // 'r'
            putch(46);  // '.'
            putch(10);  // '\n'
            break;
        }
    }
    return 0;
}