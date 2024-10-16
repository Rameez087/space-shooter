import os
import random
import time
import keyboard

WIDTH = 30
HEIGHT = 20
score = 0
game_over = False
level = "Slow" 

spaceship = {"x": WIDTH // 2, "y": HEIGHT - 2}
asteroids = []
bullets = []

def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')

def get_speed():
    global level
    if score < 50:
        level = "Slow"
        return 0.1  
    elif score < 100:
        level = "Medium"
        return 0.05  
    else:
        level = "Fast"
        return 0.025  

def draw():
    clear_screen()
    for y in range(HEIGHT):
        for x in range(WIDTH):
            if y == 0 or y == HEIGHT - 1 or x == 0 or x == WIDTH - 1:
                print('.', end='') 
            elif x == spaceship["x"] and y == spaceship["y"]:
                print('#', end='')  
            else:
                printed = False
                for asteroid in asteroids:
                    if x == asteroid["x"] and y == asteroid["y"]:
                        print('O', end='')  
                        printed = True
                        break
                for bullet in bullets:
                    if x == bullet["x"] and y == bullet["y"]:
                        print('.', end='') 
                        printed = True
                        break
                if not printed:
                    print(' ', end='')  
        print()
    print(f"Score: {score} | Level: {level}")

def input_handling():
    if keyboard.is_pressed('w') and spaceship["y"] > 1: 
        spaceship["y"] -= 1
    if keyboard.is_pressed('s') and spaceship["y"] < HEIGHT - 2:
        spaceship["y"] += 1
    if keyboard.is_pressed('a') and spaceship["x"] > 1: 
        spaceship["x"] -= 1
    if keyboard.is_pressed('d') and spaceship["x"] < WIDTH - 2: 
        spaceship["x"] += 1
    if keyboard.is_pressed('space'): 
        bullets.append({"x": spaceship["x"], "y": spaceship["y"] - 1})

def update_game_logic():
    global score, game_over

    for bullet in bullets[:]:
        bullet["y"] -= 1
        if bullet["y"] < 1:
            bullets.remove(bullet)

    for asteroid in asteroids[:]:
        asteroid["y"] += 1
        if asteroid["y"] >= HEIGHT - 1:
            asteroids.remove(asteroid)

    for bullet in bullets[:]:
        for asteroid in asteroids[:]:
            if bullet["x"] == asteroid["x"] and bullet["y"] == asteroid["y"]:
                score += 10
                bullets.remove(bullet)
                asteroids.remove(asteroid)
                break

    for asteroid in asteroids:
        if asteroid["x"] == spaceship["x"] and asteroid["y"] == spaceship["y"]:
            game_over = True

    if random.randint(0, 9) == 0:
        asteroids.append({"x": random.randint(1, WIDTH - 2), "y": 1})

def main():
    global game_over
    while not game_over:
        draw()
        input_handling()
        update_game_logic()
        time.sleep(get_speed())

    print(f"Game Over! Final Score: {score}")

if __name__ == "__main__":
    main()
