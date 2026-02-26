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
    ExecutionHandler* executionHandler;

public:
    BacktestEngine() = default;
    BacktestEngine(Strategy* strat, Portfolio* port, ExecutionHandler* exec) : strategy(strat), 
                    portfolio(port), executionHandler(exec) {}
    void pushEvent(const Event& event) { eventQueue.push(event); }
    void setStrategy(Strategy* strat) { strategy = strat; }
    void setPortfolio(Portfolio* port) { portfolio = port; }
    void setExecutionHandler(ExecutionHandler* exec) { executionHandler = exec; }
    void run();
};