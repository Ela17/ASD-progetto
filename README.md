# Laboratorio per il corso di Algoritmi e Strutture Dati

## Esercizio 1 - Merge Sort e Quick Sort

### Linguaggio richiesto: C

### Testo

Implementare una libreria che offre gli algoritmi di ordinamento  *Merge Sort* e *Quick Sort* su dati generici, implementando i seguenti prototipi di funzione:

```
void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));
void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));
```

- `base` è un puntatore al primo elemento dell'array da ordinare;
- `nitems` è il numero di elementi nell'array da ordinare;
- `size` è la dimensione in bytes di ogni elemento dell'array;
- `compar` è il criterio secondo cui ordinare i dati (dati due **puntatori a elementi** dell'array, restituisce un numero maggiore, uguale o minore di zero se il primo argomento è rispettivamente maggiore, uguale o minore del secondo).

È anche possibile implementare in alternativa i seguenti prototipi, che ordinano dati a patto che siano organizzati in un array di puntatori:

```
void merge_sort(void **base, size_t nitems, int (*compar)(const void*, const void*));
void quick_sort(void **base, size_t nitems, int (*compar)(const void*, const void*));
```

- `base` è un puntatore al primo elemento dell'array di puntatori da ordinare sulla base dei valori riferiti;
- `nitems` è il numero di elementi nell'array di puntatori da ordinare;
- `compar` è il criterio secondo cui ordinare i dati (dati due **elementi** dell'array di puntatori).

Dato che la prima versione è anche in grado di ordinare array di puntatori (passando un comparatore opportuno, i cui argomenti saranno puntatori a puntatori ai dati), non serve implementare questa seconda versione se avete già implementato la prima. In ogni caso non serve neanche implementare la prima se avete già implementato la seconda.

### Unit Testing

Implementare gli unit-test per la libreria secondo le indicazioni suggerite nel documento Unit Testing.

### Uso della libreria di ordinamento implementata

Il file `records.csv` che potete trovare (compresso) all'indirizzo:

> [https://datacloud.di.unito.it/index.php/s/9sQmzB9TdDHezX7](https://datacloud.di.unito.it/index.php/s/9sQmzB9TdDHezX7)

contiene 20 milioni di record da ordinare.
Ogni record è descritto su una riga e contiene i seguenti campi:

- `id`: (tipo intero) identificatore univoco del record;
- `field1`: (tipo stringa) contiene parole estratte dalla divina commedia,
  potete assumere che i valori non contengano spazi o virgole;
- `field2`: (tipo intero);
- `field3`: (tipo floating point).

Il formato è un CSV standard: i campi sono separati da virgole; i record sono
separati da `\n`.

Usando l'algoritmo implementato precedentemente, si realizzi la seguente funzione per ordinare *record* contenuti nel file `records.csv` in ordine non decrescente secondo i valori contenuti nei tre campi "field".

```
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo);
```

- `infile` è il file contenente i record da ordinare;
- `outfile` è il file nel quale salvare i record ordinati (che deve essere diverso da `infile`);
- `field` può valere 1, 2 o 3 e indica quale dei tre campi deve essere usato per ordinare i record.
- `algo` può valere 1 o 2 e indica quale algoritmo di ordinamento deve essere usato (MergeSort o QuickSort) per ordinare i record.

Si misurino i tempi di risposta per i due algoritmi, per ciascuno dei tre field che si possono usare come chiave di ordinamento, e si produca una breve relazione in cui si riportano i risultati ottenuti insieme a un loro commento. Il commento deve essere basato su statistiche numeriche sui tempi di esecuzione misurati. Nel caso l'ordinamento si protragga per più di 10 minuti potete interrompere l'esecuzione e riportare un fallimento dell'operazione. I risultati sono quelli che vi sareste aspettati? Se sì, perché? Se no, fate delle ipotesi circa il motivo per cui gli algoritmi non funzionano come vi aspettate, verificatele e riportate quanto scoperto nella relazione. I risultati dipendono dal campo usato come chiave di ordinamento?

## Esercizio 2 - Edit distance

### Linguaggio richiesto: C

### Testo

Si consideri il problema di determinare la minima distanza di edit tra due stringhe (_edit distance_): date due stringhe $s_1$ e $s_2$, non necessariamente della stessa lunghezza, determinare il minimo numero di operazioni necessarie per trasformare la stringa $s_2$ in $s_1$. Si assuma che le operazioni disponibili siano solo due: **cancellazione** e **inserimento**. Per esempio:

- "casa" e "cassa" hanno edit distance pari a 1 (1 cancellazione);
- "casa" e "cara" hanno edit distance pari a 2 (1 cancellazione + 1 inserimento);
- “vinaio” e “vino” hanno edit distance=2 (2 inserimenti);
- "tassa" e "passato" hanno edit distance pari a 4 (3 cancellazioni + 1 inserimento);
- "pioppo" e "pioppo" hanno edit distance pari a 0.

Si implementi innanzitutto una funzione ricorsiva di calcolo della edit distance, implementando il seguente prototipo di funzione:

```
int edit_distance(const char *s1, const char* s2);
```

- `s1` è la stringa che si vuole ottenere $s_1$;
- `s2` è la stringa di partenza $s_2$.

La struttura della funzione deve rispecchiare la seguente definizione (indichiamo con $|s|$ la lunghezza di $s$ e con $\mathrm{rest}(s)$ la sottostringa di $s$ ottenuta ignorando il primo carattere di $s$):

- se $|s_1|$ = 0, allora $\mathrm{edit\_distance}(s_1,s_2) = |s_2|$;
- se $|s_2|$ = 0, allora $\mathrm{edit\_distance}(s_1,s_2) = |s_1|$;
- altrimenti, siano:
  - $d_{\mathrm{no-op}} = \mathrm{edit\_distance}(\mathrm{rest}(s1),\mathrm{rest}(s2))$   se $s1[0]=s2[0]$, $\infty$ altrimenti
  - $d_{\mathrm{canc}} = 1 + \mathrm{edit\_distance}(s1,\mathrm{rest}(s2))$
  - $d_{\mathrm{ins}} = 1 + \mathrm{edit\_distance}(\mathrm{rest}(s1),s2)$

Si ha quindi che: $\mathrm{edit\_distance}(s_1,s_2) = \min\{d_{\mathrm{no-op}}, d_{\mathrm{canc}}, d_{\mathrm{ins}}\}$.

In seguito, si implementi anche una versione della funzione di calcolo della edit distance che adotta una strategia di programmazione dinamica. Tale versione deve essere anch'essa ricorsiva (in particolare, essa deve essere ottenuta attraverso un insieme minimale di modifiche apportate all'implementazione richiesta al punto precedente). La funzione deve implementare il seguente prototipo:

```
int edit_distance_dyn(const char *s1, const char* s2);
```

*Nota*: Le definizioni sopra riportate non corrispondono al modo usuale di definire la distanza di edit. Sono comunque quelle necessarie a risolvere l'esercizio e su cui dovrà essere basato il codice prodotto.

### Unit Testing

Implementare gli unit-test degli algoritmi secondo le indicazioni suggerite nel documento Unit Testing.

### Uso delle funzioni implementate

All'indirizzo:

> [https://datacloud.di.unito.it/index.php/s/9BKY7BXFCY4bMcB](https://datacloud.di.unito.it/index.php/s/9BKY7BXFCY4bMcB)

potete trovare un dizionario (`dictionary.txt`) e un file da correggere (`correctme.txt`).

Il dizionario contiene un elenco di parole. Le parole sono scritte di seguito, ciascuna su una riga.

Il file `correctme.txt` contiene un testo da correggere. Alcune parole in questo testo non ci sono nel dizionario.

Si implementi un'applicazione che usa la funzione `edit_distance_dyn` per determinare, per ogni parola `w` in `correctme.txt`, una breve lista di parole in `dictionary.txt` con edit distance minima da `w`. Si sperimenti il funzionamento dell'applicazione e si riporti in una breve relazione i risultati degli esperimenti.

## Esercizio 3 - PriorityQueue

### Linguaggio richiesto: Java

### Testo

Si implementi la struttura dati *coda con priorità (PriorityQueue)*.

La struttura dati deve gestire tipi generici e consentire un numero qualunque e non noto a priori di elementi, implementando la seguente interfaccia (con requisiti minimi di complessità):

```
public interface AbstractQueue<E> {
  public boolean empty(); // controlla se la coda è vuota -- O(1)
  public boolean push(E e); // aggiunge un elemento alla coda -- O(logN)
  public boolean contains(E e); // controlla se un elemento è in coda -- O(1)
  public E top(); // accede all'elemento in cima alla coda -- O(1)
  public void pop(); // rimuove l'elemento in cima alla coda -- O(logN)
  public boolean remove(E e); // rimuove un elemento se presente in coda -- O(logN)
};
```

*Suggerimento*: per implementare i metodi `contains` e `remove` potrebbe essere necessario usare una struttura dati di appoggio oltre allo heap (è ammesso usare strutture dati dalla libreria standard di Java se necessario).

La classe concreta `PriorityQueue<E>` che implementa l'interfaccia dovrebbe avere almeno un costruttore che crea una coda vuota e prende come argomento un `Comparator<E>` da usare per confrontare gli elementi:

```
PriorityQueue(Comparator<E> comparator)
```

_Nota_: `Comparator` è un'[interfaccia base](https://docs.oracle.com/en/java/javase/20/docs/api/java.base/java/util/Comparator.html) di Java.

### Unit Testing

Implementare gli unit-test degli algoritmi.

## Esercizio 4 - Grafi sparsi e foreste ricoprenti minime

### Linguaggio richiesto: Java

### Testo

Si implementi una libreria che realizza la struttura dati *Grafo* in modo che sia ottimale per dati sparsi.

L'implementazione deve essere generica sia per quanto riguarda il tipo dei nodi, sia per quanto riguarda le etichette
degli archi, implementando la seguente interfaccia (con requisiti minimi di complessità; dove _N_ può indicare il numero di nodi o il numero di archi, a seconda del contesto):

```
public interface AbstractGraph<V,L> {
  public boolean isDirected(); // dice se il grafo è diretto o meno -- O(1)
  public boolean isLabelled(); // dice se il grafo è etichettato o meno -- O(1)
  public boolean addNode(V a); // aggiunge un nodo -- O(1)
  public boolean addEdge(V a, V b, L l); // aggiunge un arco dati estremi ed etichetta -- O(1) (*)
  public boolean containsNode(V a); // controlla se un nodo è nel grafo -- O(1)
  public boolean containsEdge(V a, V b); // controlla se un arco è nel grafo -- O(1) (*)
  public boolean removeNode(V a); // rimuove un nodo dal grafo -- O(N)
  public boolean removeEdge(V a, V b); // rimuove un arco dal grafo -- O(1) (*)
  public int numNodes(); // numero di nodi -- O(1)
  public int numEdges(); // numero di archi -- O(N)
  public Collection<V> getNodes(); // recupero dei nodi del grafo -- O(N)
  public Collection<? extends AbstractEdge<V,L>> getEdges(); // recupero degli archi del grafo -- O(N)
  public Collection<V> getNeighbours(V a); // recupero dei nodi adiacenti ad un dato nodo -- O(1) (*)
  public L getLabel(V a, V b); // recupero dell'etichetta di un arco -- O(1) (*)
};
```

_(*)_ quando il grafo è veramente sparso, assumendo che l'operazione venga effettuata su un nodo la cui lista di adiacenza ha una lunghezza in O(1).

_Nota_: `AbstractCollection` è un'[interfaccia base](https://docs.oracle.com/en/java/javase/20/docs/api/java.base/java/util/AbstractCollection.html) di Java.

L'interfaccia `AbstractGraph` si basa sulla seguente interfaccia per la rappresentazione di un arco:

```
public interface AbstractEdge<V,L> {
  public V getStart(); // il nodo di partenza dell'arco
  public V getEnd(); // il nodo di arrivo dell'arco
  public L getLabel(); // l'etichetta dell'arco
};
```

La classe concreta `Graph<V,L>` che implementa l'interfaccia `AbstractGraph` dovrebbe avere almeno un costruttore che crea un grafo vuoto in complessità O(1) e prende come argomenti due valori booleani per impostare se il grafo è da considerarsi diretto o meno, e se è da considerarsi etichettato o meno:

```
Graph(boolean directed, boolean labelled)
```

A seconda del valore di questi due parametri, cambierà il comportamento dei metodi per gestire gli archi per tutte le operazioni successive.

*Suggerimento*:  un grafo non diretto può essere rappresentato usando un'implementazione per grafi diretti modificata
per garantire che, per ogni arco *(a,b)* etichettato *w*, presente nel grafo, sia presente nel grafo anche l'arco *(b,a)*
etichettato *w*. Ovviamente, il grafo dovrà mantenere l'informazione che specifica se esso è un grafo diretto o non diretto.
Similmente, un grafo non etichettato può essere rappresentato usando l'implementazione per grafi etichettati modificata per garantire
che le etichette siano sempre `null` (che invece non devono mai essere `null` per i grafi etichettati).

### Unit Testing

Implementare gli unit-test degli algoritmi.

### Uso della libreria che implementa la struttura dati Grafo

Si implementi l'algoritmo di Prim per la determinazione della minima foresta ricoprente di un grafo, secondo il seguente template:

```
public class Prim {
  public static <V, L extends Number> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(Graph<V, L> graph) {
    // calcola la minima foresta ricoprente con l'algoritmo di Prim
    // restituisce la collezione degli archi che formano la foresta
  }
  public static void main(String[] args) {
    // leggi i dati CSV del grafo dal percorso in args[1]
    // calcola la minima foresta ricoprente con minimumSpanningForest
    // scrivi su standard output solo la descrizione della foresta calcolata come CSV con formato analogo a quello in input
    // su standard error si possono scrivere ulteriori informazioni, come il numero di nodi e archi nella foresta calcolata,
    // o il peso totale della foresta
  }
}
```

L'implementazione dell'algoritmo di Prim dovrà utilizzare la struttura dati *PriorityQueue* implementata nell'esercizio precedente e la struttura dati grafo appena implementata.
La struttura dati e l'algoritmo di Prim dovranno poi essere utilizzati con i dati contenuti nel file `italian_dist_graph.csv`, che potete recuperare all'indirizzo:

> [https://datacloud.di.unito.it/index.php/s/FqneW99EGWLSRpY](https://datacloud.di.unito.it/index.php/s/FqneW99EGWLSRpY)

Tale file contiene le distanze in metri tra varie località italiane e una frazione delle località a loro più vicine. Il formato è un CSV standard: i campi sono separati da virgole; i record sono separati dal carattere di fine riga (`\n`).

Ogni record contiene i seguenti dati:

- `place1`: (tipo stringa) nome della località "sorgente" (la stringa può contenere spazi ma non può contenere virgole);
- `place2`: (tipo stringa) nome della località "destinazione" (la stringa può contenere spazi ma non può contenere virgole);
- `distance`: (tipo float) distanza in metri tra le due località.

**Note:**

- Nel caso in cui il grafo sia costituito da una sola componente connessa, l'algoritmo restituirà un albero. Nel caso in cui, invece, vi siano più componenti connesse, l'algoritmo restituirà una foresta costituita dai minimi alberi ricoprenti di ciascuna componente connessa.
- Potete intrepretare le informazioni presenti nelle righe del file come archi **non diretti** (per cui probabilmente vorrete inserire nel vostro grafo sia l'arco di andata che quello di ritorno a fronte di ogni riga letta).
- Il file è stato creato a partire da un dataset poco accurato. I dati riportati contengono inesattezze e imprecisioni.
- Un'implementazione corretta dell'algoritmo di Prim, eseguita sui dati contenuti nel file `italian_dist_graph.csv`, dovrebbe determinare una minima foresta ricoprente con 18.640 nodi, 18.637 archi (non orientati) e di peso complessivo di circa 89.939,913 Km.