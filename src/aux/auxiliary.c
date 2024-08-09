#include "delivery.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h> 
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>


void initialize_random() {
    srand(time(NULL));
}

void check_allocation(void *pointer, const char *message) 
{
    if (!pointer) 
    {
        fprintf(stderr, "Erro ao alocar memória para %s: %d - %s\n", message, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

BOOL valid_answer(int min, int max, int answer) {
    return answer >= min && answer <= max;
}

BOOL contains_digit(const char *str) 
{
    while (*str) 
    {
        if (isdigit((unsigned char)*str)) 
        {
            printf("Não é permitido o uso de números!\n");
            return TRUE;
        }
        str++;
    }
    return FALSE;
}

BOOL contains_string(const char *str) 
{
    while (*str) {
        if (isalpha((unsigned char)*str)) 
        {
            printf("Não é permitido o uso de caracteres!\n");
            return TRUE;
        }
        str++;
    }
    return FALSE;
}

int char_quant(char *str) 
{
    int i;
    for (i = 0; str[i] != '\0'; i++);
    return i;
}

BOOL validate_cpf(Client *head, char *cpf) 
{
    int size = char_quant(cpf);
    if (!valid_answer(CPF_LIMIT, CPF_LIMIT, size)) 
    {
        printf("TAMANHO INVALIDO\n");
        return FALSE;
    } 
    else if (contains_string(cpf)) 
        return FALSE;

    Client *aux = head;
    while (aux) {
        if (strcmp(aux->cpf, cpf) == 0) 
        {
            printf("CPF já está em uso\n");
            return FALSE;
        }
        aux = aux->next;
    }

    return TRUE;
}

int get_int(char *message) 
{
    int value;
    printf("DIGITE %s -> ", message);
    scanf("%d", &value);
    return value;
}

void get_char(char *message, char *str) 
{
    char value[100];
    do {
        printf("DIGITE %s -> ", message);
        setbuf(stdin, NULL);
        scanf("%[^\n]", value);
    } 
    while (contains_digit(value));
    strcpy(str, value);
}

void get_char_digit(char *message, char *str) 
{
    char value[100];
    printf("DIGITE %s -> ", message);
    setbuf(stdin, NULL);
    scanf("%[^\n]", value);
    strcpy(str, value);
}

int random_choice(int min, int max) 
{
    if (min > max) return 1;
    int num = min + rand() % (max - min + 1);
    if (num < min) num += min;
    return num;
}

int random_delay() {
    return (rand() % 7) + 2;
}

#include "delivery.h"

void free_client_node(Client *c) {
    if (c) {

        free(c->cpf);
        free(c->name);
        free(c->address);
        free(c);
    }
}

void free_node_route(Route_node *rn) {
    if (rn) {
        // Não libera o cliente aqui para evitar double_free
        free(rn);
    }
}

void free_route(Route *r) {
    if (r) {
        Route_node *current = r->start;
        while (current) {

void free_node_route(Route_node *rn) 
{
    if (rn) 
    {
        rn->client = NULL;
        rn = NULL;
    }
}

void free_route(Route *r) 
{
    if (r) 
    {
        Route_node *current = r->start;
        while (current) 
        {

            Route_node *next = current->next;
            free_node_route(current);
            current = next;
        }
        free(r);
    }
}


void free_node_deliveries(Deliveries_node *dn) {
    if (dn) {
        // Não libera o route_node aqui para evitar double_free

        free(dn);
    }
}


void free_deliveries(Deliveries *d) {
    if (d) {
        Deliveries_node *current = d->top;
        while (current) {

            Deliveries_node *next = current->next;
            free_node_deliveries(current);
            current = next;
        }
        free(d);
    }
}


void free_node_devolution(Devolution_node *node) {
    if (node) {
        // Não libera o route aqui para evitar double_free

        free(node);
    }
}

void free_devolution(Devolution *d) {
    if (d) 
    {
        Devolution_node *current = d->start;
        while (current) {

          
            Devolution_node *next = current->next;
            free_node_devolution(current);
            current = next;
        }
        free(d);
    }
}


void free_client(Client *head) {
    Client *current = head;
    Client *next_client;

    while (current != NULL) {

        next_client = current->next;
        free_client_node(current);
        current = next_client;
    }

}

