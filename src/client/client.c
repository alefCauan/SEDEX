#include "delivery.h"
#include <stdio.h>
#include <string.h>


int id_client = 7;
int cont_client = 6;


// mostra um cliente especifico
void print_client(Client client) {
    printf("ID_CLIENT - %d\n", client.id_client);
    printf("CPF  - %s\n", client.cpf);
    printf("Nome - %s\n", client.name);
    printf("Endereço - %s\n", client.address);
}

// Listagem de Clientes
void client_list(Client *head) {
    Client *aux = head->next;
    while (aux) {
        print_client(*aux);
        aux = aux->next;
    }
}

// Cadastro de Clientes

void client_register(Client *head) 
{

    Client *new_client = alloc_client();
    Client *aux = head;

    while (aux->next) aux = aux->next;

    do {
        get_char_digit("o cpf do cliente", new_client->cpf);

    } 
    while (!validate_cpf(head, new_client->cpf));

    
    get_char("o nome do cliente", new_client->name);
    get_char("o endereco do cliente", new_client->address);

    new_client->id_client = id_client;
    id_client += 1;
    aux->next = new_client;
    cont_client += 1;
}

// Busca de Cliente
void client_search(Client *head) {
    Client *aux_client;
    Aux aux = {0};

    while (TRUE) {
        printf("\n___ TIPOS DE BUSCA ____\n");
        do {
            printf("[1] - ID\n");
            printf("[2] - CPF\n");
            printf("[0] - VOLTAR\n");
            aux.opt = get_int("sua escolha");
        } while (!valid_answer(0, 2, aux.opt));

        if (aux.opt == 0) break;

        switch (aux.opt) {
        case 1:
            aux_client = head->next;
            do {
                aux.id = get_int("o id do cliente");
                aux.attempts += 1;
            } while (!valid_answer(0, id_client, aux.id) && aux.attempts < 3);

            if (aux.attempts <= 3) {
                while (aux_client) {
                    if (aux_client->id_client == aux.id) {
                        print_client(*aux_client);
                        break;
                    }
                    aux_client = aux_client->next;
                }
            } else {
                printf("Cliente não encontrado!\n");
            }
            break;
        case 2:
            aux_client = head->next;
            do {
                get_char_digit("o cpf do cliente", aux.cpf);
            } while (!validate_cpf(head, aux.cpf));

            while (aux_client) {
                if (strcmp(aux_client->cpf, aux.cpf) == 0) {
                    print_client(*aux_client);
                    break;
                }
                aux_client = aux_client->next;
            }
            break;
        default:
            break;
        }
    }
}

// Remoção de Cliente

void client_removal(Client *head) 
{

    if (!head) return;

    Client *aux_client, *previous;
    Aux aux = {0};


    while (TRUE) 
    {

        printf("\n___ TIPOS DE REMOÇÃO ____\n");
        do {
            printf("[1] - ID\n");
            printf("[2] - CPF\n");
            printf("[0] - VOLTAR\n");
            aux.opt = get_int("sua escolha");

        } 
        while (!valid_answer(0, 2, aux.opt));

        if (aux.opt == 0) break;

        switch (aux.opt) 
        {

        case 1:
            aux_client = head->next;
            previous = head;
            do {
                aux.id = get_int("o id do cliente");
                aux.attempts += 1;

            } 
            while (!valid_answer(0, id_client, aux.id) && aux.attempts <= 3);

            if (aux.attempts >= 3) break;

            while (aux_client) 
            {

                if (aux.id == aux_client->id_client) {
                    previous->next = aux_client->next;
                    free_client_node(aux_client);
                    printf("Cliente removido com sucesso.\n");
                    cont_client -= 1;
                    return;
                }
                previous = aux_client;
                aux_client = aux_client->next;
            }
            break;
        case 2:
            aux_client = head->next;
            previous = head;
            do {
                get_char_digit("o cpf do cliente", aux.cpf);

            } 
            while (!validate_cpf(head, aux.cpf));

            while (aux_client) 
            {
                if (strcmp(aux.cpf, aux_client->cpf) == 0) {
                    previous->next = aux_client->next;
                    free_client_node(aux_client);
                    printf("Cliente removido com sucesso.\n");
                    cont_client -= 1;
                    return;
                }
                previous = aux_client;
                aux_client = aux_client->next;
            }
            break;
        default:
            break;
        }
        printf("Cliente não encontrado.\n");
    }
}

void initialize_clients(Client *clients) 
{
    Client *aux = clients;

    for (int i = 0; i < cont_client; i++) 
    {
        Client *new_client = alloc_client();
        new_client->id_client = i + 1;
        new_client->cpf = strdup(cpf_text[i]);
        new_client->name = strdup(name_text[i]);
        new_client->address = strdup(address_text[i]);
        new_client->next = NULL;

        if (aux == NULL) 
        {
            clients = new_client;
            aux = clients;
        } 
        else 
        {
            aux->next = new_client;
            aux = new_client;
        }
    }
}

