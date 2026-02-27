import yfinance as yf
import pandas as pd


print("Downloading data...")
df = yf.download("AAPL", period = "60d", interval="5m", multi_level_index = False)

df.index.name = 'Date'
df = df.reset_index()
df['Symbol'] = 'AAPL'
df['Date'] = df['Date'].dt.strftime('%Y%m%d%H%M')

df = df.dropna()
df[['Date', 'Symbol', 'Open', 'High', 'Low', 'Close', 'Volume']].to_csv("historical_data.csv", index = False, header = False)
print("Downloaded Data to historical_data.csv. Ready for C++.")