#include <stdio.h>
#include "delivery.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <errno.h>
#include <time.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// AUXILIARES ////////////////////////////////////

// int vector_position(int largura, int i, int j) {return largura * i + j;}
void initialize_random() {
    srand(time(NULL));
}  
// checar se um ponteiro está alocado corretamente 
void check_allocation(void *pointer, const char *mensage) 
{
    if(!pointer) 
    {
        fprintf(stderr, "Erro ao alocar memória para %s: %d - %s\n", mensage, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

// verifica se uma escolha é valida 
BOOL valid_answer(int min, int max, int answer)
{
    if(answer > max || answer < min)
        return FALSE;
    
    return TRUE;
}

BOOL contains_digit(const char *str) 
{
    while(*str) 
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
    while(*str) 
    {
        if (isalpha((unsigned char)*str)) 
        {
            printf("Nao eh permitido o uso de caracteres!\n");
            return TRUE;
        }
        str++;
    }
    return FALSE;
}

int char_quant(char *str)
{
    int i;
    for(i = 0; str[i] != '\0'; i++);

    return i;
}

BOOL validate_cpf(Client *head, char *cpf)
{
    int size = char_quant(cpf);
    if(!valid_answer(CPF_LIMIT, CPF_LIMIT, size))
    {
        printf("TAMANHO INVALIDO\n");
        return FALSE;
    }
    else if
        (contains_string(cpf)) return FALSE;
    
    Client *aux = head;
    while(aux)
    {
        if(strcmp(aux->cpf, cpf) == 0)
        {
            printf("CPF já está em uso\n");
            return FALSE;
        }
        aux = aux->next;
    }
    
    return TRUE;
}

// pega o valor de um numero inteiro 
int get_int(char *mensage)
{
    int value;
    printf("DIGITE %s -> ", mensage);
    scanf("%d", &value);

    return value;
}

// gera uma string, e valida dependendo do tipo de str
void get_char(char *mensage, char *str)
{
    char value[100];

    do{
        printf("DIGITE %s -> ", mensage);
        setbuf(stdin, NULL);
        scanf("%[^\n]", value);
    } 
    while(contains_digit(value));

    strcpy(str, value);
}

// permite uma string com digitos
void get_char_digit(char *mensage, char *str)
{
    char value[100];

    printf("DIGITE %s ->", mensage);
    setbuf(stdin, NULL);
    scanf("%[^\n]", value);
    
    strcpy(str, value);
}

int random_choice(int min, int max)
{
    if (min > max) 
        return 1;

    int num = min + rand() % (max - min + 1);

    
    if(num < min)
        num += min;

    return num;
}

int random_delay()
{    
    return (rand() % 7) + 2;
}

////////////////////////////////////////////////////////////////////////////////
//////////////////// FUNÇÕES DE ALOCAÇÃO/DESALOCAÇÃO ///////////////////////////

char *alloc_string()
{
    char *str = (char *)malloc(100 * sizeof(char));
    return str;
}

Client *alloc_client() 
{
    Client *c = (Client *)malloc(sizeof(Client));
    check_allocation(c, "Client alloc\n");
    c->cpf = alloc_string();
    c->name = alloc_string();
    c->address = alloc_string();
    c->next = NULL;
    return c;
}

Deliveries_node *alloc_node_deliveries() 
{
    Deliveries_node *dn = (Deliveries_node *)malloc(sizeof(Deliveries_node));
    check_allocation(dn, "Deliveries_node alloc\n");
    dn->route_node = alloc_node_route();
    dn->next = NULL;
    return dn;
}

Deliveries *alloc_deliveries() 
{
    Deliveries *d = (Deliveries *)malloc(sizeof(Deliveries));
    check_allocation(d, "Deliveries alloc\n");
    d->top = NULL;
    return d;
}

Route_node *alloc_node_route() 
{
    Route_node *rn = (Route_node *)malloc(sizeof(Route_node));
    check_allocation(rn, "Route_node alloc\n");
    rn->client = alloc_client();
    rn->next = NULL;
    return rn;
}

Route *alloc_route() 
{
    Route *r = (Route *)malloc(sizeof(Route));
    check_allocation(r, "Route alloc\n");
    r->start = NULL;
    r->end = NULL;
    return r;
}

Devolution_node *alloc_node_devolution()
{
    Devolution_node *dn = (Devolution_node *)malloc(sizeof(Devolution_node));
    check_allocation(dn, "Devolution node alloc");
    dn->route = alloc_node_route();
    dn->next = NULL;

    return dn;
}

Devolution *alloc_devolution() 
{
    Devolution *d = (Devolution *)malloc(sizeof(Devolution));
    check_allocation(d, "Devolution alloc");
    d->start = NULL;
    d->end = NULL;

    return d;
}

////////////////////////////////////////////////////

void free_client_node(Client *c) 
{
    if (c) 
    {
        free(c->cpf);
        free(c->name);
        free(c->address);
        free(c);
    }
}

void free_node_route(Route_node *rn) 
{
    if (rn) 
    {
        rn->next = NULL;
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

void free_node_deliveries(Deliveries_node *dn) 
{
    if (dn)
    {
        free_node_route(dn->route_node);
        free(dn);
    }
}

void free_deliveries(Deliveries *d) 
{
    if (d) 
    {
        Deliveries_node *current = d->top;
        while (current) 
        {
            Deliveries_node *next = current->next;
            free_node_deliveries(current);
            current = next;
        }
        free(d);
    }
}

void free_node_devolution(Devolution_node *node)
{
    if(node)
        free_node_route(node->route);
}

void free_devolution(Devolution *d) 
{
    if (d) 
    {
        Devolution_node *current = d->start;
        while (current) 
        {
            Devolution_node *next = current->next;
            free_node_route(current->route);
            current = next;
        }
        free(d);
    }
}

void free_client(Client *head) 
{
    Client *current = head;
    Client *next_client;

    while (current != NULL) 
    {
        next_client = current->next; 
        free_client_node(current);
        current = next_client;
    }
}


////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE PEDIDO //////////////////////////////////

// mostra um cliente especifico
void print_client(Client client)
{
    printf("ID_CLIENT - %d\n", client.id_client);
    printf("CPF  - %s\n", client.cpf);
    printf("Nome - %s\n", client.name);
    printf("Endereço - %s\n", client.address);
}

// Listagem de Clientes
void customer_list(Client *head) 
{
    Client *aux = head->next;
    while (aux) 
    {
        print_client(*aux);
        aux = aux->next;
    }
}

// Cadastro de Clientes
void customer_register(Client *head) 
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
void customer_search(Client *head) 
{
    Client *aux_client;
    Aux aux = {0};

    while (TRUE) 
    {
        printf("\n___ TIPOS DE BUSCA ____\n");
        do {
            printf("[1] - ID\n");
            printf("[2] - CPF\n");
            printf("[0] - VOLTAR\n");
            aux.opt = get_int("sua escolha");
        } 
        while(!valid_answer(0, 2, aux.opt));

        if (aux.opt == 0) break;

        switch (aux.opt) 
        {
        case 1:
            aux_client = head->next;

            do {
                aux.id = get_int("o id do cliente");
                aux.attempts += 1;
            } 
            while(!valid_answer(0, id_client, aux.id) && aux.attempts < 3);

            if (aux.attempts <= 3) 
            {
                while (aux_client) 
                {
                    if (aux_client->id_client == aux.id) 
                    {
                        print_client(*aux_client);
                        break;
                    }
                    aux_client = aux_client->next;
                }
            } 
            else 
                printf("Cliente não encontrado!\n");
            break;
        case 2:
            aux_client = head->next;

            do {
                get_char_digit("o cpf do cliente", aux.cpf);
            } 
            while(!validate_cpf(head, aux.cpf));

            while (aux_client) 
            {
                if (strcmp(aux_client->cpf, aux.cpf) == 0) 
                {
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

    while (TRUE) {
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
            } while (!valid_answer(0, id_client, aux.id) && aux.attempts <= 3);

            if (aux.attempts >= 3) break;

            while (aux_client) 
            {
                if (aux.id == aux_client->id_client) 
                {
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
                if (strcmp(aux.cpf, aux_client->cpf) == 0) 
                {
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

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE ROTA ////////////////////////////////////

void choose_product(Itens *item) 
{
    Aux aux = {0};

    aux.opt = random_choice(0, NUM_PRODUCTS - 1);
    item->product = aux.opt;
    item->price = products_prices[aux.opt];
    strcpy(item->name, products_text[aux.opt]);
}

// Adicionar Entrega na Rota
void add_delivery_route(Route *route, Client *client) 
{
    if (cont_client < 1)
        return;

    Client *aux = client;
    int client_index = random_choice(1, cont_client);

    for (int i = 0; i < client_index - 1; i++)
        aux = aux->next;

    Route_node *new_node = alloc_node_route();
    check_allocation(new_node, "Route node");

    // cria novo cliente/pedido para entrega 
    new_node->client = aux;
    choose_product(&new_node->item);
    id_delivery += 1;
    new_node->id_delivery = id_delivery;
    // new_node->id_delivery = (route->end) ? route->end->id_delivery + 1 : 1;
    new_node->next = NULL;

    // Verificar se o cliente já está na fila
    Route_node *existing_node = find_client_in_route(route, aux);
    if (existing_node) 
    {
        new_node->next = existing_node->next;
        existing_node->next = new_node;

        if (existing_node == route->end)
        {
            route->end->next = new_node;
            route->end = route->end->next;
        } 
    
        printf("Entrega adicionada após cliente existente: Cliente %s, Produto %s, Preço R$%.2f, ID Entrega %d\n",
               new_node->client->name, new_node->item.name, new_node->item.price, new_node->id_delivery);
        return;
    }

    // Verificar se o endereço já está na fila
    existing_node = find_address_in_route(route, aux->address);
    if (existing_node) 
    {
        new_node->next = existing_node->next;
        existing_node->next = new_node;
        if (existing_node == route->end) 
            route->end = new_node;

        printf("Entrega adicionada após endereço existente: Cliente %s, Produto %s, Preço R$%.2f, ID Entrega %d\n",
               new_node->client->name, new_node->item.name, new_node->item.price, new_node->id_delivery);
        return;
    }

    // Adicionar no final da fila se não encontrar cliente ou endereço
    if (!route->start) 
    {
        route->start = new_node;
        route->end = new_node;
    } 
    else 
    {
        route->end->next = new_node;
        route->end = new_node;
    }

    printf("Entrega adicionada no final da fila: Cliente %s, Produto %s, Preço R$%.2f, ID Entrega %d\n",
           new_node->client->name, new_node->item.name, new_node->item.price, new_node->id_delivery);
}

// Remover Entrega da Rota
void remove_delivery_route(Route *route) 
{
    if (route->start == NULL) 
    {
        printf("Nenhuma entrega para remover.\n");
        return;
    }

    Route_node *removed = route->start;
    route->start = removed->next;

    if (route->start == NULL) 
        route->end = NULL;

    printf("Entrega removida: Cliente %s, Produto %s, Preço R$%.2f, ID Entrega %d\n",
           removed->client->name, removed->item.name, removed->item.price, removed->id_delivery);

    free(removed);
}

// Listar Entregas na Rota
void list_route(Route *route) 
{
    if (route->start == NULL) 
    {
        printf("A rota de entregas está vazia.\n");
        return;
    }

    Route_node *current = route->start;
    printf("Lista de entregas na rota:\n");
    while (current != NULL) 
    {
        printf("ID Entrega: %d, Cliente: %s, Produto: %s, Preço: R$%.2f\n",
               current->id_delivery, current->client->name, current->item.name, current->item.price);
        current = current->next;
    }
}

// Função para Verificar se um Cliente Específico já Está na Fila
Route_node *find_client_in_route(Route *route, Client *client) 
{
    Route_node *current = route->start;
    while (current) 
    {
        if (current->client->id_client == client->id_client) 
            return current;

        current = current->next;
    }
    
    return NULL;
}

// Função para Verificar se um Endereço Específico já Está na Fila e Retornar o Nó
Route_node* find_address_in_route(Route *route, const char *address) 
{
    Route_node *current = route->start;
    while (current) 
    {
        if (strcmp(current->client->address, address) == 0) 
            return current;

        current = current->next;
    }
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE ENTREGA /////////////////////////////////

// verifica se o stack está vazio
BOOL is_empty(Deliveries *deliveries)
{
    return deliveries->top == NULL;
}

void undelivered_push(Deliveries *deliveries, Route_node *route_node) 
{
    Deliveries_node *new_node = (Deliveries_node *)malloc(sizeof(Deliveries_node));
    check_allocation(new_node, "Deliveries node");

    new_node->route_node = route_node;
    new_node->next = deliveries->top;
    deliveries->top = new_node;

    printf("PEDIDO (%s) DE %s EM %s ADICIONADO A ROTA DE NÃO EFETUADAS\n", new_node->route_node->item.name, new_node->route_node->client->name, new_node->route_node->client->address);
}

// Remover Entrega Não Efetuada da Pilha
Deliveries_node *undelivered_pop(Deliveries_node *deliveries)
{  
    if(deliveries)
    {
        Deliveries_node *removed = deliveries;
        deliveries = removed->next;
        // free_node_deliveries(removed);
        return deliveries;
    }

    return deliveries;
}
// Listar Entregas Não Efetuadas
void list_unfulfilled_deliveries(Deliveries *deliveries)
{
    Deliveries_node *aux = deliveries->top;
    if (aux==NULL)
        printf("A lista de não entregues esta vazia!");
    
    printf("Lista de entregas não efetuadas:\n");
    while (aux!=NULL)
    {
        printf("-=-=-=-=-=-=-=-\n");
        print_client(*deliveries->top->route_node->client);
        aux = aux->next;
    }

    free_node_deliveries(aux);
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE DEVOLUÇÃO ///////////////////////////////

// Adicionar Devolução na Fila
void add_devolution(Devolution *devolution, Deliveries *deliveries) 
{
    // fprintf(stderr, "Stack de deliveries está vazio\n");
    if (is_empty(deliveries)) 
        return;

    while (!is_empty(deliveries) && deliveries->top->route_node) 
    {
        Route_node *route_node = deliveries->top->route_node;

        // Aloca um novo nó de devolução
        Devolution_node *new_node = alloc_node_devolution();
        new_node->route = route_node;

        if (!devolution->start) 
        {
            devolution->start = new_node;
            devolution->end = new_node;
        } 
        else 
        {
            devolution->end->next = new_node;
            devolution->end = new_node;
        }

        deliveries->top = deliveries->top->next;
    }
}
// Remover Devolução da Fila
void remove_devolution(Devolution *devolution) 
{
    if (devolution->start == NULL) 
    {
        printf("Nenhuma devolução para remover.\n");
        return;
    }

    Devolution_node *removed = devolution->start;
    devolution->start = removed->next;
    
    if (devolution->start == NULL) 
        devolution->end = NULL;

    free_node_devolution(removed);
    printf("Devolução removida com sucesso.\n");
}


void list_devolutions(Devolution *devolution)
{
    Devolution_node *aux = devolution->start;
    printf("Lista de devolucoes: \n");

    while (aux != NULL)
    {
        printf("-=-=-=-=-=-=-=-\n");
        print_client(*aux->route->client);
        printf("-=-=-=-=-=-=-=-\n");
        aux = aux->next;
    }
}

// Funções para exibir os submenus e capturar a escolha do usuário
void menu_client(Client *client) 
{
    int choice;
    do {
        printf("\n==== MENU CLIENTES ====\n");
        printf("1. Registrar Cliente\n");
        printf("2. Buscar Cliente\n");
        printf("3. Remover Cliente\n");
        printf("4. Listar Clientes\n");
        printf("0. Voltar\n");
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
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (choice != 0);
}

void menu_route(Route *route, Client *client) 
{
    int choice;
    do {
        printf("\n==== MENU ROTAS ====\n");
        printf("1. Remover Entrega da Rota\n");
        printf("2. Listar Entregas na Rota\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção -> ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                remove_delivery_route(route);
                break;
            case 2:
                list_route(route);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (choice != 0);
}

void menu_delivery(Deliveries *deliveries) 
{
    int choice;
    do {
        printf("\n==== MENU ENTREGAS NÃO EFETUADAS ====\n");
        printf("1. Remover Entrega Não Efetuada da Pilha\n");
        printf("2. Listar Entregas Não Efetuadas\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                Deliveries_node *node1 = alloc_node_deliveries();
                printf("digite o endereco:");
                // scanf("%s", node1->client->address);
                // undelivered(deliveries, node1);
                break;
            case 2:
                // remove_undelivered(deliveries);
                break;
            case 3:
                list_unfulfilled_deliveries(deliveries);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (choice != 0);
}

void menu_devolution(Devolution *devolution) 
{
    int choice;
    do {
        printf("\n==== MENU DEVOLUÇÕES ====\n");
        printf("1. Adicionar Devolução na Fila\n");
        printf("2. Remover Devolução da Fila\n");
        printf("3. Listar Devoluções\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Deliveries_node *node1 = alloc_node_deliveries();
                break;
            case 2:
                remove_devolution(devolution);
                break;
            case 3:
                list_devolutions(devolution);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (choice != 0);
}

void main_menu(Route *route, Deliveries *deliveries, Devolution *devolution)
{
    Aux aux = {0};

    do {
        do
        {
            printf("\n--------- MENU DE ENTREGAS ----------\n");
            printf("1 - CADASTRAR CLIENTE\n");
            printf("2 - REMOVER CLINTE\n");
            printf("3 - LISTAR CLIENTE\n");
            printf("4 - ABRIR PARA PEDIDOS\n");
            printf("5 - REALIZAR ROTA DE ENTREGA\n");
            printf("6 - LISTAR DEVOLUÇÕES\n");
            printf("Escolha uma opção ->");
            scanf("%d", &aux.opt);
        }
        while(!valid_answer(0, 6, aux.opt));
        

        switch (aux.opt) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (aux.opt != 0);
}

// Verifica se um evento vai acontecer ou não
BOOL random_event(Odds odd) 
{
    int choice = random_choice(1, 100);
    return choice <= (int)odd;
}

// Calcular o score ao entregar ou na devolução
void score_calc_event(Score score) 
{
    total_score += score;
}

// Evento de rota, uma pessoa realiza um pedido
void route_event(Route *route, Client *client) 
{
    if(random_event(LOW_MID))
        add_delivery_route(route, client);
}

Route_node *next(Route_node *route) 
{
    if (!route)
        return route;

    route = route->next;
    return route;
}

void verify_next_client(Client *previous, Client *next, int *chances, Odds odd)
{
    if(odd > 0 && (previous->id_client == next->id_client || strcmp(previous->address, next->address) == 0))
        *chances = 100;
    else 
        *chances = odd;
}

// Evento que verifica se a pessoa estava em casa
void home_delivery_event(Route *route, Deliveries *deliveries, Devolution *devolution) 
{
    // Primeira tentativa
    printf("\n-- REALIZANDO A PRIMEIRA TENTATIVA DE ENTREGA --\n");
    Route_node *aux_route = route->start;

    int chances = MID_HIGH;

    while (aux_route) 
    {
        sleep(0.5);
        if (random_event(chances)) 
        {
            if(aux_route->next)
                verify_next_client(aux_route->client, aux_route->next->client, &chances, MID_HIGH);

            printf("PEDIDO (%s) ENTREGURE PARA %s no endereço %s [SCORE +5]\n", aux_route->item.name, aux_route->client->name, aux_route->client->address);
            score_calc_event(DELIVERY_FIRST);
 
            aux_route = aux_route->next;
        } 
        else 
        {
            if(aux_route->next)
                verify_next_client(aux_route->client, aux_route->next->client, &chances, 0);

            aux_route->attempts += 1;
            undelivered_push(deliveries, aux_route);
            
            aux_route = aux_route->next;
        }
    }
    printf("\n-- FINALIZANDO A PRIMEIRA TENTATIVA DE ENTREGA --\n");

    sleep(1.5);

    printf("\n--- INICIANDO A SEGUNDA  TENTATIVA DE ENTREGA ---\n");
    // Segunda tentativa
    chances = MID_HIGH;
    Deliveries_node *aux_deli = deliveries->top;
    while (aux_deli != NULL) 
    {
        sleep(0.5);
        if (random_event(chances)) 
        {
            if(aux_deli->next)
                verify_next_client(aux_deli->route_node->client, aux_deli->next->route_node->client, &chances, MID_HIGH);

            printf("PEDIDO (%s) ENTREGURE PARA %s NO ENDEREÇO %s [SCORE +3]\n", 
            aux_deli->route_node->item.name, 
            aux_deli->route_node->client->name, 
            aux_deli->route_node->client->address);
            score_calc_event(DELIVERY_SECOND);
            aux_deli = undelivered_pop(aux_deli);
        } 
        else 
        {
            if(aux_deli->next)
                verify_next_client(aux_deli->route_node->client, aux_deli->next->route_node->client, &chances, 0);

            printf("PEDIDO (%s) DE %s NO ENDEREÇO %s MOVIDO PARA DEVOLUÇÃO [SCORE -1]\n", aux_deli->route_node->item.name, aux_deli->route_node->client->name, aux_deli->route_node->client->address);
            aux_deli->route_node->attempts += 1;
            add_devolution(devolution, deliveries);
            score_calc_event(DELIVERY_DEVOLUTION);
            aux_deli = aux_deli->next;
        }
    }
    printf("\n--- FINALIZANDO A SEGUNDA TENTATIVA DE ENTREGA ---\n");
}

void init_operation()
{
    initialize_random();

    // criação de rota
    Route *route = alloc_route();
    // criação de pilha de entregas não efetuadas
    Deliveries *deliveries = alloc_deliveries();
    // criação de fila de devoluções
    Devolution *devolution = alloc_devolution();
    // criação de clientes
    Client *clients = (Client *)malloc(sizeof(Client));
    clients->id_client = 1;
    clients->cpf = strdup("12345");
    clients->name = strdup("Alef cauan");
    clients->address = strdup("123 Main St");
    clients->next = (Client *)malloc(sizeof(Client));
    clients->next->id_client = 2;
    clients->next->cpf = strdup("98765");
    clients->next->name = strdup("Jane Smith");
    clients->next->address = strdup("456 Elm St");
    clients->next->next = (Client *)malloc(sizeof(Client));
    clients->next->next->id_client = 3;
    clients->next->next->cpf = strdup("98767");
    clients->next->next->name = strdup("Lima");
    clients->next->next->address = strdup("466 Elm St");
    clients->next->next->next = NULL;
    clients->next->next->next = (Client *)malloc(sizeof(Client));
    clients->next->next->next->id_client = 4;
    clients->next->next->next->cpf = strdup("23456");
    clients->next->next->next->name = strdup("Alvez");
    clients->next->next->next->address = strdup("467 Junco");
    clients->next->next->next->next = NULL;
    cont_client += 4;

    int interval_seconds = 10;  // Ajuste o intervalo conforme necessário

    // Tempo de início
    time_t start_time = time(NULL);

    while (TRUE) 
    {
        // Executa a função route_event
        route_event(route, clients);

        // Verifica se o intervalo de tempo passou
        if (difftime(time(NULL), start_time) >= interval_seconds) 
        {
            // Executa a função home_delivery_event
            home_delivery_event(route, deliveries, devolution);
            // Atualiza o tempo de início para o próximo intervalo
            start_time = time(NULL);
            break;
        }

        // Adiciona uma pequena pausa para evitar alta utilização da CPU
        usleep(100000);  // Pausa de 100 milissegundos
    }
    
    printf("final score = %d\n", total_score);
    // Liberação de memória (implementação simplificada)
    free_route(route);
    free_deliveries(deliveries);
    free_devolution(devolution);
    free_client(clients);
}


int main() 
{
    init_operation();

    return 0;
}

