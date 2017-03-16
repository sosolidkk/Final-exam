/*Nome: Joao Pedro Chaves de Lima
* 1º Periodo
* Ambiente: GNU_Linux
* Distro: Ubuntu 16.10
* Compilador = GCC
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_FUNC 150 //Tamanho do vetor func (tFuncionario)
#define TAM_DEPT 10 //Tamanho do vetor dept (tDepartamento)

#define ARQ_FUNC "funcionario.bin"
#define ARQ_DEPT "departamento.bin"

/* Struct: tData */
typedef struct{
    int dia;
    int mes;
    int ano;
}tData;

/* Struct: tFuncionario */
typedef struct {
    char nome[100];
    char cpf[12];
    tData dt_adm;
    tData dt_nasc;
    int cargo;
    int dept;
}tFuncionario;

/* Struct: tDepartamento */
typedef struct {
    char nome[100];
    int codigo;
    int quantidadeFuncDept;
}tDepartamento;

// Declaração das variáveis globais
tFuncionario func[TAM_FUNC];
tDepartamento dept[TAM_DEPT];
int prox[TAM_FUNC];
int controle[2][11];

// Declaração dos protótipos das funções //
int menu();

//Funções referentes ao Dept
int menuDept();
int criarDept(int *qtdDept); //FEITA 1.1
int alterarNomeDept(int qtdDept); //FEITA 1.2
void consultarDept(int qtdDept); //FEITA 1.3
void listarDept(int qtdDept); //FEITA 1.4
int excluirDept(int *qtdDept); //FEITA 1.5

//Funções referentes ao Func
int menuFunc(int qtdFunc, int qtdFuncEx);
int criarFunc(int *qtdFunc, int qtdDept, int *qtdFuncEx); //FEITA 1.1
int alterarDadosFunc(int qtdFunc, int qtdFuncEx); //FEITA 1.2
int transFuncDept(int qtdFunc, int qtdDept, int qtdFuncEx); //FEITA 1.3
int excluirFunc(int *qtdFunc, int qtdDept, int *qtdFuncEx); //FEITA 1.4
void pesquisarFunc(int qtdFunc, int qtdFuncEx); //FEITA 1.5
void listarFunc(int qtdFunc, int qtdFuncEx, int qtdDept); //FEITA 1.6
void listarFuncDept(int qtdFunc, int qtdDept, int qtdFuncEx); //FEITA 1.7

//Funções referentes ao alterarFunc
int menuAlterarFunc(char cpf[]); //FEITA
int alterarCpfFunc(int i, int qtdFunc, int qtdFuncEx); //FEITA 1.1
int alterarNomeFunc(int i); //FEITA 1.2
int alterarDtAdmFunc(int i); //FEITA 1.3
int alterarDtNascFunc(int i); //FEITA 1.4
int alterarCargoFunc(int i); //FEITA 1.5

//Funções referentes a arquivos
int gravarArquivos(int qtdFunc, int qtdFuncEx, int qtdDept); //FEITA
int recuperarArquivos(int *qtdFunc, int *qtdFuncEx, int *qtdDept); //FEITA

//Funçẽos necessárias
int checkCodigoDept(int qtdDept, int codigo); //FEITA
int checkCpfFunc(int qtdFunc, char cpf[], int qtdFuncEx); //FEITA
int returnIndiceDept(int codigo, int qtdDept); //FEITA
int returnIndiceFunc(char cpf[], int qtdFunc, int qtdFuncEx); //FEITA
int checkValidDate(int dia, int mes, int ano); //FEITA
void checkInput(char *input); //FEITA
void clearBuffer(); //FEITA
void imprimeFuncProxCont(int qtdFunc, int qtdFuncEx); //FEITA

