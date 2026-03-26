import pandas as pd
import matplotlib.pyplot as plt

cache_hit_file = pd.read_csv("access_cache_hit.csv")
single_file = pd.read_csv("access_single.csv")

# pd.concat([cache_hit_file, single_file[single_file['time'] <= 1000]], keys=["hit", "missed"]).hist(color=['b', 'r'])
plt.hist([cache_hit_file['time'], single_file[single_file['time'] <= 1000]['time']], color=['b', 'r'])
plt.show()