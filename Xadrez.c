#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>


typedef struct tab{
	char tipo;
	char cor;
} tab;

typedef struct pos{
	int ini[2];
	int fin[2];
} pos;

typedef struct possivel{
	int x;
	int y;
} possivel;

void initTabuleiro(tab tabuleiro[8][8]);
bool vazio(tab tabuleiro[8][8],int x,int y);
void move(tab tabuleiro[8][8], pos p, possivel *cor);
bool inimigo(tab tabuleiro[8][8], pos p, int x, int y);
possivel* peao(tab tabuleiro[8][8], pos p);
void imprimirTabuleiro(tab tabuleiro[8][8]);
possivel* cavalo(tab tabuleiro[8][8], pos p);
possivel* torre(tab tabuleiro[8][8], pos p);
possivel* rainha(tab tabuleiro[8][8], pos p);
possivel* rei(tab tabuleiro[8][8], pos p);
void jogada(tab tabuleiro[8][8]);
void aloca(possivel **p, int tam);
int tamanho(possivel *p);
bool valido(int x, int y);


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

bool vazio(tab tabuleiro[8][8],int x,int y)
{
	return tabuleiro[y][x].tipo == '-';
}

bool inimigo(tab tabuleiro[8][8], pos p, int x, int y)
{
	return tabuleiro[p.ini[0]][p.ini[1]].cor == tabuleiro[y][x].cor;
}

void move(tab tabuleiro[8][8], pos p, possivel *cor)// O erro está no vetor COR
{
	for(int i=0; i<6;i++)
	{
		
		if(p.fin[1] == cor[i].x && p.fin[0] == cor[i].y)
		{
			tabuleiro[p.fin[0]][p.fin[1]] = tabuleiro[p.ini[0]][p.ini[1]]; // Coloca a peça da posição inicial na posição final
			tabuleiro[p.ini[0]][p.ini[1]] = (tab) {'-','N'}; // Coloca um espaço vazio na posição inicial	
			free(cor);
			return;
		}
	}
	system("pause");
	printf("\nMovimento inválido, tente novamente.");
}

possivel* peao(tab tabuleiro[8][8], pos p)
{
	possivel *coordenadas = NULL;
	int tam;
	if(tabuleiro[p.ini[0]][p.ini[1]].cor == 'B') // Verifica se a movimentação é de um peão branco 
	{
		if(valido(0,p.ini[0]+1) && vazio(tabuleiro, p.ini[1], p.ini[0]+1)) // Verifica se a casa a frente está vazia e se o movimento é possível e válido
		{
			tam = tamanho(coordenadas)+1;
			aloca(&coordenadas, tam);
			(coordenadas+(tam-1))->x=p.ini[1];
			(coordenadas+(tam-1))->y =p.ini[0]+1;
		}
		else if(valido(p.ini[1]-1,p.ini[0]+1) && valido(p.ini[1]+1,p.ini[0]+1)) // verifica se as casas diagonais são válidas
		{
			tam = tamanho(coordenadas)+1;
			aloca(&coordenadas, tam);
			if(inimigo(tabuleiro, p, p.ini[1]-1, p.ini[0]+1)) // verifica se há um inimigo na diagonal esquerda
			{
				(coordenadas+(tam-1))->x=p.ini[1]-1;
				(coordenadas+(tam-1))->y=p.ini[0]+1;
			}
			else if(inimigo(tabuleiro, p, p.ini[1]+1, p.ini[0]+1)) // verifica se há um inimigo na diagonal direita
			{
				(coordenadas+(tam-1))->x=p.ini[1]+1;
				(coordenadas+(tam-1))->y=p.ini[0]+1;
			}
			
		}
	}
	else // Se o peão não for branco, então ele é preto
	{
		if(valido(0,p.ini[0]-1) && vazio(tabuleiro, p.ini[1], p.ini[0]-1)) // Verifica se a casa a frente está vazia e se o movimento é possível e válido
		{
			tam = tamanho(coordenadas)+1;
			aloca(&coordenadas, tam);
			(coordenadas+(tam-1))->x=p.ini[1];
			(coordenadas+(tam-1))->y=p.ini[0]-1;
		}
		else if(valido(p.ini[1]-1,p.ini[0]-1) && valido(p.ini[1]+1,p.ini[0]-1)) // verifica se as casas diagonais são válidas
		{
			tam = tamanho(coordenadas)+1;
			aloca(&coordenadas, tam); 
			if(inimigo(tabuleiro, p, p.ini[1]-1, p.ini[0]-1)) // verifica se há um inimigo na diagonal esquerda
			{
				(coordenadas+(tam-1))->x=p.ini[1]-1;
				(coordenadas+(tam-1))->y=p.ini[0]-1;
			}
			else if(inimigo(tabuleiro, p, p.ini[1]+1, p.ini[0]-1)) // verifica se há um inimigo na diagonal direita
			{
				(coordenadas+(tam-1))->x=p.ini[1]+1;
				(coordenadas+(tam-1))->y=p.ini[0]-1;
			}
			
		}
	}
	return coordenadas;
}

