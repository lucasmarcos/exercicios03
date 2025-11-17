/*

\subsubsection{Reservas de hotel com estruturas aninhadas}

Implemente um sistema completo de reservas de hotel utilizando estruturas aninhadas e ponteiros para gerenciar quartos e hóspedes.

\textbf{Especificações:}

Crie uma estrutura \texttt{Data} com os campos \texttt{dia}, \texttt{mes} e \texttt{ano} (\texttt{int}). Crie uma estrutura \texttt{Hospede} com \texttt{nome} (\texttt{string} de 64 caracteres) e \texttt{CPF} (\texttt{string} de 15 caracteres).
Crie uma estrutura \texttt{Quarto} contendo: \texttt{numero} (\texttt{int}), \texttt{tipo} (\texttt{string} de 16 caracteres: ``solteiro'', ``casal'' ou ``suite''), \texttt{diaria} (\texttt{float}), \texttt{status} (\texttt{string} de 16 caracteres: ``disponivel'' ou ``ocupado''), \texttt{hospede} (estrutura \texttt{Hospede}), \texttt{checkIn} e \texttt{checkOut} (ambas do tipo \texttt{Data}).
Implemente as funções: \texttt{void reserva(Quarto *q, Hospede h, Data checkIn, Data checkOut)} que registra uma reserva em um quarto disponível, \texttt{float total(Quarto q)} que calcula o valor total da estadia baseado no número de diárias e no preço, \texttt{void checkout(Quarto *q)} que libera o quarto e \texttt{void disponiveis(Quarto quartos[], int tamanho)} que mostra todos os quartos disponíveis.
No programa principal, mantenha um vetor de 16 quartos e implemente um menu completo para gerenciar as reservas.

\subsubsection{Caso de Teste 1: Reserva}
\begin{itemize}
    \item Quarto: Número 101, Tipo: ``casal'', Preço: 150.00
    \item Hóspede: Nome: ``Ana Costa'', CPF: ``123.456.789-00''
    \item Check-in: 15/11/2025, Check-out: 18/11/2025
    \item Saída: Reserva confirmada, Total: 450.00 (3 diárias)
\end{itemize}

\subsubsection{Caso de Teste 2: Múltiplas Reservas}
\begin{itemize}
    \item Hotel com 5 quartos
    \item Reserva 1: Quarto 101 ocupado (15/11 a 18/11)
    \item Reserva 2: Quarto 102 ocupado (16/11 a 17/11)
    \item Reserva 3: Quarto 103 disponível
    \item Listagem de disponíveis: Quartos 103, 104, 105
\end{itemize}

\subsubsection{Caso de Teste 3: Check-out}
\begin{itemize}
    \item Quarto 101 ocupado: Hóspede ``Ana Costa'', 3 diárias, Preço: 150.00/dia
    \item Operação: Check-out
    \item Saída: Total a pagar: 450.00, Quarto 101 agora disponível
\end{itemize}

*/

#include <stdio.h>
#include <string.h>

#define MAX_QUARTOS 16
#define TAM_NOME 64
#define TAM_CPF 15
#define TAM_TIPO 16
#define TAM_STATUS 16

typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

typedef struct {
  char nome[TAM_NOME];
  char CPF[TAM_CPF];
} Hospede;

typedef struct {
  int numero;
  char tipo[TAM_TIPO];
  float diaria;
  char status[TAM_STATUS];
  Hospede hospede;
  Data checkIn;
  Data checkOut;
} Quarto;

int calcularDias(Data checkIn, Data checkOut) {
  return checkOut.dia - checkIn.dia;
}

