#include "Node.h"
#include "MainLoop.h"
#include <sstream>
#include <algorithm>
#include <tinyxml2.h> //XML handling

#include "imgui.h"

void Node::_Init()
{
	//callback for game logic
}

void Node::_Ready()
{
	//callback for game logic
}

void Node::_Update(float)
{
	//callback for game logic
}

void Node::_Render()
{
	//callback for game logic
}

void Node::_Destroy()
{
}

void Node::_ShowInspector()
{
	ImGui::Text("Type: %s", GetType().c_str());
	ImGui::Separator();
	static char nameBuffer[256];
	ImGui::InputText("Name##set", nameBuffer, sizeof(nameBuffer));
	if (ImGui::Button("Set Name")) {
		SetName(nameBuffer);
	}
}

void Node::SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc)
{
	element->SetAttribute("name", m_name.c_str());
	element->SetAttribute("path", m_path.GetPath().c_str());
	element->SetAttribute("type", GetType().c_str());

	for (auto child : m_childs) {
		tinyxml2::XMLElement* childElement = doc->NewElement(child->GetType().c_str());
		child->SerializeToXML(childElement, doc);
		element->InsertEndChild(childElement);
	}
}

void Node::DeserializeFromXML(tinyxml2::XMLElement* element)
{
	const char* nameAttr = element->Attribute("name");
	if (nameAttr) {
		m_name = nameAttr;
	}
	const char* pathAttr = element->Attribute("path");
	if (pathAttr) {
		m_path.SetPath(pathAttr);
	}

	// Deserialize children (detect class from tag name)
	for (tinyxml2::XMLElement* childElement = element->FirstChildElement();
		childElement != nullptr;
		childElement = childElement->NextSiblingElement()) {

		const char* tagName = childElement->Attribute("type");
		Node* childNode = NodeFactory::Create(tagName);
		childNode->DeserializeFromXML(childElement);
		AddChild(childNode);
	}
}

void Node::Init()
{
	printf("Init %s\n", m_path.GetPath().c_str());
	// Construct the path based on the parent's path
	if (m_parent) {
		m_path.SetPath(m_parent->m_path.GetPath() + "/" + m_name);
	}
	else {
		m_path.SetPath(m_name); // Root node's path is its own name
	}

	_Init();
	for (auto child : m_childs) {
		child->Init();
	}
}

void Node::Ready()
{
	printf("Ready %s\n", m_path.GetPath().c_str());
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
		if (child->m_isDestroyed) continue; // Skip destroyed nodes
		child->Update(deltaTime);
	}
	_Update(deltaTime);

	// Remove pending nodes
	if (!m_pendingRemoveNodes.empty())
	{
		for (Node* child : m_pendingRemoveNodes) {
			m_childs.erase(std::remove(m_childs.begin(), m_childs.end(), child), m_childs.end());
			child->Destroy();
			delete child;
		}
		m_pendingRemoveNodes.clear();
	}
}

void Node::Render()
{
	_Render();
	for (auto child : m_childs) {
		if (child->m_isDestroyed) continue; // Skip destroyed nodes
		child->Render();
	}
}

void Node::SetName(const std::string& name)  
{  
	this->m_name = name;
	// Validate the name to ensure it's unique among siblings
	ValidateName(this->m_name);
	if (m_parent) {  
		m_path.SetPath(m_parent->m_path.GetPath() + "/" + this->m_name);
	}  
	else {  
		m_path.SetPath(this->m_name); // Root node's path is its own name  
	}  

	// Update the paths of all child nodes recursively  
	for (auto child : m_childs) {  
		child->SetName(child->GetName());  
	}  
}

const std::string& Node::GetName()
{
	return m_name;
}

void Node::SetParent(Node* parent)
{
	m_parent = parent;
}

void Node::SetRoot(SceneTree* root)
{
	m_root = root;
}

Node* Node::GetParent()
{
	return m_parent;
}

SceneTree* Node::GetRoot()
{
	return m_root;
}

