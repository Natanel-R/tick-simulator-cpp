#include "Strategy.h"
#include "BacktestEngine.h"




void Strategy::calculate_signals(const MarketEvent& event)
{
    // Need to add calculation based on the event

    SignalEvent ny_signal;
    my_signal.type = EventType::SIGNAL;

    Event new_event = my_signal;
    engine->pushEvent(new_event);
}