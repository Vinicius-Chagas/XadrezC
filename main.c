#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tab{
	char tipo;
	char cor;
} tab;

typedef struct pos{
	int ini[2];
	int fin[2];
} pos;

void initTabuleiro(tab tabuleiro[8][8]);
bool vazio(tab tabuleiro[8][8], pos p);
void move(tab tabuleiro[8][8], pos p);
bool inimigo(tab tabuleiro[8][8], pos p);
void peao(tab tabuleiro[8][8], pos p);
void imprimirTabuleiro(tab tabuleiro[8][8]);
void cavalo(tab tabuleiro[8][8], pos p);
void torre(tab tabuleiro[8][8], pos p);
void reinha(tab tabuleiro[8][8], pos p);
void rei(tab tabuleiro[8][8], pos p);
void jogada(tab tabuleiro[8][8]);


int main()
{
	tab tabuleiro[8][8];
	initTabuleiro(tabuleiro);
	imprimirTabuleiro(tabuleiro);
	jogada(tabuleiro);


	system("pause");
	return 0;
}

void initTabuleiro(tab tabuleiro[8][8])
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(i==j || (i==0 && j==7) || (i==7 && j==0)) // Coloca as torres no tabuleiro
				tabuleiro[i][j].tipo = 'T';
			if((i==0 && j==1) || (i==0 && j==6) || (i==7 && j==1) || (i==7 && j==6)) // COloca os cavalos
				tabuleiro[i][j].tipo = 'C';
			if((i==0 && j==2) || (i==0 && j==5) || (i==7 && j==2) || (i==7 && j==5)) // Coloca os bispos
				tabuleiro[i][j].tipo = 'B';
			if((i==0 && j==4) || (i==7 && j==3)) // Posiciona os reis
				tabuleiro[i][j].tipo = 'K';
			if((i==0 && j==3) || (i==7 && j==4)) // Posiciona a rainha
				tabuleiro[i][j].tipo = 'Q';
			if(i==1 || i==6) // Posiciona peões
				tabuleiro[i][j].tipo = 'P';
			if(i>1 && i<6)
				tabuleiro[i][j].tipo = '-';

			if(i<2)
				tabuleiro[i][j].cor = 'B';
			else if(i>5)
				tabuleiro[i][j].cor = 'P';
		}
	}
}

bool vazio(tab tabuleiro[8][8], pos p)
{
	if(tabuleiro[p.ini[0]][p.ini[1]].tipo == '-')
		return true;
	else
		return false;
}

bool inimigo(tab tabuleiro[8][8], pos p)
{
	if(tabuleiro[p.ini[0]][p.ini[1]].cor == tabuleiro[p.fin[0]][p.fin[1]].cor)
		return false;
	else
		return true;
}

void move(tab tabuleiro[8][8], pos p)
{
	tabuleiro[p.fin[0]][p.fin[0]] = tabuleiro[p.ini[0]][p.ini[0]]; // Coloca a peça da posição inicial na posição final
	tabuleiro[p.ini[0]][p.ini[0]] = (tab) {'-','N'}; // Coloca um espaço vazio na posição inicial

}

void peao(tab tabuleiro[8][8], pos p)
{
	if(vazio(tabuleiro, p) && p.fin[0]==p.ini[0]+1) // Caso o movimento seja para frente e a casa esteja vazia
		move(tabuleiro, p);
	else if(inimigo(tabuleiro, p) && p.fin[0]==p.ini[0]+1 && (p.fin[1]==p.ini[1]+1 || p.fin[1]==p.ini[1]-1)) // Caso o movimento seja lateral e haja um inimigo na casa
		move(tabuleiro, p);
	else
		printf("Movimento invalido");
}

void cavalo(tab tabuleiro[8][8], pos p)
{
	if((vazio(tabuleiro, p) || inimigo(tabuleiro, p)) && (p.fin[0]==p.ini[0]+2 && (p.fin[1]==p.ini[1]+1 || p.fin[1]==p.ini[1]+1)) || 
	(p.fin[0]==p.ini[0]-2 && (p.fin[1]==p.ini[1]+1 || p.fin[1]==p.ini[1]+1)) || (p.fin[1]==p.ini[1]+2 && (p.fin[0]==p.ini[0]+1 || p.fin[0]==p.ini[0]+1)) ||
	p.fin[1]==p.ini[1]+2 && (p.fin[0]==p.ini[0]+1 || p.fin[0]==p.ini[0]+1))// Todos os movimentos possiveis em L, dois para frentee e um para o lado
		move(tabuleiro, p);
	else
		printf("Movimento invalido");

}
void torre(tab tabuleiro[8][8], pos p)
{
	if((vazio(tabuleiro, p) || inimigo(tabuleiro, p)))
	{
		move(tabuleiro, p);
		return;
	}
	for(int i=1; i<9; i++)
	{
		if((p.fin[0]==p.in[0]]+i && (p.fin[0]<7&&p.fin[0]>=0)) || (p.fin[0]==p.ini[0]-i && (p.fin[0]<7&&p.fin[0]>=0)) || 
			(p.fin[1]==p.in[1]]+i && (p.fin[1]<7&&p.fin[1]>=0)) || (p.fin[1]==p.ini[1]-i && (p.fin[1]<7&&p.fin[1]>=0)))//Permite movimentar enquanto na mesma linha ou coluna, restrito de 0 a 7
		{
			move(tabuleiro, p);
			return;
		}	
	}
	printf("\nMovimento invalido");
}

