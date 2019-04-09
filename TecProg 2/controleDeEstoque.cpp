#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <time.h>

// Mude esse texto com o nome da sua empresa
char nomeDaEmpresa[20] = "<Nome_da_empresa>";

// Variável para salvar o último código gerado, para não perder esse valor ao recadastrar produtos excluídos.
int saveLastCodeGenerated = 0;

// Variável usada para cadastrar o próximo produto (nunca se repete).
int lastCodeGenerated = 0;

	// Informações do produto:
// Código
int prodCode[5000];
// Descrição
char prodDesc[5000][500];
// Departamento
char prodDept[5000][50];
// Quantidade em estoque
int prodInvCount[5000];
// Quantidade mínima em estoque
int prodInvMinCountWarn[5000];
// Preço unitário
float prodUnitPrice[5000];

// Lixeira do Sistema. Salva o todos os códigos dos produtos excluídos e Recadastra esses códigos na próxima vez que entrar no Menu Cadastro
int codProdutosExcluidos[5000];
int proximoLugarNaLixeira = 0;

	// Teste Automatizado
// Quantos produtos serão cadastrados ao inicializar o sistema.
int cadastrosAutomaticos = 300;
// Lógica do cadastro dos produtos
cadastrarAutomaticamente() {
	int i;	
	srand(time(NULL));
	for (i=0; i<cadastrosAutomaticos; i++) {
		char desc[6]="desc ", dept[6]="dept ";
		char string[10];
		itoa(i, string, 10);
		prodCode[i] = lastCodeGenerated;
		strcpy(prodDesc[i], strcat(desc, string));
		strcpy(prodDept[i], strcat(dept, string));
		prodInvCount[i] = (rand() % cadastrosAutomaticos * 10);
		prodInvMinCountWarn[i] = (rand() % (cadastrosAutomaticos * 10)) / 2;
		prodUnitPrice[i] = (rand() % 100);
		lastCodeGenerated++;
		saveLastCodeGenerated = lastCodeGenerated;
	}
	if (i>0) {
		printf("\t             #########################################");
		printf("\n\t    ###############################################################");
		printf("\n\t#### (!) Efetuados > %d < cadastros automáticos com sucesso. (!) ####", i);
		printf("\n\t    ###############################################################");
		printf("\n\t             #########################################\n\n");
	}
}

			// DECLARAÇÃO
			
		// Instruções
	
void instrucoesDoSistema();
void instrucoesBasicas();
void instrucoesPrincipal();
void instrucoesCadastro();

		// Funções
	



// FUNÇÕES

