//DGHI - Ativ05 - Hotel
//Deborah Carvalho Saad
//Geovanna Cristina Brenzinger
//Henrique Abreu Hollanda da Rocha
//Isabela Nunes dos Santos
//Hotel que possui 20 andares com 14 apartamentos por andar. Se o apartamento estiver livre, o apartamento eh alocado e
//o hospede faz o registro. Ao deixar o hotel, o hospede faz o check-out e libera o apartamento. Da pra fazer reserva.

#include <stdio.h>
#include <string.h> 

//Criacao da estrutura endereco, para o tipo de dado enredeco
typedef struct endereco {
    char rua[50];
    char num[4];
    char cep[10];
    char munic[40];
    char estado[4];
} tipoEndereco;

typedef struct cliente {
    char nome[40];
    char cel[12];
    char cpf[15];
    tipoEndereco endc;
} tipoCliente;

typedef struct apto {
    char status;
    tipoCliente hospa;
} tipoApto;

void fMenu();
void fMapa(tipoApto Mat[21][14]);
int fCPF(tipoApto Mat[21][14], char cpft[15]);
void fCadastro(tipoApto Mat[21][14], int i, int j);
void fReserva(tipoApto Mat[21][14], int i, int j);
void fCancelarR(tipoApto Mat[21][14], char cpft[15]);
void fCheckIn(tipoApto Mat[21][14], char cpft[15]);
void fCheckOut(tipoApto Mat[21][14], char cpft[15]);
void fOcupacao(tipoApto Mat[21][14]);
void fSituacao (tipoApto Mat[21][14]);
void fLimpar();

main() {
    tipoApto Mat[21][14];
    int i, j, op, ck, l, k;
    char cpft[15];

    for (int i = 1; i < 21; i++)
        for (int j = 1; j < 16; j++)
            Mat[i][j].status = '.';

    do {
        fMenu();
        scanf("%d", &op);

        switch (op) {
        case 1:
            fMapa(Mat);
            break;
        case 2:
            printf("\n Digite, respectivamente, o andar e o quarto desejados, separados por espaco:\t");
            scanf("%d %d", &i, &j);
            if ((i>0 && i<21) && (j>0 && j<15)) {     
                fReserva(Mat, i, j);
            } else {
                printf("\n Andar e/ou apartamento inexistente. \n");
            }
            break;
        case 3:
        	fLimpar();
            printf("\n Digite o CPF do cliente: ");
            scanf("%s", cpft);
            fCancelarR(Mat, cpft);
        	break;
        case 4:
            fLimpar();
            printf("\n Digite o CPF do cliente: ");
            scanf("%s", cpft);
            fCheckIn(Mat, cpft);
        	break;
        case 5:
            fLimpar();
            printf("\n Digite o CPF do cliente: ");
            scanf("%s", cpft);
            fCheckOut(Mat, cpft);
        	break;
        case 6:
        	fOcupacao(Mat);
        	break;
        case 7:
			fSituacao (Mat);
        	break;
        case 8:
            printf("\n PROGRAMA FINALIZADO!");
            break;
        default:
            printf("\n Opcao invalida!\n");
        }
    } while (op != 8);
}

//Funcao que exibe o menu de opcoes.
void fMenu() {
    printf("\n 1 - Visualizar o mapa.");
    printf("\n 2 - Iniciar reserva.");
    printf("\n 3 - Cancelar reserva.");
    printf("\n 4 - Iniciar check-in.");
    printf("\n 5 - Iniciar check-out.");
    printf("\n 6 - Verificar %% de ocupacao.");
    printf("\n 7 - Verificar situacao de um quarto.");
    printf("\n 8 - Sair do programa.\n");
    printf("\n Digite a opcao desejada: ");
}

//Funcao que imprime o mapa do hotel
void fMapa(tipoApto Mat[21][14]) {
    printf("\n");
    printf("Quarto");
    for (int j = 1; j < 15; j++) {
        printf("  %2d ", j);
    }
    printf("\n\n");
    for (int i = 20; i > 0; i--) {
        printf(" %2d\t", i);
    	for (int j = 1; j < 15; j++)
       		printf(" %c   ", Mat[i][j].status);
    	for(int j = 15; j>14 ; j--)
       		printf(" Andar\n");
        printf("\n");
    }
    printf("Quarto \t");
    for (int j = 1; j < 15; j++) {
        printf("%2d   ", j);
    }
    printf("\n");
}

