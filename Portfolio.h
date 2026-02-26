#pragma once
#include "Event.h"

class BacktestEngine;



class Portfolio
{
private:
    BacktestEngine* engine;
    int64_t current_cash = 100000000; //100k$
    int64_t current_holdings = 0;
public:
    Portfolio(BacktestEngine* eng) : engine(eng) {}
    void on_signal(const SignalEvent& event);
    void on_fill(const FillEvent& event);
};