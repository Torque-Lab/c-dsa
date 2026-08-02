#include<iostream>
#include<vector>
#include<set>
#include<fstream>
using namespace std;



/*
    This  program written by "mathura kumar" and supposed to be
    naive implimentation of algorithms which try to find best matching 
    of graph by creating all possible combination.

    This program will take input from graph.txt file to build graph and write output
    to out_matching.txt.

    e.g input data in file will be in layout given below:-

    V=number of vertex, E=number of edge,W=weight of edges
    vertex number should greater then zero
        
        4 5  This reprsent 4 vertex and 5 edge
        1 2  It will be read as node 1 and node 2 has edge with weight assumed to be 1 in graph
        1 4
        2 4
        3 4
        2 3
        9999 end of data marker
    
    output file data layout:-         
         2 This reprsent matching size
        1 2 It will be read as node 1 and node 2 as connection
        1 4
        9999 end of data marker
    Time Complexity- O((E/[E-(V-1)!](V-1)!)** Max(V,E))
*/

class Graph{
    int numNodes, numEdges;
    string inputfile_path,outputfile_path;
    vector<pair<int,int>> edges;
    vector<pair<int,int>> best_match;
    vector<pair<int,int>> current_match;

    public:
        Graph(string input_file_path,string output_file_path) {
            this->inputfile_path=input_file_path;
            this->outputfile_path=output_file_path;
             }

        void explore_subset_of_graph() {
            cout<<"wait for a moment matching getting explored..\n";

            build_all_possible_matching_subsets(0);
            if(!write_Matching_to_file()){
                cout<<"error occured while writing output to file";
            };
            cout<< "matching created but cpu hate naive.please read output_matching.txt\n";
        }

        bool read_file_build_graph() {
            
            fstream file (inputfile_path);

            if (file.fail()){
                cout<<"error in reading data from file";
                return false;
            }

            file >>numNodes>>numEdges;
            edges.clear();
            best_match.clear();

            edges.reserve(numNodes);
            best_match.reserve(numNodes/2);
            int u,v,w;

            while (file >> u >> v >> w) {
                if (u == 9999 && v == 9999)
                    break;

                if (u < 1 || u > numNodes || v < 1 || v > numNodes)
                        return false;
                if (u<v)
                    edges.push_back({u-1, v-1});
            }
            return true;
        }
        
    private:
        bool write_Matching_to_file() {
            fstream file (outputfile_path, std::ios::out);
            if(file.fail()){
                cout<<"error while opening file to write";
                return false;
            }
            int matching_size=best_match.size();
            file << matching_size<<"\n";
            for(auto [u,v] : best_match){
                file << u+1 << " " << v+1 << "\n";
            }

            return true;

        }

        void build_all_possible_matching_subsets(int index) {
            if(index == edges.size()) {
                if(is_valid_matching(current_match)) {
                    if(current_match.size() > best_match.size())
                        best_match = current_match;
                     }
                return;
            }

            auto [u,v] = edges[index];

             // Take
            current_match.push_back({u,v});
            build_all_possible_matching_subsets(index+1);
            current_match.pop_back();

            // Leave
            build_all_possible_matching_subsets(index+1);
        }

      bool is_valid_matching(const vector<pair<int,int>>& match) {
         
        vector<bool> used(numNodes,false);

        for(auto [u,v] : match) {
            if(used[u] || used[v])
            return false;

            used[u]=true;
            used[v]=true;
        }

    return true;
    }
};

int main (){
  
    cout<<"opeing file to build graph.... from graph.txt\n";
    Graph G1=  Graph("graph.txt","output_matching.txt");

    if(G1.read_file_build_graph()){
        
        G1.explore_subset_of_graph();
       
    }else{
    
    cout<<"error occured while reading file to build graph and partial graph seem corrupted";
    }

    return 0;
}