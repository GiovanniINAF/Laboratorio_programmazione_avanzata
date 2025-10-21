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

// Funzione per inserire un nuovo nodo in subito dopo un nodo esistente
void insert(Node *node, Node *node_to_insert) {
    if (node == NULL) {
        fprintf(stderr, "Errore: il nodo 'node' deve essere valido per l'inserimento intermedio.\n");
        return;
    }
    // 1. Il 'next' del nuovo nodo punta a ciò che era dopo 'node'
    node_to_insert->next = node->next;
    // 2. Il 'next' di 'node' punta ora al nuovo nodo 'node_to_insert'
    node->next = node_to_insert;
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
    Node *n5 = create_node(50);
    Node *n6 = create_node(60);
   
    
    // Inseriamoli in testa. L'ordine finale sarà 40 -> 30 -> 20 -> 10
    insert_at_head(&head, n1);
    insert_at_head(&head, n2);
    insert_at_head(&head, n3);
    insert_at_head(&head, n4);

    // Inseriamo il nodo n5 subito dopo il nodo n3. L'ordine finale sarà 40 -> 30 -> 50 -> 20 -> 10
    insert(n3, n5);

    // Inseriamo il nodo n6 subito dopo il nodo n2. L'ordine finale sarà 40 -> 30 -> 50 -> 20 -> 60 -> 10
    insert(n2, n6);
    
    printf("La mia lista concatenata: ");
    print_list(head);

    // Importantissimo: liberiamo la memoria!
    free_list(head);

    return 0;
}
