#pragma once
#include "Event.h"

class BacktestEngine;


class ExecutionHandler
{
private:
    BacktestEngine* engine;
public:
    ExecutionHandler(BacktestEngine* eng) : engine(eng) {}
    void on_order(const OrderEvent& event);
};