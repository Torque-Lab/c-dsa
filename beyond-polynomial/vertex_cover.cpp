#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <random>

using namespace std;

/*
Naive algo for vertex cover
*/

class Graph {

    int numNodes, numEdges;
    string inputfile_path, outputfile_path;

    vector<vector<pair<int,float>>> adj_list;
    vector<tuple<int,int,float>> edges;
    vector<int> best_cover;

public:

    Graph(string input_file_path, string output_file_path) {
        inputfile_path = input_file_path;
        outputfile_path = output_file_path;
    }

    bool read_file_build_graph() {
        fstream file(inputfile_path);

        if(file.fail()) {
            cout << "failed to open input file\n";
            return false;
        }
        file >> numNodes >> numEdges;

        adj_list.clear();
        adj_list.resize(numNodes);

        edges.clear();
        edges.reserve(numEdges);

        int u,v;
        float w;

        while(file >> u >> v >> w) {
            u--;
            v--;
            adj_list[u].push_back({v,w});
            adj_list[v].push_back({u,w});

            edges.push_back({u,v,w});
        }

        return true;
    }

    void display_graph() {
        cout << "\nAdjacency List of given graph\n\n";

        for(int i=0;i<numNodes;i++)
        {
            cout << i+1 << " : ";
            for(auto edge : adj_list[i])
                cout << "(" << edge.first+1 << "," << edge.second << ") ";

            cout << "\n";
        }
    }

    void explore_subset_of_graph() {
        vector<int> current_cover;

        best_cover.clear();

        for(int size=1; size<=numNodes; size++) {
            if(build_subsets_of_given_size_and_find_VC(0,size,current_cover))
                break;
        }

        if(write_vertex_cover_to_file()){
            cout<<"\nvertext cover written in file\n";
        }else{
            cout<<"failed to write vertex cover in file\n";
        }

        cout << "\nMinimum Vertex Cover Size = "
             << best_cover.size() << "\n";

        cout << "Vertices : ";

        for(int v : best_cover)
            cout << v+1 << " ";

        cout << "\n";
    }

    bool random_graph_generator(int numNodes,int numEdges,string input_file_path){

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> distrib(1, numNodes);

            fstream file (input_file_path,ios::out);

            if(file.fail()){
                cout<<"fail to open file to write graph generated with probability";
                return false;
                 };

            file << numNodes << " " << numEdges <<"\n";
            numNodes=numNodes;
            numEdges=numEdges;

            for (int i=1;i<=numEdges;i++){
                int u= distrib(gen);
                int v=distrib(gen);
                int w=distrib(gen);
                file <<u<<" "<< v<< " "<<w<< "\n";

            }
        
        return true;

     }
    
private:
    bool build_subsets_of_given_size_and_find_VC(int index, int remaining, vector<int> &current_cover) {
            if(remaining==0) {
                if(is_valid_cover(current_cover)) {
                    best_cover=current_cover;
                    return true;
                }
            return false;
        }

            if(index==numNodes)
                return false;

            if(numNodes-index<remaining)
                return false;
            current_cover.push_back(index);
            if(build_subsets_of_given_size_and_find_VC(index+1, remaining-1, current_cover))
                return true;
            current_cover.pop_back();
            return build_subsets_of_given_size_and_find_VC(index+1, remaining, current_cover);
    }
    bool is_valid_cover(vector<int> &cover) {
        vector<bool> chosen(numNodes,false);

        for(int v : cover)
            chosen[v]=true;

        for(auto edge : edges) {
            auto [u,v,w] = edge;

            if(!chosen[u] && !chosen[v])
                return false;
        }

        return true;
    }

    bool write_vertex_cover_to_file() {
        fstream file(outputfile_path,ios::out);

        if(file.fail()) {
            cout<<"Cannot open output file\n";
            return false;
        }

        file << best_cover.size() << "\n";

        for(int v : best_cover)
            file << v+1 << " ";

        file << "\n";

        return true;
    }
};



int main()
{
    cout<<"Enter processing mode 1 for manual graph and 2 for random graph\n";

    int mode;
    cin>>mode;

    if (mode==1){
            Graph G("graph.txt","vertex_cover.txt");
                if(G.read_file_build_graph()) {
                G.display_graph();
                G.explore_subset_of_graph();

                }else{
                cout << "can not complete work and it seem something serious wrong\n";
                }

    }
    else if(mode ==2){
           Graph G("seed_graph.txt", "vertex_cover.txt");
            cout<<"Enter required Vertex:\n";
            int numNodes;
            cin>>numNodes;
            cout<<"Enter required numder of edges:\n";
            int numEdges;
            cin>>numEdges;

            if (numNodes<0 || numEdges<0){
                cout<<"input negative not allowed so aborting any further processing";
                return 1;
            }
            if (numEdges > (numNodes*(numNodes-1))/2){
                cout<<"Total edge exceeding max possible value\n";
                return 1;
            }

            if(G.random_graph_generator(numNodes,numEdges,"seed_graph.txt")){
                cout<<"start"; 
                        if(G.read_file_build_graph()) {
                            G.display_graph();
                            G.explore_subset_of_graph();
                        }else {
                        cout<<"graph read failed aborting work\n";
                        }

                }else{
                cout << "failing to write random see graph in file\n";
                }

    }else {
        cout<<"you selected wrong mode and so work getting aborted goodbye\n";
    }

    return 0;
}