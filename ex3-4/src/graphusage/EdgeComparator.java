package graphusage;
import graph.Edge;
import java.util.Comparator;

/**
 * Comparator for edges based on their labels.
 */
public class EdgeComparator<V, L extends Number> implements Comparator<Edge<V, L>> {
  @Override
  public int compare(Edge<V, L> e1, Edge<V, L> e2) {
      return Double.compare(e1.getLabel().doubleValue(), e2.getLabel().doubleValue());
  }
}