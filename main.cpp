#include "BacktestEngine.h"
#include "Strategy.h"
#include "Portfolio.h"
#include "ExecutionHandler.h"
#include "DataHandler.h"
#include <chrono>
#include <iostream>






int main()
{
    BacktestEngine engine;
    Strategy strategy(&engine);
    Portfolio portfolio(&engine, "../trades.csv");
    ExecutionHandler execution_handler(&engine);
    DataHandler data_handler(&engine, "../historical_data.csv");

    engine.setStrategy(&strategy);
    engine.setPortfolio(&portfolio);
    engine.setExecutionHandler(&execution_handler);
    
    auto start_time = std::chrono::high_resolution_clock::now();
    uint64_t tick_count = 0;
    while (data_handler.read_next_tick())
    {
        engine.run();
        tick_count++;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << "Total Ticks Processed: " << tick_count << ".\n";
    std::cout << "Total Time Elapsed: " << duration << " microseconds.\n";
    if (tick_count != 0) std::cout << "Average Time Per Tick: " << (static_cast<double>(duration) / tick_count) << ".\n";
    else std::cout << "Average Time Per Tick: 0 microseconds.\n";
    return 0;
}