#include "Strategy.h"
#include "BacktestEngine.h"




void Strategy::calculate_signals(const MarketEvent& event)
{
    std::string tick_symbol(event.symbol);
    SymbolState& state = symbol_states[tick_symbol];

    state.fast_sma.update(event.close);
    state.slow_sma.update(event.close);
    if (!state.fast_sma.is_ready() || !state.slow_sma.is_ready()) return;

    if (state.fast_sma.get_value() > state.slow_sma.get_value() && !state.invested)
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
        state.invested = true;
    }
    else if (state.fast_sma.get_value() < state.slow_sma.get_value() && state.invested)
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
        state.invested = false; 
    }
}