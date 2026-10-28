
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ratio>
#include <sched.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <set>
#include <tuple>
#include <random>
#include "lib/rapidcsv.h"
#include "sys/wait.h"
#include "errno.h"
#include "chrono"
#include <stdexcept> 

using namespace std;

using Triple = tuple<string, string, string>;
bool global_naive_thresold_hit=false;
auto initial_time_for_recursion = chrono::high_resolution_clock::now();

# define  MAX_ALLOWED_TIME_IN_Milli_SECOND 60000


class three_dimensional_matching {
	int common_cardinality;
	int triple_number;
	vector<Triple> T;
	vector<Triple> current_naive_matching;
	vector<Triple> best_naive_matching;
	vector<Triple> approx_matching;
	set<string> usedX, usedY, usedZ;
	mt19937 seed_gen;

	public :
		three_dimensional_matching(int triple_number,int cardanality){
			this->common_cardinality = cardanality;
			this->triple_number = triple_number;
			random_device rd;
			mt19937 gen(rd());
			this->seed_gen = gen;

	}

public :
	bool seed_input_triples_randomly(){
		int max_triplet_with_exatly_one_from_each = common_cardinality* common_cardinality *common_cardinality;
		if (triple_number > max_triplet_with_exatly_one_from_each){
			cout<<triple_number<<"\n";
			cout<<max_triplet_with_exatly_one_from_each;
			cout<< "given triplet number is beyond max";
			return false;
		}
		 T.clear();
		 T.reserve(triple_number);
		 usedX.clear();
		 usedY.clear();
		 usedZ.clear();
		 current_naive_matching.clear();
		 best_naive_matching.clear();
		 current_naive_matching.reserve(triple_number);
		 best_naive_matching.reserve(triple_number);

		for (int i=0;i < triple_number;i++){
			string x= "x" + to_string(random_genertor(common_cardinality));
			string y= "y" + to_string(random_genertor(common_cardinality));
			string z= "z" + to_string(random_genertor(common_cardinality));

			T.push_back({x,y,z});
		}

		return true;
	}

	void three_d_naive_matching (int index) {

		
		auto current_time=chrono::high_resolution_clock::now();
		chrono::duration<double,milli>time_passed_since;
		time_passed_since=current_time-initial_time_for_recursion;

		if (time_passed_since.count() > MAX_ALLOWED_TIME_IN_Milli_SECOND ){
			global_naive_thresold_hit=true;
			throw runtime_error("time exceeded_escaping deep recursion");
		}
		if (index >=T.size()) {
			if (current_naive_matching.size() > best_naive_matching.size()) {
				best_naive_matching = current_naive_matching;
			}

		return;		
		}

		auto [x, y, z] = T[index];

		if (!usedX.count(x) && !usedY.count(y) && !usedZ.count(z)) {
			usedX.insert(x);
			usedY.insert(y);
			usedZ.insert(z);
			current_naive_matching.push_back(T[index]);
			three_d_naive_matching(index + 1);

			// leave 		
			current_naive_matching.pop_back();		
			usedX.erase(x);
			usedY.erase(y);
			usedZ.erase(z);
		}	

		three_d_naive_matching(index+ 1);
	}

	void display_best_feasible_matching_from_T(){

		cout<< "3-D optimal matching:"<<best_naive_matching.size();
		for (auto &[x,y,z]: best_naive_matching){

			cout<<"\n list of triplet:\n";
			cout<<" ("<<x <<","<<y<<","<<z<<");";
		}
		cout<<"\n";

	}

	void three_factor_approx_matching (){
		set<string>matched;
		approx_matching.clear();
		approx_matching.reserve(T.size());
		for (int i=0; i<T.size();i++){
			auto [x,y,z] =T[i];
			if (!matched.count(x) && !matched.count(y) &&!matched.count(z)){
				matched.insert(x);
				matched.insert(y);
				matched.insert(z);
				approx_matching.push_back({x,y,z});

			}
		}
	}

