/*

\subsubsection{Arquivo CSV com geração de relatório}

Desenvolva um programa que leia um arquivo CSV (valores separados por vírgula) contendo dados de vendas e gere um relatório estatístico em arquivo texto.

\textbf{Especificações:}

O arquivo CSV de entrada terá o formato: data, produto, quantidade, valorUnitario (uma linha por venda).
Implemente a função \texttt{void processar(char *entrada, char *saida)} que lê o CSV, calcula o total de vendas, o produto mais vendido em quantidade, o produto com maior faturamento e o valor médio por venda.
O relatório de saída deve ser gravado em arquivo texto formatado com todas essas informações.
Trate adequadamente linhas vazias ou malformadas no arquivo de entrada.
Implemente validação para garantir que o arquivo de entrada existe antes de processar.

\subsubsection{Caso de Teste 1}
\begin{itemize}
  \item Conteúdo do arquivo ``vendas.csv'':
  \item ``01/11/2025,Notebook,2,2500.00''
  \item ``02/11/2025,Mouse,5,50.00''
  \item ``03/11/2025,Teclado,3,150.00''
  \item Saída em ``relatorio.txt'':
  \item Total de vendas: 5700.00
  \item Produto mais vendido: Mouse (5 unidades)
  \item Maior faturamento: Notebook (5000.00)
  \item Valor médio por venda: 1900.00
\end{itemize}

\subsubsection{Caso de Teste 2}
\begin{itemize}
  \item Arquivo com linha malformada:
  \item ``01/11/2025,Produto1,10,100.00''
  \item ``02/11/2025,Produto2'' (linha incompleta)
  \item ``03/11/2025,Produto3,5,200.00''
  \item Saída: Processadas 2 vendas válidas, 1 linha ignorada
\end{itemize}

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_LINHA 256
#define TAM_NOME 128
#define TAM_DATA 32
#define MAX_VENDAS 1024

struct venda {
  char data[TAM_DATA];
  char produto[TAM_NOME];
  int quantidade;
  float valorUnitario;
  float valorTotal;
};

void processar(char *entrada, char *saida)
{
  FILE *fpEntrada, *fpSaida;
  char linha[TAM_LINHA];
  struct venda vendas[MAX_VENDAS];
  int numVendas = 0;
  int linhasIgnoradas = 0;

  fpEntrada = fopen(entrada, "r");
  if (fpEntrada == NULL) {
    printf("Arquivo '%s' não encontrado\n", entrada);
    return;
  }

  printf("Processando arquivo '%s'\n", entrada);

  while (fgets(linha, TAM_LINHA, fpEntrada) != NULL) {
    linha[strcspn(linha, "\n")] = '\0';

    if (strlen(linha) == 0) {
      continue;
    }

    char data[TAM_DATA], produto[TAM_NOME];
    int quantidade;
    float valorUnitario;

    int resultado = sscanf(linha, "%[^,],%[^,],%d,%f",
      data, produto, &quantidade, &valorUnitario);

    if (resultado == 4) {
      strcpy(vendas[numVendas].data, data);
      strcpy(vendas[numVendas].produto, produto);
      vendas[numVendas].quantidade = quantidade;
      vendas[numVendas].valorUnitario = valorUnitario;
      vendas[numVendas].valorTotal = quantidade * valorUnitario;
      numVendas++;
    } else {
      linhasIgnoradas++;
      printf("Linha malformada ignorada: %s\n", linha);
    }
  }

  fclose(fpEntrada);

  if (numVendas == 0) {
    printf("Nenhuma venda válida encontrada no arquivo\n");
    return;
  }

  float totalVendas = 0.0;
  int indiceMaisVendido = 0;
  int indiceMaiorFaturamento = 0;

  for (int i = 0; i < numVendas; i++) {
    totalVendas += vendas[i].valorTotal;

    if (vendas[i].quantidade > vendas[indiceMaisVendido].quantidade) {
      indiceMaisVendido = i;
    }

    if (vendas[i].valorTotal > vendas[indiceMaiorFaturamento].valorTotal) {
      indiceMaiorFaturamento = i;
    }
  }

  float valorMedio = totalVendas / numVendas;

  fpSaida = fopen(saida, "w");
  if (fpSaida == NULL) {
    printf("Erro ao criar arquivo de saída '%s'\n", saida);
    return;
  }

  fprintf(fpSaida, "RELATÓRIO DE VENDAS\n");
  fprintf(fpSaida, "Arquivo processado: %s\n", entrada);
  fprintf(fpSaida, "Vendas processadas: %d\n", numVendas);

  if (linhasIgnoradas > 0) {
    fprintf(fpSaida, "Linhas ignoradas: %d\n", linhasIgnoradas);
  }

  fprintf(fpSaida, "ESTATÍSTICAS\n");
  fprintf(fpSaida, "Total de vendas: R$ %.2f\n", totalVendas);
  fprintf(fpSaida, "Produto mais vendido: %s (%d unidades)\n",
    vendas[indiceMaisVendido].produto,
    vendas[indiceMaisVendido].quantidade);
  fprintf(fpSaida, "Maior faturamento: %s (R$ %.2f)\n",
    vendas[indiceMaiorFaturamento].produto,
    vendas[indiceMaiorFaturamento].valorTotal);
  fprintf(fpSaida, "Valor médio por venda: R$ %.2f\n", valorMedio);

  fprintf(fpSaida, "DETALHAMENTO DAS VENDAS\n");

  for (int i = 0; i < numVendas; i++) {
    fprintf(fpSaida, "Data: %s\n", vendas[i].data);
    fprintf(fpSaida, "Produto: %s\n", vendas[i].produto);
    fprintf(fpSaida, "Quantidade: %d\n", vendas[i].quantidade);
    fprintf(fpSaida, "Valor Unitário: R$ %.2f\n", vendas[i].valorUnitario);
    fprintf(fpSaida, "Valor Total: R$ %.2f\n", vendas[i].valorTotal);
  }

  fclose(fpSaida);

  printf("Processamento concluído com sucesso\n");
  printf("Vendas processadas: %d\n", numVendas);
  if (linhasIgnoradas > 0) {
    printf("Linhas ignoradas: %d\n", linhasIgnoradas);
  }
  printf("Total de vendas: R$ %.2f\n", totalVendas);
  printf("Relatório salvo em: %s\n", saida);

  printf("RESUMO DO RELATÓRIO\n");
  printf("Total de vendas: R$ %.2f\n", totalVendas);
  printf("Produto mais vendido: %s (%d unidades)\n",
    vendas[indiceMaisVendido].produto,
    vendas[indiceMaisVendido].quantidade);
  printf("Maior faturamento: %s (R$ %.2f)\n",
    vendas[indiceMaiorFaturamento].produto,
    vendas[indiceMaiorFaturamento].valorTotal);
  printf("Valor médio por venda: R$ %.2f\n", valorMedio);
}

int main(int argc, char *argv[])
{
  char arquivoEntrada[TAM_NOME];
  char arquivoSaida[TAM_NOME];

  printf("Nome do arquivo CSV de entrada: ");
  fgets(arquivoEntrada, TAM_NOME, stdin);
  arquivoEntrada[strcspn(arquivoEntrada, "\n")] = '\0';

  printf("Nome do arquivo de saída para o relatório: ");
  fgets(arquivoSaida, TAM_NOME, stdin);
  arquivoSaida[strcspn(arquivoSaida, "\n")] = '\0';

  processar(arquivoEntrada, arquivoSaida);

  return 0;
}
