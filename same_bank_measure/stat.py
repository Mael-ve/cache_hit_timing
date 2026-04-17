import pandas as pd
import matplotlib.pyplot as plt 

time_file = pd.read_csv("access_two_value.csv")
tab = time_file.median(axis=1)

plt.hist(tab, rwidth=0.6, bins=100) 
plt.show()