	void display_approx_matching_from_T(){

		cout<< "3-D approx matching:"<<approx_matching.size();
		for (auto &[x,y,z]: approx_matching){

			cout<<"\n list of triplet:\n";
			cout<<" ("<<x <<","<<y<<","<<z<<");";
		}
		cout<<"\n";

	}
	int get_approx_matching_size(){
		return approx_matching.size();
	}
	int get_naive_matching_size(){
		return best_naive_matching.size();
	}

	void heurstic_matching_approach(){

	}

	void integer_LP(){

	}
	
	private:
		int random_genertor(int max_limit){

		uniform_int_distribution<> distr(1, max_limit); 
		return distr(this->seed_gen);
	}


 };

 class report_builder_for_np_hard {

	string naive_vs_approx_file;
	string naive_vs_heuristic_file;
	string approx_vs_heuristic_file;


	public:
		report_builder_for_np_hard(string naive_vs_approx_file,
			string naive_vs_heuristic_file,string approx_vs_heuristic_file
		){

			this->naive_vs_approx_file=naive_vs_approx_file;
			this->naive_vs_heuristic_file=naive_vs_heuristic_file;
			this->approx_vs_heuristic_file=approx_vs_heuristic_file;

		}

	bool prepare_naive_vs_approx_csv_file(){

		vector<string>column_name={"cardinality(n)","size_of_input_T",
			"naive_maximum_matching_size","naive_time_taken(milli_second)","approximation_maximal_matching_size",
			"approximation_time_taken(milli_second)","approx-factor (approx/naive)"};

		rapidcsv::Document doc(naive_vs_approx_file);
			
		for (int i=0;i<column_name.size();i++){
			doc.SetColumnName(i , column_name[i]);

		}
		doc.Save();

		return true;
	}
	bool add_entry_to_naive_vs_approx_csv_and_call_child(int index,
		vector<string>&naive_approx_row,bool should_call_child,
		int triple, int cardinality){
		
		rapidcsv::Document doc(naive_vs_approx_file);
		doc.InsertRow(index,naive_approx_row);
		doc.Save();
		write_for_child(naive_approx_row, cardinality);
		bool child_progress=false;
		if (should_call_child){
			cout<< "calling child";
			child_progress=call_graph_builder_child(cardinality);

		}
		return child_progress;
	}

	void write_for_child(vector<string>data,int cardinality){
		string file_path ="vis_data"+to_string(3)+"_" + to_string(cardinality)+".txt";
		fstream child_file(file_path,ios::app);
		child_file << data[3] << " " <<data[1]<<"\n";
		child_file.close();

	}
	bool prepare_naive_vs_heuristic_csv_file(){

		vector<string>column_name={"cardinality(n)","size_of_input_T",
			"naive_maximum_matching_size","naive_time_taken(milli_second)","heuristic_maximal_matching_size",
			"heuristic_time_taken(milli_second)","heu-factor(heu/naive)"};

		rapidcsv::Document doc(naive_vs_heuristic_file);
			
		for (int i=0;i<column_name.size();i++){
			doc.SetColumnName(i , column_name[i]);

		}

		return true;
	}

	bool approx_vs_heuristic_csv_file(){

		vector<string>column_name={"cardinality(n)","size_of_input_T",
			"approximation_matching_size","approximation_time_taken(milli_second)","heuristic_maximal_matching_size",
			"heuristic_time_taken(milli_second)","factor_between_approximation_heuristic (heu/approx)"};

		rapidcsv::Document doc(naive_vs_heuristic_file);
			
		for (int i=0;i<column_name.size();i++){
			doc.SetColumnName(i , column_name[i]);

		}

		return true;
	}

	bool call_graph_builder_child(int cardinality){
		

		string base_args= to_string(3)+ "##"+ to_string(cardinality);

		pid_t pid= fork();

		if(pid <0){
			cout <<"forked failed for cardinality";
			return false;
		}
		
		if (pid==0){
			cout<<"just forked";
			execlp("python3",
				"python3",
				"visual_3d.py",
				base_args.c_str(),
				( char *) NULL);

			cout<<"error from exec python"<<strerror(errno);
			exit(0);

		}else {
			int status;
			waitpid(pid,&status,0);
		}

		return true;
	}


 };


