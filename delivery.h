// informações do cliente
#ifndef DELIVERY_H
#define DELIVERY_H

typedef struct client {
    int id_cliente;
    char nome[100];
    char endereco[200];
    struct client *proximo;
} Client;

// Nó de entrega na rota
typedef struct deliveries_node {
    Client *cliente;
    int id_entrega;
    int tentativas;
    char endereco[200];
    struct deliveries_node *proximo;
} Deliveries_node;

// Pilha de entregas não efetuadas
typedef struct deliveries {
    Deliveries_node *topo;
} Deliveries;

// Nó de devolução
typedef struct devolution_node {
    Client *cliente;
    int id_entrega;
    char endereco[200];
    struct devolution_node *proximo;
} Devolution_node;

// Fila de devoluções
typedef struct devolution {
    Devolution_node *inicio;
    Devolution_node *fim;
} Devolution;

// Nó de rota de entregas
typedef struct route_node {
    Client *cliente;
    int id_entrega;
    char endereco[200];
    struct route_node *proximo;
} Route_node;

// Fila de rotas de entregas
typedef struct route {
    Route_node *inicio;
    Route_node *fim;
} Route;

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// AUXILIARES ////////////////////////////////////

// checar se um ponteiro está alocado corretamente 
void check_allocation(void *pointer, const char *mensage); 

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// DEFINES ///////////////////////////////////////

#define DELIVERY_FIRST 5 // fez a entrega de primeira
#define DELIVERY_SECOND 3 // fez a entrega de segunda 
#define DELIVERY_DEVOLUTION -1 // não fez a entrega 
#define TRUE 1
#define FALSE 0

typedef int BOOL;

////////////////////////////////////////////////////////////////////////////////
//////////////////// FUNÇÕES DE ALOCAÇÃO/DESALOCAÇÃO ///////////////////////////

Deliveries_node *alloc_node_deliveries(void);   // alocar node entregas 
Devolution_node *alloc_node_devolution(void);   // alocar node devolições 
Route_node *alloc_node_route(void);        // alocar node rota

Client *alloc_client(void); // alocar cliente
Deliveries *alloc_deliveries(void); // alocar entregas 
Devolution *alloc_devolution(void); // alocar devolições 
Route *alloc_route(void);  // alocar rota

void free_node_deliveries(Deliveries_node *dn);
void free_node_devolution(Devolution_node *dn);
void free_node_route(Route_node *rn);

void free_client(Client *c);
void free_deliveries(Deliveries *d);
void free_devolution(Devolution *d);
void free_route(Route *r);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE PEDIDO //////////////////////////////////

// Cadastro de Clientes
void customer_register();
void customer_register(Client *client);
// Busca de Cliente
void customer_search(Client *client);
// Remoção de Cliente
void client_removal(Client *client);
// Listagem de Clientes
void customer_List(Client *client);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE ROTA ////////////////////////////////////

// Adicionar Entrega na Rota
void add_delivery_route(Route *route);
// Remover Entrega da Rota
void remove_delivery_route(Route *route);
// Listar Entregas na Rota
void list_route(Route *route);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE ENTREGA /////////////////////////////////

// Adicionar Entrega Não Efetuada na Pilha
void add_undelivered(Deliveries *deliveries);
// Remover Entrega Não Efetuada da Pilha
void remove_undelivered(Deliveries *deliveries);
// Listar Entregas Não Efetuadas
void list_unfulfilled_deliveries(Deliveries *deliveries);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE DEVOLUÇÃO ///////////////////////////////

// Adicionar Devolução na Fila
void add_devolution(Devolution *devolution);
// Remover Devolução da Fila
void remove_devolution(Devolution *devolution);
// listar devoluções
void list_devolutions(Devolution *devolution);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////// FUNÇÕES DE MENU ///////////////////////////////////
 
void menu_client(Client *client);
void menu_route(Route *route);
void menu_delivery(Deliveries *deliveries);
void menu_devolution(Devolution *devolution);


#endif