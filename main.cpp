#include "graph.h"

int main() {
    Graph g;

    // Sample City Nodes
    g.addNode("A", 0, 0);
    g.addNode("B", 2, 1);
    g.addNode("C", 4, 3);
    g.addNode("D", 6, 1);
    g.addNode("E", 7, 4);

    // Sample Edges
    g.addEdge("A", "B", 2);
    g.addEdge("B", "C", 3);
    g.addEdge("A", "C", 5);
    g.addEdge("C", "D", 2);
    g.addEdge("D", "E", 3);
    g.addEdge("B", "E", 10);

    int choice;
    string src, dest;

    cout << "===== Dynamic Route Optimization =====\n";
    cout << "Enter Source City: ";
    cin >> src;
    cout << "Enter Destination City: ";
    cin >> dest;

    cout << "\n1. Dijkstra's Algorithm\n2. A* Search\nChoice: ";
    cin >> choice;

    switch (choice) {
        case 1: g.dijkstra(src, dest); break;
        case 2: g.aStar(src, dest); break;
        default: cout << "Invalid choice!\n";
    }

    return 0;
}