int main() {
    int opMenu, opMenuFunc, opMenuDept, opMenuAlterarFunc;
    int qtdDept = 0, qtdFunc = 0, qtdFuncEx = 0;
    char resp;

    //Inicialização das variáveis
    controle[0][0] = -1;

    //Recuperando do arquivo
    do {
        printf("Deseja recuperar dos arquivos salvos? <s|n> \n-> ");
        scanf(" %c", &resp);

        if(resp == 's' || resp == 'S') {
            recuperarArquivos(&qtdFunc, &qtdFuncEx, &qtdDept);
            break;
        } else if(resp == 'n' || resp == 'N')
            break;
    } while(resp != 'S' || resp != 's' || resp != 'n' || resp != 'N');

    do {
        opMenu = menu();
        switch(opMenu) {
            case 0: break;
            case 1: //Menu Funcionario
                do {
                    opMenuFunc = menuFunc(qtdFunc, qtdFuncEx);
                    switch(opMenuFunc) {
                        case 0: break;
                        case 1: criarFunc(&qtdFunc, qtdDept, &qtdFuncEx); break;
                        case 2: alterarDadosFunc(qtdFunc, qtdFuncEx); break;
                        case 3: transFuncDept(qtdFunc, qtdDept, qtdFuncEx); break;
                        case 4: excluirFunc(&qtdFunc, qtdDept, &qtdFuncEx); break;
                        case 5: pesquisarFunc(qtdFunc, qtdFuncEx); break;
                        case 6: listarFunc(qtdFunc, qtdFuncEx, qtdDept); break;
                        case 7: listarFuncDept(qtdFunc, qtdDept, qtdFuncEx); break;
                        case 8: imprimeFuncProxCont(qtdFunc, qtdFuncEx); break;
                        default: system("clear");
                    }
                } while(opMenuFunc != 0);
                break;
            case 2: //Menu Departamento
                do {
                    opMenuDept = menuDept();
                    switch(opMenuDept) {
                        case 0: break;
                        case 1: criarDept(&qtdDept); break;
                        case 2: alterarNomeDept(qtdDept); break;
                        case 3: consultarDept(qtdDept); break;
                        case 4: listarDept(qtdDept); break;
                        case 5: excluirDept(&qtdDept); break;
                        case 6: imprimeFuncProxCont(qtdFunc, qtdFuncEx); break;
                        default: system("clear");
                    }
                } while(opMenuDept != 0);
                break;
            default: printf("Invalid option.\n");
        }
    } while (opMenu != 0);

    gravarArquivos(qtdFunc, qtdFuncEx, qtdDept); //Grava em arquivos antes de finalizar o programa

    return 0;
}
/*
* Nome: menu().
* Função: imprimir o menu com suas opções.
* Funcionamento: Mostra todas as opções do programa referentes ao menu principal
* e espera até que o usuário digite uma.
* Retorno: a opção escolhida.
*/
int menu() { //TERMINADA_MENU
    int resp;
    //system("clear"); //Se for windows mude para "cls"

    printf("\n<- MENU RELATORIO ->\n");
    printf("1 - Funcionario. \n2 - Departamento.\n");
    printf("-> ");

    scanf("%d", &resp);

    return resp;
}
/*
* Nome: menuFunc(menu funcionario).
* Função: imprimir o menu funcionario com suas opções.
* Funcionamento: Mostra todas as opções do programa referentes ao menu funcionario
* e espera até que o usuário digite uma.
* Retorno: a opção escolhida.
*/
int menuFunc(int qtdFunc, int qtdFuncEx) { //TERMINADA_MENU_1.1
    int resp;
    //system("clear"); //Se for windows mude para "cls"

    printf("\n<- MENU FUNCIONARIO qtdFunc %d  | qtdFuncEx%d ->\n", qtdFunc, qtdFuncEx);
    printf("1 - Cadastrar Funcionario. \n2 - Alterar dados do Funcionario.\n");
    printf("3 - Transferir Funcionario de Departamento. \n4 - Demitir Funcionario.\n");
    printf("5 - Pesquisar um Funcionario. \n6 - Listar Todos os Funcionarios. \n7 - Lista Todos de um Departamento.\n");
    printf("0 - Sair. \n-> ");

    scanf("%d", &resp);

    return resp;
}
/*
* Nome: criarFunc(criar funcionario).
* Função: criar um funcionario com seus dados.
* Funcionamento: Checa primeiro se a empresa possui departamentos e funcionarios, caso passe em ambos os teste
* ele vai pedir as informações necessárias para o cadastro, e caso esteja tudo correto, ira fazer as alterações.
* nos vetores prox, func, controle e dept.
* Retorno: 0 se ok, -1 error e -2 cancelamento.
*/
int criarFunc(int *qtdFunc, int qtdDept, int *qtdFuncEx) { //TERMINADA_FUNC_1.1
    int resp, iDept, temp;
    char cpf[12];

    if(qtdDept <= 0) {
        printf("Cadastre primeiro um departamento para cadastrar um funcionario.\n");
        return -1;
    }

    if(*qtdFunc >= TAM_FUNC) {
        printf("Empresa esta lotada de funcionarios, por favor demita alguns ou espere o crescimento da mesma.\n");
        return -1;
    }

    do {
        clearBuffer();

        printf("Digite o cpf do funcionario:\n-> ");
        checkInput(fgets(cpf, 12, stdin));

        if(checkCpfFunc(*qtdFunc, cpf, *qtdFuncEx) != 0) {
            printf("Cpf %s ja existe.\n", cpf);
            do{
                printf("Deseja inserir um novo? (1 - s | 0 - n) \n-> ");
                scanf("%d", &resp);

                if(resp == 0) {
                    printf("Operacao cancelada.\n");
                    return -2;
                }
            }while(resp != 1);
        }
    } while(checkCpfFunc(*qtdFunc, cpf, *qtdFuncEx) != 0);
    strcpy(func[controle[1][0]].cpf, cpf);

    printf("Qual o nome do funcionario?\n-> ");
    checkInput(fgets(func[controle[1][0]].nome, 100, stdin));

    do {
        printf("Digite a data de admissao do funcionario (dd/mm/aaaa): \n-> ");
        scanf("%d %d %d", &func[controle[1][0]].dt_adm.dia, &func[controle[1][0]].dt_adm.mes, &func[controle[1][0]].dt_adm.ano);
    } while(checkValidDate(func[controle[1][0]].dt_adm.dia, func[controle[1][0]].dt_adm.mes, func[controle[1][0]].dt_adm.ano) != 0);

    do {
        printf("Digite a data de nascimento do funcionario (dd/mm/aaaa): \n-> ");
        scanf("%d %d %d", &func[controle[1][0]].dt_nasc.dia, &func[controle[1][0]].dt_nasc.mes, &func[controle[1][0]].dt_nasc.ano);
    } while(checkValidDate(func[controle[1][0]].dt_nasc.dia, func[controle[1][0]].dt_nasc.mes, func[controle[1][0]].dt_nasc.ano) != 0);

    printf("Digite o cargo do funcionario: \n-> ");
    scanf("%d", &func[controle[1][0]].cargo);

    do {
        printf("Digite o codigo do departamento: \n-> ");
        scanf("%d", &func[controle[1][0]].dept);

        if(checkCodigoDept(qtdDept, func[controle[1][0]].dept) != -1) {
            listarDept(qtdDept);
            printf("Codigo %d invalido.\n", func[controle[1][0]].dept);
            do{
                printf("Deseja inserir um novo? (1 - s | 0 - n) \n-> ");
                scanf("%d", &resp);

                if(resp == 0) {
                    printf("Operacao cancelada.\n");
                    return -2;
                }
            }while(resp != 1);
        }
    } while(checkCodigoDept(qtdDept, func[controle[1][0]].dept) != -1);

    printf("Funcionario cadastrado.\n");

    //Atualizando vetDept
    iDept = returnIndiceDept(func[controle[1][0]].dept, qtdDept);
    dept[iDept].quantidadeFuncDept += 1;

    if(controle[1][0] == *qtdFunc && *qtdFunc + *qtdFuncEx == *qtdFunc) { //Situação 1 - 0 elementos excluídos
        printf("Situacao 1 - Cadastrar\n");
        *qtdFunc += 1;
        controle[1][0] += 1;

        prox[*qtdFunc - 1] = controle[1][iDept + 1];
        controle[1][iDept + 1] = *qtdFunc - 1;
    } else { // Situação 2 - N elementos excluídos
        printf("Situacao 2 - Cadastrar\n");
        if(controle[1][iDept + 1] == -1) { // Caso um dept não possua elementos cadastrados
            printf("ifCadastrar2\n");
            controle[1][iDept + 1] = controle[1][0];
            controle[1][0] = prox[controle[1][0]];

            prox[controle[1][iDept + 1]] = -1;

            *qtdFunc += 1;
        } else { // Caso o dept possua elementos cadastrados
            printf("elseCadastrar2\n");
            temp = controle[1][iDept  + 1];
            controle[1][iDept + 1] = controle[1][0];
            controle[1][0] = prox[controle[1][0]];

            prox[controle[1][iDept + 1]] = temp;

            *qtdFunc += 1;
        }
    }

    if(*qtdFuncEx > 0)
        *qtdFuncEx -= 1;

    printf("Funcionario cadastrado com sucesso.\n");

    return 0;
}
/*
* Nome: alterarDadosFunc(alterar dados de um funcionario).
* Função: altera os dados de um funcionario.
* Funcionamento: Recebe a quantidade de funcionarios e funcionarios excluidos e checa se possui algum.
* Caso possua algum, ele pede um cpf para realizar as alterações referentes ao funcionario. Caso o cpf
* exista (já tenha sido cadastrado) ele mostra o menu para alterar dados de um funcionarios.
* Retorno: 0 se ok, -1 error e -2 cancelamento.
*/
int alterarDadosFunc(int qtdFunc, int qtdFuncEx) { //TERMINADA_FUNC_1.2
    int resp, opMenuDadosFunc, aux;
    char cpf[12];

    if(qtdFunc <= 0) {
        printf("Cadastre um funcionario para poder alterar as informacoes dele.\n");
        return -1;
    }

    do {
        clearBuffer();

        printf("Digite o cpf do funcionario: \n-> ");
        checkInput(fgets(cpf, 12, stdin));

        if(checkCpfFunc(qtdFunc, cpf, qtdFuncEx) != -1) {
            printf("Cpf %s nao existe.\n", cpf);
            do{
                printf("Deseja inserir um novo? (1 - s | 0 - n) \n-> ");
                scanf("%d", &resp);

                if(resp == 0) {
                    printf("Operacao cancelada.\n");
                    return -2;
                }
            }while(resp != 1);
        }
    } while(checkCpfFunc(qtdFunc, cpf, qtdFuncEx) != -1);

    aux = returnIndiceFunc(cpf, qtdFunc, qtdFuncEx);

    do {
        opMenuDadosFunc = menuAlterarFunc(func[aux].cpf);
        switch(opMenuDadosFunc) {
            case 0: system("clear"); break;
            case 1: alterarCpfFunc(aux, qtdFunc, qtdFuncEx); break;
            case 2: alterarNomeFunc(aux); break;
            case 3: alterarDtNascFunc(aux); break;
            case 4: alterarDtAdmFunc(aux); break;
            case 5: alterarCargoFunc(aux); break;
            default: printf("Default menuDadosFunc.\n");
        }
    } while(opMenuDadosFunc != 0);

    return 0;
}
/*
* Nome: transFuncDept(transferir um funcionario de departamento).
* Função: transfere um funcionario da empresa de um departamento para outro.
* Funcionamento: Recebe a quantidade de funcionarios cadastrados, funcionarios excluidos e a quantidade de departamentos na empresa.
* Primeiro se pede um codigo e após isso faz a checagem se o codigo existe ou não, caso exista
* checa se ele possui funcionarios para serem transferidos, caso possua, se pede o código departamento de destino
* e é feita outra checagem, caso o código do departamento de destino exista, é checado em qual condição se encaixa e as modificações
* nos vetores prox, dept, func e controle são feitas.
* Retorno: 0 se ok, -1 error e -2 cancelamento.
*/
int transFuncDept(int qtdFunc, int qtdDept, int qtdFuncEx) { //TERMINADA_FUNC_1.3
    int i, iDeptOrigem, iDeptDestino, iFunc;
    int resp, codOrigem, codDestino;
    char cpf[12];

    if(qtdFunc <= 0) {
        printf("Nao existem funcionarios para serem transferidos.\n");
        return 0;
    }

    while(1) {
        do {
            printf("Digite o codigo do departamento de origem:\n-> ");
            scanf("%d", &codOrigem);

            if(checkCodigoDept(qtdDept, codOrigem) != -1) {
                listarDept(qtdDept);
                printf("Codigo %d invalido.\n", codOrigem);
                do{
                    printf("Deseja inserir um novo? (1 - s | 0 - n) \n-> ");
                    scanf("%d", &resp);

                    if(resp == 0) {
                        printf("Operacao cancelada.\n");
                        return -2;
                    }
                }while(resp != 1);
            }
        } while(checkCodigoDept(qtdDept, codOrigem) != -1);

        if(dept[returnIndiceDept(codOrigem, qtdDept)].quantidadeFuncDept == 0) {
            printf("Departamento nao possui funcionario(s) para ser(em) transferido(s).\n");
            return -1;
        }

        do {
            clearBuffer();

            printf("Digite o cpf do funcionario:\n-> ");
            checkInput(fgets(cpf, 12, stdin));

            if(checkCpfFunc(qtdFunc, cpf, qtdFuncEx) != -1) {
                printf("Cpf %s nao existe.\n", cpf);
                do{
                    printf("Deseja inserir um novo? (1 - s | 0 - n) \n-> ");
                    scanf("%d", &resp);

                    if(resp == 0) {
                        printf("Operacao cancelada.\n");
                        return -2;
                    }
                }while(resp != 1);
            }
        } while(checkCpfFunc(qtdFunc, cpf, qtdFuncEx) != -1);

        iFunc = returnIndiceFunc(cpf, qtdFunc, qtdFuncEx);

        if(func[iFunc].dept != codOrigem) {
            printf("Funcionario %s nao esta cadastrado no departamento %d.\n", cpf, codOrigem);
            printf("Deseja inserir as informacoes novamente? (1 - s | 0 - n) \n-> ");
            scanf("%d", &resp);

            if(resp == 1)
                continue;
            else {
                printf("Operacao cancelada.\n");
                return -2;
            }
        } else
            break;
    }

    do {
        printf("Digite o codigo do departamento de destino:\n-> ");
        scanf("%d", &codDestino);

        if(checkCodigoDept(qtdDept, codDestino) != -1) {
            listarDept(qtdDept);
            printf("Codigo %d invalido.\n", codDestino);
            do{
                printf("Deseja inserir um novo? (1 - s | 0 - n) \n-> ");
                scanf("%d", &resp);

                if(resp == 0) {
                    printf("Operacao cancelada.\n");
                    return -2;
                }
            }while(resp != 1);
        }
    } while(checkCodigoDept(qtdDept, codDestino) != -1);

    iDeptOrigem = returnIndiceDept(codOrigem, qtdDept);
    iDeptDestino = returnIndiceDept(codDestino, qtdDept);

    if((prox[iFunc] != -1 || prox[iFunc] == -1) && iFunc != controle[1][iDeptOrigem + 1]) { //Situação 1
        printf("Situacao 1 transf.\n");
        for(i = 0; i < qtdFunc; i++) {
            if(iFunc == prox[i]) {
                prox[i] = prox[iFunc];
                break;
            }
        }
        prox[iFunc] = controle[1][iDeptDestino + 1];

        controle[1][iDeptDestino + 1] = iFunc;

        func[iFunc].dept = controle[0][iDeptDestino + 1];

        dept[iDeptOrigem].quantidadeFuncDept -= 1;
        dept[iDeptDestino].quantidadeFuncDept += 1;

    } else if(iFunc == controle[1][iDeptOrigem + 1] && dept[iDeptOrigem].quantidadeFuncDept > 1) { //Situação 2
        printf("Situação 2 transf.\n");

        controle[1][iDeptOrigem + 1] = prox[iFunc];

        prox[iFunc] = controle[1][iDeptDestino + 1];

        controle[1][iDeptDestino + 1] = iFunc;

        func[iFunc].dept = controle[0][iDeptDestino + 1];

        dept[iDeptOrigem].quantidadeFuncDept -= 1;
        dept[iDeptDestino].quantidadeFuncDept += 1;

    } else if(dept[iDeptOrigem].quantidadeFuncDept == 1) { //Situação 3 - OK
        printf("Situação 3 transf.\n");

        prox[iFunc] = controle[1][iDeptDestino + 1];

        controle[1][iDeptDestino + 1] = iFunc;
        controle[1][iDeptOrigem + 1] = -1;

        func[iFunc].dept = controle[0][iDeptDestino + 1];

        dept[iDeptOrigem].quantidadeFuncDept -= 1;
        dept[iDeptDestino].quantidadeFuncDept += 1;

    }
    printf("Funcionario alterado de departamento com sucesso.\n");

    return 0;
}
/*
* Nome: excluirFunc(demite/exclui um funcionario da empresa).
* Função: demite/exclui um funcionario da empresa de um departamento para outro.
* Funcionamento: Recebe a quantidade de funcionarios cadastrados (ponteiro), funcionarios excluidos (ponteiro) e a quantidade de departamentos na empresa.
* Primeiro se pede um codigo e após isso faz a checagem se o codigo existe ou não, caso exista
* checa se ele possui funcionarios para serem excluidos, caso possua, ele pede um cpf e faz a checagem do cpf, caso exista
* o programa checha se o cpf possui ao departamento em questão, caso possua ele procura em qual situação deve ser encaixada
* o processo de exclusão e faz as devidas alteraçções nos vetores prox, func, controle e dept.
* Retorno: 0 se ok, -1 error e -2 cancelamento.
*/
int excluirFunc(int *qtdFunc, int qtdDept, int *qtdFuncEx) {
    int i, iDept, iFunc, codigo, resp;
    char resp2 = 'x', cpf[12];

    if(*qtdFunc <= 0) {
        printf("Nao existem funcionarios a serem excluidos.\n");
        return -1;
    }

    while(1) {
        do {
            printf("Digite o codigo do departamento:\n-> ");
            scanf("%d", &codigo);

            if(checkCodigoDept(qtdDept, codigo) != -1) {
                listarDept(qtdDept);
                printf("Codigo %d invalido.\n", codigo);
                do{
                    printf("Deseja inserir um novo? (1 - s | 0 - n) \n-> ");
                    scanf("%d", &resp);

                    if(resp == 0) {
                        printf("Operacao cancelada.\n");
                        return -2;
                    }
                }while(resp != 1);
            }
        } while(checkCodigoDept(qtdDept, codigo) != -1);

        if(dept[returnIndiceDept(codigo, qtdDept)].quantidadeFuncDept == 0) {
            printf("Departamento nao possui funcionario(s) para ser(em) excluido(s).\n");
            return -1;
        }

        do {
            clearBuffer();

            printf("Digite o cpf do funcionario:\n-> ");
            checkInput(fgets(cpf, 12, stdin));

            if(checkCpfFunc(*qtdFunc, cpf, *qtdFuncEx) != -1) {
                printf("Cpf %s nao existe.\n", cpf);
                do{
                    printf("Deseja inserir um novo? (1 - s | 0 - n) \n-> ");
                    scanf("%d", &resp);

                    if(resp == 0) {
                        printf("Operacao cancelada.\n");
                        return -2;
                    }
                }while(resp != 1);
            }
        } while(checkCpfFunc(*qtdFunc, cpf, *qtdFuncEx) != -1);

        i = returnIndiceFunc(cpf, *qtdFunc, *qtdFuncEx);

        if(func[i].dept != codigo) {
            printf("Funcionario %s nao esta cadastrado no departamento %d.\n", cpf, codigo);
            printf("Deseja inserir as informacoes novamente? (1 - s | 0 - n) \n-> ");
            scanf("%d", &resp);

            if(resp == 1)
                continue;
            else {
                printf("Operacao cancelada.\n");
                return -2;
            }
        } else
            break;
    }

    while(resp2 != 'S' || resp2 != 's' || resp2 != 'n' || resp2 != 'N') {
        printf("Deseja realmente exluir o funcionario %s? <s|n> \n-> ", cpf);
        scanf(" %c", &resp2);

        if(resp2 == 'S' || resp2 == 's') {
            iDept = returnIndiceDept(codigo, qtdDept);
            iFunc = returnIndiceFunc(cpf, *qtdFunc, *qtdFuncEx);

            if((iFunc != controle[1][iDept + 1]) && dept[iDept].quantidadeFuncDept > 1) { //Situação 1
                printf("Situacao 1 excluir.\n");
                for(i = 0; i < *qtdFunc; i++) {
                    if(iFunc == prox[i]) {
                        prox[i] = prox[iFunc];
                        break;
                    }
                }
                prox[iFunc] = controle[1][0];

                controle[1][0] = iFunc;

                func[iFunc] = func[TAM_FUNC - 1];
                func[iFunc].dept = -1;

                dept[iDept].quantidadeFuncDept -= 1;

                *qtdFunc -= 1;
                *qtdFuncEx += 1;

                if(dept[iDept].quantidadeFuncDept == 1)
                    prox[controle[1][iDept + 1]] = -1;
            } else if(dept[iDept].quantidadeFuncDept > 1 && iFunc == controle[1][iDept + 1]) { //Situação 2
                printf("Situacao 2 excluir.\n");
                func[iFunc] = func[TAM_FUNC - 1];
                func[iFunc].dept = -1;

                dept[iDept].quantidadeFuncDept -= 1;

                controle[1][iDept + 1] = prox[iFunc];

                prox[iFunc] = controle[1][0];

                controle[1][0] = iFunc;

                *qtdFunc -= 1;
                *qtdFuncEx += 1;
            } else if(dept[iDept].quantidadeFuncDept == 1 && *qtdFunc > 1) { //Situação 3
                printf("Situacao 3 excluir.\n");
                func[iFunc] = func[TAM_FUNC - 1];
                func[iFunc].dept = -1;

                dept[iDept].quantidadeFuncDept -= 1;

                prox[iFunc] = controle[1][0];

                controle[1][iDept + 1] = -1;
                controle[1][0] = iFunc;

                *qtdFunc -= 1;
                *qtdFuncEx += 1;
            } else if(*qtdFunc == 1) { //Situação 4
                printf("Situacao 4 excluir.\n");
                func[iFunc] = func[TAM_FUNC - 1];
                func[iFunc].dept = -1;

                dept[iDept].quantidadeFuncDept -= 1;

                prox[iFunc] = controle[1][0];

                controle[1][iDept + 1] = -1;
                controle[1][0] = iFunc;

                *qtdFunc -= 1;
                *qtdFuncEx += 1;
            }

            printf("Funcionario %s excluido com sucesso.\n", cpf);
            break;
        } else if(resp2 == 'N' || resp2 == 'n') {
            printf("Operacao cancelada.\n");
            return -2;
        }
    }

    return 0;
}
/*
* Nome: pesquisarFunc(consultar um funcionario).
* Função: consultar as informações de um funcionario da empresa.
* Funcionamento: Recebe apenas a quantidade de funcionarios cadastrados na empresa.
* Primeiro se pede um cpf e após isso faz a checagem se o cpf existe ou não, caso exista
* é percorrido em um laço de repetição por todos os funcionarios cadastrados e caso o cpf
* digitado seja igual ao de um funcionario cadastrado, ele retorna as informações do mesmo.
* Retorno: void.
*/
void pesquisarFunc(int qtdFunc, int qtdFuncEx) { //TERMINADA_FUNC_1.5
    int resp, iFunc;
    char cpf[12];

    if(qtdFunc <= 0) {
        printf("Nao existem funcionarios cadastrados.\n");
        return;
    }

    do {
        clearBuffer();

        printf("Digite o cpf do funcionario:\n-> ");
        checkInput(fgets(cpf, 12, stdin));

        if(checkCpfFunc(qtdFunc, cpf, qtdFuncEx) != -1) {
            printf("Cpf %s nao existe.\n", cpf);
            do{
                printf("Deseja inserir um novo? (1 - s | 0 - n) \n-> ");
                scanf("%d", &resp);

                if(resp == 0) {
                    printf("Operacao cancelada.\n");
                    return;
                }
            }while(resp != 1);
        }
    } while(checkCpfFunc(qtdFunc, cpf, qtdFuncEx) != -1);

    iFunc = returnIndiceFunc(cpf, qtdFunc, qtdFuncEx);

    printf("CPF-> %s\n", func[iFunc].cpf);
    printf("NOME-> %s\n", func[iFunc].nome);
    printf("DT_ADM-> %d/%d/%d\n", func[iFunc].dt_adm.dia, func[iFunc].dt_adm.mes, func[iFunc].dt_adm.ano);
    printf("DT_NASC-> %d/%d/%d\n", func[iFunc].dt_nasc.dia, func[iFunc].dt_nasc.mes, func[iFunc].dt_nasc.ano);
    printf("CARGO-> %d\n", func[iFunc].cargo);
    printf("DEPT_COD-> %d\n", func[iFunc].dept);
}
/*
* Nome: listarFunc(listar um funcionario).
* Função: consultar as informações de todos funcionario da empresa.
* Funcionamento: Recebe a quantidade de funcionarios cadastrados na empresa e o número de departamentos.
* É percorrido um laço de repetição por todos os departamentos cadastrados e caso determinado funcionário
* faça parte desse departamento, as informações do mesmo vão ser impressas.
* Retorno: void.
*/
void listarFunc(int qtdFunc, int qtdFuncEx, int qtdDept) { //TERMINADA_FUNC_1.6
    int i, j, temp;

    if(qtdFunc <= 0) {
        printf("Nao existem funcionarios cadastrados.\n");
        return;
    }

    /*for(i = 0; i < qtdDept; i++) {
        printf("\n<--- DEPT %d --->\n", dept[i].codigo);
        for(j = 0; j < qtdFunc + qtdFuncEx; j++) {
            if(func[j].dept == -1)
                continue;
            if(func[j].dept == dept[i].codigo) {
                printf("CPF-> %s\n", func[j].cpf);
                printf("NOME-> %s\n", func[j].nome);
                printf("DT_ADM-> %d/%d/%d\n", func[j].dt_adm.dia, func[j].dt_adm.mes, func[j].dt_adm.ano);
                printf("DT_NASC-> %d/%d/%d\n", func[j].dt_nasc.dia, func[j].dt_nasc.mes, func[j].dt_nasc.ano);
                printf("CARGO-> %d\n", func[j].cargo);
                printf("DEPT_COD-> %d\n\n", func[j].dept);
            }
        }
    }*/

    // Outra maneira de Imprimir
    for(i = 0; i < qtdDept; i++) {
        printf("\n<--- DEPT %d --->\n", dept[i].codigo);
        for(j = 0; j < dept[i].quantidadeFuncDept; j++) {
            if(j == 0)
                temp = controle[1][i + 1];
                printf("CPF-> %s\n", func[temp].cpf);
                printf("NOME-> %s\n", func[temp].nome);
                printf("DT_ADM-> %d/%d/%d\n", func[temp].dt_adm.dia, func[temp].dt_adm.mes, func[temp].dt_adm.ano);
                printf("DT_NASC-> %d/%d/%d\n", func[temp].dt_nasc.dia, func[temp].dt_nasc.mes, func[temp].dt_nasc.ano);
                printf("CARGO-> %d\n", func[temp].cargo);
                printf("DEPT_COD-> %d\n\n", func[temp].dept);

            if(j == 0)
                temp = prox[controle[1][i + 1]];
            else
                temp = prox[temp];
        }
    }

}
/*
* Nome: listarFuncDept(listar funcionario(s) por departamento).
* Função: consultar as informações de funcionarios da empresa por departamento.
* Funcionamento: Recebe a quantidade de funcionarios cadastrados e funcionarios excluidos na empresa e o número de departamentos.
* Se pede um código de um departamento, se o código não existir ele retorna para o menu funcionario.
* Caso exista percorrido um laço de repetição por todos os funcionarios em busca daqueles que foram cadastrados no mesmo código.
* Caso façam parte desse departamento, as informações dos mesmos vão ser impressas.
* Retorno: void.
*/
void listarFuncDept(int qtdFunc, int qtdDept, int qtdFuncEx) { //TERMINADA_FUNC_1.7
    int i, codigo;

    if(qtdFunc <= 0) {
        printf("Nao existem funcionarios cadastrados.\n");
        return;
    }

    printf("Digite o codigo do departamento que deseja listar: \n-> ");
    scanf("%d", &codigo);

    if(checkCodigoDept(qtdDept, codigo) != -1) {
        printf("Codigo %d invalido.\n", codigo);
        return;
    }

    for(i = 0; i < qtdFunc + qtdFuncEx; i++) {
        if(func[i].dept == codigo) {
            printf("CPF-> %s\n", func[i].cpf);
            printf("NOME-> %s\n", func[i].nome);
            printf("DT_ADM-> %d/%d/%d\n", func[i].dt_adm.dia, func[i].dt_adm.mes, func[i].dt_adm.ano);
            printf("DT_NASC-> %d/%d/%d\n", func[i].dt_nasc.dia, func[i].dt_nasc.mes, func[i].dt_nasc.ano);
            printf("CARGO-> %d\n\n", func[i].cargo);
        }
    }
}
/*
* Nome: menuAlterarFunc(menu alterar funcionario).
* Função: imprimir o menu alterar funcionario com suas opções.
* Funcionamento: Mostra todas as opções do programa referentes ao menu alterar funcionario
* e espera até que o usuário digite uma.
* Retorno: a opção escolhida.
*/
int menuAlterarFunc(char cpf[]) { //TERMINADA_MENU_1.1.1
    int resp, i;
    //system("clear"); //Se for windows mude para "cls"

    printf("\n<- MENU ALTERAR FUNCIONARIO %s ->\n", cpf);
    printf("1 - CPF\n");
    printf("2 - NOME\n");
    printf("3 - DT_NASCIMENTO\n");
    printf("4 - DT_ADMISSAO\n");
    printf("5 - CARGO \n0 - SAIR \n-> ");

    scanf("%d", &resp);

    return resp;
}
/*
* Nome: AlterarCpfFunc(alterar o cpf de um funcionario).
* Função: alterar o cpf de um funcionario.
* Funcionamento: Recebe o índice do funcionario, a quantidade de funcionarios e a quantidade de funcionarios escluidos.
* Pede para se digitar um cpf, caso não exista, o cpf do funcionário de índice i é alterado com sucesso.
* Retorno: 0 se ok, -2 cancelamento.
*/
int alterarCpfFunc(int i, int qtdFunc, int qtdFuncEx) { //TERMINADA_FUNC_1.2.1
    int resp;
    char cpf[12];

    do {
        clearBuffer();

        printf("Digite o novo cpf do funcionario:\n-> ");
        checkInput(fgets(cpf, 12, stdin));

        if(checkCpfFunc(qtdFunc, cpf, qtdFuncEx) != 0) {
            printf("Cpf %s ja existe.\n", cpf);
            do{
                printf("Deseja inserir um novo? (1 - s | 0 - n) \n-> ");
                scanf("%d", &resp);

                if(resp == 0) {
                    printf("Operacao cancelada.\n");
                    return -2;
                }
            }while(resp != 1);
        }
    } while(checkCpfFunc(qtdFunc, cpf, qtdFuncEx) != 0);

    strcpy(func[i].cpf, cpf);
    printf("CPF alterado com sucesso.\n");

    return 0;
}
/*
* Nome: AlterarNomeFunc(alterar o nome de um funcionario).
* Função: alterar o nome de um funcionario.
* Funcionamento: Recebe o índice do funcionario.
* Pede para se digitar um novo nome e o nome do funcionário de índice i é alterado com sucesso.
* Retorno: 0 se ok.
*/
int alterarNomeFunc(int i) { //TERMINADA_FUNC_1.2.2
    char nome[100];

    clearBuffer();

    printf("Digite o novo nome do funcionario: \n-> ");
    checkInput(fgets(nome, 100, stdin));

    strcpy(func[i].nome, nome);

    printf("NOME alterado com sucesso.\n");

    return 0;
}
/*
* Nome: AlterarDtNascFunc(alterar a data de nascimento de um funcionario).
* Função: alterar a data de nascimento de um funcionario.
* Funcionamento: Recebe o índice do funcionario.
* Pede para se digitar uma nova data e caso a data do funcionário de índice i seja válida, é alterada com sucesso.
* Retorno: 0 se ok.
*/
int alterarDtNascFunc(int i) { //TERMINADA_FUNC_1.2.3
    int dia, mes, ano;

    do {
        printf("Digite a nova data de nascimento do funcionario (dd/mm/aaaa): \n-> ");
        scanf("%d %d %d", &dia, &mes, &ano);
    } while(checkValidDate(dia, mes, ano) != 0);

    func[i].dt_nasc.dia = dia;
    func[i].dt_nasc.mes = mes;
    func[i].dt_nasc.ano = ano;

    printf("DT_NASC alterada com sucesso.\n");

    return 0;
}
/*
* Nome: AlterarDtAdmFunc(alterar a data de admissao de um funcionario).
* Função: alterar a data de admissao de um funcionario.
* Funcionamento: Recebe o índice do funcionario.
* Pede para se digitar uma nova data e caso a data do funcionário de índice i seja válida, é alterada com sucesso.
* Retorno: 0 se ok.
*/
int alterarDtAdmFunc(int i) { //TERMINADA_FUNC_1.2.4
    int dia, mes, ano;

    do {
        printf("Digite a nova data de admissao do funcionario (dd/mm/aaaa): \n-> ");
        scanf("%d %d %d", &dia, &mes, &ano);
    } while(checkValidDate(dia, mes, ano) != 0);

    func[i].dt_adm.dia = dia;
    func[i].dt_adm.mes = mes;
    func[i].dt_adm.ano = ano;

    printf("DT_ADM alterada com sucesso.\n");

    return 0;
}
/*
* Nome: AlterarCargoFunc(alterar o cargo de um funcionario).
* Função: alterar o cargo de um funcionario.
* Funcionamento: Recebe o índice do funcionario.
* Pede para se digitar um cargo e o cargo do funcionário de índice i é alterada com sucesso.
* Retorno: 0 se ok.
*/
int alterarCargoFunc(int i) { //TERMINADA_FUNC_1.2.5
    int cargo;

    printf("Digite o novo cargo do funcionario: \n-> ");
    scanf("%d", &cargo);

    func[i].cargo = cargo;

    printf("CARGO alterado com sucesso.\n");

    return 0;
}
/*
* Nome: menuDept(menu departamento).
* Função: imprimir o menu departamento com suas opções.
* Funcionamento: Mostra todas as opções do programa referentes ao menu departamento
* e espera até que o usuário digite uma.
* Retorno: a opção escolhida.
*/
int menuDept() { //TERMINADA_MENU_1.2
    int resp;
    //system("clear"); //Se for windows mude para "cls"

    printf("\n<- MENU DEPARTAMENTO ->\n");
    printf("1 - Criar Departamento. \n2 - Alterar Nome do Departamento.\n");
    printf("3 - Consultar Departamento. \n4 - Lista Departamentos.\n");
    printf("5 - Excluir Departamento. \n0 - Sair. \n-> ");

    scanf("%d", &resp);

    return resp;
}
/*
* Nome: criarDept(criar departamento).
* Função: criar um departamento para permitir o cadastro de funcionarios na empresa
* Funcionamento: Recebe um código(int) e um nome(char[100]), caso o código exista ele imprimirá uma mensagem
* perguntando se o usuário deseja digitar outro código (1 para sim e 0 para não).
* Caso o departamento seja criado a qtdDept é incrementada em 1, e as alterações no controle são feitas.
* Retorno: 0 se ok, -1 error e -2 cancelamento.
*/
int criarDept(int *qtdDept) { //TERMINADA_DEPT_1.1
    int resp;
    system("clear"); //Se for windows mude para "cls"

    if(*qtdDept >= TAM_DEPT) {
        printf("Quantidade maxima de departamentos atingida.\n");
        return -1;
    }

    do {
        printf("Digite o codigo do departamento:\n-> ");
        scanf("%d", &dept[*qtdDept].codigo);

        if(checkCodigoDept(*qtdDept, dept[*qtdDept].codigo) != 0) {
            printf("Codigo %d ja cadastrado.\n", dept[*qtdDept].codigo);
            do{
                printf("Deseja inserir um novo? (1 - s | 0 - n) \n-> ");
                scanf("%d", &resp);

                if(resp == 0) {
                    printf("Operacao cancelada.\n");
                    return -2;
                }
            }while(resp != 1);
        }
    } while(checkCodigoDept(*qtdDept, dept[*qtdDept].codigo) != 0);

    clearBuffer();

    printf("Digite o nome do departamento:\n-> ");
    checkInput(fgets(dept[*qtdDept].nome, 100, stdin));

    dept[*qtdDept].quantidadeFuncDept = 0; //*qtdDept = índice do departamento
    *qtdDept += 1;

    controle[0][*qtdDept] = dept[*qtdDept - 1].codigo; //controle na linha 0 recebe o código do departamento
    controle[1][*qtdDept] = -1; //Recebe -1 pois não possuí funcionarios cadastrados ainda

    printf("Departamento criado com sucesso.\n");

    return 0;
}
/*
* Nome: alterarNomeDept(alterar nome de um departamento).
* Função: altera o nome de um departamento da empresa.
* Funcionamento: Recebe apenas a quantidade de departamentos cadastrados na empresa.
* Primeiro se pede um código e após isso faz a checagem se o código existe ou não, caso exista
* é atribuida a uma variável i o índice do departamento que está sendo referenciado e se pede para digitar
* o novo nome, assim alterando com sucesso. Não é necessária a checagem de nomes entre departamentos.
* Retorno: 0 se ok, -1 error e -2 cancelamento.
*/
int alterarNomeDept(int qtdDept) { //TERMINADA_DEPT_1.2
    int resp, codigo, i;
    system("clear"); //Se for windows mude para "cls"

    if(qtdDept <= 0) {
        printf("Nao ha departamentos cadastrados na empresa para alterar o nome.\n");
        return -1;
    }

    do {
        printf("Digite o codigo do departamento:\n-> ");
        scanf("%d", &codigo);

        if(checkCodigoDept(qtdDept, codigo) != -1) {
            printf("Codigo %d invalido.\n", codigo);
            do{
                printf("Deseja inserir um novo? (1 - s | 0 - n) \n-> ");
                scanf("%d", &resp);

                if(resp == 0) {
                    printf("Operacao cancelada.\n");
                    return -2;
                }
            }while(resp != 1);
        }
    } while(checkCodigoDept(qtdDept, codigo) != -1);

    i = returnIndiceDept(codigo, qtdDept);

    clearBuffer();

    printf("Nome atual do departamento: %s\n", dept[i].nome);

    printf("Digite o novo nome do departamento:\n-> ");
    checkInput(fgets(dept[i].nome, 100, stdin));

    printf("Nome alterado com sucesso para %s.\n", dept[i].nome);

    return 0;
}
/*
* Nome: consultarDept(consultar um departamento).
* Função: consulta as informações de um departamento da empresa.
* Funcionamento: Recebe apenas a quantidade de departamentos cadastrados na empresa.
* Primeiro se pede um código e após isso faz a checagem se o código existe ou não, caso exista
* é percorrido em um laço de repetição por todos os departamentos cadastrados e caso o código
* digitado seja igual ao de um departamento cadastrado, ele retorna as informações do mesmo.
* Retorno: void.
*/
void consultarDept(int qtdDept) { //TERMINADA_DEPT_1.3
    int codigo, i;
    system("clear"); //Se for windows mude para "cls"

    if(qtdDept <= 0) {
        printf("Nao ha departamentos cadastrados na empresa para se consultar.\n");
        return;
    }

    printf("Digite o codigo do departamento consultado: \n-> ");
    scanf("%d", &codigo);

    for(i = 0; i < qtdDept; i++) {
        if(codigo == dept[i].codigo) {
            printf("Nome: %s\n", dept[i].nome);
            printf("Quantidade de Func.: %d\n", dept[i].quantidadeFuncDept);

            return;
        }
    }

    printf("Codigo %d invalido.\n", codigo);
    return;
}
/*
* Nome: listarDept(listar todos os departamentos).
* Função: consulta as informações de todos os departamentos da empresa.
* Funcionamento: Recebe apenas a quantidade de departamentos cadastrados na empresa.
* É percorrido em um laço de repetição por todos os departamentos cadastrados retornando as informações do mesmo.
* Caso não exista departamentos, ele retorna uma mensagem de erro.
* Retorno: void.
*/
void listarDept(int qtdDept) { //TERMINADA_DEPT_1.4
    int i;
    system("clear"); //Se for windows mude para "cls"

    if(qtdDept <= 0) {
        printf("Nao ha departamentos cadastrados na empresa para se listar.\n");
        return;
    }

    for(i = 0; i < qtdDept; i++) {
        printf("\n<--- Dept %d --->\n", i);
        printf("Codigo: %d\n", dept[i].codigo);
        printf("Nome: %s\n", dept[i].nome);
        printf("QtdFunc: %d\n", dept[i].quantidadeFuncDept);
    }
}
/*
* Nome: excluirDept(excluir um departamento).
* Função: excluir um departamento da empresa.
* Funcionamento: Recebe apenas a quantidade de departamentos cadastrados (ponteiro) na empresa.
* Primeiro se pede um código e após isso faz a checagem se o código existe ou não, caso exista
* é atribuida a uma variável iDept o índice do departamento que está sendo referenciado e se verifica se o mesmo
* possui funcionarios cadastrados e caso possua a exclusão não é permitida, caso não posssua se pede para digitar
* S ou N para se excluir o departamento.
* Retorno: 0 se ok, -1 error e -2 cancelamento.
*/
int excluirDept(int *qtdDept) { //TERMINADA_DEPT_1.5
    int iDept, j, codigo, resp;
    char resp2 = 'x';
    system("clear"); //Se for windows mude para "cls"

    if(*qtdDept <= 0) {
        printf("Nao ha departamentos cadastrados na empresa para se excluir.\n");
        return -1;
    }

    do{
        do {
            printf("Digite o codigo do departamento:\n-> ");
            scanf("%d", &codigo);

            if(checkCodigoDept(*qtdDept, codigo) != -1) {
                printf("Codigo %d invalido.\n", codigo);
                do{
                    printf("Deseja inserir um novo? (1 - s | 0 - n) \n-> ");
                    scanf("%d", &resp);

                    if(resp == 0) {
                        printf("Operacao cancelada.\n");
                        return -2;
                    }
                }while(resp != 1);
            }
        } while(checkCodigoDept(*qtdDept, codigo) != -1);

        iDept = returnIndiceDept(codigo, *qtdDept);

        printf("Nome: %s\n", dept[iDept].nome);
        printf("QtdFunc: %d\n", dept[iDept].quantidadeFuncDept);

        if(dept[iDept].quantidadeFuncDept > 0) {
            printf("Departamento %d possui funcionarios cadastrados.\n", codigo);
            do {
                printf("Deseja inserir um novo codigo? (1 - s | 0 - n) \n-> ");
                scanf("%d", &resp);

                if(resp == 0) {
                    printf("Operacao cancelada.\n");
                    return -2;
                }
            } while(resp != 1);
        } else
            resp = 0;
    } while(resp != 0);

    while(resp2 != 'S' || resp2 != 's' || resp2 != 'n' || resp2 != 'N') {
        printf("Deseja realmente exluir o departamento %d? <s|n> \n-> ", codigo);
        scanf(" %c", &resp2);

        if(resp2 == 'S' || resp2 == 's') {
            for(j = iDept; j < *qtdDept ; j++) {
                dept[j] = dept[j + 1];
                controle[0][j + 1] = controle[0][j + 2];
                controle[1][j + 1] = controle[1][j + 2];
            }
            *qtdDept -= 1;

            if(*qtdDept < 0)
                *qtdDept = 0;

            printf("Departamento %d excluido com sucesso.\n", codigo);
            break;
        } else if(resp2 == 'N' || resp2 == 'n') {
            printf("Departamento %d nao foi excluido.\n", codigo);
            return -2;
        }
    }

    return 0;
}

