#include <stdio.h>
#include <stdlib.h>

// Definiamo la struttura del nostro "bigliettino" (il Nodo)
typedef struct Node {
    int data;                 // Il dato che vogliamo conservare
    struct Node *next;        // Il puntatore al prossimo nodo
} Node;

// Funzione per creare un nuovo nodo. Ritorna un puntatore al nodo creato.
Node* create_node(int data) {
    // Chiediamo al sistema memoria sufficiente per un nuovo nodo
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Errore: impossibile allocare memoria.\n");
        exit(1);
    }
    newNode->data = data; // Mettiamo il dato nel nodo
    newNode->next = NULL; // Il nuovo nodo, per ora, non punta a nulla
    return newNode;
}

// Funzione per inserire un nuovo nodo in testa alla lista
void insert_at_head(Node **head, Node *node_to_insert) {
    node_to_insert->next = *head; // Il nuovo nodo punta a quello che prima era il primo
    *head = node_to_insert;       // La nostra "testa" della lista ora è il nuovo nodo
}

// Funzione per stampare la lista
void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next; // Passiamo al prossimo
    }
    printf("NULL\n");
}

// Funzione per liberare tutta la memoria allocata per la lista
void free_list(Node *head) {
    Node *current = head;
    Node *temp;
    while (current != NULL) {
        temp = current;          // Salviamo il nodo corrente
        current = current->next; // Passiamo al successivo
        free(temp);              // Liberiamo la memoria del nodo salvato
    }
}

int main() {
    // Inizialmente, la nostra lista è vuota
    Node *head = NULL;

    // Creiamo qualche nodo
    Node *n1 = create_node(10);
    Node *n2 = create_node(20);
    Node *n3 = create_node(30);
    Node *n4 = create_node(40);
    
    // Inseriamoli in testa. L'ordine finale sarà 30 -> 20 -> 10
    insert_at_head(&head, n1);
    insert_at_head(&head, n2);
    insert_at_head(&head, n3);
    insert_at_head(&head, n4);

    printf("La mia lista concatenata: ");
    print_list(head);

    // Importantissimo: liberiamo la memoria!
    free_list(head);

    return 0;
}
