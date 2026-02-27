#pragma once
#include "Event.h"
#include <unordered_map>
#include <string>
#include <fstream>

class BacktestEngine;



class Portfolio
{
private:
    BacktestEngine* engine;
    std::ofstream out_file;
    int64_t current_cash = 100000000; //100k$
    std::unordered_map<std::string, int64_t> positions;
public:
    Portfolio(BacktestEngine* eng, const std::string& file_path) : engine(eng), out_file(file_path) 
    {
        out_file << "Date,Symbol,Action,Quantity,Price,Cash\n";
    }
    void on_signal(const SignalEvent& event);
    void on_fill(const FillEvent& event);
};