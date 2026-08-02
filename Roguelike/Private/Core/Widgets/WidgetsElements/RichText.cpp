#include <Core/Widgets/WidgetsElements/RichText.h>

#include <algorithm>
#include <cmath>
#include <cctype>
#include <string>
#include <vector>

namespace
{
    std::string Trim(const std::string& s)
    {
        size_t Start = 0;

        while (Start < s.size() && std::isspace(static_cast<unsigned char>(s[Start])))
            ++Start;

        size_t End = s.size();

        while (End > Start && std::isspace(static_cast<unsigned char>(s[End - 1])))
            --End;

        return s.substr(Start, End - Start);
    }

    std::string ToUpper(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
        {
            return static_cast<char>(std::toupper(c));
        });

        return s;
    }

    std::vector<std::string> SplitLines(const std::string& text)
    {
        std::vector<std::string> lines;
        std::string current;

        for (char c : text)
        {
            if (c == '\n')
            {
                lines.push_back(current);
                current.clear();
            }
            else if (c != '\r')
            {
                current.push_back(c);
            }
        }

        lines.push_back(current);
        return lines;
    }

    bool SameStyle(const FRichTextSigmentStyle& a, const FRichTextSigmentStyle& b)
    {
        return a.TextSize == b.TextSize &&
               a.TextColor.r == b.TextColor.r &&
               a.TextColor.g == b.TextColor.g &&
               a.TextColor.b == b.TextColor.b &&
               a.TextColor.a == b.TextColor.a;
    }
}

WRichText::WRichText(const std::string& Text, const FRichTextStyle& Style)
{
    RichTextStyle = Style;

    if (Text != "None")
    {
        UpdateText(Text);
    }
}

WRichText::WRichText(const std::string& Text, Rectangle& Bound, const FRichTextStyle& Style)
{
    SetBound(Bound);

    RichTextStyle = Style;

    if (Text != "None")
    {
        UpdateText(Text);
    }
}

WRichText::WRichText(const std::string& Text, Vector2& Location, const FRichTextStyle& Style)
{
    SetWorldLocation(Location);

    RichTextStyle = Style;

    if (Text != "None")
    {
        UpdateText(Text);
    }
}

void WRichText::UpdateText(const std::string& Text)
{
    RichTextSigments.clear();

    MaxStringLenghts = -1;

    if (Text == "None" || Text.empty())
    {
        MarkLayoutDirty();
        return;
    }

    FRichTextSigmentStyle CurrentStyle = FRichTextSigmentStyle();

    std::size_t i = 0;

    while (i < Text.size())
    {
        if (Text[i] != '[')
        {
            std::size_t NextTagStart = Text.find('[', i);

            if (NextTagStart == std::string::npos)
                NextTagStart = Text.size();

            AppendText(
                Text.substr(i, NextTagStart - i),
                CurrentStyle
            );

            i = NextTagStart;
            continue;
        }

        std::size_t CloseBracket = Text.find(']', i + 1);

        if (CloseBracket == std::string::npos)
        {
            AppendText(
                Text.substr(i),
                CurrentStyle
            );

            break;
        }

        std::string RawTag = Text.substr(i + 1, CloseBracket - i - 1);
        std::string Teg = Trim(RawTag);

        bool ParsedTag = ApplyTag(Teg, CurrentStyle);

        if (ParsedTag)
        {
            i = CloseBracket + 1;
        }
        else
        {
            AppendText(
                Text.substr(i, CloseBracket - i + 1),
                CurrentStyle
            );

            i = CloseBracket + 1;
        }
    }

    MarkLayoutDirty();
}
void WRichText::MarkLayoutDirty()
{
    bLayoutDirty = true;
}

void WRichText::ValidateLayout()
{
    if (bLayoutDirty)
    {
        RebuildLayout();
    }
}

void WRichText::RebuildLayout()
{
    CachedLayoutLines.clear();
    CachedMaxLineWidth = 0;

    if (RichTextSigments.empty())
    {
        MaxStringLenghts = 0;
        bLayoutDirty = false;
        return;
    }

    FLayoutLine CurrentLine;

    int LastTextSize = 0;

    auto PushCurrentLine = [&](int DefaultHeight)
    {
        if (CurrentLine.Height == 0)
            CurrentLine.Height = DefaultHeight;

        CachedLayoutLines.push_back(std::move(CurrentLine));
        CurrentLine = FLayoutLine();
    };

    for (std::size_t SegmentIndex = 0; SegmentIndex < RichTextSigments.size(); ++SegmentIndex)
    {
        const FRichTextSigmentStyle& Segment = RichTextSigments[SegmentIndex];

        if (Segment.Text.empty())
            continue;

        LastTextSize = Segment.TextSize;

        const std::vector<std::string> Lines = SplitLines(Segment.Text);

        for (std::size_t i = 0; i < Lines.size(); ++i)
        {
            if (i > 0)
            {
                PushCurrentLine(Segment.TextSize);
            }

            if (Lines[i].empty())
                continue;

            FLayoutPart Part;
            Part.Text = Lines[i];
            Part.SegmentIndex = SegmentIndex;
            Part.TextSize = Segment.TextSize;
            Part.Width = static_cast<int>(MeasureText(Lines[i].c_str(), Segment.TextSize));

            CurrentLine.Width += Part.Width;
            CurrentLine.Height = std::max(CurrentLine.Height, Segment.TextSize);

            CurrentLine.Parts.push_back(std::move(Part));
        }
    }

    if (!CurrentLine.Parts.empty() || CachedLayoutLines.empty())
    {
        PushCurrentLine(LastTextSize);
    }

    for (const FLayoutLine& Line : CachedLayoutLines)
    {
        CachedMaxLineWidth = std::max(CachedMaxLineWidth, Line.Width);
    }

    MaxStringLenghts = CachedMaxLineWidth;

    bLayoutDirty = false;
}

