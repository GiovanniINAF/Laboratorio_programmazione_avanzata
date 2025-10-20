# Esercizi su Linked lists, binary trees e Hash tables

## Linked Lists
Il file linked_list.c contiene un esempio di linked list, in cui dei numeri interi vengono
ricorsivamente inseriti in testa alla lista. Provate a compilare e modificare il codice
a vostro piacimento inserendo ulteriori numeri in testa alla lista, per prendere dimestichezza.

```
Esercizio 1: Provate ad inserire un nuovo numero ma stavolta non in testa alla lista, ma tra
due numeri già presenti nella stessa.
Esercizio 2: Come funzionerebbe se, invece di assegnare dei numeri sparsi nella lista (sparse vector),
si provasse a costruire una sparse matrix?
```

## Binary trees
Il file binary_tree.c contiene un esempio di struttura ad albero, in cui le parole vengono
ordinate alfabeticamente, in modo che se una nuova parola viene prima in ordine alfabetico
rispetto alla parola del nodo precedente viene assegnata al nodo (sottoalbero) sinistro, altrimenti viene
assegnata al nodo destro. La memoria del tree non viene liberata nell'esempio, provate a
liberarla basandovi sull'esempio della linked list.

```
Esercizio 3: Provate a generare dei numeri casuali compresi tra 0 e 1 e creare un binary tree,
in modo tale che un nuovo numero venga assegnato al nodo sinistro se minore del valore del nodo
precedente, oppure al nodo destro se maggiore.
```

## Hash Tables
Il file hash_table_simple.c contiene un esempio di hash table, mi piacerebbe che provaste a
compilarlo e girarlo, cercando di capire cosa il codice fa. 

## Ollama (Facoltativo, ne riparleremo più avanti)
Se voleste usare l'intelligenza artificiale per aiutarvi con il coding, vi proporrei un'alternativa
a ChatGPT o Gemini. Ollama ha supporto per Linux, Windows e MacOS. Vi permette di girare dei modelli
LLM sia sulla vostra macchina in locale (se avete abbastanza RAM), oppure vi permette un certo numero
di prompt giornalieri su un modello cloud che è possibile testare gratuitamente.
