#pragma once
#include "Event.h"


class BacktestEngine;

class Strategy
{
private:
    BacktestEngine* engine; 

public:
    Strategy(BacktestEngine* eng) : engine(eng) {}
    void calculate_signals(const MarketEvent& event);
};

