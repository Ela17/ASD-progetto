package test.priorityqueue;

import priorityqueue.*;

import static org.junit.Assert.*;

import java.util.Comparator;

import org.junit.Before;
import org.junit.Test;

public class UnitTestBase{

  PriorityQueue<Integer> pq;

  @Before
  public void setUp() throws Exception {
    Comparator<Integer> comp = Comparator.naturalOrder();
    pq = new PriorityQueue<Integer>(comp);
  }

  @Test(timeout=100)
  public void testEmptyTrue() {
    assertTrue( "Prova fallita: Empty con coda vuota", pq.empty());
  }
  
  @Test(timeout=100)
  public void testEmptyFalse() {
    pq.push(1);
    assertFalse( "Prova fallita: Empty con coda piena", pq.empty());
  }
   
  @Test(timeout=100)
  public void testPushTrue() {
    assertTrue( "Prova fallita: Push con coda vuota, test = push-true", pq.push(1));
  }
  
  @Test(timeout=100)
  public void testPushEmptyQueue() {
    boolean flag = pq.push(1);
    if(flag)
      assertEquals( "Prova fallita: Push con coda vuota, test = top", (int)pq.top(), 1);
    else
      fail("Prova fallita: Push con coda vuota, test = push");
  }

  @Test(timeout=100)
  public void testPushLowerNumber() {
    boolean flag = pq.push(10);
    flag = flag && pq.push(1);
    if(flag)
      assertEquals( "Prova fallita: Push con un numero minore, test = top", (int)pq.top(), 1);
    else
      fail("Prova fallita: Push con un numero minore, test = push");
  }
  
  @Test(timeout=100)
  public void testPushHigherNumber_Contains(){
    boolean flag = pq.push(1);
    flag = flag && pq.push(10);
    if(flag)
      assertTrue( "Prova fallita: Push con un numero maggiore, test = contains", pq.contains(1) );
    else
      fail("Prova fallita: Push con un numero maggiore, test = push");
  }

  @Test(timeout=100)
  public void testPushHigherNumber_Top() {
    boolean flag = pq.push(1);
    flag = flag && pq.push(10);
    if(flag)
      assertEquals( "Prova fallita: Push con un numero maggiore, test = top", (int)pq.top(), 1);
    else
      fail("Prova fallita: Push con un numero maggiore, test = push");
  }
    
  @Test(timeout=100)
  public void testPushExistingValue() {
    boolean flag = pq.push(1);
    flag = flag && pq.push(10);
    if(flag)
      assertFalse( "Prova fallita: Push con un numero esistente, test = push-false", pq.push(1));
    else
      fail("Prova fallita: Push con un numero esistente, test = push");
  }
    
  @Test(timeout=100)
  public void testPush30Values_PushLower_Contains() {
    boolean flag_push = true, flag_contains = true;
    
    for(int i=30; i>0; i--) 
      flag_push = flag_push && pq.push(i);
    
    for(int i=1; i<=30; i++){
      flag_contains = flag_contains && pq.contains(i);
    }
    if(flag_push)
      assertTrue( "Prova fallita: Push di molti valori sempre più piccoli, test = contains-true", flag_contains);
    else
      fail("Prova fallita: Push di molti valori sempre più piccoli, test = push");
  }
    
  @Test(timeout=100)
  public void testPush30Values_PushHigher_Contains() {
    boolean flag_push = true, flag_contains = true;
    for(int i=0; i<30; i++) flag_push = flag_push && pq.push(i);
    
    for(int i=29; i>=0; i--){
      flag_contains = flag_contains && pq.contains(i);
    }
    
    if(flag_push)
      assertTrue( "Prova fallita: Push di molti valori sempre più grandi, test = contains-true", flag_contains);
    else
      fail("Prova fallita: Push di molti valori sempre più grandi, test = push");
  }
    
  @Test(timeout=100)
  public void testContainsEmptyQueue() {
    assertFalse( "Prova fallita: Contains con coda vuota, test = contains-false", pq.contains(1));
  }
  
  @Test(timeout=100)
  public void testContainsFalse() {
    pq.push(1);
    pq.push(3);
    pq.push(4);
    pq.push(5);
    assertFalse( "Prova fallita: Contains trova un valore non in coda, test = contains-false", pq.contains(2));
  }
  
