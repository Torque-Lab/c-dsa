#include<iostream>
#include<vector>
#include<set>
#include<fstream>
using namespace std;



/*
    This  program written by "mathura kumar" and supposed to be
    naive implimentation of algorithms which try to find minmum spanning tree
    of graph by creating all possible combination of v-1 edges out of total edges.

    This program will take input from graph.txt file to build graph and write output
    to out_mst.txt.

    e.g input data in file will be in layout given below:-

    V=number of vertex, E=number of edge,W=weight of edges
    vertex number should greater then zero
        
        4 5  This reprsent 4 vertex and 5 edge
        1 2 10  It will be read as node 1 and node 2 has edge with weight 10
        1 4 15
        2 4 30
        3 4 90
        2 3 15
        9999 end of data marker
    
    output file data layout:-         
        4 3 This reprsent 4 vertex and 3 edge
        1 2 10  It will be read as node 1 and node 2 has edge with weight 10
        1 4 15
        2 3 15
        9999 end of data marker
    Time Complexity- O((Total possible tree we can make from E edge using V-1 Edge or E/[E-(V-1)!](V-1)!)** Max(V,E))
*/

class Graph{
    int numNodes, numEdges;
    string inputfile_path,outputfile_path;
    vector<vector<pair<int,float>>>adj_list;
    vector<vector<pair<int,float>>>mst;
    vector<tuple<int,int,float>> edges;
    double best_mst=0;


    public:
        Graph(string input_file_path,string output_file_path){
            this->inputfile_path=input_file_path;
            this->outputfile_path=output_file_path;

             }

        void explore_subset_of_graph(){
            vector<vector<pair<int,float>>> currentSelection(numNodes);
            best_mst =__INT32_MAX__;

            buildSubsets(0, currentSelection, 0.0);
            write_MST_to_file();
        }

        bool read_file_build_graph(){
            
            fstream file (inputfile_path);
            file >> numNodes >>numEdges;
            adj_list.resize(numNodes);
            mst.resize(numNodes);
            int u,v;
            float w;

            if (file.fail()){
                cout<<"error in reading data from file";
                return false;
            }
            do{
                if (file.eof()){
                    break;
                }

                file >> u >>v >> w;
                if (u>400 || u-1<0) {
                    return false;
                }
                adj_list[u-1].push_back({make_pair(v-1,w)});
                adj_list[v-1].push_back({make_pair(u-1,w)});

                if (u < v)
                edges.push_back({u-1, v-1, w});
            

            }while  (
                u !=999 || v!=999 || w !=9.999 
            );

            return true;
        }

        void display_graph(){
            for (int i=0;i<numNodes;i++){
                for (const auto &edge:adj_list[i]){
                    cout<<"Node: "<<i<<"---"<<edge.first<<",weight: "<<edge.second<<"\n";
                }
            }
        }
    private:
        bool write_MST_to_file(){
            fstream file (outputfile_path, std::ios::out);
            if(file.fail()){
                cout<<"error while opening file to write";
                return false;
            }
            file << numNodes << " "<< numNodes-1 <<"\n";
            for (int i=0;i<numNodes;i++){
                for (const auto &edges:mst[i]){
                    int next= edges.first;
                    double weight= edges.second;
                    file << i << " " << next << " " << weight<<"\n";
                }
            }
            return true;

        }
        void buildSubsets(int index,vector<vector<pair<int,float>>> &currentSelection,
                          float currentWeight){
    
             if (index == edges.size()) {
                 if (isValidMst(0,-1,currentSelection)) {
                        if (best_mst == 0 || currentWeight < best_mst) {
                        best_mst = currentWeight;
                        mst = currentSelection;
                        }
                    }
                return;
                }

            auto [u, v, w] = edges[index];

            currentSelection[u].push_back({v, w});
            currentSelection[v].push_back({u, w});
            //take
            buildSubsets(index + 1,currentSelection,currentWeight + w);
            
            currentSelection[u].pop_back();
            currentSelection[v].pop_back();
            //leave
            buildSubsets(index + 1, currentSelection, currentWeight);

        }   

        bool isValidMst(int current_node,int current_parent,vector<vector<pair<int,float>>>&current_selection){

            vector<bool> visited(numNodes, false);
            if (isDFSCycleFree(0, -1, current_selection, visited))
                return false;
    
            for (bool v : visited){
                if (!v)
                return false;
            }
            return true;   
        }

        bool isDFSCycleFree(int node,int parent,vector<vector<pair<int,float>>>& adj, vector<bool>& visited) {
            visited[node] = true;     

            for (const auto &edge: adj[node]) {
                int next=edge.first;

            if (!visited[next]) {
               if(isDFSCycleFree(next, node, adj, visited)){
                return true;
               };

            }else if (next != parent) {
                return true;
        }
    }
    return false;
}

};

int main (){

    Graph G1=  Graph("graph.txt","output_mst.txt");
    G1.read_file_build_graph();
    G1.explore_subset_of_graph();

    return 0;
}