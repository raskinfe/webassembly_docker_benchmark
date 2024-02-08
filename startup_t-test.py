import numpy as np
from scipy import stats

# Average startup times
native_executable_times = np.array([1294686, 993515, 1016486, 851651, 948633, 814061, 768795, 893620, 1258276, 908186])
wasm_times = np.array([32106099, 5090029, 5503663, 8142029, 7079086, 5674608, 5533695, 7925733, 6286836, 6811699])
docker_times = np.array([499118880, 319831183, 340214933, 322488424, 316686817, 315039562, 304116234, 386481920, 300331040, 302955980])

# Perform t-test between Native Executable and WebAssembly
t_statistic, p_value = stats.ttest_ind(native_executable_times, wasm_times, equal_var=False)
print(f'Test between Native Executable and WebAssembly:\n'
      f'T-Statistic: {t_statistic}\n'
      f'P-Value: {p_value}')

# Perform t-test between Native Executable and Docker Container
t_statistic, p_value = stats.ttest_ind(native_executable_times, docker_times, equal_var=False)
print(f'\nTest between Native Executable and Docker Container:\n'
      f'T-Statistic: {t_statistic}\n'
      f'P-Value: {p_value}')

# Perform t-test between WebAssembly and Docker Container
t_statistic, p_value = stats.ttest_ind(wasm_times, docker_times, equal_var=False)
print(f'\nTest between WebAssembly and Docker Container:\n'
      f'T-Statistic: {t_statistic}\n'
      f'P-Value: {p_value}')
