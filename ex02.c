/*

\subsubsection{Gerenciamento de produtos com ponteiros}

Implemente um sistema para gerenciar produtos de uma loja utilizando estruturas e ponteiros.
O sistema deve permitir cadastro, busca e atualização de produtos.

\textbf{Especificações:}

Crie uma estrutura \texttt{Produto} contendo: \texttt{codigo} (\texttt{int}), \texttt{nome} (\texttt{string} de até 64 caracteres), \texttt{preco} (\texttt{float}) e quantidade em estoque (\texttt{int}).
Implemente as seguintes funções: \texttt{void cadastrar(Produto *p)} que recebe um ponteiro para produto e preenche seus dados via entrada do usuário, \texttt{Produto* buscar(Produto produtos[], int tamanho, int codigo)} que retorna um ponteiro para o produto com o código especificado ou NULL se não encontrado, e \texttt{void atualizar(Produto *p, int quantidade)} que adiciona ou remove itens do estoque (quantidade pode ser positiva ou negativa).
No programa principal, mantenha um vetor de até 10 produtos e implemente um menu com opções para cadastrar, buscar, atualizar estoque e listar todos os produtos.

\subsubsection{Caso de Teste 1: Cadastro}
\begin{itemize}
    \item Entrada: Código: 101, Nome: ``Notebook'', Preço: 2500.00, Estoque: 15
    \item Saída: Produto cadastrado com sucesso
\end{itemize}

\subsubsection{Caso de Teste 2: Busca Existente}
\begin{itemize}
    \item Produtos cadastrados: Código 101 (Notebook), Código 102 (Mouse)
    \item Entrada: Buscar código 101
    \item Saída: Produto encontrado - Nome: Notebook, Preço: 2500.00, Estoque: 15
\end{itemize}

\subsubsection{Caso de Teste 3: Busca Inexistente}
\begin{itemize}
    \item Produtos cadastrados: Código 101, Código 102
    \item Entrada: Buscar código 999
    \item Saída: Produto não encontrado
\end{itemize}

\subsubsection{Caso de Teste 4: Atualização de Estoque}
\begin{itemize}
    \item Produto: Código 101, Estoque inicial: 15
    \item Operação 1: Adicionar 10 unidades
    \item Saída: Estoque atual: 25
    \item Operação 2: Remover 8 unidades
    \item Saída: Estoque atual: 17
\end{itemize}

*/

#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 16
#define TAM_NOME 64

typedef struct {
  int codigo;
  char nome[TAM_NOME];
  float preco;
  int quantidade;
} Produto;

void cadastrar(Produto *p) {
  printf("Código: ");
  scanf("%d", &p->codigo);

  printf("Nome: ");
  getchar();
  fgets(p->nome, TAM_NOME, stdin);
  p->nome[strcspn(p->nome, "\n")] = '\0';

  printf("Preço: ");
  scanf("%f", &p->preco);

  printf("Quantidade em estoque: ");
  scanf("%d", &p->quantidade);
}

Produto* buscar(Produto produtos[], int tamanho, int codigo) {
  for (int i = 0; i < tamanho; i++) {
    if (produtos[i].codigo == codigo) {
      return &produtos[i];
    }
  }
  return NULL;
}

void atualizar(Produto *p, int quantidade) {
  p->quantidade += quantidade;

  if (quantidade > 0) {
    printf("Adicionadas %d unidades ao estoque\n", quantidade);
  } else {
    printf("Removidas %d unidades do estoque\n", -quantidade);
  }

  printf("Estoque atual: %d\n", p->quantidade);
}

void exibirProduto(Produto *p) {
  printf("Código: %d\n", p->codigo);
  printf("Nome: %s\n", p->nome);
  printf("Preço: R$ %.2f\n", p->preco);
  printf("Estoque: %d unidades\n", p->quantidade);
}

void listarProdutos(Produto produtos[], int qtdCadastrados) {
  if (qtdCadastrados == 0) {
    printf("Nenhum produto cadastrado ainda\n");
    return;
  }

  printf("PRODUTOS CADASTRADOS\n");

  for (int i = 0; i < qtdCadastrados; i++) {
    printf("Produto %d\n", i + 1);
    exibirProduto(&produtos[i]);
  }

  printf("Total de produtos: %d\n", qtdCadastrados);
}

void exibirMenu() {
  printf("SISTEMA DE GERENCIAMENTO\n");
  printf("1. Cadastrar produto\n");
  printf("2. Buscar produto\n");
  printf("3. Atualizar estoque\n");
  printf("4. Listar todos os produtos\n");
  printf("5. Sair\n");
  printf("Escolha uma opção: ");
}

int main(int argc, char *argv[]) {
  Produto produtos[MAX_PRODUTOS];
  int qtdCadastrados = 0;
  int opcao;

  int codigo;
  int quantidade;
  Produto *p;

  do {
    exibirMenu();
    scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        if (qtdCadastrados < MAX_PRODUTOS) {
          cadastrar(&produtos[qtdCadastrados]);
          qtdCadastrados++;
        } else {
          printf("Limite de produtos atingido (%d produtos)\n", MAX_PRODUTOS);
        }

        break;

      case 2:
        printf("Digite o código do produto: ");
        scanf("%d", &codigo);

        p = buscar(produtos, qtdCadastrados, codigo);

        if (p != NULL) {
          printf("Produto encontrado\n");
          exibirProduto(p);
        } else {
          printf("Produto não encontrado\n");
        }

        break;

      case 3:
        printf("Digite o código do produto: ");
        scanf("%d", &codigo);

        p = buscar(produtos, qtdCadastrados, codigo);

        if (p != NULL) {
          printf("Quantidade a adicionar/remover: ");
          scanf("%d", &quantidade);

          if (p->quantidade + quantidade < 0) {
            printf("Operação inválida\n");
            printf("Estoque atual: %d unidades\n", p->quantidade);
          } else {
            atualizar(p, quantidade);
          }
        } else {
          printf("Produto não encontrado\n");
        }

        break;

      case 4:
        listarProdutos(produtos, qtdCadastrados);
        break;

      default:
        printf("Opção inválida\n");
    }

  } while (opcao != 5);

  return 0;
}