void reserva(Quarto *q, Hospede h, Data checkIn, Data checkOut) {
  if (strcmp(q->status, "disponivel") != 0) {
    printf("Quarto %d não está disponível\n", q->numero);
    return;
  }

  strcpy(q->status, "ocupado");
  q->hospede = h;
  q->checkIn = checkIn;
  q->checkOut = checkOut;

  int dias = calcularDias(checkIn, checkOut);
  float valorTotal = q->diaria * dias;

  printf("Reserva confirmada\n");
  printf("Quarto: %d\n", q->numero);
  printf("Hóspede: %s\n", h.nome);
  printf("Check-in: %02d/%02d/%d\n", checkIn.dia, checkIn.mes, checkIn.ano);
  printf("Check-out: %02d/%02d/%d\n", checkOut.dia, checkOut.mes, checkOut.ano);
  printf("Diárias: %d\n", dias);
  printf("Total: R$ %.2f\n", valorTotal);
}

float total(Quarto q) {
  int dias = calcularDias(q.checkIn, q.checkOut);
  return q.diaria * dias;
}

void checkout(Quarto *q) {
  if (strcmp(q->status, "disponivel") == 0) {
    printf("Quarto %d já está disponível\n", q->numero);
    return;
  }

  float valorTotal = total(*q);

  printf("CHECK-OUTn");
  printf("Quarto: %d\n", q->numero);
  printf("Hóspede: %s\n", q->hospede.nome);
  printf("CPF: %s\n", q->hospede.CPF);
  printf("Total a pagar: R$ %.2f\n", valorTotal);

  strcpy(q->status, "disponivel");
  strcpy(q->hospede.nome, "");
  strcpy(q->hospede.CPF, "");

  printf("Quarto %d agora está disponível\n", q->numero);
}

void disponiveis(Quarto quartos[], int tamanho) {
  int encontrou = 0;

  printf("QUARTOS DISPONÍVEIS\n");

  for (int i = 0; i < tamanho; i++) {
    if (strcmp(quartos[i].status, "disponivel") == 0) {
      printf("Quarto: %d\n", quartos[i].numero);
      printf("Tipo: %s\n", quartos[i].tipo);
      printf("Diária: R$ %.2f\n", quartos[i].diaria);
      encontrou = 1;
    }
  }

  if (!encontrou) {
    printf("Nenhum quarto disponível no momento");
  }
}

Quarto* buscarQuarto(Quarto quartos[], int tamanho, int numero) {
  for (int i = 0; i < tamanho; i++) {
    if (quartos[i].numero == numero) {
      return &quartos[i];
    }
  }
  return NULL;
}

void listarTodos(Quarto quartos[], int tamanho) {
  printf("TODOS OS QUARTOS\n");

  for (int i = 0; i < tamanho; i++) {
    printf("Quarto: %d\n", quartos[i].numero);
    printf("Tipo: %s\n", quartos[i].tipo);
    printf("Diária: R$ %.2f\n", quartos[i].diaria);
    printf("Status: %s\n", quartos[i].status);

    if (strcmp(quartos[i].status, "ocupado") == 0) {
      printf("Hóspede: %s\n", quartos[i].hospede.nome);
      printf("Check-in: %02d/%02d/%d\n",
        quartos[i].checkIn.dia,
        quartos[i].checkIn.mes,
        quartos[i].checkIn.ano
      );
      printf("Check-out: %02d/%02d/%d\n",
        quartos[i].checkOut.dia,
        quartos[i].checkOut.mes,
        quartos[i].checkOut.ano
      );
    }
  }
}

void inicializarQuartos(Quarto quartos[]) {
  for (int i = 0; i < MAX_QUARTOS; i++) {
    quartos[i].numero = 101 + i;
    strcpy(quartos[i].status, "disponivel");

    if (i < 6) {
      strcpy(quartos[i].tipo, "solteiro");
      quartos[i].diaria = 100.00;
    } else if (i < 12) {
      strcpy(quartos[i].tipo, "casal");
      quartos[i].diaria = 150.00;
    } else {
      strcpy(quartos[i].tipo, "suite");
      quartos[i].diaria = 250.00;
    }
  }
}

