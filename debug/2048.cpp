#include <iostream>
using namespace std;

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

const char CHR_SPACE = 32;
const char CHR_ENTER = 10;

int map[MAP_LEN * MAP_LEN]; 
int score;
int step;
int max_num_len;
int alive;
int seed;

// get index
int get_index(int x, int y) {
    return x * MAP_LEN + y;
}

int rand_num() {
    seed = (seed * 414047 + 4531063) % 0x40000000;
    if (seed < 0)
        seed = -seed;
    return seed / 41489 % 0x8000;
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
    cout << CHR_ENTER;
    cout << "step: ";
    cout << step;
    cout << CHR_ENTER;
    cout << "score: ";
    cout << score;
    cout << CHR_ENTER;
    
    int x = 0;
    while (x < MAP_LEN) {
        int y = 0;
        while (y < MAP_LEN) {
            int value = map[get_index(x, y)];
            if (value == 0) {
                int i = LEN_OF_POW2[value] + 1;
                while (i <= max_num_len) {
                    cout << "_";
                    i = i + 1;
                }
                cout << CHR_SPACE;
            } else {
                cout << POW2[value];
                int i = LEN_OF_POW2[value];
                while (i <= max_num_len) {
                    cout << CHR_SPACE;
                    i = i + 1;
                }
            }
            y = y + 1;
        }
        cout << CHR_ENTER;
        x = x + 1;
    }
}

int move_one_line(int line_idx, int direction) {
    int moved = 0;
    int val1, val2, val3, val4;
    int idx1, idx2, idx3, idx4;
    
    // get operations and value
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
    
    if (direction == UP || direction == LEFT) {
        // movement
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
        
        // integrate the same number
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
        // move right or down
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
    // update the graph
    map[idx1] = val1;
    map[idx2] = val2;
    map[idx3] = val3;
    map[idx4] = val4;
    return moved;
}

void generate() {
    int empty = 0;
    int chosen_pos = 0;
    int i = 0;
    while (i < MAP_LEN * MAP_LEN) {
        if (map[i] == 0) {
            empty = empty + 1;
            if (rand_num() % empty == 0) {
                chosen_pos = i;
            }
        }
        i = i + 1;
    }
    int num;
    if (rand_num() % 2 < 1) {
        num = 1;
    } else {
        num = 2;
    }
    map[chosen_pos] = num;
}

void move(int direction) {
    int moved = 0;
    int i = 0;
    while (i < MAP_LEN) {
        for(int j = 0; j < 4; ++j){
            if (move_one_line(j, direction)) {
                moved = 1;
            }
        }
        i = i + 1;
    }
    if (!moved) {
        cout << "Invalid input. Try again." << CHR_ENTER;
        return;
    }
    
    step = step + 1;
    generate();
    print_map();
    return;
}

int can_move() {
    int i = 0;
    
    // check whether there is a space
    while (i < MAP_LEN * MAP_LEN) {
        if (map[i] == 0) {
            return 1;
        }
        i = i + 1;
    }
    
    // check whether two neighbors can integrate
    i = 0;
    while (i < MAP_LEN * MAP_LEN) {
        int x = i / MAP_LEN;
        int y = i % MAP_LEN;
        
        // check righthandsides
        if (y < MAP_LEN - 1 && map[i] == map[i + 1]) {
            return 1;
        }
        // check downwards
        if (x < MAP_LEN - 1 && map[i] == map[i + MAP_LEN]) {
            return 1;
        }
        i = i + 1;
    }
    
    return 0;
}

int main() {
    cout << "Input a random number as the seed: \n";
    cin >> seed;
    cout << "w, a, s, d: move\n";
    cout << "h: print this help\n";
    cout << "q: quit\np: print the map\n";
    init();
    generate();
    print_map();
    
    char ch;
    while (alive && cin.get(ch)) {
        if (ch == 'w') {
            move(UP);
        } else if (ch == 'a') {
            move(LEFT);
        } else if (ch == 's') {
            move(DOWN);
        } else if (ch == 'd') {
            move(RIGHT);
        } else if (ch == 'h') {
            cout << "w, a, s, d: move\n";
            cout << "h: print this help\n";
            cout << "q: quit\np: print the map\n";
        } else if (ch == 'q') {
            cout << "Game over!\n";
            return 0;
        } else if (ch == 'p') {
            cout << CHR_ENTER;
            print_map();
        } else if (ch == ' ' || ch == '\n' || ch == '\r') {
            continue;
        } else {
            cout << "Invalid input. Try again." << CHR_ENTER;
            seed = (seed + ch) % 0x40000000;
        }
        
        if (!can_move()) {
            cout << "Game over!\n";
            break;
        }
    }
    return 0;
}