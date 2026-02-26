import yfinance as yf
import pandas as pd


print("Downloading data...")
df = yf.download("AAPL", period = "5y", interval="1d", multi_level_index = False)

df = df.reset_index()
df['Symbol'] = 'AAPL'
df['Date'] = df['Date'].dt.strftime("%Y%m%d")

df = df.dropna()
df[['Date', 'Symbol', 'Open', 'High', 'Low', 'Close', 'Volume']].to_csv("historical_data.csv", index = False, header = False)
print("Downloaded Data to historical_data.csv. Ready for C++.")