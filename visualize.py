import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def main():
    print("Loading backtest data...")
    
    # 1. Load the market data and the trades
    market_data = pd.read_csv("historical_data.csv", names=['Date', 'Symbol', 'Open', 'High', 'Low', 'Close', 'Volume'])
    trades = pd.read_csv("trades.csv")

    # Convert dates to strings so they look nice on the X-axis
    market_data['Date'] = pd.to_datetime(market_data['Date'], format='%Y%m%d%H%M')
    trades['Date'] = pd.to_datetime(trades['Date'], format='%Y%m%d%H%M')

    # 2. Setup the dashboard (2 rows, 1 column)
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8), sharex=True)
    fig.suptitle("Quant Engine Backtest Results", fontsize=16)

    # --- TOP CHART: Stock Price & Trades ---
    ax1.plot(market_data['Date'], market_data['Close'], label='AAPL Close Price', color='black', linewidth=1.5)
    
    # Filter trades for buys and sells
    buys = trades[trades['Action'] == 'BUY']
    sells = trades[trades['Action'] == 'SELL']
    
    # Plot green up-arrows for buys, red down-arrows for sells
    ax1.scatter(buys['Date'], buys['Price'], marker='^', color='green', label='Buy', s=100, zorder=5)
    ax1.scatter(sells['Date'], sells['Price'], marker='v', color='red', label='Sell', s=100, zorder=5)
    
    ax1.set_ylabel("Price ($)")
    ax1.legend()
    ax1.grid(True, linestyle='--', alpha=0.6)

    # --- BOTTOM CHART: Portfolio Cash ---
    # To show cash over time, we merge the trades onto the market data dates
    # If no trade happened on a day, we just carry forward the previous day's cash
    merged = pd.merge(market_data, trades[['Date', 'Cash']], on='Date', how='left')
    merged['Cash'] = merged['Cash'].ffill() # Forward-fill missing days
    
    # Fill any starting NaN values with our initial $100,000
    merged['Cash'] = merged['Cash'].fillna(100000.0) 

    # Total return
    starting_cash = 100000.0
    ending_cash = merged['Cash'].iloc[-1]
    total_return = ((ending_cash / starting_cash) - 1.0) * 100
    # Max Drawdown
    running_max = merged['Cash'].cummax()
    drawdown = (merged['Cash'] / running_max) - 1.0
    max_drawdown = drawdown.min() * 100
    # Sharpe ratio
    daily_returns = merged['Cash'].pct_change().dropna()
    if daily_returns.std() != 0:
        sharpe_ratio = (daily_returns.mean() / daily_returns.std()) * np.sqrt(252)
    else:
        sharpe_ratio = 0.0
    print("\n" + "="*30)
    print("BACKTEST RESULTS")
    print("="*30)
    print(f"Final Cash:   ${ending_cash:,.2f}")
    print(f"Total Return: {total_return:.2f}%")
    print(f"Max Drawdown: {max_drawdown:.2f}%")
    print(f"Sharpe Ratio: {sharpe_ratio:.2f}")
    print("="*30 + "\n")


    # Plot
    ax2.plot(merged['Date'], merged['Cash'], label='Portfolio Cash', color='blue', linewidth=2)
    ax2.set_ylabel("Cash Balance ($)")
    ax2.set_xlabel("Date")
    ax2.legend()
    ax2.grid(True, linestyle='--', alpha=0.6)

    # 3. Render the dashboard
    fig.autofmt_xdate() # Adds the 45-degree tilt to the dates
    plt.tight_layout()
    plt.savefig("backtest_report.png", dpi=300)
    print("Dashboard saved successfully as 'backtest_report.png'!")

if __name__ == "__main__":
    main()