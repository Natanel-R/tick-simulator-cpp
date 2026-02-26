#include "BacktestEngine.h"
#include "Strategy.h"
#include "Portfolio.h"
#include "ExecutionHandler.h"
#include "DataHandler.h"






int main()
{
    BacktestEngine engine;
    Strategy strategy(&engine);
    Portfolio portfolio(&engine);
    ExecutionHandler execution_handler(&engine);
    DataHandler data_handler(&engine, "historical_data.csv");

    engine.setStrategy(&strategy);
    engine.setPortfolio(&portfolio);
    engine.setExecutionHandler(&execution_handler);
    
    while (data_handler.read_next_tick())
    {
        engine.run();
    }

    return 0;
}