possivel* cavalo(tab tabuleiro[8][8], pos p)
{

	possivel *coordenadas = NULL;
	possivel aux[]={{2,-1},{2,1},{-2,1},{-2,-1},{-1,2},{1,2},{1,-2},{-1,-2}}; // Instancia todas as posições possíveis de um cavalo em relação a sua posição inicial
	aloca(&coordenadas, 8);

	for(int i=0; i<8 ; i++)
	{
		if(valido(p.ini[1]+aux[i].x, p.ini[0]+aux[i].y))
			if(vazio(tabuleiro,p.ini[1]+aux[i].x, p.ini[0]+aux[i].y) || inimigo(tabuleiro, p, p.ini[1]+aux[i].x, p.ini[0]+aux[i].y)) // verifica todas as instancias possíveis em relação a posição inicial
			{
				(coordenadas+i)->x=p.ini[1]+aux[i].x;
				(coordenadas+i)->y=p.ini[0]+aux[i].y;
			}

	}

	return coordenadas;

}
possivel* torre(tab tabuleiro[8][8], pos p) // Torre branca está comendo o peão branco
{
	int esquerda = 1, direita = 1, frente = 1, tras = 1;
	possivel *coordenadas = NULL;
	int tam;
	for(int i=1; i<9; i++)
	{
	
		if(valido(0,p.ini[0]+i) && vazio(tabuleiro, p.ini[1], p.ini[0]+i) && frente == 1) // Verifica para frente e guarda as posições possiveis no vetor coordenadas
		{
			tam = tamanho(coordenadas)+1;
			aloca(&coordenadas, tam);
			(coordenadas+(tam-1))->x=p.ini[1];
			(coordenadas+(tam-1))->y=p.ini[0]+i;
		}
		else if(frente == 1 && !vazio(tabuleiro, p.ini[1], p.ini[0]+i)) // Caso tenha uma peça nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
		{
			frente = 0;
			if(inimigo(tabuleiro, p, p.ini[1], p.ini[0]+i))
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1];
				(coordenadas+(tam-1))->y=p.ini[0]+i;
			}
		}

		if(valido(0,p.ini[0]-i) && vazio(tabuleiro, p.ini[1], p.ini[0]-i) && tras == 1) // Verifica para tras e guarda as posições possiveis no vetor coordenadas
		{
			tam = tamanho(coordenadas)+1;
			aloca(&coordenadas, tam);
			(coordenadas+(tam-1))->x=p.ini[1];
			(coordenadas+(tam-1))->y=p.ini[0]-i;
		}
		else if(tras == 1 && !vazio(tabuleiro, p.ini[1], p.ini[0]-i)) // Caso tenha uma peça nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
		{
			tras = 0;
			if(inimigo(tabuleiro, p, p.ini[1], p.ini[0]-i))
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1];
				(coordenadas+(tam-1))->y=p.ini[0]-i;
			}
		}
				

		if(valido(p.ini[1]+i,0) && vazio(tabuleiro, p.ini[1]+i, p.ini[0]) && direita == 1) // verifica para a direita e guarda as posições possiveis no vetor coordenadas
		{
			tam = tamanho(coordenadas)+1;
			aloca(&coordenadas, tam);
			(coordenadas+(tam-1))->x=p.ini[1]+i;
			(coordenadas+(tam-1))->y=p.ini[0];
		}
		else if(direita == 1 && !vazio(tabuleiro, p.ini[1]+i, p.ini[0])) // Caso tenha uma peça nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
		{
			direita = 0;
			if(inimigo(tabuleiro, p, p.ini[1]+i, p.ini[0]))
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1]+i;
				(coordenadas+(tam-1))->y=p.ini[0];
			}
				
			}
				

			if(valido(p.ini[1]-i,0) && vazio(tabuleiro, p.ini[1]-i, p.ini[0]) && esquerda == 1) // Verifica para a esquerda e guarda as posições possiveis no vetor coordenadas
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1]-i;
				(coordenadas+(tam-1))->y=p.ini[0];
			}
			else if(esquerda == 1 && !vazio(tabuleiro, p.ini[1]-i, p.ini[0])) // Caso tenha uma peça nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
			{ 
				esquerda = 0;
				if(inimigo(tabuleiro, p, p.ini[1]-i, p.ini[0]))
				{
					tam = tamanho(coordenadas)+1;
					aloca(&coordenadas, tam);
					(coordenadas+(tam-1))->x=p.ini[1]-i;
					(coordenadas+(tam-1))->y=p.ini[0];
				}
			}		
				
		
	}

	return coordenadas;

