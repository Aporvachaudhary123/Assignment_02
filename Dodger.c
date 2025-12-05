#include <stdio.h>
#include <conio.h>   // For getch() & _kbhit()
#include <windows.h> // For Sleep()
#include <stdlib.h>  // For rand()
#include <time.h>    // For time()

// Player lanes: 0 (Left), 1 (Middle), 2 (Right)

int main() {
    int playerLane = 1;  // Player starts in middle lane
    int obstacleLane, obstacleStep;
    int score = 0;
    int speed = 150;     // Slow speed (beginner friendly)

    srand(time(0));      // Generate random obstacles

    obstacleLane = rand() % 3;
    obstacleStep = 0;

    printf("WELCOME TO CAR DODGER!\n");
    printf("Use LEFT and RIGHT Arrow keys to move.\n");
    printf("Press any key to start...\n");
    getch();

    while (1) {

        // ----------- USER INPUT (Move Player) ----------
        if (_kbhit()) {
            char key = getch();

            if (key == 75 && playerLane > 0)  // Left Arrow
                playerLane--;

            if (key == 77 && playerLane < 2)  // Right Arrow
                playerLane++;
        }

        // ----------- CLEAR SCREEN ----------
        system("cls");

        printf("Score: %d\n", score);
        printf("-------------\n");

        // ----------- DRAW GAME AREA ----------
        for (int row = 0; row < 10; row++) {
            if (row == obstacleStep) {
                if (obstacleLane == 0) printf("| X       |\n");
                if (obstacleLane == 1) printf("|    X    |\n");
                if (obstacleLane == 2) printf("|       X |\n");
            } else {
                printf("|         |\n");
            }
        }

        // Draw Player Car
        if (playerLane == 0) printf("| A       |\n");
        if (playerLane == 1) printf("|    A    |\n");
        if (playerLane == 2) printf("|       A |\n");

        // ------------- COLLISION CHECK -------------
        if (obstacleStep == 10 && playerLane == obstacleLane) {
            printf("\nGAME OVER!\n");
            printf("Final Score: %d\n", score);
            break;
        }

        // Move obstacle down
        obstacleStep++;

        // Obstacle resets when it reaches bottom
        if (obstacleStep > 10) {
            obstacleStep = 0;
            obstacleLane = rand() % 3;
            score++;

            if (speed > 40) speed--; // Increase difficulty slowly
        }

        Sleep(speed); // Slow game down
    }

    printf("Press R to Restart or Q to Quit...\n");

    while (1) {
        if (_kbhit()) {
            char ch = getch();
            if (ch == 'R' || ch == 'r')
                main(); // restart
            if (ch == 'Q' || ch == 'q')
                return 0;
        }
    }
}
