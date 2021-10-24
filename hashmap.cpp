#include <stdbool.h>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <unordered_map>
enum Flags {UNUSED, PROCESSING, USED};

//useful aliases
using string = std::string;
using std::cout;
using std::endl;

template<typename T1, typename T2> class hashmap: public std::unordered_map<T1, T2> {
public:
    bool hasKey(T1 key){
        return this->find(key) != this->end();
    }
};

class Node{
public:
    int incoming;
    hashmap<string, Node*>outgoing;
    bool detached(){
        return outgoing.empty() && incoming == 0; 
    }
};

class Graph{
    hashmap<string, Node> nodes;
public:
    void addEdge(string from, string to){
        nodes[from].outgoing[to] = &nodes[to];
        nodes[to].incoming++;
    }
    
    void removeEdge(string from, string to){
        //handing edge cases
        if(!nodes.hasKey(from) || !nodes.hasKey(to) || !nodes[from].outgoing.hasKey(to))return;
        //normal cases
        nodes[from].outgoing.erase(to);
        nodes[to].incoming--;
        //erase the nodes if detached
        if(nodes[from].detached())nodes.erase(from);
        if(nodes[to].detached())nodes.erase(to);
    }
    
    
    
    bool traverse(string key, Node node, hashmap<string, bool> states){
        if(states.hasKey(key))return states[key];
        states[key] = true;
        for (auto &pair : node.outgoing) {
            string key2 = pair.first;
            Node node2 = pair.second[0];
            if(traverse(key2,node2,states))return true;
        }
        states[key] = false;
        return false;
    }
    
    bool isCyclic(){
        hashmap<string, bool> states;
        //traverse the matrix
        for (auto &pair : nodes) {
            string key = pair.first;
            Node node = pair.second;
            if(states.hasKey(key))continue;
            if(traverse(key,node,states))return true;
        }
        return false;
    }
    
    
    void print(){
        cout << "Printing the nodes (vertices): " << endl;
        for (auto &pair : nodes) {
            Node node = pair.second;
            cout << "name: " << pair.first << endl;
            cout << "incoming: " << node.incoming << endl;
            cout << "connections: {";
            for (auto &pair2 : node.outgoing) {
                cout << " " << pair2.first << " ";
            }
            cout << "}" << endl;
            cout << endl;
        }
        cout << endl;
    }
};

int main(){
    // Create a graph given in the above diagram
    Graph g;
    
    //the setup part
    g.addEdge("a", "d");
    g.addEdge("b", "c");
    g.addEdge("d", "f");
    g.addEdge("a", "x");
    g.addEdge("x", "f");
    //g.addEdge("f", "a"); //this one creates a cycle a->x->f->a. comment out and create a cycle.
    g.removeEdge("a", "w");//removing a non-existing edge should do nothing
    g.print();
    
    //finally, the main part
    if (g.isCyclic())
        cout << "Graph contains cycle";
    else
        cout << "Graph doesn't contain cycle";
    cout <<  endl;
    
    return 0;
}