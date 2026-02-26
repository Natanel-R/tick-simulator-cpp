#pragma once
#include "Event.h"
#include <fstream>

class BacktestEngine;



class Portfolio
{
private:
    BacktestEngine* engine;
    std::ofstream out_file;
    int64_t current_cash = 100000000; //100k$
    int64_t current_holdings = 0;
public:
    Portfolio(BacktestEngine* eng, const std::string& file_path) : engine(eng), out_file(file_path) 
    {
        out_file << "Date,Action,Quantity,Price,Cash\n";
    }
    void on_signal(const SignalEvent& event);
    void on_fill(const FillEvent& event);
};