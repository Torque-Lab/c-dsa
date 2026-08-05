#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>

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

        adj_list.resize(numNodes);

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
            if(build_subsets_of_given_size(0,size,current_cover))
                break;
        }

        write_vertex_cover_to_file();

        cout << "\nMinimum Vertex Cover Size = "
             << best_cover.size() << "\n";

        cout << "Vertices : ";

        for(int v : best_cover)
            cout << v+1 << " ";

        cout << "\n";
    }

private:
    bool build_subsets_of_given_size(int index, int remaining, vector<int> &current_cover) {
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
            if(build_subsets_of_given_size(index+1, remaining-1, current_cover))
                return true;
            current_cover.pop_back();
            return build_subsets_of_given_size(index+1, remaining, current_cover);
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
    cout << "wait a bit buddy opening file to read ..\n";

    Graph G("graph.txt","vertex_cover.txt");

    if(G.read_file_build_graph()) {
        G.display_graph();
        G.explore_subset_of_graph();
    }else{
        cout << "can not complete work and it seem something serious wrong\n";
    }

    return 0;
}