  @Test(timeout=100)
  public void testContainsTrueFirst() {
    pq.push(1);
    pq.push(2);    
    pq.push(3);
    pq.push(4);
    pq.push(5);
    assertTrue( "Prova fallita: Contains non trova il primo valore in coda, test = contains-true", pq.contains(1));
  }
  
  @Test(timeout=100)
  public void testContainsTrueLast() {
    pq.push(1);
    pq.push(2);    
    pq.push(3);
    pq.push(4);
    pq.push(5);
    assertTrue( "Prova fallita: Contains non trova l'ultimo valore in coda, test = contains-true", pq.contains(5));
  }
  
  @Test(timeout=100)
  public void testContainsTrue() {
    pq.push(1);
    pq.push(2);    
    pq.push(3);
    pq.push(4);
    pq.push(5);
    assertTrue( "Prova fallita: Contains non trova un valore in coda, test = contains-true", pq.contains(2));
  }
  
  @Test(timeout=100)
  public void testTopEmptyQueue() {
    assertNull( "Prova fallita: top con coda vuota, test = top-Null", pq.top());
  }
  
  @Test(timeout=100)
  public void testTopQueue() {
    pq.push(5);
    assertEquals( "Prova fallita: top con coda non-vuota, test = top-Equals", (int)pq.top(), 5);
  }

  @Test(timeout=100)
  public void testPopEmptyQueue() {
    boolean flag = pq.empty();
    pq.pop();
    flag = flag && pq.empty();
    assertTrue( "Prova fallita: pop da coda vuota, test = empty-true", flag);
  }
    
 @Test(timeout=100)
  public void testPopOneElementQueue() {
    pq.push(1);
    pq.pop();
    assertTrue( "Prova fallita: pop da coda con un elemento, test = empty-true", pq.empty());
}
  
  @Test(timeout=100)
  public void testPopMultipleElementQueue_Contains() {
    pq.push(10);
    pq.push(5);
    pq.push(1);
    pq.pop();
    assertFalse( "Prova fallita: pop da coda con più elementi, test = contains-false", pq.contains(1));
  }
  
  @Test(timeout=100)
  public void testPopMultipleElementQueue_Top() {
    pq.push(10);
    pq.push(5);
    pq.push(1);
    pq.pop();
    assertEquals( "Prova fallita: pop da coda con più elementi, test = top", (int)pq.top(), 5);
  }
    
  @Test(timeout=100)
  public void testRemoveEmptyQueue() {
    assertFalse( "Prova fallita: remove da coda vuota, test = remove-false", pq.remove(10));
  }
  
  @Test(timeout=100)
  public void testRemoveQueue_ElementNotExisting() {
    pq.push(1);
    pq.push(2);
    pq.push(4);
    pq.push(5);

    assertFalse( "Prova fallita: remove di elemento non in coda, test = remove-false", pq.remove(3));
  }
  
  @Test(timeout=100)
  public void testRemoveOneElementQueue() {
    pq.push(10);
    if(pq.remove(10))
      assertTrue( "Prova fallita: remove da coda con un solo elemento, test = contains-true", pq.empty() );
    else
      fail("Prova fallita: remove da coda con un solo elemento non effettuata, test = remove");
  }
    
  @Test(timeout=100)
  public void  testRemoveQueue_ElementExisting() {
    pq.push(1);
    pq.push(2);
    pq.push(3);
    pq.push(4);
    pq.push(5);
    
    boolean flag =  pq.remove(3);
    if(flag)
      assertFalse( "Prova fallita: non effettuata remove di elemento in coda, test = contains-false", pq.contains(3));
    else
      fail("Prova fallita: non effettuata remove di elemento in coda, test = remove");
  }
  
  @Test(timeout=100)
  public void  testRemoveQueueUntilEmpty() {
    pq.push(1);
    pq.push(2);
    pq.push(3);
    pq.push(4);
    pq.push(5);
    
    boolean flag =  pq.remove(3);
    flag = flag && pq.remove(2);
    flag = flag && pq.remove(4);
    flag = flag && pq.remove(5);
    flag = flag && pq.remove(1);
    if(flag)
      assertTrue( "Prova fallita: rimossi tutti gli elementi ma coda risulta non-vuota, test = empty-true", pq.empty());
    else
      fail("Prova fallita: non effettuata remove di elemento in coda, test = remove");
  }
  
}