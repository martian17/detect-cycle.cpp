#include <stdbool.h>
#include <stdint.h>
#include <vector>
#include <iostream>
using namespace std;
enum Flags {UNUSED, PROCESSING, USED};

class Graph{
    //adjacency matrix
    vector<vector<bool>> nodes;
    int size;
public:
    Graph(int size){
        this->size = size;
        //set the matrix size and initialize to zero
        nodes.resize(size);
        for(int i = 0; i < size; i++){
            nodes[i].resize(size,false);
        }
    }
    void addEdge(int target, int connection){
        nodes[target][connection] = true;
    }
    void removeEdge(int target, int connection){
        nodes[target][connection] = false;
    }
    
    
    bool traverse(int id, vector<uint8_t> used){
        if(used[id] == USED) false;//dead end, no loop found
        if(used[id] == PROCESSING) return true;//loop found
        //else basically, unclaimed
        used[id] = PROCESSING;
        for(int i = 0; i < size; i++){
            if(!nodes[id][i])continue;//unpopulated
            if(traverse(i,used))return true;
        }
        used[id] = USED;
        return false;
    }
    
    bool isCyclic(){
        vector<uint8_t> used(size,UNUSED);
        //traverse the matrix
        for(int i = 0; i < size; i++){
            //traverse this vertex
            if(used[i] == USED)continue;
            if(traverse(i,used))return true;
        }
        return false;
    }
    
    
    //just an innocent print function
    void print(){
        cout << "Printing the adjacency matrix" << endl;
        cout << "\\to";
        //header
        for(int i = 0; i < nodes[0].size(); i++){
            cout << " " << i << " ";
        }
        cout << endl;
        cout << "from\\" << endl;
        //body
        for(int i = 0; i < nodes.size(); i++){
            cout << i << "  ";
            for(int j = 0; j < nodes[i].size(); j++){
                cout << " " << nodes[i][j] << " ";
            }
            cout << endl;
        }
    }
};


int main(){
    // Create a graph given in the above diagram
    Graph g(5);
    
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 1);
    g.print();
    
    if (g.isCyclic())
        cout << "Graph contains cycle";
    else
        cout << "Graph doesn't contain cycle";
    cout <<  endl;
    
    return 0;
}