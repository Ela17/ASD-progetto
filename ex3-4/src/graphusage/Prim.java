package graphusage;
import priorityqueue.PriorityQueue;

import java.io.*;
import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.util.*;

import graph.AbstractEdge;
import graph.Edge;
import graph.Graph;

/**
 * The class contains methpods to compute the Minimum Spanning Forest of a graph using Prim's algorithm.
 * The class contains a main method that reads a graph from a csv file and writes the Minimum Spanning Forest to another csv file.
 */
public class Prim {

  /**
   * Computes the Minimum Spanning Forest of a graph using Prim's algorithm.
   * @param <V> the type of the nodes in the graph.
   * @param <L> the type of the labels of the edges in the graph.
   * @param graph the graph to compute the Minimum Spanning Forest of.
   * @return a collection of edges that form the Minimum Spanning Forest.
   */
  public static <V, L extends Number> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(Graph<V, L> graph) {
    HashSet<V> visited = new HashSet<>();
    LinkedList<Edge<V,L>> result = new LinkedList<>();
    PriorityQueue<Edge<V,L>> queue = new PriorityQueue<>(new EdgeComparator<>());

    for (V startNode : graph.getNodes()) {
      if (!visited.contains(startNode)) {
        mstPrim(graph, startNode, visited, queue, result);
      }
    }
    
    return result;
  }

  /**
   * Prim's algorithm to compute the Minimum Spanning Tree of a graph starting from a given node.
   * @param <V> the type of the nodes in the graph.
   * @param <L> the type of the labels of the edges in the graph.
   * @param graph the graph to compute the Minimum Spanning Tree of.
   * @param startNode the node to start the computation from.
   * @param visited the set of nodes that have been visited.
   * @param queue the priority queue of edges.
   * @param result the list of edges that form the Minimum Spanning Tree.
   */
  private static <V, L extends Number> void mstPrim(Graph<V, L> graph, V startNode, HashSet<V> visited, PriorityQueue<Edge<V, L>> queue, LinkedList<Edge<V,L>> result) {
    visited.add(startNode);

    for (V neighbor : graph.getNeighbours(startNode)) {
      L label = graph.getLabel(startNode, neighbor);
      queue.push(new Edge<>(startNode, neighbor, label));
    }
    
    while (!queue.empty()) {
      Edge<V, L> minEdge = queue.top();
      queue.pop();

      V targetNode = minEdge.getEnd();

      if (!visited.contains(targetNode)) {
        visited.add(targetNode);
        result.add(minEdge);

        for (V neighbor : graph.getNeighbours(targetNode)) {
          if (!visited.contains(neighbor)) {
            L label = graph.getLabel(targetNode, neighbor);
            queue.push(new Edge<V,L>(targetNode, neighbor, label));
          }
        }
      }
    }
  }


  public static void main(String[] args) {

    if (args.length < 1) {
      System.err.println("Usage: java Prim <input_file>");
      System.exit(1);
    }

    String inputFile = args[0];
    Graph<String, Double> graph = new Graph<>(false, true);

    try {
      graph = readGraphFromCsv(inputFile);
    } catch (IOException e) {
      System.err.println("Error reading input file: " + e.getMessage());
      System.exit(1);
    }

    @SuppressWarnings("unchecked")
    LinkedList<Edge<String, Double>> mst = (LinkedList<Edge<String, Double>>) minimumSpanningForest(graph);
    mst.sort(new EdgeComparator<>());

    printForestOnCsv(mst);
  }


  /**
   * Reads a graph from a csv file.
   * @param path the path to the csv file.
   * @return the graph read from the csv file.
   * @throws IOException if an I/O error occurs.
   */
  private static Graph<String, Double> readGraphFromCsv(String path) throws IOException {
    Graph<String, Double> graph = new Graph<>(false, true);
        
    try (BufferedReader br = new BufferedReader(new FileReader(path))) {
      String line;
      while ((line = br.readLine()) != null) {
        String[] parts = line.split(",");
        String place1 = parts[0];
        String place2 = parts[1];
        double distance = Double.parseDouble(parts[2]);
        
        graph.addNode(place1);
        graph.addNode(place2);
        graph.addEdge(place1, place2, distance);
      }
    }
        
    return graph;
  }

  /**
   * Prints the Minimum Spanning Forest to a csv file.
   * @param mst the Minimum Spanning Forest to print.
   */
  private static void printForestOnCsv(LinkedList<Edge<String, Double>> mst) {
    DecimalFormatSymbols symbols = new DecimalFormatSymbols(Locale.US);
    DecimalFormat df = new DecimalFormat("0.000000", symbols);

    try (BufferedWriter writer = new BufferedWriter(new FileWriter("my_file.csv"))) {
      Double totWeight = 0.0;

      for (AbstractEdge<String, Double> edge : mst) {
        String start = edge.getStart();
        String end = edge.getEnd();
        if (start.compareTo(end) > 0) {
          String tmp = start;
          start = end;
          end = tmp;
        }
        writer.write(start + "," + end + "," + df.format(edge.getLabel()));
        writer.newLine();
        totWeight += edge.getLabel();
      }

      writer.newLine();
      writer.write("Number of edges: " + mst.size());
      writer.newLine();
      writer.write("Total weight: " + totWeight + " km");

    } catch (IOException e) {
      e.printStackTrace();
    }

  }

  /**
   * Prints the Minimum Spanning Forest to the standard output.
   * @param mst the Minimum Spanning Forest to print.
   */
  private static void printForest(LinkedList<Edge<String, Double>> mst) {
    DecimalFormatSymbols symbols = new DecimalFormatSymbols(Locale.US);
    DecimalFormat df = new DecimalFormat("0.000000", symbols);

    for (AbstractEdge<String, Double> edge : mst) {
      String start = edge.getStart();
      String end = edge.getEnd();
      if (start.compareTo(end) > 0) {
        String tmp = start;
        start = end;
        end = tmp;
      }
      System.out.println(start + "," + end + "," + df.format(edge.getLabel()));
    }
  }

}
