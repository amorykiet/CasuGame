#include "Player.h"
#include "manager/CollisionManager.h"
#include "manager/InputManager.h"
#include "manager/RenderManager.h"
#include "MainLoop.h"

#include "imgui.h"

void Player::_SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) {
	element->SetAttribute("x", position.x);
	element->SetAttribute("y", position.y);
	element->SetAttribute("size", size);
	Node::_SerializeToXML(element, doc);
}

void Player::_DeserializeFromXML(tinyxml2::XMLElement* element) {
	element->QueryFloatAttribute("x", &position.x);
	element->QueryFloatAttribute("y", &position.y);
	element->QueryFloatAttribute("size", &size);
	Node::_DeserializeFromXML(element);
}

void Player::_ShowInspector()
{
	Node::_ShowInspector();
	ImGui::Separator();
	ImGui::InputFloat("Position X", &position.x);
	ImGui::InputFloat("Position Y", &position.y);
	ImGui::InputFloat("Size", &size);
}

void Player::_Ready() {
	int windowWidth = MainLoop::GetInstance()->GetWidth();
	int windowHeight = MainLoop::GetInstance()->GetHeight();

	position = RVector2(windowWidth / 2.0f, windowHeight / 2.0f);
	if (HasChildWithType("Collision"))
	{
		collision = dynamic_cast<Collision*>(GetChildByType("Collision"));
		CollisionManager::GetInstance()->AddCollision(collision);
		collisionOffset = collision->GetPosition();
	}
}

void Player::_Update(float dt) {
	//movement logic
	if (InputManager::GetInstance()->IsKeyDown(KEY_W)) {
		position.y -= 100 * dt;
	}
	else if (InputManager::GetInstance()->IsKeyDown(KEY_S)) {
		position.y += 100 * dt;
	}
	if (InputManager::GetInstance()->IsKeyDown(KEY_A)) {
		position.x -= 100 * dt;
	}
	else if (InputManager::GetInstance()->IsKeyDown(KEY_D)) {
		position.x += 100 * dt;
	}

	//update collision position
	if (collision)
	{
		collision->SetPosition(position + collisionOffset);
	}
}

void Player::_Render() {
#ifdef USE_TEXTURE
	RenderManager::GetInstance()->DrawTexturePro("assets/texture/player.png",
		RRectangle(0, 0, 64, 64),
		RRectangle(position.x - size/2, position.y - size/2, size, size));
#else
	RenderManager::GetInstance()->DrawCircleV(position, size, BLUE);
#endif

}

void Player::_Destroy() {
	CollisionManager::GetInstance()->RemoveCollision(collision);
}

RVector2 Player::GetPosition()
{
	return position;
}
