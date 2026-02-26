#pragma once
#include <deque>
#include <cstdint>

class SMA
{
private:
    std::deque<uint64_t> prices;
    uint64_t total_sum = 0;
    uint64_t period;
public:
    SMA(uint64_t p) : period(p) {}
    void update(uint64_t new_price) 
    {
        total_sum += new_price;
        prices.push_back(new_price);
        if (prices.size() > period)
        {
            uint64_t front_price = prices.front();
            total_sum -= front_price;
            prices.pop_front();
        }
    }
    uint64_t get_value() const
    {
        if (prices.size() == 0) return 0;
        return total_sum / prices.size();
    }
    bool is_ready() const
    {
        return prices.size() == period;
    }
};