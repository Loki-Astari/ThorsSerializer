#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <memory>
#include <iostream>

enum class ENUM : std::uint8_t {AAAAA, BBBBB, CCCCC};
struct CLASS {
    ENUM val = ENUM::AAAAA;
    int y =5;
};

ThorsAnvil_MakeEnum(ENUM, AAAAA, BBBBB, CCCCC);
ThorsAnvil_MakeTrait(CLASS, val, y);

TEST(Issue78Test, ThorwOnInvalidEnumDeSerializationOriginalEnum)
{
    using ThorsAnvil::Serialize::jsonExporter;

    auto action = []() {
        ThorsAnvil::Serialize::PrinterConfig config;
        config.catchExceptions = false;

        CLASS a;
        a.val = static_cast<ENUM>(5);

        std::stringstream output;
        output << jsonExporter(a, config);

        std::cerr << "Issue78: ERROR " << output.str() << "\n";
    };

    EXPECT_THROW(
        action(),
        std::runtime_error
    );
}

enum class ENUMWithMagic : std::uint8_t {AAAAA, BBBBB, CCCCC};
struct CLASSWithMagic {
    ENUMWithMagic val = ENUMWithMagic::AAAAA;
    int y =5;
};

ThorsAnvil_MakeTrait(CLASSWithMagic, val, y);

TEST(Issue78Test, ThorwOnInvalidEnumDeSerializationMagicEnum)
{
    using ThorsAnvil::Serialize::jsonExporter;

    auto action = []() {
        ThorsAnvil::Serialize::PrinterConfig config;
        config.catchExceptions = false;

        CLASSWithMagic a;
        a.val = static_cast<ENUMWithMagic>(5);

        std::stringstream output;
        output << jsonExporter(a, config);

        std::cerr << "Issue78: ERROR: " << output.str() << "\n";
    };

    EXPECT_THROW(
        action(),
        std::runtime_error
    );
}

TEST(Issue78Test, EnumDeSerializationMagicEnum)
{
    using ThorsAnvil::Serialize::jsonExporter;

    ThorsAnvil::Serialize::PrinterConfig config;
    config.characteristics = ThorsAnvil::Serialize::OutputType::Stream;
    config.catchExceptions = false;

    CLASSWithMagic a;

    std::stringstream output;
    output << jsonExporter(a, config);

    std::cerr << "Issue78: " << output.str() << "\n";

    EXPECT_EQ(R"({"val":"AAAAA","y":5})", output.str());
}


