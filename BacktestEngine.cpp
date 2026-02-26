#include "BacktestEngine.h"
#include "Strategy.h"
#include "Portfolio.h"
#include "ExecutionHandler.h"

void BacktestEngine::run()
{
    while (!eventQueue.empty())
    {
        Event next_event = eventQueue.front();
        eventQueue.pop();
        std::visit([this](auto&& event_payload){
            using PayloadType = std::decay_t<decltype(event_payload)>;
            if constexpr (std::is_same_v<PayloadType, MarketEvent>)
            {
                strategy->calculate_signals(event_payload);
            }
            else if constexpr (std::is_same_v<PayloadType, SignalEvent>)
            {
                portfolio->on_signal(event_payload);
            }
            else if constexpr (std::is_same_v<PayloadType, OrderEvent>)
            {
                
            }
            else if constexpr (std::is_same_v<PayloadType, FillEvent>)
            {   
                portfolio->on_fill(event_payload);
            }
        }, next_event);
    }
}