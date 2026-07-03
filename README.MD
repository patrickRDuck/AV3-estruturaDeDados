# AV3 - Estruturas de Dados

Este repositório contém os projetos práticos desenvolvidos para a disciplina de Estruturas de Dados. Cada trabalho aborda cenários reais de aplicação de conceitos como filas lineares, filas circulares, Listas e Pilhas.

---

## 👥 Integrantes e Identificação
* **Nome dos Integrantes:** 
  * PATRICK RIBEIRO DUARTE
  * ALESSANDRA DOS SANTOS REIS
  * IGOR JERÔNIMO ROSÁRIO DE ALMEIDA
  * LUANDA VITÓRIA CARDOSO DOS SANTOS
  * JOÃO GABRIEL MUTTI BASTOS COSTA
* **Turma:** CMP3A - Ciência da Computação 3º Período / manhã

---

## 📌 Temas Escolhidos por Trabalho

* **Trabalho A:** Playlist de Músicas
* **Trabalho B:** Bandeja de E-mails Não Lidos
* **Trabalho C:** Atendimento Bancário

---

## 📄 Breve Explicação de Cada Programa

### 1. Trabalho A: Gerenciador de Playlist Musical (CRUD Sequencial Contíguo)
Este projeto foca na manipulação direta de coleções de dados homogêneas na memória, implementando um sistema completo de gerenciamento (*Create, Read, Update, Delete*) de faixas musicais. Ele utiliza um **Vetor de Structs Alocado Dinamicamente** que simula uma estrutura estática sequencial.

**Destaques Técnicos:**
* **Alocação Contígua de Blocos:** O programa solicita ao sistema operacional um único bloco maciço de memória contígua capaz de hospedar exatamente 100 structs do tipo `Musica` (`MAX_MUSICAS * sizeof(struct Musica)`), permitindo indexação direta via colchetes (`playlist[i]`).
* **Algoritmo de Exclusão por Deslocamento Físico (*Shifting*):** O maior desafio técnico deste modelo está na operação de exclusão. Como o vetor precisa se manter compacto e sequencial para garantir que as buscas e listagens iterativas funcionem sem falhas, a remoção de um elemento intermediário obriga o sistema a executar um rearranjo: todos os elementos à direita do índice excluído são copiados uma posição para trás em um laço de repetição (`(*playlist)[j] = (*playlist)[j + 1]`), decrementando em seguida o ponteiro do contador geral.
* **Sanitização de Strings e Proteção de Buffer:** O código implementa o tratamento rigoroso de buffers de entrada usando `getchar()` para capturar o caractere de quebra de linha sabotador residual do `scanf()`, além de usar `strcspn()` para substituir o terminador `\n` inserido pelo `fgets()` por um caractere nulo (`\0`), garantindo exatidão nas buscas por ID e listagens na tela.

---

### 2. Trabalho B: Simulador de Caixa de Entrada de E-mails (Pilha Dinâmica)
Este software modela o comportamento de uma caixa de correio eletrônico utilizando o conceito de **Pilha Dinâmica** (Estrutura de dados *LIFO - Last In, First Out*). O fluxo é coordenado através de dois ponteiros de topo que gerenciam coleções isoladas de memória:
* **Pilha de Não Lidos (`nao_lidos`):** Novos e-mails recebidos entram no topo da pilha. Dessa forma, a mensagem mais recente é sempre a primeira disponível para leitura.
* **Pilha de Lidos (`lidos`):** Atua como um arquivo de histórico para e-mails já processados, separando visualmente mensagens respondidas de mensagens apenas visualizadas.

