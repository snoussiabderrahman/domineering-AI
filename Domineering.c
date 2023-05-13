#include<stdio.h>
#include<string.h>
#define N 8
#define Bot '1'
#define Player '0'
#define SAVE '2'
#define INFINITY 9999
char mat[N][N]={{' ',' ',' ',' ',' ',' ',' ',' '},
                {' ',' ',' ',' ',' ',' ',' ',' '},
                {' ',' ',' ',' ',' ',' ',' ',' '},
                {' ',' ',' ',' ',' ',' ',' ',' '},
                {' ',' ',' ',' ',' ',' ',' ',' '},
                {' ',' ',' ',' ',' ',' ',' ',' '},
                {' ',' ',' ',' ',' ',' ',' ',' '},
                {' ',' ',' ',' ',' ',' ',' ',' '}};

void print_mat()
{
    printf("    0   1   2   3   4   5   6   7 \n");
    printf("  ---------------------------------\n");
    for(int i=0;i<N;i++)
    {
        printf("%d ",i);
        for(int j=0;j<N;j++)
        printf("| %c ",mat[i][j]);
        printf("|\n");
        printf("  ---------------------------------\n");
    }
}

int check_game()
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N-1;j++)
        {
            if(mat[i][j] == ' ' && mat[i][j+1] == ' ')
            return 0;
        }
    }
    for(int j=0;j<N;j++)
    {
        for(int i=0;i<N-1;i++)
        {
            if(mat[i][j] == ' ' && mat[i+1][j] == ' ')
            return 0;
        }
    }
    return 1;
}

int number_place_save(char ply)
{
    int number_place=0,bol=1;
    if(ply == Player)
    {
        for(int j=0;j<N;j++)
        {
            for(int i=0;i<N-1;i++)
            {
                if(mat[i][j] == ' ' && mat[i+1][j] == ' ')
                {
                    if(j-1 != -1 && (mat[i][j-1] != Player || mat[i+1][j-1] != Player))
                     bol=0;
                    if(j+1 != 8 && (mat[i][j+1] != Player || mat[i+1][j+1] != Player))
                      bol=0;
                    if(bol)
                    {
                        number_place++;
                        i++;
                    }
                    else bol=1;
                }
            }
        }
        return number_place;
    }
    if(ply == Bot)
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N-1;j++)
            {
                if(mat[i][j] == ' ' && mat[i][j+1] == ' ')
                {
                    if(i-1 != -1 && (mat[i-1][j] != Bot || mat[i-1][j+1] != Bot))
                      bol=0;
                    if(i+1 != 8 && (mat[i+1][j] != Bot || mat[i+1][j+1] != Bot))
                      bol=0;
                    if(bol)
                    {
                        number_place++;
                        j++;
                    }
                    else bol=1;
                }
            }
        }
        return number_place;
    }
}

int test_place(char ply,int i,int j)
{
    if(ply == Bot)
    {
        if(i-1 != -1 && (mat[i-1][j] != Bot || mat[i-1][j+1] != Bot))
          return 0;
        if(i+1 != 8 && (mat[i+1][j] != Bot || mat[i+1][j+1] != Bot))
          return 0;
        return 1;
    }
    if(ply == Player)
    {
        if(j-1 != -1 && (mat[i][j-1] != Player || mat[i+1][j-1] != Player))
          return 0;
        if(j+1 != 8 && (mat[i][j+1] != Player || mat[i+1][j+1] != Player))
          return 0;
        return 1;
    }
}

void stocker_place_save(char ply)
{
    if(ply == Bot)
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N-1;j++)
            {
                if(mat[i][j] == ' ' && mat[i][j+1] == ' ' && test_place(Bot,i,j))
                {
                    mat[i][j] = SAVE;
                    mat[i][j+1] = SAVE;
                }
            }
        }
    }
    else{
        for(int j=0;j<N;j++)
        {
            for(int i=0;i<N-1;i++)
            {
                if(mat[i][j] == ' ' && mat[i+1][j] == ' ' && test_place(Player,i,j))
                {
                    mat[i][j] = SAVE;
                    mat[i+1][j] = SAVE;
                }
            }
        }
    }
}

void delete_place_save()
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(mat[i][j] == SAVE)
            mat[i][j] = ' ';
        }
    }
}

int number_place_non_save(char ply)
{
    int nb=0;
    if(ply == Bot)
    {
        stocker_place_save(Bot);
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N-1;j++)
            {
                if(mat[i][j] == ' ' && mat[i][j+1] == ' ')
                nb++;
            }
        }
        delete_place_save();
        return nb;
    }
    else{
        stocker_place_save(Player);
        for(int j=0;j<N;j++)
        {
            for(int i=0;i<N-1;i++)
            {
                if(mat[i][j] == ' ' && mat[i+1][j] == ' ')
                nb++;
            }
        }
        delete_place_save();
        return nb;
    }
}

