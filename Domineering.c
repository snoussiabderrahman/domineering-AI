#include<stdio.h>
#include<string.h>
#define N 8
#define Bot '1'
#define Player '0'
#define SAVE '2'
#define INFINITY 99999



char mat[N][N]={{' ',' ',' ',' ',' ',' ',' ',' '},
                {' ',' ',' ',' ',' ',' ',' ',' '},
                {' ',' ',' ',' ',' ',' ',' ',' '},
                {' ',' ',' ',' ',' ',' ',' ',' '},
                {' ',' ',' ',' ',' ',' ',' ',' '},
                {' ',' ',' ',' ',' ',' ',' ',' '},
                {' ',' ',' ',' ',' ',' ',' ',' '},
                {' ',' ',' ',' ',' ',' ',' ',' '}};

void print_mat()  // print the matrix
{
    system("cls");
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

// check if the game is over
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

//  count the number of place save
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

int test_place(char ply,int i,int j)  // test if the place is stored
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

void stock_place_save(char ply)  // store the place save 
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

void delete_place_save()  // delete the place save
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

int number_place_non_save(char ply)   // count the number of place non save
{
    int nb=0;
    if(ply == Bot)
    {
        stock_place_save(Bot);
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
        stock_place_save(Player);
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

int number_play(char ply)  // count the number of play or score of the player
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

int best_pos(char ply)   // find the best position to play
{
    int cij,number_place_stock,nb_save,nb_max;

    if(ply == Bot)
    {
        number_place_stock = number_place_save(Bot);
        nb_max = number_place_stock;
        print_mat( );
        return 0;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N-1;j++)
            {
                stock_place_save(Bot);
                if(mat[i][j] == ' ' && mat[i][j+1] == ' ')
                {
                    mat[i][j] = Bot;
                    mat[i][j+1] = Bot;
                    nb_save = number_place_save(Bot);
                    mat[i][j] = ' ';
                    mat[i][j+1] = ' ';
                    if(nb_save > nb_max)
                    {
                        nb_max = nb_save;
                        cij = i*8+j;
                    }
                }
                delete_place_save();
            }
        }
        if(nb_max != number_place_stock)
        return cij;
        else return -1;

    }
    else{
        number_place_stock =number_place_save(Player);
        nb_max = number_place_stock;
        
        for(int j=0;j<N;j++)
        {
            for(int i=0;i<N-1;i++)
            {
                stock_place_save(Player);
                
                if(mat[i][j] == ' ' && mat[i+1][j] == ' ')
                {
                    mat[i][j] = Player;
                    mat[i+1][j] = Player;
                    nb_save = number_place_save(Player);
                    mat[i][j] = ' ';
                    mat[i+1][j] = ' ';
                    if(nb_save > nb_max)
                    {
                        nb_max = nb_save;
                        cij=i*8+j;
                    }
                }
                delete_place_save();
            }
        }
        if(nb_max != number_place_stock)
        return cij;
        else return -1;
    }
}

int minimax(int min_max)  // min max algorithm
{
    int bestScore,score,pos,score_bot,score_player;

    if(check_game())
    {
        score_bot = number_place_save(Bot) + number_play(Bot);
        score_player = number_place_save(Player) + number_play(Player);
        return score_bot - score_player;
    }
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
            score_bot = number_place_save(Bot) + number_play(Bot);
            score_player = number_place_save(Player) + number_play(Player);
            return score_bot - score_player;
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
            score_bot = number_place_save(Bot) + number_play(Bot);
            score_player = number_place_save(Player) + number_play(Player);
            return score_bot - score_player;
        }
    }
}

int best_play()  // find the best play
{
    int bestMove,bestScore = -INFINITY,score;
    int i,j,pos;
    
    for(i=0;i<N;i++)
    {
        for(j=0;j<N-1;j++)
        {
            stock_place_save(Bot);
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

void play() // the player play
{
    int i,j;
    printf(" show i,j :");
    scanf("%d%d",&i,&j);
    mat[i][j] = Player;
    mat[i+1][j] = Player;
    //print_mat();
}

int charge_BOT()  // find aij the position save
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N-1;j++)
        {
            if(mat[i][j] == ' ' && mat[i][j+1] == ' ')
            return i*8+j;
        }
    }
    return -1;
}

int main()
{
    int i,j,best_position,b=1,aij;
    mat[1][0] = Bot;
    mat[1][1] = Bot;
    print_mat();
    while(!check_game())
    {
        play();
        if(number_place_non_save(Bot) != 0)
        {
            //find best position and play it 
            best_position = best_play();
            mat[best_position/8][best_position%8] = Bot;
            mat[best_position/8][best_position%8+1] = Bot;
        }
        else{
            //find aij and position save and play it
            aij = charge_BOT();
            if (aij != -1)
            {
                mat[aij/8][aij%8] = Bot;
                mat[aij/8][aij%8+1] = Bot;
            }else{      //the player win
                b=0;
                break;
            }
        }
        print_mat();
    }
    if(b)
    printf("\n The Bot beat you");
    else 
    printf("\n The Player beat");
    return 0;
}
