#ifndef THORSANVIL_SLACK_API_CHAT_H
#define THORSANVIL_SLACK_API_CHAT_H

#include "Traits.h"
#include "SerUtil.h"
#include "test/SlackBlockKit.h"

#include <string>
#include <vector>

namespace ThorsAnvil::Slack::API::Chat
{

using OptString         = std::optional<std::string>;
struct BotIcon
{
    std::string                 image_36;
    std::string                 image_48;
    std::string                 image_72;
};
struct BotProfile
{
    std::string                 id;
    std::string                 app_id;
    std::string                 user_id;
    std::string                 name;
    BotIcon                     icons;
    bool                        deleted;
    std::time_t                 updated;
    std::string                 team_id;
};

struct Message
{
    std::string                 user;
    std::string                 type;
    std::string                 ts;
    std::string                 bot_id;
    std::string                 app_id;
    std::string                 text;
    std::string                 team;
    BotProfile                  bot_profile;
    BlockKit::Blocks            blocks;
};

struct PostMessageReply
{
    bool                        ok;
    OptString                   error;
    OptString                   warning;
    OptString                   channel;
    OptString                   ts;
    Message                     message;
};

struct PostMessage
{
    static const std::string api;
    static constexpr bool hasBody = true;
    using Reply = PostMessageReply;
    std::string                 channel;
    OptString                   text;
    BlockKit::OptBlocks         blocks;
    OptString                   icon_emoji;
    OptString                   username;
    OptString                   thread_ts;
};


}

ThorsAnvil_MakeTrait(ThorsAnvil::Slack::API::Chat::BotIcon, image_36, image_48, image_72);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::API::Chat::BotProfile, id, app_id, user_id, name, icons, deleted, updated, team_id);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::API::Chat::Message, user, type, ts, bot_id, app_id, text, team, bot_profile, blocks);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::API::Chat::PostMessageReply, ok, error, channel, ts, message);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::API::Chat::PostMessage, channel, text, blocks, icon_emoji, username, thread_ts);

#endif
