#include "gtest/gtest.h"
#include <bowling.h>

TEST(Bowling, Testcase1)
{
    std::string str="12121212121212121212";
    Bowling* line = new Bowling(str.c_str());
    EXPECT_EQ (30, line->processLine());
    delete line;
}

TEST(Bowling, Spares1)
{
    std::string str="5/5/5/5/5/5/5/5/5/5/5";
    Bowling* line = new Bowling(str.c_str());
    EXPECT_EQ (150, line->processLine());
    delete line;
}

TEST(Bowling, Spares2)
{
    std::string str="6/6/6/6/6/6/6/6/6/6/6";
    Bowling* line = new Bowling(str.c_str());
    EXPECT_EQ (160, line->processLine());
    delete line;
}

TEST(Bowling, Strikes1)
{
    std::string str="------------------XXX";
    Bowling* line = new Bowling(str.c_str());
    EXPECT_EQ (30, line->processLine());
    delete line;
}

TEST(Bowling, Strikes2)
{
    std::string str="----------------XXXX";
    Bowling* line = new Bowling(str.c_str());
    EXPECT_EQ (60, line->processLine());
    delete line;
}

TEST(Bowling, FullStrike)
{
    std::string str="XXXXXXXXXXXX";
    Bowling* line = new Bowling(str.c_str());
    EXPECT_EQ (300, line->processLine());
    delete line;
}

TEST(Bowling, WowUBad)
{
    std::string str="--X---------5---/--";
    Bowling* line = new Bowling(str.c_str());
    EXPECT_EQ (25, line->processLine());
    delete line;
}

TEST(Bowling, WowUTerrible)
{
    std::string str="--------------------";
    Bowling* line = new Bowling(str.c_str());
    EXPECT_EQ (0, line->processLine());
    delete line;
}

TEST(Bowling, TestTooLong1)
{
    std::string str="5/5/5/5/5/5/5/5/5/5/5/";
    Bowling* line = new Bowling(str.c_str());
    EXPECT_EQ (-1, line->processLine());
    delete line;
}

TEST(Bowling, TestTooShort1)
{
    std::string str="5/5/5/5/5/";
    Bowling* line = new Bowling(str.c_str());
    EXPECT_EQ (-1, line->processLine());
    delete line;
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
