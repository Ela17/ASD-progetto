package test.graph;

import graph.*;

import java.util.Collection;
import static org.junit.Assert.*;
import org.junit.Before;
import org.junit.Test;

public class UnitTest{

  Graph<String,Integer> graph00;
  Graph<String,Integer> graph01;
  Graph<String,Integer> graph10;

  @Before
  public void setUp() throws Exception {
    graph00 = new Graph<String,Integer>(false, false);
    graph01 = new Graph<String,Integer>(false, true);
    graph10 = new Graph<String,Integer>(true, false);
  }

  @Test(timeout=100)
  public void testIsDirected00() {
    assertFalse("Test failed: graph00 should be not directed.", graph00.isDirected());
  }  
  
  @Test(timeout=100)
  public void testIsDirected10() {
    assertTrue("Test failed: graph10 should be directed.", graph10.isDirected());
  }

  @Test(timeout=100)
  public void testIsLabelled00() {
    assertFalse("Test failed: graph00 should be not labelled.", graph00.isLabelled());
  }  

  @Test(timeout=100)
  public void testIsLabelled01() {
    assertTrue("Test failed: graph01 should be labelled.", graph01.isLabelled());
  }  

  @Test(timeout=100)
  public void testAddNode() {
    assertTrue(graph00.addNode("A"));
  }

  @Test(timeout=100)
  public void testAddExistingNode() {
    graph00.addNode("A");
    assertFalse("Test failed: addNode -> node already exists.", graph00.addNode("A"));
  }

  @Test(timeout=100)
  public void testAddEdgeLabelled() {
      graph01.addNode("A");
      graph01.addNode("B");
      assertTrue(graph01.addEdge("A", "B", 0));
  }

  @Test(timeout=100)
  public void testAddExistingEdgeLabelled() {
      graph01.addNode("A");
      graph01.addNode("B");
      graph01.addEdge("A", "B", 0);
      assertFalse("Test failed: addEdge -> edge already exists.", graph01.addEdge("A", "B", 1));
  }

  @Test(timeout=100)
  public void testAddEdgeLabelledNull() {
      graph01.addNode("A");
      graph01.addNode("B");
      assertFalse("Test failed: addEdge -> can't create an unlabelled edge in a labelled graph.", graph01.addEdge("A", "B", null));
  }

  @Test(timeout=100)
  public void testAddEdgeNotLabelled() {
      graph00.addNode("A");
      graph00.addNode("B");
      assertTrue(graph00.addEdge("A", "B", null));
  }

  @Test(timeout=100)
  public void testAddExistingEdgeNotLabelled() {
      graph00.addNode("A");
      graph00.addNode("B");
      graph00.addEdge("A", "B", null);
      assertFalse("Test failed: addEdge -> edge already exists.", graph00.addEdge("A", "B", null));
  }

  @Test(timeout=100)
  public void testAddEdgeNotLabelledNotNull() {
      graph00.addNode("A");
      graph00.addNode("B");
      assertFalse("Test failed: addEdge -> can't create a labelled edge in an unlabelled graph.", graph00.addEdge("A", "B", 1));
  }

  @Test(timeout=100)
  public void testContainsNodeTrue() {
    graph00.addNode("A");
    assertTrue("Test failed: containsNode -> graph should contain node 'A'", graph00.containsNode("A"));
  }  
  
  @Test(timeout=100)
  public void testContainsNodeFalse() {
    graph00.addNode("A");
    assertFalse("Test failed: containsNode -> graph should not contain node 'B'", graph00.containsNode("B"));
  }

  @Test(timeout=100)
  public void testContainsNodeAfterRemove() {
      graph00.addNode("A");
      graph00.addNode("B");
      graph00.removeNode("A");
      assertFalse("Test failed: containsNode -> graph should not contain node 'A' after removal", graph00.containsNode("A"));
  }
  
  @Test(timeout=100)
  public void testContainsEdge() {
    graph00.addNode("A");
    graph00.addNode("B");
    graph00.addEdge("A", "B", null);
    assertTrue("Test failed: containsEdge -> graph should contain edge between 'A' and 'B'", graph00.containsEdge("A", "B"));
  }  
  
  @Test(timeout=100)
  public void testDirectedContainsSpecularEdge() {
    graph00.addNode("A");
    graph00.addNode("B");
    graph00.addEdge("A", "B", null);
    assertTrue("Test failed: containsEdge -> graph should contain edge between 'B' and 'A'", graph00.containsEdge("B", "A"));
  }

  @Test(timeout=100)
  public void testUndirectedContainsSpecularEdge() {
    graph10.addNode("A");
    graph10.addNode("B");
    graph10.addEdge("A", "B", null);
    assertFalse("Test failed: containsEdge -> graph should not contain edge between 'B' and 'A'", graph10.containsEdge("B", "A"));
  }

  @Test(timeout=100)
  public void testRemoveNode() {
    graph00.addNode("A");
    graph00.addNode("B");
    graph00.addEdge("A", "B", null);
    assertTrue("Test failed: removeNode -> removing node 'A' should succeed", graph00.removeNode("A"));
  }
  
  @Test(timeout=100)
  public void testContainsEdgeAfterRemoveNode() {
    graph00.addNode("A");
    graph00.addNode("B");
    graph00.addEdge("A", "B", null);
    graph00.removeNode("A");
    assertFalse("Test failed: removeNode -> graph should not contain edge 'A'-'B' after node 'A' removal", graph00.containsEdge("A", "B"));
  }

