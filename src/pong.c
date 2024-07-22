#include <stdio.h>

void StartGame(int height, int width, int ball_pos_y, int ball_pos_x, int ball_dir_y, int ball_dir_x,
               int pos_plt_p1, int pos_plt_p2, int score_player1, int score_player2, char input);
void widthLine(int width);
void AppearanceAndDynamics(int height, int width, int ball_pos_y, int ball_pos_x, int pos_plt_p1,
                           int pos_plt_p2, int score_player1, int score_player2);

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
    StartGame(height, width, ball_pos_y, ball_pos_x, ball_dir_y, ball_dir_x, pos_plt_p1, pos_plt_p2,
              score_player1, score_player2, input);
    return 0;
}

void widthLine(int width) {
    for (int i = 0; i < width; i++) {
        printf("\033[32;42m-\033[0m");
    }
}

void AppearanceAndDynamics(int height, int width, int ball_pos_y, int ball_pos_x, int pos_plt_p1,
                           int pos_plt_p2, int score_player1, int score_player2) {
    printf("\e[1;1H\e[2J");
    PlayerScore(score_player1, score_player2, width);
    widthLine(width);
    printf("\n");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 0 || x == width - 1)
                printf("\033[32;42m|\033[0m");
            else if (y == ball_pos_y && x == ball_pos_x)
                printf("\033[32;45m*\033[0m");
            else if ((y == pos_plt_p1 || y == pos_plt_p1 + 1 || y == pos_plt_p1 + 2) && x == 2)
                printf("\033[30;40m|\033[0m");
            else if ((y == pos_plt_p2 || y == pos_plt_p2 + 1 || y == pos_plt_p2 + 2) && x == width - 3)
                printf("\033[30;40m|\033[0m");
            else if (x == width / 2)
                printf("\033[37;47m|\033[0m");
            else
                printf("\033[42m \033[0m");
        }
        printf("\n");
    }
    widthLine(width);
    printf("\n");
}

void StartGame(int height, int width, int ball_pos_y, int ball_pos_x, int ball_dir_y, int ball_dir_x,
               int pos_plt_p1, int pos_plt_p2, int score_player1, int score_player2, char input) {
    while (score_player1 < 21 && score_player2 < 21 && input != 'q') {
        AppearanceAndDynamics(height, width, ball_pos_y, ball_pos_x, pos_plt_p1, pos_plt_p2, score_player1,
                              score_player2);

        input = getchar();
        while (getchar() != '\n')
            ;

        if (input == '\n') {
            continue;
        }

        ball_pos_y += ball_dir_y;
        ball_pos_x += ball_dir_x;

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
        if ((ball_pos_x == 3 &&
             (ball_pos_y == pos_plt_p1 || ball_pos_y == pos_plt_p1 + 1 || ball_pos_y == pos_plt_p1 - 1)) ||
            (ball_pos_x == 3 &&
             (ball_pos_y == pos_plt_p1 || ball_pos_y == pos_plt_p1 + 2 || ball_pos_y == pos_plt_p1 - 2))) {
            ball_dir_x = -ball_dir_x;
        }
        if ((ball_pos_x == width - 4 &&
             (ball_pos_y == pos_plt_p2 || ball_pos_y == pos_plt_p2 + 1 || ball_pos_y == pos_plt_p2 - 1)) ||
            (ball_pos_x == width - 4 &&
             (ball_pos_y == pos_plt_p2 || ball_pos_y == pos_plt_p2 + 2 || ball_pos_y == pos_plt_p2 - 2))) {
            ball_dir_x = -ball_dir_x;
        }

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
            printf(" ");
        } else {
            printf("SCORE: %d | %d\n", score_player1, score_player2);
        }
    }
    printf("\n");
}

void GameOver(char input, int width, int score_player1, int score_player2) {
    for (int x = 0; x <= width / 2 - 6; x++) {
        if (x < width / 2 - 6) {
            printf(" ");
        } else if (input == 'q') {
            printf("Nobody wins");
        } else {
            if (score_player1 > score_player2) {
                printf("Player one win!");
            } else {
                printf("Player two win!");
            }
        }
    }
    printf("\n\n\n");
    printf(
        "\033[32m:'######::::::'###::::'##::::'##:'########:::::'#######::'##::::'##:'########:'########::"
        "\033[0m\n");
    printf(
        "\033[32m'##... ##::::'## ##::: ###::'###: ##.....:::::'##.... ##: ##:::: ##: ##.....:: ##.... "
        "##:\033[0m\n");
    printf(
        "\033[33m##:::..::::'##:. ##:: ####'####: ##:::::::::: ##:::: ##: ##:::: ##: ##::::::: ##:::: "
        "##:\033[0m\n");
    printf(
        "\033[33m##::'####:'##:::. ##: ## ### ##: ######:::::: ##:::: ##: ##:::: ##: ######::: "
        "########::\033[0m\n");
    printf(
        "\033[33m##::: ##:: #########: ##. #: ##: ##...::::::: ##:::: ##:. ##:: ##:: ##...:::: ##.. "
        "##:::\033[0m\n");
    printf(
        "\033[31m##::: ##:: ##.... ##: ##:.:: ##: ##:::::::::: ##:::: ##::. ## ##::: ##::::::: ##::. "
        "##::\033[0m\n");
    printf(
        "\033[31m. ######::: ##:::: ##: ##:::: ##: ########::::. #######::::. ###:::: ########: ##:::. "
        "##:\033[0m\n");
    printf(
        "\033[31m:......::::..:::::..::..:::::..::........::::::.......::::::...:::::........::..:::::..::"
        "\033[0m\n");
}
