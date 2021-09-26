#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct /** Estrutura de dados **/
{
	char nome[31];
	int ano;
	float montante;
}Client;


typedef struct /** Estrutura de dados que contém tipos e variáveis essenciais para o armazenamento de dados na memória **/
{
	Client *pCliente;
	int qntd;
}listaClientes;


/** Declaração das funções a serem utilizadas abaixo **/
void criarlistavazia(listaClientes *listaP); 
void criarlistavaziamaior(listaClientes *listaP, int pos);
void InserirRegistro(char nome[], int ano, float montante, listaClientes *listaP, int pos);
void ListarClientes(listaClientes lista);
listaClientes buscarRegistroRemove(char nome[], listaClientes lista);
listaClientes buscarRegistroUpdate (char nome[], listaClientes lista);
void ZerarMontantes(listaClientes lista);
void listarMelhorCliente(listaClientes lista);
void ListaMontanteCliente(char buscarNome[], listaClientes lista);
void menu();


int main(void)
{
	system("color 70");


	char nome[31];
	int ano;
	float montante;
	
	char buscarNome[31];
	
	listaClientes lista;
	
	criarlistavazia(&lista);
	lista.qntd = 0;
	
	int op = 8;
	
	while(op!=0)
	{
		switch(op)
		{
			case 1: /** Cadastro de clientes **/
				
				printf("\n\n Digite o nome do cliente: ");
				scanf("%s", nome);
				printf("\n\n Digite o ano de nascimento: ");
				scanf("%d", &ano);
				printf("\n\n Digite o montante de gastos do cliente: ");
				scanf("%f", &montante);
				
					InserirRegistro(nome, ano, montante, &lista, lista.qntd);
				lista.qntd += 1;
				printf("\n Cadastro realizado com sucesso!");
				op = 8;
			break;
			
			
			case 2: /** Excluir clientes **/
			
				printf("\n Digite o nome do cliente que deseja remover: ");
				scanf("%s", buscarNome);
				lista = buscarRegistroRemove (buscarNome, lista);
				op = 8;
			break;
			
			case 3: /** Atualizar Gastos de cliente **/
			
				printf("\n Digite o nome do cliente que deseja atualizar: ");
				scanf("%s", buscarNome);
				lista = buscarRegistroUpdate(buscarNome, lista);
				op = 8;
			break;
			
			case 4: /** Zerando montantes de um determinado cliente **/
			
				ZerarMontantes(lista);
				op = 8;
			break;
			case 5: /** Listagem de clientes **/
			
				ListarClientes(lista);
				op = 8;
			
			break;
			
			case 6: /** Listagem do melhor cliente **/
			
				listarMelhorCliente(lista);
				op = 8;
			
			break;
			
			case 7: /**Listagem do montante especifico de um cliente**/
				
				printf("\n Digite o nome do cliente: ");
				scanf("%s", buscarNome);
				ListaMontanteCliente(buscarNome, lista);
				op = 8;
			
			break;
				
			default:
				menu();
				scanf("%d", &op);
			break;
		}
	}
	
}

void criarlistavazia(listaClientes *listaP) /** Alocando 10 espaços na memória **/
{
	listaP->pCliente = (Client *) calloc(10, sizeof(Client));  
}

void criarlistavaziamaior(listaClientes *listaP, int pos)
{
	listaP->pCliente = (Client*) calloc(listaP->pCliente, 10* ((pos/10)+1) * sizeof(Client));
}

void InserirRegistro(char nome[], int ano, float montante, listaClientes *listaP, int pos) /** função Realloc que permite realocar espaços flexibilizando a memória, de modo que não ultrapasse 10 espaços **/
{
	printf("\n Posicao: %d", pos);
	if(pos >= 10 && pos % 10 == 0)
	{
		listaP->pCliente = (Client *) realloc (listaP->pCliente, 10* ((pos/10)+1) * sizeof(Client));
	}
	
	Client p;
	strncpy(p.nome, nome, 31);
	p.ano = ano;
	p.montante = montante;
	
	memcpy((listaP->pCliente+pos), &p, sizeof(Client));
	
}

void ListarClientes(listaClientes lista)
{
	for(int i = 0; i < lista.qntd; i++)
	{
		printf("\n\n Cliente: %d \n\n", i);
		printf("Nome: %s, Ano: %d, Montante: %f", (lista.pCliente+i)->nome, (lista.pCliente+i)->ano, (lista.pCliente+i)->montante);
	}
}

listaClientes buscarRegistroRemove(char nome[], listaClientes lista)
{
	listaClientes listaTmp;
	criarlistavaziamaior(&listaTmp, lista.qntd);
	listaTmp.qntd = lista.qntd;
	
	int iTmp = 0;
	for(int i = 0; i < lista.qntd; i++)
	{
		if(strcmp(nome, (lista.pCliente+i)->nome) !=0)
		{
			int x = i - iTmp;
			memcpy(listaTmp.pCliente+x, lista.pCliente+i, sizeof(Client));
		}
		else
		{
			iTmp = 1;
		}
		
		listaTmp.qntd -= 1;
		return listaTmp;
	}
}

listaClientes buscarRegistroUpdate (char nome[], listaClientes lista)
{
	float montanteAtual;
	
	for(int i = 0; i<lista.qntd; i++)
	{
		if(strcmp(nome, (lista.pCliente+i)->nome) == 0)
		{
			printf("\n Digite o montante do cliente: ");
			scanf("%f", &montanteAtual);
			(lista.pCliente+i)->montante = montanteAtual;
			return lista;
		}
	}
	
	return lista;
}

void ZerarMontantes(listaClientes lista)
{
	for(int i=0; i < lista.qntd; i++)
	{
		(lista.pCliente+i)->montante = 0.0;
	}
	
	printf("\n\n Montante do mes zerado com sucesso!");
}

void listarMelhorCliente(listaClientes lista)
{
	float MontanteTemporario = 0.0;
	Client *p;
	for(int i = 0; i < lista.qntd; i++)
	{
		printf("\n Montante do cliente %s: %f", (lista.pCliente+i)->nome, (lista.pCliente+i)->montante);
		if((lista.pCliente+i)->montante > MontanteTemporario)
		{
			MontanteTemporario = (lista.pCliente+i)->montante;
			p = lista.pCliente+i;
		}
	}
	
	printf("\n O melhor cliente do mes foi: ");
	printf("Nome: %s, ano: %d, montante: %f", p->nome, p->ano, p->montante);
	
}

void ListaMontanteCliente(char buscarNome[], listaClientes lista)
{
	for(int i = 0; i<lista.pCliente; i++)
	{
		if(strcmp(buscarNome, (lista.pCliente+i)->nome) == 0)
		{
			printf("\n Cliente: %d", i);
			printf("Nome: %s, Ano: %d, Montante: %f", (lista.pCliente+i)->nome, (lista.pCliente+i)->ano, (lista.pCliente+i)->montante);
		}
	}
}





void menu() /** Menu contendo as opções das funcionalidades abaixo **/
{	
	
	printf("\n\n=========================================================MENU===========================================================\n\n");
	
	
	printf("\n\n 1 - Cadastrar cliente");
	printf("\n\n 2 - Excluir cliente");
	printf("\n\n 3 - Atualizar montante de cliente");
	printf("\n\n 4 - Zerar todos os montantes / virada do mes");
	printf("\n\n 5 - Listar clientes");
	printf("\n\n 6 - Melhor cliente");
	printf("\n\n 7 - Exibir compras cliente");
	printf("\n\n 8 - Sair do sistema");
	
	printf("\n\n\n Digite um numero de acordo com as opcoes acima: ");
	
	
}


