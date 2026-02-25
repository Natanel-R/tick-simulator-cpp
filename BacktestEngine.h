#pragma once
#include <queue>
#include "Event.h"
#include <type_traits>


class Strategy;
class Portfolio;
class ExecutionHandler;

class BacktestEngine
{
private:
    std::queue<Event> eventQueue;
    Strategy* strategy;
    Portfolio* portfolio;

public:
    BacktestEngine() = default;
    BacktestEngine(Strategy* strat, Portfolio* port) : strategy(strat), portfolio(port) {}
    void pushEvent(const Event& event) { eventQueue.push(event); }
    void setStrategy(Strategy* strat) { strategy = strat; }
    void setPortfolio(Portfolio* port) { portfolio = port; }
    void run();
};