// informações do cliente
#ifndef DELIVERY_H
#define DELIVERY_H


// nome incial das pessoas
static const char *name_text[] = {
    "Alef Cauan",
    "Mateus da Rocha",
    "Gabriel Lima",
    "Gabriel Alvez",
    "Ghabriel Sousa",
    "Marcio Roberto"
};

// nome inicial dos endereços
static const char *address_text[] = {
    "PI. Monsenhor 444 r.s",
    "PI. Bocaina 999",
    "CE Parambu 123",
    "CE Parambu 456",
    "MA Paraibana 11",
    "PE Paulistana 000"
};

// string inicial do cpf 
static const char *cpf_text[] = {
    "12345",
    "98765",
    "98767",
    "23456",
    "11156",
    "23411"
};

// enum do score de entrega
typedef enum score {
    DELIVERY_FIRST = 5, // fez a entrega de primeira
    DELIVERY_SECOND = 3, // fez a entrega de segunda 
    DELIVERY_DEVOLUTION = -1 // não fez a entrega
} Score;
// enum com as probabilidades de evento
typedef enum odds {
    LOW = 5,
    LOW_MID = 15, 
    MID = 30,
    MID_HIGH = 55,
    HIGH = 80
} Odds;
// enum contendo os valores do produtos
typedef enum product {
    LAPTOP,
    SMARTPHONE,
    TABLET,
    HEADPHONES,
    SMARTWATCH,
    CAMERA,
    TV,
    MONITOR,
    KEYBOARD,
    MOUSE,
    PRINTER,
    ROUTER,
    SPEAKER,
    GAMING_CONSOLE,
    USB_DRIVE,
    EXTERNAL_HDD,
    SSD,
    GRAPHICS_CARD,
    MOTHERBOARD,
    PROCESSOR,
    NUM_PRODUCTS
} Product;

// nomes de todos os produtos
static const char *products_text[] = {
    "Laptop",
    "Smartphone",
    "Tablet",
    "Headphones",
    "Smartwatch",
    "Camera",
    "TV",
    "Monitor",
    "Keyboard",
    "Mouse",
    "Printer",
    "Router",
    "Speaker",
    "Gaming Console",
    "USB Drive",
    "External HDD",
    "SSD",
    "Graphics Card",
    "Motherboard",
    "Processor"
};

// Array de preços dos produtos
static const float products_prices[] = {
    1500.0,  // Laptop
    800.0,   // Smartphone
    300.0,   // Tablet
    100.0,   // Headphones
    200.0,   // Smartwatch
    500.0,   // Camera
    1000.0,  // TV
    250.0,   // Monitor
    50.0,    // Keyboard
    30.0,    // Mouse
    120.0,   // Printer
    80.0,    // Router
    150.0,   // Speaker
    400.0,   // Gaming Console
    20.0,    // USB Drive
    70.0,    // External HDD
    90.0,    // SSD
    300.0,   // Graphics Card
    200.0,   // Motherboard
    250.0    // Processor
};

// struct que representa o cliente
typedef struct client {
    int id_client;
    char *cpf;
    char *name;
    char *address;
    struct client *next;
} Client;

typedef struct itens {
    Product product;
    char name[20];
    float price;
} Itens;

// Nó de rota de entregas
typedef struct route_node {
    Client *client;
    Itens item;
    int id_delivery;
    int attempts;
    struct route_node *next;
} Route_node;

// Fila de rotas de entregas
typedef struct route {
    Route_node *start;
    Route_node *end;
} Route;

// Nó de entrega na rota
typedef struct deliveries_node {
    Route_node *route_node;
    struct deliveries_node *next;
} Deliveries_node;

// Pilha de entregas não efetuadas
typedef struct deliveries {
    Deliveries_node *top;
} Deliveries;

// Node de Devoluções 
typedef struct devolution_node {
    Route_node *route;
    struct devolution_node *next;
} Devolution_node;
// Fila de devoluções
typedef struct devolution {
    Devolution_node *start;
    Devolution_node *end;
} Devolution;


typedef struct aux
{
    int id;
    int opt;
    int attempts;
    char name[100];
    char addres[100];
    char cpf[100];
}Aux;


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// DEFINES ///////////////////////////////////////

// #define DELIVERY_FIRST 5 // fez a entrega de primeira
// #define DELIVERY_SECOND 3 // fez a entrega de segunda 
// #define DELIVERY_DEVOLUTION -1 // não fez a entrega 
#define CPF_LIMIT 5
#define TRUE 1
#define FALSE 0

