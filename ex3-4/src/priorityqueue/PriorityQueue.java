package priorityqueue;
import java.util.*;

/**
 * This class implements a generic priority queue using a heap.
 * 
 * @param <E> The type of elements in the priority queue
 */
public class PriorityQueue<E> implements AbstractQueue<E>{
	
  private ArrayList<E> queue;
  private Comparator<E> comparator;
  private HashMap<E, Integer> indexMap;

  private int nElem;

  /**
   * Constructs a new PriorityQueue with a default comparator.
   * 
   * @param comparator the comparator to be used to order the elements
   */
  public PriorityQueue(Comparator<E> comparator) {
    this.queue = new ArrayList<>();
    this.comparator = comparator;
    this.indexMap = new HashMap<E, Integer>();
	  nElem = 0;
  }

  @Override
  public String toString() {
    String s = "";
    for(int i = 0; i <= nElem - 1; i++){
      s = s + queue.get(i);
      if(i <= nElem - 2){
        s = s + ", ";
      }
    }
    return s;
  }
  

  /**
   * Checks if the priority queue is empty.
   *
   * @return true if the queue is empty, false otherwise.
   */
  public boolean empty() {
    return nElem == 0;  /*O(1)*/
  }
  
  /**
   * Checks if an element is in the priority queue.
   *
   * @param e the element to check for in the queue.
   * @return true if the queue contains the element e, false otherwise.
   */
  public boolean contains(E e) {
    return indexMap.containsKey(e);		/*O(1)*/
  }

  /**
   * Returns the element at the top of the priority queue without removing it.
   *
   * @return the element at the top of the priority queue.
   */
  public E top() {
    if(nElem == 0) return null;
    return queue.get(0);											
  }
  
  /**
   * Removes the element at the top of the queue.
   */
  public void pop() {
    if(!this.empty()){
      E lastElem = queue.get(nElem-1);
      E firstElem = queue.get(0);
      
      indexMap.remove(queue.set(0, lastElem));
      indexMap.replace(firstElem, 0);
      
      queue.remove(nElem-1);
      nElem--;
      if(nElem > 1)
        heapifyDown(0);
    }
  }
  
  
  /**
   * Adds an element to the priority queue.
   * If the element already exists, it is not added again.
   *
   * @param e the element to add to the priority queue
   * @return true if the element was successfully added, false otherwise
   */
  public boolean push(E e) {	
    if(contains(e)) return false; 			
    if(nElem == queue.size()){
      queue.add(e);	
    }
    else{
      queue.set(nElem, e); 
	  }
	  nElem++;
    indexMap.put(e, nElem-1);	

    if(compareElements(nElem-1, parent(nElem-1)) < 0)
      heapifyUp(nElem-1);	

    return true;
  }
  
  /**
   * Removes the element e from the priority queue.
   *
   * @param e the element to remove from the queue
   * @return true if the element was successfully removed, false otherwise
   */
  public boolean remove(E e) {	/*O(log N)*/
    if(!indexMap.containsKey(e)) return false;	

    int i = indexMap.get(e);

    heapSwap(i, nElem-1);

    indexMap.remove(e);
    nElem--;

    if(i < nElem/2)
      heapifyDown(i);
    if(compareElements(i, parent(i)) < 0)
      heapifyUp(i);
    
    return true;
  }
  

  /**
   * Returns the index of the parent of the node at index i.
   *
   * @param i the index of the node to get the parent of
   * @return the index of the parent of the node at index i, if it exists. Otherwise, return 0
   */
  private int parent(int i) {
    if (i == 0) return 0;
    return (i - 1) / 2;
  }

  /**
   * Returns the left child of the node at index i, if it exists.
   *
   * @param i the index of the node to get the left child of.
   * @return the index of the left child of the node at index i, if it exists. Otherwise, return i.
   */
  private int leftChild(int i) {
    if (2 * i + 1 < nElem )	return 2 * i + 1;
    return i;
  }

  /**
   * Returns the right child of the node at index i, if it exists.
   *
   * @param i the index of the node to get the right child of.
   * @return the index of the right child of the node at index i, if it exists. Otherwise, return i.
   */
  private int rightChild(int i) {
    if (2 * i + 2 < nElem)	return 2 * i + 2;
    return i;
  }
  
  /**
   * Heapifies the subtree rooted at index i.
   *
   * @param i the index of the root of the subtree to heapify.
   */
  private void heapifyDown(int i){	

    for(int m = min(i, leftChild(i), rightChild(i)) /*O(1)*/ ; m != i; m = min(i, leftChild(i), rightChild(i)) ) /*O(1)*/{
      heapSwap(i, m);
      i = m;
    }

  }

  /**
   * Performs heapification upwards starting from index i.
   * Necessary for when a random node it's been modified. 
   * Due to the structure of the Heap ADT one cannot be sure wether a node has a higher or lower priority than its parent.
   * In these cases a heapify is necessary towards the root before one can perform the 'standard' heapify towards the leefes.
   * 
   * @param i the index of the node to be fixed
   */
  private void heapifyUp(int i){ 
    do{ 
      heapSwap(i, parent(i));	
      i = parent(i);
      
    }while(compareElements(i, parent(i)) < 0);
  }

  /**
   * Determines the index of the minimum of the three elements at indexes i, l, and r.
   *
   * @param i the index of the first element to compare
   * @param l the index of the second element to compare
   * @param r the index of the third element to compare
   * @return the index of the minimum of the three elements
   */
  private int min(int i, int l, int r) {	
    int min = i;
    if (compareElements(l, min) < 0)
      min = l;
    if (compareElements(r, min) < 0)	
      min = r;	
    return min;
  }

  /**
   * Swaps the elements at indexes i and j in the priority queue.
   *
   * @param i index of the first element
   * @param j index of the second element
   */
  private void heapSwap(int i, int j){
    E temp = queue.get(i);
    queue.set(i, queue.get(j));
    queue.set(j, temp);

    indexMap.replace(queue.get(i), i);
    indexMap.replace(queue.get(j), j);
  }

  /**
   * Compares the elements at indexes i and j
   *
   * @param i index of the first element
   * @param j index of the second element
   * @return 0 if the elements are equal, a negative number if the element at index i is less than the element at index j, 
   *          and a positive number if the element at index i is greater than the element at index j.
   */
  private int compareElements(int i, int j){
    return comparator.compare(queue.get(i), queue.get(j));
  }

}
