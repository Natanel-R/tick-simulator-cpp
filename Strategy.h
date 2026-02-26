#pragma once
#include "Event.h"
#include "Indicators.h"

class BacktestEngine;

class Strategy
{
private:
    BacktestEngine* engine; 
    bool invested = false;
    SMA fast_sma{10};
    SMA slow_sma{50};
public:
    Strategy(BacktestEngine* eng) : engine(eng) {}
    void calculate_signals(const MarketEvent& event);
};

