
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <string>
#include <set>

class Vec2 {
public:
    int x, y;
    Vec2(int x, int y) {
        this->x = x;
        this->y = y;
    }
    Vec2() {
        this->x = 0;
        this->y = 0;
    }
};
class Node {
public:
    Vec2 position;
    int nodeID;
    std::list<Node*> neighbors;
    Node(Vec2 position, int nodeID) {
        this->position = position;
        this->nodeID = nodeID;
    }

};
class Graph {
public:
    std::vector<Node*> nodes;
    std::list<Node*> visited;
    Node DepthFirst(Graph graph, Node* node, std::list<Node*> visited);
    void BreadthFirst(Graph graph, Node* node, std::list<Node*> visited, std::list<Node*> toVisit);
    Graph();
};
Node Graph::DepthFirst(Graph graph, Node* node, std::list<Node*> visited) {
    if (node->nodeID == 155) {
        return *node;
    }
    visited.push_back(node);
    for (Node* n : node->neighbors) {
        std::cout << n->nodeID << " ";
        if (visited.back() != n) {
            DepthFirst(graph, n, visited);
        }

    }
}

void Graph::BreadthFirst(Graph graph, Node* node, std::list<Node*> visited, std::list<Node*> toVisit) {
    toVisit.push_back(node);
    std::list<Node*> newToVisit;
    for (Node* n : toVisit) {

        visited.push_back(toVisit.back());
        toVisit.pop_front();
        for (Node* nb : visited.back()->neighbors) {
            std::cout << nb->nodeID << " ";
            if (nb != visited.back()) {
                newToVisit.push_back(nb);
            }
        }
    }
    BreadthFirst(graph, node, visited, newToVisit);
}

Graph::Graph(){
    std::vector<Node*> nodes;
    std::list<Node*> visited;
    std::list<Node*> neighbors;
}

Graph ReadFile(Graph graph) {
    std::string myText;
    Node* node{};
    int posX = 0;
    int posY = 0;
    int idNode = 0;
    std::ifstream readFile("AssignmentNodes.txt");
    std::cout << "111 = 'o'. 88 = 'X'. 83 = 'S', 71 = 'G'\n" << myText << std::endl;
    while (std::getline(readFile, myText)) {

        //loops through characters in file and checks the value and converts into integers
        for (char ch : myText) {
            //As long as character isn't X, then loop through the lines in file
            if (ch == 'o' && posY < 40 || ch == 'S' && posY < 40 || ch == 'G' && posY < 40) {
                Node* node = new Node({ posX,posY }, idNode);
                graph.nodes.push_back(node);
                idNode++;
                std::cout << int(ch);
                std::cout << "\nPosition X: " << posX << "\nPosition Y: " << posY << "\nNode ID: " << idNode << "\n\n";
            }
            else {
                break;
            }
            ++posX;

        }
        posX = 0;
        posY++;
    }
    readFile.close();
    return graph;
}
void MakeNeighbors(Node* node1, Node* node2) {
    for (auto neighbor : node1->neighbors) {
        if (neighbor == node2) {
            return;
        }
    }
    node1->neighbors.push_back(node2);
    node2->neighbors.push_back(node1);

}
Graph AddNeighbors(Graph graph) {
    
    for (int i = 0; i < graph.nodes.size(); i++) {
        const Vec2 nodePos = graph.nodes[i]->position;
        const Vec2 nodePosUp = {nodePos.x, nodePos.y+1};
        const Vec2 nodePosDown = { nodePos.x, nodePos.y - 1 };
        const Vec2 nodePosLeft = { nodePos.x -1, nodePos.y };
        const Vec2 nodePosRight = { nodePos.x + 1, nodePos.y };

        for (int j = i+1; j < graph.nodes.size(); j++) {
            if (graph.nodes[j]->position.x == nodePosUp.x && graph.nodes[j]->position.y == nodePosUp.y) {
                MakeNeighbors(graph.nodes[i],graph.nodes[j]);
            }
            if (graph.nodes[j]->position.x == nodePosRight.x && graph.nodes[j]->position.y == nodePosRight.y) {
                MakeNeighbors(graph.nodes[i], graph.nodes[j]);
            }
            if (graph.nodes[j]->position.x == nodePosDown.x && graph.nodes[j]->position.y == nodePosDown.y) {
                MakeNeighbors(graph.nodes[i], graph.nodes[j]);
            }
            if (graph.nodes[j]->position.x == nodePosLeft.x && graph.nodes[j]->position.y == nodePosLeft.y) {
                MakeNeighbors(graph.nodes[i], graph.nodes[j]);
            }
        }
    }
    return graph;
}
void DepthFirstTraverse(Graph graph, Node* node, std::set<int> discoveredNodeIDs) {
    discoveredNodeIDs.insert(node->nodeID);

    std::cout << node->nodeID << " ";
    for (auto neighbor : node->neighbors) {

        auto search = discoveredNodeIDs.find(neighbor->nodeID);
        if (search != discoveredNodeIDs.end())
            break;
        else {
            DepthFirstTraverse(graph, neighbor, discoveredNodeIDs);
        }
    }
}

void BreadthFirstTraverse(Graph graph, Node* nodeToFind,std::set<int>visitedIDs,std::list<Node*>nodesToVisit) {
    std::list<Node*>newNodesToVisit;
    for (Node* n : nodesToVisit) {

        if (n->nodeID == nodeToFind->nodeID) {
            std::cout << "Found goal node " << nodeToFind->nodeID;
            return;
        }
        visitedIDs.insert(n->nodeID);
        for (auto neighbor : n->neighbors) {
            auto search = visitedIDs.find(neighbor->nodeID);
            if (search == visitedIDs.end()) {
                newNodesToVisit.push_back(neighbor);
            }
        }
    }
    BreadthFirstTraverse(graph, nodeToFind,visitedIDs, newNodesToVisit);
}
int main()
{
    Graph g{};
    Graph newGraph = ReadFile(g);
    //Check to see that the graph has returned from function correctly
    std::cout << "Graph size: " << newGraph.nodes.size() << std::endl;
    //Add neighbors to nodes
    AddNeighbors(newGraph);
    std::list<Node*> visited;
    std::set<int> visitedIDs;
    std::list<Node*> toVisit;
    std::set<int> discoveredNodes;
    //DepthFirstTraverse(newGraph,newGraph.nodes[12],discoveredNodes);
    //BreadthFirstTraverse(newGraph, newGraph.nodes[12], visitedIDs, toVisit);
    //newGraph.DepthFirst(newGraph,newGraph.nodes[12], visited);
    newGraph.BreadthFirst(newGraph, newGraph.nodes[12], visited, toVisit);
}
