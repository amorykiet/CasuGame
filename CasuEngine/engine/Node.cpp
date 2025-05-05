#include "Node.h"
#include "MainLoop.h"
#include <sstream>

void Node::_Init()
{
	printf("Init %s\n", m_path.GetPath().c_str());
}

void Node::_Ready()
{
	printf("Ready %s\n", m_path.GetPath().c_str());
}

void Node::_Update(float)
{
	//callback for game logic
}

void Node::_Render()
{
	//callback for game logic
}

void Node::Init()
{
	// Construct the path based on the parent's path
	if (m_parent) {
		m_path.SetPath(m_parent->m_path.GetPath() + "/" + name);
	}
	else {
		m_path.SetPath(name); // Root node's path is its own name
	}

	_Init();
	for (auto child : m_childs) {
		child->Init();
	}
}

void Node::Ready()
{
	for (auto child : m_childs) {
		child->Ready();
	}
	_Ready();
}

void Node::Update(float deltaTime)
{    
	// Initialize pending nodes
	if (!m_pendingInitNodes.empty())
	{
		for (Node* node : m_pendingInitNodes) {
			node->Init();
			node->Ready();
		}
		m_pendingInitNodes.clear();
	}


	for (auto child : m_childs) {
		child->Update(deltaTime);
	}
	_Update(deltaTime);
}

void Node::Render()
{
	_Render();
	for (auto child : m_childs) {
		child->Render();
	}
}

void Node::AddChild(Node* child)
{
	if (child == nullptr) return;
	child->SetParent(this);
	if (m_root)
	{
		child->SetRoot(m_root);
	}
	m_childs.push_back(child);

	// dynamically init the child node
	if (MainLoop::GetInstance()->IsRunning())
	{
		m_pendingInitNodes.push_back(child);
	}
}


void Node::RemoveChild(Node* child)
{
	child->Destroy();
	delete child;
	m_childs.erase(std::remove(m_childs.begin(), m_childs.end(), child), m_childs.end());
}


Node* Node::GetNode(const NodePath& path)
{
   // Split the relative path into parts
   std::string relativePath = path.GetPath();
   std::istringstream stream(relativePath);
   std::string segment;
   Node* currentNode = this;

   while (std::getline(stream, segment, '/')) {
       if (segment == "..") {
           // Move to the parent node
           currentNode = currentNode->m_parent;
           if (!currentNode) {
               return nullptr; // Invalid path
           }
       } else if (segment != "." && !segment.empty()) {
           // Search for the child node with the matching name
           auto it = std::find_if(
               currentNode->m_childs.begin(),
               currentNode->m_childs.end(),
               [&segment](Node* child) { return child->GetName() == segment; });

           if (it == currentNode->m_childs.end()) {
               return nullptr; // Node not found
           }
           currentNode = *it;
       }
   }

   return currentNode;
}

Node* Node::GetNode(const std::string& path)
{
	NodePath nodePath(path);
	return GetNode(nodePath);
}

void Node::Destroy()
{
	for (auto child : m_childs) {
		child->Destroy();
		delete child;
	}
	m_childs.clear();
}
