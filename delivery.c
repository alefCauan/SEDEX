#include <stdio.h>
#include "delivery.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
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
    printf("DIGITE %s ->", mensage);
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
    dn->client = alloc_client();
    dn->next = NULL;
    return dn;
}

Route_node *alloc_node_route() 
{
    Route_node *rn = (Route_node *)malloc(sizeof(Route_node));
    check_allocation(rn, "Route_node alloc\n");
    rn->client = alloc_client();
    rn->next = NULL;
    return rn;
}

Deliveries *alloc_deliveries() 
{
    Deliveries *d = (Deliveries *)malloc(sizeof(Deliveries));
    check_allocation(d, "Deliveries alloc\n");
    d->top = NULL;
    return d;
}

Devolution *alloc_devolution() {
    Devolution *d = (Devolution *)malloc(sizeof(Devolution));
    check_allocation(d, "Devolution alloc\n");
    d->start = NULL;
    d->end = NULL;
    return d;
}

Route *alloc_route() 
{
    Route *r = (Route *)malloc(sizeof(Route));
    check_allocation(r, "Route alloc\n");
    r->start = NULL;
    r->end = NULL;
    return r;
}

////////////////////////////////////////////////////

void free_client(Client *c) 
{
    if (c) 
    {
        free(c->cpf);
        free(c->name);
        free(c->address);
        free(c);
    }
}

void free_node_deliveries(Deliveries_node *dn) 
{
    if (dn) 
    {
        free_client(dn->client);
        free(dn);
    }
}

void free_node_route(Route_node *rn) 
{
    if (rn) 
    {
        free_client(rn->client);;
        free(rn);
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

void free_devolution(Devolution *d) 
{
    if (d) 
    {
        Route_node *current = d->start;
        while (current) 
        {
            Route_node *next = current->next;
            free_node_route(current);
            current = next;
        }
        free(d);
    }
}



////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE PEDIDO //////////////////////////////////

// mostra um cliente espesifico
void print_client(Client client)
{
    printf("Nome: %s\n", client.name);
    printf("CPF: %s\n", client.cpf);
    printf("Endereço: %s\n", client.address);
    printf("ID: %d\n", client.id_client);
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
        while (!valid_answer(0, 2, aux.opt));

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
                    free_client(aux_client);
                    printf("Cliente removido com sucesso.\n");
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
                    free_client(aux_client);
                    printf("Cliente removido com sucesso.\n");
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
Deliveries make_delivery(Route *route){
    alloc_deliveries();
}
////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE ENTREGA /////////////////////////////////

// Adicionar Entrega Não Efetuada na Pilha
void add_undelivered(Deliveries *deliveries, Deliveries_node *deliveries_node){
    if (deliveries->top!=NULL){
    deliveries_node->next = deliveries->top;
    deliveries->top = deliveries_node->next; 
    }else{
    deliveries->top = deliveries_node;
}

}
// Remover Entrega Não Efetuada da Pilha
void remove_undelivered(Deliveries *deliveries)
{  
    if(deliveries->top!=NULL)
    {
        Deliveries_node *removed = deliveries->top;
        deliveries->top = removed->next;
        printf("produto removido");
        // return removed; 
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
        print_client(*aux->client);
        aux = aux->next;
    }
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNÇÕES DE DEVOLUÇÃO ///////////////////////////////

// Adicionar Devolução na Fila
void add_devolution(Devolution *devolution, Deliveries_node *deliveries_node)
{
    printf("a");
}
// Remover Devolução da Fila
void remove_devolution(Devolution *devolution) 
{
    if (devolution->start == NULL) {
        printf("Nenhuma devolução para remover.\n");
        return;
    }

    Route_node *removed = devolution->start;
    devolution->start = removed->next;
    
    if (devolution->start == NULL) 
        devolution->end = NULL;

    free_node_route(removed);
    printf("Devolução removida com sucesso.\n");
}


void list_devolutions(Devolution *devolution)
{
    Route_node *aux = devolution->end;
    printf("Lista de devolucoes: \n");
    while (aux!=NULL)
    {
        printf("-=-=-=-=-=-=-=-\n");
        printf("Id: %d", aux->id_delivery);
        print_client(*aux->client);
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

void menu_route(Route *route) 
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
                add_delivery_route(route);
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
                scanf("%s", node1->client->address);
                add_undelivered(deliveries, node1);
                break;
            case 2:
                remove_undelivered(deliveries);
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
                scanf("%s", node1->client->address);
                add_devolution(devolution, node1);
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

// Função para exibir o menu principal e capturar a escolha do usuário
void menu() 
{
    int choice;
    Client *client = alloc_client();
    Route *route = alloc_route();
    Deliveries *deliveries = alloc_deliveries();
    Devolution *devolution = alloc_devolution();

    do {
        printf("\n==== MENU PRINCIPAL ====\n");
        printf("1. Menu Clientes\n");
        printf("2. Menu Rotas\n");
        printf("3. Menu Entregas Não Efetuadas\n");
        printf("4. Menu Devoluções\n");
        printf("0. Sair\n");
        printf("Escolha uma opção -> ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                menu_client(client);
                break;
            case 2:
                menu_route(route);
                break;
            case 3:
                menu_delivery(deliveries);
                break;
            case 4:
                menu_devolution(devolution);
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


int main()
{
    menu();
    return 0;
}
