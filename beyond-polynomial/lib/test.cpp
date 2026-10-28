
#include <iostream>
#include <string>
#include <unordered_map>
#include "networkx.h"

using namespace std;
using namespace network;

int main() {

	Networkx<int> g;

	g.add_nodes({1, 2, 3, 4, 5});
	g.add_edge(1, 2);
	g.add_edges({{2, 3}, {3, 4}, {4, 5}});

	g.show();

	Networkx<char> letters(true);

	letters.add_edges({{'A', 'B'}, {'B', 'C'}});

	cout << letters.has_edge('A', 'B') << '\n'; // 1
	cout << letters.has_edge('B', 'A') << '\n'; // 0

	letters.show();

	Networkx<string> people;
	people.add_edges({
		{"Alice", "Bob"},
		{"Bob", "Charlie"}
	});

	vector<string>path = people.dijkstra("Alice", "Charlie");
	for (int i=0;i<path.size();i++){
		cout<< path[i]<<" ";
	}

	unordered_map<string, unordered_set<string>>copy;
	bool is_directed;
	people.get_graph(copy, is_directed);

	for (auto &[node,neighbors]:copy){
		for (auto it=neighbors.begin();it!=neighbors.end();it++){
			cout<<" \nneighbour of "<< node<<"\n"<<*it<<" ";

		}
		cout<<"\n";
	}
}
