#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <tuple>
#include <fstream>
#include <chrono>
#include <sys/wait.h>
#include <iomanip>

using namespace std;

/*
Naive algo for vertex cover
*/

class Graph {

	int numNodes, numEdges;
	string inputfile_path, outputfile_path;	
	vector<vector<pair<int, float>>> adj_list;
	vector<tuple<int, int, float>> edges;
	vector<int> greedy_cover;
	vector<double>lp_approx_cover;
	double lp_optimal_value;
	int lp_vc_size;

public:
	Graph(string input_file_path, string output_file_path) {
		inputfile_path = input_file_path;
		outputfile_path = output_file_path;
		}

	bool read_file_build_graph() {

		fstream file(inputfile_path);
		if (file.fail()) {
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
		while (file >> u >> v >> w) {
			u--;
			v--;
			adj_list[u].push_back({v, w});
			adj_list[v].push_back({u, w});
			edges.push_back({u, v, w});
		}

		return true;
	}

	void display_graph() {
		cout << "adjacency List of given graph\n";

		for (int i = 0; i < numNodes; i++) {
			cout << i + 1 << " : ";
			for (auto edge : adj_list[i]) {
				cout << "(" << edge.first + 1 << "," << edge.second << ") ";
			}
			cout << "\n";
		}
	}

	bool prepare_contraint_model_for_LP(int numNodes,int numEdges){

		string contraint_file="model" +to_string(numNodes) +to_string(numEdges)+".mod";
		string solution_file="lp_solution" +to_string(numNodes) +to_string(numEdges)+".txt";
			fstream file(contraint_file,ios::out);
			if (file.fail()){
				return false;
			}

			for (int i=1; i<=numNodes;i++){
				string var ="x" +to_string(i);
				file <<"var "<<var << ">=0;"<<"\n";
			}
			file <<"minimize total_sum:";

			for (int i=1; i<=numNodes;i++){
				string var ="x"+to_string(i);
				file <<var;
				if (i < numNodes){
					file<<"+";
				}
			}
			file << ";\n";
			for (auto &edge:edges){
				auto [first_endpoint,second_endpoint,weight] =edge;
				string var1= "x"+to_string(first_endpoint+1);
				string var2= "x"+to_string(second_endpoint+1);
				file << "subject to edge"<<first_endpoint+1<<"_"<<second_endpoint+1<<" : "<<var1<<"+"<<var2<<">= 1;\n";

			}
			file <<"solve;\n";

			file <<"printf \"\\n                          \\n\" > \""<<solution_file<<"\";\n";
			file <<"printf \"  Choosen Nodes As Per LP \\n\" >> \""<<solution_file<<"\";\n";
			file <<"printf \"                          \\n\" >> \""<<solution_file<<"\";\n";

			file <<"printf \"Minimum Nodes: %g\\n\\n\", total_sum >> \""<<solution_file<<"\";\n";

			file <<"printf \"Selected Variable Choices:\\n\" >> \""<<solution_file<<"\";\n";

			for (int i=1;i<=numNodes;i++){
			string var ="x" +to_string(i);
			file <<"printf \""<<var<<" = %g\\n\", "<<var
				<<" >> \""<<solution_file<<"\";\n";
			}

			file <<"\nprintf \"\\nFOR_PROGRAM\\n\" >> \""<<solution_file<<"\";\n";
			file <<"printf \"%g\\n \", total_sum >> \""<<solution_file<<"\";\n";

			for (int i=1;i<=numNodes;i++){
				string var ="x" +to_string(i);
				file <<"printf \"%g \", "<<var
				<<" >> \""<<solution_file<<"\";\n";
			}

			file <<"printf \"\\n\\n\" >> \""<<solution_file<<"\";\n";

			file <<"end;\n";

			file.close();
			return true;

		
	}
	bool read_lp_solution_and_verify(int numNodes, int numEdges){

		double lp_optimal;
		string solution_file="lp_solution"+to_string(numNodes)+to_string(numEdges)+".txt";
		string approx_cover_file="approx_vertex_cover"+to_string(numNodes)+to_string(numEdges)+".txt";
		ifstream solution_file_fd(solution_file,ios::in);

		if (solution_file_fd.fail()){
			return false;
		}

		string line;
		bool found_marker=false;

		while (getline(solution_file_fd,line)){
		if (line=="FOR_PROGRAM"){
			found_marker=true;
			break;
			}
		}
		if (!(solution_file_fd >> lp_optimal)){
			solution_file_fd.close();
			return false;
		}
		lp_approx_cover.resize(numNodes);
		lp_optimal_value=lp_optimal;
		for (int i=1;i<=numNodes;i++){
			double value;

			if (!(solution_file_fd >> value)){
				solution_file_fd.close();
				return false;
		}
			lp_approx_cover[i-1]=value;
		}
		solution_file_fd.close();
		if (is_valid_LP_found(lp_approx_cover)){
			cout<<"valid LP founded";
			ofstream approx_fd (approx_cover_file,ios::out);
			approx_fd <<lp_vc_size<<"\n";
			for (int i=0;i<numNodes;i++){
				if (lp_approx_cover[i]>=0.5){
					approx_fd<<i+1 << " ";
				}
			}
			return true;
		}else{
			cout<< "fractional LP not exist";
			return false;
		}
		
		return false;
	}

	bool verify_vc_approx__done_by_LP_and_write_to_file(int numNodes,int numEdges){

		if (read_lp_solution_and_verify(numNodes, numEdges)){
			return true;
		}
		return false;
	}

	

	int get_greedy_cover_size() {
		return greedy_cover.size();
	}

	int get_approx_vc_cover_size(){
		return lp_vc_size;
	}
	double get_lp_optimal_value(){
		return lp_optimal_value;
	}



	void write_final_result(const string &filename, int nodes, int edges, int greedyVC, double greedyTime,double lp_optimal,int lp_approxVC, double lp_approxTime, double lp_approxFactor) {

		ofstream file(filename, ios::app);

		file << left
		<< setw(10) << nodes
		<< setw(10) << edges
		<< setw(22) << greedyVC
		<< setw(24) << fixed << setprecision(5) << greedyTime
		<<setw(24) << lp_optimal
		<< setw(24) << lp_approxVC
		<< setw(24) << lp_approxTime
		<< setw(24) << lp_approxFactor
		<< '\n';
	}




    	bool do_greedy_vc_approx_and_verify_vc(int numNodes){
       		 
		vector<int>matched(numNodes,false);

       	 	for (auto &[u,v,w] : edges){
            	if (!matched[u] && !matched[v]) {
               	 	matched[u] = true;
                	matched[v] = true;
                	greedy_cover.push_back(u);
                	greedy_cover.push_back(v);
             }
        	}
        	if(is_valid_cover(greedy_cover)){
           	 write_two_f_vertex_cover_to_file();
           	 return true;
        	}
        return false;
    }
private:
	bool is_valid_cover(vector<int> &cover) {
		vector<bool> chosen(numNodes, false);

		for (int v : cover)
			chosen[v] = true;

		for (auto edge : edges) {
			auto [u, v, w] = edge;

		if (!chosen[u] && !chosen[v])
			return false;
	}

	return true;
	}

	bool is_valid_LP_found(vector<double> &cover) {
		vector<bool> chosen(numNodes, false);
			lp_vc_size=0;
		for (int i=0;i <cover.size();i++){
			if (cover[i]>=0.5){
				lp_vc_size+=1;
				chosen[i]=true;
			}
		}
		for (auto edge : edges) {

			auto [u, v, w] = edge;
			if (!chosen[u] && !chosen[v])
				return false;
		}
		return true;
	}
	
	bool write_two_f_vertex_cover_to_file() {

        	fstream file(outputfile_path, ios::out);

        	if (file.fail()) {
            	cout << "Cannot open output file\n";
            	return false;
        	}

        	file << greedy_cover.size() << "\n";

        	for (int v : greedy_cover){
           		 file << v + 1 << " ";
		}
        	file << "\n";
        	file.close();
        	return true;
   	 }
	
};

