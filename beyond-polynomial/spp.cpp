#include <iostream>
#include <fstream>
#include <vector>
using namespace std;





/*
    This  program written by "mathura kumar" and supposed to be
    naive implimentation of algorithms which try to find shortest
    path between given source and destination of graph by creating 
    all possible combination of path seqeunces.

    This program will take input from graph.txt file to build graph
    and write output to out_spp.txt.

    e.g input data in file will be in layout given below:-

    V=number of vertex, E=number of edge,W=weight of edges
    vertex number should greater then zero
        
        4 5  This reprsent 4 vertex and 5 edge
        1 2 10 It will be read as node 1 and node 2 has edge with weight 10
        1 4 15
        2 4 30
        3 4 90
        2 3 15
        1 3 20
        9999 end of data marker
    
    output file data layout:-         
    Shortest distance between 2 & 3 is 15
    Path: 2 3 
    Time Complexity- O((E/[E-(V-1)!]*(V-1)!)** Max(V,E))
*/



class Graph {
    int numNodes, numEdges;
    string inputfile_path;
    string outputfile_path;
    vector<vector<pair<int,float>>> adj_list;
    vector<int> shortest_path;
    vector<int> current_path;
    long long shortest_distance = __INT64_MAX__;


    public:
        Graph(string input_file_path, string output_file_path) {
            this->inputfile_path = input_file_path;
            this->outputfile_path = output_file_path;
        }
    bool read_file_build_graph() {
        fstream file(inputfile_path);

        if(file.fail()) {
            cout << "error occured while reading file\n";
            return false;
        }
        file >> numNodes >> numEdges;
        adj_list.clear();
        adj_list.resize(numNodes);
        int u,v,w;

        while(file >> u >> v >> w) {
            if(u == 9999 && v == 9999)
                break;
            if(u < 1 || u > numNodes || v < 1 || v > numNodes) {
                return false;
            }
            adj_list[u-1].push_back({v-1,w});
            adj_list[v-1].push_back({u-1,w});
        }
        return true;
    }

    void explore_best_shortest_path(int source, int destination)
    {
        vector<bool> visited(numNodes,false);
        current_path.clear();
        shortest_path.clear();
        shortest_distance = __INT64_MAX__;

        current_path.push_back(source-1);
        visited[source-1]=true;

        cout<<"exploring various path ,keep waiting,its not magic\n";
        find_shortest_path(source-1,destination-1,0,visited);

        fstream file (outputfile_path,std::ios::out);

        if(file.fail()){
            cout<<"error while writing path in file\n";
        }
        
        cout<<"now i have seen all route let me write for you in file..\n";
        if(shortest_distance == __INT64_MAX__) {
            file<<"No path exist and just waste of compute\n";
            return;
        }

        file <<"Shortest distance between "<<source<<" & "<<destination<<" is "<< shortest_distance << endl;
        file<<"Path: ";
        for(int node: shortest_path){
            file << node+1 << " ";
        }
        cout<<"goodbye and write completed. See your path in file..\n";
        cout<<endl;
    }

private:
    void find_shortest_path(int current_node,int destination,long long current_distance,
                           vector<bool>& visited) {

        if(current_node == destination) {
                if(current_distance < shortest_distance) {
                    shortest_distance = current_distance;
                    shortest_path = current_path;
                }
            return;
        }
        for(auto [next_node, weight] : adj_list[current_node]) {

            if(!visited[next_node]) {
                visited[next_node]=true;
                current_path.push_back(next_node);

                find_shortest_path(next_node,destination,current_distance + weight,
                                  visited);

                current_path.pop_back();

                visited[next_node]=false;
            }
        }
    }

};


int main (){

    cout<<"started file reading to build graph\n";
    Graph g1=Graph("graph.txt","out_spp.txt");

    if (g1.read_file_build_graph()){

        g1.explore_best_shortest_path(2,3);

    }else{
        cout<<"o shit i even not able to read file to build graph and you thought i provide you shortest path\n";

    }
}