void exibirMenu() {
  printf("1. Fazer reserva\n");
  printf("2. Realizar check-out\n");
  printf("3. Listar quartos disponíveis\n");
  printf("4. Listar todos os quartos\n");
  printf("5. Consultar quarto específico\n");
  printf("6. Sair\n");
  printf("Escolha uma opção: ");
}

int main(int argc, char *argv[]) {
  Quarto quartos[MAX_QUARTOS];
  int opcao;

  inicializarQuartos(quartos);

  do {
    exibirMenu();
    scanf("%d", &opcao);

    switch (opcao) {
      case 1: {
        int numeroQuarto;
        Hospede h;
        Data checkIn, checkOut;

        printf("NOVA RESERVA\n");
        printf("Número do quarto: ");
        scanf("%d", &numeroQuarto);

        Quarto *q = buscarQuarto(quartos, MAX_QUARTOS, numeroQuarto);

        if (q == NULL) {
          printf("Quarto não encontrado\n");
          break;
        }

        if (strcmp(q->status, "ocupado") == 0) {
          printf("Quarto não está disponível\n");
          break;
        }

        printf("Dados do hóspede:\n");
        printf("Nome: ");
        getchar();
        fgets(h.nome, TAM_NOME, stdin);
        h.nome[strcspn(h.nome, "\n")] = '\0';

        printf("CPF: ");
        fgets(h.CPF, TAM_CPF, stdin);
        h.CPF[strcspn(h.CPF, "\n")] = '\0';

        printf("Data de check-in:\n");
        printf("Dia: ");
        scanf("%d", &checkIn.dia);
        printf("Mês: ");
        scanf("%d", &checkIn.mes);
        printf("Ano: ");
        scanf("%d", &checkIn.ano);

        printf("Data de check-out:\n");
        printf("Dia: ");
        scanf("%d", &checkOut.dia);
        printf("Mês: ");
        scanf("%d", &checkOut.mes);
        printf("Ano: ");
        scanf("%d", &checkOut.ano);

        reserva(q, h, checkIn, checkOut);
        break;
      }

      case 2: {
        int numeroQuarto;
        printf("Número do quarto para check-out: ");
        scanf("%d", &numeroQuarto);

        Quarto *q = buscarQuarto(quartos, MAX_QUARTOS, numeroQuarto);

        if (q == NULL) {
          printf("Quarto não encontrado\n");
        } else {
          checkout(q);
        }
        break;
      }

      case 3:
        disponiveis(quartos, MAX_QUARTOS);
        break;

      case 4:
        listarTodos(quartos, MAX_QUARTOS);
        break;

      case 5: {
        int numeroQuarto;
        printf("Número do quarto: ");
        scanf("%d", &numeroQuarto);

        Quarto *q = buscarQuarto(quartos, MAX_QUARTOS, numeroQuarto);

        if (q == NULL) {
          printf("Quarto não encontrado\n");
        } else {
          printf("INFORMAÇÕES DO QUARTO\n");
          printf("Número: %d\n", q->numero);
          printf("Tipo: %s\n", q->tipo);
          printf("Diária: R$ %.2f\n", q->diaria);
          printf("Status: %s\n", q->status);

          if (strcmp(q->status, "ocupado") == 0) {
            printf("Hóspede: %s\n", q->hospede.nome);
            printf("CPF: %s\n", q->hospede.CPF);
            printf(
              "Check-in: %02d/%02d/%d\n",
              q->checkIn.dia, q->checkIn.mes, q->checkIn.ano
            );
            printf(
              "Check-out: %02d/%02d/%d\n",
              q->checkOut.dia, q->checkOut.mes, q->checkOut.ano
            );
            printf("Total da estadia: R$ %.2f\n", total(*q));
          }
        }
        break;
      }

      default:
        printf("Opção inválida\n");
    }
  } while (opcao != 6);

  return 0;
}