// p.fin[0]==p.ini[0]+i || p.fin[0]==p.ini[0]-i || p.fin[1]==p.ini[1]+i || p.fin[1]==p.ini[1]-i
	
}

possivel* rainha(tab tabuleiro[8][8], pos p)
{
	int dEC = 1, dEB = 1, dDC = 1, dDB = 1;
	int esquerda = 1, direita = 1, frente = 1, tras = 1;
	possivel aux[]={{1,-1},{1,1},{-1,1},{-1,-1},{0,1},{0,-1},{1,0},{-1,0}};
	possivel *coordenadas = NULL;
	int tam;

	for(int i=1; i<9; i++)
	{
		if(valido(p.ini[1]-i,p.ini[0]-i) && vazio(tabuleiro, p.ini[1]-i, p.ini[0]-i) && dEC == 1) // Verifica dEC e guarda as posições possiveis no vetor coordenadas
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1]-i;
				(coordenadas+(tam-1))->y=p.ini[0]-i;
			}
			else if(dEC == 1 && !vazio(tabuleiro, p.ini[1]-i, p.ini[0]-i)) // Caso tenha uma peça inimiga nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
			{
				dEC = 0;
				if(inimigo(tabuleiro, p, p.ini[1]-i, p.ini[0]-i))
				{
					tam = tamanho(coordenadas)+1;
					aloca(&coordenadas, tam);
					(coordenadas+(tam-1))->x=p.ini[1]-i;
					(coordenadas+(tam-1))->y=p.ini[0]-i;
				}
			}

			if(valido(p.ini[1]-i,p.ini[0]+i) && vazio(tabuleiro, p.ini[1]-i,p.ini[0]+i) && dEB == 1) // Verifica para dEB e guarda as posições possiveis no vetor coordenadas
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1]-i;
				(coordenadas+(tam-1))->y=p.ini[0]+i;
			}
			else if(dEB == 1 && !vazio(tabuleiro, p.ini[1]-i,p.ini[0]+i)) // Caso tenha uma peça inimiga nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
			{
				dEB = 0;
				if(inimigo(tabuleiro, p, p.ini[1]-i, p.ini[0]+i))
				{
					tam = tamanho(coordenadas)+1;
					aloca(&coordenadas, tam);
					(coordenadas+(tam-1))->x=p.ini[1]-i;
					(coordenadas+(tam-1))->y=p.ini[0]+i;
				}
			}
				

			if(valido(p.ini[1]+i,p.ini[0]-i) && vazio(tabuleiro, p.ini[1]+i, p.ini[0]-i) && dDC == 1) // verifica para a dDC e guarda as posições possiveis no vetor coordenadas
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1]+i;
				(coordenadas+(tam-1))->y=p.ini[0]-i;
			}
			else if(dDC == 1 && !vazio(tabuleiro, p.ini[1]+i, p.ini[0]-i)) // Caso tenha uma peça inimiga nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
			{
				dDC = 0;
				if(inimigo(tabuleiro, p, p.ini[1]+i, p.ini[0]-i))
				{
					tam = tamanho(coordenadas)+1;
					aloca(&coordenadas, tam);
					(coordenadas+(tam-1))->x=p.ini[1]+i;
					(coordenadas+(tam-1))->y=p.ini[0]-i;
				}
				
			}
				

			if(valido(p.ini[1]+i,p.ini[0]+i) && vazio(tabuleiro, p.ini[1]+i, p.ini[0]+i) && dDB == 1) // Verifica para a dDB e guarda as posições possiveis no vetor coordenadas
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1]+i;
				(coordenadas+(tam-1))->y=p.ini[0]+i;
			}
			else if(dDB == 1 && !vazio(tabuleiro, p.ini[1]+i, p.ini[0]+i)) // Caso tenha uma peça nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
			{ 
				dDB = 0;
				if(inimigo(tabuleiro, p, p.ini[1]+i, p.ini[0]+i))
				{
					tam = tamanho(coordenadas)+1;
					aloca(&coordenadas, tam);
					(coordenadas+(tam-1))->x=p.ini[1]+i;
					(coordenadas+(tam-1))->y=p.ini[0]+i;
				}
			}
			if(valido(0,p.ini[0]+i) && vazio(tabuleiro, p.ini[1], p.ini[0]+i) && frente == 1) // Verifica para frente e guarda as posições possiveis no vetor coordenadas
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1];
				(coordenadas+(tam-1))->y=p.ini[0]+i;
			}
			else if(frente == 1 && !vazio(tabuleiro, p.ini[1], p.ini[0]+i)) // Caso tenha uma peça nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
			{
				frente = 0;
				if(inimigo(tabuleiro, p, p.ini[1], p.ini[0]+i))
				{
					tam = tamanho(coordenadas)+1;
					aloca(&coordenadas, tam);
					(coordenadas+(tam-1))->x=p.ini[1];
					(coordenadas+(tam-1))->y=p.ini[0]+i;
				}
			}

			if(valido(0,p.ini[0]-i) && vazio(tabuleiro, p.ini[1], p.ini[0]-i) && tras == 1) // Verifica para tras e guarda as posições possiveis no vetor coordenadas
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1];
				(coordenadas+(tam-1))->y=p.ini[0]-i;
			}
			else if(tras == 1 && !vazio(tabuleiro, p.ini[1], p.ini[0]-i)) // Caso tenha uma peça nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
			{
				tras = 0;
				if(inimigo(tabuleiro, p, p.ini[1], p.ini[0]-i))
				{
					tam = tamanho(coordenadas)+1;
					aloca(&coordenadas, tam);
					(coordenadas+(tam-1))->x=p.ini[1];
					(coordenadas+(tam-1))->y=p.ini[0]-i;
				}
			}
				

			if(valido(p.ini[1]+i,0) && vazio(tabuleiro, p.ini[1]+i, p.ini[0]) && direita == 1) // verifica para a direita e guarda as posições possiveis no vetor coordenadas
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1]+i;
				(coordenadas+(tam-1))->y=p.ini[0];
			}
			else if(direita == 1 && !vazio(tabuleiro, p.ini[1]+i, p.ini[0])) // Caso tenha uma peça nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
			{
				direita = 0;
				if(inimigo(tabuleiro, p, p.ini[1]+i, p.ini[0]))
				{
					tam = tamanho(coordenadas)+1;
					aloca(&coordenadas, tam);
					(coordenadas+(tam-1))->x=p.ini[1]+i;
					(coordenadas+(tam-1))->y=p.ini[0];
				}
				
			}
				

			if(valido(p.ini[1]-i,0) && vazio(tabuleiro, p.ini[1]-i, p.ini[0]) && esquerda == 1) // Verifica para a esquerda e guarda as posições possiveis no vetor coordenadas
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1]-i;
				(coordenadas+(tam-1))->y=p.ini[0];
			}
			else if(esquerda == 1 && !vazio(tabuleiro, p.ini[1]-i, p.ini[0])) // Caso tenha uma peça nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
			{ 
				esquerda = 0;
				if(inimigo(tabuleiro, p, p.ini[1]-i, p.ini[0]))
				{
					tam = tamanho(coordenadas)+1;
					aloca(&coordenadas, tam);
					(coordenadas+(tam-1))->x=p.ini[1]-i;
					(coordenadas+(tam-1))->y=p.ini[0];
				}
			}	
			if(valido(p.ini[1]+aux[i-1].x, p.ini[0]+aux[i-1].y))
			if(vazio(tabuleiro,p.ini[1]+aux[i-1].x, p.ini[0]+aux[i-1].y) || inimigo(tabuleiro, p, p.ini[1]+aux[i-1].x, p.ini[0]+aux[i-1].y))
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1]+aux[i-1].x;
				(coordenadas+(tam-1))->y=p.ini[0]+aux[i-1].y;
			}
	}
	return coordenadas;

}
possivel* rei(tab tabuleiro[8][8], pos p)
{
	possivel *coordenadas = NULL;
	possivel aux[]={{1,-1},{1,1},{-1,1},{-1,-1},{0,1},{0,-1},{1,0},{-1,0}};
	aloca(&coordenadas, 8);

	for(int i=0; i<8 ; i++)
	{
		if(valido(p.ini[1]+aux[i].x, p.ini[0]+aux[i].y))
			if(vazio(tabuleiro,p.ini[1]+aux[i].x, p.ini[0]+aux[i].y) || inimigo(tabuleiro, p, p.ini[1]+aux[i].x, p.ini[0]+aux[i].y))
			{
				(coordenadas+i)->x=p.ini[1]+aux[i].x;
				(coordenadas+i)->y=p.ini[0]+aux[i].y;
			}

	}
	return coordenadas;
}
possivel* bispo(tab tabuleiro[8][8], pos p)
{
	int dEC = 1, dEB = 1, dDC = 1, dDB = 1;
	//dEC - Diagonal esquerda cima
	//dEB - Diagonal esquerda baixo
	//dDC - Diagonal direita cima
	//dDB - Diagonal direita baixo
	possivel *coordenadas = NULL;
	int tam;
	for(int i=1; i<9; i++)
	{
		if(valido(p.ini[1]-i,p.ini[0]-i) && vazio(tabuleiro, p.ini[1]-i, p.ini[0]-i) && dEC == 1) // Verifica dEC e guarda as posições possiveis no vetor coordenadas
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1]-i;
				(coordenadas+(tam-1))->y=p.ini[0]-i;
			}
			else if(dEC == 1 && !vazio(tabuleiro, p.ini[1]-i, p.ini[0]-i)) // Caso tenha uma peça inimiga nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
			{
				dEC = 0;
				if(inimigo(tabuleiro, p, p.ini[1]-i, p.ini[0]-i))
				{
					tam = tamanho(coordenadas)+1;
					aloca(&coordenadas, tam);
					(coordenadas+(tam-1))->x=p.ini[1]-i;
					(coordenadas+(tam-1))->y=p.ini[0]-i;
				}
			}

			if(valido(p.ini[1]-i,p.ini[0]+i) && vazio(tabuleiro, p.ini[1]-i,p.ini[0]+i) && dEB == 1) // Verifica para dEB e guarda as posições possiveis no vetor coordenadas
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1]-i;
				(coordenadas+(tam-1))->y=p.ini[0]+i;
			}
			else if(dEB == 1 && !vazio(tabuleiro, p.ini[1]-i,p.ini[0]+i)) // Caso tenha uma peça inimiga nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
			{
				dEB = 0;
				if(inimigo(tabuleiro, p, p.ini[1]-i, p.ini[0]+i))
				{
					tam = tamanho(coordenadas)+1;
					aloca(&coordenadas, tam);
					(coordenadas+(tam-1))->x=p.ini[1]-i;
					(coordenadas+(tam-1))->y=p.ini[0]+i;
				}
			}
				

			if(valido(p.ini[1]+i,p.ini[0]-i) && vazio(tabuleiro, p.ini[1]+i, p.ini[0]-i) && dDC == 1) // verifica para a dDC e guarda as posições possiveis no vetor coordenadas
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1]+i;
				(coordenadas+(tam-1))->y=p.ini[0]-i;
			}
			else if(dDC == 1 && !vazio(tabuleiro, p.ini[1]+i, p.ini[0]-i)) // Caso tenha uma peça inimiga nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
			{
				dDC = 0;
				if(inimigo(tabuleiro, p, p.ini[1]+i, p.ini[0]-i))
				{
					tam = tamanho(coordenadas)+1;
					aloca(&coordenadas, tam);
					(coordenadas+(tam-1))->x=p.ini[1]+i;
					(coordenadas+(tam-1))->y=p.ini[0]-i;
				}
				
			}
				

			if(valido(p.ini[1]+i,p.ini[0]+i) && vazio(tabuleiro, p.ini[1]+i, p.ini[0]+i) && dDB == 1) // Verifica para a dDB e guarda as posições possiveis no vetor coordenadas
			{
				tam = tamanho(coordenadas)+1;
				aloca(&coordenadas, tam);
				(coordenadas+(tam-1))->x=p.ini[1]+i;
				(coordenadas+(tam-1))->y=p.ini[0]+i;
			}
			else if(dDB == 1 && !vazio(tabuleiro, p.ini[1]+i, p.ini[0]+i)) // Caso tenha uma peça nessa posição, guarda a posição nos movimentos possíveis e para a verificação para esta direção
			{ 
				dDB = 0;
				if(inimigo(tabuleiro, p, p.ini[1]+i, p.ini[0]+i))
				{
					tam = tamanho(coordenadas)+1;
					aloca(&coordenadas, tam);
					(coordenadas+(tam-1))->x=p.ini[1]+i;
					(coordenadas+(tam-1))->y=p.ini[0]+i;
				}
			}	
	}	
	return coordenadas;
}