bool gerarRelatorio() {
	printf("\n\n\t\tInforme o nome do arquivo para salvar o relatorio: ");
	char fileName[50];
fflush(stdin);
	gets(fileName);
	FILE *relatorio;
	relatorio = fopen(fileName, "w");
}
bool codigoExiste(int codigo) {
	int i = 0, existe;
	while ( i<proximoLugarNaLixeira && existe != true) {
		if(codigo == codProdutosExcluidos[i] || codigo > lastCodeGenerated) {
			existe = false;
		} else {
			existe = true;
		}
		i++;
	}
	if(codigo > lastCodeGenerated) {
			existe = false;
	}
	return existe;
}
int estadoDeEstoque(int codigoDoProduto, char exibir) {
	int estado = 0;
	char stringEstado[20];
	if (exibir == 's' || exibir == 'S') { printf("Estado de estoque: "); }
	if (prodInvCount[codigoDoProduto] > prodInvMinCountWarn[codigoDoProduto]) {
		strcpy(stringEstado, "Aceitável.");
		estado = 1;
	}
	if (prodInvCount[codigoDoProduto] == prodInvMinCountWarn[codigoDoProduto]) {
		strcpy(stringEstado, "Atenção!");
		estado = 2;
	}
	if (prodInvCount[codigoDoProduto] < prodInvMinCountWarn[codigoDoProduto]) {
		strcpy(stringEstado, "(!) CRÍTICO! (!)");
		estado = 3;
	}
	if (exibir == 's' || exibir == 'S') { printf("%s", stringEstado); }
	if (exibir == 's' || exibir == 'S') { printf("   ( %d / %d )\n", prodInvCount[codigoDoProduto], prodInvMinCountWarn[codigoDoProduto]); }
	return estado;
}
exibirCadastro(int codigoDoProduto) {
	
	if(codigoExiste(codigoDoProduto)){
		printf("\n\n\t\tCódigo do produto: %d", prodCode[codigoDoProduto]);
		printf("\n\t\tDescrição: %s", prodDesc[codigoDoProduto]);
		printf("\n\t\tDepartamento: %s", prodDept[codigoDoProduto]);
		printf("\n\t\tQuantidade em estoque: %d", prodInvCount[codigoDoProduto]);
		printf("\n\t\tEstoque mínimo: %d", prodInvMinCountWarn[codigoDoProduto]);
		printf("\n\t\tPreço unitário: %.2f", prodUnitPrice[codigoDoProduto]);
		printf("\n\t\t");	estadoDeEstoque(codigoDoProduto, 's');
	}
}
int buscarTrecho(char trecho[], char texto[]) {
	int a=0, b=0, c=0, achei = 0;
	while (texto[c]!='\0' && achei == 0){
		a=c;
		if (texto[a] == trecho[b] && achei == 0) {
			if (trecho[b+1] == '\0'){
				achei = 1;
			}
			b++;
		} else {
			b=0;
		}
		c++;
	}
	return achei;
}
exibirTodosCadastros() {
	int i;
	for (i=0; i<lastCodeGenerated; i++) {
		exibirCadastro(i);
	}
}
consultarPorEstadoDeEstoque() {
	printf("\n\n\tQual estado deseja buscar? (APENAS NÚMERO)");
	printf("\n");
	printf("\n\t1) Aceitável.");
	printf("\n\t2) Atenção!");
	printf("\n\t3) CRÍTICO!");
	printf("\n");
	int estado = 0;
	while (estado == 0) {
		printf("\n\t      Opção: ");
		scanf("%d", &estado);
		if(estado != 1 && estado != 2 && estado != 3){
			printf("\n\t(!) Opção inválida. Escolha uma das opções apresentadas. (APENAS NÚMERO) (!)\n");
			estado = 0;
		}
	}
	int i, achei=0;
	for (i=0; i<lastCodeGenerated; i++) {
		if(estadoDeEstoque(i, 'n') == estado) {
			exibirCadastro(i);
			achei = 1;
		}
	}
	if (achei == 0){
		printf("\n\t\tNenhum produto encontrado com esse estado de estoque.");
	}
}
int contarDigitos(float numero){
	int digitos;
	if (numero > -10 && numero < 10){
		digitos = 1;
	} else if (numero > -100 && numero < 100){
		digitos = 2;
	} else if (numero > -1000 && numero < 1000){
		digitos = 3;
	} else if (numero > -10000 && numero < 10000){
		digitos = 4;
	} else if (numero > -100000 && numero < 100000){
		digitos = 5;
	} else if (numero > -1000000 && numero < 1000000){
		digitos = 6;
	} else if (numero > -10000000 && numero < 10000000){
		digitos = 7;
	} else if (numero > -100000000 && numero < 100000000){
		digitos = 8;
	} else if (numero > -1000000000 && numero < 1000000000){
		digitos = 9;
	}
	return digitos;
}
consultarPorDescricao() {
	int produtos = 0;
	int i;
	char busca[500];
	printf("\n\tDigite a descrição buscada:");
	printf("\n\t\t");
fflush(stdin);
	gets(busca);
	for (i=0; i<lastCodeGenerated; i++){
		if(buscarTrecho(busca, prodDesc[i]) == 1){
			exibirCadastro(i);
			produtos++;
		}
	}
	if (produtos == 0) {
		printf("\n\n\t\t\tNenhum produto encontrado com essa descrição.");
	}
}
consultarPorDepartamento() {
	int produtos = 0;
	int i;
	char busca[500];
	printf("\n\tDigite o departamento buscado:");
	printf("\n\t\t");
fflush(stdin);
	gets(busca);
	for (i=0; i<lastCodeGenerated; i++){
		if(buscarTrecho(busca, prodDept[i]) == 1){
			exibirCadastro(i);
			produtos++;
		}
	}
	if (produtos == 0) {
		printf("\n\n\t\tNenhum produto encontrado com esse departamento.");
	}
}
int consultarPorCodigo() {
	int codigo, existe = 0;
	while (existe == 0){
		printf("\n\n\t\tInforme o codigo do produto: ");
fflush(stdin);
		scanf("%d", &codigo);
		if (codigoExiste(codigo)){
		printf("\n\t\t     Informações do produto de código %d", codigo);
			exibirCadastro(codigo);
			existe = 1;
			return codigo;
		} else {
			printf ("\n\t\t (!) Produto não cadastrado ou excluído! (!)");
			existe = 0;
		}
	}
}
entradaDeMercadoria() {
	int codigoDoProduto = consultarPorCodigo();
	int entrada = 0;
	printf("\n\tQuantidade de produtos comprados: ");
	scanf("%d", &entrada);
	prodInvCount[codigoDoProduto] += entrada;
	printf("\n\t\tNova quantidade em estoque: %d", prodInvCount[codigoDoProduto]);
	printf("\n\t\t");	estadoDeEstoque(codigoDoProduto, 's');
}
saidaDeMercadoria() {
	int codigoDoProduto = consultarPorCodigo();
	int saida = 0;
	printf("\n\tQuantidade de produtos vendidos: ");
	scanf("%d", &saida);
	prodInvCount[codigoDoProduto] = prodInvCount[codigoDoProduto] - saida;
	printf("\n\t\tNova quantidade em estoque: %d", prodInvCount[codigoDoProduto]);
	printf("\n\t\t");	estadoDeEstoque(codigoDoProduto, 's');
}
relatorioCritico(){
	printf("\n\t|---------------------|---------------------|-----------------|");
	printf("\n\t|      Descrição      |   Qtde em Estoque   |   Qtde mínima   |");
	printf("\n\t|---------------------|---------------------|-----------------|");
	for (int i=0; i<lastCodeGenerated; i++) {
		if(estadoDeEstoque(i, 'n') == 3) {
			printf("\n\t| ");
			printf("%s", prodDesc[i]);
			for(int j=0; j<20-strlen(prodDesc[i]); j++){
				printf(" ");
			}
			printf("|");
			int espacos1 = (20 - contarDigitos(prodInvCount[i])), espacosNaTela1 = 0, metadeEspacos1 = (espacos1 / 2);
			for (int j=0; j<=metadeEspacos1; j++) {
				printf(" ");
			}
			printf("%d", prodInvCount[i]);
			for (int j=0; j<metadeEspacos1; j++) {
				printf(" ");
				espacosNaTela1++;
			}
			if (contarDigitos(prodInvCount[i]) % 2 == 1){
				printf(" ");
				espacosNaTela1++;
			}
			printf("|");
			int espacos2 = (17 - contarDigitos(prodInvMinCountWarn[i])), espacosNaTela2 = 0, metadeEspacos2 = (espacos2 / 2);
			
			for (int j=0; j<=metadeEspacos2-1; j++) {
				printf(" ");
				espacosNaTela2++;
			}
			printf("%d", prodInvMinCountWarn[i]);
			if(contarDigitos(prodInvMinCountWarn[i]) % 2 == 1){
				metadeEspacos2--;
			}
			for (int j=0; j<=metadeEspacos2; j++) {
				printf(" ");
				espacosNaTela2++;
			}
			printf("|");
		}
	}
	printf("\n\t|---------------------|---------------------|-----------------|");
}
relatorioTotal(){
	printf("\n\t|---------------------|---------------------|------------------|-----------------|");
	printf("\n\t|      Descrição      |   Qtde em Estoque   |  Preço unitário  |   Preço Total   |");
	printf("\n\t|---------------------|---------------------|------------------|-----------------|");
	double totalTudo = 0;
	for (int i=0; i<lastCodeGenerated; i++) {
		// Descrição
		printf("\n\t| ");
		printf("%s", prodDesc[i]);
		for(int j=0; j<20-strlen(prodDesc[i]); j++){
			printf(" ");
		}
		printf("|");
		
		// Qtde em Estoque
		int espacos1 = (20 - contarDigitos(prodInvCount[i])), espacosNaTela1 = 0, metadeEspacos1 = (espacos1 / 2);
		for (int j=0; j<=metadeEspacos1-2; j++) {
			printf(" ");
		}
		printf("%d", prodInvCount[i]);
		for (int j=0; j<metadeEspacos1+2; j++) {
			printf(" ");
			espacosNaTela1++;
		}
		if (contarDigitos(prodInvCount[i]) % 2 == 1){
			printf(" ");
			espacosNaTela1++;
		}
		printf("|");
		
		// Preço unitário
		int espacos2 = (16 - contarDigitos(prodUnitPrice[i])), espacosNaTela2 = 0, metadeEspacos2 = (espacos2 / 2);
		for (int j=0; j<=metadeEspacos2-1; j++) {
			printf(" ");
			espacosNaTela2++;
		}
		printf("%.2f", prodUnitPrice[i]);
		for (int j=1; j<metadeEspacos2; j++) {
			printf(" ");
			espacosNaTela2++;
		}
		if (contarDigitos(prodUnitPrice[i]) % 2 == 1){
			printf(" ");
			espacosNaTela2++;
		}
		printf("|");
		
		// Preço Total
		float prodTotalPrice = prodInvCount[i] * prodUnitPrice[i];
		int espacos3 = (16 - contarDigitos(prodInvCount[i] * prodUnitPrice[i])), espacosNaTela3 = 0, metadeEspacos3 = (espacos3 / 2);
		for (int j=0; j<=metadeEspacos3-1; j++) {
			printf(" ");
			espacosNaTela3++;
		}
		printf("%.2f", prodTotalPrice);
		if (contarDigitos(prodTotalPrice) % 2 == 0){
			metadeEspacos3--;
		}
		for (int j=0; j<metadeEspacos3-1; j++) {
			printf(" ");
			espacosNaTela3++;
		}
		printf("|");
		totalTudo += prodTotalPrice;
	}
	printf("\n\t|---------------------|---------------------|------------------|-----------------|");
	printf("\n\t|   Valor acumulado de todos produtos em Estoque: ");
	printf("%.2f", totalTudo);
	for (int j=0; j<28-contarDigitos(totalTudo); j++){
	printf(" ");
	}
	printf("|");
	printf("\n\t|---------------------|---------------------|------------------|-----------------|");
}

	// ALTERAÇÃO
