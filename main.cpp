#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
using namespace std;

typedef struct Node {
    int localitate;
    unordered_map<Node*, int> destinations;
};

unordered_map<string, int> paths;
void loopNode(Node* node, vector<Node*>& previousPaths, int& lungime) {
    previousPaths.push_back(node);

    if (previousPaths.size() > 1) {
        stringstream ss;
        for (Node* _node : previousPaths) {
            ss << _node->localitate << " ";
        }
        paths[ss.str()] = lungime;
    }

    for (auto&[key, value] : node->destinations) {
        lungime += value;
        loopNode(key, previousPaths, lungime);
        lungime -= value;

        int newLungime = 0;
        vector<Node*> newPrevPaths;
        loopNode(key, newPrevPaths, newLungime);
    }
    previousPaths.pop_back();
}

int main()
{
    ifstream input("date.in");
    ofstream output("date.out");

    int N, localitate, destinatie, distanta;
    input >> N;

    unordered_map<int, Node*> nodes;
    while (true) {
        input >> localitate >> destinatie >> distanta;
        if (input.eof()) break;

        Node* node;
        if (nodes.find(localitate) == nodes.end()) {
            node = new Node;
            node->localitate = localitate;
            nodes[localitate] = node;
        }
        node = nodes[localitate];

        Node* destNode;
        if (nodes.find(destinatie) == nodes.end()) {
            destNode = new Node;
            destNode->localitate = destinatie;
            nodes[destinatie] = destNode;
        }
        destNode = nodes[destinatie];
        node->destinations[destNode] = distanta;
    }

    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        vector<Node*> previousPaths;
        int lungime = 0;
        loopNode(it->second, previousPaths, lungime);
    }

    for (auto &[key, value] : paths) {
        output << key << "\n";
        output << "The sum of the path is " << value << "\n";
    }

    output << "There are a total of " << paths.size() << " roads" << endl;

    return 0;
}
