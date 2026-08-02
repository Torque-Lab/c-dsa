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

class Graph {
    int numNodes, numEdges;
    string inputfile_path,outputfile_path;
    vector<vector<pair<int,float>>>adj_list;
    vector<vector<pair<int,float>>>mst;
    vector<tuple<int,int,float>> edges;
    double best_mst=0;


    public:
        Graph(string input_file_path,string output_file_path) {
            this->inputfile_path=input_file_path;
            this->outputfile_path=output_file_path;

             }

        void explore_subset_of_graph() {
            vector<vector<pair<int,float>>> current_selection(numNodes);
            best_mst =__INT32_MAX__;

            build_subsets(0, current_selection, 0.0);

            if(!write_MST_to_file()) {
                cout<<"output write failed due some reason";
            };
            cout<<"MST found and written in mst.txt\n";
        }

        bool read_file_build_graph() {
            
            fstream file (inputfile_path);
            file >> numNodes >>numEdges;
            adj_list.resize(numNodes);
            mst.resize(numNodes);
            int u,v;
            float w;

            if (file.fail()) {
                cout<<"error in reading data from file";
                return false;
            }
            while (file >> u>> v>>w) {

                if (u>400 || u-1<0) {
                    return false;
                }

                if(u==9999 || v==999 || w==9999)
                    return false;

                adj_list[u-1].push_back({make_pair(v-1,w)});
                adj_list[v-1].push_back({make_pair(u-1,w)});

                if (u < v)
                edges.push_back({u-1, v-1, w});
            

            }

            return true;
        }

        void display_graph() {
            for (int i=0;i<numNodes;i++){ 
                for (const auto &edge:adj_list[i]) {
                    cout<<"Node: "<<i<<"---"<<edge.first<<",weight: "<<edge.second<<"\n";
                }
            }
        }
    private:
        bool write_MST_to_file() {
            fstream file (outputfile_path, std::ios::out);
            if(file.fail()){
                cout<<"error while opening file to write";
                return false;
            }
            file << numNodes << " "<< numNodes-1 <<"\n";
            for (int i=0;i<numNodes;i++){
                for (const auto &edges:mst[i]) {
                    int next= edges.first;
                    double weight= edges.second;
                    file << i << " " << next << " " << weight<<"\n";
                }
            }
            return true;

        }
        void build_subsets(int index,vector<vector<pair<int,float>>> &current_selection,
                          float current_weight) {
    
             if (index == edges.size()) {
                 if (is_valid_mst(0,-1,current_selection)) {
                        if (best_mst == 0 || current_weight < best_mst) {
                        best_mst = current_weight;
                        mst = current_selection;
                        }
                    }
                return;
                }

            auto [u, v, w] = edges[index];

            current_selection[u].push_back({v, w});
            current_selection[v].push_back({u, w});
            //take
            build_subsets(index + 1,current_selection,current_weight + w);
            
            current_selection[u].pop_back();
            current_selection[v].pop_back();
            //leave
            build_subsets(index + 1, current_selection, current_weight);

        }   

        bool is_valid_mst(int current_node,int current_parent,vector<vector<pair<int,float>>>&current_selection) {

            vector<bool> visited(numNodes, false);
            if (is_dfs_cycle_free(0, -1, current_selection, visited))
                return false;
    
            for (bool v : visited){
                if (!v)
                return false;
            }
            return true;   
        }

        bool is_dfs_cycle_free(int node,int parent,vector<vector<pair<int,float>>>& adj, vector<bool>& visited) {
            visited[node] = true;     

            for (const auto &edge: adj[node]) {
                int next=edge.first;

            if (!visited[next]) {
               if(is_dfs_cycle_free(next, node, adj, visited)){
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

    cout<<"opening graph.txt to build graph so kindlly be patient and wait..\n";

    Graph G1=  Graph("graph.txt","output_mst.txt");

    if(G1.read_file_build_graph()){
        G1.explore_subset_of_graph();

    }else{

    cout<<R"(o shit it seems you are running me in windows os hell,
          i failed to open file and goodbye, next time run me from
          unix system or create file before calling me)";
          cout<<"\n";
    }


    return 0;
}