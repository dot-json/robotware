#include "framework.h"

void tabAssistance() {
	ImGui::BeginChild("at1", ImVec2(250, dx::menu.height - 88), true);
	ImGui::SetCursorPos({(250 - ImGui::CalcTextSize("aimbot").x) / 2, 4});
	ImGui::TextColored(ImVec4(0.77f, 0.77f, 0.77f, 1), "aimbot");
	auto currentY = ImGui::GetCursorPosY();
	ImGui::SetCursorPosY(currentY - 4);
	ImGui::Separator();

	ImGui::EndChild();
}
void tabVisuals() {

}
void tabMisc() {
	ImGui::BeginChild("mt1", ImVec2((dx::menu.width - 116) / 2 - 24, dx::menu.height - 88), true);
	ImGui::SetCursorPos({ ((dx::menu.width - 116) / 2 - 24 - ImGui::CalcTextSize("movement").x) / 2, 4 });
	ImGui::TextColored(ImVec4(0.77f, 0.77f, 0.77f, 1), "movement");
	auto currentY = ImGui::GetCursorPosY();
	ImGui::SetCursorPosY(currentY - 4);
	ImGui::Separator();

	ImGui::EndChild();

	ImGui::SetCursorPos({ (dx::menu.width - 116) / 2 + 8, 16 });

	ImGui::BeginChild("mt2", ImVec2((dx::menu.width - 116) / 2 - 24, dx::menu.height - 88), true);
	ImGui::SetCursorPos({ ((dx::menu.width - 116) / 2 - 24 - ImGui::CalcTextSize("config").x) / 2, 4 });
	ImGui::TextColored(ImVec4(0.77f, 0.77f, 0.77f, 1), "config");
	currentY = ImGui::GetCursorPosY();
	ImGui::SetCursorPosY(currentY - 4);
	ImGui::Separator();

	ImGui::EndChild();
}
void tabSettings() {

}


void Title(std::string text) {
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

	//ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::TextColored(ImVec4(0.85f, 0.85f, 0.85f, 1), text.c_str());
}

void dx::renderMenu() {
	ImGui::SetNextWindowSize(ImVec2(menu.width, menu.height));
	if (ImGui::Begin("robotware", &mOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar )) {
		ImGui::PushFont(font_Futura_25);
		ImGui::SetCursorPosY(10);
		Title("ROBOTWARE");
		ImGui::PopFont();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::SetCursorPos({ menu.width - 55 - 16, 9});
		ImGui::PushFont(font_Futura_12);
		if (ImGui::Button("HIDE", ImVec2(54, 26)))
			mOpen = false;
		ImGui::PopFont();
		ImGui::PopStyleColor(4);

		ImGui::SetCursorPos(ImVec2(16.f, 40.f));
		ImGui::BeginChild("tabID", ImVec2(68.f, 4*64.f + 55));
		ImGui::PushFont(font_menu_tab);
		for (auto i = 0; i < 4; i++) {
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.16f, 0.15f, 0.18f, 1.00f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.16f, 0.15f, 0.18f, 1.00f));
			bool changeCol = false;
			if (i == selectedTab) {
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.92f, 0.02f, 0.35f, 1.00f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.92f, 0.02f, 0.35f, 1.00f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.92f, 0.02f, 0.35f, 1.00f));
				changeCol = true;
			}
			if (ImGui::ImageButton((void*)tabTextures[i], ImVec2(64.f, 64.f), ImVec2(0,0), ImVec2(1,1), 2)) {
				selectedTab = i;
			}
			if (changeCol)
				ImGui::PopStyleColor(3);
			ImGui::PopStyleColor(2);
		}
		ImGui::PopFont();
		ImGui::EndChild();
		//------------------------------------------------------------
		ImGui::PushFont(font_menu_info);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(12, 1));
		ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1), "Build Date:");
		ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1), __DATE__);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(12, 8));
		ImGui::Spacing();
		ImGui::PopStyleVar();
		ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1), "Version:");
		ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1), "1.0.0");
		ImGui::PopStyleVar();
		ImGui::PopFont();
		//------------------------------------------------------------

		ImGui::SetCursorPos(ImVec2(100.f, 40.f));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.40f, 0.40f, 0.43f, 0.16f));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.09f, 0.08f, 0.1f, 0.40f));
		ImGui::BeginChild("mainWindow", ImVec2(menu.width - 116, menu.height - 56), true, ImGuiWindowFlags_NoMove);
		switch (selectedTab)
		{
		case 0:
			tabAssistance();
			break;
		case 1:
			tabVisuals();
			break;
		case 2:
			tabMisc();
			break;
		case 3:
			tabSettings();
			break;
		}
		ImGui::EndChild();
		ImGui::PopStyleColor(2);

	}ImGui::End();
}

void dx::loadImCfg() {
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding = ImVec2(16, 16);
	style->WindowRounding = 0.f;
	style->FramePadding = ImVec2(5, 2);
	style->FrameRounding = 0.f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(4, 3);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 9.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;
	style->FrameBorderSize = 1.f;
	style->ChildBorderSize = 1.f;
	style->WindowBorderSize = 1.f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.88f, 0.88f, 0.88f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.40f, 0.40f, 0.43f, 0.32f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.11f, 0.10f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.14f, 0.13f, 0.16f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.16f, 0.19f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.71f, 0.70f, 0.72f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.00f, 0.37f, 1.00f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.06f, 0.33f, 1.00f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.92f, 0.02f, 0.35f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.12f, 0.11f, 0.14f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.92f, 0.02f, 0.35f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.88f, 0.03f, 0.34f, 1.00f);
	style->Colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.16f, 0.17f, 1.00f);
	style->Colors[ImGuiCol_TabHovered] = ImVec4(0.92f, 0.02f, 0.35f, 1.00f);
	style->Colors[ImGuiCol_TabActive] = ImVec4(0.92f, 0.02f, 0.35f, 1.00f);
	style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.14f, 0.15f, 0.16f, 0.97f);
	style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.35f, 0.37f, 1.00f);
	style->Colors[ImGuiCol_ChildBg] = ImVec4(0.06f, 0.05f, 0.07f, 0.20f);
	style->Colors[ImGuiCol_Separator] = ImVec4(0.40f, 0.40f, 0.43f, 0.26f);
}
