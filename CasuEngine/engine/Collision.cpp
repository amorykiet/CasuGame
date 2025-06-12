#include "Collision.h"
#include <algorithm>
#include <cstdio>

#include "imgui.h"

void Collision::_Render()
{
	if (m_isShowRec)
	{
		m_collisionRec.DrawLines(PURPLE);
	}
}

void Collision::_SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc)
{
	element->SetAttribute("showRec", m_isShowRec);
	element->SetAttribute("x", m_collisionRec.x);
	element->SetAttribute("y", m_collisionRec.y);
	element->SetAttribute("width", m_collisionRec.width);
	element->SetAttribute("height", m_collisionRec.height);
	element->SetAttribute("layer", m_layer);
	element->SetAttribute("masks", m_masks.size());
	for (size_t i = 0; i < m_masks.size(); ++i) {
		element->SetAttribute(("mask" + std::to_string(i)).c_str(), m_masks[i]);
	}
	Node::_SerializeToXML(element, doc);
}

void Collision::_DeserializeFromXML(tinyxml2::XMLElement* element)
{
	element->QueryBoolAttribute("showRec", &m_isShowRec);
	element->QueryFloatAttribute("x", &m_collisionRec.x);
	element->QueryFloatAttribute("y", &m_collisionRec.y);
	element->QueryFloatAttribute("width", &m_collisionRec.width);
	element->QueryFloatAttribute("height", &m_collisionRec.height);
	element->QueryIntAttribute("layer", &m_layer);
	int maskCount;
	element->QueryIntAttribute("masks", &maskCount);
	m_masks.clear();
	for (int i = 0; i < maskCount; ++i) {
		int mask;
		element->QueryIntAttribute(("mask" + std::to_string(i)).c_str(), &mask);
		m_masks.push_back(mask);
	}
	Node::_DeserializeFromXML(element);
}

void Collision::_ShowInspector()
{
	Node::_ShowInspector();
	ImGui::Separator();
	ImGui::Checkbox("Show Collision Rec", &m_isShowRec);
	ImGui::InputFloat("X", &m_collisionRec.x);
	ImGui::InputFloat("Y", &m_collisionRec.y);
	ImGui::InputFloat("Width", &m_collisionRec.width);
	ImGui::InputFloat("Height", &m_collisionRec.height);
	ImGui::InputInt("Layer", &m_layer);
	ImGui::Text("Masks");
	for (size_t i = 0; i < m_masks.size(); ++i) {
		ImGui::InputInt(("Mask " + std::to_string(i)).c_str(), &m_masks[i]);
	}
	// remove mask
	if (ImGui::Button("Remove Mask")) {
		if (!m_masks.empty()) {
			m_masks.pop_back();
		}
	}
	// add mask
	if (ImGui::Button("Add Mask")) {
		m_masks.push_back(0);
	}

}

void Collision::_Destroy()
{
	m_masks.clear();
}

Collision::Collision() : m_collisionRec{ 0, 0, 0, 0 }, m_layer(0), m_masks{ 0 } {}

Collision::Collision(const RRectangle& rec) : m_collisionRec(rec), m_layer(0), m_masks{ 0 } {}

Collision::Collision(float x, float y, float width, float height)
	: m_collisionRec{ x, y, width, height }, m_layer(0), m_masks{ 0 } {
}

bool Collision::CheckCollision(const RRectangle& other) {
	return ::CheckCollisionRecs(m_collisionRec, other);
}

bool Collision::CheckCollision(const Collision& other) {
	if (CheckMask(other.m_layer)) {
		return CheckCollision(other.m_collisionRec);
	}
	return false;
}

bool Collision::CheckMask(int layer) {
	return std::find(m_masks.begin(), m_masks.end(), layer) != m_masks.end();
}

RRectangle Collision::GetCollisionRec() {
	return m_collisionRec;
}

RRectangle Collision::GetCollisionRec(const Collision& other) {
	return ::GetCollisionRec(m_collisionRec, other.m_collisionRec);
}

void Collision::AddMask(int id) {
	m_masks.push_back(id);
}

void Collision::RemoveMask(int id) {
	m_masks.erase(std::remove(m_masks.begin(), m_masks.end(), id), m_masks.end());
}

void Collision::SetLayer(int id) {
	m_layer = id;
}

int Collision::GetLayer() const {
	return m_layer;
}

RVector2 Collision::GetSize() const {
	return { m_collisionRec.width, m_collisionRec.height };
}

RVector2 Collision::GetPosition() const {
	return { m_collisionRec.x, m_collisionRec.y };
}

void Collision::SetPosition(RVector2 pos) {
	m_collisionRec.x = pos.x;
	m_collisionRec.y = pos.y;
}

void Collision::SetSize(RVector2 size) {
	m_collisionRec.width = size.x;
	m_collisionRec.height = size.y;
}

void Collision::OnCollisionEnter(Collision& other) {
	for (auto& callback : m_onCollisionEnterCallbacks) {
		callback(other);
	}
}

void Collision::OnCollisionRelease(Collision& other) {
	for (auto& callback : m_onCollisionReleaseCallbacks) {
		callback(other);
	}
}

void Collision::AddOnCollisionEnterCallback(CollisionCallback callback)
{
	m_onCollisionEnterCallbacks.push_back(callback);
}

void Collision::AddOnCollisionReleaseCallback(CollisionCallback callback)
{
	m_onCollisionReleaseCallbacks.push_back(callback);
}

void Collision::ShowCollisionRec(bool show)
{
	m_isShowRec = show;
}
