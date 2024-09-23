#include "SerializeConfig.h"
#include "SerUtil.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "test/TwitterTest.h"
#include "test/CountryTest.h"
#include "test/CatalogTest.h"
#include <fstream>
#include <chrono>

TEST(JsonBenchmarkPerfTest, parse)
{
    using ThorsAnvil::Serialize::ParseType;
    std::ifstream           twitter("test/data/twitter.json");
    std::ifstream           country("test/data/canada.json");
    std::ifstream           catalog("test/data/citm_catalog.json");

    std::string             twitterData;
    std::string             countryData;
    std::string             catalogData;
    std::getline(twitter, twitterData, static_cast<char>(-1));
    std::getline(country, countryData, static_cast<char>(-1));
    std::getline(catalog, catalogData, static_cast<char>(-1));
    ThorsAnvil::Serialize::ParserConfig  config{ThorsAnvil::Serialize::ParserConfig{}.setCatchExceptions(false)};

    auto start = std::chrono::high_resolution_clock::now();
    for (int loop = 0; loop < 10; ++loop)
    {
        TwitterTest::Twitter    twitterValue;
        CountryTest::Country    countryValue;
        CatalogTest::Perform    catalogValue;

        twitterData >> ThorsAnvil::Serialize::jsonImporter(twitterValue, config);
        countryData >> ThorsAnvil::Serialize::jsonImporter(countryValue, config);
        catalogData >> ThorsAnvil::Serialize::jsonImporter(catalogValue, config);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cerr << "Time: Parse:     " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
}

TEST(JsonBenchmarkPerfTest, stringify)
{
    using ThorsAnvil::Serialize::ParseType;
    std::ifstream           twitter("test/data/twitter.json");
    std::ifstream           country("test/data/canada.json");
    std::ifstream           catalog("test/data/citm_catalog.json");

    std::string             twitterData;
    std::string             countryData;
    std::string             catalogData;
    std::getline(twitter, twitterData, static_cast<char>(-1));
    std::getline(country, countryData, static_cast<char>(-1));
    std::getline(catalog, catalogData, static_cast<char>(-1));

    TwitterTest::Twitter    twitterValue;
    CountryTest::Country    countryValue;
    CatalogTest::Perform    catalogValue;

    ThorsAnvil::Serialize::ParserConfig  config{ThorsAnvil::Serialize::ParserConfig{}.setCatchExceptions(false)};
    ThorsAnvil::Serialize::PrinterConfig configOut{ThorsAnvil::Serialize::PrinterConfig{}.setOutputType(ThorsAnvil::Serialize::OutputType::Stream)};

    twitterData >> ThorsAnvil::Serialize::jsonImporter(twitterValue, config);
    countryData >> ThorsAnvil::Serialize::jsonImporter(countryValue, config);
    catalogData >> ThorsAnvil::Serialize::jsonImporter(catalogValue, config);

    auto start = std::chrono::high_resolution_clock::now();
    for (int loop = 0; loop < 10; ++loop)
    {
        std::string twitterOut;
        std::string countryOut;
        std::string catalogOut;

        twitterOut << ThorsAnvil::Serialize::jsonExporter(twitterValue, configOut);
        countryOut << ThorsAnvil::Serialize::jsonExporter(countryValue, configOut);
        catalogOut << ThorsAnvil::Serialize::jsonExporter(catalogValue, configOut);

    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cerr << "Time: Stringify: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
}

TEST(JsonBenchmarkPerfTest, pritify)
{
    using ThorsAnvil::Serialize::ParseType;
    std::ifstream           twitter("test/data/twitter.json");
    std::ifstream           country("test/data/canada.json");
    std::ifstream           catalog("test/data/citm_catalog.json");

    std::string             twitterData;
    std::string             countryData;
    std::string             catalogData;
    std::getline(twitter, twitterData, static_cast<char>(-1));
    std::getline(country, countryData, static_cast<char>(-1));
    std::getline(catalog, catalogData, static_cast<char>(-1));

    TwitterTest::Twitter    twitterValue;
    CountryTest::Country    countryValue;
    CatalogTest::Perform    catalogValue;

    ThorsAnvil::Serialize::ParserConfig  config{ThorsAnvil::Serialize::ParserConfig{}.setCatchExceptions(false)};
    ThorsAnvil::Serialize::PrinterConfig configOut{ThorsAnvil::Serialize::PrinterConfig{}.setOutputType(ThorsAnvil::Serialize::OutputType::Default)};

    twitterData >> ThorsAnvil::Serialize::jsonImporter(twitterValue, config);
    countryData >> ThorsAnvil::Serialize::jsonImporter(countryValue, config);
    catalogData >> ThorsAnvil::Serialize::jsonImporter(catalogValue, config);

    auto start = std::chrono::high_resolution_clock::now();
    for (int loop = 0; loop < 10; ++loop)
    {
        std::string twitterOut;
        std::string countryOut;
        std::string catalogOut;

        twitterOut << ThorsAnvil::Serialize::jsonExporter(twitterValue, configOut);
        countryOut << ThorsAnvil::Serialize::jsonExporter(countryValue, configOut);
        catalogOut << ThorsAnvil::Serialize::jsonExporter(catalogValue, configOut);

    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cerr << "Time: Stringify: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
}

