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
void check_allocation(void *pointer, char *mensage); 

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// DEFINES ///////////////////////////////////////

#define DELIVERY_FIRST 5 // fez a entrega de primeira
#define DELIVERY_SECOND 3 // fez a entrega de segunda 
#define DELIVERY_DEVOLUTION -1 // não fez a entrega 
#define TRUE 1
#define FALSE 0



////////////////////////////////////////////////////////////////////////////////
//////////////////// FUNÇÕES DE ALOCAÇÃO/DESALOCAÇÃO ///////////////////////////

void *alloc_node_deliveries();   // alocar node entregas 
void *alloc_node_devolution();   // alocar node devolições 
void *alloc_node_route();        // alocar node rota

void *alloc_client(); // alocar cliente
void *alloc_deliveries(); // alocar entregas 
void *alloc_devolution(); // alocar devolições 
void *alloc_route();  // alocar rota

void free_client();
void free_deliveries();
void free_devolution();
void free_route();

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE PEDIDO //////////////////////////////////

// Cadastro de Clientes
void customer_register();
// Busca de Cliente
void customer_search();
// Remoção de Cliente
void client_removal();
// Listagem de Clientes
void customer_List(Client *client);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE ROTA ////////////////////////////////////

// Adicionar Entrega na Rota
void add_delivery_route();
// Remover Entrega da Rota
void remove_delivery_route();
// Listar Entregas na Rota
void list_route(Route *route);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE ENTREGA /////////////////////////////////

// Adicionar Entrega Não Efetuada na Pilha
void add_undelivered();
// Remover Entrega Não Efetuada da Pilha
void remove_undelivered();
// Listar Entregas Não Efetuadas
void list_unfulfilled_deliveries(Deliveries *deliveries);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE DEVOLUÇÃO ///////////////////////////////

// Adicionar Devolução na Fila
void add_devolution();
// Remover Devolução da Fila
void remove_devolution();



#endif