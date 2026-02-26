#include "ExecutionHandler.h"
#include "BacktestEngine.h"


void ExecutionHandler::on_order(const OrderEvent& event)
{
    uint64_t slippage = (event.price * 5) / 10000;
    uint64_t final_price = (event.side == Side::Buy) ? event.price + slippage : event.price - slippage;

    FillEvent fill;
    fill.date = event.date;
    fill.quantity = event.quantity;
    fill.price = final_price;
    fill.type = EventType::FILL;
    fill.side = event.side;
    fill.commission = 1000; // 1$

    for (int i = 0; i < 8; ++i)
    {
        fill.symbol[i] = event.symbol[i];
    }
    engine->pushEvent(fill);
}