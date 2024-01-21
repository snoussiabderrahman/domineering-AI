#include <stdio.h>
#include <stdlib.h>

#define DEPTH 5
#define INFINITY __INT_MAX__
#define Bot 'B'
#define Player 'P'

char board[8][8];

int N = 8;

typedef enum {
    false,
    true
} bool;

void draw_game() {
    system("cls");
    printf("\n \t    Domineering \n\n");
    printf("    1   2   3   4   5   6   7   8 \n");
    printf("  ---------------------------------\n");
    for(int i = 0;i < N;i++)
    {
        printf("%d ",i+1);
        for(int j = 0;j < N;j++)
        printf("| %c ",board[i][j]);
        printf("|\n");
        printf("  ---------------------------------\n");
    }
}

bool place_item(int row, int col, char ply, bool silent) {
    int col_m = 0;
    int row_m = 0;
    if (ply == Player) {
        row_m = 1;
    } else {
        col_m = 1;
    }

    if (row + row_m >= N || col + col_m >= N || board[row + row_m][col] != ' ' || board[row][col + col_m] != ' ') {
        if (!silent)
            printf("Please check your input and try again.\n");
        return false;
    } else {
        board[row][col] = ply;
        board[row + row_m][col + col_m] = ply;
    }

    return true;
}

void remove_item(int row, int col, char ply) {
    if (ply == Player) {
        board[row][col] = ' ';
        board[row + 1][col] = ' ';
    } else {
        board[row][col] = ' ';
        board[row][col + 1] = ' ';
    }
}

int get_possibilities(char ply) {
    int sum = 0;
    int row_m = 0;
    int col_m = 0;
    if (ply == Player) {
        row_m = 1;
    } else {
        col_m = 1;
    }

    for (int i = 0; i < N - row_m; i++) {
        for (int j = 0; j < N - col_m; j++) {
            if (board[i][j] == ' ' && board[i + row_m][j + col_m] == ' ') {
                sum += 1;
            }
        }
    }

    return sum;
}

int alphabeta(int recursivity, char ply, int *ri, int *rj, int alpha, int beta) {
    if (recursivity == 0)
        return get_possibilities(ply) - ((ply == Bot) ? get_possibilities(Player) : get_possibilities(Bot));

    int fi = 0;
    int fj = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (place_item(i, j, ply, true)) {
                int e = -alphabeta(recursivity - 1, ((ply == Bot) ? Player : Bot), &fi, &fj, -beta, -alpha);
                remove_item(i, j, ply);
                if (e > alpha) {
                    alpha = e;
                    *ri = i;
                    *rj = j;
                    if (alpha >= beta) {
                        return beta;
                    }
                }
            }
        }
    }
    return alpha;
}

void best_move(int recursivity, char ply) {
    int i = 0;
    int j = 0;
    alphabeta(DEPTH, Bot, &i, &j, -INFINITY, INFINITY);
    place_item(i, j, Bot, true);
}

int main() {

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = ' ';
        }
    }

    int  row = -1,col = -1;
    bool validated = false;

    while (row != 0 || !validated) {
        draw_game();
        printf("Player turn...\n");

        if (get_possibilities(Player) == 0) {
            printf("You lost.\n");
            break;
        }

        scanf("%d", &row);

        if (row > 0 && row <= N) {
            scanf("%d", &col);

            if (col > 0 && col <= N) {
                validated = place_item(row - 1, col - 1, Player, false);

                if (validated) {
                    if (get_possibilities(Bot) == 0) {
                        printf("You win.\n");
                        break;
                    }
                    // using alpha-beta pruning
                    best_move(DEPTH, Bot);
                }
            }else printf("Please check your input and try again.\n");
        }else printf("Please check your input and try again.\n");
    }

    return 0;
}
