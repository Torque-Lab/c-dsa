#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <fstream>
#include <random>
#include <chrono>
#include <sys/wait.h>
#include <iomanip>

using namespace std;

/*
Naive algo for vertex cover
*/

class Graph
{

    int numNodes, numEdges;
    string inputfile_path, outputfile_path;

    vector<vector<pair<int, float>>> adj_list;
    vector<tuple<int, int, float>> edges;
    vector<int> best_cover;
    vector<int>approx_cover;

public:
    Graph(string input_file_path, string output_file_path)
    {
        inputfile_path = input_file_path;
        outputfile_path = output_file_path;
    }

    bool read_file_build_graph()
    {
        fstream file(inputfile_path);

        if (file.fail())
        {
            cout << "failed to open input file\n";
            return false;
        }
        file >> numNodes >> numEdges;

        adj_list.clear();
        adj_list.resize(numNodes);

        edges.clear();
        edges.reserve(numEdges);

        int u, v;
        float w;

        while (file >> u >> v >> w)
        {
            u--;
            v--;
            adj_list[u].push_back({v, w});
            adj_list[v].push_back({u, w});

            edges.push_back({u, v, w});
        }

        return true;
    }

    void display_graph()
    {
        cout << "\nAdjacency List of given graph\n\n";

        for (int i = 0; i < numNodes; i++)
        {
            cout << i + 1 << " : ";
            for (auto edge : adj_list[i])
                cout << "(" << edge.first + 1 << "," << edge.second << ") ";

            cout << "\n";
        }
    }


    bool do_two_factor_vc_approx_and_verify_vc(){
        vector<int>matched(numNodes,false);

        for (auto &[u,v,w] : edges){
            if (!matched[u] && !matched[v]) {
                matched[u] = true;
                matched[v] = true;
                approx_cover.push_back(u);
                approx_cover.push_back(v);
             }
        }
        if(is_valid_cover(approx_cover)){
            write_two_f_vertex_cover_to_file();
            return true;
        }
        return false;
    }

    void explore_subset_of_graph()
    {
        vector<int> current_cover;

        best_cover.clear();

        for (int size = 1; size <= numNodes; size++)
        {
            if (build_subsets_of_given_size_and_find_VC(0, size, current_cover))
                break;
        }

        if (write_vertex_cover_to_file())
        {
            cout << "\nvertext cover written in file\n";
        }
        else
        {
            cout << "failed to write vertex cover in file\n";
        }

        cout << "\nMinimum Vertex Cover Size = "
             << best_cover.size() << "\n";

        cout << "Vertices : ";

        for (int v : best_cover)
            cout << v + 1 << " ";

        cout << "\n";
    }
    int get_vertex_cover_size()
    {

        return best_cover.size();
    }

    int get_approx_vc_cover_size(){
        return approx_cover.size();
    }


    bool random_graph_generator(int numNodes, int numEdges, string input_file_path)
    {

        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<int> nodeDist(1, numNodes);
        uniform_int_distribution<int> weightDist(1, numNodes);

        set<pair<int, int>> edges;
        vector<tuple<int, int, int>> graphEdges;

        for (int v = 2; v <= numNodes; v++)
        {

            uniform_int_distribution<int> parentDist(1, v - 1);
            int u = parentDist(gen);
            int a = min(u, v);
            int b = max(u, v);
            int w = weightDist(gen);
            edges.insert({a, b});
            graphEdges.push_back({u, v, w});
        }

        while ((int)graphEdges.size() < numEdges)
        {

            int u = nodeDist(gen);
            int v = nodeDist(gen);

            // No self loop
            if (u == v)
                continue;

            int a = min(u, v);
            int b = max(u, v);

            if (edges.count({a, b}))
                continue;

            int w = weightDist(gen);
            edges.insert({a, b});
            graphEdges.push_back({u, v, w});
        }
        fstream file(input_file_path, ios::out);
        if (file.fail())
        {
            cout << "Failed to open file to write generated graph.\n";
            return false;
        }
        file << numNodes << " " << numEdges << "\n";
        for (const auto &[u, v, w] : graphEdges)
        {
            file << u << " " << v << " " << w << "\n";
        }

        file.close();

        return true;
    }
    void write_final_result(const string &filename,
                            int nodes, int edges,
                            int bruteVC, double bruteTime,
                            int approxVC, double approxTime,
                            double approxFactor)
    {
        ofstream file(filename, ios::app);

        file << left
             << setw(10) << nodes
             << setw(10) << edges
             << setw(22) << bruteVC
             << setw(24) << fixed << setprecision(5) << bruteTime
             << setw(22) << approxVC
             << setw(18) << approxTime
             << setw(16) << approxFactor
             << '\n';
    }

private:
    bool build_subsets_of_given_size_and_find_VC(int index, int remaining, vector<int> &current_cover)
    {
        if (remaining == 0)
        {
            if (is_valid_cover(current_cover))
            {
                best_cover = current_cover;
                return true;
            }
            return false;
        }

        if (index == numNodes)
            return false;

        if (numNodes - index < remaining)
            return false;
        current_cover.push_back(index);
        if (build_subsets_of_given_size_and_find_VC(index + 1, remaining - 1, current_cover))
            return true;
        current_cover.pop_back();
        return build_subsets_of_given_size_and_find_VC(index + 1, remaining, current_cover);
    }
    bool is_valid_cover(vector<int> &cover)
    {
        vector<bool> chosen(numNodes, false);

        for (int v : cover)
            chosen[v] = true;

        for (auto edge : edges)
        {
            auto [u, v, w] = edge;

            if (!chosen[u] && !chosen[v])
                return false;
        }

        return true;
    }