//Funcao que retorna 1 se o cpf salvo na matriz, for igual ao parametro digitado no main "cpft" 
//(t de temporario, ja que toda vez que precisar digitar o cpf, salva nessa mesma variavel)
//retornando 0 quando não for.
int fCPF(tipoApto Mat[21][14], char cpft[15]) {
    for (int i = 20; i > 0; i--)
        for (int j = 1; j < 15; j++) {
            if (strcmp(Mat[i][j].hospa.cpf, cpft) == 0) {
                return 1;
            }
        }
    return 0;
}

//Funcao que realiza o cadastro do cliente com todas as informacoes.
void fCadastro(tipoApto Mat[21][14], int i, int j) {
    fLimpar();
    printf("\n\n\t Nome:	\t");
    scanf("%s", Mat[i][j].hospa.nome);
    fLimpar();
    printf("\t Celular:\t");
    scanf("%s", Mat[i][j].hospa.cel);
    fLimpar();
    printf("\t CPF:	\t");
    scanf("%s", Mat[i][j].hospa.cpf);
    printf("\n\n\n");
    fLimpar();
    printf("\t Endereco\n");
    printf("\t Rua:	\t");
    scanf("%s", Mat[i][j].hospa.endc.rua);
    fLimpar();
    printf("\t Numero:\t");
    scanf("%s", Mat[i][j].hospa.endc.num);
    fLimpar();
    printf("\t CEP:	\t");
    scanf("%s", Mat[i][j].hospa.endc.cep);
    fLimpar();
    printf("\t Municipio:\t");
    scanf("%s", Mat[i][j].hospa.endc.munic);
    fLimpar();
    printf("\t Estado:\t");
    scanf("%s", Mat[i][j].hospa.endc.estado);
    fLimpar();
}

//Funcao que faz a reserva a partir do quarto digitado.
//Retorna se o quarto ja estiver reservado ou ocupado.
void fReserva(tipoApto Mat[21][14], int i, int j){
	if (Mat[i][j].status == '.') {
                fCadastro(Mat, i, j);
                Mat[i][j].status = 'R';
                fMapa(Mat);
                printf("\n\n Reserva realizada com sucesso no Andar %d | Quarto %d!\n", i, j);
            } else {
                printf("\n\n Quarto Reservado ou Ocupado! Escolha outro.\n");
            }
}

//Utilizando a mesma estrutura de fCheckIn, essa funcao cancela uma reserva, caso ela tenha sido feita
//pelo mesmo cpf que esta cancelando. Caso o cpf ainda nao esteja cadastrado, a reserva nao existe.
void fCancelarR(tipoApto Mat[21][14], char cpft[15]) {
	int i, j, k, l;
	if (fCPF(Mat, cpft) == 1) {
        fLimpar();
        printf("\n Digite, respectivamente, o andar e o quarto reservados, separados por espaco:\t");
        scanf("%d %d", &i, &j);
        if ((i>0 && i<21) && (j>0 && j<15)) {
            if (Mat[i][j].status == 'O') {
                printf("\n Quarto ja ocupado!\n");
            } else if (strcmp(Mat[i][j].hospa.cpf, cpft) == 0) {
                Mat[i][j].status = '.';
                fMapa(Mat);
                printf("\n Reserva cancelada no Andar %d | Quarto %d!\n", i, j);
            } else {
                printf("\n Quarto errado! Esse CPF reservou outro quarto.\n");
            }
        } else {
            printf("\n Andar e/ou Quarto inexistente. \n");
        }
    } else {
    	printf("\n CPF nao cadastrado!\n");
	}
}

//Funcao que realiza o check-in a partir do parametro recebido "cpft" (temporario), usando as variaveis locais i, j,
//k, l, (sendo k, l duas variaveis tambem temporarias, assim nao altera o valor ja definido para i e j).
void fCheckIn(tipoApto Mat[21][14], char cpft[15]) {
	int i, j, k, l;
	if (fCPF(Mat, cpft) == 1) {
        for (i = 20; i > 0; i--) {
	        for (j = 1; j < 15; j++) {
	            if (strcmp(Mat[i][j].hospa.cpf, cpft) == 0 && Mat[i][j].status == 'R') {
	                Mat[i][j].status = 'O';
	                fMapa(Mat);
	                printf("\n Check-in realizado com sucesso no andar %d quarto %d!\n", i, j);
	                break;
	            }
	        }
   		}
    } else {
        fLimpar();
        printf("\n Digite, respectivamente, o andar e o quarto desejados, separados por espaco:\t");
        scanf("%d %d", &k, &l);
        if ((k>0 && k<21) && (l>0 && l<15)) {
            if (Mat[k][l].status == 'R' || Mat[k][l].status == 'O') {
                printf("\n Quarto ja reservado ou ocupado! Escolha outro.\n");
                fLimpar();
            } else {
    			printf("\n Hospede nao cadastrado, favor realizar o cadastro abaixo: \n");
                i=k;
                j=l;
                fCadastro(Mat, i, j);
                Mat[i][j].status = 'O';
            	fMapa(Mat);
                printf("\n Check-in realizado com sucesso no andar %d quarto %d!\n", i, j);
            }
		} else {
            printf("\n Andar e/ou apartamento inexistente. \n");
    	}
    }
}

