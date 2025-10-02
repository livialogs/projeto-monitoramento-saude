# Projeto de Paradigmas: Sistema de Monitoramento de Saúde

**Autor:** Lívia Maria Dutra Galvão
**Instituição:** Universidade de Pernambuco - Surubim
**Disciplina:** Paradigmas de Linguagens de Programação
**Professor:** Jheklos
**Data de Entrega:** 02/10/2025

---

## 1. Descrição do Projeto

Este projeto é um sistema de linha de comando para o automonitoramento de sintomas de depressão e ansiedade. A aplicação foi desenvolvida utilizando o paradigma de programação imperativa em duas linguagens, que são **C** e **Perl**, com o objetivo de analisar e comparar suas características, vantagens e desvantagens na resolução do mesmo problema.

O sistema apresenta um menu interativo, faz uma triagem inicial com base nas escalas GAD-2 (ansiedade) e PHQ-2 (depressão), calcula as pontuações, emite um alerta caso os resultados excedam um limiar pré-definido, permite a visualização do histórico de avaliações e salva cada novo resultado em um arquivo de dados no formato CSV.

## 2. Como Compilar e Executar

O projeto está organizado em duas pastas principais, uma para implementação de cada linguagem.

### Versão em C (`/c_implementation`)

É necessário ter um compilador C (como o GCC/MinGW) instalado e configurado nas variáveis de ambiente do sistema.

1.  Navegue até a pasta da implementação em C:
    ```bash
    cd c_implementation
    ```
2.  Compile o programa:
    ```bash
    gcc main.c -o main.exe
    ```
3.  Execute o programa compilado:
    ```bash
    ./main.exe
    ```

### Versão em Perl (`/perl_implementation`)

É necessário ter um interpretador Perl (como o Strawberry Perl) instalado e configurado.

1.  Navegue até a pasta da implementação em Perl:
    ```bash
    cd perl_implementation
    ```
2.  Execute o script:
    ```bash
    perl main.pl
    ```

---

## 3. Avaliação Comparativa das Linguagens

### 3.1. Sistemas de Tipos e Forma de Execução

* **Linguagem C:** Tem um sistema de **tipagem estática** e é uma linguagem **compilada**. Isso significa que todas as variáveis precisam ter seus tipos declarados antes do uso (ex: `int opcao;`). Erros de tipo são detectados durante o processo de compilação, o que aumenta a segurança do código antes até de sua execução. O resultado da compilação é um código de máquina nativo, o que ajuda no desempenho.

* **Linguagem Perl:** A linguagem Perl é interpretada, o que significa que não existe um passo de compilação para criar um arquivo .exe separado. Em vez disso, um programa tradutor (o interpretador) lê e executa o nosso código fonte linha por linha, em tempo real.  Combinado a isso, Perl utiliza tipagem dinâmica, o que na prática funciona como um "bolso flexível" para as variáveis. Diferente de C, não é preciso definir um tipo fixo para uma variável (como int). Uma mesma variável pode guardar um número em um momento e um texto no momento seguinte. O tipo da variável é decidido "na hora", ou seja, em tempo de execução. Isso faz o desenvolvimento ter muito mais flexibilidade e velocidade no desenvolvimento (prototipagem). A desvantagem é que, se um erro de tipo ocorrer (como tentar fazer uma conta com um texto), ele só será descoberto quando o programa já estiver rodando, o que pode causar bugs inesperados.


### 3.2. Desempenho

A análise de desempenho foi dividida em duas categorias:

* **Desempenho de Execução:** A versão em C é objetivamente mais rápida. Por ser compilada para código de máquina nativo, a execução de laços e cálculos é feita com o mínimo de sobrecarga. Para uma aplicação com processamento intensivo, C seria é a escolha superior.

* **Desempenho de Desenvolvimento:** A versão em Perl foi bem mais rápida de desenvolver. Tarefas como manipulação de strings, leitura de entradas e principalmente a escrita de dados formatados em arquivo exigem muito menos código em Perl do que em C. A tipagem dinâmica também contribuiu para um desenvolvimento mais ágil.

---

## 4. Justificativas de Design de Software

### 4.1. Justificativa das Escolhas de Fluxo de Controle

O fluxo principal do programa é controlado por laços e estruturas condicionais para guiar a experiência do usuário.


* **Implementação em C:** 
* Menu Principal (do-while): Escolhi um laço do-while para o menu principal. Esta estrutura garante que o bloco de código (exibir o menu e pedir a opção) seja executado pelo menos uma vez antes da condição (opcao != 0) ser verificada. Isso se encaixa bem no comportamento esperado de um menu, que deve sempre aparecer na primeira execução.
* Seleção de Opções (switch-case): Para o direcionamento das opções do menu, a estrutura switch-case foi a melhor. Para uma única variável inteira (opcao) sendo comparada com múltiplos valores constantes (1, 2, 0), o switch é mais legível, organizado e mais eficiente do que uma longa cadeia de if-else if.
* Validação de Entrada (do-while): Na função fazerPergunta, um laço do-while foi novamente usado para validar a resposta do usuário. Ele garante que a pergunta seja feita uma vez, e o laço só se repete se a resposta inserida pelo usuário for inválida (menor que 0 ou maior que 3).
* Tratamento de Erro de Arquivo (if): Depois da tentativa de abrir o arquivo CSV com fopen, uma verificação if (arquivo == NULL) foi implementada. Esse condicional é muito importante para a robustez do programa, porque ele desvia o fluxo principal e encerra a função salvarDados caso o arquivo não possa ser aberto, o que previne que o programa tente escrever em um ponteiro nulo e cause um crash.

