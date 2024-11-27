#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h>
// atoi, srandom, random
// add here other necessary include directives

#define DEAD  '.'
#define ALIVE 'o'
#define DYING '+'

#define BLINKER 0
#define TOAD 1
#define BEACON 2
#define PULSAR 3
#define PENTADECATHLON 4
#define RANDOM 5

#define NLINES_RANDOM 50
#define NCOLUMNS_RANDOM 200

unsigned int GLOBAL_nlines, GLOBAL_ncolumns;
char *GLOBAL_grid_A=NULL, *GLOBAL_grid_B=NULL;

// -1 for INFINITE
//#define NITERS -1
#define NITERS 2000

//////////////////////////////////////////////////////////////////////
#include <termcap.h>
void clearScreen() {
 char buf[1024]; char *str;

 tgetent(buf, getenv("TERM"));
 str = tgetstr("cl", NULL);
 fputs(str, stdout);
}

//////////////////////////////////////////////////////////////////////
void gridShow(char *grid)
{
	
	for(int i =0; i< GLOBAL_nlines; i++){
		for(int j = 0; j < GLOBAL_ncolumns; j++){
			char cell = grid[i * GLOBAL_ncolumns + j];
			switch(cell){
				case ALIVE:
				 putchar(ALIVE); putchar(' ');
				 break;
				case DEAD:
				 putchar(DEAD); putchar(' ');
				 break;
				case DYING:
				 putchar(DYING); putchar(' ');
				 break;
				default:
				break;
			}
		}
		putchar('\n');
	}
 // shows the grid in the screen, one grid line per screen line;
 // do not forget to call clearScreen before calling gridShow
}

////////////////////////////////////////////////////////////////////
void defineDimensions(int pattern)                                                   //1
{ 
	switch(pattern){
		case BLINKER: 
			GLOBAL_nlines = 5;
			GLOBAL_ncolumns = 5;
			break;
		case TOAD:
			GLOBAL_nlines = 6;
			GLOBAL_ncolumns = 6;
			break;
		case BEACON:
			GLOBAL_nlines = 6;
			GLOBAL_ncolumns = 6;
			break;
		case PULSAR:
			GLOBAL_nlines = 17;
			GLOBAL_ncolumns = 17;
			break;
		case PENTADECATHLON:
			GLOBAL_nlines = 18;
			GLOBAL_ncolumns = 11;
			break;
		case RANDOM:
			GLOBAL_nlines = NLINES_RANDOM;
			GLOBAL_ncolumns = NCOLUMNS_RANDOM;
			break;
		default:
		break;
	}
	
 // define number of lines (GLOBAL_nlines) and columns (GLOBAL_coluns)
 // of the grids, depending on the pattern (BLINKER, TOAD, ..., RANDOM);
 // for the specific number of lines and columns of each pattern see 
 // https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life ;
 // if pattern is RANDOM you must use NLINES_RANDOM and NCOLUMNS_RANDOM
}

