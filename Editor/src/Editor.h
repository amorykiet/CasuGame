#pragma once
#include "engine/Node.h"
#include "core/Singleton.h"

class Editor: public Singleton<Editor> {
public:
	void Init();
	void Update();
	void Render();
	void Close();

	void ShowNodeTree(Scene* scene);
	void ShowNodeTreeRecursive(Node* node);
	void ShowNodeInspector(Node* node);
	void ShowAddNodeMenu();

	void ShowGameWindowBox();

private:
	Node* m_selectedNode = nullptr;
};