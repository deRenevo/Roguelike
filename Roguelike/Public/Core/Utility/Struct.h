#pragma once

#include "raylib.h"

#include <string>

struct FTextStyle 
{
	int FontSize = 24;
	Color TextColor = RAYWHITE;
};

struct FBorderStyle
{
	Color BaseColor = DARKGRAY;
	Color BorderColor = GRAY;
	float BorderWidth = 2;
};

struct FButtonStyle
{
    FBorderStyle Normal = {
    .BaseColor = GRAY,
    .BorderColor = DARKGRAY,
    .BorderWidth = 2.0f
    };

    FBorderStyle Hovered = {
        .BaseColor = LIGHTGRAY,
        .BorderColor = GRAY,
        .BorderWidth = 2.0f
    };

    FBorderStyle Clicked = {
        .BaseColor = WHITE,
        .BorderColor = LIGHTGRAY,
        .BorderWidth = 2.0f
    };

	FTextStyle TextStyle;
};

struct FRichTextSigmentStyle
{
    std::string Text = " ";
    Color TextColor =  RAYWHITE;
    int TextSize = 24;
};

enum class EWidgetVerticalAlignment 
{
    Top,
    Center,
    Bottom
};

enum class EWidgetHorizontalAlignment 
{
    Right,
    Center,
    Left
};