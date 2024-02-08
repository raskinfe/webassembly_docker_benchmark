import matplotlib.pyplot as plt

# Algorithm names
algorithms = ['RLE Compression', 'Base64 Encoding', 'AES Encryption', 'BFS Graph', 'Matrix Multiplication', 'Quick Sort', 'Hashing']

# Average CPU times for each scenario
native_times = [0.002587500, 0.000006100, 0.000004100, 0.000030700, 0.000001500, 0.001384200, 0.000008500]
wasm_times = [0.003748300, 0.000011400, 0.000009700, 0.000017500, 0.000006900, 0.001478300, 0.000003100]
docker_times = [0.002660100, 0.000015400, 0.000005900, 0.000109700, 0.000002400, 0.001394100, 0.000013900]

# Plotting the data
bar_width = 0.3
index = range(len(algorithms))

fig, ax = plt.subplots()

# Convert CPU times to microseconds
native_times_micro = [time * 1e6 for time in native_times]
wasm_times_micro = [time * 1e6 for time in wasm_times]
docker_times_micro = [time * 1e6 for time in docker_times]

native_bars = ax.bar(index, native_times_micro, width=bar_width, label='Native')
wasm_bars = ax.bar([i + bar_width for i in index], wasm_times_micro, width=bar_width, label='WASM')
docker_bars = ax.bar([i + 2 * bar_width for i in index], docker_times_micro, width=bar_width, label='Docker')

# Adding labels and title
plt.xlabel('Algorithms')
plt.ylabel('Average CPU Time (Micro Seconds)')
plt.title('CPU Performance Comparison: Native vs. WASM vs. Docker')
plt.xticks([i + bar_width for i in index], algorithms)
plt.legend()

def autoLabel(bars):
    for bar in bars:
        height = bar.get_height()
        ax.annotate(f'{height:.1f}',  # Format the label with 1 decimal points
                    xy=(bar.get_x() + bar.get_width() / 2, height),
                    xytext=(0, 3),  # 3 points vertical offset
                    textcoords='offset points',
                    ha='center', va='bottom')

# Add labels for each set of bars
autoLabel(wasm_bars)
autoLabel(native_bars)
autoLabel(docker_bars)

ax.set_yscale('log')  # Use a logarithmic scale for the y-axis
ax.yaxis.set_major_formatter(plt.ScalarFormatter()) 

# # Increase the step in the y-axis
# ax.set_yticks([i/100 for i in range(0, 1000000, 10000)]) 
# ax.yaxis.set_major_formatter(plt.FormatStrFormatter('%.2f'))  # Format the y-axis labels with 2 decimal points

# Show the plot
plt.savefig('cpu_time.png')
plt.show()
