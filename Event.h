#pragma once
#include <variant>
#include <cstdint>

enum class EventType
{
    MARKET,
    SIGNAL,
    ORDER,
    FILL
};

enum class Side
{
    Buy,
    Sell
};

struct MarketEvent
{
    uint64_t timestamp;
    uint64_t quantity;
    uint64_t price;
    char symbol[8];
    EventType type;
};

struct SignalEvent
{
    uint64_t timestamp;
    uint64_t quantity;
    uint64_t price;
    char symbol[8];
    EventType type;
    Side side;
};

struct OrderEvent
{
    uint64_t timestamp;
    uint64_t quantity;
    uint64_t price;
    char symbol[8];
    EventType type;
    Side side;
};

struct FillEvent
{
    uint64_t timestamp;
    uint64_t quantity;
    uint64_t price
    uint64_t commission;
    char symbol[8];
    EventType type;
    Side side;
};

using Event = std::variant<MarketEvent, SignalEvent, OrderEvent, FillEvent>;
