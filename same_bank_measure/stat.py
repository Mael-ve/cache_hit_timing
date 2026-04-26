import pandas as pd
import matplotlib.pyplot as plt 

THRESHOLD = 300

time_file = pd.read_csv("access_two_value.csv")
tab = time_file.mean(axis=1)
tab = tab[tab <= 500]

c_under = len(tab[tab <= THRESHOLD])
p_under= c_under / len(tab) * 100
c_above = len(tab[tab > THRESHOLD])
p_above = c_above / len(tab) * 100
print(f"There are {c_under} ({p_under}%) value under threshold")
print(f"There are {c_above} ({p_above}%) value above threshold")

plt.hist(tab, rwidth=0.6, bins=100) 
plt.show()



