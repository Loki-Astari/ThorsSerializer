#ifndef THORSANVIL_SLACK_BLOCKKIT_H
#define THORSANVIL_SLACK_BLOCKKIT_H

#include "Traits.h"
#include "SerUtil.h"

#include <string>
#include <vector>

namespace ThorsAnvil::Slack::BlockKit
{

using OptString         = std::optional<std::string>;
using OptInt            = std::optional<int>;
using OptBool           = std::optional<bool>;

template<typename T>
using OptVector     = std::optional<std::vector<T>>;

// Section 1:
// Objects used by Blocks.
// See Blocks Below.
    struct ElActive
    {
        // see: https://docs.slack.dev/reference/block-kit/block-elements
    };
    using OptElActive  = std::optional<ElActive>;

    struct ElImg
    {
        // see: https://docs.slack.dev/reference/block-kit/block-elements/image-element
        // or   https://docs.slack.dev/reference/block-kit/composition-objects/text-object
    };

    struct ElBut
    {
        // see: https://docs.slack.dev/reference/block-kit/block-elements/feedback-buttons-element
        // or   https://docs.slack.dev/reference/block-kit/block-elements/icon-button-element
    };

    enum TextType { /*vera-ignore*/ plain_text, mrkdwn};
    struct ElText
    {
        // https://docs.slack.dev/reference/block-kit/composition-objects/text-object
        TextType                    type;           // Can be one of "plain_text" or "mrkdwn"
        std::string                 text;           // The text for the block. This field accepts any of the standard text formatting markup when type is mrkdwn. The minimum length is 1 and maximum length is 3000 characters.
        OptBool                     emoji;          // Indicates whether emojis in a text field should be escaped into the colon emoji format. This field is only usable when type is plain_text.
        OptBool                     verbatim;       // When set to false (as is default) URLs will be auto-converted into links, conversation names will be link-ified, and certain mentions will be automatically parsed.
                                                    // When set to true, Slack will continue to process all markdown formatting and manual parsing strings, but it won’t modify any plain-text content. For example, channel names will not be hyperlinked.
                                                    // This field is only usable when type is mrkdwn.
    };
    using OptElText     = std::optional<ElText>;
    using OptElTexts    = std::optional<std::vector<ElText>>;

    struct ElSlackFile
    {
        // https://docs.slack.dev/reference/block-kit/composition-objects/slack-file-object
        OptString                   url;            // This URL can be the url_private or the permalink of the Slack file.
        OptString                   id;             // Slack ID of the file.
    };
    using OptElSlackFile  = std::optional<ElSlackFile>;

    struct ElInput
    {
        // One of:
        // https://docs.slack.dev/reference/block-kit/block-elements/checkboxes-element/
        // https://docs.slack.dev/reference/block-kit/block-elements/date-picker-element/
        // https://docs.slack.dev/reference/block-kit/block-elements/datetime-picker-element/
        // https://docs.slack.dev/reference/block-kit/block-elements/email-input-element/
        // https://docs.slack.dev/reference/block-kit/block-elements/file-input-element/
        // https://docs.slack.dev/reference/block-kit/block-elements/multi-select-menus-element
        // https://docs.slack.dev/reference/block-kit/block-elements/number-input-element/
        // https://docs.slack.dev/reference/block-kit/block-elements/plain-text-input-element/
        // https://docs.slack.dev/reference/block-kit/block-elements/radio-button-element
        // https://docs.slack.dev/reference/block-kit/block-elements/rich-text-input-element/
        // https://docs.slack.dev/reference/block-kit/block-elements/select-menu-element/
        // https://docs.slack.dev/reference/block-kit/block-elements/time-picker-element/
        // https://docs.slack.dev/reference/block-kit/block-elements/url-input-element/
    };

    struct InfoStyle
    {
         OptBool    bold;
         OptBool    italic;
         OptBool    strike;
         OptBool    highlight;
         OptBool    client_highlight;
         OptBool    unlink;
    };
    struct InfoText
    {
        bool    bold;
        bool    italic;
        bool    strike;
        bool    code;
    };
    using OptInfoStyle = std::optional<InfoStyle>;
    using OptInfoText = std::optional<InfoText>;

