import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import ttest_rel

# Results for file system I/O benchmark
native_executable_times = np.array([2.478366, 2.507122, 2.497655, 2.571678, 2.978593, 2.970729, 2.495028, 2.490393, 2.486665, 2.436887])
wasm_times = np.array([3.456634, 3.441236, 3.455093, 3.382871, 3.357339, 3.419040, 3.351412, 3.331104, 3.494141, 3.548427])
docker_times = np.array([2.603363, 3.082534, 2.732915, 2.617017, 3.598521, 3.267595, 2.958886, 3.059142, 4.180266, 3.669315])

# Calculate average times
average_times = {
    'Native Executable': np.mean(native_executable_times),
    'WebAssembly (Wasm)': np.mean(wasm_times),
    'Docker Container': np.mean(docker_times)
}

# Plotting the bar chart
labels = list(average_times.keys())
values = list(average_times.values())

bars = plt.bar(labels, values, color=['blue', 'orange', 'green'])

for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval, f"{yval:.2f} Seconds", ha='center', va='bottom')


plt.ylabel('Average Write Time (seconds)')
plt.title('File System I/O Benchmark')
plt.savefig('file_i_o_benchmark_pc.png')
plt.show()

# Perform t-tests
t_statistic_native_vs_wasm, p_value_native_vs_wasm = ttest_rel(native_executable_times, wasm_times)
t_statistic_native_vs_docker, p_value_native_vs_docker = ttest_rel(native_executable_times, docker_times)
t_statistic_wasm_vs_docker, p_value_wasm_vs_docker = ttest_rel(wasm_times, docker_times)

# Display t-test results
print(f'T-Test Results: Native Executable vs. WebAssembly (Wasm)')
print(f'T-Statistic: {t_statistic_native_vs_wasm}')
print(f'P-Value: {p_value_native_vs_wasm}\n')

print(f'T-Test Results: Native Executable vs. Docker Container')
print(f'T-Statistic: {t_statistic_native_vs_docker}')
print(f'P-Value: {p_value_native_vs_docker}\n')

print(f'T-Test Results: WebAssembly (Wasm) vs. Docker Container')
print(f'T-Statistic: {t_statistic_wasm_vs_docker}')
print(f'P-Value: {p_value_wasm_vs_docker}')
