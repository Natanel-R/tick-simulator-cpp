#pragma once
#include "Event.h"

class BacktestEngine;



class Portfolio
{
private:
    BacktestEngine* engine;
public:
    Portfolio(BacktestEngine* eng) : engine(eng) {}
    void on_signal(const SignalEvent& event);
    void on_fill(const FillEvent& event);
};