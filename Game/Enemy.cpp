#include "Enemy.h"
#include "manager/CollisionManager.h"
#include "manager/RenderManager.h"
#include "SceneTree.h"
#include "MainLoop.h"

#include "imgui.h"

#include "manager/AudioManager.h"

#ifdef USE_TEXTURE
#include "raymath.h"
#endif

void Enemy::_SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) {
	element->SetAttribute("x", position.x);
	element->SetAttribute("y", position.y);
	element->SetAttribute("size", size);
	element->SetAttribute("directionX", direction.x);
	element->SetAttribute("directionY", direction.y);
	element->SetAttribute("speed", speed);
    Node::_SerializeToXML(element, doc);
}

void Enemy::_DeserializeFromXML(tinyxml2::XMLElement* element) {
	element->QueryFloatAttribute("x", &position.x);
	element->QueryFloatAttribute("y", &position.y);
	element->QueryIntAttribute("size", &size);
	element->QueryFloatAttribute("directionX", &direction.x);
	element->QueryFloatAttribute("directionY", &direction.y);
	element->QueryFloatAttribute("speed", &speed);
    Node::_DeserializeFromXML(element);
}

void Enemy::_ShowInspector()
{
	Node::_ShowInspector();
	ImGui::Separator();
	ImGui::InputFloat("Position X", &position.x);
	ImGui::InputFloat("Position Y", &position.y);
	ImGui::InputInt("Size", &size);
	ImGui::InputFloat("Speed", &speed);
	ImGui::InputFloat("Direction X", &direction.x);
	ImGui::InputFloat("Direction Y", &direction.y);
}

void Enemy::_Ready() {
    if (HasChildWithType("Collision"))
    {
        collision = dynamic_cast<Collision*>(GetChildByType("Collision"));
        CollisionManager::GetInstance()->AddCollision(collision);
		collision->AddOnCollisionEnterCallback(std::bind(&Enemy::OnCollisionEnter, this, std::placeholders::_1));
		collisionOffset = collision->GetPosition();
    }
}

void Enemy::_Update(float dt) {
	// Move the enemy in the direction
	position.x += direction.x * speed * dt;
	position.y += direction.y * speed * dt;
	if (collision)
	{
		collision->SetPosition(position + collisionOffset);
	}

    // Out of window
	int windowWidth = MainLoop::GetInstance()->GetWidth();
	int windowHeight = MainLoop::GetInstance()->GetHeight();

	float padding = 20.0f;
	if (position.x < -padding|| position.x > windowWidth + padding|| position.y < - padding || position.y > windowHeight + padding)
	{
        CollisionManager::GetInstance()->RemoveCollision(collision);
		Remove();
	}
}

void Enemy::_Render() {	
#ifdef USE_TEXTURE
	float rotation = Vector2Angle(RVector2(0, -1), direction) * (180.0f / PI);

	RenderManager::GetInstance()->DrawTexturePro("assets/texture/enemy.png",
		RRectangle(0, 0, 128, 128),
		RRectangle(position.x, position.y, size, size),
		RVector2(size/2, size/8),
		rotation);
#else
    RenderManager::GetInstance()->DrawCircleV(position, size, RED);
#endif
}

void Enemy::_Destroy() {
    CollisionManager::GetInstance()->RemoveCollision(collision);
}

void Enemy::SetPlayerHitCallback(PlayerHit callback)
{
	playerHitCallback = callback;
}

void Enemy::NotifyPlayerHit()
{
	if (playerHitCallback)
	{
		playerHitCallback();
	}
}

Collision* Enemy::GetCollision() {
	return collision;
}

void Enemy::SetPosition(RVector2 pos) {
	position = pos;
}

void Enemy::SetDirection(RVector2 dir) {
	direction = dir;
}

void Enemy::SetSpeed(float spd) {
	speed = spd;
}

void Enemy::OnCollisionEnter(Collision& other) {
    if (other.GetParent()->GetType() == "Player") {
		AudioManager::GetInstance()->PlaySound("assets/sound/coin.wav");
        printf("Enemy collided with Player\n");
        NotifyPlayerHit();
        CollisionManager::GetInstance()->RemoveCollision(collision);
		Remove();
    }
}