alterarPorCodigo() {
	int codigo = consultarPorCodigo();
	int iAlteracao = -9999;
	float fAlteracao = -9999;
	char sAlteracao[500];
	printf("\n\n\t\tAbrindo produto para alteração...");
	printf("\n\t\tPara alterar, insira um novo valor para o campo.");
	printf("\n\t\tCaso não queira alterar o campo, deixe-o em branco para textos, e escreva \"-9999\" para números.");
	printf("\n");
	printf("\n\t\tCódigo do produto: %d", prodCode[codigo]);
	printf("\n\t\tDescrição atual:");
	printf("\n\t\t%s", prodDesc[codigo]);
	printf("\n\t\tNova descrição:");
	printf("\n\t\t");
fflush(stdin);
	gets(sAlteracao);
	if (strcmp(sAlteracao, "") != 0){
		strcpy(prodDesc[codigo], sAlteracao);
		printf("\nCampo alterado.\n");
	} else {
		printf("\nCampo ignorado.\n");
	}
	strcpy(sAlteracao, "");
	printf("\n\t\tDepartamento atual:");
	printf("\n\t\t%s", prodDept[codigo]);
	printf("\n\t\tNovo departamento:");
	printf("\n\t\t");
fflush(stdin);
	gets(sAlteracao);
	if (strcmp(sAlteracao, "") != 0){
		strcpy(prodDept[codigo], sAlteracao);
		printf("\nCampo alterado.\n");
	} else {
		printf("\nCampo ignorado.\n");
	}
	strcpy(sAlteracao, "");
	printf("\n\t iAlteração antes: %d", iAlteracao);
	printf("\n\t\tEstoque atual:");
	printf("\n\t\t%d", prodInvCount[codigo]);
	printf("\n\t\tNovo estoque:");
	printf("\n\t\t");
fflush(stdin);
	scanf("%d", &iAlteracao);
	printf("\n\t iAlteração depois: %d", iAlteracao);
	if (iAlteracao != -9999){
		prodInvCount[codigo] = iAlteracao;
		printf("\n\t\tCampo alterado");
	} else {
		printf("\n\t\tCampo ignorado");
	}
	iAlteracao = -9999;
	printf("\n\t iAlteração antes: %d", iAlteracao);
	printf("\n\t\tEstoque mínimo atual:");
	printf("\n\t\t%d", prodInvMinCountWarn[codigo]);
	printf("\n\t\tNovo estoque mínimo:");
	printf("\n\t\t");
fflush(stdin);
	scanf("%d", &iAlteracao);
	printf("\n\t iAlteração depois: %d", iAlteracao);
	if (iAlteracao != -9999){
		prodInvMinCountWarn[codigo] = iAlteracao;
		printf("\n\t\tCampo alterado");
	} else {
		printf("\n\t\tCampo ignorado");
	}
	iAlteracao = -9999;
	printf("\n\t fAlteração antes: %.2f", fAlteracao);
	printf("\n\t\tPreço unitário atual:");
	printf("\n\t\t%.2f", prodUnitPrice[codigo]);
	printf("\n\t\tNovo preço unitário:");
	printf("\n\t\t");
fflush(stdin);
	scanf("%f", &fAlteracao);
	printf("\n\t fAlteração depois: %.2f", fAlteracao);
	if (fAlteracao != -9999){
		prodUnitPrice[codigo] = fAlteracao;
		printf("\n\t\tCampo alterado");
	} else {
		printf("\n\t\tCampo ignorado");
	}
}
	// EXCLUSÃO
