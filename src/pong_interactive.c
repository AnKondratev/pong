#include <ncurses.h>
#include <stdio.h>

void StartGame(int height, int width, int ball_pos_y, int ball_pos_x, int ball_dir_y, int ball_dir_x,
               int pos_plt_p1, int pos_plt_p2, int score_player1, int score_player2, char input);
void widthLine(int width);
void Appearance(int height, int width, int ball_pos_y, int ball_pos_x, int pos_plt_p1, int pos_plt_p2,
                int score_player1, int score_player2);

void PlayerScore(int score_player1, int score_player2, int width);
void GameOver(char input, int width, int score_player1, int score_player2);

int main() {
    int height = 25;
    int width = 80;
    int ball_pos_y = height / 2;
    int ball_pos_x = width / 2;
    int ball_dir_y = 1;
    int ball_dir_x = -1;
    int pos_plt_p1 = height / 2;
    int pos_plt_p2 = pos_plt_p1;
    int score_player1 = 0;
    int score_player2 = 0;
    char input = ' ';

    // Инициализация ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    timeout(100);  // Задержка ожидания ввода (100 мс)

    StartGame(height, width, ball_pos_y, ball_pos_x, ball_dir_y, ball_dir_x, pos_plt_p1, pos_plt_p2,
              score_player1, score_player2, input);

    // Завершение работы с ncurses
    endwin();

    return 0;
}

void widthLine(int width) {
    for (int i = 0; i < width; i++) {
        printw("-");
    }
}

void Appearance(int height, int width, int ball_pos_y, int ball_pos_x, int pos_plt_p1, int pos_plt_p2,
                int score_player1, int score_player2) {
    clear();
    PlayerScore(score_player1, score_player2, width);
    widthLine(width);
    printw("\n");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 0 || x == width - 1)
                printw("|");
            else if (y == ball_pos_y && x == ball_pos_x)
                printw("*");
            else if ((y == pos_plt_p1 || y == pos_plt_p1 + 1 || y == pos_plt_p1 + 2) && x == 2)
                printw("|");
            else if ((y == pos_plt_p2 || y == pos_plt_p2 + 1 || y == pos_plt_p2 + 2) && x == width - 3)
                printw("|");
            else if (x == width / 2)
                printw("|");
            else
                printw(" ");
        }
        printw("\n");
    }
    widthLine(width);
    printw("\n");
    refresh();
}

void StartGame(int height, int width, int ball_pos_y, int ball_pos_x, int ball_dir_y, int ball_dir_x,
               int pos_plt_p1, int pos_plt_p2, int score_player1, int score_player2, char input) {
    while (score_player1 < 21 && score_player2 < 21 && input != 'q') {
        Appearance(height, width, ball_pos_y, ball_pos_x, pos_plt_p1, pos_plt_p2, score_player1,
                   score_player2);

        input = getch();
        if (input == ERR) {
            input = ' ';
        }

        if (ball_pos_x == 1) {
            score_player2++;
            ball_pos_y = height / 2;
            ball_pos_x = width / 2;
            ball_dir_x = 1;
        }
        if (ball_pos_x == width - 2) {
            score_player1++;
            ball_pos_y = height / 2;
            ball_pos_x = width / 2;
            ball_dir_x = -1;
        }
        if (ball_pos_y == height - 1) {
            ball_dir_y = -ball_dir_y;
        }
        if (ball_pos_y == 0) {
            ball_dir_y = -ball_dir_y;
        }
        if (ball_pos_x == 3 &&
            (ball_pos_y == pos_plt_p1 || ball_pos_y == pos_plt_p1 + 1 || ball_pos_y == pos_plt_p1 + 2)) {
            ball_dir_x = -ball_dir_x;
        }
        if (ball_pos_x == width - 4 &&
            (ball_pos_y == pos_plt_p2 || ball_pos_y == pos_plt_p2 + 1 || ball_pos_y == pos_plt_p2 + 2)) {
            ball_dir_x = -ball_dir_x;
        }
        ball_pos_y += ball_dir_y;
        ball_pos_x += ball_dir_x;
        if (input == 'a' || input == 'z' || input == 'k' || input == 'm' || input == ' ') {
            if (input == 'a' && pos_plt_p1 > 0) pos_plt_p1--;
            if (input == 'z' && pos_plt_p1 < height - 3) pos_plt_p1++;
            if (input == 'k' && pos_plt_p2 > 0) pos_plt_p2--;
            if (input == 'm' && pos_plt_p2 < height - 3) pos_plt_p2++;
        }
        GameOver(input, width, score_player1, score_player2);
    }
}

void PlayerScore(int score_player1, int score_player2, int width) {
    for (int x = 0; x <= width / 2 - 6; x++) {
        if (x < width / 2 - 6) {
            printw(" ");
        } else {
            printw("SCORE: %d | %d\n", score_player1, score_player2);
        }
    }
    printw("\n");
}

void GameOver(char input, int width, int score_player1, int score_player2) {
    for (int x = 0; x <= width / 2 - 6; x++) {
        if (x < width / 2 - 6) {
            printw(" ");
        } else if (input == 'q') {
            printw("Nobody wins");
        } else {
            if (score_player1 > score_player2) {
                printw("Player one win!");
            } else {
                printw("Player two win!");
            }
        }
    }
    printw("\n\n\n");
    printw(":'######::::::'###::::'##::::'##:'########:::::'#######::'##::::'##:'########:'########::\n");
    printw("'##... ##::::'## ##::: ###::'###: ##.....:::::'##.... ##: ##:::: ##: ##.....:: ##.... ##:\n");
    printw("##:::..::::'##:. ##:: ####'####: ##:::::::::: ##:::: ##: ##:::: ##: ##::::::: ##:::: ##:\n");
    printw("##::'####:'##:::. ##: ## ### ##: ######:::::: ##:::: ##: ##:::: ##: ######::: ########::\n");
    printw("##::: ##:: #########: ##. #: ##: ##...::::::: ##:::: ##:. ##:: ##:: ##...:::: ##.. ##:::\n");
    printw("##::: ##:: ##.... ##: ##:.:: ##: ##:::::::::: ##:::: ##::. ## ##::: ##::::::: ##::. ##::\n");
    printw(". ######::: ##:::: ##: ##:::: ##: ########::::. #######::::. ###:::: ########: ##:::. ##:\n");
    printw(":......::::..:::::..::..:::::..::........::::::.......::::::...:::::........::..:::::..::\n");
}