* **Implementação em Perl:** 
* Menu Principal (while(1) e last): Na versão em Perl, usei um idioma comum da linguagem: um laço while(1) para criar um loop infinito. O controle de fluxo é gerenciado internamente pelo comando last, que é chamado quando a condição de saída ($opcao == 0) é satisfeita. Esta abordagem é flexível e muito utilizada em scripts.
* Seleção de Opções (if/elsif/else): Diferente de C, Perl em sua versão base não tem uma estrutura switch nativa. Por isso, a seleção de opções do menu foi implementada com uma cadeia if/elsif/else, que é a forma padrão e legível de se lidar com múltiplas condições na linguagem.
* Validação de Entrada (while): Na sub-rotina fazer_pergunta, um laço while foi usado. A lógica é similar à da versão em C, repetindo o pedido de entrada enquanto a resposta for considerada inválida.
* Tratamento de Erro de Arquivo (or die): Perl oferece uma forma idiomática e muito concisa para tratar erros de operações de I/O. A expressão or die(...) foi anexada à chamada open(). Este é um poderoso mecanismo de controle de fluxo: se a função open() falhar (retornando um valor falso), a execução do programa é imediatamente interrompida (die), e uma mensagem de erro detalhada é exibida. É uma abordagem "fail-fast" (falhe rápido) que previne a continuação de um script em um estado inconsistente.

* **Lógica de Alerta:** A lógica de alerta do sistema é controlada por uma regra de decisão simples, implementada em um bloco if (`if (phq2_total >= 3 || gad2_total >= 3)`). Ele funciona como uma triagem: o programa verifica se a pontuação de depressão é 3 ou mais OU (||) se a de ansiedade é 3 ou mais. Se pelo menos uma dessas condições for verdadeira, o programa aciona o "gatilho" e exibe a mensagem de alerta para o usuário. Caso contrário, ele segue o fluxo normal. Essa estrutura condicional é o "cérebro" do programa, permitindo que ele tome ações diferentes com base nos dados de entrada.


### 4.2. Explicação da Modularização

O código em ambas as linguagens foi organizado em funções (ou sub-rotinas em Perl) com responsabilidades únicas, visando maior clareza e manutenibilidade.

* `exibirMenu()`: Responsável apenas por limpar a tela e imprimir as opções, mantendo o laço principal do programa mais limpo.
* `realizarAvaliacao()`: Realiza todo o fluxo do questionário, chamando outras funções para tarefas específicas.
* `fazerPergunta()`: Criada para evitar a repetição de código (princípio DRY - Don't Repeat Yourself). Esta função encapsula a lógica de exibir uma pergunta, ler a resposta do usuário e validar se a entrada está dentro do intervalo esperado (0-3).
* `salvarDados()`: Isola toda a complexidade de manipulação de arquivos (abrir, formatar a data/hora, escrever e fechar), tornando o resto do código independente dos detalhes de armazenamento.
* `verHistorico()` (C) / `ver_historico()` (Perl):** Esta função é responsável por uma única tarefa: ler todo o conteúdo do arquivo `historico_respostas.csv` e exibi-lo na tela. Isso separa a lógica de leitura da lógica de escrita, mantendo o código organizado.

### 4.3. Legibilidade e Validação de Entrada

Nomes de variáveis e funções descritivos foram utilizados em ambas as implementações para facilitar o entendimento do código. A validação de entrada do usuário chama atenção por dar uma comparação interessante:

* Em **C**, a função `scanf` é suscetível a erros quando o usuário digita um texto em vez de um número, causando um loop infinito. Foi necessária uma solução manual para limpar o buffer de entrada (`while (getchar() != '\n');`) e garantir a robustez do programa.

* Em **Perl**, a validação foi feita de forma mais segura e concisa com uma única linha de **expressão regular** (`unless ($resposta =~ /^[0-3]$/)`), que verifica se a entrada é exatamente um dígito entre 0 e 3. Isso mostra a força da linguagem para o processamento de texto e validação de padrões.

---

## 5. Desafios e Aprendizados

O principal desafio técnico encontrado foi um conflito de compiladores no ambiente de desenvolvimento. A instalação do Strawberry Perl incluiu uma versão do GCC que entrou em conflito com a versão instalada via MSYS2. O problema foi diagnosticado através de erros inesperados de compilação e resolvido ajustando a ordem das pastas na variável de ambiente `PATH` do sistema, priorizando o compilador do MSYS2 acima do Strawberry Perl. Isso reforçou a importância de um bom gerenciamento do ambiente de desenvolvimento.