#include <stdio.h>
#include <stdlib.h>

// Definizione della struttura per un singolo nodo della lista
typedef struct List_node {
    int key;                 // Valore principale memorizzato nel nodo
    int i, j;                // Indici o coordinate (es. riga e colonna di una matrice)
    struct List_node *next;  // Puntatore al nodo successivo nella lista
} List_node;

// Definizione della struttura per l'intera lista
typedef struct List {
    List_node *head;         // Puntatore al primo nodo della lista (la "testa")
} List;

// -----------------------------------------------------------
// FUNZIONI DI BASE
// -----------------------------------------------------------

/**
 * @brief Crea e alloca memoria per una nuova struttura List.
 * * @return List* Puntatore alla lista appena creata.
 */
List *create_list() {
    // Alloca memoria per la struttura List
    List *list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        perror("Errore di allocazione per List");
        exit(EXIT_FAILURE);
    }
    // Inizializza la testa a NULL: la lista è vuota
    list->head = NULL;
    return list;
}

/**
 * @brief Crea e alloca memoria per un nuovo nodo.
 * * @param data Il valore 'key' da assegnare al nodo.
 * @param row L'indice di riga (viene memorizzato come row + 1).
 * @param col L'indice di colonna (viene memorizzato come col + 1).
 * @return List_node* Puntatore al nodo appena creato.
 */
List_node *mk_node(int data, int row, int col) {
    // Alloca memoria per la struttura List_node
    List_node *node = (List_node *)malloc(sizeof(List_node));
    if (node == NULL) {
        perror("Errore di allocazione per List_node");
        exit(EXIT_FAILURE);
    }
    // Inizializza i campi
    node->key = data;
    // Gli indici sono memorizzati come base 0 (col, row) (C order)
    node->i = row;
    node->j = col;
    node->next = NULL; // Il nuovo nodo di solito è l'ultimo o viene inserito in mezzo
    return node;
}

// -----------------------------------------------------------
// FUNZIONI DI INSERIMENTO
// -----------------------------------------------------------

/**
 * @brief Inserisce il nodo 'x' all'inizio della lista.
 * * @param x Il nodo da inserire.
 * @param list La lista in cui inserire.
 */
void insert_first(List_node *x, List *list) {
    // 1. Il 'next' del nuovo nodo punta all'attuale testa
    x->next = list->head;
    // 2. La 'head' della lista diventa il nuovo nodo
    list->head = x;
}

/**
 * @brief Inserisce il nodo 'x' subito dopo un nodo esistente 'y'.
 * * @param x Il nodo da inserire.
 * @param y Il nodo dopo il quale inserire 'x'.
 */
void insert(List_node *x, List_node *y) {
    if (y == NULL) {
        fprintf(stderr, "Errore: il nodo 'y' deve essere valido per l'inserimento intermedio.\n");
        return;
    }
    // 1. Il 'next' del nuovo nodo punta a ciò che era dopo 'y'
    x->next = y->next;
    // 2. Il 'next' di 'y' punta ora al nuovo nodo 'x'
    y->next = x;
}

// -----------------------------------------------------------
// FUNZIONI DI UTILITY
// -----------------------------------------------------------

/**
 * @brief Stampa il contenuto di tutta la lista.
 * * @param list La lista da stampare.
 * @param name Un carattere identificativo per la lista (es. 'A', 'B').
 */
void print_list(List *list, char name) {
    List_node *p;
    p = list->head;
    printf("\nLa lista concatenata %c consiste di: ", name);
    // Itera finché non si raggiunge la fine della lista (NULL)
    while (p != NULL) {
        printf("%d(i = %d) (j = %d) -> ", p->key, p->i, p->j);
        p = p->next; // Passa al nodo successivo
    }
    printf("NULL\n"); // Indica la fine della lista
}

/**
 * @brief Dealloca tutta la memoria occupata dalla lista e dai suoi nodi.
 * * @param list La lista da cancellare.
 */
void delete_list(List *list) {
    List_node *node, *temp;
    node = list->head;

    // Itera attraverso ogni nodo per liberare la memoria
    while (node != NULL) {
        temp = node->next; // Salva il puntatore al nodo successivo
        free(node);        // Libera la memoria del nodo corrente
        node = temp;       // Passa al nodo successivo salvato
    }
    // Libera la memoria della struttura List stessa
    free(list);
    printf("Lista deallocata con successo.\n");
}

// -----------------------------------------------------------
// ESEMPIO DI UTILIZZO (main)
// -----------------------------------------------------------

int main() {
    // 1. Creazione della lista
    List *my_list = create_list();
    printf("Lista creata (vuota).\n");

    // 2. Creazione di nodi
    List_node *n1 = mk_node(10, 0, 0); // key=10, i=0, j=0
    List_node *n2 = mk_node(20, 1, 5); // key=20, i=1, j=5
    List_node *n3 = mk_node(30, 9, 3); // key=30, i=9, j=3
    List_node *n4 = mk_node(40, 4, 4); // key=40, i=4, j=4
    List_node *n5 = mk_node(50, 5, 6); // key=50, i=5, j=6

    // 3. Inserimento di nodi

    // Inserisco n1 per primo
    insert_first(n1, my_list); // Lista: 10
    print_list(my_list, 'M');

    // Inserisco n2 all'inizio
    insert_first(n2, my_list); // Lista: 20 -> 10
    print_list(my_list, 'M');

    // Inserisco n4 all'inizio
    insert_first(n4, my_list); // Lista: 40 -> 20 -> 10
    print_list(my_list, 'M');
    
    // Inserisco n3 dopo n2 (n2 è il secondo nodo, my_list->head->next)
    // n2 è (my_list->head->next)
    insert(n3, my_list->head->next); // Lista: 40 -> 20 -> 30 -> 10
    print_list(my_list, 'M');

    // Inserisco n5 dopo n3 
    insert(n5, n3); // Lista: 40 -> 20 -> 30 -> 50 -> 10
    print_list(my_list, 'M');

    // 4. Deallocazione della lista
    delete_list(my_list);

    return 0;
}