extern int id_client;
extern int id_delivery;
extern int cont_client;
extern int total_score;
typedef int BOOL;

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// AUXILIARES ////////////////////////////////////

void line();
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
BOOL validate_cpf(Client *head, char *cpf);
// pega o valor de um numero inteiro 
int get_int(char *mensage);
// gera uma string, e valida dependendo do tipo de str
void get_char(char *mensage, char *str);
// permite uma string com digitos
void get_char_digit(char *mensage, char *str);
// fazer uma escolha aleatoria entre os parametros
int random_choice(int min, int max);
// gera um delay aleatorio
int random_delay();
// printa cliente
void print_client(Client client); 

////////////////////////////////////////////////////////////////////////////////
//////////////////// FUNÇÕES DE ALOCAÇÃO/DESALOCAÇÃO ///////////////////////////

char *alloc_string();

Deliveries_node *alloc_node_deliveries(void);   // alocar node entregas 
Route_node *alloc_node_route(void);        // alocar node rota

Client *alloc_client(void); // alocar cliente
Deliveries *alloc_deliveries(void); // alocar entregas 
Devolution *alloc_devolution(void); // alocar devolições 
Route *alloc_route(void);  // alocar rota
Devolution_node *alloc_node_devolution();

void free_client_node(Client *c);
void free_node_deliveries(Deliveries_node *dn);
void free_node_route(Route_node *rn);
void free_node_devolution(Devolution_node *node);

void free_client(Client *c);
void free_deliveries(Deliveries *d);
void free_devolution(Devolution *d);
void free_route(Route *r);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE CLIENTE /////////////////////////////////


// Cadastro de Clientes
void client_register(Client *client);
// Busca de Cliente
void client_search(Client *client);
// Remoção de Cliente
void client_removal(Client *client);
// Listagem de Clientes
void client_list(Client *head);

// inicia clientes com algumas pessoas 
void initialize_clients(Client *client);


////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE ROTA ////////////////////////////////////

// Adicionar Entrega na Rota
void add_delivery_route(Route *route, Client *client);
// Remover Entrega da Rota
void remove_delivery_route(Route *route);
// Listar Entregas na Rota
void list_route(Route *route);
// Função para Verificar se um Cliente Específico já Está na Fila
Route_node *find_client_in_route(Route *route, Client *client);
// Função para Verificar se um Endereço Específico já Está na Fila e Retornar o Nó
Route_node* find_address_in_route(Route *route, const char *address);


////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE ENTREGA /////////////////////////////////

// verifica se o stack está vazio
BOOL is_empty(Deliveries *deliveries);
// Adicionar Entrega Não Efetuada na Pilha
void undelivered_push(Deliveries *deliveries, Route_node *route_node);
// Remover Entrega Não Efetuada da Pilha
Deliveries_node *undelivered_pop(Deliveries_node *deliveries);
// Listar Entregas Não Efetuadas
void list_unfulfilled_deliveries(Deliveries *deliveries);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE DEVOLUÇÃO ///////////////////////////////

// Adicionar Devolução na Fila
void add_devolution(Devolution *devolution, Deliveries *deliveries);
// Remover Devolução da Fila
void remove_devolution(Devolution *devolution);
// listar devoluções
void list_devolutions(Devolution *devolution);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////// FUNÇÕES DE EVENTO /////////////////////////////////

// verifica se um evento vai acontecer ou não
BOOL random_event(Odds odd);
// calcular o score ao entregar ou na devolução
void score_calc_event(Score score);
// evento de rota, uma pessoa realiza um pedido
void route_event(Route *route, Client *client);
// verifica o proximo cliente da lista 
void verify_next_client(Client *previous, Client *next, int *chances, Odds odd);

// verifica o proximo cliente da lista 
void verify_next_client_stack(Client *previous, Client *next, int *chances, Odds odd);

// Evento que verifica se a pessoa estava em casa
void home_delivery_event(Route *route, Deliveries *deliveries, Devolution *devolution);
// inicializa a randomização
void initialize_random();

////////////////////////////////////////////////////////////////////////////////
//////////////////////////// FUNÇÕES DE MENU ///////////////////////////////////
void main_menu(Client *client, Route *route, Deliveries *deliveries, Devolution *devolution);
void menu_client(Client *client);
void menu_route(Route *route, Client *client);
void menu_delivery(Deliveries *deliveries);
void menu_devolution(Devolution *devolution);
void menu();

////////////////////////////////////////////////////////////////////////////////
////////////////////////// FUNCAO DE INICIO ////////////////////////////////////

void init_operation();
#endif