void imprimirTabuleiro(tab tabuleiro[8][8])
{
	printf("\n\n");
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
	possivel *cor;
	int aux;
	do{ 
		printf("\nDigite a posicao atual da peca: ");
		scanf("%d %d", &p.ini[0], &p.ini[1]);
		printf("\nDigite a posicao de destino: ");
		scanf("%d %d", &p.fin[0], &p.fin[1]);
		printf("\n\nP ini - > %d %d, P fin - > %d %d",p.ini[0], p.ini[1], p.fin[0], p.fin[1]);
		printf("\n\n Peca - > %c, cor - > %c",tabuleiro[p.ini[0]][p.ini[1]].tipo, tabuleiro[p.ini[0]][p.ini[1]].cor);
		switch(tabuleiro[p.ini[0]][p.ini[1]].tipo)
		{
			case 'P':
				cor = peao(tabuleiro, p); // O valor não está sendo passado corretamente para o ponteiro cor
				move(tabuleiro, p, cor);
				break;
			case 'T':
				cor = torre(tabuleiro, p);
				move(tabuleiro, p, cor);
				break;
			case 'B':
				cor = bispo(tabuleiro, p);
				move(tabuleiro, p, cor);
				break;
			case 'C':
				cor = cavalo(tabuleiro, p);
				move(tabuleiro, p, cor);
				break;
			case 'Q':
				cor = rainha(tabuleiro, p);
				move(tabuleiro, p, cor);
				break;
			case 'K':
				cor = rei(tabuleiro, p);
				move(tabuleiro, p, cor);
				break;
			default:
				printf("\nPosicao vazia");
				system("pause");
				break;
		}
		system("pause");
		system("cls");
		imprimirTabuleiro(tabuleiro);
		printf("\n\nContinuar?");
		scanf("%i", &aux);

	}while(aux!=0);
}

void aloca(possivel **p, int tam)
{
	if((*p=(possivel*)realloc(*p, tam*sizeof(possivel))) == NULL)
    {
        printf("\nErro na alocaçao\n\n");
        system("pause");
        exit(1);
    }
}

int tamanho(possivel *p)
{
	if(p==NULL)
		return 0;
	else
		return sizeof(*p)/sizeof(possivel);
}

bool valido(int x, int y)
{
	return x >=0 && x< 8 && y>=0 && y<8;
}