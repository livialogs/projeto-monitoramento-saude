#!/usr/bin/perl
use strict;
use warnings;
use Time::Piece; # Módulo padrão do Perl p tempo

sub ver_historico {
    my $caminho_arquivo = "../data/historico_respostas.csv";

    open(my $fh, '<', $caminho_arquivo) or die "Nao foi possivel abrir o arquivo '$caminho_arquivo': $!";

    print "\n--- Historico de Avaliacoes ---\n";
    # Lê e imprime cada linha do arquivo
    while (my $linha = <$fh>) {
        print $linha;
    }
    print "--- Fim do Historico ---\n";

    close($fh);
}

# --- Função Principal ---
sub main {
    # Laço infinito para o menu, só sai com a opção 0
    while (1) {
        exibir_menu();
        my $opcao = <STDIN>; # Lê a entrada do usuário
        chomp($opcao);       # Remove a quebra de linha da entrada

        if ($opcao == 1) {
            realizar_avaliacao();
        }
        elsif ($opcao == 2) {
            ver_historico();
        }
        elsif ($opcao == 0) {
            print "\nSaindo do programa...\n";
            last; # Quebra o laço while(1)
        }
        else {
            print "\nOpcao invalida! Tente novamente.\n";
        }

        # Pausa para o usuário ler a mensagem
        print "\nPressione Enter para continuar...";
        <STDIN>; # Apenas espera o usuário pressionar Enter
    }
}

# --- Definição das Sub-rotinas (Funções) ---

sub exibir_menu {
    system("cls || clear");
    print "========================================\n";
    print "   Sistema de Monitoramento de Saude (Perl)\n";
    print "========================================\n";
    print "1 - Realizar nova avaliacao\n";
    print "2 - Ver historico\n";
    print "0 - Sair\n";
    print "\nEscolha uma opcao: ";
}

sub realizar_avaliacao {
    print "\n--- Nova Avaliacao ---\n";
    print "Responda de 0 a 3, onde:\n";
    print "0 = Nenhuma vez\n";
    print "1 = Varios dias\n";
    print "2 = Mais da metade dos dias\n";
    print "3 = Quase todos os dias\n\n";

    # --- Bloco PHQ-2 ---
    my $phq1 = fazer_pergunta("Nas ultimas 2 semanas, com que frequencia voce teve pouco interesse ou prazer em fazer as coisas?");
    my $phq2 = fazer_pergunta("Nas ultimas 2 semanas, com que frequencia voce se sentiu para baixo, deprimido(a) ou sem esperanca?");
    my $phq2_total = $phq1 + $phq2;

    # --- Bloco GAD-2 ---
    my $gad1 = fazer_pergunta("Nas ultimas 2 semanas, com que frequencia voce se sentiu nervoso(a), ansioso(a) ou muito tenso(a)?");
    my $gad2 = fazer_pergunta("Nas ultimas 2 semanas, com que frequencia voce nao foi capaz de impedir ou controlar as preocupacoes?");
    my $gad2_total = $gad1 + $gad2;
    
    print "\n--- Resultados da Triagem ---\n";
    print "Pontuacao PHQ-2 (Depressao): $phq2_total\n";
    print "Pontuacao GAD-2 (Ansiedade): $gad2_total\n";
    
    if ($phq2_total >= 3 or $gad2_total >= 3) {
        print "\nALERTA: Sua pontuacao sugere que uma avaliacao mais detalhada e recomendada.\n";
        print "Neste momento, o sistema ainda nao aplica as escalas completas (PHQ-9/GAD-7).\n";
        print "\nIMPORTANTE: Este teste nao substitui um diagnostico profissional.\n";
        print "Recomendamos a procura de um profissional de saude mental para uma avaliacao completa.\n";
        
    } else {
        print "\nNenhum sinal de alerta detectado na triagem inicial.\n";
    }

    salvar_dados($phq2_total, $gad2_total);
}

sub fazer_pergunta {
    my ($pergunta) = @_; # Pega o argumento passado para a sub-rotina
    my $resposta = -1;
    
    while ($resposta < 0 or $resposta > 3) {
        print "$pergunta\n";
        print "Sua resposta (0-3): ";
        $resposta = <STDIN>;
        chomp($resposta);

        # Verifica se a resposta é realmente um número e está no intervalo
        unless ($resposta =~ /^[0-3]$/) {
            print "Resposta invalida. Por favor, insira um valor entre 0 e 3.\n";
            $resposta = -1; # Força a repetição do laço
        }
    }
    return $resposta;
}

sub salvar_dados {
    my ($phq2_score, $gad2_score) = @_;
    my $caminho_arquivo = "../data/historico_respostas.csv";

    # Abre o arquivo para adicionar no final (>>)
    # or die(...) é uma forma de tratar erros
    open(my $fh, '>>', $caminho_arquivo) or die "Nao foi possivel abrir o arquivo '$caminho_arquivo': $!";
    
    # Pega a data e hora atuais
    my $t = localtime;
    my $data_hora = $t->strftime('%Y-%m-%d %H:%M:%S');
    my $id_usuario = "user01";

    # Escreve a linha no arquivo usando interpolação de string
    print $fh "$id_usuario,$data_hora,$phq2_score,$gad2_score\n";
    
    close($fh); # Fecha o arquivo

    print "\nDados da avaliacao salvos com sucesso!\n";
}

# --- Inicia o programa ---
main();