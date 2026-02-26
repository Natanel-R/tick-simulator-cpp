#include "Portfolio.h"
#include "BacktestEngine.h"
#include <iostream>

void Portfolio::on_signal(const SignalEvent& event)
{
    OrderEvent order;
    order.timestamp = event.timestamp;
    order.quantity = event.quantity;
    order.price = event.price;
    order.type = event.type;
    order.side = event.side;
    for (int i = 0; i < 8; ++i)
    {
        order.symbol[i] = event.symbol[i];
    }
    engine->pushEvent(order);
}

void Portfolio::on_fill(const FillEvent& event)
{
    int64_t cost = (event.price * event.quantity) + event.commission;
    if (event.side == Side::Buy)
    {
        current_cash -= cost;
        current_holdings += event.quantity;
        std::cout << "BOUGHT " << event.quantity << " shares. Cash left: $" << (current_cash / 1000.0) << "\n";
    }
    else if (event.side == Side::Sell)
    {
        current_cash += cost;
        current_holdings -= event.quantity;
        std::cout << "SOLD " << event.quantity << " shares. Cash left: $" << (current_cash / 1000.0) << "\n";
    }
}