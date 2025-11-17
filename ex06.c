/*

\subsubsection{Remoção de registros inativos}

Implemente um sistema que gerencie estudantes em arquivo com funcionalidades de remoção.

\textbf{Especificações:}

Crie uma estrutura \texttt{Estudante} com: ra (\texttt{int}), \texttt{nome} (\texttt{string} de 64 caracteres), \texttt{curso} (\texttt{string} de 32 caracteres), \texttt{semestre} (\texttt{int}), \texttt{coeficiente} (\texttt{float}) e status (\texttt{char}: `A' para ativo, `I' para inativo).
Implemente as seguintes funções: \texttt{void inserir(char *arquivo)} para adicionar novo registro ao final do arquivo, \texttt{void remover(char *arquivo, int id)} que marca o estudante como inativo sem apagar fisicamente o registro, \texttt{void listar(char *arquivo)} que exibe apenas estudantes com status `A', e \texttt{void compactar(char *arquivo)} que remove fisicamente todos os registros marcados como inativos, criando um novo arquivo temporário apenas com registros ativos e substituindo o original.
No programa principal, implemente um menu completo com todas as operações.
Implemente tratamento robusto de erros para todas as operações de arquivo.

\subsubsection{Caso de Teste 1: Operações Básicas}
\begin{itemize}
  \item Inserir: ra: 1492462, Nome: ``Carlos Souza'', Curso: ``Engenharia de Software'', Semestre: 5, Coeficiente: 0.85, Status: `A'
  \item Inserir: ID: 2273119, Nome: ``Paula Lima'', Curso: ``Engenharia de Bioprocessos e Biotecnologia'', Semestre: 3, Coeficiente: 0.9, Status: `A'
  \item Remover: ID: 2273119 (\texttt{status} muda para `I')
  \item Listar ativos: Apenas ``Carlos Souza'' aparece
\end{itemize}

\subsubsection{Caso de Teste 2: Compactação}
\begin{itemize}
  \item Arquivo antes da compactação: 10 registros (6 ativos `A', 4 inativos `I')
  \item Após compactação: 6 registros (todos ativos)
  \item Saída: ``Removidos 4 registros inativos.''
\end{itemize}

\subsubsection{Caso de Teste 3: Arquivo Vazio}
\begin{itemize}
  \item Tentar compactar arquivo com todos registros ativos
  \item Saída: ``Nenhum registro inativo encontrado.''
\end{itemize}

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_NOME 64
#define TAM_CURSO 32
#define ARQUIVO_TEMP "temp_estudantes.dat"

struct estudante {
  int ra;
  char nome[TAM_NOME];
  char curso[TAM_CURSO];
  int semestre;
  float coeficiente;
  char status;
};

void inserir(char *arquivo)
{
  FILE *fp;
  struct estudante est;

  printf("RA: ");
  scanf("%d", &est.ra);
  getchar();

  printf("Nome: ");
  fgets(est.nome, TAM_NOME, stdin);
  est.nome[strcspn(est.nome, "\n")] = '\0';

  printf("Curso: ");
  fgets(est.curso, TAM_CURSO, stdin);
  est.curso[strcspn(est.curso, "\n")] = '\0';

  printf("Semestre: ");
  scanf("%d", &est.semestre);

  printf("Coeficiente (0.0 a 1.0): ");
  scanf("%f", &est.coeficiente);

  est.status = 'A';

  fp = fopen(arquivo, "ab");
  if (fp == NULL) {
    printf("Erro ao abrir arquivo para inserção\n");
    return;
  }

  fwrite(&est, sizeof(struct estudante), 1, fp);
  fclose(fp);

  printf("Estudante cadastrado com sucesso\n");
}

void remover(char *arquivo, int ra)
{
  FILE *fp;
  struct estudante est;
  int encontrado = 0;
  long posicao;

  fp = fopen(arquivo, "r+b");
  if (fp == NULL) {
    printf("Erro ao abrir arquivo\n");
    return;
  }

  while (fread(&est, sizeof(struct estudante), 1, fp) == 1) {
    if (est.ra == ra && est.status == 'A') {
      posicao = ftell(fp) - sizeof(struct estudante);
      est.status = 'I';
      fseek(fp, posicao, SEEK_SET);
      fwrite(&est, sizeof(struct estudante), 1, fp);
      encontrado = 1;
      printf("Estudante marcado como inativo\n");
      break;
    }
  }

  fclose(fp);

  if (!encontrado) {
    printf("Estudante com RA %d não encontrado ou já está inativo\n", ra);
  }
}

void listar(char *arquivo)
{
  FILE *fp;
  struct estudante est;
  int contador = 0;

  fp = fopen(arquivo, "rb");
  if (fp == NULL) {
    printf("Erro ao abrir arquivo ou arquivo não existe\n");
    return;
  }

  printf("ESTUDANTES ATIVOS\n");

  while (fread(&est, sizeof(struct estudante), 1, fp) == 1) {
    if (est.status == 'A') {
      contador++;
      printf("Estudante %d\n", contador);
      printf("RA: %d\n", est.ra);
      printf("Nome: %s\n", est.nome);
      printf("Curso: %s\n", est.curso);
      printf("Semestre: %d\n", est.semestre);
      printf("Coeficiente: %.2f\n", est.coeficiente);
    }
  }

  fclose(fp);

  if (contador == 0) {
    printf("Nenhum estudante ativo encontrado\n");
  } else {
    printf("Total de estudantes ativos: %d\n", contador);
  }
}

void listarTodos(char *arquivo)
{
  FILE *fp;
  struct estudante est;
  int ativos = 0, inativos = 0;

  fp = fopen(arquivo, "rb");
  if (fp == NULL) {
    printf("Erro ao abrir arquivo ou arquivo não existe\n");
    return;
  }

  printf("TODOS OS ESTUDANTES\n");

  while (fread(&est, sizeof(struct estudante), 1, fp) == 1) {
    if (est.status == 'A') {
      ativos++;
      printf("[ATIVO]\n");
    } else {
      inativos++;
      printf("[INATIVO]\n");
    }

    printf("RA: %d\n", est.ra);
    printf("Nome: %s\n", est.nome);
    printf("Curso: %s\n", est.curso);
    printf("Semestre: %d\n", est.semestre);
    printf("Coeficiente: %.2f\n", est.coeficiente);
  }

  fclose(fp);

  printf("Ativos: %d | Inativos: %d | Total: %d\n",
      ativos, inativos, ativos + inativos);
}

void compactar(char *arquivo)
{
  FILE *fpOriginal, *fpTemp;
  struct estudante est;
  int ativos = 0, removidos = 0;

  fpOriginal = fopen(arquivo, "rb");
  if (fpOriginal == NULL) {
    printf("Erro ao abrir arquivo\n");
    return;
  }

  fpTemp = fopen(ARQUIVO_TEMP, "wb");
  if (fpTemp == NULL) {
    printf("Erro ao criar arquivo temporário\n");
    fclose(fpOriginal);
    return;
  }

  while (fread(&est, sizeof(struct estudante), 1, fpOriginal) == 1) {
    if (est.status == 'A') {
      fwrite(&est, sizeof(struct estudante), 1, fpTemp);
      ativos++;
    } else {
      removidos++;
    }
  }

  fclose(fpOriginal);
  fclose(fpTemp);

  if (removidos == 0) {
    printf("Nenhum registro inativo encontrado\n");
    printf("O arquivo já está compactado\n");
    remove(ARQUIVO_TEMP);
  } else {
    remove(arquivo);
    rename(ARQUIVO_TEMP, arquivo);

    printf("Compactação concluída com sucesso\n");
    printf("Registros ativos mantidos: %d\n", ativos);
    printf("Registros inativos removidos: %d\n", removidos);
  }
}

void exibirMenu()
{
  printf("1. Inserir estudante\n");
  printf("2. Remover estudante\n");
  printf("3. Listar estudantes ativos\n");
  printf("4. Listar todos os estudantes\n");
  printf("5. Compactar arquivo\n");
  printf("6. Sair\n");
  printf("Escolha uma opção: ");
}

int main(int argc, char *argv[])
{
  char nomeArquivo[] = "estudantes.dat";
  int opcao, ra;

  printf("Arquivo: %s\n", nomeArquivo);

  do {
    exibirMenu();
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
      case 1:
        inserir(nomeArquivo);
        break;

      case 2:
        printf("Digite o RA do estudante a remover: ");
        scanf("%d", &ra);
        remover(nomeArquivo, ra);
        break;

      case 3:
        listar(nomeArquivo);
        break;

      case 4:
        listarTodos(nomeArquivo);
        break;

      case 5:
        compactar(nomeArquivo);
        break;

      default:
        printf("Opção inválida\n");
    }
  } while (opcao != 6);

  return 0;
}
