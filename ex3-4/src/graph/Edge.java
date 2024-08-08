package graph;

/**
 * This class represents an edge in a graph.
 *
 * @param <V> the type of vertices in the graph
 * @param <L> the type of labels on the edges, if the graph is labelled
 */
public class Edge<V,L> implements AbstractEdge<V,L>{

  private V start;
  private V end;
  private L label;

  /**
   * Constructs a new edge between two vertices with a specified label.
   *
   * @param start the starting vertex of the edge
   * @param end the ending vertex of the edge
   * @param label the label of the edge, representing the relationship between start and end vertices
   */
  public Edge(V start, V end, L label) {
    this.start = start;
    this.end = end;
    this.label = label;
  }
  
  /**
   * Retrieves the starting vertex of the edge.
   *
   * @return the starting vertex of the edge
   */
  @Override
  public V getStart() {
    return start;
  }

  /**
   * Retrieves the ending vertex of the edge.
   *
   * @return the ending vertex of the edge
   */
  @Override
  public V getEnd() {
    return end;
  }

  /**
   * Retrieves the label associated with the edge.
   *
   * @return the label of the edge, representing the relationship between start and end vertices
   */
  @Override
  public L getLabel() {
    return label;
  }
  
  /**
   * Returns a string representation of the edge in the format "start -> end    label".
   *
   * @return a string representation of the edge
   */
  @Override
  public String toString() {
    return start + " -> " + end + "\t" + label;
  }
}
