/*

\subsubsection{Contador de palavras em arquivo de texto}

Desenvolva um programa que leia um arquivo de texto e conte quantas palavras ele contém, exibindo também o número de linhas e caracteres.

\textbf{Especificações:}

O programa deve solicitar ao usuário o nome do arquivo a ser analisado. Implemente a função \texttt{void analisar(char *arquivo, int *linhas, int *palavras, int *caracteres)} que recebe ponteiros para armazenar as contagens e processa o arquivo.
Considere que palavras são sequências de caracteres separadas por espaços, tabs ou quebras de linha.
Trate adequadamente erros de abertura de arquivo, exibindo mensagem apropriada se o arquivo não existir.
Ao final, exiba um resumo com o total de linhas, palavras e caracteres encontrados.

\subsubsection{Caso de Teste 1}
\begin{itemize}
  \item Conteúdo do arquivo ``texto1.txt'':
  \item ``Olá mundo!''
  \item Saída: Linhas: 1, Palavras: 2, Caracteres: 11
\end{itemize}

\textbf{Caso de Teste 2}
\begin{itemize}
  \item Conteúdo do arquivo ``texto2.txt'':
  \item ``Primeira linha do texto''
  \item ``Segunda linha aqui''
  \item ``Terceira e última''
  \item Saída: Linhas: 3, Palavras: 9, Caracteres: 57
\end{itemize}

\textbf{Caso de Teste 3}
\begin{itemize}
  \item Entrada: Nome do arquivo: ``inexistente.txt''
  \item Saída: Erro: Arquivo não encontrado
\end{itemize}

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TAM_NOME_ARQUIVO 256

void analisar(char *arquivo, int *linhas, int *palavras, int *caracteres)
{
  FILE *fp;
  char ch;
  int dentroPalavra = 0;

  *linhas = 0;
  *palavras = 0;
  *caracteres = 0;

  fp = fopen(arquivo, "r");

  if (fp == NULL) {
    printf("Arquivo '%s' não encontrado\n", arquivo);
    return;
  }

  while ((ch = fgetc(fp)) != EOF) {
    (*caracteres)++;

    if (ch == '\n') {
      (*linhas)++;
      dentroPalavra = 0;
    } else if (isspace(ch)) {
      dentroPalavra = 0;
    } else if (!dentroPalavra) {
      dentroPalavra = 1;
      (*palavras)++;
    }
  }

  if (*caracteres > 0 && ch != '\n') {
    (*linhas)++;
  }

  fclose(fp);
}

void exibirResumo(char *arquivo, int linhas, int palavras, int caracteres)
{
  printf("Arquivo: %s\n", arquivo);
  printf("Linhas: %d\n", linhas);
  printf("Palavras: %d\n", palavras);
  printf("Caracteres: %d\n", caracteres);
}

int main(int argc, char *argv[])
{
  char nomeArquivo[TAM_NOME_ARQUIVO];
  int linhas, palavras, caracteres;
  int opcao;

  printf("Digite o nome do arquivo: ");
  fgets(nomeArquivo, TAM_NOME_ARQUIVO, stdin);
  nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';

  analisar(nomeArquivo, &linhas, &palavras, &caracteres);

  if (linhas > 0 || palavras > 0 || caracteres > 0) {
    exibirResumo(nomeArquivo, linhas, palavras, caracteres);
  }

  return 0;
}
