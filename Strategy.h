#pragma once
#include "Event.h"


class BacktestEngine;

class Strategy
{
private:
    BacktestEngine* engine; 
    bool invested = false;
public:
    Strategy(BacktestEngine* eng) : engine(eng) {}
    void calculate_signals(const MarketEvent& event);
};

