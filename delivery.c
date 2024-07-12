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

void *alloc_client() 
{
    Client *c = (Client *)malloc(sizeof(Client));
    check_allocation(c, "Client alloc\n");
    return c;
}

void *alloc_node_deliveries() 
{
    Deliveries_node *dn = (Deliveries_node *)malloc(sizeof(Deliveries_node));
    check_allocation(dn, "Deliveries_node alloc\n");
    dn->cliente = alloc_client();
    return dn;
}

void *alloc_node_devolution() 
{
    Devolution_node *dn = (Devolution_node *)malloc(sizeof(Devolution_node));
    check_allocation(dn, "Devolution_node alloc\n");
    dn->cliente = alloc_client();
    return dn;
}

void *alloc_node_route() 
{
    Route_node *rn = (Route_node *)malloc(sizeof(Route_node));
    check_allocation(rn, "Route_node alloc\n");
    rn->cliente = alloc_client();
    return rn;
}

void *alloc_deliveries() 
{
    Deliveries *d = (Deliveries *)malloc(sizeof(Deliveries));
    check_allocation(d, "Deliveries alloc\n");
    d->topo = NULL;
    return d;
}

void *alloc_devolution()
{
    Devolution *d = (Devolution *)malloc(sizeof(Devolution));
    check_allocation(d, "Devolution alloc\n");
    d->inicio = NULL;
    d->fim = NULL;
    return d;
}

void *alloc_route() 
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

    while (current) 
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