/*
* Nome: gravarArquivos(gravar em arquivo).
* Função: gravar as informações referentes ao vetor de departamento e funcionario.
* Funcionamento: Recebe a quantidade de departamentos e funcionarios cadastrados na empresa e a quantidade de funcionarios excluidos(Demitidos).
* É criado o arquivo para escrita em binário (WB) dos departamentos e gravados os dados do departamento 1 por 1.
* Após a gravação dos departamentos o arquivos departamento.bin é fechado e é aberto o outro de nome funcionario.bin
* Os funcionarios são gravados por ordem de departamento, 1 por 1, ignorando os buracos (funcionarios excluidos).
* Retorno: 0 se ok, -1 error.
*/
int gravarArquivos(int qtdFunc, int qtdFuncEx, int qtdDept) { //TERMINADA_ARQ_1.1
    int i, j;
    FILE *fileFunc, *fileDept;

    fileDept = fopen(ARQ_DEPT, "wb");

    if(!fileDept) {
        printf("ErrorFileDeptCreation.\n");
        return -1;
    }

    for(i = 0; i < qtdDept; i++) {
        fwrite(&dept[i], sizeof(tDepartamento), 1, fileDept);
    }

    fclose(fileDept);

    fileFunc = fopen(ARQ_FUNC, "wb");

    if(!fileFunc) {
        printf("ErrorFileFuncCreation.\n");
        return -1;
    }

    for(i = 0; i < qtdDept; i++) {
        printf("\n<--- DEPT %d --->\n", dept[i].codigo);
        for(j = 0; j < qtdFunc + qtdFuncEx; j++) {
            if(func[j].dept == -1)
                continue;
            if(func[j].dept == dept[i].codigo) {
                printf("func %d salvo.\n", j + 1);
                fwrite(&func[j], sizeof(tFuncionario), 1, fileFunc);
            }
        }
    }

    fclose(fileFunc);

    return 0;
}
/*
* Nome: recuperarArquivos(recupera de arquivo).
* Função: recupera as informações referentes ao vetor de departamento e funcionario.
* Funcionamento: Procura por dois arquivos de nome funcionario.bin e departamento.bin.
* Caso o arquivo dos departamentos não exista, o programa não restaura as informações, caso exista ele restaura os departamentos de 1 por 1.
* Após a recuperação dos departamentos é feita a recuperação dos funcionários 1 por 1, fazendo as devidas alterações no seu prox[i].
* Os funcionarios são recuperados por ordem de departamento, 1 por 1, ignorando os buracos (funcionarios excluidos).
* Retorno: 0 se ok, -1 error.
*/
int recuperarArquivos(int *qtdFunc, int *qtdFuncEx, int *qtdDept) { //TERMINADA_ARQ_1.2
    int iDept, iFunc, auxFunc = 0, auxDept = 0, temp = 0;
    FILE *fileFunc, *fileDept;

    //Recuperar Departamentos
    fileDept = fopen(ARQ_DEPT, "rb");

    if(!fileDept) {
        printf("ErrorOpenFileDept.\n");
        return -1;
    } else {
        for(iDept = 0; iDept < TAM_DEPT; iDept++) {
            if(fread(&dept[iDept], sizeof(tDepartamento), 1, fileDept) == 1) {
                auxDept++;
                controle[0][iDept + 1] = dept[iDept].codigo;
            } else
                break;
        }

        printf("%d departamentos recuperados.\n", auxDept);
        *qtdDept = auxDept;
    }

    fclose(fileDept);

    fileFunc = fopen(ARQ_FUNC, "rb");

    if(!fileFunc) {
        printf("ErrorOpenFileFunc.\n");
        return -1;
    } else {
        for(iDept = 0; iDept < *qtdDept; iDept++) {
            for(iFunc = auxFunc, auxFunc = 0; auxFunc < dept[iDept].quantidadeFuncDept; iFunc++) {
                if(fread(&func[iFunc], sizeof(tFuncionario), 1, fileFunc) == 1) {
                    *qtdFunc += 1;
                    auxFunc++;
                    controle[1][0] += 1;

                    prox[*qtdFunc - 1] = controle[1][iDept + 1];
                    controle[1][iDept + 1] = *qtdFunc - 1;

                } else
                    break;
            }
            if(dept[iDept].quantidadeFuncDept == 0) {
              controle[1][iDept + 1] = -1;
            }

            prox[temp] = -1;
            temp = iFunc;
            auxFunc = iFunc;
        }
    }

    printf("%d funcionarios recuperados.\n", *qtdFunc);

    return 0;
}
/*
* Nome: checkCodigoDept(checa o código de um departamento).
* Função: faz a checagem se o código digitado é igual a já um existente.
* Funcionamento: Recebe a quantidade de departamento e um código.
* Se a quantidade de departamentos for igual a 0, então significa que não precisa de checagem.
* Caso seja maior que 0, é rodado um laço pra procurar um código igual, se encontrar, a checagem para.
* Retorno: 0 se ok, -1 se possuí código igual.
*/
int checkCodigoDept(int qtdDept, int codigo) { //TERMINADA_CHECK_1.1
    int i;

	if(qtdDept == 0)
		return 0;
	else
		for(i = 0; i < qtdDept; i++)
			if(codigo == dept[i].codigo)
			    return -1;
    return 0;
}
/*
* Nome: checkCpfFunc(checa o cpf de um funcionario).
* Função: faz a checagem se o cpf digitado é igual a já um existente.
* Funcionamento: Recebe a quantidade de funcionarios e funcionarios excluidos e um cpf.
* Se a quantidade de funcionarios for igual a 0, então significa que não precisa de checagem.
* Caso seja maior que 0, é rodado um laço pra procurar um cpf igual, se encontrar, a checagem para.
* Retorno: 0 se ok, -1 se possuí cpf igual.
*/
int checkCpfFunc(int qtdFunc, char cpf[], int qtdFuncEx) { //TERMINADA_CHECK_1.2
    int i;

    if(qtdFunc == 0)
        return 0;
    else
        for(i = 0; i < qtdFunc + qtdFuncEx; i++) {
            if(strcmp(func[i].cpf, cpf) == 0)
                return -1;;
        }
    return 0;
}
/*
* Nome: checkValidDate(checa se uma data é válida).
* Função: faz a checagem se uma data é válida.
* Funcionamento: Recebe um dia, mês e ano e checa se a data é valida dentro de determinados critérios.
* Se o ano está entre 1900 e 2100. Se o mês está entre 1 e 12, e se dependendo do ano (bissexto) e do mês.
* o dia pode estar entre 1 e 31.
* Retorno: 0 se ok, -1 se possuí cpf igual.
*/
int checkValidDate(int dia, int mes, int ano) { //TERMINADA_CHECK_1.3
    if(ano >= 1900 && ano <= 2100) {
        if(mes >= 1 && mes <= 12) {
            switch(mes) {
                case 1: if(dia > 0 && dia <= 31) return 0; else return -1;  break;
                case 2:
                    if(ano % 4 == 0 && (ano % 400 == 0 || ano % 100 != 0)) {
                        if(dia > 0 && dia <= 29)
                            return 0;
                        else
                            return -1;
                        break;
                    } else
                        if(dia > 0 && dia <= 28)
                            return 0;
                        else
                            return -1;
                        break;
                case 3: if(dia > 0 && dia <= 31) return 0; else return -1;  break;
                case 4: if(dia > 0 && dia <= 30) return 0; else return -1;  break;
                case 5: if(dia > 0 && dia <= 31) return 0; else return -1;  break;
                case 6: if(dia > 0 && dia <= 30) return 0; else return -1;  break;
                case 7: if(dia > 0 && dia <= 31) return 0; else return -1;  break;
                case 8: if(dia > 0 && dia <= 31) return 0; else return -1;  break;
                case 9: if(dia > 0 && dia <= 30) return 0; else return -1;  break;
                case 10: if(dia > 0 && dia <= 31) return 0; else return -1;  break;
                case 11: if(dia > 0 && dia <= 30) return 0; else return -1;  break;
                case 12: if(dia > 0 && dia <= 31) return 0; else return -1;  break;
                default: printf("Error checkValidData.\n");
            }
        } else
            return -1;
    } else
        return -1;
}
/*
* Nome: checkInput.
* Função: remover um \n de uma string e adicionar o \0 no local.
* Funcionamento: Recebe um ponteiro de um char e verifica a última posição do mesmo.
* Se for igual a um \n, ele troca por um \0.
* Retorno: void.
*/
void checkInput(char *input) { //TERMINADA_CHECK_1.4
    if(input[strlen(input) - 1] == '\n')
    input[strlen(input) - 1] = '\0';
    else
    while(getchar() != '\n');
}
/*
* Nome: returnIndiceDept(retorna um índice de um departamento específico).
* Função: retorna o índice de um departamento com base no código.
* Funcionamento: Recebe a quantidade de departamentos e um código e checa se existe um código igual.
* Caso exista, a checagem para e retorna o índice do departamento.
* Retorno: i.
*/
int returnIndiceDept(int codigo, int qtdDept) { //TERMINADA_RETURN_IDEPT
    int i;

    for(i = 0; i < qtdDept; i++)
        if(codigo == dept[i].codigo)
            break;

    return i;
}
/*
* Nome: returnIndiceFunc(retorna um índice de um funcionario específico).
* Função: retorna o índice de um funcionario com base no cpf.
* Funcionamento: Recebe a quantidade de funcionarios e um cpf e checa se existe um cpf igual.
* Caso exista, a checagem para e retorna o índice do funcionario.
* Retorno: i.
*/
int returnIndiceFunc(char cpf[], int qtdFunc, int qtdFuncEx) { //TERMINADA_RETURN_IFUNC
    int i;

    for(i = 0; i < qtdFunc + qtdFuncEx; i++)
        if(strcmp(func[i].cpf, cpf) == 0)
            break;

    return i;
}
/*
* Nome: clearBuffer(limpar o buffer).
* Função: Evita o caracter que fica pendente em determinada leitura.
* Funcionamento: Quando a função é chamada ela vai ler um caracter enquanto for diferente de EOF
* (End of File) e diferente de \n. Ou seja, evita o \n ou outro char de uma leitura anterior.
* Retorno: void.
*/
void clearBuffer() { //TERMINADA_CLEAR_BUFFER
	int ch;
	while ((ch = getchar()) != EOF && ch != '\n');
}