int codigoParaExclusao = -1;
excluirPorCodigo() {
	char userInput = 'z';
	while(userInput != '0' && userInput != 'C') {
		int codExiste = 0;
		while(codExiste == 0 ) {
			codigoParaExclusao = consultarPorCodigo();
			if (codigoExiste(codigoParaExclusao)){
				codExiste = 1;
			}
		}
		printf("\n\t\tDeseja realmente excluir o produto?");
		printf("\n\t\t5) deleTar");
		printf("\n\t\t0) Cancelar");
		printf("\n\t\t          Opção: ");
fflush(stdin);
		scanf("%c", &userInput);
		userInput = toupper(userInput);
		switch(userInput){
			case '5':
			case 'T':
				printf("\n\n\t (!!!) VOCÊ TEM CERTEZA ABSOLUTA QUE DESEJA EXCLUIR O PRODUTO? (!!!)");
				printf("\n\t (!!!) ESTA OPERAÇÃO NÃO PODE SER DESFEITA! (!!!)");
				printf("\n\t\t6) Sim");
				printf("\n\t\t0) Cancelar");
				printf("\n\t\t          Opção: ");
fflush(stdin);
				scanf("%c", &userInput);
				userInput = toupper(userInput);
				if (userInput == '6' || userInput == 'S') {
					strcpy(prodDesc[codigoParaExclusao], "");
					strcpy(prodDept[codigoParaExclusao], "");
					prodInvCount[codigoParaExclusao] = 0;
					prodInvMinCountWarn[codigoParaExclusao] = 0;
					prodUnitPrice[codigoParaExclusao] = 0;
					codProdutosExcluidos[proximoLugarNaLixeira] = codigoParaExclusao;
					proximoLugarNaLixeira++;
					printf("\n\t\t\tExclusão concluída.");
				}
				printf("\n\t\tDeseja excluir outro produto informando seu código?");
				printf("\n");
				printf("\n\t\t1) Sim");
				printf("\n\t\t0) Não");
				printf("\n\t\t     Opção: ");
fflush(stdin);
				scanf("%c", &userInput);
				userInput = toupper(userInput);
				switch (userInput){
					case '1':
					case 'S':
						break;
					case '0':
					case 'N':
						userInput = '0';
						break;
				}
				break;
		}
	}
}