std::string Node::GetType()
{
	std::string name = typeid(*this).name();
	std::string prefix = "class ";  // or "struct "

	// Remove "class " prefix if present
	if (name.compare(0, prefix.length(), prefix) == 0) {
		name = name.substr(prefix.length());
	}

	return name;
}

void Node::ValidateName(std::string& name)
{
	// Check if the name is empty
	if (name.empty()) {
		name = GetType();
	}
    // Check if the name is already taken by another child of the parent
    if (m_parent) {
       auto it = std::find_if(m_parent->m_childs.begin(), m_parent->m_childs.end(), [&](Node* sibling) {
           return sibling != this && sibling->GetName() == name;
       });
       if (it != m_parent->m_childs.end()) {
           // Name is already taken, generate a new unique name
           std::string baseName = name;
           int counter = 1;
           do {
               name = baseName + std::to_string(counter);
               counter++;
               it = std::find_if(m_parent->m_childs.begin(), m_parent->m_childs.end(), [&](Node* sibling) {
                   return sibling != this && sibling->GetName() == name;
               });
           } while (it != m_parent->m_childs.end());
       }
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

	// Validate the name to ensure it's unique among siblings
	child->SetName(child->m_name);
	m_childs.push_back(child);

	// dynamically init the child node
	if (MainLoop::GetInstance()->IsRunning())
	{
		m_pendingInitNodes.push_back(child);
	}
	// if the main loop is not running, we can call Init and Ready directly
	else
	{
		child->Init();
		child->Ready();
	}
}


void Node::RemoveChild(Node* child)
{
	if (child == nullptr) return;
	child->m_isDestroyed = true;
	// Mark the child for deferred deletion
	if (MainLoop::GetInstance()->IsRunning())
	{
		child->GetParent()->m_pendingRemoveNodes.push_back(child);
	}
	else
	{
		m_childs.erase(std::remove(m_childs.begin(), m_childs.end(), child), m_childs.end());
		child->Destroy();
		delete child;
	}
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

Node* Node::GetChildByType(const std::string& name)
{
	for (auto child : m_childs) {
		if (child->GetType() == name) {
			return child;
		}
	}
	return nullptr;
}

bool Node::HasChild(const NodePath& path)
{
	Node* node = GetNode(path);
	return node != nullptr;
}

bool Node::HasChild(const std::string& name)
{
	NodePath nodePath(name);
	return HasChild(nodePath);
}

bool Node::HasChildWithType(const std::string& type)
{
	for (auto child : m_childs) {
		if (child->GetType() == type) {
			return true;
		}
	}
	return false;
}

const std::vector<Node*>& Node::GetChilds()
{
	return m_childs;
}

bool Node::isDestroyed()
{
	return m_isDestroyed;
}

void Node::Destroy()
{
	_Destroy();
	printf("Destroy %s\n", m_path.GetPath().c_str());
	for (auto child : m_childs) {
		child->Destroy();
		delete child;
	}
	m_childs.clear();
}

void Node::ShowInspector()
{
	ImGui::SetNextWindowPos(ImVec2(300, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
	ImGui::Begin(m_name.c_str());
	if (ImGui::Button("Save##NodePro"))
	{
		SceneTree::GetInstance()->SaveCurrentSceneToXML();
	}
	_ShowInspector();
	ImGui::End();
}

void Node::Remove()
{
	if (m_parent) {
		m_parent->RemoveChild(this);
	}
	else {
		Destroy();
		delete this;
	}
}

void Node::SaveAsScene(const std::string& filePath)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* root = doc.NewElement("Scene");
	doc.InsertFirstChild(root);
	SerializeToXML(root, &doc);
	tinyxml2::XMLError result = doc.SaveFile(filePath.c_str());
	if (result != tinyxml2::XML_SUCCESS) {
		printf("Error saving scene to XML: %s\n", doc.ErrorName());
	}
}

void Node::SaveAsScene()
{
	std::string filePath = m_name + ".scene";
	SaveAsScene(filePath);
}
