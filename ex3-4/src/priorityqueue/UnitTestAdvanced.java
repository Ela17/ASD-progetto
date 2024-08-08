package test.priorityqueue;

import priorityqueue.*;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import java.util.Comparator;

/**
 * Unit test for PriorityQueue.
 */
public class UnitTestAdvanced{

  PriorityQueue<Integer> pq;

  @Before
  public void setUp() throws Exception {
    Comparator<Integer> comp = Comparator.naturalOrder();
    pq = new PriorityQueue<Integer>(comp);
    pq.push(1);
    pq.push(2);
    pq.push(3);
    pq.push(4);
    pq.push(5);
  }

  public void clean(){
    while(pq.empty() == false){
      pq.pop();
    }
  }

  @Test(timeout=100)
  public void testEmptiedQueue() {
    
    clean();
    
    assertTrue( "Prova fallita: queue non vuota dopo essere svuotata, test = empty-true", pq.empty());

  }

  @Test(timeout=100)
  public void testRipopulatedQueue() {
    
    clean();
    pq.push(1);
    
    assertFalse( "Prova fallita: queue vuota dopo essere Ripopolata, test = empty-false", pq.empty());
  }


  @Test(timeout=100)
  public void testDoublePush() {
    
    pq.remove(3);
    
    assertTrue( "Prova fallita: non effettuata push di elemento non in coda, test = push-true", pq.push(3));
  }
  
  @Test(timeout=100)
  public void testDoubleRemove_False() {
    
    pq.remove(3);
    
    assertFalse( "Prova fallita: effettuata remove di elemento non in coda, test = remove-false", pq.remove(3));
  }
  
  @Test(timeout=100)
  public void testDoubleRemove_True() {
    
    pq.remove(3);
    pq.push(3);
    
    assertTrue( "Prova fallita: non effettuata remove di elemento in coda, test = push-true", pq.remove(3));
  }
  
  @Test(timeout=100)
  public void testContainsFalse_RemovedElement() {
    
    pq.remove(3);
    
    assertFalse( "Prova fallita: trovato elemento non in coda, test = contains-false", pq.contains(3));
  }
  
  @Test(timeout=100)
  public void testContainsFalse_ReinseredElement() {
    
    pq.remove(3);
    pq.push(3);
    assertTrue( "Prova fallita: non trovato elemento in coda, test = contains-true", pq.contains(3));
  }

  @Test(timeout=100)
  public void testTopEmptiedQueue() {
    
    clean();
    
    assertNull( "Prova fallita: errore nella Top con coda Svuotata, test = top-Null", pq.top());
  }
  
  @Test(timeout=100)
  public void testTopRipopulatedQueue() {
    
    clean();
    pq.push(6);
    pq.push(7);
    pq.push(8);
    pq.push(9);
    pq.push(10);
    
    assertEquals( "Prova fallita: errore nella Top con coda Ririempita, test = top-Equals", (int)pq.top(), 6);
  }
  
}