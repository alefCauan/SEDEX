#include "delivery.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include <errno.h>
#include <time.h>
#include <unistd.h>


// Escolhe um produto aleatoriamente para um item
void choose_product(Itens *item) 
{
    Aux aux = {0};
    aux.opt = random_choice(0, NUM_PRODUCTS - 1);
    item->product = aux.opt;
    item->price = products_prices[aux.opt];
    strcpy(item->name, products_text[aux.opt]);
}

// Adicionar Entrega na Rota
void add_delivery_route(Route *route, Client *client) 
{
    if (cont_client < 1)
        return;

    Client *aux = client;
    int client_index = random_choice(1, cont_client);

    for (int i = 0; i < client_index - 1; i++)
        aux = aux->next;

    Route_node *new_node = alloc_node_route();
    check_allocation(new_node, "Route node");

    new_node->client = aux;
    choose_product(&new_node->item);
    id_delivery += 1;
    new_node->id_delivery = id_delivery;
    new_node->next = NULL;

    // Verificar se o cliente já está na fila
    Route_node *existing_node = find_client_in_route(route, aux);
    if (existing_node) {
        new_node->next = existing_node->next;
        existing_node->next = new_node;

        if (existing_node == route->end) {
            route->end->next = new_node;
            route->end = route->end->next;
        } 

        printf("Entrega adicionada após cliente existente: Cliente %s, Produto %s, Preço R$%.2f, ID Entrega %d\n",
               new_node->client->name, new_node->item.name, new_node->item.price, new_node->id_delivery);
        return;
    }

    // Verificar se o endereço já está na fila
    existing_node = find_address_in_route(route, aux->address);
    if (existing_node) {
        new_node->next = existing_node->next;
        existing_node->next = new_node;
        if (existing_node == route->end) 
            route->end = new_node;

        printf("Entrega adicionada após endereço existente: Cliente %s, Produto %s, Preço R$%.2f, ID Entrega %d\n",
               new_node->client->name, new_node->item.name, new_node->item.price, new_node->id_delivery);
        return;
    }

    // Adicionar no final da fila se não encontrar cliente ou endereço
    if (!route->start) {
        route->start = new_node;
        route->end = new_node;
    } else {
        route->end->next = new_node;
        route->end = new_node;
    }

    printf("Entrega adicionada no final da fila: Cliente %s, Produto %s, Preço R$%.2f, ID Entrega %d\n",
           new_node->client->name, new_node->item.name, new_node->item.price, new_node->id_delivery);
}

// Remover Entrega da Rota
void remove_delivery_route(Route *route) {
    if (route->start == NULL) {
        printf("Nenhuma entrega para remover.\n");
        return;
    }

    Route_node *removed = route->start;
    route->start = removed->next;

    if (route->start == NULL) 
        route->end = NULL;

    printf("Entrega removida: Cliente %s, Produto %s, Preço R$%.2f, ID Entrega %d\n",
           removed->client->name, removed->item.name, removed->item.price, removed->id_delivery);

    free(removed);
}

// Listar Entregas na Rota
void list_route(Route *route) {
    if (route->start == NULL) {
        printf("A rota de entregas está vazia.\n");
        return;
    }

    Route_node *current = route->start;
    printf("Lista de entregas na rota:\n");
    while (current != NULL) {
        printf("ID Entrega: %d, Cliente: %s, Produto: %s, Preço: R$%.2f\n",
               current->id_delivery, current->client->name, current->item.name, current->item.price);
        current = current->next;
    }
}

// Função para Verificar se um Cliente Específico já Está na Fila
Route_node *find_client_in_route(Route *route, Client *client) {
    Route_node *current = route->start;
    while (current) {
        if (current->client->id_client == client->id_client) 
            return current;
        current = current->next;
    }
    return NULL;
}

// Função para Verificar se um Endereço Específico já Está na Fila e Retornar o Nó
Route_node* find_address_in_route(Route *route, const char *address) {
    Route_node *current = route->start;
    while (current) {
        if (strcmp(current->client->address, address) == 0) 
            return current;
        current = current->next;
    }
    return NULL;
}
