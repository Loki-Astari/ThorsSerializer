
#ifndef THORSANVIL_BINARY_REP_TEST_TEST_UTIL_H
#define THORSANVIL_BINARY_REP_TEST_TEST_UTIL_H

template<typename T>
void checkValue(T const& value, std::string const& expected)
{
    std::stringstream   stream;
    stream.write(reinterpret_cast<char const*>(&value), sizeof(T));

    std::string         result(sizeof(T), '\x00');
    stream.read(&result[0], sizeof(T));

    EXPECT_EQ(sizeof(T), expected.size());

    for(int loop = 0;loop < expected.size(); ++loop)
    {   EXPECT_EQ(expected[loop], result[loop]);
    }
}

#endif

