#pragma once
#include "Event.h"
#include "Indicators.h"
#include <unordered_map>
#include <string>


class BacktestEngine;

class Strategy
{
private:
    
    struct SymbolState
    {
        SMA fast_sma{10};
        SMA slow_sma{50};
        bool invested = false;

        SymbolState() : fast_sma(10), slow_sma(50), invested(false) {}
    };

    BacktestEngine* engine; 
    std::unordered_map<std::string, SymbolState> symbol_states;

public:
    Strategy(BacktestEngine* eng) : engine(eng) {}
    void calculate_signals(const MarketEvent& event);
};

