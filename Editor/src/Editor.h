#pragma once

#include "engine/Node.h"
#include "core/Singleton.h"

class Editor: public Singleton<Editor> {
public:
	void Init();
	void Update();
	void Render();
	void Close();
	void Run();

	void ShowNodeTree(Scene* scene);
	void ShowNodeTreeRecursive(Node* node);
	void ShowNodeInspector(Node* node);
	void ShowNodeContextMenu();

	void ShowGameWindowBox();
	void RemoveCurrentNode();

private:
	Node* m_selectedNode = nullptr;
	Node* m_contextNode = nullptr;
	bool ShouldShowContextPopup = false;
};