    enum BroadcastType {/*vera-ignore*/here, channel, everyone};
    struct ElRtBroadcast
    {
        BroadcastType       range;      // The range of the broadcast; value can be here, channel, or everyone.
                                        // Using here notifies only the active members of a channel; channel notifies all members of a channel;
                                        // everyone notifies every person in the #general channel.
        ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::ElRtBroadcast, broadcast);
        ThorsAnvil_TypeFieldName(type);
    };
    struct ElRtColor
    {
        std::string         value;      // The hex value for the color.
        ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::ElRtColor, color);
        ThorsAnvil_TypeFieldName(type);
    };
    struct ElRtChannel
    {
        std::string         channel_id; // The ID of the channel to be mentioned.
        OptInfoStyle        style;      // An object of six optional boolean properties that dictate style: bold, italic, strike, highlight, client_highlight, and unlink.
        ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::ElRtChannel, channel);
        ThorsAnvil_TypeFieldName(type);
    };
    struct ElRtDate
    {
        std::time_t         timestamp;  // A Unix timestamp for the date to be displayed in seconds.
        std::string         format;     // A template string containing curly-brace-enclosed tokens to substitute your provided timestamp. See details below.
        OptString           url;        // URL to link the entire format string to.
        OptString           fallback;   // Text to display in place of the date should parsing, formatting or displaying fail.
        ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::ElRtDate, date);
        ThorsAnvil_TypeFieldName(type);
    };
    struct ElRtEmoji
    {
        std::string         name;       // The name of the emoji; i.e. "wave" or "wave::skin-tone-2".
        OptString           unicode;    // Represents the unicode code point of the emoji, where applicable.
        ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::ElRtEmoji, emoji);
        ThorsAnvil_TypeFieldName(type);
    };
    struct ElRtLink
    {
        std::string         url;        // The link's url.
        OptElText           text;       // The text shown to the user (instead of the url). If no text is provided, the url is used.
        OptBool             unsafe;     // Indicates whether the link is safe.
        OptInfoText         style;      // An object containing four boolean properties: bold, italic, strike, and code.
        ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::ElRtLink, link);
        ThorsAnvil_TypeFieldName(type);
    };
    struct ElRtText
    {
        std::string         text;       // The text shown to the user.
        OptInfoText         style;      // An object containing four boolean fields, none of which are required: bold, italic, strike, and code.
        ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::ElRtText, text);
        ThorsAnvil_TypeFieldName(type);
    };
    struct ElRtUser
    {
        std::string         user_id;    // The ID of the user to be mentioned.
        OptInfoStyle        style;      // An object of six optional boolean properties that dictate style: bold, italic, strike, highlight, client_highlight, and unlink.
        ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::ElRtUser, user);
        ThorsAnvil_TypeFieldName(type);
    };
    struct ElRtUserGroup
    {
        std::string         usergroup_id;   // The ID of the user group to be mentioned.
        OptInfoStyle        style;          // An object of six optional boolean properties that dictate style: bold, italic, strike, highlight, client_highlight, and unlink.
        ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::ElRtUserGroup, usergroup);
        ThorsAnvil_TypeFieldName(type);
    };
    using RtElement = std::variant<ElRtBroadcast, ElRtColor, ElRtChannel, ElRtDate, ElRtEmoji, ElRtLink, ElRtText, ElRtUser, ElRtUserGroup>;
    using VecRtElement = std::vector<RtElement>;
    struct RichTextSection
    {
        VecRtElement            elements;
        ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::RichTextSection, rich_text_section);
        ThorsAnvil_TypeFieldName(type);
    };
    using VecRichTextSection = std::vector<RichTextSection>;
    enum ListType {/*vera-ignore*/bullet, ordered};
    struct RichTextList
    {
        ListType                style;      // Either "bullet" or "ordered"
        VecRichTextSection      elements;   // An array of rich_text_section objects containing two properties: type, which is "rich_text_section", and elements, which is an array of rich text element objects.
        OptInt                  indent;     // Number of pixels to indent the list.
        OptInt                  offset;     // Number to offset the first number in the list. For example, if the offset = 4, the first number in the ordered list would be 5.
        OptInt                  border;     // Number of pixels of border thickness.
        ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::RichTextList, rich_text_list);
        ThorsAnvil_TypeFieldName(type);
    };
    struct RichTextPreformatted
    {
        VecRtElement            elements;   // An array of rich text elements.
        OptInt                  border;     // Number of pixels of border thickness.
        ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::RichTextPreformatted, rich_text_preformatted);
        ThorsAnvil_TypeFieldName(type);
    };
    struct RichTextQuote
    {
        VecRtElement            elements;   // An array of rich text elements.
        OptInt                  border;     // Number of pixels of border thickness.
        ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::RichTextQuote, rich_text_quote);
        ThorsAnvil_TypeFieldName(type);
    };
    using ElRichTextObj = std::variant<RichTextSection, RichTextList, RichTextPreformatted, RichTextQuote>;
    using VecElRichTextObj = std::vector<ElRichTextObj>;

    struct ElRow
    {
    };

    struct ElColInfo
    {
    };

