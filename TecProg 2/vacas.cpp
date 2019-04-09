#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int ultimoCodigoCadastrado = 0;

int anoAtual = 2019;

		// DECLARANDO FUNÇÕES

	// Instruções do Sistema
void instrucoesPrincipal();

	// Menus 
void menuRelatorio();
void menuCadastro();
void menuPrincipal();

	// 	Relatórios
void relatorioComAbate();
void relatorioSemAbate();
void exibirTodosAnimais();
void exibirAnimaisParaAbate();
void exibirAnimaisSemAbate();

		// DEFININDO REGISTROS

	// Vacas
struct vaca {
		int codigo, nascimento;
		float leite, alimento;
		char abate;
	};
struct vaca vacas[2500];

		// MAIN
main() {
	setlocale(LC_ALL, "Portuguese");
	printf("\n\t\tPara começar, digite o ano atual:  ");
	scanf("%d", &anoAtual);
	instrucoesPrincipal();
	menuPrincipal();
}

		// DEFININDO A LÓGICA DAS FUNÇÕES
		
	// Instruções
void instrucoesPrincipal() {
	
}
	
	// Menus
void menuRelatorio() {
	char resposta = 'x';
	while (resposta != '0' && resposta != 'S') {
		printf("\n\t########################################################");
		printf("\n\t#         Menu Relatório     (Apenas número)           #");
		printf("\n\t########################################################");
		printf("\n\t#   1) Incluindo animais destinados ao abate           #");
		printf("\n\t#   2) Desconsiderando animais destinados ao abate     #");
		printf("\n\t#   3) Exibir todos os animais cadastrados             #");
		printf("\n\t#   4) Exibir apenas animais destinados ao abate       #");
		printf("\n\t#   5) Exibir apenas animais não destinados ao abate   #");
		printf("\n\t#   0) Voltar                                          #");
		printf("\n\t########################################################");
		printf("\n\t#");
		printf("\n\t###   Opção:  ");
fflush(stdin);
		scanf("%c", &resposta);
		resposta = toupper(resposta);
		switch(resposta) {
			case '1':
				relatorioComAbate();
				break;
			case '2':
				relatorioSemAbate();
				break;
			case '3':
				exibirTodosAnimais();
				break;
			case '4':
				exibirAnimaisParaAbate();
				break;
			case '5':
				exibirAnimaisSemAbate();
				break;
			case '0':
				break;
			default:
				printf("\n\t#####   Opção inválida! Escolha uma das opções apresentadas!\n");
				break;
		}
	}
}

void menuCadastro() {
	char resposta = 'x';
	while (resposta != '0' && resposta != 'N') {
		printf("\n\t##########################################");
		printf("\n\t#     Menu Cadastro");
		printf("\n\t#########################");
		printf("\n\t#   Código da vaca:");
		vacas[ultimoCodigoCadastrado].codigo = ultimoCodigoCadastrado;
		printf("\n\t#     %d", ultimoCodigoCadastrado);
		printf("\n\t#   Leite Produzido (Litros por semana)");
		printf("\n\t###   ");
		scanf("%f", &vacas[ultimoCodigoCadastrado].leite);
		printf("\t#   Alimento consumido (kg por semana)");
		printf("\n\t###   ");
		scanf("%f", &vacas[ultimoCodigoCadastrado].alimento);
		printf("\t#   Ano de nascimento:");
		printf("\n\t###   ");
		scanf("%d", &vacas[ultimoCodigoCadastrado].nascimento);
		
		bool maisDe5Anos = anoAtual - vacas[ultimoCodigoCadastrado].nascimento > 5;
		bool produzMenosDe40Litros = vacas[ultimoCodigoCadastrado].leite < 40;
		bool comeDemais = vacas[ultimoCodigoCadastrado].leite >= 50 && vacas[ultimoCodigoCadastrado].leite <= 70 && vacas[ultimoCodigoCadastrado].alimento/7 > 50;
		
		if( maisDe5Anos || produzMenosDe40Litros || comeDemais){
			vacas[ultimoCodigoCadastrado].abate = 'S';
		} else {
			vacas[ultimoCodigoCadastrado].abate = 'N';
		}
		printf("\t#   Destinado ao abate:");
		printf("\n\t#     %c", vacas[ultimoCodigoCadastrado].abate);
		printf("\n\t##########################################");
		ultimoCodigoCadastrado++;
		printf("\n");
		printf("\n\t (!) Salvo com sucesso! (!)");
		printf("\n");
		printf("\n\t##########################################");
		printf("\n\t#     Deseja cadastrar outra vaca?");
		printf("\n");
		printf("\n\t#   1) Sim");
		printf("\n\t#   0) Não");
		printf("\n\t#     Opção:  ");
fflush(stdin);
		scanf("%c", &resposta);
		resposta = toupper(resposta);
	}
	
	
	
}