int number_play(char ply)
{
    int score=0;
    if(ply == Bot)
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N-1;j++)
            {
                if(mat[i][j] == Bot && mat[i][j+1] == Bot)
                {
                    score++;
                    j++;
                }
            }
        }
        return score;
    }
    if(ply == Player)
    {
        for(int j=0;j<N;j++)
        {
            for(int i=0;i<N-1;i++)
            {
                if(mat[i][j] == Player && mat[i+1][j] == Player)
                {
                    score++;
                    i++;
                }
            }
        }
        return score;
    }
}

int best_pos(char ply)
{
    int cij,nb,nb_save,nb_max;
    if(ply == Bot)
    {
        nb = number_place_save(Bot);
        nb_max = nb;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N-1;j++)
            {
                stocker_place_save(Bot);
                if(mat[i][j] == ' ' && mat[i][j+1] == ' ')
                {
                    mat[i][j] == Bot;
                    mat[i][j+1] == Bot;
                    nb_save = number_place_save(Bot);
                    mat[i][j] == ' ';
                    mat[i][j+1] == ' ';
                    if(nb_save > nb_max)
                    {
                        nb_max = nb_save;
                        cij=i*8+j;
                    }
                }
                delete_place_save();
            }
        }
        if(nb_max != nb)
        return cij;
        else return -1;

    }
    else{
        nb =number_place_save(Player);
        nb_max =nb;
        for(int j=0;j<N;j++)
        {
            for(int i=0;i<N-1;i++)
            {
                stocker_place_save(Player);
                if(mat[i][j] == ' ' && mat[i+1][j] == ' ')
                {
                    mat[i][j] == Player;
                    mat[i+1][j] == Player;
                    nb_save = number_place_save(Player);
                    mat[i][j] == ' ';
                    mat[i][j+1] == ' ';
                    if(nb_save > nb_max)
                    {
                        nb_max = nb_save;
                        cij=i*8+j;
                    }
                }
                delete_place_save();
            }
        }
        if(nb_max != nb)
        return cij;
        else return -1;
    }
}

int minimax(int min_max)
{
    int bestScore,score,pos;
    int a,b,c,d;

    if(min_max)
    {
        bestScore = -INFINITY;
        pos = best_pos(Bot);
        if(pos != -1)
        {
            mat[pos/8][pos%8] = Bot;
            mat[pos/8][pos%8+1] = Bot;
            score = minimax(0);
            mat[pos/8][pos%8] = ' ';
            mat[pos/8][pos%8+1] = ' ';
            if(score > bestScore)
            bestScore = score;
            return bestScore;
        }
        else{
            a= number_place_save(Bot);
            b= number_play(Bot);
            c=number_place_save(Player);
            d= number_play(Player);
            return (a+b)-(c+d);
        }
    }
    else
    {
        bestScore = INFINITY;
        pos = best_pos(Player);
        if(pos != -1)
        {
            mat[pos/8][pos%8] = Player;
            mat[pos/8+1][pos%8] = Player;
            score = minimax(1);
            mat[pos/8][pos%8] = ' ';
            mat[pos/8+1][pos%8] = ' ';
            if(score < bestScore)
            bestScore = score;
            return bestScore;
        }
        else{
            a= number_place_save(Bot);
            b= number_play(Bot);
            c=number_place_save(Player);
            d= number_play(Player);
            return (a+b)-(c+d);
        }
    }
}

int best_Move()
{
    int bestMove,bestScore = -INFINITY,score;
    int i,j,pos;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N-1;j++)
        {
            stocker_place_save(Bot);
            if(mat[i][j] == ' ' && mat[i][j+1] ==' ')
            {
                mat[i][j] = Bot;
                mat[i][j+1] = Bot;
                score = minimax(0);
                mat[i][j] = ' ';
                mat[i][j+1] = ' ';
                if(score > bestScore)
                {
                    bestScore = score;
                    bestMove = i*8+j;
                }
            }
            delete_place_save();
        }
    }
    return bestMove;
}

void play()
{
    int i,j;
    printf(" show i,j :");
    scanf("%d%d",&i,&j);
    mat[i][j] = Player;
    mat[i+1][j] = Player;
    print_mat();
}

int charge_BOT()
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N-1;j++)
        {
            if(mat[i][j] == ' ' && mat[i][j+1] == ' ')
            return i*8+j;
        }
    }
}

int main()
{
    int i,j,c,b,aij;
    //mat[1][0] = Bot;
    //mat[1][1] = Bot;
    print_mat();
    while(!check_game())
    {
        play();
        b=1;
        if(number_place_non_save(Bot) != 0)
        {
            c = best_Move();
            mat[c/8][c%8] = Bot;
            mat[c/8][c%8+1] = Bot;
            b=1;
        }
        else{
            aij = charge_BOT();
            printf("\n %d \n",aij);
            mat[aij/8][aij%8] = Bot;
            mat[aij/8][aij%8+1] = Bot;
            b=1;
        }
        print_mat();
    }
    if(b)
    printf("\n The bot beat you");
    else 
    printf("\n the Player beat");
    return 0;
}
