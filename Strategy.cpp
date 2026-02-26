#include "Strategy.h"
#include "BacktestEngine.h"




void Strategy::calculate_signals(const MarketEvent& event)
{
    if (!invested && event.close < 150000) // 150$
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
    else if (invested && event.close > 150000)
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