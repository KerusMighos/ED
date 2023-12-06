#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <windows.h>

typedef int TipoChave;

typedef struct TipoCelula *Apontador;

typedef struct
{
    int ID;
    int idTurma;

    char nomeProfessor[80];
    char disciplina[50];

} TipoProfessor;

typedef struct
{
    int ID;
    int idTurma;

    char nomeAluno[80];
    int idade;

} TipoAluno;

typedef struct
{
    int ID;

    char nomeDoCurso[50];
    int cargaHoraria;
    char descricaoCurso[500];

} TipoCurso;

typedef struct
{
    int ID;
    int idProfessor;

} TipoTurma;

typedef union
{
    TipoAluno aluno;
    TipoCurso curso;
    TipoTurma turma;
    TipoProfessor professor;

} TipoItem;

struct TipoCelula
{
    TipoItem Item;
    Apontador Prox;
};

typedef struct
{
    Apontador Primeiro, Ultimo;
    int TagTipo;
    int tamanho;

} TipoLista;

TipoLista AlunosInstancia, CursosInstancia, TurmasInstancia, ProfessoresInstancia;

void Inicia(TipoLista *Lista)
{
    Lista->Primeiro = (Apontador)malloc(sizeof(struct TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
    Lista->tamanho = 0;
}

int Vazia(TipoLista *Lista)
{
    return (Lista->Primeiro == Lista->Ultimo);
}

void Insere(TipoItem *x, TipoLista *Lista)
{
    Lista->Ultimo->Prox = (Apontador)malloc(sizeof(struct TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = *x;
    Lista->Ultimo->Prox = NULL;
    Lista->tamanho++;
}

void Imprime1Aluno(TipoAluno aluno)
{

    printf("Matrícula: %d\n", aluno.ID);
    printf("Nome: %s\n", aluno.nomeAluno);
    printf("\n");
};

void Imprime1Curso(TipoCurso curso)
{

    printf("Nome do Curso: %s\n", curso.nomeDoCurso);
    printf("Carga Horária: %d horas\n", curso.cargaHoraria);
    printf("ID do Curso: %d\n", curso.ID);
    printf("Descrição do Curso: %s\n", curso.descricaoCurso);
    printf("\n");
};
void Imprime1Turma(TipoTurma turma)
{

    printf("Identificador da Turma: %d\n", turma.ID);
    printf("Professor Responsável: %d\n", turma.idProfessor);
};

void Imprime1Professor(TipoProfessor professor)
{
    printf("Nome do Professor: %s\n", professor.nomeProfessor);
    printf("Disciplina Lecionada: %s\n", professor.disciplina);
    printf("\n");
};

void ImprimeLista(TipoLista Lista)
{
    Apontador Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL)
    {

        TipoItem itemNow = Aux->Item;

        switch (Lista.TagTipo)
        {
        case 1:
            Imprime1Aluno(itemNow.aluno);
            break;
        case 2:
            Imprime1Curso(itemNow.curso);
            break;
        case 3:
            Imprime1Turma(itemNow.turma);
            break;
        case 4:
            Imprime1Professor(itemNow.professor);
            break;
        default:
            break;
        }

        Aux = Aux->Prox;
    }
}

void DestroiLista(TipoLista *Lista)
{
    Apontador Aux = Lista->Primeiro;
    while (Aux != NULL)
    {
        Apontador temp = Aux;
        Aux = Aux->Prox;
        free(temp);
    }
    Lista->Primeiro = Lista->Ultimo = NULL;
    Lista->tamanho = 0;
}

TipoItem *getById(int idToSearch, TipoLista Lista)
{

    Apontador Aux;
    Aux = Lista.Primeiro;

    while (Aux != NULL)
    {

        TipoItem *itemNow = &(Aux->Item);

        switch (Lista.TagTipo)
        {
        case 1:
            if (itemNow->aluno.ID == idToSearch)
            {
                return itemNow;
            }
            break;
        case 2:
            if (itemNow->curso.ID == idToSearch)
            {
                return itemNow;
            }
            break;
        case 3:
            if (itemNow->turma.ID == idToSearch)
            {
                return itemNow;
            }
            break;
        case 4:
            if (itemNow->professor.ID == idToSearch)
            {
                return itemNow;
            }
            break;
        default:
            break;
        }

        Aux = Aux->Prox;
    }

    return NULL;
}

void cadastraAluno()
{

    TipoAluno newAluno;

    printf("Digite o nome do aluno: ");
    getchar();
    fgets(newAluno.nomeAluno, sizeof(newAluno.nomeAluno), stdin);
    newAluno.nomeAluno[strcspn(newAluno.nomeAluno, "\n")] = '\0';
    // Adicionei a função getchar para resolver o bug e limpar o buffer do teclado

    printf("Digite a matricula do aluno: (apenas numeros)");

    scanf("%d", &newAluno.ID);

    if (getById(newAluno.ID, AlunosInstancia))
    {
        printf("Essa matricula ja está em uso!!!");
        return;
    }

    system("cls");
    printf("Aluno Cadastrado com Sucesso !\n");
    printf("Aguarde alguns segundos para retornar ao Menu Principal");

    // Sleep(3000);   // NÃO APAGAR ESSA FUNÇÃO DEFINE O TEMPO DE TELA
    system("cls"); // LIMPA A TELA NO WINDOWS

    TipoItem item;
    item.aluno = newAluno;
    Insere(&item, &AlunosInstancia);
};

void cadastraCurso()
{

    TipoCurso newCurso;

    printf("Digite o nome do curso: ");
    getchar(); // Adicionei a função getchar para resolver o bug e limpar o buffer do teclado.
    fgets(newCurso.nomeDoCurso, sizeof(newCurso.nomeDoCurso), stdin);
    newCurso.nomeDoCurso[strcspn(newCurso.nomeDoCurso, "\n")] = '\0';

    printf("Digite a carga horaria do curso: ");
    getchar(); // Adicionei a função getchar para resolver o bug e limpar o buffer do teclado.
    scanf("%d", &newCurso.cargaHoraria);

    printf("Digite o ID do curso: (apenas numeros)");
    getchar(); // Adicionei a função getchar para resolver o bug e limpar o buffer do teclado.
    scanf("%d", &newCurso.ID);

    printf("Digite a descrição do curso: ");
    getchar(); // Adicionei a função getchar para resolver o bug e limpar o buffer do teclado.
    fgets(newCurso.descricaoCurso, sizeof(newCurso.descricaoCurso), stdin);
    newCurso.descricaoCurso[strcspn(newCurso.descricaoCurso, "\n")] = '\0';
    system("cls");

    if (getById(newCurso.ID, CursosInstancia))
    {
        printf("Esse id de curso já em uso!!!");
        return;
    }

    printf("Curso cadastrado com sucesso !");
    printf("Aguarde alguns segundos para retornar ao Menu Principal");
    // Sleep(3000);

    printf("Curso cadastrado com sucesso !\n");
    printf("Aguarde alguns segundos para retornar ao Menu Principal");
    // Sleep(3000);
    system("cls");

    TipoItem item;
    item.curso = newCurso;
    Insere(&item, &CursosInstancia);
};
void cadastraTurma()
{

    TipoTurma newTurma;

    printf("Digite o número de identificação de turma: ");
    getchar(); // Adicionei a função getchar para resolver o bug e limpar o buffer do teclado.
    scanf("%d", &newTurma.ID);

    if (getById(newTurma.ID, TurmasInstancia))
    {
        printf("Esse id de turma já em uso!!!");
        return;
    }

    TipoItem item;
    item.turma = newTurma;
    Insere(&item, &TurmasInstancia);

    printf("Número registrado com sucesso !\n");
    printf("Aguarde alguns instantes para retornar ao Menu Principal");
    // Sleep(3000); //NÃO APAGAR ESSA FUNÇÃO DEFINE O TEMPO DE TELA
    system("cls"); // LIMPA A TELA NO WINDOWS
};
void cadastraProfessor()
{

    TipoProfessor newProfessor;

    printf("Digite o nome do Professor: ");
    getchar(); // Adicionei a função getchar para resolver o bug e limpar o buffer do teclado
    fgets(newProfessor.nomeProfessor, sizeof(newProfessor.nomeProfessor), stdin);
    newProfessor.nomeProfessor[strcspn(newProfessor.nomeProfessor, "\n")] = '\0';

    printf("Digite o nome da disciplina a ser lecionada pelo mesmo: ");
    getchar(); // Adicionei a função getchar para resolver o bug e limpar o buffer do teclado
    fgets(newProfessor.disciplina, sizeof(newProfessor.disciplina), stdin);
    newProfessor.disciplina[strcspn(newProfessor.disciplina, "\n")] = '\0';
    getchar(); // Adicionei a função getchar para resolver o bug e limpar o buffer do teclado

    if (getById(newProfessor.ID, ProfessoresInstancia))
    {
        printf("Esse id de professor já em uso!!!");
        return;
    }

    TipoItem item;
    item.professor = newProfessor;
    Insere(&item, &ProfessoresInstancia);
};

void matriculaAlunoEmTurma()
{

    int idTurma, idAluno;

    printf("Digite a matricula do aluno: (apenas numeros)");
    scanf("%d", &idAluno);

    printf("Digite o ID da turma desejado: ");
    scanf("%d", &idTurma);

    if (!getById(idAluno, AlunosInstancia) || !getById(idTurma, TurmasInstancia))
    {
        printf("Aluno ou turma nao encontrado!\n");
        return;
    }

    getById(idAluno, AlunosInstancia)->aluno.idTurma = idTurma; // TODO

    printf("Matricula realizada com sucesso!\n");
};
void designacaoProfessores()
{
    int idTurma, idProfessor;

    printf("Digite o ID do professor: (apenas numeros)");
    scanf("%d", &idProfessor);

    printf("Digite o ID da turma desejado: ");
    scanf("%d", &idTurma);

    if (!getById(idProfessor, ProfessoresInstancia) || !getById(idTurma, TurmasInstancia))
    {
        printf("Professor ou turma nao encontrado!\n");
        return;
    }

    getById(idProfessor, ProfessoresInstancia)->professor.idTurma = idTurma; // TODO

    printf("Matricula realizada com sucesso!\n");
};

// void listaAlunos(){};
// void listaCursos(){};
// void listaTurmas(){};
// void listaProfessores(){};

void Menu()
{
    int continua = 1;
    int opcao = 0;
    int opcaoEncerrar;
    printf("==== Escola Desenvolver ====\n");
    printf("   _________  \n");
    printf("  /         \\  \n");
    printf(" |           | \n");
    printf(" | [ ]   [ ] |\n");
    printf(" |           |\n");
    printf(" |Bem vindos!|\n");
    printf(" |___________|\n");
    printf(" |           |\n");
    printf(" |           |\n");
    printf(" |___________|\n");
    printf("A aprendizagem é a única coisa que a mente nunca se cansa, nunca tem medo e nunca se arrepende.- Leonardo da Vinci");
    // Sleep(5000);
    system("cls");

    printf("Desenvolvido por: \nAdriano Victor N. Ribeiro\nAntônio Salgueiro Fernandes\nFilipe da Silva Ribeiro\nJoão Vitor Buissine\n");
    // Sleep (10000);
    system("cls");
    while (continua)
    {
        printf("1 - Cadastrar Aluno\n");
        printf("2 - Cadastrar Curso\n");
        printf("3 - Matrícula em Cursos\n");
        printf("4 - Cadastrar Turma\n");
        printf("5 - Designação de Professores\n");
        printf("6 - Lista Alunos\n");
        printf("7 - Lista Cursos\n");
        printf("8 - Lista Turmas\n");
        printf("9 - Lista Professores\n");
        printf("10 - Finalizar Sessão \n");
        printf("Digite o numero da opcao desejada: ");

        scanf("%d", &opcao);
        system("cls");
        switch (opcao)
        {
        case 1:
            cadastraAluno();

            break;
        case 2:
            cadastraCurso();
            break;
        case 3:
            matriculaAlunoEmTurma();
            break;
        case 4:
            cadastraTurma();
            break;
        case 5:
            designacaoProfessores();
            break;
        case 6:
            ImprimeLista(AlunosInstancia);
            break;
        case 7:
            ImprimeLista(CursosInstancia);
            break;
        case 8:
            ImprimeLista(TurmasInstancia);
            break;
        case 9:
            ImprimeLista(ProfessoresInstancia);
            break;
        case 10:
            printf("Deseja encerrar o programa ? (1) = Sim - (AnyKey) = Não\n");
            printf("");
            scanf("%d", &opcaoEncerrar);
            system("cls");
            if (opcaoEncerrar == 1)
            {
                printf("O programa será finalizado em alguns instantes !\n");
                printf("Obrigado por utilizar o nosso serviço \n");
                // Sleep (3000);
                continua = 0;
                break;
            }
            else
            {
                break;
            }
            break;
        default:
            printf("Digite uma opcao valida!!!\n");
            break;
        }
    }
}

int Confirma()
{
    int op;
    printf("Voce confirma? (0 cancela)");
    scanf("%d", &op);
    return op;
}

int main()
{
    // setlocale (LC_ALL, "Portuguese");
    Inicia(&AlunosInstancia);
    Inicia(&CursosInstancia);
    Inicia(&TurmasInstancia);
    Inicia(&ProfessoresInstancia);

    AlunosInstancia.TagTipo = 1;
    CursosInstancia.TagTipo = 2;
    TurmasInstancia.TagTipo = 3;
    ProfessoresInstancia.TagTipo = 4;

    Menu();

    return 0;
}