//Essa funcao faz o check-out, caso o check-in tenha sido feito
//pelo mesmo cpf que esta saindo.
//Caso o cpf ainda nao esteja cadastrado, o check-out nao acontece e avisa.
void fCheckOut(tipoApto Mat[21][14], char cpft[15]) {
	int i, j;
    int found = 0;

    for (i = 20; i > 0; i--) {
        for (j = 1; j < 15; j++) {
            if (strcmp(Mat[i][j].hospa.cpf, cpft) == 0 && Mat[i][j].status == 'O') {
                Mat[i][j].status = '.';
                fMapa(Mat);
                printf("\n Check-out realizado com sucesso no andar %d quarto %d!\n", i, j);
                found = 1;
                break;
            }
        }
    }
    if (!found) {
        printf("\n CPF nao cadastrado ou o cliente nao fez check-in.\n");
    }
}

//Essa funcao "varre" a matriz e conta todos os 'O' e 'R' encontrados, depois faz o calculo
//para determinar a % de quartos ocupados e a % de quartos reservados.
void fOcupacao(tipoApto Mat[21][14]) {
	int i, j;
	int contO=0;
	int contR=0;
	float ocup, reserv;
	
	for (i = 20; i > 0; i--) {
        for (j = 1; j < 15; j++) {
            if (Mat[i][j].status == 'O') {
                contO++;
            }
            if (Mat[i][j].status == 'R') {
            	contR++;
			}
        }
    }
    
    ocup = (100.0*contO) / (20*14);
    reserv = (100.0*contR) / (20*14);
    
    printf("\n Temos %.2f%% quartos ocupados.\n", ocup);
    printf("\n Temos %.2f%% quartos reservados.\n", reserv);
}

//Essa funcao mostra a situacao de um quarto (ocupado, reservado ou livrre) e, 
//caso nao esteja livre, mostra os dados do hospede.
void fSituacao (tipoApto Mat[21][14]) {
	int i, j;
	fLimpar();
	printf("\n Digite, respectivamente, o andar e o quarto desejados, separados por espaco:\t");
        scanf("%d %d", &i, &j);
	if(Mat[i][j].status == 'O'){
		printf("\n Quarto ocupado pelo hospede %s.", Mat[i][j].hospa.nome);
		printf("\n\n Dados do hospede: ");
		printf(" CPF: %s\t", Mat[i][j].hospa.cpf);
		printf(" Celular: %s\t", Mat[i][j].hospa.cel);
		printf("\n Endereco rua: %s\t", Mat[i][j].hospa.endc.rua );
		printf(" Numero: %s\t", Mat[i][j].hospa.endc.num);
		printf(" CEP: %s\t", Mat[i][j].hospa.endc.cep);
		printf(" Municipio: %s\t", Mat[i][j].hospa.endc.munic);
		printf(" Estado: %s\t\n", Mat[i][j].hospa.endc.estado);
	} else if(Mat[i][j].status == 'R') {
		printf("\n Quarto reservado pelo hospede %s.", Mat[i][j].hospa.nome);
		printf("\n\n Dados do hospede: ");
		printf(" CPF: %s\t", Mat[i][j].hospa.cpf);
		printf(" Celular: %s\t", Mat[i][j].hospa.cel);
		printf("\n Rua: %s\t", Mat[i][j].hospa.endc.rua );
		printf(" Numero: %s\t", Mat[i][j].hospa.endc.num);
		printf(" CEP: %s\t", Mat[i][j].hospa.endc.cep);
		printf(" Municipio: %s\t", Mat[i][j].hospa.endc.munic);
		printf(" Estado: %s\t\n", Mat[i][j].hospa.endc.estado);
	} else {
		printf("\n Quarto livre!\n");
	}
}

//limpa o buffer de entrada do teclado
void fLimpar() {
    char carac;
    while ((carac = getchar()) != '\n' && carac != EOF) {}
}
