#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int WIDTH = 30;
const int HEIGHT = 20;
int score = 0;
bool game_over = false;
string level = "Slow";

int spaceship_x = WIDTH / 2;
int spaceship_y = HEIGHT - 2;

const int MAX_ASTEROIDS = 10;
const int MAX_BULLETS = 5;

int asteroids[MAX_ASTEROIDS][2];
int bullets[MAX_BULLETS][2];

void initialize_game() {
    for (int i = 0; i < MAX_ASTEROIDS; ++i) {
        asteroids[i][0] = -1;
        asteroids[i][1] = -1;
    }
    for (int i = 0; i < MAX_BULLETS; ++i) {
        bullets[i][0] = -1;
        bullets[i][1] = -1;
    }
}

void clear_screen() {
    system("cls");
}

double get_speed() {
    if (score < 50) {
        level = "Slow";
        return 100; 
    } else if (score < 100) {
        level = "Medium";
        return 50; 
    } else {
        level = "Fast";
        return 25; 
    }
}

void draw() {
    clear_screen();
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1) {
                cout << '.';  
            } else if (x == spaceship_x && y == spaceship_y) {
                cout << '#';  
            } else {
                bool printed = false;

                for (int i = 0; i < MAX_ASTEROIDS; ++i) {
                    if (x == asteroids[i][0] && y == asteroids[i][1]) {
                        cout << 'O';  
                        printed = true;
                        break;
                    }
                }

                for (int i = 0; i < MAX_BULLETS; ++i) {
                    if (x == bullets[i][0] && y == bullets[i][1]) {
                        cout << '.';  
                        printed = true;
                        break;
                    }
                }

                if (!printed) {
                    cout << ' ';  
                }
            }
        }
        cout << endl;
    }
    cout << "Score: " << score << " | Level: " << level << endl;
}

void input_handling() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'w' && spaceship_y > 1) {
            spaceship_y--;  
        }
        if (key == 's' && spaceship_y < HEIGHT - 2) {
            spaceship_y++; 
        }
        if (key == 'a' && spaceship_x > 1) {
            spaceship_x--; 
        }
        if (key == 'd' && spaceship_x < WIDTH - 2) {
            spaceship_x++; 
        }
        if (key == ' ') {  
            for (int i = 0; i < MAX_BULLETS; ++i) {
                if (bullets[i][0] == -1 && bullets[i][1] == -1) {
                    bullets[i][0] = spaceship_x;
                    bullets[i][1] = spaceship_y - 1;
                    break;
                }
            }
        }
    }
}

void update_game_logic() {
    // Move bullets
    for (int i = 0; i < MAX_BULLETS; ++i) {
        if (bullets[i][1] > 0) {
            bullets[i][1]--;
        } else {
            bullets[i][0] = -1;
            bullets[i][1] = -1; 
        }
    }

    for (int i = 0; i < MAX_ASTEROIDS; ++i) {
        if (asteroids[i][1] > 0) {
            asteroids[i][1]++;
            if (asteroids[i][1] >= HEIGHT - 1) {
                asteroids[i][0] = -1;
                asteroids[i][1] = -1;  
            }
        }
    }

    for (int i = 0; i < MAX_BULLETS; ++i) {
        for (int j = 0; j < MAX_ASTEROIDS; ++j) {
            if (bullets[i][0] == asteroids[j][0] && bullets[i][1] == asteroids[j][1]) {
                score += 10;
                bullets[i][0] = -1;
                bullets[i][1] = -1;  
                asteroids[j][0] = -1;
                asteroids[j][1] = -1;  
            }
        }
    }

    for (int i = 0; i < MAX_ASTEROIDS; ++i) {
        if (spaceship_x == asteroids[i][0] && spaceship_y == asteroids[i][1]) {
            game_over = true;
        }
    }

    if (rand() % 10 == 0) {
        for (int i = 0; i < MAX_ASTEROIDS; ++i) {
            if (asteroids[i][0] == -1 && asteroids[i][1] == -1) {
                asteroids[i][0] = rand() % (WIDTH - 2) + 1;
                asteroids[i][1] = 1;
                break;
            }
        }
    }
}

void delay(double milliseconds) {
    Sleep(milliseconds);
}

int main() {
    srand(time(0));
    initialize_game();

    while (!game_over) {
        draw();
        input_handling();
        update_game_logic();
        delay(get_speed());
    }

    cout << "Game Over! Final Score: " << score << endl;
    return 0;
}