// MENUS
menuConsulta() {
	char userOpt;
	while (userOpt != '0' && userOpt != 'V') {
		printf("\n");
		printf("\n\tMenu Principal > Consulta");
		printf("\n");
		printf("\n\t1) Entrada de mercadoria");
		printf("\n\t2) Saída de mercadoria");
		printf("\n\t3) consultar por Código");
		printf("\n\t4) consultar por Descrição");
		printf("\n\t5) consultar por dePartamento");
		printf("\n\t6) consultar por estado de estoQue");
		printf("\n\t7) exibir Todos os cadastros");
		printf("\n\t0) Voltar");
		printf("\n");
		printf("\n\t       Opção: ");
fflush(stdin);
		scanf("%c", &userOpt);
		userOpt = toupper(userOpt);
				
		switch (userOpt) {
			case '1':
			case 'E':
				entradaDeMercadoria();
				break;
			case '2':
			case 'S':
				saidaDeMercadoria();
				break;
			case '3':
			case 'C':
				consultarPorCodigo();
				break;
			case '4':
			case 'D':
				consultarPorDescricao();
				break;
			case '5':
			case 'P':
				consultarPorDepartamento();
				break;
			case '6':
			case 'Q':
				consultarPorEstadoDeEstoque();
				break;
			case '7':
			case 'T':
				exibirTodosCadastros();
				break;
			case '0':
			case 'V':
				break;
			default:
				printf("\n\n (!) Opção inválida. Selecione uma das opções. (!)\n");
				break;
		}
	}
}

// FUNÇÕES
	// ALTERAÇÃO
buscarParaAlterar() {
	menuConsulta();
	alterarPorCodigo();
}
	// EXCLUSÃO
