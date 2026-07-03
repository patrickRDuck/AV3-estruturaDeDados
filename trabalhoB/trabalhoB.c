#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>


//CONSTANTES
#define MAX 200
#define LIM 20

/* Estrutura que armazena os dados de um email */
struct email {
    char nome[LIM];
    char titulo[50];
    char conteudo[MAX];
    char retorno[MAX];
};

/* Nó da pilha dinâmica */
struct no{
    struct email dado;
    struct no *prox;
};


//PROTÓTIPOS
int empilhar(struct no **topo, struct email valor);
int desempilhar(struct no **topo, struct email *valor);
void sortear(struct no **topo);
void menu();
void liberarPilha(struct no **topo);

int main()
{
    setlocale(LC_ALL, " ");
    struct no *lidos = NULL; // Nó da pilha de emais lidos
    struct no *nao_lidos = NULL; //Nó da pilha de emails não lidos
    
    struct email aux; //variável para armazenar email que será adicionado as pilhas
    char resp;
    
    sortear(&nao_lidos);
    int r;
    do{
        system("clear");
        menu();
        scanf("%d", &r);
        
        switch(r){
            case 1:
                system("clear");
                struct no *auxiliar = nao_lidos;

                while(auxiliar != NULL){
                
                    printf("* Nome: %s\n", auxiliar->dado.nome);
                    printf("Título: %s\n\n", auxiliar->dado.titulo);
                
                    auxiliar = auxiliar->prox;
                }
                    printf("Deseja ler seu último email não lido? [s/n]: ");
                    scanf(" %c",&resp);
                    
                    if (resp == 's'){
                        system("clear");
                        printf(
                        "Nome: %s\nTítulo: %s\nConteúdo: %s\n\n",
                        nao_lidos->dado.nome,
                        nao_lidos->dado.titulo,
                        nao_lidos->dado.conteudo
                    );
                        printf("Deseja responder este email? [s/n]: ");
                        scanf(" %c",&resp);
                        
                        if(resp == 's'){
                            printf("SUA RESPOSTA: ");
                            int c;
                            while((c = getchar()) != '\n' && c != EOF);
                        
                            fgets(nao_lidos->dado.retorno, MAX, stdin);
                        
                            nao_lidos->dado.retorno[
                                strcspn(nao_lidos->dado.retorno, "\n")
                            ] = '\0';
                         }

                        desempilhar(&nao_lidos, &aux);
                        empilhar(&lidos, aux);
                        printf("EMAIL VISUALIZADO!\n");
                        
                    }
                    sleep(3);
                break;
            case 2:
                system("clear");
                if(lidos == NULL){
                    printf("NENHUM EMAIL VIZUALIDADO\n");
                }else{
                    printf("EMAILS QUE VOCÊ RESPONDEU:\n\n");
                    struct no *auxiliar = lidos;

                    while(auxiliar != NULL){
                    
                        if(strlen(auxiliar->dado.retorno) > 0){
                    
                            printf("Nome: %s\n", auxiliar->dado.nome);
                            printf("Título: %s\n", auxiliar->dado.titulo);
                            printf("Conteúdo: %s\n", auxiliar->dado.conteudo);
                            printf("Resposta: %s\n\n", auxiliar->dado.retorno);
                        }
                    
                        auxiliar = auxiliar->prox;
                    }
                    printf("___________________________________\n\n");
                    printf("EMAILS VISUALIZADOS:\n\n");
                    auxiliar = lidos;

                    while(auxiliar != NULL){
                    
                        if(strlen(auxiliar->dado.retorno) == 0){
                    
                            printf("Nome: %s\n", auxiliar->dado.nome);
                            printf("Título: %s\n", auxiliar->dado.titulo);
                            printf("Conteúdo: %s\n\n", auxiliar->dado.conteudo);
                        }
                    
                        auxiliar = auxiliar->prox;
                    }
                }
                sleep(8);
                break;
            
            case 3:
                system("clear");
                printf("Saindo do sistema...");
                sleep(3);
                liberarPilha(&nao_lidos);
                liberarPilha(&lidos);
                break;
                
            default:
                system("clear");
                printf("OPÇÃO INVÁLIDA!\n");
                sleep(3);
                break;
        }
        
    }while(r!=3);
    }


/*
    Empilha um email no topo da pilha.

    Cria dinamicamente um novo nó e o coloca
    na primeira posição da pilha.
*/
int empilhar(struct no **topo, struct email valor){

    struct no *novo;

    novo = malloc(sizeof(struct no));

    if(novo == NULL){
        printf("ERRO DE ALOCACAO!\n");
        return 0;
    }

    novo->dado = valor;

    novo->prox = *topo;

    *topo = novo;

    return 1;
}

/*
    Remove o elemento do topo da pilha.

    Copia o email removido para a variável
    recebida por parâmetro e libera a memória.
*/
int desempilhar(struct no **topo, struct email *valor){

    struct no *aux;

    if(*topo == NULL){
        printf("PILHA VAZIA!\n");
        return 0;
    }

    aux = *topo;

    *valor = aux->dado;

    *topo = aux->prox;

    free(aux);

    return 1;
}

