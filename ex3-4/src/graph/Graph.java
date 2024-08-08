package graph;
import java.util.*;

/**
 * This class implements a generic graph that can be directed or undirected and
 * can be labeled or unlabeled. 
 * It uses a map to maintain nodes and a linked list to manage the edges of each node.
 * 
 * @param <V> The type of the nodes in the graph
 * @param <L> The type of the labels of the edges
 */
public class Graph<V, L> implements AbstractGraph<V, L>{

  private final boolean directed;
  private final boolean labelled;
  private HashMap<V, LinkedList<Edge<V,L>>> nodeMap; 
  
  /**
   * Constructs a new graph.
   * 
   * @param directed true if the graph is directed, false otherwise
   * @param labelled true if the graph is labeled, false otherwise
   */
  public Graph(boolean directed, boolean labelled){
    this.directed = directed;
    this.labelled = labelled;
    nodeMap = new HashMap<V, LinkedList<Edge<V,L>>>();
  }

  /**
   * @return true if the graph is directed, false otherwise
   */
  public boolean isDirected(){
    return this.directed;
  }
  
  /**
   * @return true if the graph is labelled, false otherwise
   */
  public boolean isLabelled(){
    return this.labelled;
  }
  
  /**
   * Adds a node to the graph
   * Ensures that the node does not already exist before adding it.
   *
   * @param newest the node to be added
   * @return true if the node is correctly added, false otherwise
   */
  public boolean addNode(V newest){
    if( containsNode(newest) ) return false;
    
    nodeMap.put(newest, new LinkedList<Edge<V,L>>());
    return true;
  }
  
  /**
   * Adds an edge to the graph, if it does not already exist.
   * If the graph is not labelled, the label is ignored.
   * If the graph is directed, the edge is added from nodeA to nodeB.
   * If the graph is not directed, the edge is added from nodeA to nodeB and from nodeB to nodeA.
   *
   * @param nodeA the starting node
   * @param nodeB the ending node
   * @param label the label of the edge
   * @return true if the edge is correctly added, false otherwise
   */
  public boolean addEdge(V nodeA, V nodeB, L label){
    
    if( this.labelled && label == null) return false;
    if(!this.labelled && label != null) return false;
    if(nodeA.equals(nodeB)) return false;
    if(!(containsNode(nodeA) && containsNode(nodeB))) return false;
    if(containsEdge(nodeA, nodeB)) return false;
    
    Edge<V,L> arcA = new Edge<V,L>(nodeA, nodeB, label);
    
    nodeMap.get(nodeA).add(arcA);
    
    if( !this.directed ){
      Edge<V,L> arcB = new Edge<V,L>(nodeB, nodeA, label);
      nodeMap.get(nodeB).add(arcB);
    }
    
    return true;
  }
  
  /**
   * Checks if a node is in the graph.
   *
   * @param a the node to be checked
   * @return true if the node is in the graph, false otherwise
   */
  public boolean containsNode(V a){
    return nodeMap.containsKey(a);
  }
  
  /**
   * Checks if an edge is in the graph.
   *
   * @param a the starting node
   * @param b the ending node
   * @return true if the edge is in the graph, false otherwise
   */
  public boolean containsEdge(V a, V b){
    if(!(containsNode(a) && containsNode(b))) return false;
    for(Edge<V, L> arc : nodeMap.get(a))
      if(arc.getEnd().equals(b)) return true;
    
    return false;
  }

  /**
   * @return the number of nodes in the graph
   */
  public int numNodes(){
    return nodeMap.size();
  }

  /**
   * @return the number of edges in the graph
   */
  public int numEdges(){
    int count = 0;
    for(V node : this.nodeMap.keySet())
      count += nodeMap.get(node).size();

    if(!directed)
      count = count/2;
    return count;
  }

