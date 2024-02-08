import matplotlib.pyplot as plt

average_startup_times = {
    'Native Executable': 974790, 
    'WebAssembly (Wasmer)': 9015347,  
    'Docker Container': 340726497, 
}

# Convert nanoseconds to milliseconds
average_startup_times_ms = {key: value / 1e6 for key, value in average_startup_times.items()}

# Plotting the bar graph with actual times displayed
fig, ax = plt.subplots()
bars = ax.bar(average_startup_times_ms.keys(), average_startup_times_ms.values(), color=['blue', 'green', 'red'])

# Displaying actual times above the bars in milliseconds
for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval, f"{yval:.2f} ms", ha='center', va='bottom')

plt.ylabel('Average Startup Time (milliseconds)')
plt.title('Average Startup Time Comparison')
plt.savefig('startup_time.png')
plt.show()