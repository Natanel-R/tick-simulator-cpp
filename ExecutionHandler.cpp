#include "ExecutionHandler.h"
#include "BacktestEngine.h"


void ExecutionHandler::on_order(const OrderEvent& event)
{
    FillEvent fill;
    fill.date = event.date;
    fill.quantity = event.quantity;
    fill.price = event.price;
    fill.type = EventType::FILL;
    fill.side = event.side;
    fill.commission = 1000; // 1$

    for (int i = 0; i < 8; ++i)
    {
        fill.symbol[i] = event.symbol[i];
    }
    engine->pushEvent(fill);
}