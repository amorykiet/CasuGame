#include "Editor.h"
#include "engine/SceneTree.h"
#include "engine/CasuEngineDef.h"
#include "imgui.h"
#include "raylib.h"
#include "engine/MainLoop.h"

void Editor::Init()
{
	SceneTree::GetInstance()->LoadSceneFromXML(GAME_SCENE_FILE);
}

void Editor::Update()
{
	// Update the editor logic here
	if (m_selectedNode)
	{
		ShowNodeInspector(m_selectedNode);
	}
	ShowNodeTree(SceneTree::GetInstance()->GetCurrentScene());
	ShowAddNodeMenu();
}

void Editor::Render()
{
	SceneTree::GetInstance()->Render();
    ShowGameWindowBox();
}

void Editor::Close()
{
	SceneTree::GetInstance()->Destroy();
}

void Editor::ShowNodeTree(Scene * scene)
{
	if (scene == nullptr) return;
	ImGui::Begin("Node Tree");
	ShowNodeTreeRecursive(static_cast<Node*>(scene));
	ImGui::End();
}

void Editor::ShowNodeTreeRecursive(Node* node)
{
    if (!node) return;
    const auto& childs = node->GetChilds();
    bool isSelected = (m_selectedNode == node);

    if (childs.empty()) {
        if (ImGui::Selectable(node->GetName().c_str(), isSelected)) {
            m_selectedNode = node;
        }
        return;
    }

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
    if (isSelected)
        flags |= ImGuiTreeNodeFlags_Selected;

    bool nodeOpen = ImGui::TreeNodeEx(node->GetName().c_str(), flags);
    if (ImGui::IsItemClicked()) {
        m_selectedNode = node;
    }
    if (nodeOpen) {
        for (Node* child : childs) {
            ShowNodeTreeRecursive(child);
        }
        ImGui::TreePop();
    }
}
	
void Editor::ShowNodeInspector(Node* node)
{
}

void Editor::ShowAddNodeMenu()
{
}

void Editor::ShowGameWindowBox()
{
	// use raylib to draw the game window
	MainLoop::GetInstance()->LoadConfig();
	int windowWidth = MainLoop::GetInstance()->GetWidth();
	int windowHeight = MainLoop::GetInstance()->GetHeight();
	DrawRectangleLines(0, 0, windowWidth, windowHeight, BLACK);
}
