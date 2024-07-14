// informações do cliente
#ifndef DELIVERY_H
#define DELIVERY_H

typedef struct client {
    int id_client;
    char *cpf;
    char *name;
    char *address;
    struct client *next;
} Client;

// Nó de entrega na rota
typedef struct deliveries_node {
    Client *cliente;
    int id_entrega;
    int tentativas;
    char *address;
    struct deliveries_node *next;
} Deliveries_node;

// Pilha de entregas não efetuadas
typedef struct deliveries {
    Deliveries_node *top;
} Deliveries;

// Fila de devoluções
typedef struct devolution {
    Deliveries_node *start;
    Deliveries_node *end;
} Devolution;

// Nó de rota de entregas
typedef struct route_node {
    Client *client;
    int id_delivery;
    char *address;
    struct route_node *proximo;
} Route_node;

// Fila de rotas de entregas
typedef struct route {
    Route_node *start;
    Route_node *end;
} Route;

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// DEFINES ///////////////////////////////////////

#define DELIVERY_FIRST 5 // fez a entrega de primeira
#define DELIVERY_SECOND 3 // fez a entrega de segunda 
#define DELIVERY_DEVOLUTION -1 // não fez a entrega 
#define CPF_LIMIT 5
#define TRUE 1
#define FALSE 0
int id_client = 0;
typedef int BOOL;

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// AUXILIARES ////////////////////////////////////

// checar se um ponteiro está alocado corretamente 
void check_allocation(void *pointer, const char *mensage);
// verifica se uma escolha é valida 
BOOL valid_answer(int min, int max, int answer);
// verifica se uma string possui digitos
BOOL contains_digit(const char *str);
// verifica se uma string possui caracteres 
BOOL contains_string(const char *str);
// retorna a quantidade de caracteres de uma string 
int char_quant(char *str);
// valida a entrada de um cpf
BOOL validate_cpf(char *cpf);
// pega o valor de um numero inteiro 
int get_int(char *mensage);
// gera uma string, e valida dependendo do tipo de str
void get_char(char *mensage, char *str);
// permite uma string com digitos
void get_char_digit(char *mensage, char *str);


////////////////////////////////////////////////////////////////////////////////
//////////////////// FUNÇÕES DE ALOCAÇÃO/DESALOCAÇÃO ///////////////////////////

char *alloc_string();

Deliveries_node *alloc_node_deliveries(void);   // alocar node entregas 
Route_node *alloc_node_route(void);        // alocar node rota

Client *alloc_client(void); // alocar cliente
Deliveries *alloc_deliveries(void); // alocar entregas 
Devolution *alloc_devolution(void); // alocar devolições 
Route *alloc_route(void);  // alocar rota

void free_node_deliveries(Deliveries_node *dn);

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
void add_undelivered(Deliveries *deliveries, Deliveries_node *deliveries_node);
// Remover Entrega Não Efetuada da Pilha
void remove_undelivered(Deliveries *deliveries);
// Listar Entregas Não Efetuadas
void list_unfulfilled_deliveries(Deliveries *deliveries);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE DEVOLUÇÃO ///////////////////////////////

// Adicionar Devolução na Fila
void add_devolution(Devolution *devolution, Deliveries_node *deliveries_node);
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
void menu();


#endif