#include <stdio.h>
#include "delivery.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// AUXILIARES ////////////////////////////////////

// int vector_position(int largura, int i, int j) {return largura * i + j;}

// checar se um ponteiro está alocado corretamente 
void check_allocation(void *pointer, const char *mensage) 
{
    if(!pointer) 
    {
        fprintf(stderr, "Erro ao alocar memória para %s: %d - %s\n", mensage, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

////////////////////////////////////////////////////////////////////////////////
//////////////////// FUNÇÕES DE ALOCAÇÃO/DESALOCAÇÃO ///////////////////////////

Client *alloc_client() 
{
    Client *c = (Client *)malloc(sizeof(Client));
    check_allocation(c, "Client alloc\n");
    return c;
}

Deliveries_node *alloc_node_deliveries() 
{
    Deliveries_node *dn = (Deliveries_node *)malloc(sizeof(Deliveries_node));
    check_allocation(dn, "Deliveries_node alloc\n");
    dn->cliente = alloc_client();
    return dn;
}

Devolution_node *alloc_node_devolution() 
{
    Devolution_node *dn = (Devolution_node *)malloc(sizeof(Devolution_node));
    check_allocation(dn, "Devolution_node alloc\n");
    dn->cliente = alloc_client();
    return dn;
}

Route_node *alloc_node_route() 
{
    Route_node *rn = (Route_node *)malloc(sizeof(Route_node));
    check_allocation(rn, "Route_node alloc\n");
    rn->cliente = alloc_client();
    return rn;
}

Deliveries *alloc_deliveries() 
{
    Deliveries *d = (Deliveries *)malloc(sizeof(Deliveries));
    check_allocation(d, "Deliveries alloc\n");
    d->topo = NULL;
    return d;
}

Devolution *alloc_devolution()
{
    Devolution *d = (Devolution *)malloc(sizeof(Devolution));
    check_allocation(d, "Devolution alloc\n");
    d->inicio = NULL;
    d->fim = NULL;
    return d;
}

Route *alloc_route() 
{
    Route *r = (Route *)malloc(sizeof(Route));
    check_allocation(r, "Route alloc\n");
    r->inicio = NULL;
    r->fim = NULL;
    return r;
}

////////////////////////////////////////////////////

void free_client(Client *c) { free(c); }

void free_node_deliveries(Deliveries_node *dn) 
{
    free_client(dn->cliente);
    free(dn);
}

void free_node_devolution(Devolution_node *dn) 
{
    free_client(dn->cliente);
    free(dn);
}

void free_node_route(Route_node *rn) 
{
    free_client(rn->cliente);
    free(rn);
}

void free_deliveries(Deliveries *d) 
{
    Deliveries_node *current = d->topo;
    Deliveries_node *next;

    while (current) 
    {
        next = current->proximo;
        free_node_deliveries(current);
        current = next;
    }

    free(d);
}

void free_devolution(Devolution *d)
{
    Devolution_node *current = d->inicio;
    Devolution_node *next;

    while(current) 
    {
        next = current->proximo;
        free_node_devolution(current);
        current = next;
    }


    free(d);
}

void free_route(Route *r) 
{
    Route_node *current = r->inicio;
    Route_node *next;

    while (current) 
    {
        next = current->proximo;
        free_node_route(current);
        current = next;
    }

    free(r);
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE PEDIDO //////////////////////////////////

// Cadastro de Clientes
void customer_register(Client *client)
{
    printf("null\n");
}
// Busca de Cliente
void customer_search(Client *client)
{
    printf("null\n");
}
// Remoção de Cliente
void client_removal(Client *client)
{
    printf("null\n");
}
// Listagem de Clientes
void customer_list(Client *client)
{
    printf("null\n");
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE ROTA ////////////////////////////////////

// Adicionar Entrega na Rota
void add_delivery_route(Route *route)
{
    printf("null\n");
}
// Remover Entrega da Rota
void remove_delivery_route(Route *route)
{
    printf("null\n");
}
// Listar Entregas na Rota
void list_route(Route *route)
{
    printf("null\n");
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE ENTREGA /////////////////////////////////

// Adicionar Entrega Não Efetuada na Pilha
void add_undelivered(Deliveries *deliveries)
{
    printf("null\n");
}
// Remover Entrega Não Efetuada da Pilha
void remove_undelivered(Deliveries *deliveries)
{
    printf("null\n");
}
// Listar Entregas Não Efetuadas
void list_unfulfilled_deliveries(Deliveries *deliveries)
{
    printf("null\n");
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE DEVOLUÇÃO ///////////////////////////////

// Adicionar Devolução na Fila
void add_devolution(Devolution *devolution)
{
    printf("null\n");
}
// Remover Devolução da Fila
void remove_devolution(Devolution *devolution)
{
    printf("null\n");
}


void menu() {
    int choice;
    Client *client = NULL; // Estrutura para manipulação de clientes
    Route *route = (Route *)malloc(sizeof(Route)); // Estrutura para rotas
    Deliveries *deliveries = (Deliveries *)malloc(sizeof(Deliveries)); // Estrutura para entregas não efetuadas
    Devolution *devolution = (Devolution *)malloc(sizeof(Devolution)); // Estrutura para devoluções

    do {
        printf("\n==== MENU ====\n");
        printf("1. Registrar Cliente\n");
        printf("2. Buscar Cliente\n");
        printf("3. Remover Cliente\n");
        printf("4. Listar Clientes\n");
        printf("5. Adicionar Entrega na Rota\n");
        printf("6. Remover Entrega da Rota\n");
        printf("7. Listar Entregas na Rota\n");
        printf("8. Adicionar Entrega Não Efetuada na Pilha\n");
        printf("9. Remover Entrega Não Efetuada da Pilha\n");
        printf("10. Listar Entregas Não Efetuadas\n");
        printf("11. Adicionar Devolução na Fila\n");
        printf("12. Remover Devolução da Fila\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                customer_register(client);
                break;
            case 2:
                customer_search(client);
                break;
            case 3:
                client_removal(client);
                break;
            case 4:
                customer_list(client);
                break;
            case 5:
                add_delivery_route(route);
                break;
            case 6:
                remove_delivery_route(route);
                break;
            case 7:
                list_route(route);
                break;
            case 8:
                add_undelivered(deliveries);
                break;
            case 9:
                remove_undelivered(deliveries);
                break;
            case 10:
                list_unfulfilled_deliveries(deliveries);
                break;
            case 11:
                add_devolution(devolution);
                break;
            case 12:
                remove_devolution(devolution);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (choice != 0);

    // Desalocar memória antes de sair
    free(route);
    free(deliveries);
    free(devolution);
}
