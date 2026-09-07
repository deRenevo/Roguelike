// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Widget/Widget.h"
#include "Core/Utility/Struct.h"

#include <string>
#include <vector>
#include <cstddef>

#include "Core/Math/Vector2D.h"


enum class ERichTag
{
    None,
    Color,
    Size
};

struct FRichTextStyle
{
    EWidgetVerticalAlignment VerticalAlignment = EWidgetVerticalAlignment::Top;
    EWidgetHorizontalAlignment HorizontalAlignment = EWidgetHorizontalAlignment::Left;

    int32 LineSpacing = 2;
};


class WRichText : public WWidget
{
public:
    WRichText(const std::string& Text, const FRichTextStyle& Style = FRichTextStyle());
    WRichText(const std::string& Text, const Rectangle& bound, const FRichTextStyle& Style = FRichTextStyle());
    WRichText(const std::string& Text, const FVector2D& location, const FRichTextStyle& Style = FRichTextStyle());

    ~WRichText() override = default;

    void UpdateText(const std::string& Text);
    void ValidateLayout();

protected:
    virtual void Draw() override;
    virtual void Construction() override {};
    virtual FVector2D AutoSize() override;

private:
    struct FLayoutPart
    {
        std::string Text;
        std::size_t SegmentIndex = 0;
        int32 TextSize = 0;
        int32 Width = 0;
    };

    struct FLayoutLine
    {
        std::vector<FLayoutPart> Parts;
        int32 Width = 0;
        int32 Height = 0;
    };

    static ERichTag CheckTag(const std::string& tagText);

    static Color CheckColorTagValue(const std::string& tagValueText);

    void AppendText(const std::string& text, const FRichTextSegmentStyle& style);

    static bool ApplyTag(const std::string& tagText, FRichTextSegmentStyle& currentStyle);

    static bool ApplyTagPart(const std::string& tagPart, FRichTextSegmentStyle& currentStyle);

    void MarkLayoutDirty();
    void RebuildLayout();

    std::vector<FRichTextSegmentStyle> RichTextSegments;
    FRichTextStyle RichTextStyle;
    int32 MaxStringLenghts = -1;

    std::vector<FLayoutLine> CachedLayoutLines;
    int32 CachedMaxLineWidth = 0;
    bool bLayoutDirty = true;
};