////////////////////////////////////////////////////////////////////
void gridInit(char *grid, int pattern)                                                 //1
{
	for (int i = 0; i < GLOBAL_nlines * GLOBAL_ncolumns; i++) {
    grid[i] = DEAD;
	}

	switch (pattern) {
    case BLINKER:
        grid[11] = ALIVE;
        grid[12] = ALIVE;
        grid[13] = ALIVE;
        break;

    case TOAD:
        grid[14] = ALIVE;
        grid[15] = ALIVE;
        grid[16] = ALIVE;
        grid[19] = ALIVE;
        grid[20] = ALIVE;
        grid[21] = ALIVE;
        break;

    case BEACON:
        grid[7] = ALIVE;
        grid[8] = ALIVE;
        grid[13] = ALIVE;
        grid[22] = ALIVE;
        grid[27] = ALIVE;
        grid[28] = ALIVE;
        break;

    case PULSAR:
	grid[22] = ALIVE;
	grid[28] = ALIVE;
	grid[39] = ALIVE;
	grid[45] = ALIVE;
	grid[56] = ALIVE;
	grid[57] = ALIVE;
	grid[61] = ALIVE;
	grid[62] = ALIVE;
	grid[86] = ALIVE;
	grid[87] = ALIVE;
	grid[88] = ALIVE;
	grid[91] = ALIVE;
	grid[92] = ALIVE;
	grid[94] = ALIVE;
	grid[95] = ALIVE;
	grid[98] = ALIVE;
	grid[99] = ALIVE;
	grid[100] = ALIVE;
	grid[105] = ALIVE;
	grid[107] = ALIVE;
	grid[109] = ALIVE;
	grid[111] = ALIVE;
	grid[113] = ALIVE;
	grid[115] = ALIVE;
	grid[124] = ALIVE;
	grid[125] = ALIVE;
	grid[129] = ALIVE;
	grid[130] = ALIVE;
	grid[158] = ALIVE;
	grid[159] = ALIVE;
	grid[163] = ALIVE;
	grid[164] = ALIVE;
	grid[173] = ALIVE;
	grid[175] = ALIVE;
	grid[177] = ALIVE;
	grid[179] = ALIVE;
	grid[181] = ALIVE;
	grid[183] = ALIVE;
	grid[188] = ALIVE;
	grid[189] = ALIVE;
	grid[190] = ALIVE;
	grid[193] = ALIVE;
	grid[194] = ALIVE;
	grid[196] = ALIVE;
	grid[197] = ALIVE;
	grid[200] = ALIVE;
	grid[201] = ALIVE;
	grid[202] = ALIVE;
	grid[226] = ALIVE;
	grid[227] = ALIVE;
	grid[231] = ALIVE;
	grid[232] = ALIVE;
	grid[243] = ALIVE;
	grid[249] = ALIVE;
	grid[260] = ALIVE;
	grid[266] = ALIVE;
        break;
	case PENTADECATHLON:
	grid[37] = ALIVE;
    grid[38] = ALIVE;
    grid[39] = ALIVE;
    grid[49] = ALIVE;
    grid[60] = ALIVE;
    grid[70] = ALIVE;
    grid[71] = ALIVE;
    grid[72] = ALIVE;
    grid[92] = ALIVE;
    grid[93] = ALIVE;
    grid[94] = ALIVE;
    grid[103] = ALIVE;
    grid[104] = ALIVE;
    grid[105] = ALIVE;
    grid[125] = ALIVE;
    grid[126] = ALIVE;
    grid[127] = ALIVE;
    grid[137] = ALIVE;
    grid[148] = ALIVE;
    grid[158] = ALIVE;
    grid[159] = ALIVE;
    grid[160] = ALIVE;
		break;
    case RANDOM:
		srandom(time(NULL)); //null pq a time nao precisa de parametros
		for(int i =0; i < GLOBAL_ncolumns * GLOBAL_nlines; i++){
			if(random()%10 == 0){
				grid[i]=ALIVE;
			}
		}
		break;
    default:

        break;
}
 // initializes the starting grid depending on pattern (BLINKER,...);
 // for the initial state (dead/alive) of each cell see 
 // https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life ;
 // if pattern is RANDOM you must define the state of the grid cells
 // in a random way, ensuring only a fraction of 10% are alive cells
}

