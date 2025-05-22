#include "Player.h"
#include "manager/CollisionManager.h"
#include "manager/InputManager.h"
#include "manager/RenderManager.h"
#include "MainLoop.h"

void Player::SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) {
	element->SetAttribute("x", position.x);
	element->SetAttribute("y", position.y);
	Node::SerializeToXML(element, doc);
}

void Player::DeserializeFromXML(tinyxml2::XMLElement* element) {
	element->QueryFloatAttribute("x", &position.x);
	element->QueryFloatAttribute("y", &position.y);
	Node::DeserializeFromXML(element);
}

void Player::_Ready() {
	int windowWidth = MainLoop::GetInstance()->GetWidth();
	int windowHeight = MainLoop::GetInstance()->GetHeight();

	position = RVector2(windowWidth / 2.0f, windowHeight / 2.0f);
	if (HasChildWithType("Collision"))
	{
		collision = dynamic_cast<Collision*>(GetChildByType("Collision"));
		CollisionManager::GetInstance()->AddCollision(collision);
	}
	else
	{
		collision = new Collision(position.x, position.y, 25.0f, 25.0f);
		AddChild(collision);
		CollisionManager::GetInstance()->AddCollision(collision);
	}
}

void Player::_Update(float dt) {
	//move
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
		collision->SetPosition(position - collision->GetSize() / 2.0f);
	}
}

void Player::_Render() {
	RenderManager::GetInstance()->DrawCircleV(position, 20, BLUE);
}

void Player::_Destroy() {
	CollisionManager::GetInstance()->RemoveCollision(collision);
}
