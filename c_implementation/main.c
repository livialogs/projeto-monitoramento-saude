#include <stdio.h>
#include <stdlib.h> // Para a função system("cls") ou system("clear")
#include <time.h>   // Para registrar a data e hora

// Declaração das funções (protótipos)
void exibirMenu();
void realizarAvaliacao();
void salvarDados(int phq2_score, int gad2_score);
int fazerPergunta(const char* pergunta);
void verHistorico(); 

void verHistorico() {
    FILE *arquivo;
    char linha[256]; // Um buffer para armazenar cada linha lida

    arquivo = fopen("../data/historico_respostas.csv", "r"); // "r" para read (leitura)

    if (arquivo == NULL) {
        printf("ERRO: Nao foi possivel abrir o arquivo de dados ou ele esta vazio.\n");
        return;
    }

    printf("\n--- Historico de Avaliacoes ---\n");
    // Lê e imprime linha por linha até o final do arquivo
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }
    printf("--- Fim do Historico ---\n");

    fclose(arquivo);
}


// Função Principal
int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        while (getchar() != '\n'); // Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                realizarAvaliacao();
                break;
            case 2:
                verHistorico(); 
                break;
            case 0:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

        // Pausa para o usuário ler a mensagem antes de limpar a tela
        printf("\nPressione Enter para continuar...");
        getchar(); // Espera o Enter do usuário

    } while (opcao != 0);

    return 0;
}


// Definição das Funções

void exibirMenu() {
    system("cls || clear"); // Limpa a tela (funciona em Windows "cls" e Linux/Mac "clear")
    printf("========================================\n");
    printf("   Sistema de Monitoramento de Saude\n");
    printf("========================================\n");
    printf("1 - Realizar nova avaliacao\n");
    printf("2 - Ver historico\n");
    printf("0 - Sair\n");
    printf("\nEscolha uma opcao: ");
}

void realizarAvaliacao() {
    printf("\n--- Nova Avaliacao ---\n");
    printf("Responda de 0 a 3, onde:\n");
    printf("0 = Nenhuma vez\n");
    printf("1 = Varios dias\n");
    printf("2 = Mais da metade dos dias\n");
    printf("3 = Quase todos os dias\n\n");
    
    // --- Bloco PHQ-2 (Depressão) ---
    int phq1 = fazerPergunta("Nas ultimas 2 semanas, com que frequencia voce teve pouco interesse ou prazer em fazer as coisas?");
    int phq2 = fazerPergunta("Nas ultimas 2 semanas, com que frequencia voce se sentiu para baixo, deprimido(a) ou sem esperanca?");
    int phq2_total = phq1 + phq2;

    // --- Bloco GAD-2 (Ansiedade) ---
    int gad1 = fazerPergunta("Nas ultimas 2 semanas, com que frequencia voce se sentiu nervoso(a), ansioso(a) ou muito tenso(a)?");
    int gad2 = fazerPergunta("Nas ultimas 2 semanas, com que frequencia voce nao foi capaz de impedir ou controlar as preocupacoes?");
    int gad2_total = gad1 + gad2;

    printf("\n--- Resultados da Triagem ---\n");
    printf("Pontuacao PHQ-2 (Depressao): %d\n", phq2_total);
    printf("Pontuacao GAD-2 (Ansiedade): %d\n", gad2_total);

    // Lógica de Alerta (Fluxo de Controle)
    if (phq2_total >= 3 || gad2_total >= 3) {
        printf("\nALERTA: Sua pontuacao sugere que uma avaliacao mais detalhada e recomendada.\n");
        printf("Neste momento, o sistema ainda nao aplica as escalas completas (PHQ-9/GAD-7).\n");
        printf("\nIMPORTANTE: Este teste nao substitui um diagnostico profissional.\n");
        printf("Recomendamos a procura de um profissional de saude mental para uma avaliacao completa.\n");
        
    } else {
        printf("\nNenhum sinal de alerta detectado na triagem inicial.\n");
    }

    // Salvar os dados no arquivo
    salvarDados(phq2_total, gad2_total);
}

// Função para fazer uma pergunta e validar a resposta (Modularização)
int fazerPergunta(const char* pergunta) {
    int resposta = -1;
    do {
        printf("%s\nSua resposta (0-3): ", pergunta);
        scanf("%d", &resposta);
        while (getchar() != '\n'); // Limpa o buffer de entrada
        if (resposta < 0 || resposta > 3) {
            printf("Resposta invalida. Por favor, insira um valor entre 0 e 3.\n");
        }
    } while (resposta < 0 || resposta > 3);
    return resposta;
}


// Função para salvar os dados no arquivo CSV (Modularização)
void salvarDados(int phq2_score, int gad2_score) {
    FILE *arquivo; // Ponteiro para o arquivo
    
    // Abre o arquivo no modo "append text" (a+), que adiciona ao final.
    arquivo = fopen("../data/historico_respostas.csv", "a+");

    if (arquivo == NULL) {
        printf("ERRO: Nao foi possivel abrir o arquivo de dados.\n");
        return; // Sai da função se não conseguir abrir
    }

    // Pega a data e hora atuais
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    // Escreve os dados no arquivo
    // Formato: id_usuario,data_hora,phq2_score,gad2_score
    fprintf(arquivo, "user01,%04d-%02d-%02d %02d:%02d:%02d,%d,%d\n",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec,
            phq2_score, gad2_score);
            
    fclose(arquivo); // Fecha o arquivo para salvar as alterações

    printf("\nDados da avaliacao salvos com sucesso!\n");
}