#pragma once
#include <string>
#include <fstream>

class BacktestEngine;

class DataHandler
{
private:
    BacktestEngine* engine;
    std::ifstream csv_file;
public:
    DataHandler(BacktestEngine* eng, const std::string& file_path) : engine(eng), csv_file(file_path) {}
    bool read_next_tick();
};