void imprimeFuncProxCont(int qtdFunc, int qtdFuncEx) {
    int i, j;

    // Imprime Func
    printf("deptFunc ");
    for(i = 0; i < qtdFunc + qtdFuncEx; i++) {
        if(func[i].dept < 0)
            printf("|%d |", func[i].dept);
        else
            printf("| %d | ", func[i].dept);
    }
    printf("\n");
    printf("cpfFunc  ");
    for(i = 0; i <  qtdFunc + qtdFuncEx; i++) {
        printf("| %s | ", func[i].cpf);
    }
    printf("\n\n");
    //---------------------------------------------------------------------//

    // ImprimeProx
    printf("proxI ");
    for(i = 0; i < qtdFunc + qtdFuncEx; i++) {
        printf("| %d | ", i);
    }

    printf("\n");
    printf("prox  ");
    for(i = 0; i < qtdFunc + qtdFuncEx; i++) {
        if(prox[i] < 0)
            printf("|%d | ", prox[i]);
        else
            printf("| %d | ", prox[i]);
    }

    printf("\n\n");
    //---------------------------------------------------------------------//

    // Imprime Controle
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 11; j++) {
            if(controle[i][j] < 0)
            printf("|%d | ", controle[i][j]);
            else
            printf("| %d | ", controle[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
}
