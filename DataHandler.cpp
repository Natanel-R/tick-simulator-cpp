#include "DataHandler.h"
#include "BacktestEngine.h"
#include <sstream>
#include <iostream>


bool DataHandler::read_next_tick()
{
    if (!csv_file.is_open())
    {
        std::cout << "CRITICAL ERROR: Could not open the CSV file!\n";
        return false;
    }
    std::string line_string;
    if (!std::getline(csv_file, line_string)) return false;
    std::stringstream line_stream(line_string); 

    std::string ts_str;
    std::string sym_str;
    std::string price_str;
    std::string qty_str;
    std::getline(line_stream, ts_str, ',');
    std::getline(line_stream, sym_str, ',');
    std::getline(line_stream, price_str, ',');
    std::getline(line_stream, qty_str);

    uint64_t ts = std::stoull(ts_str);
    uint64_t qty = std::stoull(qty_str);
    uint64_t price = static_cast<uint64_t>(std::stod(price_str) * 1000);
    MarketEvent event;
    event.timestamp = ts;
    event.quantity = qty;
    event.price = price;
    event.type = EventType::MARKET;
    size_t copy_len = sym_str.length();
    if (copy_len > 7) copy_len = 7;
    for (size_t i = 0; i < copy_len; ++i)
    {
        event.symbol[i] = sym_str[i];
    }
    event.symbol[copy_len] = '\0';
    engine->pushEvent(event);
    
    return true;
}