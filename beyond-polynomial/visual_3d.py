
import sys
import os
import matplotlib.pyplot as plt

TIMEOUT_MS = 60000

def main():
	print("Visualization started")
	if len(sys.argv) < 2:
		print("sys arg are few")
		sys.exit(1)

	triple, cardinality = map(int, sys.argv[1].split("##"))
	filename = f"vis_data{triple}_{cardinality}.txt"

	if not os.path.isfile(filename):
		print("File not found:", filename)
		return

	inputs = []
	times = []

	with open(filename, "r") as file:
		for line in file:
			parts = line.split()
			if len(parts) < 2:
				continue

			try:
				time_ms = float(parts[0])
				n_cubed = float(parts[1])
			except ValueError:
				continue

			inputs.append(n_cubed)
			times.append(time_ms)

	if not times:
		print("No valid data found", flush=True)
		return


	data = sorted(zip(inputs, times))
	inputs, times = zip(*data)

	plt.figure(figsize=(9, 5))
	plt.plot(inputs, times, "o-", color="blue",
		linewidth=2, markersize=5, label="Execution time")

	# Timeout threshold
	plt.axhline(TIMEOUT_MS, color="red", linestyle="--",
		label="60,000 ms limit")

	# Highlight measurements above the threshold
	for x, y in zip(inputs, times):
		if y > TIMEOUT_MS:
			plt.scatter(x, y, color="red", marker="x", s=80)

	plt.xlabel("Input size (n^3)")
	plt.ylabel("Execution time (milliseconds)")
	plt.title(f"cardinality={cardinality}")
	plt.grid(True, alpha=0.3)
	plt.legend()
	plt.tight_layout()

	output_file = f"vis_plot{triple}_{cardinality}.png"
	plt.savefig(output_file, dpi=300)
	print("Graph saved:", output_file, flush=True)


if __name__ == "__main__":
	main()