  /**
   * @return a collection of all the nodes in the graph
   */
  public Collection<V> getNodes() {
    ArrayList<V> nodes = new ArrayList<>();
    if(!nodeMap.isEmpty()){
      for(V node : this.nodeMap.keySet()) {
        nodes.add(node);
      }
    }

    return nodes;
  }
  
  /**
   * Removes an edge from the graph, if it exists.
   * If the graph is not directed, the edge is removed from both nodes using removeUndirectedEdge().
   *
   * @param a the starting node
   * @param b the ending node
   * @return true if the edge is correctly removed, false otherwise
   */
  public boolean removeEdge(V a, V b){ // rimuove un arco dal grafo -- O(1) (*)
    if(!containsNode(a) || !containsNode(b)) return false;
    
    Edge<V,L> temp = getEdge(a, b);
    
    if(temp != null){
      nodeMap.get(a).remove(temp);
      if(!directed){
        return removeUndirectedEdge(b,a);
      }
      return true;
    }
    
    return false;
  }
  
  /**
   * Removes a node from the graph, if it exists.
   * Also removes all edges associated with the node.
   *
   * @param a the node to be removed
   * @return true if the node is correctly removed, false otherwise
   */
  public boolean removeNode(V a){
    if(!containsNode(a)) return false;
    
    for(V node : this.nodeMap.keySet()) { // O(N)
      if(!(node.equals(a))){
        removeUndirectedEdge(node, a);
      }
    }
    
    nodeMap.remove(a);
    return true;
  }

  /**
   * @return a collection of all the edges in the graph
   */
  public HashSet<Edge<V,L>> getEdges() {
    HashSet<Edge<V,L>> edges = new HashSet<>();

    if (!nodeMap.isEmpty()) {
      for(V node : this.nodeMap.keySet())
        edges.addAll(nodeMap.get(node));      
    }
    
    return edges;
  }

  /**
   * @param a the node to be checked
   * @return a collection of all the nodes adjacent to the given node
   */
  public Collection<V> getNeighbours(V a){
    ArrayList<V> adj = new ArrayList<>();
    for(Edge<V,L> arc : this.nodeMap.get(a))
      adj.add(arc.getEnd());

    return adj;
  }

  /**
   * Gets the label of the edge between two nodes, if it exists.
   *
   * @param a the starting node
   * @param b the ending node
   * @return the label of the edge between the two nodes
   */
  public L getLabel(V a, V b){
    if(this.labelled){
      if(containsNode(a) && containsNode(b)) {
        Edge<V,L> temp = getEdge(a, b);
        if(temp != null) return temp.getLabel();
      }
      System.err.println("Edge " + a.toString() + "-" + b.toString() + " not found.");
    }

    return null;
  }

  /**
   * Prints all the edges in the graph.
   * Useful for debugging and visualization purposes.
   */
  public void printEdges() {
    HashSet<Edge<V,L>> edges = getEdges();
    for(Edge<V,L> i : edges) {
      System.out.println(i.getStart().toString() + " to " +  i.getEnd().toString() + " with label " + i.getLabel().toString());
    }
  }
  
  /**
   * Removes an edge from the graph, if it exists
   * Instead of removeEdge(), this method is used to remove an edge from a graph that is not directed.
   *
   * @param a the starting node
   * @param b the ending node
   * @return true if the edge is correctly removed, false otherwise.
   */
  private boolean removeUndirectedEdge(V a, V b){ // rimuove un arco dal grafo -- O(1) (*)
  
    Edge<V,L> temp = getEdge(a, b);
    if(temp != null){
      nodeMap.get(a).remove(temp);
      return true;
    }
    else return false;
  }
  
  /**
   * Gets the edge between two nodes, if it exists.
   *
   * @param a the starting node
   * @param b the ending node
   * @return the edge between the two nodes
   */
  private Edge<V, L> getEdge(V a, V b){
    for(Edge<V, L> arc : nodeMap.get(a)){
      if(arc.getEnd().equals(b)){
        return arc;
      }
    }
    return null;
  }
  
}
