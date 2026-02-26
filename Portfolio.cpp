#include "Portfolio.h"
#include "BacktestEngine.h"
#include <iostream>

void Portfolio::on_signal(const SignalEvent& event)
{
    OrderEvent order;
    order.date = event.date;
    order.quantity = event.quantity;
    order.price = event.price;
    order.type = EventType::ORDER;
    order.side = event.side;
    for (int i = 0; i < 8; ++i)
    {
        order.symbol[i] = event.symbol[i];
    }
    engine->pushEvent(order);
}

void Portfolio::on_fill(const FillEvent& event)
{
    int64_t cost = (event.price * event.quantity);
    if (event.side == Side::Buy)
    {
        current_cash -= (cost + event.commission);
        current_holdings += event.quantity;
        out_file << event.date << ",BUY," << event.quantity << "," << (event.price/1000.0) << "," << (current_cash / 1000.0) << "\n";
    }
    else if (event.side == Side::Sell)
    {
        current_cash += (cost - event.commission);
        current_holdings -= event.quantity;
        out_file << event.date << ",SELL," << event.quantity << "," << (event.price/1000.0) << "," << (current_cash / 1000.0) << "\n";
    }
}