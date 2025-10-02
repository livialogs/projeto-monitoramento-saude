# Projeto de Paradigmas: Sistema de Monitoramento de Saúde

**Autor:** Lívia Maria Dutra Galvão
**Instituição:** Universidade de Pernambuco - Surubim
**Disciplina:** Paradigmas de Linguagens de Programação
**Professor:** Jheklos
**Data de Entrega:** 02/10/2025

---

## 1. Descrição do Projeto

O tema que escolhi foi a criação de um sistema de gerenciamento para o automonitoramento de sintomas de depressão e ansiedade, inspirado nas escalas de triagem clínica PHQ-2 e GAD-2.

A aplicação funciona de forma interativa, através de um menu no terminal, onde o usuário escolhe opções e responde a perguntas diretamente pelo teclado. Por essa característica, ele é o que chamamos de um sistema de linha de comando.

A aplicação foi desenvolvida utilizando o paradigma de programação imperativa em duas linguagens, que são **C** e **Perl**, com o objetivo de analisar e comparar suas características, vantagens e desvantagens na resolução do mesmo problema.

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

* **Linguagem C:** 
* Tipagem Estática: Significa que o tipo de cada variável (ex: int, char*) deve ser explicitamente declarado no código-fonte. O tipo de uma variável é fixo e não pode ser alterado durante a execução. Essa abordagem funciona como uma planta de engenharia: tudo é definido e verificado antes do início da "construção". A principal vantagem é a segurança, pois o compilador verifica a consistência dos tipos em tempo de compilação, detectando erros como atribuir um texto a uma variável numérica antes mesmo de o programa ser executado.
* Execução Compilada: O código-fonte em C é traduzido integralmente para código de máquina por um programa chamado compilador (neste caso, o GCC). O resultado é um arquivo executável (.exe) otimizado e independente. Este processo em duas etapas (escrever -> compilar -> executar) resulta em um desempenho de execução superior, pois o programa final "fala a língua nativa" do processador, sem a necessidade de um tradutor em tempo real.

* **Linguagem Perl:** 
* Tipagem Dinâmica: As variáveis não possuem um tipo fixo declarado no código. Uma mesma variável escalar (ex: $variavel) pode conter um número em uma linha e um texto na linha seguinte. O tipo é associado ao valor e não à variável, sendo determinado "na hora", ou seja, em tempo de execução. Isso oferece enorme flexibilidade e acelera a fase de prototipagem e desenvolvimento, pois o programador não precisa gerenciar os tipos de forma tão rígida.
* Execução Interpretada: Não há um passo de compilação para um arquivo executável separado. O código-fonte em Perl é lido e executado instrução por instrução por um programa tradutor, o interpretador. É um processo de "tradução simultânea". A vantagem é a portabilidade e a facilidade de teste (basta rodar o script), mas a contrapartida é um desempenho de execução inferior ao do código compilado, pois cada linha precisa ser traduzida antes de ser executada. A principal desvantagem da tipagem dinâmica combinada com a interpretação é que erros de tipo só são descobertos durante a execução, muitas vezes quando o programa já está em uso, o que exige uma disciplina de testes rigorosa.


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