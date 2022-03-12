#pragma once

#include <string>

namespace ImGui {
    void LoadingBar(const char* label) {
        const std::string loading[4] = { " ", ".", "..", "..." };
        int i = (int)(ImGui::GetTime() / 0.2f) & 3;
        ImGui::Text("%s%s", label, loading[i].c_str());
    }
}