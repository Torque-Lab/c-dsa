
#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "climits"
#include "queue"
#include "algorithm"
using namespace  std;

namespace network {

	template <typename Node>

	class Networkx {
	private:
		unordered_map<Node, unordered_set<Node>> adj;
		bool directed;

	public:
		Networkx(bool directed = false){
			this->directed=directed;
		}

		void add_node(const Node& node) {
			adj[node];
		}

		void add_nodes(const vector<Node>& nodes) {
			for (const auto& node : nodes) {
				add_node(node);
			}
		}

		void add_edge(const Node& u, const Node& v) {
			add_node(u);
			add_node(v);

			adj[u].insert(v);

			if (!directed) {
				adj[v].insert(u);
			}
		}

		void add_edges( const vector<pair<Node, Node>>& edges) {

			for (const auto& [u, v] : edges) {
				add_edge(u, v);
			}
		}

		bool has_node(const Node& node) const {
			return adj.find(node) != adj.end();
		}

		bool has_edge( const Node& u, const Node& v ){

			auto it = adj.find(u);
			return it != adj.end() && it->second.count(v);
		}

		const unordered_set<Node>& neighbors( const Node& node) {

			return adj.at(node);
		}

		size_t number_of_nodes() const {
			return adj.size();
		}

		size_t degree(const Node& node) const {
			return adj.at(node).size();
		}
		size_t out_degree(const Node& node) const {
			return adj.at(node).size();
		}

		size_t in_degree(const Node& node) const {
			size_t count = 0;

			for (const auto& [u, neighbors] : adj) {
				if (neighbors.count(node)) {
					count++;
				}
			}
			return count;
		}
		
		void show() {

			for (const auto& [node, nbrs] : adj) {

				for (const auto& nbr : nbrs) {
					if (directed) {
						cout << node << " -> " << nbr << '\n';
					}
					else if (node <= nbr) {
						cout << node << " <-> " << nbr << '\n';
					}
				}
			}
		}
		vector<Node> getAllNodes() {

			vector<Node> result;
			for (const auto& [node, nbrs] : adj) {
				result.push_back(node);
			}
			return result;
		}

		// return both A to B and B to A in unidirected
		vector<pair<Node, Node>> getAllEdges() {
			vector<pair<Node, Node>> result;

			for (const auto& [u, nbrs] : adj) {
				for (const auto& v : nbrs) {
					result.push_back({u, v});
				}
			}
			return result;
		}
		
		vector<Node> dijkstra(const Node& src, const Node& dest) {

			unordered_map<Node, int> dist;
			unordered_map<Node, Node> parent;

			for (const auto& [node, nbrs] : adj) {
				dist[node] = INT_MAX;
			}

			if (!has_node(src) || !has_node(dest)) {
				return {};
			}

			priority_queue<
				pair<int, Node>,
				vector<pair<int, Node>>,
				greater<pair<int, Node>>
			> pq;

			dist[src] = 0;
			pq.push({0, src});

			while (!pq.empty()) {
				auto [d, u] = pq.top();
				pq.pop();

				if (d > dist[u]) {
					continue;
				}

				if (u == dest) {
					break;
				}

				for (const auto& v : adj.at(u)) {
					if (d + 1 < dist[v]) {
						dist[v] = d + 1;
						parent[v] = u;
						pq.push({dist[v], v});
					}
				}
			}

			if (dist[dest] == INT_MAX) {
				return {};
			}

			vector<Node> path;

			for (Node curr = dest; ; curr = parent.at(curr)) {
				path.push_back(curr);

				if (curr == src) {
					break;
				}
			}

			reverse(path.begin(), path.end());
			return path;
		}
		void get_graph( unordered_map<Node, unordered_set<Node>>& graph, bool & is_directed) {
			graph = adj;
			is_directed = directed;
		}
	};

}
