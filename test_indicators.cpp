#include <gtest/gtest.h>
#include "Indicators.h"


TEST(SMATests, CalculatesRollingAverage)
{
    SMA sma{3};
    EXPECT_DOUBLE_EQ(sma.get_value(), 0.0);
    EXPECT_FALSE(sma.is_ready());

    sma.update(10.1);
    EXPECT_FALSE(sma.is_ready());
    sma.update(20.2);
    EXPECT_FALSE(sma.is_ready());
    sma.update(30.3);
    EXPECT_TRUE(sma.is_ready());
    EXPECT_DOUBLE_EQ(sma.get_value(), 20.2);

    sma.update(40.4);
    EXPECT_TRUE(sma.is_ready());
    EXPECT_DOUBLE_EQ(sma.get_value(), 30.3);
}

TEST(EMATests, CalculatesExponentialSmoothing)
{
    EMA ema{3};

    ema.update(10.0);
    EXPECT_FALSE(ema.is_ready());
    EXPECT_DOUBLE_EQ(ema.get_value(), 10.0);

    ema.update(20.0);
    EXPECT_FALSE(ema.is_ready());
    EXPECT_DOUBLE_EQ(ema.get_value(), 15.0);

    ema.update(30.0);
    EXPECT_TRUE(ema.is_ready());
    EXPECT_DOUBLE_EQ(ema.get_value(), 22.5);
}

TEST(RSITests, CalculatesRelativeStrength)
{
    RSI rsi{2};

    rsi.update(10.0);
    EXPECT_FALSE(rsi.is_ready());

    rsi.update(12.0);
    EXPECT_TRUE(rsi.is_ready());
    EXPECT_DOUBLE_EQ(rsi.get_value(), 100.0);

    rsi.update(9.0);
    EXPECT_TRUE(rsi.is_ready());
    EXPECT_NEAR(rsi.get_value(), 25.0, 1e-5);
}

TEST(BollingerTests, CalculatesRollingVariance)
{
    BollingerBands bb{3};

    bb.update(10.0);
    EXPECT_FALSE(bb.is_ready());

    bb.update(20.0);
    EXPECT_FALSE(bb.is_ready());

    bb.update(30.0);
    EXPECT_TRUE(bb.is_ready());
    EXPECT_DOUBLE_EQ(bb.get_middle(), 20.0);
    EXPECT_NEAR(bb.get_upper(), 36.3299, 1e-4);
    EXPECT_NEAR(bb.get_lower(), 3.6701, 1e-4);

    bb.update(40.0);
    EXPECT_TRUE(bb.is_ready());
    EXPECT_DOUBLE_EQ(bb.get_middle(), 30.0);
    EXPECT_NEAR(bb.get_upper(), 46.3299, 1e-4);
    EXPECT_NEAR(bb.get_lower(), 13.6701, 1e-4);
}