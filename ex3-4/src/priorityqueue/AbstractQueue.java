package priorityqueue;
public interface AbstractQueue<T> {
  public boolean empty(); // controlla se la coda è vuota -- O(1)
  public boolean push(T t); // aggiunge un elemento alla coda -- O(logN)
  public boolean contains(T t); // controlla se un elemento è in coda -- O(1)
  public T top(); // accede all'elemento in cima alla coda -- O(1)
  public void pop(); // rimuove l'elemento in cima alla coda -- O(logN)
  public boolean remove(T t); // rimuove un elemento se presente in coda -- O(logN)
};