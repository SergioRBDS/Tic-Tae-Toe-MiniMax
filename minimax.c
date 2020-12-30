#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct state{ // state of game
    int **tab;
    int tam;
    int seq;
    int profMax;
    int score;
};typedef struct state State;

State* alocaState(int tam, int seq, int prof){  // create state 
    
    State* new = (State*) malloc (sizeof(State));
    if(new == NULL){ 
        printf("memory error\n"); 
        exit(1);
    }
    
    new->tam = tam;
    new->seq = seq;
    new->profMax = prof;
    new->score = 0;
    new->tab = (int**) malloc (tam*sizeof(int*));
    if(new->tab == NULL){ 
        printf("memory error\n");
        exit(1);
    }
    
    for(int i=0;i<tam;i++){
        new->tab[i] = (int*) calloc (tam, sizeof(int));
        if(new->tab[i] == NULL){ 
            printf("memory error\n"); 
            exit(1);
        }
        
    }
    return new;
}

State* copyState(State *p){
    State *q = alocaState(p->tam, p->seq, p->profMax);
    
    for(int i=0;i<p->tam;i++)
        for(int j=0;j<p->tam;j++)
            q->tab[i][j] = p->tab[i][j];
        
    return q;
}

void desaloc(State *p){
    for(int i=0;i<p->tam;i++)
        free(p->tab[i]);
    free(p->tab);
    free(p);
}

int finishGame(State* p){
    
    //player 1
    //horizontal
    if(p->tab[0][0]==1 &&p->tab[0][1]==1 &&p->tab[0][2]==1) return 1;
    if(p->tab[1][0]==1 &&p->tab[1][1]==1 &&p->tab[1][2]==1) return 1;
    if(p->tab[2][0]==1 &&p->tab[2][1]==1 &&p->tab[2][2]==1) return 1;
    //vertical
    if(p->tab[0][0]==1 &&p->tab[1][0]==1 &&p->tab[2][0]==1) return 1;
    if(p->tab[0][1]==1 &&p->tab[1][1]==1 &&p->tab[2][1]==1) return 1;
    if(p->tab[0][2]==1 &&p->tab[1][2]==1 &&p->tab[2][2]==1) return 1;
    //diagonal
    if(p->tab[0][0]==1 &&p->tab[1][1]==1 &&p->tab[2][2]==1) return 1;
    if(p->tab[2][0]==1 &&p->tab[1][1]==1 &&p->tab[0][2]==1) return 1;
    
    //player -1
    //horizontal
    if(p->tab[0][0]==-1 &&p->tab[0][1]==-1 &&p->tab[0][2]==-1) return -1;
    if(p->tab[1][0]==-1 &&p->tab[1][1]==-1 &&p->tab[1][2]==-1) return -1;
    if(p->tab[2][0]==-1 &&p->tab[2][1]==-1 &&p->tab[2][2]==-1) return -1;    
    //vertical
    if(p->tab[0][0]==-1 &&p->tab[1][0]==-1 &&p->tab[2][0]==-1) return -1;
    if(p->tab[0][1]==-1 &&p->tab[1][1]==-1 &&p->tab[2][1]==-1) return -1;
    if(p->tab[0][2]==-1 &&p->tab[1][2]==-1 &&p->tab[2][2]==-1) return -1;
    //diagonal
    if(p->tab[0][0]==-1 &&p->tab[1][1]==-1 &&p->tab[2][2]==-1) return -1;
    if(p->tab[2][0]==-1 &&p->tab[1][1]==-1 &&p->tab[0][2]==-1) return -1;
    
    //other case
    return 0;
}

void printTab(State* p){
    for(int i=0;i<p->tam;i++){
        for(int j=0;j<p->tam;j++){
            if(p->tab[i][j]==-1)
                printf("  %d   ", p->tab[i][j]);
            else printf("   %d   ", p->tab[i][j]);
        }
        printf("\n");
    }
}

int tabFull(State *p){
    if(p->tab[0][0]!=0 &&p->tab[0][1]!=0 &&p->tab[0][2]!=0 && p->tab[1][0]!=0 &&p->tab[1][1]!=0 &&p->tab[1][2]!=0 && p->tab[2][0]!=0 &&p->tab[2][1]!=0 &&p->tab[2][2]!=0)
        return 1;
}

State* jogada(State* p, int jogador, int profundidade, int x, int y){
    
    if(x != -1 && y != -1){
        p->tab[x][y] = jogador;
        jogador = jogador*-1;
    }
    
    int result = finishGame(p);
    //printf("opabao %d %d\n", profundidade, jogador);
    if(result == 1){ p->score = 1; return p;}
    if(result == -1){ p->score = -1; return p;}
    if(profundidade == p->profMax){ p->score = 0;return p;}
    
    State* current;
    State* best;
    int max = -2;
    int min = 2;
    int bx, by;
    
    for(int i=0;i<p->tam;i++){
        for(int j=0;j<p->tam;j++){
            if(p->tab[i][j] == 0){
                current = jogada(copyState(p), jogador, profundidade+1, i, j);
                if(jogador == 1){
                    if(current->score>max){
                        best = current;
                        max = current->score;
                        if(x==-1 && y==-1){
                            bx = i;
                            by = j;
                        }
                    }
                    else desaloc(current);
                }
                else{
                    if(current->score<min){
                        best = current;
                        min = current->score;
                        if(x==-1 && y==-1){
                            bx = i;
                            by = j;
                        }
                    }
                    else desaloc(current);
                }
            }
        }
        
    }
    if(x==-1 && y==-1){
        p->tab[bx][by] = jogador;
        return p;
    }
    //best->score=0;
    return best;
}

int validPlay(State *p, int x, int y){
    
    if(x<0 || x>2 || y<0 || y>2){ printf("Invalid Play, try again\n"); return 1;}
    
    if(p->tab[x][y] != 0){ printf("Invalid Play, try again\n"); return 1;}
    
    return 0;
}

int startGame(State *inicial){
    int x, y;
    
    srand(time(NULL));
    int randNumber = rand() % 2;
    if(randNumber == 0){ inicial = jogada(inicial, -1, 1, -1, -1); printf("Current: \n"); printTab(inicial); }
        
        
    while(finishGame(inicial)!=1 && finishGame(inicial) != -1){
        printf("Insert Your Move x y\n");
        
        do{
        scanf("%d %d", &x, &y);
        }while(validPlay(inicial, x, y));
        inicial->tab[x][y] = 1;
        if(tabFull(inicial)) break;
        inicial = jogada(inicial, -1, 1, -1, -1);
        if(tabFull(inicial)) break;
        printf("Current: \n");
        printTab(inicial);
    }
    
    return finishGame(inicial);
}

int main(){
    State* inicial = alocaState(3, 3, 9);
    printf("Start: \n");
    printTab(inicial);
    
    int result = startGame(inicial);
    if(result == 1) printf("You Win\n");
    if(result == -1) printf("You Lose\n");
    if(result == 0) printf("Tie\n");
}
