#include <stdio.h>
#include "delivery.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <errno.h>
#include <time.h>

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

    printf("Num aleatorio: %d\n", num);
    return num;
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
        free(rn);
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
    printf("Nome: %s\n", client.name);
    printf("CPF: %s\n", client.cpf);
    printf("Endereço: %s\n", client.address);
    printf("ID: %d\n", client.id_client);
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

    // for (int i = 0; i < NUM_PRODUCTS; i += 2) 
    // {
    //     printf("[%2d] - %13s ", i, products_text[i]);
    //     printf("| [%2d] - %13s\n", i + 1, products_text[i + 1]);

    // }

    // do{
    //     if(aux.attempts > 0)
    //         printf("Escolha inválida. Por favor, tente novamente\n");
        
    //     aux.opt = get_int("Digite o número do produto desejado");
    //     aux.attempts += 1;
    // } 
    // while(!valid_answer(1, NUM_PRODUCTS - 1, aux.opt));
    aux.opt = random_choice(0, NUM_PRODUCTS);
    printf("product: %d\n", aux.opt);
    item->product = aux.opt;
    item->price = products_prices[aux.opt];
    strcpy(item->name, products_text[aux.opt]);

}

// Adicionar Entrega na Rota
void add_delivery_route(Route *route, Client *client) 
{
    if(cont_client < 1)
        return;

    Client *aux = client;
    int client_index = random_choice(1, cont_client);
    printf("client: %d\n", client_index);
    for(int i = 0; i < client_index - 1; i++)
        aux = aux->next;


    Route_node *new_node = (Route_node *)malloc(sizeof(Route_node));
    check_allocation(new_node, "Route node");

    new_node->client = aux;
    choose_product(&new_node->item);
    new_node->id_delivery = (route->end) ? route->end->id_delivery + 1 : 1;
    new_node->next = NULL;

    if(!route->start) 
    {
        route->start = new_node;
        route->end = new_node;
    } 
    else 
    {
        route->end->next = new_node;
        route->end = new_node;
    }

    printf("Entrega adicionada: Cliente %s, Produto %s, Preço R$%.2f, ID Entrega %d\n",
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

    printf("Entrega movida para pilha de não efetuadas: Cliente %s, Produto %s, Preço R$%.2f, ID Entrega %d\n",
           route_node->client->name, route_node->item.name, route_node->item.price, route_node->id_delivery);
}

// Remover Entrega Não Efetuada da Pilha
Deliveries_node *undelivered_pop(Deliveries *deliveries)
{  
    if(!is_empty(deliveries))
    {
        Deliveries_node *removed = deliveries->top;
        deliveries->top = removed->next;
        printf("produto removido");
        return removed;
    }
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
    if (is_empty(deliveries)) 
    {
        fprintf(stderr, "Stack de deliveries está vazio\n");
        return;
    }

    while (!is_empty(deliveries)) 
    {
        Route_node *route_node = deliveries->top->route_node;

        // Se as tentativas forem menores que 2, apenas remova da pilha
        if (route_node->attempts < 2) 
        {
            Deliveries_node *temp = deliveries->top;
            deliveries->top = deliveries->top->next;
            free_node_deliveries(temp);
            continue;
        }
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

    printf("Todas as entregas não efetuadas foram movidas para a fila de devoluções.\n");
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
        printf("1. Adicionar Entrega na Rota\n");
        printf("2. Remover Entrega da Rota\n");
        printf("3. Listar Entregas na Rota\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção -> ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                add_delivery_route(route, client);
                break;
            case 2:
                remove_delivery_route(route);
                break;
            case 3:
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
        printf("1. Adicionar Entrega Não Efetuada na Pilha\n");
        printf("2. Remover Entrega Não Efetuada da Pilha\n");
        printf("3. Listar Entregas Não Efetuadas\n");
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
                printf("digite o endereco:");
                // scanf("%s", node1->client->address);
                // add_devolution(devolution, node1);
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

int main() 
{
    initialize_random();

    // Exemplo de criação de clientes
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
    clients->next->next = NULL;
    cont_client += 2;
    

    // Exemplo de criação de rota
    Route *route = alloc_route();
    // Exemplo de criação de pilha de entregas não efetuadas
    Deliveries *deliveries = alloc_deliveries();
    // Exemplo de criação de fila de devoluções
    Devolution *devolution = alloc_devolution();
    // Adiciona entrega na rota
    add_delivery_route(route, clients);
    add_delivery_route(route, clients);
    add_delivery_route(route, clients);

    // Move uma entrega não efetuada para a pilha de entregas não efetuadas
    while (route->start)
    {
        Route_node *node_to_move = route->start;
        route->start = route->start->next;
        undelivered_push(deliveries, node_to_move);
    }
    
    // Adiciona a entrega não efetuada à fila de devoluções após a segunda tentativa falha
    add_devolution(devolution, deliveries);

    // Lista as devoluções
    list_devolutions(devolution);

    // Liberação de memória (implementação simplificada)
    free_client(clients);
    free_route(route);
    free_deliveries(deliveries);
    free_devolution(devolution);

    return 0;
}

