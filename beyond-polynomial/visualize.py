import sys
import networkx as nx
import matplotlib.pyplot as plt


n = int(sys.argv[1])

graph_file = f"seed_graph{n}.txt"
vc_file = f"vertex_cover{n}.txt"

G = nx.Graph()

with open(graph_file) as f:
        parts = f.readline().split()
        num_nodes = int(parts[0])
        num_edges = int(parts[1])

        for _ in range(num_edges):
            u, v, w = map(int, f.readline().split())
            G.add_edge(u, v, weight=w)

with open(vc_file) as f:
    cover_size = int(f.readline())
    vertex_cover = set(map(int, f.read().split()))


pos = nx.spring_layout(G, seed=42)

node_colors = [
    "green" if node in vertex_cover else "skyblue"
    for node in G.nodes
]

nx.draw(
    G,
    pos,
    with_labels=True,
    node_color=node_colors,
    node_size=700
)


weights = nx.get_edge_attributes(G, "weight")
nx.draw_networkx_edge_labels(G, pos, edge_labels=weights)

plt.savefig(f"vertex{num_nodes}.png", format="png", dpi=300)
plt.title(f"Nodes: {num_nodes}, Edges: {num_edges}, VC: {cover_size}")

plt.show()