    bool write_vertex_cover_to_file()
    {
        fstream file(outputfile_path, ios::out);

        if (file.fail())
        {
            cout << "Cannot open output file\n";
            return false;
        }

        file << best_cover.size() << "\n";

        for (int v : best_cover)
            file << v + 1 << " ";

        file << "\n";
        file.close();

        return true;
    }

    bool write_two_f_vertex_cover_to_file()
    {
        fstream file(outputfile_path, ios::out);

        if (file.fail())
        {
            cout << "Cannot open output file\n";
            return false;
        }

        file << approx_cover.size() << "\n";

        for (int v : approx_cover)
            file << v + 1 << " ";

        file << "\n";
        file.close();

        return true;
    }

};

int main()
{

    bool autonomous_mode = true;
    bool seed_file_read=true;

    if (!autonomous_mode)
    {
        cout << "Enter processing mode 1 for manual graph and 2 for random graph\n";

        int mode;
        cin >> mode;
        auto start = chrono::high_resolution_clock::now();
        if (mode == 1)
        {
            Graph G("graph.txt", "vertex_cover.txt");
            if (G.read_file_build_graph())
            {
                G.display_graph();
                G.explore_subset_of_graph();
            }
            else
            {
                cout << "can not complete work and it seem something serious wrong\n";
            }
        }
        else if (mode == 2)
        {
            cout << "Enter required Vertex:\n";
            int numNodes;
            cin >> numNodes;
            cout << "Enter required numder of edges:\n";
            int numEdges;
            cin >> numEdges;

            auto start = chrono::high_resolution_clock::now();

            if (numNodes < 0 || numEdges < 0)
            {
                cout << "input negative not allowed so aborting any further processing";
                return 1;
            }
            if (numEdges > (numNodes * (numNodes - 1)) / 2)
            {
                cout << "Total edge exceeding max possible value\n";
                return 1;
            }
            if (numEdges < numNodes - 1)
            {
                cout << "with" << numEdges << "edge not possible to create connected graph\n";
                return 1;
            }

            string input_file = "seed_graph" + to_string(numNodes) + to_string(numEdges) + ".txt";
            string output_file = "vertex_cover" + to_string(numNodes) + to_string(numEdges) + ".txt";
            Graph G(input_file, output_file);

            if (G.random_graph_generator(numNodes, numEdges, input_file))
            {
                if (G.read_file_build_graph())
                {
                    G.display_graph();
                    G.explore_subset_of_graph();
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double, milli> time_taken = end - start;
                    cout << "\nTotal time taken for " << numNodes << " nodes"
                         << " and " << numEdges << " edges" << " are:"
                         << time_taken.count() << " milli second\n";
                    cout << "\nwe have find vertex cover successfully"
                         << "so if you want to visualize graph"
                         << "please press 5 else 7 to end program: ";

                    int visual_selected = 0;
                    cin >> visual_selected;
                    if (visual_selected == 5)
                    {
                        pid_t pid = fork();
                        if (pid == 0)
                        {
                            string node = to_string(numNodes);
                            string edge = to_string(numEdges);
                            string arg = node + edge;

                            execlp(
                                "python3",
                                "python3",
                                "visualize.py",
                                arg.c_str(),
                                (char *)NULL);
                        }
                        else
                        {

                            int status;
                            waitpid(pid, &status, 0);
                        }
                    }
                    else
                    {
                        cout << "\nyou have selected unsupported mode so visual formation cancelled";
                    }
                }
                else
                {
                    cout << "graph read failed aborting work\n";
                }
            }
            else
            {
                cout << "failing to write random seed graph in file\n";
            }
        }
        else
        {
            cout << "you selected wrong mode and so work getting aborted goodbye\n";
        }
    }
    else
    {
        int numNodes = 10;
        ofstream file("vertex_cover_table.txt");

        file << "            VERTEX COVER RESULTS FOR COMPARISON BETWEEN NAIVE\n"
             << "            BRUTE FORCE ALGORITHAMS AND APPROXIMATION ALGORITHAMS\n"
             << "        \n\n";
        file << left
             << setw(10) << "Node"
             << setw(10) << "Edge"
             << setw(22) << "Brute Force VC Size"
             << setw(24) << "Brute Force Time"
             << setw(16) << "Approx VC Size"
             << setw(18) << "Approx Time"
             << setw(16) << "Approx Factor"
             << '\n';

        file << left
             << setw(10) << ""
             << setw(10) << ""
             << setw(22) << ""
             << setw(24) << "(in milli second)"
             << setw(16) << ""
             << setw(18) << "(in milli second)"
             << setw(16) << ""
             << '\n';

        file << string(108, '-') << '\n';

        file.close();
        for (int numEdges = 10; numEdges < 50;)
        {
            auto start = chrono::high_resolution_clock::now();
            string input_file = "seed_graph" + to_string(numNodes) + to_string(numEdges) + ".txt";
            string output_file = "vertex_cover" + to_string(numNodes) + to_string(numEdges) + ".txt";
            Graph G(input_file, output_file);

                if (G.read_file_build_graph())
                {
                    G.display_graph();
                    G.explore_subset_of_graph();
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double, milli> time_taken = end - start;
                    double brute_force_time_taken = time_taken.count();
                    cout << "\nTotal time taken for " << numNodes << " nodes"
                         << " and " << numEdges << " edges" << " are:"
                         << brute_force_time_taken << " milli second\n";

                    int brute_force_vc_size = G.get_vertex_cover_size();
                    chrono::duration<double, milli> two_f_time_taken;
                    int approx_two_f_vc=0;

                    if(seed_file_read){
                            cout<<"\ndoing approximation vc\n";
                            auto start_two_f= chrono::high_resolution_clock::now();
                            string input_file = "seed_graph" + to_string(numNodes) + to_string(numEdges) + ".txt";
                            string output_file = "approx_vertex_cover" + to_string(numNodes) + to_string(numEdges) + ".txt";
                            Graph G(input_file, output_file);

                            G.read_file_build_graph();
                            G.do_two_factor_vc_approx_and_verify_vc();
                            auto end_two_f= chrono::high_resolution_clock::now();
                            two_f_time_taken=end_two_f-start_two_f;
                            approx_two_f_vc=G.get_approx_vc_cover_size();
                            cout << "\nTotal time taken for " << numNodes << " nodes"
                            << " and " << numEdges << " edges" << " in approx approach are:"
                            << two_f_time_taken.count() << " milli second\n";


                            pid_t pid = fork();
                            if (pid == 0)
                            {
                            string node = to_string(numNodes);
                            string edge = to_string(numEdges);
                            string arg = node + edge;
                            
                            cout <<"child is doing work";
                            execlp(
                                "python3",
                                "python3",
                                "visualize_two_f.py",
                                arg.c_str(),
                                (char *)NULL
                            );
                            exit(0);
                           
                            }
                             else
                            {

                            int status;
                            waitpid(pid, &status, 0);
                        }

                    }
                    double approx_factor= (double) approx_two_f_vc/brute_force_vc_size;
                    double approx_two_f_time= two_f_time_taken.count();
                    G.write_final_result("vertex_cover_table.txt",
                                         numNodes, numEdges, brute_force_vc_size, brute_force_time_taken,
                                         approx_two_f_vc,approx_two_f_time, approx_factor);

                    pid_t pid = fork();
                    if (pid == 0)
                    {
                        string node = to_string(numNodes);
                        string edge = to_string(numEdges);
                        string arg = node + edge;

                        execlp(
                            "python3",
                            "python3",
                            "visualize.py",
                            arg.c_str(),
                            (char *)NULL);
                    }
                    else
                    {

                        int status;
                        waitpid(pid, &status, 0);
                    }
                }
                else
                {
                    cout << "graph file read failed";
                }
            
            numEdges = numEdges + 5;

            }
        
    }

    return 0;
}