#pragma once
#include <deque>
#include <cstdint>
#include <cmath>

class SMA
{
private:
    std::deque<double> prices;
    double total_sum = 0;
    uint64_t period;
public:
    SMA(uint64_t p) : period(p) {}
    void update(double new_price) 
    {
        total_sum += new_price;
        prices.push_back(new_price);
        if (prices.size() > period)
        {
            double front_price = prices.front();
            total_sum -= front_price;
            prices.pop_front();
        }
    }
    double get_value() const
    {
        if (prices.size() == 0) return 0;
        return total_sum / prices.size();
    }
    bool is_ready() const { return prices.size() == period; }
};


class EMA
{
private:
    uint64_t period;
    double alpha = 1;
    double current_ema = 0;
    uint64_t ticks_processed = 0;
public:
    EMA(uint64_t p) : period(p) { this->alpha = (2.0 / (this->period + 1)); }
    void update(double new_price)
    {
        if (ticks_processed == 0) current_ema = new_price;
        else
        {
            current_ema = (new_price * alpha) + (current_ema * (1 - alpha));
        }
        ticks_processed++;
    }
    bool is_ready() const { return ticks_processed >= period; }
    double get_value() const { return current_ema; }
};



class RSI
{
private:
    uint64_t period;
    double prev_price = 0;
    double avg_gain = 0;
    double avg_loss = 0;
    double current_rsi = 0;
    uint64_t ticks_processed = 0;
public:
    RSI(uint64_t p) : period(p) {}
    void update(double price)
    {
        if (ticks_processed == 0)
        {
            prev_price = price;
            ticks_processed++;
            return; 
        }
        double change = price - prev_price;
        double current_gain = 0, current_loss = 0;
        if (change > 0) current_gain = change;
        else current_loss = std::abs(change);

        avg_gain = ((avg_gain * (period - 1.0)) + current_gain) / period;
        avg_loss = ((avg_loss * (period - 1.0)) + current_loss) / period;
        if (avg_loss == 0) current_rsi = 100;
        else current_rsi = 100.0 - (100.0 / (1 + avg_gain / avg_loss));
        
        prev_price = price;
        ticks_processed++;
    }
    bool is_ready() const { return ticks_processed >= period; }
    double get_value() const { return current_rsi; }
};



class BollingerBands
{
private:
    uint64_t period;
    std::deque<double> window;
    double sum = 0;
    double sum_squares = 0;
    double middle_band = 0;
    double upper_band = 0;
    double lower_band = 0;
    uint64_t ticks_processed = 0;
public:
    BollingerBands(uint64_t p) : period(p) {}
    void update(double price)
    {
        sum += price;
        sum_squares += (price * price);
        window.push_back(price);
        if (window.size() > period)
        {
            double last_price = window.front();
            sum -= last_price;
            sum_squares -= (last_price * last_price);
            window.pop_front();
        }
        if (window.size() == period)
        {
            double mean = sum / period;
            double variance = (sum_squares/period) - (mean * mean);
            if (variance < 0) variance = 0;
            double sd = std::sqrt(variance);
            middle_band = mean;
            upper_band = mean + (2 * sd);
            lower_band = mean - (2 * sd);
        }
        ticks_processed++;
    }
    bool is_ready() const { return ticks_processed >= period; }
    double get_middle() const { return middle_band; }
    double get_upper() const { return upper_band; }
    double get_lower() const { return lower_band; }
};