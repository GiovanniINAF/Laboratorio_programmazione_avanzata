#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Definizione della dimensione fissa della tabella (preferibilmente un numero primo)
#define TABLE_SIZE 10

// --- Strutture Dati ---

// Struttura del Nodo (per la Linked List in caso di collisione)
typedef struct Entry {
    char *key;
    int value;
    struct Entry *next; // Puntatore al prossimo nodo (stessa logica della Linked List)
} Entry;

// Struttura della Tabella Hash
typedef struct HashTable {
    Entry *buckets[TABLE_SIZE]; // Array di puntatori a Entry (i nostri "bucket")
} HashTable;

// --- Funzioni di Utilità ---

// Funzione Hash: Calcola l'indice per la chiave (utilizza un semplice metodo modulo)
unsigned int hash(const char *key) {
    unsigned int hash_value = 0;
    // Somma i valori ASCII di tutti i caratteri della chiave
    for (int i = 0; i < strlen(key); i++) {
        hash_value = hash_value * 31 + key[i];
    }
    // Ritorna l'indice all'interno dei limiti della tabella
    return hash_value % TABLE_SIZE;
}

// Crea una nuova Entry (coppia chiave-valore)
Entry* create_entry(const char *key, int value) {
    Entry *new_entry = (Entry *)malloc(sizeof(Entry));
    if (new_entry == NULL) return NULL;
    
    // Alloca memoria e copia la chiave
    new_entry->key = strdup(key); 
    new_entry->value = value;
    new_entry->next = NULL;
    
    return new_entry;
}

// --- Operazioni sulla Hash Table ---

// Inserimento o Aggiornamento di una chiave-valore
void insert(HashTable *table, const char *key, int value) {
    unsigned int index = hash(key);
    Entry *current = table->buckets[index];
    
    // 1. Controlla se la chiave esiste già (aggiorna il valore)
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value; // Chiave trovata: aggiorna il valore
            return;
        }
        current = current->next;
    }
    
    // 2. Chiave non trovata: crea e inserisci una nuova Entry in testa al bucket
    Entry *new_entry = create_entry(key, value);
    if (new_entry == NULL) return; // Errore di memoria

    // L'Entry esistente (o NULL) diventa il "next" del nuovo elemento
    new_entry->next = table->buckets[index];
    // La nuova Entry diventa la testa del bucket
    table->buckets[index] = new_entry;
}

// Ricerca di un valore data la chiave
int search(HashTable *table, const char *key) {
    unsigned int index = hash(key);
    Entry *current = table->buckets[index];
    
    // Attraversa la Linked List fino a quando non trova la chiave o arriva alla fine
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value; // Chiave trovata!
        }
        current = current->next;
    }
    return -1; // Chiave non trovata (usiamo -1 come indicatore)
}

// Stampa il contenuto della Hash Table
void print_table(HashTable *table) {
    printf("\n--- Hash Table Contents ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *current = table->buckets[i];
        printf("Bucket %d:", i);
        while (current != NULL) {
            printf(" -> [%s: %d]", current->key, current->value);
            current = current->next;
        }
        printf(" -> NULL\n");
    }
    printf("---------------------------\n");
}

// Dealloca tutta la memoria dinamica allocata per la Hash Table
void free_table(HashTable *table) {
    Entry *current;
    Entry *temp;

    // Itera su tutti i bucket della tabella
    for (int i = 0; i < TABLE_SIZE; i++) {
        current = table->buckets[i];
        
        // Attraversa la lista concatenata in ogni bucket
        while (current != NULL) {
            // 1. Salva il puntatore al nodo successivo PRIMA di liberare il nodo corrente
            temp = current->next; 
            
            // 2. Libera la memoria allocata per la chiave (la stringa)
            free(current->key);   
            
            // 3. Libera la memoria allocata per la struttura Entry stessa
            free(current);        
            
            // 4. Passa al nodo successivo salvato in precedenza
            current = temp;       
        }
        // Opzionale, ma buona pratica: reimposta il puntatore del bucket a NULL
        table->buckets[i] = NULL;
    }
}

// Funzione principale per test
int main() {
    // Inizializzazione della Hash Table (tutti i bucket a NULL)
    HashTable my_table = {0}; 

    // Esempio di inserimento
    insert(&my_table, "mela", 5);
    insert(&my_table, "banana", 12);
    insert(&my_table, "arancia", 8);
    insert(&my_table, "uva", 20); // Potrebbe causare una collisione con una delle precedenti

    // Aggiornamento di un valore esistente
    insert(&my_table, "mela", 6); // Aggiorna il valore di "mela" da 5 a 6

    print_table(&my_table);

    // Esempio di ricerca
    printf("\nRicerca di 'banana': %d\n", search(&my_table, "banana")); // Output: 12
    printf("Ricerca di 'mela': %d\n", search(&my_table, "mela"));     // Output: 6
    printf("Ricerca di 'kiwi': %d (non trovato)\n", search(&my_table, "kiwi")); // Output: -1 (o valore definito per non trovato)

    // Libera la memoria!
    free_table(&my_table);
    
    return 0;
}
