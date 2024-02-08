from scipy.stats import ttest_rel

# Average CPU times for each scenario
native_times = [0.002587500, 0.000006100, 0.000004100, 0.000030700, 0.000001500, 0.001384200, 0.000008500]
wasm_times = [0.003748300, 0.000011400, 0.000009700, 0.000017500, 0.000006900, 0.001478300, 0.000003100]
docker_times = [0.002660100, 0.000015400, 0.000005900, 0.000109700, 0.000002400, 0.001394100, 0.000013900]

# Perform paired sample t-test for native vs wasm
t_statistic, p_value = ttest_rel(native_times, wasm_times)

# Print the results
print(f'T-test for Native vs Wasm:')
print(f'T-statistic: {t_statistic}')
print(f'P-value: {p_value}')

# Perform paired sample t-test for native vs docker
t_statistic, p_value = ttest_rel(native_times, docker_times)

# Print the results
print(f'\nT-test for Native vs Docker:')
print(f'T-statistic: {t_statistic}')
print(f'P-value: {p_value}')

# Perform paired sample t-test for wasm vs docker
t_statistic, p_value = ttest_rel(docker_times, wasm_times)

# Print the results
print(f'\nT-test for Wasm vs Docker:')
print(f'T-statistic: {t_statistic}')
print(f'P-value: {p_value}')
