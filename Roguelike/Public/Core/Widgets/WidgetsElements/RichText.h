#pragma once

#include <Core/Widgets/WidgetsElements/Widget.h>
#include <Core/Utility/Struct.h>

#include <string>
#include <vector>
#include <cstddef>


enum class ERichTeg
{
    None,
    Color,
    Size
};

struct FRichTextStyle
{
    EWidgetVerticalAlignment VerticalAlignment = EWidgetVerticalAlignment::Top;
    EWidgetHorizontalAlignment HorizontalAlignment = EWidgetHorizontalAlignment::Left;

    int LineSpacing = 2;
};

struct FRichTextStringStyle
{
    std::vector<FRichTextSigmentStyle> StringStyle;
};


class WRichText : public WWidget
{
public:
    WRichText(const std::string& Text, const FRichTextStyle& Style = FRichTextStyle());
    WRichText(const std::string& Text, Rectangle& Bound, const FRichTextStyle& Style = FRichTextStyle());
    WRichText(const std::string& Text, Vector2& Location, const FRichTextStyle& Style = FRichTextStyle());

    ~WRichText() override = default;

    void UpdateText(const std::string& Text);
    void ValidateLayout();

protected:
    virtual void Draw() override;
    virtual void Construction() override {};
    virtual Vector2 AutoSize() override;

private:
    struct FLayoutPart
    {
        std::string Text;
        std::size_t SegmentIndex = 0;
        int TextSize = 0;
        int Width = 0;
    };

    struct FLayoutLine
    {
        std::vector<FLayoutPart> Parts;
        int Width = 0;
        int Height = 0;
    };

    ERichTeg CheckTeg(const std::string& TegText);

    Color CheckColorTegValue(const std::string& TegValueText);

    void AppendText(const std::string& Text, const FRichTextSigmentStyle& Style);

    bool ApplyTag(const std::string& TagText, FRichTextSigmentStyle& CurrentStyle);

    bool ApplyTagPart(const std::string& TagPart, FRichTextSigmentStyle& CurrentStyle);

    std::vector<FRichTextStringStyle> GetStringsStyle(std::vector<FRichTextSigmentStyle> Sigments);

    void MarkLayoutDirty();
    void RebuildLayout();

    std::vector<FRichTextStringStyle> RichTextStringsSyle;

    std::vector<FRichTextSigmentStyle> RichTextSigments;
    FRichTextStyle RichTextStyle;
    int MaxStringLenghts = -1;

    std::vector<FLayoutLine> CachedLayoutLines;
    int CachedMaxLineWidth = 0;
    bool bLayoutDirty = true;
};