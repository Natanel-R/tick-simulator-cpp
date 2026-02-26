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

    std::string date_str;
    std::string sym_str;
    std::string open_str;
    std::string high_str;
    std::string low_str;
    std::string close_str;
    std::string volume_str;
    std::getline(line_stream, date_str, ',');
    std::getline(line_stream, sym_str, ',');
    std::getline(line_stream, open_str, ',');
    std::getline(line_stream, high_str, ',');
    std::getline(line_stream, low_str, ',');
    std::getline(line_stream, close_str, ',');
    std::getline(line_stream, volume_str);

    uint64_t date = std::stoull(date_str);
    uint64_t volume = std::stoull(volume_str);
    uint64_t open = static_cast<uint64_t>(std::stod(open_str) * 1000);
    uint64_t high = static_cast<uint64_t>(std::stod(high_str) * 1000);
    uint64_t low = static_cast<uint64_t>(std::stod(low_str) * 1000);
    uint64_t close = static_cast<uint64_t>(std::stod(close_str) * 1000);

    MarketEvent event;
    event.date = date;
    event.open = open;
    event.high = high;
    event.low = low;
    event.close = close;
    event.volume = volume;
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