buscarParaExcluir() {
	menuConsulta();
	excluirPorCodigo();
}
int existeExcluido() {
	int i = 0, existeRemovido = 0;
	do {
		if (codProdutosExcluidos[i] != -1) {
			existeRemovido = 1;
		}
		i++;
	} while (i<proximoLugarNaLixeira && existeRemovido == 0);
	return existeRemovido;
}
// MENUS
menuCadastro() {
	char userOpt;
	while (userOpt != '0' && userOpt !='N') {
		int i=0, recadastrando = 0, recadastro = -1;
		while (i<lastCodeGenerated && recadastrando == 0){
			if (codProdutosExcluidos[i] != -1 && lastCodeGenerated > codProdutosExcluidos[i]){
				saveLastCodeGenerated = lastCodeGenerated;
				lastCodeGenerated = codProdutosExcluidos[i];
				recadastro = i;
				recadastrando = 1;
			} else {
				lastCodeGenerated = saveLastCodeGenerated;
			}
			i++;
		}
		printf("\n  # # # # # # # # # # # # # # # # #");
		printf("\n  # #       Menu Principal      # #");
		printf("\n  # # # # # # # # # # # # # # # # # #");
		if (recadastrando == 1) {
			printf("\n    # #         Recadastro        # #");
		} else {
			printf("\n    # #          Cadastro         # #");
		}
		printf("\n    # # # # # # # # # # # # # # # # #");
		printf("\n    #                               #");
		printf("\n    #   > Código do produto:  %d", lastCodeGenerated);
		if (lastCodeGenerated >= 0 && lastCodeGenerated < 10) {
			printf("     #");
		} else if (lastCodeGenerated >= 10 && lastCodeGenerated < 100) {
			printf("    #");
		} else if (lastCodeGenerated >= 100 && lastCodeGenerated < 1000) {
			printf("   #");
		} else {
			printf("  #");
		}
		printf("\n    #   > Descrição do produto:     #");
		printf("\n    # # #   ");
		strcpy(prodDesc[lastCodeGenerated], "");
		while (strcmp(prodDesc[lastCodeGenerated], "") == 0) {
fflush(stdin);
			gets(prodDesc[lastCodeGenerated]);
			if (strcmp(prodDesc[lastCodeGenerated], "") == 0) {
				printf("      #     (!) O campo não pode ser vazio! (!)");
				printf("\n    # # #   ");
			}
		}
		printf("    #   > Departamento do produto:  #");
		printf("\n    # # #   ");
		strcpy(prodDept[lastCodeGenerated], "");
		while (strcmp(prodDept[lastCodeGenerated], "") == 0) {
fflush(stdin);
			gets(prodDept[lastCodeGenerated]);
			if (strcmp(prodDept[lastCodeGenerated], "") == 0) {
				printf("      #     (!) O campo não pode ser vazio! (!)");
				printf("\n    # # #   ");
			}
		}
		printf("    #   > Quantidade em estoque:    #");
		printf("\n    # # #   ");
		prodInvCount[lastCodeGenerated] = 0;
		while (prodInvCount[lastCodeGenerated] == 0) {
fflush(stdin);
			scanf("%d", &prodInvCount[lastCodeGenerated]);
			if (prodInvCount[lastCodeGenerated] == 0) {
				printf("      #     (!) O campo não pode ser zero! (!)");
				printf("\n    # # #   ");
			}
		}
		printf("    #   > Quantidade mínima:        #");
		printf("\n    # # #   ");
		prodInvMinCountWarn[lastCodeGenerated] = 0;
		while (prodInvMinCountWarn[lastCodeGenerated] == 0) {
fflush(stdin);
			scanf("%d", &prodInvMinCountWarn[lastCodeGenerated]);
			if (prodInvMinCountWarn[lastCodeGenerated] == 0) {
				printf("      #     (!) O campo não pode ser zero! (!)");
				printf("\n    # # #   ");
			}
		}
		printf("    #   > Preço unitário:           #");
		printf("\n    # # #   ");
		prodUnitPrice[lastCodeGenerated] = 0;
		while (prodUnitPrice[lastCodeGenerated] == 0) {
fflush(stdin);
			scanf("%f", &prodUnitPrice[lastCodeGenerated]);
			if (prodUnitPrice[lastCodeGenerated] == 0) {
				printf("      #     (!) O campo não pode ser zero! (!)");
				printf("\n    # # #   ");
			}
		}
		float precoTotal = prodUnitPrice[lastCodeGenerated]*prodInvCount[lastCodeGenerated];
		printf("    #   > Preço total:  %.2f", precoTotal);
		if (precoTotal >= 0 && precoTotal < 10) {
			printf("        #");
		} else if (precoTotal >= 10 && precoTotal < 100) {
			printf("       #");
		} else if (precoTotal >= 100 && precoTotal < 1000) {
			printf("      #");
		} else if (precoTotal >= 1000 && precoTotal < 10000) {
			printf("     #");
		} else if (precoTotal >= 10000 && precoTotal < 100000) {
			printf("    #");
		} else {
			printf("   #");
		}
		printf("\n    # # # # # # # # # # # # # # # # #");
		
		userOpt = 'z';
		while (userOpt != '1' && userOpt != 'S' && userOpt != '0' && userOpt != 'C') {
			printf("\n      #  1) Salvar produto      #");
			printf("\n      #  0) Cancelar cadastro   #");
			printf("\n      # # # # # # # # # # # # # #");
			printf("\n      #");
			printf("\n      # # #     Opção: ");
fflush(stdin);
			scanf("%c", &userOpt);
			userOpt = toupper(userOpt);
			printf("      #");
			switch (userOpt) {
				case '1':
				case 'S':
					if (recadastrando == 1){
						prodCode[lastCodeGenerated] = lastCodeGenerated;
						codProdutosExcluidos[recadastro] = -1;
						lastCodeGenerated = saveLastCodeGenerated;
						if (existeExcluido() == 0) {
							proximoLugarNaLixeira = 0;
						}
					} else {
						prodCode[lastCodeGenerated] = lastCodeGenerated;
						lastCodeGenerated++;
						saveLastCodeGenerated = lastCodeGenerated;
						if (existeExcluido() == 0) {
							proximoLugarNaLixeira = 0;
						}
					}
					printf("\n      #     (!) Produto salvo com sucesso. (!)");
					printf("\n      #");
					break;
				case '0':
				case 'C':
					if (recadastrando == 1) {
						lastCodeGenerated = saveLastCodeGenerated;
					}
					printf("\n      #     (!) Produto cancelado com sucesso. (!)");
					printf("\n      #");
					break;
				default:
					printf("\n      #     (!) Opção inválida. Escolha uma das opções apresentadas. (!)");
					printf("\n      #");
					break;
			}
		}
		userOpt = 'z';
		while (userOpt != '1' && userOpt != 'S' && userOpt != '0' && userOpt != 'N') {
			printf("\n    # # # # # # # # # # # # # # # # # # #");
			printf("\n    #  Deseja cadastrar outro produto?  #");
			printf("\n    #                                   #");
			printf("\n    #  1) Sim                           #");
			printf("\n    #  0) Não                           #");
			printf("\n    # # # # # # # # # # # # # # # # # # #");
			printf("\n    #");
			printf("\n    # # # # #       Opção: ");
fflush(stdin);
			scanf("%c", &userOpt);
			userOpt = toupper(userOpt);
			if (userOpt == '1' || userOpt == 'S'){
				printf("      #");
			}
			if (userOpt != '1' && userOpt != 'S' && userOpt != '0' && userOpt != 'N') {
				printf("\n (!) Opção inválida. Escolha uma das opções apresentadas. (!)");
				printf("\n");
			}
		}
	}
}
menuAlteracao() {
	char userOpt;
	while (userOpt != '0' && userOpt != 'V') {
		printf("\n\t\tMenu Principal > Alteração");
		printf("\n");
		printf("\n\t\t1) Alterar produto por código");
		printf("\n\t\t2) Buscar produto para alterar");
		printf("\n\t\t0) Voltar");
		printf("\n\t\t          Opção: ");
fflush(stdin);
		scanf("%c", &userOpt);
		userOpt = toupper(userOpt);
		switch (userOpt) {
			case '1':
			case 'A':
				alterarPorCodigo();
				break;
			case '2':
			case 'B':
				buscarParaAlterar();
				break;
			case '0':
			case 'V':
				break;
		}
	}
}
menuExclusao() {
	char userOpt;
	while (userOpt != '0' && userOpt != 'V'){
		printf("\n\n\t\t Menu Principal > Exclusão");
		printf("\n");
		printf("\n\t\t1) Excluir produto por codigo");
		printf("\n\t\t2) Buscar produto para excluir");
		printf("\n\t\t0) Voltar");
		printf("\n\t\t          Opção: ");
	fflush(stdin);
		scanf("%c", &userOpt);
		userOpt = toupper(userOpt);
		switch (userOpt) {
			case '1':
			case 'E':
				excluirPorCodigo();
				break;
			case '2':
			case 'B':
				buscarParaExcluir();
				break;
			case '0':
			case 'V':
				break;
		}
	}
}
menuRelatorio() {
	char userOpt;
	while (userOpt != '0' && userOpt != 'V'){
		printf("\n\n\tMenu Principal > Relatorio");
		printf("\n");
		printf("\n\t1) exibir relatório de estoque Crítico");
		printf("\n\t2) exibir relatório Total");
		printf("\n\t0) Voltar ao menu principal");
		printf("\n");
		printf("\n\t            Opção: ");
		userOpt = 'z';
		while (userOpt == 'z') {
fflush(stdin);
			scanf("%c", &userOpt);
			userOpt = toupper(userOpt);
			switch (userOpt) {
				case '1':
				case 'C':
					relatorioCritico();
					break;
				case '2':
				case 'T':
					relatorioTotal();
					break;
				case '0':
				case 'V':
					break;
				default:
					printf("\n\t(!) Opção inválida. Escolha uma das opções apresentadas. (!)");
					userOpt = 'z';
					break;
			}
		}
	}
}
menuPrincipal() {
	char userOpt;
	while (userOpt != '0' && userOpt != 'F') {
		printf("\n  # # # # # # # # # # # # # # # #");
		printf("\n  # #     Menu Principal      # #");
		printf("\n  # # # # # # # # # # # # # # # #");
		printf("\n  #");
		printf("\n  #  1) Cadastro");
		printf("\n  #  2) cOnsulta");
		printf("\n  #  3) Alteração");
		printf("\n  #  4) Exclusão");
		printf("\n  #  5) Relatório");
		printf("\n  #  9) Instruções do sistema");
		printf("\n  #  0) Fim");
		printf("\n  #");
		printf("\n  # # # # #    Opção: ");
fflush(stdin);
		scanf("%c", &userOpt);
		userOpt = toupper(userOpt);
		printf("    #");
		switch (userOpt) {
			case '1':
			case 'C':
				menuCadastro();
				break;
			case '2':
			case 'O':
				menuConsulta();
				break;
			case '3':
			case 'A':
				menuAlteracao();
				break;
			case '4':
			case 'E':
				menuExclusao();
				break;
			case '5':
			case 'R':
				menuRelatorio();
				break;
			case '9':
			case 'I':
				instrucoesDoSistema();
				break;
			case '0':
			case 'F':
				break;
			default:
				printf("\n\n (!) Opção inválida. Selecione uma das opções. (!)\n");
				break;
		}
	}
}