// Section 2:
// Different Types of Blocks
struct Actions
{
    // https://docs.slack.dev/reference/block-kit/blocks/actions-block/
    //std::string                 type;           // always "actions"
    std::vector<ElActive>       elements;       // Max 25 elements.
                                                // An array of interactive element objects - buttons, select menus, overflow menus, or date pickers.
    OptString                   block_id;
    ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::Actions, actions);
    ThorsAnvil_TypeFieldName(type);
};
struct Context
{
    // https://docs.slack.dev/reference/block-kit/blocks/context-block/
    //std::string                 type;           // always "context"
    std::vector<ElImg>          elements;       // Max 10 elements
                                                // An array of image elements and text objects.
    OptString                   block_id;
    ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::Context, context);
    ThorsAnvil_TypeFieldName(type);
};
struct Context_Actions
{
    // https://docs.slack.dev/reference/block-kit/blocks/context-actions-block/
    //std::string                 type;           // always "context_actions"
    std::vector<ElBut>          elements;       // Max 5 elements.
                                                // An array of feedback buttons elements and icon button elements.
    OptString                   block_id;
    ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::Context_Actions, context_actions);
    ThorsAnvil_TypeFieldName(type);
};
struct Divider
{
    // https://docs.slack.dev/reference/block-kit/blocks/divider-block/
    //std::string                 type;           // always "divider"
    OptString                   block_id;
    ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::Divider, divider);
    ThorsAnvil_TypeFieldName(type);
};
struct File
{
    // https://docs.slack.dev/reference/block-kit/blocks/file-block/
    //std::string                 type;           // always "file"
    std::string                 external_id;    // The external unique ID for this file.
    std::string                 source;         // At the moment, source will always be remote for a remote file.
    OptString                   block_id;
    ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::File, file);
    ThorsAnvil_TypeFieldName(type);
};
struct Header
{
    // https://docs.slack.dev/reference/block-kit/blocks/header-block/
    //std::string                 type;           // always "header"
    ElText               text;           // The text for the block, in the form of a plain_text text object. Maximum length for the text in this field is 150 characters.
    OptString                   block_id;
    ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::Header, header);
    ThorsAnvil_TypeFieldName(type);
};
struct Image
{
    // https://docs.slack.dev/reference/block-kit/blocks/image-block/
    //std::string                 type;           // always "image"
    std::string                 alt_text;       // A plain-text summary of the image. This should not contain any markup. Maximum length for this field is 2000 characters.
    OptString                   image_url;      // The URL for a publicly hosted image. You must provide either an image_url or slack_file. Maximum length for this field is 3000 characters.
    OptElSlackFile              slack_file;     // A Slack image file object that defines the source of the image.
    OptElText                   title;          // An optional title for the image in the form of a text object that can only be of type: plain_text. Maximum length for the text in this field is 2000 characters.
    OptString                   block_id;
    ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::Image, image);
    ThorsAnvil_TypeFieldName(type);
};
struct Input
{
    // https://docs.slack.dev/reference/block-kit/blocks/input-block/
    //std::string                 type;           // always "input".
    ElText                      label;          // A label that appears above an input element in the form of a text object that must have type of plain_text. Maximum length for the text in this field is 2000 characters.
    ElInput                     element;        // A block element. See above for full list.
    OptBool                     dispatch_action;// A boolean that indicates whether or not the use of elements in this block should dispatch a block_actions payload.
                                                // Defaults to false.
                                                // This field is incompatible with the file_input block element. If dispatch_action is set to true and a file_input block element is provided, an unsupported type error will be raised.
    OptString                   block_id;
    OptElText                   hint;           // An optional hint that appears below an input element in a lighter grey. It must be a text object with a type of plain_text. Maximum length for the text in this field is 2000 characters.
    OptBool                     optional;       // A boolean that indicates whether the input element may be empty when a user submits the modal.
                                                // Defaults to false.
    ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::Input, input);
    ThorsAnvil_TypeFieldName(type);
};
struct Markdown
{
    // https://docs.slack.dev/reference/block-kit/blocks/markdown-block/
    //std::string                 type;           // always "markdown"
    std::string                 text;           // The standard markdown-formatted text. Limit 12,000 characters max.
    OptString                   block_id;
    ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::Markdown, markdown);
    ThorsAnvil_TypeFieldName(type);
};
struct RichText
{
    // https://docs.slack.dev/reference/block-kit/blocks/rich-text-block/
    //std::string                 type;           // always "rich_text"
    VecElRichTextObj            elements;       // An array of rich text objects - rich_text_section, rich_text_list, rich_text_preformatted, and rich_text_quote. See your specific desired element below for more details.
    OptString                   block_id;
    ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::RichText, rich_text);
    ThorsAnvil_TypeFieldName(type);
};
struct Section
{
    // https://docs.slack.dev/reference/block-kit/blocks/section-block/
    //std::string                 type;           // always "section"
    // Preferred
    OptElText                   text;           // The text for the block, in the form of a text object. Minimum length for the text in this field is 1 and maximum length is 3000 characters.
                                                // This field is not required if a valid array of fields objects is provided instead.
    // Maybe: Alternative to text
    OptElTexts                  fields;         // Required if no text is provided. An array of text objects. Any text objects included with fields will be rendered in a compact format that allows for 2 columns of side-by-side text.
                                                // Maximum number of items is 10. Maximum length for the text in each item is 2000 characters.
    OptString                   block_id;
    OptElActive                 accessory;      // One of the compatible element objects noted above. Be sure to confirm the desired element works with section.
    OptBool                     expand;         // Whether or not this section block's text should always expand when rendered.
                                                // If false or not provided, it may be rendered with a 'see more' option to expand and show the full text.
                                                // For AI Assistant apps, this allows the app to post long messages without users needing to click 'see more' to expand the message.
    ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::Section, section);
    ThorsAnvil_TypeFieldName(type);
};
struct Table
{
    // https://docs.slack.dev/reference/block-kit/blocks/table-block/
    //std::string                 type;           // Always "table".
    OptString                   block_id;
    std::vector<ElRow>          rows;           // An array consisting of table rows.
                                                // Maximum 100 rows.
                                                // Each row object is an array with a max of 20 table cells. Table cells can have a type of raw_text or rich_text.
    OptVector<ElColInfo>        column_settings;// An array describing column behavior.
                                                // If there are fewer items in the column_settings array than there are columns in the table, then the items in the the column_settings array will
                                                // describe the same number of columns in the table as there are in the array itself. Any additional columns will have the default behavior.
                                                // Maximum 20 items. See below for column settings schema.
    ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::Table, table);
    ThorsAnvil_TypeFieldName(type);
};
struct Video
{
    // https://docs.slack.dev/reference/block-kit/blocks/video-block/
    //std::string                 type;           // always "video"
    std::string                 alt_text;       // A tooltip for the video. Required for accessibility
    OptString                   author_name;    // Author name to be displayed. Must be less than 50 characters.
    OptString                   block_id;
    OptElText                   description;    // Description for video in the form of a text object that must have type of plain_text. text within must be less than 200 characters.
    OptString                   provider_icon_url; // Icon for the video provider, e.g. YouTube icon.
    OptString                   provider_name;  // The originating application or domain of the video, e.g. YouTube.
    ElText                      title;          // Video title in the form of a text object that must have type of plain_text. text within must be less than 200 characters.
    OptString                   title_url;      // Hyperlink for the title text. Must correspond to the non-embeddable URL for the video. Must go to an HTTPS URL.
    std::string                 thumbnail_url;  // The thumbnail image URL
    std::string                 video_url;      // The URL to be embedded. Must match any existing unfurl domains within the app and point to a HTTPS URL.
    ThorsAnvil_VariantSerializerWithName(ThorsAnvil::Slack::BlockKit::Video, video);
    ThorsAnvil_TypeFieldName(type);
};

