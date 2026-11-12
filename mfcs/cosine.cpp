#include "iostream"
#include "vector"
#include "string"
#include <fstream>

#include <string>
#include <unordered_map>
#include "cmath"
#include "algorithm"
using namespace std;



class text_data_analysis {

	string input_file;
	string sim_output_file;
	string disim_output_file;
	int total_rows;
	int total_cols;
	vector<vector<string>>data_grid;
	vector<tuple<int,int,double>>similarity;
	unordered_map<string, bool>vocab;
	unordered_map<string,int>token_index_map;

	public:
		text_data_analysis(string input_file,string sim_output_file,string disim_output_file){
			this->input_file=input_file;
			this->sim_output_file=sim_output_file;
			this->disim_output_file=disim_output_file;

		}


	public:
		bool read_input_data(){

			ifstream file_fd(this->input_file);
	
			if(file_fd.fail()){
				cout<<"failed to open file";
				return false;
			}
	
			string token;
			cout<<"\nwait for a few moment, paragraph reads under process\n";
			while (file_fd >> token){
				if (token != "##endof_para##"){
					vocab[token]=true;
				}


			}
			file_fd.close();

			int total_token=1;
			for (auto it :vocab){
				if (it.second==true){
					total_token+=1;
				}
				
			}
	
			data_grid.resize(total_token, vector<string>(519));
				this->total_rows=total_token;
				this->total_cols=519;

			cout<<"\ntotal_token (unique word or string):\n"<<total_token;

			int col=0;
			int row=0;
			for (auto it :vocab){
				if (it.second==true){
					total_token+=1;
					data_grid[row][col]=it.first;
					token_index_map[it.first]=row;
					row++;
				}
				
			}

			ifstream file_fd2 (this->input_file);
			if (file_fd2.fail()){
				cout<<"file open failed for making token entry";
				return false;
			}
			
			string token_word;
			int target_col=1;
			int target_row=0;
			unordered_map<string, int>para;
			while (file_fd2 >> token_word){
				para[token_word]++;
				if (token_word == "##endof_para##"){
					for (auto it:para){
						int row_index_for_token=token_index_map[it.first];
						data_grid[row_index_for_token][target_col]= to_string(it.second);
					}
					target_col++;
					para.clear();



				}
			}
			
			return true;
		}

		bool do_cosine_product() {
			vector<double> column_norms(this->total_cols, 0.0);

			for (int col = 1; col < this->total_cols; col++) {
				double sum_squares = 0.0;
				for (int row = 0; row < this->total_rows; row++) {
					if (!data_grid[row][col].empty()) {
						double val = stod(data_grid[row][col]);
						sum_squares += val * val;
					}
					}
				column_norms[col] = sqrt(sum_squares);
			}


			for (int i = 1; i < this->total_cols; i++) {
				for (int j = i + 1; j < this->total_cols; j++) {
					double dot_product = 0.0;
					for (int row = 0; row < this->total_rows; row++) {
						if (!data_grid[row][i].empty() && !data_grid[row][j].empty()) {
							double val_i = stod(data_grid[row][i]);
							double val_j = stod(data_grid[row][j]);
							dot_product += val_i * val_j;
						}
					}


				double similarity_pair=0;
				if (column_norms[i] > 0 && column_norms[j] > 0) {
					similarity_pair = dot_product / (column_norms[i] * column_norms[j]);
					similarity.push_back({i,j,similarity_pair});
			}
		}
	}
	return true;
		}

		void build_stat_for_most_simimilar_and_dissimilar(){

			sort(similarity.begin(),similarity.end(),[](auto const &a,auto const &b){
				auto [i,j,s1]=a;
				auto [p,q,s2]=b;
				return s1<s2;
			});

			int total_similiraity=similarity.size();

			cout<<"\n Top 10 most similar paragraph written to file:\n";
			ofstream sim_fd(this->sim_output_file,ios::out);
			if(sim_fd.fail()){
				cout<<"failed to open outputfile";
				return;

			}
			for (int k=total_similiraity-1;k>=total_similiraity-10;k--){

				auto [i,j,s]=similarity[k];

				sim_fd<<"Cosine Similarity between paragraph ("<<i<<","<<j<<"):"<<s<<"\n";
				sim_fd<<"Following are the Word in both paragraph with count:\n";

				for (auto &it:vocab){
					int row=token_index_map[it.first];
					if (!data_grid[row][i].empty() || !data_grid[row][j].empty()){
						sim_fd<<it.first<<": "<<"["<<data_grid[row][i]<<","<<data_grid[row][j]<<"]\n";
					}
				}
				sim_fd<<"Next pair:\n\n";

			}
			
			ofstream disim_fd(this->disim_output_file,ios::out);
			if(disim_fd.fail()){
				cout<<"failed to  open file";
				return;
			}
			cout<<"\n Top 10 most Disimilar paragraph written to file:\n";
			for (int k=0;k<=9;k++){

				auto [i,j,s]=similarity[k];

				disim_fd<<"Cosine Similarity between paragraph ("<<i<<","<<j<<"):"<<s<<"\n";
				disim_fd<<"Following are the Word in both paragraph with count:\n";

				for (auto &it:vocab){
					int row=token_index_map[it.first];
					if (!data_grid[row][i].empty() || !data_grid[row][j].empty()){
						disim_fd<<it.first<<": "<<"["<<data_grid[row][i]<<","<<data_grid[row][j]<<"]\n";
					}
				}
				disim_fd<<"Next pair:\n\n";

			}

		}


};


int main (){

	text_data_analysis Analyser("forouzan_tcp.txt","most_similar_result.txt","most_di_similar_result.txt");
	Analyser.read_input_data();
	Analyser.do_cosine_product();
	Analyser.build_stat_for_most_simimilar_and_dissimilar();

	return 0;
}