void sortear(struct no **topo){
    
    struct email id1 = {"Linkedin",
    "Vaga de Estágio",
    "Você foi indicado para uma vaga de estágio! Responda esse email se você tem interesse.",
        ""
    };
    
    struct email id2 = {
    "Professor Silva",
    "Trabalho pendente",
    "Notei que você ainda não enviou a atividade. Houve algum problema? Aguardo seu retorno.",
        ""
    };
    
    struct email id3 = {
        "Equipe de RH",
        "Entrevista agendada",
        "Sua entrevista foi marcada para terça às 15h. Por favor, responda confirmando presença.",
        ""
    };
    
    struct email id4 = {
        "João",
        "Preciso da sua ajuda",
        "Estou montando um projeto e lembrei de você. Tem alguns minutos para conversar esta semana?",
        ""
    };
    
    struct email id5 = {
        "Suporte Técnico",
        "Chamado atualizado",
        "Encontramos uma possível solução. Responda este email caso o problema continue acontecendo.",
        ""
    };

    
    struct email id6 = {
    "Nubank",
    "Compra aprovada",
    "Uma compra de R$ 129,90 foi aprovada no seu cartão final 4582. Caso não reconheça, entre em contato.",
        ""
    };
    
    struct email id7 = {
        "Steam",
        "Promoção imperdível",
        "Um item da sua lista de desejos está com 75% de desconto. Oferta válida até amanhã.",
        ""
    };
    
    struct email id8 = {
        "Spotify",
        "Sua retrospectiva chegou",
        "Você ouviu 18.432 minutos de música este ano. Seu artista mais ouvido foi inesperado.",
        ""
    };
    
    struct email id9 = {
        "Google",
        "Armazenamento quase cheio",
        "Sua conta atingiu 92% da capacidade disponível. Considere liberar espaço ou contratar mais armazenamento.",
        ""
    };
    
    struct email id10 = {
        "Mercado Livre",
        "Pedido entregue",
        "Seu pedido foi entregue hoje às 14:32. Avalie sua experiência quando tiver um momento.",
        ""
    };
    
    struct email id11 = {
        "Google Fotos",
        "Memórias de 3 anos atrás",
        "Você tem novas lembranças para revisar. Reviva alguns dos seus melhores momentos.",
        ""
    };
    
    struct email id12 = {
        "Carlos",
        "Mudança de planos",
        "O encontro de amanhã talvez precise ser adiado. Você teria disponibilidade no fim de semana?",
        ""
    };
    
    struct email id13 = {
        "Equipe do Evento",
        "Confirmação necessária",
        "Sua inscrição foi aprovada. Responda este email até sexta-feira para garantir sua vaga.",
        ""
    };
    
    struct email id14 = {
        "Twitch",
        "Streamer ao vivo",
        "Um canal que você segue acabou de iniciar uma transmissão. Entre agora para assistir.",
        ""
    };
    
    struct email id15 = {
        "Suporte Premium",
        "Precisamos de mais informações",
        "Recebemos sua solicitação, mas faltam alguns detalhes. Responda esta mensagem para continuarmos.",
        ""
    };
    
    struct email id16 = {
    "YouTube",
    "Novo inscrito",
    "Seu canal recebeu um novo inscrito. Continue criando conteúdo para alcançar mais pessoas.",
        ""
    };

    struct email id17 = {
        "TikTok",
        "Resumo semanal",
        "Na última semana seus vídeos receberam 12.400 visualizações e 830 curtidas.",
        ""
    };
    
    struct email id18 = {
        "Amazon",
        "Pedido enviado",
        "Seu pedido foi despachado e está a caminho. A previsão de entrega é para os próximos dias.",
        ""
    };

    struct email e[] = {id1, id2, id3, id4, id5, id6, id7, id8, id9, 
    id10,id11, id12, id13, id14, id15, id16, id17, id18};

    int tamanho = sizeof(e) / sizeof(e[0]);
    srand(time(NULL));
    for (int i =0; i<6; i++){
        // 1. Sorteia um índice apenas entre os elementos que restam
        int indiceSorteado = rand() % tamanho;
        
        // 2. Exibe o caractere sorteado

        empilhar(topo, e[indiceSorteado]);;
        // 3. Move o último elemento disponível para a posição do que foi sorteado
        e[indiceSorteado] = e[tamanho - 1];
        
        // 4. Reduz o tamanho do array considerado para o próximo sorteio
        tamanho--;

    
        }
}

void menu(){
    printf("****    CAIXA DE ENTRADA    ****\n");
    printf("1. EMAILS NÃO LIDOS\n");
    printf("2. EMAILS VISUALIZADOS\n");
    printf("3. SAIR\n");
    printf("********************************\n-> ");
    
}

/*
    Libera todos os nós da pilha.

    Evita vazamento de memória.
*/
void liberarPilha(struct no **topo){

    struct no *aux;

    while(*topo != NULL){

        aux = *topo;

        *topo = (*topo)->prox;

        free(aux);
    }
}