**Destaques Técnicos:**
* **Alocação Dinâmica de Nós:** Este programa não possui tamanho fixo rígido em sua estrutura de armazenamento. Cada e-mail é encapsulado em um nó (`struct no`) alocado dinamicamente na memória via `malloc()`, onde cada elemento guarda seus dados e um ponteiro `prox` para o elemento de baixo.
* **Algoritmo de Sorteio sem Repetição:** Utiliza a combinação de `srand(time(NULL))` e manipulação de índices de vetores para extrair 6 e-mails aleatórios de um banco de dados de 18 mensagens. Para evitar repetição, o e-mail sorteado é substituído pelo último do vetor de sorteio, e o escopo máximo de busca é reduzido dinamicamente.
* **Migração de Estado (*Push/Pop*):** Ao ler um e-mail, o usuário pode opcionalmente concatenar uma string de resposta via `fgets()`. Ao concluir, o e-mail sofre um *Pop* (remoção e liberação via `free()`) da pilha de não lidos e um *Push* (inserção no topo) na pilha de lidos. O programa finaliza aplicando uma rotina de varredura completa para limpar a memória RAM de todos os nós restantes, evitando vazamentos (*memory leaks*).

---

### 3. Trabalho C: Sistema de Gerenciamento de Filas com Alternância de Prioridades
Este programa resolve o problema clássico de balanceamento de fluxo de atendimento em ambientes corporativos ou bancários. Ele integra duas estruturas de dados com comportamentos distintos em um único gerenciador operacional (`ticketManager`):
* **Fila Linear (`linearQueue`):** Dedicada ao fluxo de atendimento comum (Normal). Os elementos são inseridos no fim (`rear`) e removidos no início (`front`), avançando de forma linear sobre um vetor.
* **Fila Circular (`circularQueue`):** Dedicada ao fluxo Prioritário/Preferencial. Para evitar o desperdício de memória e a necessidade de deslocar elementos a cada remoção, o programa utiliza **Aritmética Modular (`%`)** com ponteiros que "dão a volta" nas extremidades do array estático.

**Destaques Técnicos:**
* **Geração Cronológica Global:** As senhas utilizam um contador global dinâmico compartilhado por referência. Isso garante que a ordem de chegada temporal seja mantida (ex: Senha 1 Normal, Senha 2 Preferencial, Senha 3 Normal).
* **Mecanismo de Alternância Baseado em Estado Estático:** O algoritmo de chamadas utiliza uma variável interna modificada pelo operador `static int`. Ela mantém o estado de contagem na memória RAM através de sucessivas execuções da função. A regra de negócio garante que **a cada 2 chamadas normais, o painel chame 1 preferencial**. Se a fila preferencial estiver vazia, o sistema é resiliente e desvia o fluxo para a fila normal para não paralisar o atendimento.
* **Persistência de Dados (Camada de Arquivos):** Todas as operações realizam o *dump* (salvamento) do estado das filas e dos metadados do contador em um arquivo `queue_data.csv` usando máscaras personalizadas no `fscanf`, permitindo que o sistema recupere perfeitamente seu estado após quedas de energia ou encerramento do programa.

---

## 🛠️ Instruções para Compilar

---

### Trabalho A: Playlist de Músicas
O Trabalho A está contido em um único arquivo fonte dentro da pasta `trabalhoA`.

* **Compilação:**
  ```bash
  cd trabalhoA
  gcc "TrabalhoA.c" -o programa_A

---

### Trabalho B: Simulador de Caixa de Entrada de E-mails (Pilha Dinâmica)
O Trabalho B está contido em um único arquivo fonte dentro da pasta `trabalhoB`.

* **Compilação:**
  ```bash
  cd trabalhoB
  gcc "TrabalhoB.c" -o programa_B

---

### Trabalho C: Sistema bancário de filas
Como o projeto foi estruturado seguindo um padrão rígido de modularização e separação de escopos na pasta `src`, precisamos passar as flags de inclusão (`-I`) para o compilador mapear os arquivos `.h`.

Abra o terminal na pasta raiz do repositório (`Trabalho_Final_Estruturas_Dados/` ou equivalente) e execute:

* **Compilação:**
  ```bash
  cd trabalhoC
  gcc src/main.c src/circularQueue/index.c src/linearQueue/index.c src/ticketManager/index.c -I include -I src/circularQueue -I src/linearQueue -I src/ticketManager -o sistema

