#pragma once

#include "NodePath.h"
#include <vector>
#include <string>

class SceneTree;

class Node
{
public:

	//Callbacks for game logic
	virtual void _Init();
	virtual void _Ready();
	virtual void _Update(float);
	virtual void _Render();

	void Init();
	void Ready();
	void Update(float deltaTime);
	void Render();

	void SetName(const std::string& name);
	const std::string& GetName() const { return name; }
	void SetParent(Node* parent) { m_parent = parent; }
	void SetRoot(SceneTree* root) { m_root = root; }
	Node* GetParent() { return m_parent; }
	SceneTree* GetRoot() { return m_root; }

	std::string GetType();
	void ValidateName(std::string& name);
	void AddChild(Node* child);
	void RemoveChild(Node* child);

	Node* GetNode(const NodePath& path);
	Node* GetNode(const std::string& path);

	void Destroy();

protected:
	NodePath m_path;
	std::string name;
	std::vector<Node*> m_childs;
	Node* m_parent;
	SceneTree* m_root;
	std::vector<Node*> m_pendingInitNodes;
	std::vector<Node*> m_pendingRemoveNodes;
};

using Scene = Node;