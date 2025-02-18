#pragma once
#include <functional>
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

namespace ImGui
{
    static void TextCenteredColumn(const char* fmt, ...)
	{
        va_list args;
        va_start(args, fmt);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetColumnWidth() - ImGui::CalcTextSize(fmt).x) / 2);
        TextV(fmt, args);
        va_end(args);
	}
    static void TextCenteredColumnV(const char* fmt, va_list args)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return;

        ImGuiContext& g = *GImGui;
        const char* text_end = g.TempBuffer + ImFormatStringV(g.TempBuffer, IM_ARRAYSIZE(g.TempBuffer), fmt, args);
        TextEx(g.TempBuffer, text_end, ImGuiTextFlags_NoWidthForLargeClippedText);
    }

    static bool CheckboxCenteredColumn(const char* label, bool* v)
    {
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetColumnWidth() - ImGui::GetFontSize()) / 2);
        return ImGui::Checkbox(label, v);
    }

    static void Tooltip(const std::function<void()>& action)
    {
        bool hovered = ImGui::IsItemHovered();
        if (hovered)
        {
            ImGui::BeginTooltip();
            if (action != nullptr) { action(); }
            ImGui::EndTooltip();
        }
    }

    static void TooltipGeneric(const char *fmt, ...)
    {
        ImGui::Tooltip([fmt] {ImGui::Text(fmt); });
    }
}