std::vector<FRichTextStringStyle> WRichText::GetStringsStyle(std::vector<FRichTextSigmentStyle> Sigments)
{
    FRichTextStringStyle StringStyle;
    for (const FRichTextSigmentStyle& Sigment : Sigments)
    {

    }
    
    return std::vector<FRichTextStringStyle>();
}

void WRichText::AppendText(
    const std::string& Text,
    const FRichTextSigmentStyle& Style
)
{
    if (Text.empty())
        return;

    if (!RichTextSigments.empty() && SameStyle(RichTextSigments.back(), Style))
    {
        RichTextSigments.back().Text += Text;
        return;
    }

    FRichTextSigmentStyle Segment = Style;
    Segment.Text = Text;

    RichTextSigments.push_back(Segment);
}

bool WRichText::ApplyTag(
    const std::string& TagText,
    FRichTextSigmentStyle& CurrentStyle
)
{
    if (TagText.empty())
        return false;

    std::vector<std::string> Parts;
    std::string Current;

    for (char Char : TagText)
    {
        if (Char == ',' || Char == ';')
        {
            Parts.push_back(Current);
            Current.clear();
        }
        else
        {
            Current.push_back(Char);
        }
    }

    Parts.push_back(Current);

    bool ParsedAnything = false;

    for (const std::string& Part : Parts)
    {
        if (ApplyTagPart(Part, CurrentStyle))
        {
            ParsedAnything = true;
        }
    }

    return ParsedAnything;
}

bool WRichText::ApplyTagPart(
    const std::string& TagPart,
    FRichTextSigmentStyle& CurrentStyle
)
{
    std::string Part = Trim(TagPart);

    if (Part.empty())
        return false;

    const std::string UpperPart = ToUpper(Part);

    // Reset Style
    // Telplate
    // [/]
    // [Default]
    // [Reset]
    if (UpperPart == "/" ||
        UpperPart == "DEFAULT" ||
        UpperPart == "/DEFAULT" ||
        UpperPart == "RESET" ||
        UpperPart == "/RESET")
    {
        CurrentStyle = FRichTextSigmentStyle();
        return true;
    }

    bool ResetPropertyIfNoValue = false;

    // Supported format
    // [/Color=RED]
    // [/Size=24]
    // [/Color]
    // [/Size]
    if (!Part.empty() && Part[0] == '/')
    {
        ResetPropertyIfNoValue = true;
        Part = Trim(Part.substr(1));
    }

    size_t EqualsPos = Part.find('=');

    std::string Key;
    std::string Value;

    if (EqualsPos == std::string::npos)
    {
        Key = Part;
        Value = "";
    }
    else
    {
        Key = Part.substr(0, EqualsPos);
        Value = Part.substr(EqualsPos + 1);
    }

    Key = Trim(Key);
    Value = Trim(Value);

    while (!Key.empty() && Key[0] == '/')
    {
        Key = Trim(Key.substr(1));
    }

    Key = ToUpper(Key);

    if (Key.empty())
    {
        if (ResetPropertyIfNoValue)
        {
            CurrentStyle = FRichTextSigmentStyle();
            return true;
        }

        return false;
    }

    ERichTeg TagType = CheckTeg(Key);

    if (TagType == ERichTeg::None)
        return false;

    if (TagType == ERichTeg::Color)
    {
        if (ResetPropertyIfNoValue && Value.empty())
        {
            CurrentStyle.TextColor = FRichTextSigmentStyle().TextColor;
        }
        else
        {
            CurrentStyle.TextColor = CheckColorTegValue(Value);
        }

        return true;
    }

    if (TagType == ERichTeg::Size)
    {
        if (ResetPropertyIfNoValue && Value.empty())
        {
            CurrentStyle.TextSize = FRichTextSigmentStyle().TextSize;
            return true;
        }

        int NewSize = 0;

        try
        {
            NewSize = std::stoi(Value);
        }
        catch (...)
        {
            NewSize = 0;
        }

        if (NewSize > 0 && NewSize <= 512)
        {
            CurrentStyle.TextSize = NewSize;
        }

        return true;
    }

    return false;
}

