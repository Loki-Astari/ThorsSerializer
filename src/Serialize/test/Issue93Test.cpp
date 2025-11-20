#include <sstream>
#include "JsonThor.h"
#include "gtest/gtest.h"

#include "SlackAPI_Chat.h"
#include "SlackBlockKit.h"


namespace Chat = ThorsAnvil::Slack::API::Chat;
namespace BK = ThorsAnvil::Slack::BlockKit;

ThorsAnvil::Serialize::PrinterConfig streamConfig{ThorsAnvil::Serialize::OutputType::Stream};

TEST(Issue93Test, RichTextPostMessage)
{
    Chat::PostMessage message{
        .channel = "C09RU2URYMS",
        .blocks = BK::Blocks{
            BK::RichText{
                .elements = {
                    BK::RichTextList{
                        .style = BK::ordered,
                        .elements = {
                            BK::RichTextSection{
                                .elements = {
                                    BK::ElRtText{
                                        .text = "Hi there",
                                        .style = BK::InfoText{true,true,true,true}
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    };


    std::stringstream       output;
    output << ThorsAnvil::Serialize::jsonExporter(message, streamConfig);
    std::cout << output.str() << "\n";
    std::size_t  size = ThorsAnvil::Serialize::jsonStreanSize(message);

    EXPECT_EQ(size, output.str().size());
}

TEST(Issue93Test, ElRtTextNoStyle)
{
    BK::ElRtText    text{
        .text = "Hi there"
    };

    std::stringstream       output;
    output << ThorsAnvil::Serialize::jsonExporter(text, streamConfig);
    std::cout << output.str() << "\n";
    std::size_t  size = ThorsAnvil::Serialize::jsonStreanSize(text);

    EXPECT_EQ(size, output.str().size());
}
TEST(Issue93Test, ElRtTextNoStyleInVariant)
{
    BK::RtElement    text{BK::ElRtText{
        .text = "Hi there"
    }};

    std::stringstream       output;
    output << ThorsAnvil::Serialize::jsonExporter(text, streamConfig);
    std::cout << output.str() << "\n";
    std::size_t  size = ThorsAnvil::Serialize::jsonStreanSize(text);

    EXPECT_EQ(size, output.str().size());
}
TEST(Issue93Test, ElRtTextWithStyle)
{
    BK::ElRtText    text{
        .text = "Hi there",
        .style = BK::InfoText{true,true,true,true}
    };

    std::stringstream       output;
    output << ThorsAnvil::Serialize::jsonExporter(text, streamConfig);
    std::cout << output.str() << "\n";
    std::size_t  size = ThorsAnvil::Serialize::jsonStreanSize(text);

    EXPECT_EQ(size, output.str().size());
}
