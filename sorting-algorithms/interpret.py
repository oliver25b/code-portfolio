import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('data.csv', index_col=False)

print(data)

plt.plot(data)

plt.title('Sorting Algorithm Comparison')
plt.legend(['Bubble Sort', 'Selection Sort', 'Insertion Sort', 'Shell Sort', 'Quick Sort', 'Merge Sort'])
plt.yscale('symlog')
plt.ylabel('Time to Sort (ms)')
plt.xticks(ticks=range(0,10), labels=data.iloc[:,0])
plt.xlabel('Number of Sortees')
plt.show()