void menuPrincipal() {
	char resposta = 'x';
	while (resposta != '0' && resposta != 'S') {
		printf("\n\t##########################");
		printf("\n\t#     Menu Principal     #");
		printf("\n\t##########################");
		printf("\n\t#   1) Cadastrar Vacas   #");
		printf("\n\t#   2) Relatório         #");
		printf("\n\t#   0) Sair              #");
		printf("\n\t##########################");
		printf("\n\t#");
		printf("\n\t###   Opção:  ");
fflush(stdin);
		scanf("%c", &resposta);
		resposta = toupper(resposta);
		switch(resposta) {
			case '1':
			case 'C':
				menuCadastro();
				break;
			case '2':
			case 'R':
				menuRelatorio();
				break;
			case '0':
			case 'S':
				break;
			default:
				printf("\n\t#####   Opção inválida! Escolha uma das opções apresentadas!\n");
				break;
		}
	}
}

	// Relatórios
void relatorioComAbate(){
	
	int i=0, animaisConsiderados=0;
	float leiteTotal=0, alimentoTotal=0;
	for (i=0; i<ultimoCodigoCadastrado; i++){
		leiteTotal += vacas[i].leite;
		alimentoTotal += vacas[i].alimento;
		animaisConsiderados++;
	}
	
	printf("\n\t\t#############################################");
	printf("\n\t\t#       Relatório incluindo abate:");
	printf("\n\t\t#");
	printf("\n\t\t#   Leite produzido por semana:    \t%.2f", leiteTotal);
	printf("\n\t\t#   Alimento consumido por semana: \t%.2f", alimentoTotal);
	printf("\n\t\t#   Total de animais considerados: \t%d", animaisConsiderados);
	printf("\n\t\t#############################################");
	
}

void relatorioSemAbate(){
	
	int i=0, animaisConsiderados=0;
	float leiteTotal=0, alimentoTotal=0;
	for (i=0; i<ultimoCodigoCadastrado; i++){
		if (vacas[i].abate != 'S') {
			leiteTotal += vacas[i].leite;
			alimentoTotal += vacas[i].alimento;
			animaisConsiderados++;
		}
	}
	
	printf("\n\t\t#############################################");
	printf("\n\t\t#       Relatório desconsiderando abate:");
	printf("\n\t\t#");
	printf("\n\t\t#   Leite produzido por semana, em L:       \t%.2f", leiteTotal);
	printf("\n\t\t#   Alimento consumido por semana, em kg:   \t%.2f", alimentoTotal);
	printf("\n\t\t#   Total de animais considerados:          \t%d", animaisConsiderados);
	printf("\n\t\t#############################################");
	
}

void exibirTodosAnimais(){
	int i;
	for (i=0; i<ultimoCodigoCadastrado; i++) {
		printf("\n\t\t#############################################");
		printf("\n\t\t#   Código:   %d", vacas[i].codigo);
		printf("\n\t\t#   Leite produzido por semana:   %.2f", vacas[i].leite);
		printf("\n\t\t#   Alimento consumido por semana:   %.2f", vacas[i].alimento);
		printf("\n\t\t#   Ano de nascimento:   %d", vacas[i].nascimento);
		printf("\n\t\t#   Destinado ao abate:   %c", vacas[i].abate);
		printf("\n\t\t#############################################");
		printf("\n");
	}
	if (ultimoCodigoCadastrado == 0){
		printf("\n\t\tNenhum animal cadastrado!");
		printf("\n");
	}
}

void exibirAnimaisParaAbate(){
	int i, encontrados = 0;
	for (i=0; i<ultimoCodigoCadastrado; i++) {
		if (vacas[i].abate == 'S') {
			printf("\n\t\t#############################################");
			printf("\n\t\t#   Código:   %d", vacas[i].codigo);
			printf("\n\t\t#   Leite produzido por semana:   %.2f", vacas[i].leite);
			printf("\n\t\t#   Alimento consumido por semana:   %.2f", vacas[i].alimento);
			printf("\n\t\t#   Ano de nascimento:   %d", vacas[i].nascimento);
			printf("\n\t\t#   Destinado ao abate:   %c", vacas[i].abate);
			printf("\n\t\t#############################################");
			printf("\n");
			encontrados++;
		}
	}
	if (ultimoCodigoCadastrado == 0){
		printf("\n\t\tNenhum animal cadastrado!");
		printf("\n");
	} else if (encontrados == 0){
		printf("\n\t\tNenhum animal encontrado!");
		printf("\n");
	}
}

void exibirAnimaisSemAbate(){
	int i, encontrados = 0;
	for (i=0; i<ultimoCodigoCadastrado; i++) {
		if (vacas[i].abate == 'N') {
			printf("\n\t\t#############################################");
			printf("\n\t\t#   Código:   %d", vacas[i].codigo);
			printf("\n\t\t#   Leite produzido por semana:   %.2f", vacas[i].leite);
			printf("\n\t\t#   Alimento consumido por semana:   %.2f", vacas[i].alimento);
			printf("\n\t\t#   Ano de nascimento:   %d", vacas[i].nascimento);
			printf("\n\t\t#   Destinado ao abate:   %c", vacas[i].abate);
			printf("\n\t\t#############################################");
			printf("\n");
			encontrados++;
		}
	}
	if (ultimoCodigoCadastrado == 0){
		printf("\n\t\tNenhum animal cadastrado!");
		printf("\n");
	} else if (encontrados == 0){
		printf("\n\t\tNenhum animal encontrado!");
		printf("\n");
	}
}
