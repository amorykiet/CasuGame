#include "Editor.h"
#include "engine/SceneTree.h"
#include "engine/CasuEngineDef.h"
#include "imgui.h"
#include "engine/MainLoop.h"
#include "rlImGui.h"
#include "raylib.h"
#include "raymath.h"

void Editor::Init()
{
	SceneTree::GetInstance()->LoadSceneFromXML(GAME_SCENE_FILE);
}

void Editor::Update()
{
    ShowNodeTree(SceneTree::GetInstance()->GetCurrentScene());
	if (m_selectedNode)
	{
		ShowNodeInspector(m_selectedNode);
	}

    if (ShouldShowContextPopup)
    {
        ImGui::OpenPopup("Context Menu");
		ShouldShowContextPopup = false;
    }

    if (m_contextNode)
    {
		ShowNodeContextMenu();
    }
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

void Editor::Run()
{
    const int screenWidth = 900;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "CasuEngine Editor");
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    rlImGuiSetup(true);
    Editor::GetInstance()->Init();
    while (!WindowShouldClose())
    {
        if (!ImGui::GetIO().WantCaptureMouse) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                Vector2 delta = GetMouseDelta();
                delta = Vector2Scale(delta, -1.0f / camera.zoom);
                camera.target = Vector2Add(camera.target, delta);
            }
            float wheel = GetMouseWheelMove();
            if (wheel != 0)
            {
                Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
                camera.offset = GetMousePosition();
                camera.target = mouseWorldPos;
                float scale = 0.2f * wheel;
                camera.zoom = Clamp(expf(logf(camera.zoom) + scale), 0.125f, 64.0f);
            }
        }

        BeginDrawing();
        rlImGuiBegin();
        ClearBackground(RAYWHITE);

        Editor::GetInstance()->Update();

        BeginMode2D(camera);
        Editor::GetInstance()->Render();
        EndMode2D();

        rlImGuiEnd();
        EndDrawing();
    }

    Editor::GetInstance()->Close();
    rlImGuiShutdown();
    CloseWindow();
}

void Editor::ShowNodeTree(Scene * scene)
{
	if (scene == nullptr) return;
	ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
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
        if (ImGui::IsItemClicked(1) && !ShouldShowContextPopup) {
            m_selectedNode = node;
            m_contextNode = node;
            ShouldShowContextPopup = true;
        }
        return;
    }

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
    if (isSelected)
        flags |= ImGuiTreeNodeFlags_Selected;

    bool isNodeOpen = ImGui::TreeNodeEx(node->GetName().c_str(), flags);
    if (ImGui::IsItemClicked(0)) {
        m_selectedNode = node;
    }
	if (ImGui::IsItemClicked(1) && !ShouldShowContextPopup) {
        m_selectedNode = node;
		m_contextNode = node;
        ShouldShowContextPopup = true;
	}
    if (isNodeOpen) {
        for (Node* child : childs) {
            ShowNodeTreeRecursive(child);
        }
        ImGui::TreePop();
    }
}
	
void Editor::ShowNodeInspector(Node* node)
{
    if (node == nullptr) return;
	ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(320, 10), ImGuiCond_FirstUseEver);
	node->ShowInspector();
}

void Editor::ShowNodeContextMenu()
{
    if (ImGui::BeginPopup("Context Menu"))
    {
        if (ImGui::Button("Remove"))
        {
            m_contextNode->Remove();
            m_contextNode = nullptr;
			m_selectedNode = nullptr;
            SceneTree::GetInstance()->SaveCurrentSceneToXML(GAME_SCENE_FILE);
        }
		ImGui::Separator();
		static int selectedType = 0;
		std::vector<std::string> classNames = NodeFactory::GetRegisteredClassNames();
        std::vector<const char*> classNamePtrs;
        for (const auto& name : classNames) {
            classNamePtrs.push_back(name.c_str());
        }
        ImGui::Combo("Type", &selectedType, classNamePtrs.data(), (int)classNamePtrs.size());
        ImGui::SameLine();
        if (ImGui::Button("Add Child")) {
            Node* newNode = NodeFactory::Create(classNames[selectedType]);
            if (newNode && m_contextNode) {
                m_contextNode->AddChild(newNode);
                m_selectedNode = newNode;
                SceneTree::GetInstance()->SaveCurrentSceneToXML(GAME_SCENE_FILE);
            }
        }

        ImGui::EndPopup();
    }

    if (!ImGui::IsPopupOpen("Context Menu")) {
        m_contextNode = nullptr;
    }
}

void Editor::ShowGameWindowBox()
{
	// use raylib to draw the game window
	MainLoop::GetInstance()->LoadConfig();
	int windowWidth = MainLoop::GetInstance()->GetWidth();
	int windowHeight = MainLoop::GetInstance()->GetHeight();
	DrawRectangleLines(0, 0, windowWidth, windowHeight, BLACK);
}

void Editor::RemoveCurrentNode()
{
	if (m_selectedNode)
	{
		m_selectedNode->Remove();
		m_selectedNode = nullptr;
	}
}