void rainha(tab tabuleiro[8][8], pos p)
{
	if((vazio(tabuleiro, p) || inimigo(tabuleiro, p)))
	{
		move(tabuleiro, p);
		break;
	}
	else if(p.fin[0]==p.ini[0]+1 || p.fin[0]==p.ini[0]-1 || p.fin[1]==p.ini[1]+1 || p.fin[1]==p.ini[1]-1 || (p.fin[0]==p.ini[0]+1 && 
		(p.fin[1]==p.ini[1]-1||p.fin[1]==p.ini[1]+1))(p.fin[0]==p.ini[0]-1 && (p.fin[1]==p.ini[1]-1||p.fin[1]==p.ini[1]+1)))//Movimenta uma casa a frente em todas as direções possíveis.
	for(int i=0; i<8; i++)
	{
		if((p.fin[0]==p.in[0]]+i && (p.fin[0]<7&&p.fin[0]>=0)) || (p.fin[0]==p.ini[0]-i && (p.fin[0]<7&&p.fin[0]>=0)) || 
			(p.fin[1]==p.in[1]]+i && (p.fin[1]<7&&p.fin[1]>=0)) || (p.fin[1]==p.ini[1]-i && (p.fin[1]<7&&p.fin[1]>=0)))
			{
			move(tabuleiro, p);
			break;
			}
		else if((p.fin[0]==p.ini[0]]+i && (p.fin[0]<7&&p.fin[0]>=0) && (p.fin[1]==p.ini[1]+i || p.fin[1]==p.ini[1]+i)) || 
			(p.fin[0]==p.ini[0]]-i && (p.fin[0]<7&&p.fin[0]>=0) && (p.fin[1]==p.ini[1]+i || p.fin[1]==p.ini[1]+i))) //Permite movimentar lateralmente até o fim do tabuleiro
			{
			move(tabuleiro, p);
			break;
			}
	}
	printf("\nMovimento invalido");
}
void rei(tab tabuleiro[8][8], pos p)
{
	if(p.fin[0]==p.ini[0]+1 || p.fin[0]==p.ini[0]-1 || p.fin[1]==p.ini[1]+1 || p.fin[1]==p.ini[1]-1 || (p.fin[0]==p.ini[0]+1 && 
		(p.fin[1]==p.ini[1]-1||p.fin[1]==p.ini[1]+1))(p.fin[0]==p.ini[0]-1 && (p.fin[1]==p.ini[1]-1||p.fin[1]==p.ini[1]+1)))//Movimenta uma casa a frente em todas as direções possíveis.
		move(tabuleiro, p);
	else
		printf("Movimento invalido");
}
void bispo(tab tabuleiro[8][8], pos p)
{
	for(int i=1; i<9; i++)
	{
		if((p.fin[0]==p.ini[0]]+i && (p.fin[0]<7&&p.fin[0]>=0) && (p.fin[1]==p.ini[1]+i || p.fin[1]==p.ini[1]+i)) || 
			(p.fin[0]==p.ini[0]]-i && (p.fin[0]<7&&p.fin[0]>=0) && (p.fin[1]==p.ini[1]+i || p.fin[1]==p.ini[1]+i))) //Permite movimentar lateralmente até o fim do tabuleiro
		{
			move(tabuleiro, p);
			break;
		}	
	}	
		printf("Movimento invalido");
}

void imprimirTabuleiro(tab tabuleiro[8][8])
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			printf("%c  ",tabuleiro[i][j].tipo);
			if(j==7)
				printf("\n\n");
		}
	}
}

void jogada(tab tabuleiro[8][8])
{
	pos p;
	printf("\nDigite a posição atual da peça: ");
	scanf("%d %d", &p.ini[0], &p.ini[1]);
	printf("\nDigite a posição de destino: ");
	scanf("%d %d", &p.fin[0], &p.fin[1]);
	switch(tabuleiro[p.ini[0]][p.ini[1]])
	{
		case 'P':
			peao(tabuleiro, p);
			break;
		case 'T':
			torre(tabuleiro, p);
			break;
		case 'B':
			bispo(tabuleiro, p);
			break;
		case 'C':
			cavalo(tabuleiro, p);
			break;
		case 'Q':
			rainha(tabuleiro, p);
			break;
		case 'K':
			rei(tabuleiro, p);
			break;
		default:
			printf("\nPosição vazia");
			system("pause");
			break;
	}
	system("cls");
	imprimirTabuleiro(tabuleiro);
}