import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import ttest_ind

# Memory consumption data
memory_native = [4912, 4913, 4912, 4913, 4915, 4915, 4909, 4908, 4923, 4937]
memory_wasm = [4946, 4948, 4954, 4960, 4954, 4954, 4955, 4945, 4948, 4949]
memory_docker = [4922, 4916, 4900, 4935, 4948 ,4956 ,4938 ,4900  ,4914 , 4909]

# Calculate averages
average_memory_native = np.mean(memory_native)
average_memory_wasm = np.mean(memory_wasm)
average_memory_docker = np.mean(memory_docker)

# Plotting
labels = ['Native Executable', 'WebAssembly (Wasm)', 'Docker Container']
average_memory_data = [average_memory_native, average_memory_wasm, average_memory_docker]

fig, ax = plt.subplots()
bars = ax.bar(labels, average_memory_data, color=['blue', 'orange', 'green'])

for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval, f"{yval:.2f} MiB", ha='center', va='bottom')


ax.set_ylabel('Average Memory Consumption (MiB)')
ax.set_title('Average Memory Consumption Comparison')
plt.savefig('memory_benchmark_pc.png')
plt.show()

# T-test
t_stat, p_value = ttest_ind(memory_native, memory_wasm)
print(f'T-Test Results: Native Executable vs. WebAssembly (Wasm)')
print(f'T-Statistic: {t_stat}')
print(f'P-Value: {p_value}')

t_stat, p_value = ttest_ind(memory_native, memory_docker)
print(f'\nT-Test Results: Native Executable vs. Docker Container')
print(f'T-Statistic: {t_stat}')
print(f'P-Value: {p_value}')

t_stat, p_value = ttest_ind(memory_wasm, memory_docker)
print(f'\nT-Test Results: WebAssembly (Wasm) vs. Docker Container')
print(f'T-Statistic: {t_stat}')
print(f'P-Value: {p_value}')
