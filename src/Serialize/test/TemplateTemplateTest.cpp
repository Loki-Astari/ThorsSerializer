#include "gtest/gtest.h"
#include "Traits.h"
#include "JsonThor.h"


template<typename T>
struct Time
{
    T   time;
};

struct SetDate
{
    std::string     type = "date";
};
struct SetTimeStamp
{
    std::string     type = "timestamp";
};

template<typename T>
concept IsDateType = requires {T::type;};

template<template<typename> typename T, typename L>
struct CurrentDate
{
    T<L>    currentDate;
};


ThorsAnvil_Template_MakeTrait(1, Time, time);
ThorsAnvil_MakeTrait(SetDate, type);
ThorsAnvil_MakeTrait(SetTimeStamp, type);
// Notice the TT here.
//  This indicates that the first template parameter is a template.
//  That can take a single parameter.
ThorsAnvil_TTemplate_MakeTrait(2, CurrentDate, currentDate);

TEST(TemplateTemplateTest, SerializeATemplateTemplateDate)
{
    using ThorsAnvil::Serialize::jsonExporter;
    using ThorsAnvil::Serialize::OutputType;
    using ThorsAnvil::Serialize::PrinterConfig;

    CurrentDate<Time, SetDate>  time;
    std::stringstream   stream;
    stream << jsonExporter(time, PrinterConfig{OutputType::Stream});

    EXPECT_EQ(R"({"currentDate":{"time":{"type":"date"}}})", stream.str());
}
TEST(TemplateTemplateTest, SerializeATemplateTemplateTimeStamp)
{
    using ThorsAnvil::Serialize::jsonExporter;
    using  ThorsAnvil::Serialize::OutputType;
    using  ThorsAnvil::Serialize::PrinterConfig;

    CurrentDate<Time, SetTimeStamp>  time;
    std::stringstream   stream;
    stream << jsonExporter(time, PrinterConfig{OutputType::Stream});

    EXPECT_EQ(R"({"currentDate":{"time":{"type":"timestamp"}}})", stream.str());
}