////////////////////////////////////////////////////////////////////////
void gridEvolve(char *current, char *next)
{
	/*1. Any live cell goes to dying state in the next generation;
	2. Any dying cell with two or three live or dying neighbours survives;
	3. Any dead cell with three live or dying neighbours becomes a live cell;
	4. All other dying cells die in the next generation. Similarly, all other dead cells stay dead.
	5. In the initial state a cell is live or dead, not dying.*/
	
	for(int line = 0; line < GLOBAL_nlines; line++){
			for(int column = 0; column < GLOBAL_ncolumns; column++){
				//regras do jogo
				if(current[line * GLOBAL_ncolumns + column] == ALIVE){
					next[line * GLOBAL_ncolumns + column] = DYING;
				}else if(current[line * GLOBAL_ncolumns + column] == DYING){
					int vizinhosAliveOrDying = 0;
					for(int k = line - 1; k <= line + 1; k++){
						for(int l = column - 1; l <= column + 1; l++){
							if(k < 0 || k >= GLOBAL_nlines || l < 0 || l >= GLOBAL_ncolumns || (k == line && l == column)){
								continue;
							}
							if(current[k * GLOBAL_ncolumns + l] == ALIVE || current[k * GLOBAL_ncolumns + l] == DYING){
								vizinhosAliveOrDying++;
							}
						}
					}
					if(vizinhosAliveOrDying == 2 || vizinhosAliveOrDying == 3){
						next[line * GLOBAL_ncolumns + column] = ALIVE;
					}else{
						next[line * GLOBAL_ncolumns + column] = DEAD;
					}
				}else if(current[line * GLOBAL_ncolumns + column] == DEAD){
					int vizinhosAliveOrDying = 0;
					for(int k = line - 1; k <= line + 1; k++){
						for(int l = column - 1; l <= column + 1; l++){
							if(k < 0 || k >= GLOBAL_nlines || l < 0 || l >= GLOBAL_ncolumns || (k == line && l == column)){
								continue;
							}
							if(current[k * GLOBAL_ncolumns + l] == ALIVE || current[k * GLOBAL_ncolumns + l] == DYING){
								vizinhosAliveOrDying++;
							}
						}
					}
					if(vizinhosAliveOrDying == 3){
						next[line * GLOBAL_ncolumns + column] = ALIVE;
					}else{
						next[line * GLOBAL_ncolumns + column] = DEAD;
					}
			}
	}
 // generates the next grid depending on the content of the current grid,
 // by applying the game of life rules to each cell of the current grid
	}
}
//////////////////////////////////////////////////////////////////////

int gridCompare(char *gridA, char *gridB)
{
	int equal=0;
	for(int i = 0; i < GLOBAL_ncolumns * GLOBAL_nlines; i++){
		if(gridA[i] != gridB[i]){
			equal = 1;
			break;
		}
	}
	return equal;
}


//////////////////////////////////////////////////////////////////////
int main(int argc, char **argv){

	//argv é um array de strings que contém os argumentos passados para o programa na linha de comando.
	//é uma função que converte uma string em um número inteiro
	
    int pattern = atoi(argv[1]);   
	
	//verificacao que o numero passado em arg[1] corresponde a um dos padrões,
    if (pattern < 0 || pattern > 5)
    {
        printf("Padrão inválido. Saindo do programa.\n");
        exit(1);
    }
    
    //definimos a dimensão da grid relacionado ao padrão inserido no terminal
	defineDimensions(pattern);
	
	
	//alocamos memoria para armazenar as grids 
	//a quantidade total de bytes necessaria para armazenar a grid, corresponde ao numero de de colunas pelo numero de linhas
    GLOBAL_grid_A = (char *)malloc(GLOBAL_nlines * GLOBAL_ncolumns * sizeof(char));
    GLOBAL_grid_B = (char *)malloc(GLOBAL_nlines * GLOBAL_ncolumns * sizeof(char));

	//criamos a nossa grid, com o respetivo padrao
    gridInit(GLOBAL_grid_A, pattern);
	
	//iniciamos o numero de iteracoes a 0 para servir como contador
    int niters = 0;
    while (niters <= NITERS && gridCompare(GLOBAL_grid_A, GLOBAL_grid_B))
    {

		clearScreen();
		gridShow(GLOBAL_grid_A);
        gridEvolve(GLOBAL_grid_A, GLOBAL_grid_B);
        if(gridCompare(GLOBAL_grid_A, GLOBAL_grid_B)){
			char* temp = GLOBAL_grid_A;
			GLOBAL_grid_A = GLOBAL_grid_B;
			GLOBAL_grid_B = temp;
			niters++;
		}else break;
    }
	if(niters-1 == NITERS){
		printf("finished all iterations\n");
	}
    free(GLOBAL_grid_A);
    free(GLOBAL_grid_B);

    return(0);
}



