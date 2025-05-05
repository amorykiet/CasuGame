#include "Node.h"
#include "MainLoop.h"

void Node::_Init()
{
	printf("Init %s\n", name.c_str());
}

void Node::_Ready()
{
	printf("Ready %s\n", name.c_str());
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

void Node::Destroy()
{
	for (auto child : m_childs) {
		child->Destroy();
		delete child;
	}
	m_childs.clear();
}
