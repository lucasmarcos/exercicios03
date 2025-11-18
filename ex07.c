/*

\subsubsection{Persistência de registros: Sistema de biblioteca}

Implemente um sistema de gerenciamento de biblioteca que integre estruturas de dados com persistência em arquivos, incluindo funcionalidades de busca, empréstimo e geração de relatórios.

\textbf{Especificações:}

Crie uma estrutura \texttt{Data} com \texttt{dia}, \texttt{mes} e \texttt{ano} (\texttt{int}).

Crie uma estrutura \texttt{Livro} contendo: \texttt{codigo} (\texttt{int}), \texttt{titulo} (\texttt{string} de 64 caracteres), \texttt{autor} (\texttt{string} de 64 caracteres), \texttt{editora} (\texttt{string} de 64 caracteres), \texttt{ano} (\texttt{int}), \texttt{ISBN} (\texttt{string} de 32 caracteres), \texttt{categoria} (\texttt{string} de 32 caracteres), \texttt{exemplares} (\texttt{int}), \texttt{disponiveis} (\texttt{int}) e \texttt{status} (\texttt{char}: `A' para ativo, `I' para inativo/removido).

Crie uma estrutura \texttt{Emprestimo} com: \texttt{codigo} (\texttt{int}), \texttt{codigoLivro} (\texttt{int}), \texttt{usuario} (\texttt{string} de 64 caracteres), \texttt{dataEmprestimo} (\texttt{Data}), \texttt{dataPrevista} (\texttt{Data}), \texttt{dataReal} (\texttt{Data}, usar 0/0/0 para não devolvido) e \texttt{status} (\texttt{char}: `A' para ativo, `D' para devolvido, `T' para atrasado).

Implemente as seguintes funções principais:

\begin{itemize}

\item \texttt{void carregar(char *arquivo, Livro livros[], int *total)} que carrega todos os livros do arquivo para memória ao iniciar o programa

\item \texttt{void salvar(char *arquivo, Livro livros[], int total)} que salva todo o acervo da memória para o arquivo ao encerrar ou quando solicitado

\item \texttt{void adicionar(Livro livros[], int *total)} que adiciona um novo livro

\item \texttt{void editar(Livro livros[], int total, int codigo)} que permite modificar dados de um livro existente

\item \texttt{void remover(Livro livros[], int total, int codigo)} que marca o livro como inativo se não houver empréstimos pendentes

\item \texttt{Livro* buscarCodigo(Livro livros[], int total, int codigo)} que retorna ponteiro para o livro ou NULL

\item \texttt{void buscarTitulo(Livro livros[], int total, char *titulo)} que busca e exibe livros com título correspondente

\item \texttt{void buscarAutor(Livro livros[], int total, char *autor)} similar à busca por título

\item \texttt{void listarCategoria(Livro livros[], int total, char *categoria)} que lista todos os livros de uma categoria específica

\item \texttt{int emprestimo()} que registra empréstimo se houver exemplar disponível e atualiza a disponibilidade

\item \texttt{int devolucao()} que registra devolução, atualiza disponibilidade e verifica atraso

\item \texttt{void relatorioAcervo(char *arquivoSaida, Livro livros[], int total)} que cria arquivo texto com estatísticas do acervo (total de livros, livros por categoria, exemplares totais, taxa de disponibilidade)

\item \texttt{void relatorioEmprestimos(char *arquivo, Emprestimo e[], int total)} que cria relatório com empréstimos ativos, devolvidos e atrasados

\item \texttt{void listarAtrasados(Emprestimo emprestimos[], int total, Data dataAtual)} que identifica e exibe empréstimos com atraso.

\end{itemize}

No programa principal, implemente um menu interativo organizando as operações em submenus (Livros, Empréstimos, Buscas, Relatórios, Sistema).
Ao iniciar, carregue automaticamente os dados dos arquivos ``biblioteca.txt'' e ``emprestimos.txt''.
Ao encerrar ou quando o usuário solicitar, salve todos os dados.

\subsubsection{Caso de Teste 1: Cadastro e Busca}
\begin{itemize}
  \item Adicionar: Código: 1001, Título: ``Clean Code'', Autor: ``Robert Martin'', Editora: ``Prentice Hall'', Ano: 2008, ISBN: ``978-0132350884'', Categoria: ``Programação'', Exemplares: 3, Status: `A'
  \item Adicionar: Código: 1002, Título: ``Design Patterns'', Autor: ``Gang of Four'', Editora: ``Addison-Wesley'', Ano: 1994, ISBN: ``978-0201633610'', Categoria: ``Programação'', Exemplares: 2, Status: `A'
  \item Buscar por título ``Clean'': Encontra ``Clean Code''
  \item Buscar por autor ``Martin'': Encontra ``Clean Code''
  \item Listar categoria ``Programação'': Mostra ambos os livros
\end{itemize}

\subsubsection{Caso de Teste 2: Empréstimos}
\begin{itemize}
  \item Livro: Código 1001, Exemplares totais: 3, Disponíveis: 3
  \item Empréstimo 1: Usuário ``João Silva'', Data: 01/11/2025, Devolução prevista: 15/11/2025
  \item Estado após empréstimo: Disponíveis: 2
  \item Empréstimo 2: Usuário ``Maria Costa'', Data: 05/11/2025, Devolução prevista: 19/11/2025
  \item Estado após empréstimo: Disponíveis: 1
  \item Devolução 1: Data real: 14/11/2025 (no prazo)
  \item Estado após devolução: Disponíveis: 2
\end{itemize}

\subsubsection{Caso de Teste 3: Empréstimos Atrasados}
\begin{itemize}
  \item Empréstimo: Código 3001, Livro: 1001, Usuário: ``Pedro Santos''
  \item Data empréstimo: 01/11/2025, Devolução prevista: 08/11/2025
  \item Data atual: 10/11/2025, Status: `T' (atrasado)
  \item Listar atrasados: Mostra Pedro Santos com 2 dias de atraso
\end{itemize}

\subsubsection{Caso de Teste 4: Validações}
\begin{itemize}
  \item Tentar adicionar livro com código 1001 (já existe)
  \item Saída: ``Erro: Código já cadastrado''
  \item Tentar emprestar livro sem exemplares disponíveis
  \item Saída: ``Erro: Não há exemplares disponíveis''
  \item Tentar remover livro com empréstimos ativos
  \item Saída: ``Erro: Livro possui empréstimos pendentes''
\end{itemize}

\subsubsection{Caso de Teste 5: Persistência}
\begin{itemize}
  \item Sessão 1: Adicionar 5 livros, realizar 3 empréstimos, salvar e encerrar
  \item Sessão 2: Reabrir programa
  \item Verificação: Todos os 5 livros e 3 empréstimos carregados corretamente
  \item Adicionar 2 novos livros, realizar 1 devolução
  \item Salvar e encerrar
  \item Sessão 3: Reabrir e verificar: 7 livros totais, 2 empréstimos ativos
\end{itemize}

\subsubsection{Caso de Teste 6: Relatórios}
\begin{itemize}
  \item Acervo: 10 livros (5 Programação, 3 Ficção, 2 História)
  \item Total de exemplares: 25, Disponíveis: 18, Emprestados: 7
  \item Relatório de acervo mostra:
  \item Total de títulos: 10
  \item Programação: 5 livros, Ficção: 3 livros, História: 2 livros
  \item Taxa de disponibilidade: 72\%
  \item Relatório de empréstimos mostra:
  \item Empréstimos ativos: 7
  \item Empréstimos atrasados: 2
  \item Devoluções no mês: 15
\end{itemize}

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LIVROS 512
#define MAX_EMPRESTIMOS 1024
#define TAM_STR 64
#define TAM_ISBN 32
#define TAM_CATEGORIA 32

struct data {
  int dia;
  int mes;
  int ano;
};

struct livro {
  int codigo;
  char titulo[TAM_STR];
  char autor[TAM_STR];
  char editora[TAM_STR];
  int ano;
  char ISBN[TAM_ISBN];
  char categoria[TAM_CATEGORIA];
  int exemplares;
  int disponiveis;
  char status;
};

struct emprestimo {
  int codigo;
  int codigoLivro;
  char usuario[TAM_STR];
  struct data dataEmprestimo;
  struct data dataPrevista;
  struct data dataReal;
  char status;
};

struct livro livros[MAX_LIVROS];
struct emprestimo emprestimos[MAX_EMPRESTIMOS];
int totalLivros = 0;
int totalEmprestimos = 0;
int proximoCodigoEmprestimo = 1;

int compararDatas(struct data d1, struct data d2)
{
  if (d1.ano != d2.ano) return d1.ano - d2.ano;
  if (d1.mes != d2.mes) return d1.mes - d2.mes;
  return d1.dia - d2.dia;
}

int calcularDiasAtraso(struct data prevista, struct data atual)
{
  return atual.dia - prevista.dia;
}

void carregar(char *arquivo, struct livro livros[], int *total)
{
  FILE *fp = fopen(arquivo, "rb");
  if (fp == NULL) {
    printf("Arquivo '%s' não encontrado\n", arquivo);
    *total = 0;
    return;
  }

  *total = 0;
  while (fread(&livros[*total], sizeof(struct livro), 1, fp) == 1) {
    (*total)++;
  }

  fclose(fp);
  printf("Carregados %d livros de '%s'\n", *total, arquivo);
}

void salvar(char *arquivo, struct livro livros[], int total)
{
  FILE *fp = fopen(arquivo, "wb");
  if (fp == NULL) {
    printf("Erro ao salvar arquivo '%s'\n", arquivo);
    return;
  }

  for (int i = 0; i < total; i++) {
    fwrite(&livros[i], sizeof(struct livro), 1, fp);
  }

  fclose(fp);

  printf("Salvos %d livros em '%s'\n", total, arquivo);
}

void carregarEmprestimos(char *arquivo, struct emprestimo emp[], int *total)
{
  FILE *fp = fopen(arquivo, "rb");
  if (fp == NULL) {
    printf("Arquivo '%s' não encontrado\n", arquivo);
    *total = 0;
    return;
  }

  *total = 0;
  while (fread(&emp[*total], sizeof(struct emprestimo), 1, fp) == 1) {
    if (emp[*total].codigo >= proximoCodigoEmprestimo) {
      proximoCodigoEmprestimo = emp[*total].codigo + 1;
    }
    (*total)++;
  }

  fclose(fp);
  printf("Carregados %d empréstimos de '%s'\n", *total, arquivo);
}

void salvarEmprestimos(char *arquivo, struct emprestimo emp[], int total)
{
  FILE *fp = fopen(arquivo, "wb");
  if (fp == NULL) {
    printf("Erro ao salvar empréstimos\n");
    return;
  }

  for (int i = 0; i < total; i++) {
    fwrite(&emp[i], sizeof(struct emprestimo), 1, fp);
  }

  fclose(fp);

  printf("Salvos %d empréstimos em '%s'\n", total, arquivo);
}

void adicionar(struct livro livros[], int *total)
{
  if (*total >= MAX_LIVROS) {
    printf("Limite de livros atingido\n");
    return;
  }

  struct livro novo;

  printf("Adicionar novo livro\n");
  printf("Código: ");
  scanf("%d", &novo.codigo);
  getchar();

  for (int i = 0; i < *total; i++) {
    if (livros[i].codigo == novo.codigo && livros[i].status == 'A') {
      printf("Código já cadastrado\n");
      return;
    }
  }

  printf("Título: ");
  fgets(novo.titulo, TAM_STR, stdin);
  novo.titulo[strcspn(novo.titulo, "\n")] = '\0';

  printf("Autor: ");
  fgets(novo.autor, TAM_STR, stdin);
  novo.autor[strcspn(novo.autor, "\n")] = '\0';

  printf("Editora: ");
  fgets(novo.editora, TAM_STR, stdin);
  novo.editora[strcspn(novo.editora, "\n")] = '\0';

  printf("Ano: ");
  scanf("%d", &novo.ano);
  getchar();

  printf("ISBN: ");
  fgets(novo.ISBN, TAM_ISBN, stdin);
  novo.ISBN[strcspn(novo.ISBN, "\n")] = '\0';

  printf("Categoria: ");
  fgets(novo.categoria, TAM_CATEGORIA, stdin);
  novo.categoria[strcspn(novo.categoria, "\n")] = '\0';

  printf("Número de exemplares: ");
  scanf("%d", &novo.exemplares);

  novo.disponiveis = novo.exemplares;
  novo.status = 'A';

  livros[*total] = novo;
  (*total)++;

  printf("Livro adicionado com sucesso\n");
}

struct livro* buscarCodigo(struct livro livros[], int total, int codigo)
{
  for (int i = 0; i < total; i++) {
    if (livros[i].codigo == codigo && livros[i].status == 'A') {
      return &livros[i];
    }
  }

  return NULL;
}

void buscarTitulo(struct livro livros[], int total, char *titulo)
{
  int encontrados = 0;
  char tituloLower[TAM_STR], buscarLower[TAM_STR];

  strcpy(buscarLower, titulo);
  for (int i = 0; buscarLower[i]; i++) {
    buscarLower[i] = tolower(buscarLower[i]);
  }

  printf("Resultados da busca\n");

  for (int i = 0; i < total; i++) {
    if (livros[i].status != 'A') continue;

    strcpy(tituloLower, livros[i].titulo);
    for (int j = 0; tituloLower[j]; j++) {
      tituloLower[j] = tolower(tituloLower[j]);
    }

    if (strstr(tituloLower, buscarLower) != NULL) {
      printf("Código: %d\n", livros[i].codigo);
      printf("Título: %s\n", livros[i].titulo);
      printf("Autor: %s\n", livros[i].autor);
      printf("Disponíveis: %d de %d\n", livros[i].disponiveis, livros[i].exemplares);
      encontrados++;
    }
  }

  if (encontrados == 0) {
    printf("Nenhum livro encontrado\n");
  } else {
    printf("Total: %d livro(s) encontrado(s)\n", encontrados);
  }
}

void buscarAutor(struct livro livros[], int total, char *autor)
{
  int encontrados = 0;
  char autorLower[TAM_STR], buscarLower[TAM_STR];

  strcpy(buscarLower, autor);
  for (int i = 0; buscarLower[i]; i++) {
    buscarLower[i] = tolower(buscarLower[i]);
  }

  printf("Resultados da busca\n");

  for (int i = 0; i < total; i++) {
    if (livros[i].status != 'A') continue;

    strcpy(autorLower, livros[i].autor);
    for (int j = 0; autorLower[j]; j++) {
      autorLower[j] = tolower(autorLower[j]);
    }

    if (strstr(autorLower, buscarLower) != NULL) {
      printf("\nCódigo: %d\n", livros[i].codigo);
      printf("Título: %s\n", livros[i].titulo);
      printf("Autor: %s\n", livros[i].autor);
      printf("Disponíveis: %d de %d\n", livros[i].disponiveis, livros[i].exemplares);
      encontrados++;
    }
  }

  if (encontrados == 0) {
    printf("Nenhum livro encontrado\n");
  } else {
    printf("Total: %d livro(s) encontrado(s)\n", encontrados);
  }
}

void listarCategoria(struct livro livros[], int total, char *categoria)
{
  int encontrados = 0;

  printf("Categoria: %s\n", categoria);

  for (int i = 0; i < total; i++) {
    if (livros[i].status == 'A' && strcmp(livros[i].categoria, categoria) == 0) {
      printf("Código: %d\n", livros[i].codigo);
      printf("Título: %s\n", livros[i].titulo);
      printf("Autor: %s\n", livros[i].autor);
      printf("Disponíveis: %d de %d\n", livros[i].disponiveis, livros[i].exemplares);
      encontrados++;
    }
  }

  if (encontrados == 0) {
    printf("Nenhum livro nesta categoria\n");
  } else {
    printf("Total: %d livro(s)\n", encontrados);
  }
}

void remover(struct livro livros[], int total, int codigo)
{
  struct livro *livro = buscarCodigo(livros, total, codigo);

  if (livro == NULL) {
    printf("Livro não encontrado\n");
    return;
  }

  for (int i = 0; i < totalEmprestimos; i++) {
    if (emprestimos[i].codigoLivro == codigo && emprestimos[i].status == 'A') {
      printf("Livro possui empréstimos pendentes\n");
      return;
    }
  }

  livro->status = 'I';

  printf("Livro removido\n");
}

void listarTodos()
{
  printf("ACERVO COMPLETO\n");

  for (int i = 0; i < totalLivros; i++) {
    if (livros[i].status != 'A') continue;

    printf("Código: %d\n", livros[i].codigo);
    printf("Título: %s\n", livros[i].titulo);
    printf("Autor: %s\n", livros[i].autor);
    printf("Categoria: %s\n", livros[i].categoria);
    printf("Exemplares: %d | Disponíveis: %d\n",
      livros[i].exemplares, livros[i].disponiveis);
  }
}

int emprestimo()
{
  int codigoLivro;
  struct emprestimo novo;

  printf("Novo empréstimo\n");
  printf("Código do livro: ");
  scanf("%d", &codigoLivro);
  getchar();

  struct livro *livro = buscarCodigo(livros, totalLivros, codigoLivro);

  if (livro == NULL) {
    printf("Livro não encontrado\n");
    return 0;
  }

  if (livro->disponiveis <= 0) {
    printf("Não há exemplares disponíveis\n");
    return 0;
  }

  novo.codigo = proximoCodigoEmprestimo++;
  novo.codigoLivro = codigoLivro;

  printf("Nome do usuário: ");
  fgets(novo.usuario, TAM_STR, stdin);
  novo.usuario[strcspn(novo.usuario, "\n")] = '\0';

  printf("Data do empréstimo (dd mm aaaa): ");
  scanf("%d %d %d", &novo.dataEmprestimo.dia,
    &novo.dataEmprestimo.mes, &novo.dataEmprestimo.ano);

  printf("Data prevista de devolução (dd mm aaaa): ");
  scanf("%d %d %d", &novo.dataPrevista.dia,
    &novo.dataPrevista.mes, &novo.dataPrevista.ano);

  novo.dataReal.dia = 0;
  novo.dataReal.mes = 0;
  novo.dataReal.ano = 0;
  novo.status = 'A';

  livro->disponiveis--;
  emprestimos[totalEmprestimos++] = novo;

  printf("Empréstimo registrado | Código: %d\n", novo.codigo);
  printf("Disponíveis agora: %d de %d\n", livro->disponiveis, livro->exemplares);

  return 1;
}

int devolucao()
{
  int codigoEmprestimo;

  printf("Devolução\n");
  printf("Código do empréstimo: ");
  scanf("%d", &codigoEmprestimo);

  struct emprestimo *emp = NULL;
  for (int i = 0; i < totalEmprestimos; i++) {
    if (emprestimos[i].codigo == codigoEmprestimo) {
      emp = &emprestimos[i];
      break;
    }
  }

  if (emp == NULL || emp->status != 'A') {
    printf("Empréstimo não encontrado\n");
    return 0;
  }

  printf("Data da devolução (dd mm aaaa): ");
  scanf("%d %d %d", &emp->dataReal.dia, &emp->dataReal.mes, &emp->dataReal.ano);

  struct livro *livro = buscarCodigo(livros, totalLivros, emp->codigoLivro);
  if (livro != NULL) {
    livro->disponiveis++;
  }

  if (compararDatas(emp->dataReal, emp->dataPrevista) > 0) {
    int dias = calcularDiasAtraso(emp->dataPrevista, emp->dataReal);
    printf("Devolução com atraso de %d dia(s)\n", dias);
    emp->status = 'T';
  } else {
    printf("Devolução no prazo\n");
    emp->status = 'D';
  }

  return 1;
}

void listarAtrasados(struct emprestimo emprestimos[], int total, struct data dataAtual)
{
  int encontrados = 0;

  printf("EMPRÉSTIMOS ATRASADOS\n");

  for (int i = 0; i < total; i++) {
    if (emprestimos[i].status == 'A') {
      if (compararDatas(dataAtual, emprestimos[i].dataPrevista) > 0) {
        int dias = calcularDiasAtraso(emprestimos[i].dataPrevista, dataAtual);

        struct livro *livro = buscarCodigo(livros, totalLivros, emprestimos[i].codigoLivro);

        printf("Código empréstimo: %d\n", emprestimos[i].codigo);
        printf("Usuário: %s\n", emprestimos[i].usuario);
        if (livro) printf("Livro: %s\n", livro->titulo);
        printf("Devolução prevista: %02d/%02d/%d\n",
          emprestimos[i].dataPrevista.dia,
          emprestimos[i].dataPrevista.mes,
          emprestimos[i].dataPrevista.ano);
        printf("Dias de atraso: %d\n", dias);
        encontrados++;
      }
    }
  }

  if (encontrados == 0) {
    printf("Nenhum empréstimo atrasado\n");
  } else {
    printf("Total de %d empréstimo(s) atrasado(s)\n", encontrados);
  }
}

void relatorioAcervo(char *arquivoSaida, struct livro livros[], int total)
{
  FILE *fp = fopen(arquivoSaida, "w");
  if (fp == NULL) {
    printf("Erro ao criar relatório\n");
    return;
  }

  int totalAtivos = 0, totalExemplares = 0, totalDisponiveis = 0;

  char categorias[64][TAM_CATEGORIA];
  int contCategorias[64] = {0};
  int numCategorias = 0;

  for (int i = 0; i < total; i++) {
    if (livros[i].status != 'A') continue;

    totalAtivos++;
    totalExemplares += livros[i].exemplares;
    totalDisponiveis += livros[i].disponiveis;

    int encontrou = 0;
    for (int j = 0; j < numCategorias; j++) {
      if (strcmp(categorias[j], livros[i].categoria) == 0) {
        contCategorias[j]++;
        encontrou = 1;
        break;
      }
    }
    if (!encontrou && numCategorias < 50) {
      strcpy(categorias[numCategorias], livros[i].categoria);
      contCategorias[numCategorias] = 1;
      numCategorias++;
    }
  }

  fprintf(fp, "RELATÓRIO DO ACERVO\n");

  fprintf(fp, "Total de títulos: %d\n", totalAtivos);
  fprintf(fp, "Total de exemplares: %d\n", totalExemplares);
  fprintf(fp, "Exemplares disponíveis: %d\n", totalDisponiveis);
  fprintf(fp, "Exemplares emprestados: %d\n", totalExemplares - totalDisponiveis);

  float taxa = totalExemplares > 0 ? (totalDisponiveis * 100.0 / totalExemplares) : 0;
  fprintf(fp, "Taxa de disponibilidade: %.1f%%\n\n", taxa);

  fprintf(fp, "LIVROS POR CATEGORIA\n");

  for (int i = 0; i < numCategorias; i++) {
    fprintf(fp, "%s: %d livro(s)\n", categorias[i], contCategorias[i]);
  }

  fclose(fp);

  printf("Relatório de acervo salvo em '%s'\n", arquivoSaida);
}

void relatorioEmprestimos(char *arquivo, struct emprestimo e[], int total)
{
  FILE *fp = fopen(arquivo, "w");
  if (fp == NULL) {
    printf("Erro ao criar relatório\n");
    return;
  }

  int ativos = 0, devolvidos = 0, atrasados = 0;

  for (int i = 0; i < total; i++) {
    if (e[i].status == 'A') ativos++;
    else if (e[i].status == 'D') devolvidos++;
    else if (e[i].status == 'T') atrasados++;
  }

  fprintf(fp, "RELATÓRIO DE EMPRÉSTIMOS\n");

  fprintf(fp, "Empréstimos ativos: %d\n", ativos);
  fprintf(fp, "Empréstimos atrasados: %d\n", atrasados);
  fprintf(fp, "Devoluções realizadas: %d\n", devolvidos);
  fprintf(fp, "Total de empréstimos: %d\n\n", total);

  fclose(fp);

  printf("Relatório de empréstimos salvo em '%s'\n", arquivo);
}

void menuLivros()
{
  int opcao;
  int cod;

  do {
    printf("MENU LIVROS\n");
    printf("1. Adicionar livro\n");
    printf("2. Remover livro\n");
    printf("3. Listar todos\n");
    printf("0. Voltar\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar();

    switch(opcao) {
      case 1:
        adicionar(livros, &totalLivros);
        break;

      case 2:
        printf("Código do livro: ");
        scanf("%d", &cod);
        remover(livros, totalLivros, cod);
        break;

      case 3:
        listarTodos();
        break;
    }
  } while(opcao != 0);
}

void menuEmprestimos()
{
  int opcao;
  struct data hoje;

  do {
    printf("MENU EMPRÉSTIMOS\n");
    printf("1. Realizar empréstimo\n");
    printf("2. Realizar devolução\n");
    printf("3. Listar atrasados\n");
    printf("0. Voltar\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar();

    switch(opcao) {
      case 1:
        emprestimo();
        break;

      case 2:
        devolucao();
        break;

      case 3:
        printf("Data atual (dd mm aaaa): ");
        scanf("%d %d %d", &hoje.dia, &hoje.mes, &hoje.ano);
        listarAtrasados(emprestimos, totalEmprestimos, hoje);
        break;
    }
  } while(opcao != 0);
}

void menuBuscas()
{
  int opcao;
  int cod;
  char busca[TAM_STR];
  struct livro *l;

  do {
    printf("MENU BUSCAS\n");
    printf("1. Buscar por código\n");
    printf("2. Buscar por título\n");
    printf("3. Buscar por autor\n");
    printf("4. Listar por categoria\n");
    printf("0. Voltar\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar();

    switch(opcao) {
      case 1:
        printf("Código: ");
        scanf("%d", &cod);
        l = buscarCodigo(livros, totalLivros, cod);
        if (l) {
          printf("Livro encontrado\n");
          printf("Título: %s\n", l->titulo);
          printf("Autor: %s\n", l->autor);
          printf("Disponíveis: %d de %d\n", l->disponiveis, l->exemplares);
        } else {
          printf("Livro não encontrado\n");
        }
        break;

      case 2:
        printf("Título: ");
        fgets(busca, TAM_STR, stdin);
        busca[strcspn(busca, "\n")] = '\0';
        buscarTitulo(livros, totalLivros, busca);
        break;

      case 3:
        printf("Autor: ");
        fgets(busca, TAM_STR, stdin);
        busca[strcspn(busca, "\n")] = '\0';
        buscarAutor(livros, totalLivros, busca);
        break;

      case 4:
        printf("Categoria: ");
        fgets(busca, TAM_STR, stdin);
        busca[strcspn(busca, "\n")] = '\0';
        listarCategoria(livros, totalLivros, busca);
        break;
    }
  } while(opcao != 0);
}

void menuRelatorios()
{
  int opcao;

  do {
    printf("MENU RELATÓRIOS\n");
    printf("1. Relatório de acervo\n");
    printf("2. Relatório de empréstimos\n");
    printf("0. Voltar\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar();

    switch(opcao) {
      case 1:
        relatorioAcervo("relatorio_acervo.txt", livros, totalLivros);
        break;

      case 2:
        relatorioEmprestimos("relatorio_emprestimos.txt", emprestimos, totalEmprestimos);
        break;
    }
  } while(opcao != 0);
}

int main(int argc, char *argv[])
{
  int opcao;

  printf("BIBLIOTECA\n");

  carregar("biblioteca.txt", livros, &totalLivros);
  carregarEmprestimos("emprestimos.txt", emprestimos, &totalEmprestimos);

  do {
    printf("MENU PRINCIPAL\n");
    printf("1. Livros\n");
    printf("2. Empréstimos\n");
    printf("3. Buscas\n");
    printf("4. Relatórios\n");
    printf("5. Salvar dados\n");
    printf("0. Sair\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar();

    switch(opcao) {
      case 1:
        menuLivros();
        break;

      case 2:
        menuEmprestimos();
        break;

      case 3:
        menuBuscas();
        break;

      case 4:
        menuRelatorios();
        break;

      case 5:
        salvar("biblioteca.txt", livros, totalLivros);
        salvarEmprestimos("emprestimos.txt", emprestimos, totalEmprestimos);
        break;

      case 0:
        printf("Salvando dados\n");
        salvar("biblioteca.txt", livros, totalLivros);
        salvarEmprestimos("emprestimos.txt", emprestimos, totalEmprestimos);
        printf("Fim\n");
        break;

      default:
        printf("Opção inválida\n");
    }
  } while(opcao != 0);

  return 0;
}
