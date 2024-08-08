#include "delivery.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <errno.h>
#include <time.h>
#include <unistd.h>


int id_delivery = 0;
int total_score = 0;
////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE ENTREGA /////////////////////////////////

// verifica se o stack está vazio
BOOL is_empty(Deliveries *deliveries)
{
    return deliveries->top == NULL;
}

void undelivered_push(Deliveries *deliveries, Route_node *route_node) 
{
    Deliveries_node *new_node = (Deliveries_node *)malloc(sizeof(Deliveries_node));
    check_allocation(new_node, "Deliveries node");

    new_node->route_node = route_node;
    new_node->next = deliveries->top;
    deliveries->top = new_node;

    printf("PEDIDO (%s) DE %s EM %s ADICIONADO A ROTA DE NÃO EFETUADAS\n", new_node->route_node->item.name, new_node->route_node->client->name, new_node->route_node->client->address);
}

// Remover Entrega Não Efetuada da Pilha
Deliveries_node *undelivered_pop(Deliveries_node *deliveries)
{  
    if(deliveries)
    {
        Deliveries_node *removed = deliveries;
        deliveries = removed->next;
        // free_node_deliveries(removed);
        return deliveries;
    }

    return deliveries;
}
// Listar Entregas Não Efetuadas
void list_unfulfilled_deliveries(Deliveries *deliveries)
{
    Deliveries_node *aux = deliveries->top;
    if (aux==NULL)
        printf("A lista de não entregues esta vazia!");
    
    printf("Lista de entregas não efetuadas:\n");
    while (aux!=NULL)
    {
        printf("-=-=-=-=-=-=-=-\n");
        print_client(*deliveries->top->route_node->client);
        aux = aux->next;
    }

    free_node_deliveries(aux);
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE DEVOLUÇÃO ///////////////////////////////

// Adicionar Devolução na Fila
void add_devolution(Devolution *devolution, Deliveries *deliveries) 
{
    // fprintf(stderr, "Stack de deliveries está vazio\n");
    if (is_empty(deliveries)) 
        return;

    while (!is_empty(deliveries) && deliveries->top->route_node) 
    {
        Route_node *route_node = deliveries->top->route_node;

        // Aloca um novo nó de devolução
        Devolution_node *new_node = alloc_node_devolution();
        new_node->route = route_node;

        if (!devolution->start) 
        {
            devolution->start = new_node;
            devolution->end = new_node;
        } 
        else 
        {
            devolution->end->next = new_node;
            devolution->end = new_node;
        }

        deliveries->top = deliveries->top->next;
    }
}
// Remover Devolução da Fila
void remove_devolution(Devolution *devolution) 
{
    if (devolution->start == NULL) 
    {
        printf("Nenhuma devolução para remover.\n");
        return;
    }

    Devolution_node *removed = devolution->start;
    devolution->start = removed->next;
    
    if (devolution->start == NULL) 
        devolution->end = NULL;

    free_node_devolution(removed);
    printf("Devolução removida com sucesso.\n");
}


void list_devolutions(Devolution *devolution)
{
    Devolution_node *aux = devolution->start;
    printf("Lista de devolucoes: \n");

    while (aux != NULL)
    {
        printf("-=-=-=-=-=-=-=-\n");
        print_client(*aux->route->client);
        printf("-=-=-=-=-=-=-=-\n");
        aux = aux->next;
    }
}

void menu_route(Route *route, Client *client) 
{
    int choice;
    do {
        printf("\n==== MENU ROTAS ====\n");
        printf("1. Remover Entrega da Rota\n");
        printf("2. Listar Entregas na Rota\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção -> ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                remove_delivery_route(route);
                break;
            case 2:
                list_route(route);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (choice != 0);
}

void menu_delivery(Deliveries *deliveries) 
{
    int choice;
    do {
        printf("\n==== MENU ENTREGAS NÃO EFETUADAS ====\n");
        printf("1. Remover Entrega Não Efetuada da Pilha\n");
        printf("2. Listar Entregas Não Efetuadas\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                Deliveries_node *node1 = alloc_node_deliveries();
                printf("digite o endereco:");
                // scanf("%s", node1->client->address);
                // undelivered(deliveries, node1);
                break;
            case 2:
                // remove_undelivered(deliveries);
                break;
            case 3:
                list_unfulfilled_deliveries(deliveries);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (choice != 0);
}

void menu_devolution(Devolution *devolution) 
{
    int choice;
    do {
        printf("\n==== MENU DEVOLUÇÕES ====\n");
        printf("1. Adicionar Devolução na Fila\n");
        printf("2. Remover Devolução da Fila\n");
        printf("3. Listar Devoluções\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Deliveries_node *node1 = alloc_node_deliveries();
                break;
            case 2:
                remove_devolution(devolution);
                break;
            case 3:
                list_devolutions(devolution);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (choice != 0);
}

// Verifica se um evento vai acontecer ou não
BOOL random_event(Odds odd) 
{
    int choice = random_choice(1, 100);
    return choice <= (int)odd;
}

// Calcular o score ao entregar ou na devolução
void score_calc_event(Score score) 
{
    total_score += score;
}

// Evento de rota, uma pessoa realiza um pedido
void route_event(Route *route, Client *client) 
{
    if(random_event(LOW_MID))
        add_delivery_route(route, client);
}

Route_node *next(Route_node *route) 
{
    if (!route)
        return route;

    route = route->next;
    return route;
}

void verify_next_client(Client *previous, Client *next, int *chances, Odds odd)
{
    if(odd > 0 && (previous->id_client == next->id_client || strcmp(previous->address, next->address) == 0))
        *chances = 100;
    else 
        *chances = odd;
}

// Evento que verifica se a pessoa estava em casa
void home_delivery_event(Route *route, Deliveries *deliveries, Devolution *devolution) 
{
    // Primeira tentativa
    printf("\n-- REALIZANDO A PRIMEIRA TENTATIVA DE ENTREGA --\n");
    Route_node *aux_route = route->start;

    int chances = MID_HIGH;

    while (aux_route) 
    {
        sleep(0.5);
        if (random_event(chances)) 
        {
            if(aux_route->next)
                verify_next_client(aux_route->client, aux_route->next->client, &chances, MID_HIGH);

            printf("PEDIDO (%s) ENTREGURE PARA %s no endereço %s [SCORE +5]\n", aux_route->item.name, aux_route->client->name, aux_route->client->address);
            score_calc_event(DELIVERY_FIRST);
 
            aux_route = aux_route->next;
        } 
        else 
        {
            if(aux_route->next)
                verify_next_client(aux_route->client, aux_route->next->client, &chances, 0);

            aux_route->attempts += 1;
            undelivered_push(deliveries, aux_route);
            
            aux_route = aux_route->next;
        }
    }
    printf("\n-- FINALIZANDO A PRIMEIRA TENTATIVA DE ENTREGA --\n");

    sleep(1.5);

    printf("\n--- INICIANDO A SEGUNDA  TENTATIVA DE ENTREGA ---\n");
    // Segunda tentativa
    chances = MID_HIGH;
    Deliveries_node *aux_deli = deliveries->top;
    while (aux_deli != NULL) 
    {
        sleep(0.5);
        if (random_event(chances)) 
        {
            if(aux_deli->next)
                verify_next_client(aux_deli->route_node->client, aux_deli->next->route_node->client, &chances, MID_HIGH);

            printf("PEDIDO (%s) ENTREGURE PARA %s NO ENDEREÇO %s [SCORE +3]\n", 
            aux_deli->route_node->item.name, 
            aux_deli->route_node->client->name, 
            aux_deli->route_node->client->address);
            score_calc_event(DELIVERY_SECOND);
            aux_deli = undelivered_pop(aux_deli);
        } 
        else 
        {
            if(aux_deli->next)
                verify_next_client(aux_deli->route_node->client, aux_deli->next->route_node->client, &chances, 0);

            printf("PEDIDO (%s) DE %s NO ENDEREÇO %s MOVIDO PARA DEVOLUÇÃO [SCORE -1]\n", aux_deli->route_node->item.name, aux_deli->route_node->client->name, aux_deli->route_node->client->address);
            aux_deli->route_node->attempts += 1;
            add_devolution(devolution, deliveries);
            score_calc_event(DELIVERY_DEVOLUTION);
            aux_deli = aux_deli->next;
        }
    }
    printf("\n--- FINALIZANDO A SEGUNDA TENTATIVA DE ENTREGA ---\n");
}

void main_menu(Client *client, Route *route, Deliveries *deliveries, Devolution *devolution)
{
    Aux aux = {0};

    do {
        do
        {
            printf("\n--------- MENU DE ENTREGAS ----------\n");
            printf("1 - CADASTRAR CLIENTE\n");
            printf("2 - REMOVER CLINTE\n");
            printf("3 - LISTAR CLIENTE\n");
            printf("4 - ABRIR PARA PEDIDOS\n");
            printf("5 - REALIZAR ROTA DE ENTREGA\n");
            printf("6 - LISTAR DEVOLUÇÕES\n");
            printf("Escolha uma opção ->");
            scanf("%d", &aux.opt);
        }
        while(!valid_answer(0, 6, aux.opt));

        switch (aux.opt)
        {
            case 1:
                client_register(client);
                break;
            case 2:
                client_removal(client);
                break;
            case 3:
                client_list(client);
                break;
            case 4:
                route_event(route, client);
                break;
            case 5:
                home_delivery_event(route, deliveries, devolution);
                break;
            case 6:
                list_devolutions(devolution);
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } 
    while (aux.opt != 0);
}


void init_operation()
{
    initialize_random();

    // criação de rota
    Route *route = alloc_route();
    // criação de pilha de entregas não efetuadas
    Deliveries *deliveries = alloc_deliveries();
    // criação de fila de devoluções
    Devolution *devolution = alloc_devolution();
    // criação de clientes
    Client *clients = (Client *)malloc(sizeof(Client));
    clients->id_client = 1;
    clients->cpf = strdup("12345");
    clients->name = strdup("Alef cauan");
    clients->address = strdup("123 Main St");
    clients->next = (Client *)malloc(sizeof(Client));
    clients->next->id_client = 2;
    clients->next->cpf = strdup("98765");
    clients->next->name = strdup("Jane Smith");
    clients->next->address = strdup("456 Elm St");
    clients->next->next = (Client *)malloc(sizeof(Client));
    clients->next->next->id_client = 3;
    clients->next->next->cpf = strdup("98767");
    clients->next->next->name = strdup("Lima");
    clients->next->next->address = strdup("466 Elm St");
    clients->next->next->next = NULL;
    clients->next->next->next = (Client *)malloc(sizeof(Client));
    clients->next->next->next->id_client = 4;
    clients->next->next->next->cpf = strdup("23456");
    clients->next->next->next->name = strdup("Alvez");
    clients->next->next->next->address = strdup("467 Junco");
    clients->next->next->next->next = NULL;
    cont_client += 4;

    int interval_seconds = 10;  // Ajuste o intervalo conforme necessário

    // Tempo de início
    time_t start_time = time(NULL);

    while (TRUE) 
    {
        // Executa a função route_event
        route_event(route, clients);

        // Verifica se o intervalo de tempo passou
        if (difftime(time(NULL), start_time) >= interval_seconds) 
        {
            // Executa a função home_delivery_event
            home_delivery_event(route, deliveries, devolution);
            // Atualiza o tempo de início para o próximo intervalo
            start_time = time(NULL);
            break;
        }

        // Adiciona uma pequena pausa para evitar alta utilização da CPU
        usleep(100000);  // Pausa de 100 milissegundos
    }
    
    printf("final score = %d\n", total_score);
    // Liberação de memória (implementação simplificada)
    // funcao problematica
    free_route(route);
    // Funcao que as vezes da problema
    free_deliveries(deliveries);
    // Funcao problematica
    free_devolution(devolution);
    free_client(clients);
}