using Block = std::variant<Actions, Context, Context_Actions, Divider, File, Header, Image, Input, Markdown, RichText, Section, Table, Video>;
using Blocks = std::vector<Block>;
using OptBlocks = std::optional<Blocks>;

}

ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElActive);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElImg);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElBut);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElText, type, text, emoji, verbatim);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElSlackFile, url, id);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElInput);
// -- Rich Text
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::InfoStyle, bold, italic, strike, highlight, client_highlight, unlink);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::InfoText, bold, italic, strike, code);
// ---
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElRtBroadcast, range);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElRtColor, value);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElRtChannel, channel_id, style);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElRtDate, timestamp, format, url, fallback);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElRtEmoji, name, unicode);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElRtLink, url, text, unsafe, style);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElRtText, text, style);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElRtUser, user_id, style);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElRtUserGroup, usergroup_id, style);
//---
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::RichTextSection, elements);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::RichTextList, style, elements, indent, offset, border);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::RichTextPreformatted, elements, border);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::RichTextQuote, elements, border);
// -- Rich Text
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElRow);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::ElColInfo);
/// ----
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::Actions, elements);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::Context, elements);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::Context_Actions, elements);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::Divider);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::File, external_id, source);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::Header, text);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::Image, alt_text, image_url, slack_file, title);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::Input, label, element, dispatch_action, hint, optional);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::Markdown, text);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::RichText, elements);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::Section, text, fields, accessory, expand);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::Table, rows, column_settings);
ThorsAnvil_MakeTrait(ThorsAnvil::Slack::BlockKit::Video, alt_text, author_name, description, provider_icon_url, provider_name, title, title_url, thumbnail_url, video_url);


#endif
