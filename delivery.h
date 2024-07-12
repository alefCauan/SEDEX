// informações do cliente
typedef struct client {
    int id_cliente;
    char nome[100];
    char endereco[200];
    struct client* proximo;
} Client;

// Nó de entrega na rota
typedef struct deliveries_node {
    Client* cliente;
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
    struct devolution_node* proximo;
} Devolution_node;

// Fila de devoluções
typedef struct devolution {
    Devolution_node* inicio;
    Devolution_node* fim;
} Devolution;

// Nó de rota de entregas
typedef struct route_node {
    int id_entrega;
    Client* cliente;
    char endereco[200];
    struct route_node* proximo;
} Route_node;

// Fila de rotas de entregas
typedef struct route {
    Route_node* inicio;
    Route_node* fim;
} Route;

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// DEFINES ///////////////////////////////////////

#define DELIVERY_FIRST 5 // fez a entrega de primeira
#define DELIVERY_SECOND 3 // fez a entrega de segunda 
#define DELIVERY_DEVOLUTION -1 // não fez a entrega 

////////////////////////////////////////////////////////////////////////////////
//////////////////// FUNÇÕES DE ALOCAÇÃO/DESALOCAÇÃO ///////////////////////////
void alloc_client(); // alocar cliente
void alloc_deliveries(); // alocar entregas 
void alloc_devolution(); // alocar devolições 
void alloc_route();  // alocar rota

void free_client();
void free_deliveries();
void free_devolution();
void free_route();

////////////////////////////////////////////////////////////////////////////////
//////////////////// FUNÇÕES DE ALOCAÇÃO/DESALOCAÇÃO ///////////////////////////