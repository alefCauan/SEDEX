#include "delivery.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <errno.h>
#include <time.h>
#include <unistd.h>

char *alloc_string() 
{
    char *str = (char *)malloc(100 * sizeof(char));
    check_allocation(str, "String allocation");
    return str;
}

Client *alloc_client() 
{
    Client *c = (Client *)malloc(sizeof(Client));
    check_allocation(c, "Client allocation");
    c->cpf = alloc_string();
    c->name = alloc_string();
    c->address = alloc_string();
    c->next = NULL;
    return c;
}

Deliveries_node *alloc_node_deliveries() 
{
    Deliveries_node *dn = (Deliveries_node *)malloc(sizeof(Deliveries_node));
    check_allocation(dn, "Deliveries_node allocation");
    dn->route_node = alloc_node_route();
    dn->next = NULL;
    return dn;
}

Deliveries *alloc_deliveries() 
{
    Deliveries *d = (Deliveries *)malloc(sizeof(Deliveries));
    check_allocation(d, "Deliveries allocation");
    d->top = NULL;
    return d;
}

Route_node *alloc_node_route() 
{
    Route_node *rn = (Route_node *)malloc(sizeof(Route_node));
    check_allocation(rn, "Route_node allocation");
    rn->client = alloc_client();
    rn->next = NULL;
    return rn;
}

Route *alloc_route() 
{
    Route *r = (Route *)malloc(sizeof(Route));
    check_allocation(r, "Route allocation");
    r->start = NULL;
    r->end = NULL;
    return r;
}

Devolution_node *alloc_node_devolution() 
{
    Devolution_node *dn = (Devolution_node *)malloc(sizeof(Devolution_node));
    check_allocation(dn, "Devolution_node allocation");
    dn->route = alloc_node_route();
    dn->next = NULL;
    return dn;
}

Devolution *alloc_devolution() 
{
    Devolution *d = (Devolution *)malloc(sizeof(Devolution));
    check_allocation(d, "Devolution allocation");
    d->start = NULL;
    d->end = NULL;
    return d;
}
