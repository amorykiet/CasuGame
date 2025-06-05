#pragma once

#include "NodePath.h"
#include <vector>
#include <string>
#include "tinyxml2.h"
#include "NodeFactory.h"

class SceneTree;

class Node
{
public:
	friend class SceneTree;

	virtual ~Node() = default;

	//Callbacks for game logic
	virtual void _Init();
	virtual void _Ready();
	virtual void _Update(float);
	virtual void _Render();
	virtual void _Destroy();

	virtual void _ShowInspector();
	virtual void SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc);
	virtual void DeserializeFromXML(tinyxml2::XMLElement* element);

	void Init();
	void Ready();
	void Update(float deltaTime);
	void Render();

	void SetName(const std::string& name);
	const std::string& GetName();
	void SetParent(Node* parent);
	void SetRoot(SceneTree* root);
	Node* GetParent();
	SceneTree* GetRoot();

	std::string GetType();
	void ValidateName(std::string& name);
	void AddChild(Node* child);
	void RemoveChild(Node* child);

	Node* GetNode(const NodePath& path);
	Node* GetNode(const std::string& path);
	Node* GetChildByType(const std::string& name);
	bool HasChild(const NodePath& path);
	bool HasChild(const std::string& name);
	bool HasChildWithType(const std::string& type);
	const std::vector<Node*>& GetChilds();
	bool isDestroyed();

	void ShowInspector();
	void Remove();

protected:
	void Destroy();
	bool m_isDestroyed = false;
	NodePath m_path;
	std::string name;
	std::vector<Node*> m_childs;
	Node* m_parent;
	SceneTree* m_root;
	std::vector<Node*> m_pendingInitNodes;
	std::vector<Node*> m_pendingRemoveNodes;
};

using Scene = Node;

REGISTER_NODE_CLASS(Scene);
REGISTER_NODE_CLASS(Node);