int main() {


	for (int cardinality=3; cardinality<10;cardinality++){
		int max_triple_each_using_once=cardinality*cardinality*cardinality;
			int interval=0;
			int index=0;

		 string naive_vs_approx_file="naive_approx"+to_string(cardinality)+".csv";
		 string naive_vs_heuristic_file="naive_heuristic"+to_string(cardinality)+".csv";
		 string approx_vs_heuristic_file="approx_heuristic"+to_string(cardinality)+".csv";
		 int triple=cardinality;
		int time_to_call_child=0;
		bool should_call_child=false;
		for (;triple<=max_triple_each_using_once;){

			three_dimensional_matching hyper_graph(triple,cardinality);
				
	 			if (hyper_graph.seed_input_triples_randomly()){
					
					fstream file1(naive_vs_approx_file,ios::app);
					fstream file2 (naive_vs_heuristic_file,ios::app);
					fstream file3(approx_vs_heuristic_file, ios::app);

					report_builder_for_np_hard Report(naive_vs_approx_file,naive_vs_heuristic_file,
									approx_vs_heuristic_file);

					auto start_three_f_m=chrono::high_resolution_clock::now();
					hyper_graph.three_factor_approx_matching();
					// hyper_graph.display_approx_matching_from_T();
					Report.prepare_naive_vs_approx_csv_file();
					auto end_three_f_m=chrono::high_resolution_clock::now();
					chrono::duration<double,milli>approxy_duration;
					
					approxy_duration=end_three_f_m-start_three_f_m;

					hyper_graph.heurstic_matching_approach();

					vector<string>naive_approx_row;
					try{
					auto start_naive=chrono::high_resolution_clock::now();

					initial_time_for_recursion=chrono::high_resolution_clock::now();

					hyper_graph.three_d_naive_matching(0);
					auto end_naive=chrono::high_resolution_clock::now();

					chrono::duration<double,milli>naive_duration;
					naive_duration=end_naive-start_naive;
					
					naive_approx_row.clear();
					naive_approx_row.push_back(to_string(cardinality));
					naive_approx_row.push_back(to_string(triple));
					naive_approx_row.push_back(to_string(hyper_graph.get_naive_matching_size()));
					naive_approx_row.push_back(to_string(naive_duration.count()));
					naive_approx_row.push_back(to_string(hyper_graph.get_approx_matching_size()));
					naive_approx_row.push_back(to_string(approxy_duration.count()));
					double factor_1= (double ) hyper_graph.get_approx_matching_size()/hyper_graph.get_naive_matching_size();
					naive_approx_row.push_back(to_string(factor_1));
					

					if (cardinality <= 4){
						interval=2;
						time_to_call_child=triple+interval;
					}
					if (cardinality>4 and cardinality < 6){
						interval=4;
						time_to_call_child=triple+interval;
					}
					if (cardinality >= 6){
						interval=6;
						time_to_call_child=triple+interval;
					}
					if (time_to_call_child > max_triple_each_using_once){
						should_call_child=true;
						cout<<"hit all case";
					}

					Report.add_entry_to_naive_vs_approx_csv_and_call_child(index,naive_approx_row, should_call_child, triple, cardinality);
					// hyper_graph.display_best_feasible_matching_from_T();

					}catch(std::runtime_error &e){
						cout<< "time exceeded";
						if (global_naive_thresold_hit){
							naive_approx_row.clear();
							naive_approx_row.push_back(to_string(cardinality));
							naive_approx_row.push_back(to_string(triple));
							naive_approx_row.push_back(to_string(0000));
							naive_approx_row.push_back(to_string(60000));
							naive_approx_row.push_back(to_string(hyper_graph.get_approx_matching_size()));
							naive_approx_row.push_back(to_string(approxy_duration.count()));
							double factor_1= 0;
							naive_approx_row.push_back(to_string(factor_1));
							Report.add_entry_to_naive_vs_approx_csv_and_call_child(index, naive_approx_row, true, interval, cardinality);

							break;
						}
					}
				}


				if (cardinality <= 4){
					interval=2;
					triple=triple+interval;
				}
				if (cardinality>4 and cardinality < 6){
					interval=4;
					triple=triple+interval;
				}
				if (cardinality >= 6){
					interval=6;
					triple=triple+interval;
				}

			}
			
		

	}

}
