// Maze configurations.
const int WIDTH = 100, HEIGHT = 100;

// Directions.
const int LEFT = 0;
const int RIGHT = 1;
const int TOP = 2;
const int DOWN = 3;

// Map properties represented as three 1D arrays.
int visited[HEIGHT * WIDTH];      // To mark if a cell is visited.
int no_left_wall[HEIGHT * WIDTH]; // To indicate if there's no left wall.
int no_top_wall[HEIGHT * WIDTH];  // To indicate if there's no top wall.

// Image for rendering the maze.
int image[(HEIGHT * 2 + 1) * (WIDTH * 2 + 1)]; // 1D array for rendering.

// Random seed.
int seed;

// Random number generator.
int rand() {
  seed = (seed * 214013 + 2531011) % 0x40000000;
  if (seed < 0) seed = -seed;
  return seed / 65536 % 0x8000;
}

// Gets neighbors of the given cell by direction.
// Returns 0 if the neighbor is out of the map.
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

// Removes the wall at the given direction of the cell.
void remove_wall(int x, int y, int dir) {
  int index = y * WIDTH + x;
  if (dir == LEFT) {
    no_left_wall[index] = 1;
  } else if (dir == RIGHT) {
    no_left_wall[(y * WIDTH + x + 1)] = 1; // Right cell's left wall.
  } else if (dir == TOP) {
    no_top_wall[index] = 1;
  } else if (dir == DOWN) {
    no_top_wall[((y + 1) * WIDTH + x)] = 1; // Bottom cell's top wall.
  }
}

// Generates a maze using Depth-First Search.
void gen_maze(int x, int y) {
  int index = y * WIDTH + x;
  visited[index] = 1;

  // Shuffle directions.
  int dirs[4] = {LEFT, RIGHT, TOP, DOWN};
  for (int i = 0; i < 4; ++i) {
    int r = rand() % 4;
    int temp = dirs[i];
    dirs[i] = dirs[r];
    dirs[r] = temp;
  }

  // Explore neighbors.
  for (int i = 0; i < 4; ++i) {
    int xx = x, yy = y;
    if (get_neighbor(xx, yy, dirs[i]) && !visited[yy * WIDTH + xx]) {
      remove_wall(x, y, dirs[i]);
      gen_maze(xx, yy);
    }
  }
}

// Draws the maze into the image array.
void render() {
  // Initialize image array to black (walls everywhere).
  for (int i = 0; i < (HEIGHT * 2 + 1) * (WIDTH * 2 + 1); ++i) {
    image[i] = 0;
  }

  // Draw cells and walls based on the maze properties.
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      int index = y * WIDTH + x;

      // Set the center of the cell to white (path).
      image[(y * 2 + 1) * (WIDTH * 2 + 1) + (x * 2 + 1)] = 1;

      // Set the left wall if it exists.
      if (!no_left_wall[index]) {
        image[(y * 2 + 1) * (WIDTH * 2 + 1) + x * 2] = 1;
      }

      // Set the top wall if it exists.
      if (!no_top_wall[index]) {
        image[(y * 2) * (WIDTH * 2 + 1) + (x * 2 + 1)] = 1;
      }
    }
  }

  // Draw the bottom and right borders of the maze.
  for (int y = 0; y < HEIGHT * 2 + 1; ++y) {
    image[y * (WIDTH * 2 + 1) + (WIDTH * 2)] = 1; // Right border.
  }
  for (int x = 0; x < WIDTH * 2 + 1; ++x) {
    image[(HEIGHT * 2) * (WIDTH * 2 + 1) + x] = 1; // Bottom border.
  }
}

int main() {
//  puts("-----\n");
  puts("Input a random number as seed:\n");
  seed = getint(); // Set the random seed.
  puts("Input a number as the zoom factor for rendering:\n");
  int zoom = getint(); // Zoom factor for rendering.
  starttime();

  // Generate the maze.
  gen_maze(rand() % WIDTH, rand() % HEIGHT);
  render();

  stoptime();
  starttime();

  // Output the PPM image header.
  putch(80); putch(51); putch(10); // P3
  putint((WIDTH * 2 + 1) * zoom); putch(32);
  putint((HEIGHT * 2 + 1) * zoom); putch(10);
  putint(255); putch(10);

  // Output the maze image data.
  for (int y = 0; y < (HEIGHT * 2 + 1) * zoom; ++y) {
    for (int x = 0; x < (WIDTH * 2 + 1) * zoom; ++x) {
      int xx = x / zoom, yy = y / zoom;
      int cell_value = image[yy * (WIDTH * 2 + 1) + xx];
      int r = cell_value * 255 * x / ((WIDTH * 2 + 1) * zoom);
      int g = cell_value * 255 * y / ((HEIGHT * 2 + 1) * zoom);
      int b = cell_value * 255;
      putint(r); putch(32); putint(g); putch(32); putint(b); putch(32);
    }
    putch(10);
  }

  stoptime();
  return 0;
}
