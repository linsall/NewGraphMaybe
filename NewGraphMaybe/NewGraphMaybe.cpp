
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <string>

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
    void DepthFirst(Graph graph, Node* node, std::list<Node*> neighbors);
    Graph();
};
void Graph::DepthFirst(Graph graph, Node* node, std::list<Node*> neighbors) {
    visited.push_back(node);
}
Graph::Graph(){
    std::vector<Node*> nodes;
    std::list<Node*> visited;
    std::list<Node*> neighbors;
}

Graph ReadFile(Graph graph) {
    //std::string str;
    //std::ifstream file("AssignmentNodes.txt");
    //while (std::getline(file, str)) {

    //    if (str.empty()) {
    //        break;
    //    }
    //    std::cout << str << std::endl;
    //}
    //file.close();
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
            ch = int(ch);
            //As long as character isn't X  and the y position is smaller than 20 (size of graph in file), then loop through the lines in file
            if (ch == 'o' && posY < 20 || ch == 'S' && posY < 20 || ch == 'G' && posY < 20) {
                Node* node = new Node({ posX,posY }, idNode);
                graph.nodes.push_back(node);
                idNode++;
                std::cout << int(ch) << " ";
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
    //Add Neighbors
}
int main()
{
    Graph g{};
    Graph newGraph = ReadFile(g);
    //Check to see that the graph has returnedfrom function correctly
    std::cout << "Graph size: " << newGraph.nodes.size();
    
}