	int main() {

	int MAX_EDGE=200;
	int EDGE_INTERVAL=20;
	int numNodes = 20;
	int sig_break=false;
	bool repeat_sig=true;

REPEAT_JUMP:
	string final_result_file = "vertex_cover_table" + to_string(numNodes) + to_string(MAX_EDGE) + ".txt";
	ofstream file(final_result_file);

	file << "            VERTEX COVER RESULTS FOR COMPARISON BETWEEN      \n"
	     << "            Greedy ALGORITHAMS AND LP_APPROXIMATION ALGORITHAMS\n"
	     << "        \n\n";
	file << left
	     << setw(10) << "Node"
	     << setw(10) << "Edge"
	     << setw(22) << "Greedy VC Size"
	     << setw(24) << "Greedy Time"
	     <<setw(24)  << "LP_Optimal_value"
	     << setw(24) << "LP_Approx VC Size"
	     << setw(24) << "LP_Approx Time"
	     << setw(24) << "LP_Approx Factor"
	     << '\n';	
	file << left
	     << setw(10) << ""
	     << setw(10) << ""
	     << setw(22) << ""
	     << setw(24) << "(in milli second)"
	     <<setw (24) << ""
	     << setw(24) << ""
	     << setw(24) << "(in milli second)"
	     << setw(24) << ""
	     << '\n';

	file << string(108, '-') << '\n';

	file.close();

	for (int numEdges = 20; numEdges <MAX_EDGE;) {

		auto start = chrono::high_resolution_clock::now();
		string input_file = "seed_graph" + to_string(numNodes) + to_string(numEdges) + ".txt";
		string output_file = "vertex_cover" + to_string(numNodes) + to_string(numEdges) + ".txt";
		Graph G_greedy(input_file, output_file);
		if (numEdges > (numNodes*(numNodes-1))/2){
			break;
		}

		if (G_greedy.read_file_build_graph()) {
			G_greedy.display_graph();
			G_greedy.do_greedy_vc_approx_and_verify_vc(numNodes);
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double, milli> time_taken = end - start;
			double greedy_time_taken = time_taken.count();
			cout << "\nTotal time taken for " << numNodes << " nodes"
			<< " and " << numEdges << " edges" << " are:"
			<< greedy_time_taken << " milli second\n";

			int greedy_vc_size = G_greedy.get_greedy_cover_size();
			chrono::duration<double, milli> lp_time_taken;
			int lp_vc_size=0;


			cout<<"doing approximation vc\n";
			auto start_lp_f= chrono::high_resolution_clock::now();
			string input_file = "seed_graph" + to_string(numNodes) + to_string(numEdges) + ".txt";
			string output_file = "approx_vertex_cover" + to_string(numNodes) + to_string(numEdges) + ".txt";
			Graph G_LP(input_file, output_file);
			if (!G_LP.read_file_build_graph()){
				cout<< "Graph read failed";
				break;
			}
			if (!G_LP.prepare_contraint_model_for_LP(numNodes, numEdges)){
				cout <<"prepare error";
				break;
			}
			string model_path="model"+to_string(numNodes)+to_string(numEdges)+".mod";

			pid_t pid1 =fork();
			if (pid1==0){
				execlp("glpsol", "glpsol", "-m",model_path.c_str(),(char *)NULL);
				exit(0);
			} else{
				int status;
				waitpid(pid1, &status, 0);
			}
			if (!G_LP.read_lp_solution_and_verify(numNodes, numEdges)){
				cout<<"lp_solution read error";
				break;
			}
			auto end_lp_f= chrono::high_resolution_clock::now();

			lp_time_taken=end_lp_f-start_lp_f;
			lp_vc_size=G_LP.get_approx_vc_cover_size();
			cout << "Total time taken for " << numNodes << " nodes"
			<< " and " << numEdges << " edges" << " in approx approach are:"
			<< lp_time_taken.count() << " milli second\n";


			pid_t pid2 = fork();
			if (pid2 == 0) {
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
			} else{
				int status;
				waitpid(pid2, &status, 0);
			}


		
			double approx_factor= (double) lp_vc_size/greedy_vc_size;
			double lp_time= lp_time_taken.count();
			double lp_optimal=G_LP.get_lp_optimal_value();
			G_greedy.write_final_result(final_result_file,
						 numNodes, numEdges, greedy_vc_size, greedy_time_taken, lp_optimal,
					lp_vc_size,lp_time, approx_factor);
		}


		pid_t pid3 = fork();
		if (pid3 == 0) {
			string node = to_string(numNodes);
			string edge = to_string(numEdges);
			string arg = node + edge;

			execlp(
				"python3",
				"python3",
				"visualize.py",
				arg.c_str(),
				(char *)NULL);

			exit(0);
		} else{
			int status;
			waitpid(pid3, &status, 0);
		}
		numEdges = numEdges + EDGE_INTERVAL;
		if (numEdges > 190 && sig_break) {
			break;
		}
		if (numEdges > 45 && sig_break) {
			break;
		}


		if (numEdges==200){
			sig_break=true;
			numEdges=190;
		}

		if (numEdges==50){
			sig_break=true;
			numEdges=45;
		}

	}
	if (repeat_sig){
		repeat_sig=false;
		MAX_EDGE=50;
		numNodes=10;
		EDGE_INTERVAL=5;
		goto REPEAT_JUMP;
	}
	return 0;
}