/*

\subsubsection{Cadastro de alunos com cálculo de média}

Desenvolva um programa que gerencie o cadastro de alunos utilizando estruturas.
O programa deve armazenar informações básicas de cada aluno e calcular a média de suas notas.

\textbf{Especificações:}

Crie uma estrutura chamada \texttt{Aluno} contendo os campos: \texttt{nome} (\texttt{string} de até 64 caracteres), \texttt{matrícula} (\texttt{int}), \texttt{nota1}, \texttt{nota2} e \texttt{nota3} (\texttt{float}). Implemente uma função \texttt{float calcularMedia(Aluno aluno)} que retorne a média aritmética das três notas. No programa principal, permita ao usuário cadastrar até 5 alunos, armazenando-os em um vetor de estruturas. Após o cadastro, exiba todos os alunos com suas respectivas médias e informe quem obteve a maior média da turma.

\subsubsection{Caso de Teste 1}
\begin{itemize}
    \item Entrada: Nome: ``João Silva'', Matrícula: 2023001, Notas: 7.5, 8.0, 9.0
    \item Saída: Média: 8.17
\end{itemize}

\subsubsection{Caso de Teste 2}
\begin{itemize}
    \item Entrada: Nome: ``Maria Santos'', Matrícula: 2023002, Notas: 10.0, 9.5, 10.0
    \item Saída: Média: 9.83
\end{itemize}

\subsubsection{Caso de Teste 3}
\begin{itemize}
    \item Entrada: 3 alunos cadastrados
    \item Aluno 1: ``Pedro'', Matrícula: 2023003, Notas: 6.0, 7.0, 6.5 (Média: 6.50)
    \item Aluno 2: ``Ana'', Matrícula: 2023004, Notas: 9.0, 8.5, 9.5 (Média: 9.00)
    \item Aluno 3: ``Carlos'', Matrícula: 2023005, Notas: 7.0, 7.5, 8.0 (Média: 7.50)
    \item Saída: Maior média: Ana com 9.00
\end{itemize}

*/

#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 8
#define TAM_NOME 64

typedef struct {
  char nome[TAM_NOME];
  int matricula;
  float nota1;
  float nota2;
  float nota3;
} Aluno;

float calcularMedia(Aluno aluno) {
  return (aluno.nota1 + aluno.nota2 + aluno.nota3) / 3;
}

void cadastrarAluno(Aluno *aluno) {
  printf("Nome: ");
  getchar();
  fgets(aluno->nome, TAM_NOME, stdin);
  aluno->nome[strcspn(aluno->nome, "\n")] = '\0';

  printf("Matrícula: ");
  scanf("%d", &aluno->matricula);

  printf("Nota 1: ");
  scanf("%f", &aluno->nota1);

  printf("Nota 2: ");
  scanf("%f", &aluno->nota2);

  printf("Nota 3: ");
  scanf("%f", &aluno->nota3);
}

void exibirAluno(Aluno aluno, float media) {
  printf("Nome: %s\n", aluno.nome);
  printf("Matrícula: %d\n", aluno.matricula);
  printf("Notas: %.2f, %.2f, %.2f\n", aluno.nota1, aluno.nota2, aluno.nota3);
  printf("Média: %.2f\n", media);
}

int encontrarMaiorMedia(Aluno alunos[], int qtd) {
  int indiceMaior = 0;
  float maiorMedia = calcularMedia(alunos[0]);

  for (int i = 1; i < qtd; i++) {
    float media = calcularMedia(alunos[i]);
    if (media > maiorMedia) {
      maiorMedia = media;
      indiceMaior = i;
    }
  }

  return indiceMaior;
}

int main(int argc, char *argv[]) {
  Aluno alunos[MAX_ALUNOS];
  int qtdAlunos;

  do {
    printf("Quantos alunos deseja cadastrar? (1 a %d): ", MAX_ALUNOS);
    scanf("%d", &qtdAlunos);

    if (qtdAlunos < 1 || qtdAlunos > MAX_ALUNOS) {
      printf("Quantidade inválida! Digite um valor entre 1 e %d.\n", MAX_ALUNOS);
    }
  } while (qtdAlunos < 1 || qtdAlunos > MAX_ALUNOS);

  for (int i = 0; i < qtdAlunos; i++) {
    printf("Aluno %d\n", i + 1);
    cadastrarAluno(&alunos[i]);
  }

  printf("ALUNOS CADASTRADOS\n");

  for (int i = 0; i < qtdAlunos; i++) {
    printf("Aluno %d\n", i + 1);
    float media = calcularMedia(alunos[i]);
    exibirAluno(alunos[i], media);
  }

  int indiceMaior = encontrarMaiorMedia(alunos, qtdAlunos);
  float maiorMedia = calcularMedia(alunos[indiceMaior]);

  printf("MAIOR MÉDIA\n");
  printf("Aluno: %s\n", alunos[indiceMaior].nome);
  printf("Média: %.2f\n", maiorMedia);

  return 0;
}