setUpRegistrosVazios(){
	int i;
	for (i=0; i<1000; i++){
		codProdutosExcluidos[i] = -1;
	}
}

			// DEFINIÇÕES (Lógica)
			
		// Instruções
		
void instrucoesBasicas() {
	printf("\n   #################################################");
	printf("\n   #                                               #");
	printf("\n   #     Instruções básicas do Sistema - Uso       #");
	printf("\n   #                                               #");
	printf("\n   # # # # # # # # # # # # # # # # # # # # # # # # ###########");
	printf("\n   #                                                         #");
	printf("\n   #   -> Para selecionar uma opção, digite o número OU      #");
	printf("\n   #      a letra MAIÚSCULA destacada.                       #");
	printf("\n   #                                                         #");
	printf("\n   ###########################################################");
	printf("\n");
}
void instrucoesPrincipal() {
	printf("\n  #######################################");
	printf("\n  #                                     #");
	printf("\n  #    Instruções do Menu Principal:    #");
	printf("\n  #                                     #");
	printf("\n  # # # # # # # # # # # # # # # # # # # #####################################");
	printf("\n  #                                                                         #");
	printf("\n  #  1) Cadastro: Permite o cadastramento de produtos informando            #");
	printf("\n  #               descrição, departamento, quantidade em estoque,           #");
	printf("\n  #               quantidade mínima de estoque e preço unitário.            #");
	printf("\n  #                                                                         #");
	printf("\n  #  2) Consulta: Permite buscar os produtos já cadastrados no sistema,     #");
	printf("\n  #               informando seu código, descrição ou departamento.         #");
	printf("\n  #                                                                         #");
	printf("\n  #  3) Alteração: Permite buscar e alterar produtos já cadastrados,        #");
	printf("\n  #                preservando seu código.                                  #");
	printf("\n  #                                                                         #");
	printf("\n  #  4) Exclusão: Permite buscar e excluir um produto do sistema.           #");
	printf("\n  #                                                                         #");
	printf("\n  #  5) Relatório: Permite a geração de relatórios de vendas.               #");
	printf("\n  #                                                                         #");
	printf("\n  ###########################################################################");
	printf("\n");
}
void instrucoesCadastro() {
}
void instrucoesDoSistema() {
	printf("\n\n ####################################");
	printf("\n #                                  #");
	printf("\n #  Bem-vindo à tela de Instruções  #");
	printf("\n #                                  #");
	printf("\n ####################################");
	printf("\n");
	printf("\n (!) Pressione qualquer tecla para continuar (!)");
	getch();
	printf("\n");
	instrucoesBasicas();
	printf("\n (!) Pressione qualquer tecla para continuar (!)");
	getch();
	printf("\n");
	instrucoesPrincipal();
	printf("\n (!) Pressione qualquer tecla para continuar (!)");
	getch();
	printf("\n");
	instrucoesCadastro();
	printf("\n (!) Pressione qualquer tecla para continuar (!)");
	getch();
	printf("\n");
}


main() {
	FILE *config;
	config = fopen("config.txt", "r");
	setlocale(LC_ALL, "Portuguese");
	cadastrarAutomaticamente();
	setUpRegistrosVazios();
	printf("\n# # # # # # # # # # # # # # # # #");
	printf("\n# #    Controle de Estoque    # #");
	printf("\n# # # # # # # # # # # # # # # # #");
	printf("\n");
	instrucoesBasicas();
	menuPrincipal();
}