  @Test(timeout=100)
  public void testRemoveEdgeTrue() {
      graph00.addNode("A");
      graph00.addNode("B");
      graph00.addEdge("A", "B", null);
      assertTrue("Test failed: removeEdge -> removing edge between 'A' and 'B' should succeed", graph00.removeEdge("A", "B"));
  }

  @Test(timeout=100)
  public void testRemoveEdgeFalse() {
      graph00.addNode("A");
      graph00.addNode("B");
      graph00.addEdge("A", "B", null);
      graph00.removeEdge("A", "B");
      assertFalse("Test failed: removeEdge -> graph should not contain edge between 'A' and 'B' after removal", graph00.containsEdge("A", "B"));
  }

  @Test(timeout=100)
  public void testUndirectedContainsSpecularEdgeAfterRemoveEdge() {
    graph00.addNode("A");
    graph00.addNode("B");
    graph00.addEdge("A", "B", null);
    graph00.removeEdge("A", "B");
    assertFalse("Test failed: removeNode -> graph should not contain edge 'B'-'A' after edge 'A'-'B' removal", graph00.containsEdge("B", "A"));
  }

  @Test
  public void testNumNodes() {
      graph00.addNode("A");
      graph00.addNode("B");
      assertEquals("Test failed: numNodes -> number of nodes should be 2", 2, graph00.numNodes());
  }

  @Test
  public void testNumNodesAfterRemoval() {
      graph00.addNode("A");
      graph00.addNode("B");
      graph00.removeNode("A");
      assertEquals("Test failed: numNodes -> number of nodes should be 1", 1, graph00.numNodes());
  }

  @Test(timeout=100)
  public void testUndirectedNumEdges() {
    graph00.addNode("A");
    graph00.addNode("B");
    graph00.addNode("C");
    graph00.addEdge("A", "B", null);
    graph00.addEdge("A", "C", null);
    assertEquals("Test failed: numEdges -> number of edges should be 2", 2, graph00.numEdges());
  }  
  
  @Test(timeout=100)
  public void testDirectedNumEdges() {
    graph10.addNode("A");
    graph10.addNode("B");
    graph10.addNode("C");
    graph10.addEdge("A", "B", null);
    graph10.addEdge("A", "C", null);
    assertEquals("Test failed: numEdges -> number of edges should be 2", 2, graph10.numEdges());
  }

  @Test(timeout=100)
  public void testNumEdgesAfterRemoveNode() {
      graph00.addNode("A");
      graph00.addNode("B");
      graph00.addNode("C");
      graph00.addEdge("A", "B", null);
      graph00.addEdge("A", "C", null);
      graph00.removeNode("B");
      assertEquals("Test failed: numEdges -> number of edges should be 1", 1, graph00.numEdges());
  }

  @Test(timeout=100)
  public void testNumEdgesAfterRemoval() {
      graph00.addNode("A");
      graph00.addNode("B");
      graph00.addNode("C");
      graph00.addEdge("A", "B", null);
      graph00.addEdge("A", "C", null);
      graph00.removeEdge("A", "B");
      assertEquals("Test failed: numEdges -> number of edges should be 1", 1, graph00.numEdges());
  }

  @Test(timeout=100)
  public void testGetNodes() {
      graph00.addNode("A");
      graph00.addNode("B");
      graph00.addNode("C");
      Collection<String> nodes = graph00.getNodes();
      assertEquals("Test failed: getNodes -> nodes collection should contain 3 nodes", 3, nodes.size());
  }

  @Test(timeout=100)    
  public void testGetEdgesUndirected() {
    graph00.addNode("A");
    graph00.addNode("B");
    graph00.addNode("C");
    graph00.addNode("D");
    graph00.addEdge("A", "B", null);
    graph00.addEdge("A", "C", null);
    graph00.addEdge("B", "D", null);
    Collection<Edge<String, Integer>> edges = graph00.getEdges();
    assertEquals("Test failed: getEdges -> edges collection should contain 6 edges", 6, edges.size());
  }

  @Test(timeout=100)    
  public void testGetEdgesDirected() {
    graph10.addNode("A");
    graph10.addNode("B");
    graph10.addNode("C");
    graph10.addNode("D");
    graph10.addEdge("A", "B", null);
    graph10.addEdge("A", "C", null);
    graph10.addEdge("B", "D", null);
    Collection<Edge<String, Integer>> edges = graph10.getEdges();
    assertEquals("Test failed: getEdges -> edges collection should contain 3 edges", 3, edges.size());
  }

  @Test(timeout=100)
  public void testGetNeighbours() {
    graph00.addNode("A");
    graph00.addNode("B");
    graph00.addNode("C");
    graph00.addNode("D");
    graph00.addEdge("A", "B", null);
    graph00.addEdge("A", "C", null);
    graph00.addEdge("B", "D", null);
    Collection<String> neighboursA = graph00.getNeighbours("A");
    assertEquals("Test failed: getNeighbours -> neighbours collection should contain 2 nodes", 2, neighboursA.size());
    Collection<String> neighboursC = graph00.getNeighbours("C");
    assertEquals("Test failed: getNeighbours -> neighbours collection should contain 1 nodes", 1, neighboursC.size());
  }

}