ERichTeg WRichText::CheckTeg(const std::string &TegText)
{
    const std::string Tag = ToUpper(TegText);

    if (Tag == "COLOR" || Tag == "COLOUR")
        return ERichTeg::Color;

    if (Tag == "SIZE" || Tag == "FONTSIZE")
        return ERichTeg::Size;

    return ERichTeg::None;
}

Color WRichText::CheckColorTegValue(const std::string& TegValueText)
{
    const std::string ColorTeg = ToUpper(TegValueText);

    if (ColorTeg == "LIGHTGRAY") return LIGHTGRAY;
    else if (ColorTeg == "GRAY") return GRAY;
    else if (ColorTeg == "DARKGRAY") return DARKGRAY;
    else if (ColorTeg == "YELLOW") return YELLOW;
    else if (ColorTeg == "GOLD") return GOLD;
    else if (ColorTeg == "ORANGE") return ORANGE;
    else if (ColorTeg == "PINK") return PINK;
    else if (ColorTeg == "RED") return RED;
    else if (ColorTeg == "MAROON") return MAROON;
    else if (ColorTeg == "GREEN") return GREEN;
    else if (ColorTeg == "LIME") return LIME;
    else if (ColorTeg == "DARKGREEN") return DARKGREEN;
    else if (ColorTeg == "SKYBLUE") return SKYBLUE;
    else if (ColorTeg == "BLUE") return BLUE;
    else if (ColorTeg == "DARKBLUE") return DARKBLUE;
    else if (ColorTeg == "PURPLE") return PURPLE;
    else if (ColorTeg == "VIOLET") return VIOLET;
    else if (ColorTeg == "DARKPURPLE") return DARKPURPLE;
    else if (ColorTeg == "BEIGE") return BEIGE;
    else if (ColorTeg == "BROWN") return BROWN;
    else if (ColorTeg == "DARKBROWN") return DARKBROWN;
    else if (ColorTeg == "WHITE") return WHITE;
    else if (ColorTeg == "BLACK") return BLACK;
    else if (ColorTeg == "BLANK") return BLANK;
    else if (ColorTeg == "MAGENTA") return MAGENTA;
    else if (ColorTeg == "RAYWHITE") return RAYWHITE;

    return RAYWHITE;
}

void WRichText::Draw()
{
    WWidget::Draw();

    ValidateLayout();

    if (CachedLayoutLines.empty())
        return;

    int ContainerWidth = CachedMaxLineWidth;

    Vector2 WorldPosition = GetWidgetLocationWithAligment();

    const int StartX = static_cast<int>(WorldPosition.x);
    int StartY = static_cast<int>(WorldPosition.y);
    int Y = StartY;

    for (const FLayoutLine& Line : CachedLayoutLines)
    {
        int X = StartX;

        switch (RichTextStyle.HorizontalAlignment)
        {
        case EWidgetHorizontalAlignment::Left:
            X = StartX;
            break;

        case EWidgetHorizontalAlignment::Center:
            X = StartX + (ContainerWidth - Line.Width) / 2;
            break;

        case EWidgetHorizontalAlignment::Right:
            X = StartX + ContainerWidth - Line.Width;
            break;
        }

        if (X < StartX)
            X = StartX;

        const int LineHeight = Line.Height;

        for (const FLayoutPart& Part : Line.Parts)
        {
            if (Part.SegmentIndex >= RichTextSigments.size())
                continue;

            const FRichTextSigmentStyle& Segment = RichTextSigments[Part.SegmentIndex];

            int OffsetY = 0;

            switch (RichTextStyle.VerticalAlignment)
            {
            case EWidgetVerticalAlignment::Top:
                OffsetY = 0;
                break;

            case EWidgetVerticalAlignment::Center:
                OffsetY = (LineHeight - Part.TextSize) / 2;
                break;

            case EWidgetVerticalAlignment::Bottom:
                OffsetY = LineHeight - Part.TextSize;
                break;
            }

            DrawText(
                Part.Text.c_str(),
                X,
                Y + OffsetY,
                Part.TextSize,
                Segment.TextColor
            );

            X += Part.Width;
        }

        Y += LineHeight + RichTextStyle.LineSpacing;
    }

    //DrawRectangle(StartX, StartY, GetSize().x, GetSize().y, RAYWHITE);
}

Vector2 WRichText::AutoSize()
{
    ValidateLayout();

    if (CachedLayoutLines.empty())
    {
        Vector2 Size;
        Size.x = 0.0f;
        Size.y = 0.0f;
        return Size;
    }

    int TotalHeight = 0;

    for (std::size_t i = 0; i < CachedLayoutLines.size(); ++i)
    {
        TotalHeight += CachedLayoutLines[i].Height;

        if (i + 1 < CachedLayoutLines.size())
        {
            TotalHeight += RichTextStyle.LineSpacing;
        }
    }

    if (TotalHeight < 0)
        TotalHeight = 0;

    return Vector2(static_cast<float>(CachedMaxLineWidth), static_cast<float>(TotalHeight));
}