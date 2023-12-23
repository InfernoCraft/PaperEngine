﻿#include "Editor.h"
#include "OutlinerPanel.h"

#include "editor/SelectionManager.h"

namespace PaperED
{
	void Entities(Ref<Scene>& activeScene)
	{
		if (ImGui::TreeNode("Entities"))
		{
			auto entities = activeScene->Registry().view<TransformComponent>();
			for (auto entt : entities) {
				Entity entity(entt, activeScene.get());
				ImGui::PushID(entity.GetPaperID().toString().c_str());
				if (ImGui::Selectable(entity.GetName().c_str())) {
					SelectionManager::Select(SelectionManagerType::ViewPort, entity.GetPaperID());
				}
				ImGui::PopID();
			}

			ImGui::TreePop();
		}
	}

	void TwoDObjects(Ref<Scene>& activeScene)
	{
		if (ImGui::TreeNode("2D-Object"))
		{
			auto sprites_s = activeScene->Registry().view<SpriteComponent>();
			if (!sprites_s.empty() && ImGui::TreeNode("Sprite"))
			{
				for (auto [entt, sprite] : sprites_s.each()) {
					Entity entity(entt, activeScene.get());
					ImGui::PushID(entity.GetPaperID().toString().c_str());
					if (ImGui::Selectable(entity.GetName().c_str())) {
						SelectionManager::Select(SelectionManagerType::ViewPort, entity.GetPaperID());
					}
					ImGui::PopID();
				}
				ImGui::TreePop();
			}

			auto lines = activeScene->Registry().view<LineComponent>();
			if (lines.size() && ImGui::TreeNode("Line"))
			{
				for (auto [entt, line] : lines.each()) {
					Entity entity(entt, activeScene.get());
					ImGui::PushID(entity.GetPaperID().toString().c_str());
					if (ImGui::Selectable(entity.GetName().c_str())) {
						SelectionManager::Select(SelectionManagerType::ViewPort, entity.GetPaperID());
					}
					ImGui::PopID();
				}
				ImGui::TreePop();
			}

			auto texts = activeScene->Registry().view<TextComponent>();
			if (texts.size() && ImGui::TreeNode("Text"))
			{
				for (auto [entt, text] : texts.each()) {
					Entity entity(entt, activeScene.get());
					ImGui::PushID(entity.GetPaperID().toString().c_str());
					if (ImGui::Selectable(entity.GetName().c_str())) {
						SelectionManager::Select(SelectionManagerType::ViewPort, entity.GetPaperID());
					}
					ImGui::PopID();
				}
				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
	}

	void Cameras(Ref<Scene>& activeScene)
	{
		if (ImGui::TreeNode("Cameras"))
		{
			auto cameras = activeScene->Registry().view<CameraComponent>();
			for (auto entt : cameras) {
				Entity entity(entt, activeScene.get());
				ImGui::PushID(entity.GetPaperID().toString().c_str());
				if (ImGui::Selectable(entity.GetName().c_str())) {
					SelectionManager::Select(SelectionManagerType::ViewPort, entity.GetPaperID());
				}
				ImGui::PopID();
			}

			ImGui::TreePop();
		}
	}

	void OutlinerPanel::OnImGuiRender(bool& isOpen)
	{
		Ref<Scene> activeScene = Scene::GetActive();
	
		UI::ScopedStyle min_width(ImGuiStyleVar_WindowMinSize, ImVec2(400.0f, 0.0f));
	
		ImGui::Begin(panelName.c_str(), &isOpen);
	
		if (activeScene)
		{
			Entities(activeScene);
			TwoDObjects(activeScene);
			Cameras(activeScene);
		}

		ImGui::End();
		
	}
}
