import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def load_data():
    data = pd.read_csv("ppm.csv")
    ppm_log = data.iloc[1::2, 0].reset_index(drop=True)  # 奇数行
    timestamp = data.iloc[2::2, 0].reset_index(drop=True)  # 偶数行
    return pd.DataFrame({"timestamp": timestamp, "ppm_log": ppm_log})


if __name__ == "__main__":
    data = load_data()
    print(data.head())
    print(data.tail())
    print(data.shape)
    plt.plot(data["timestamp"], data["ppm_log"])
    plt.show()
