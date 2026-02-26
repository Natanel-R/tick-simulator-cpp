#include "Strategy.h"
#include "BacktestEngine.h"




void Strategy::calculate_signals(const MarketEvent& event)
{
    fast_sma.update(event.close);
    slow_sma.update(event.close);
    if (!fast_sma.is_ready() || !slow_sma.is_ready()) return;

    if (fast_sma.get_value() > slow_sma.get_value() && !invested)
    {
        SignalEvent signal;
        signal.date = event.date;
        signal.quantity = 100;
        signal.price = event.close;
        signal.type = EventType::SIGNAL;
        signal.side = Side::Buy;

        for (int i = 0; i < 8; ++i)
        {
            signal.symbol[i] = event.symbol[i];
        }
        engine->pushEvent(signal);
        invested = true;
    }
    else if (fast_sma.get_value() < slow_sma.get_value() && invested)
    {
        SignalEvent signal;
        signal.date = event.date;
        signal.quantity = 100;
        signal.price = event.close;
        signal.type = EventType::SIGNAL;
        signal.side = Side::Sell; 
        
        for (int i = 0; i < 8; ++i) {
            signal.symbol[i] = event.symbol[i];
        }
        engine->pushEvent(signal);
        invested = false; 
    }
}