#include "Enemy.h"
#include "manager/CollisionManager.h"
#include "manager/RenderManager.h"
#include "SceneTree.h"
#include "MainLoop.h"

void Enemy::SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) {
	element->SetAttribute("x", position.x);
	element->SetAttribute("y", position.y);
	element->SetAttribute("size", size);
	element->SetAttribute("directionX", direction.x);
	element->SetAttribute("directionY", direction.y);
    Node::SerializeToXML(element, doc);
}

void Enemy::DeserializeFromXML(tinyxml2::XMLElement* element) {
	element->QueryFloatAttribute("x", &position.x);
	element->QueryFloatAttribute("y", &position.y);
	element->QueryIntAttribute("size", &size);
	element->QueryFloatAttribute("directionX", &direction.x);
	element->QueryFloatAttribute("directionY", &direction.y);
    Node::DeserializeFromXML(element);
}

void Enemy::_Ready() {
    if (HasChildWithType("Collision"))
    {
        collision = dynamic_cast<Collision*>(GetChildByType("Collision"));
        CollisionManager::GetInstance()->AddCollision(collision);
    }
	else
	{
		collision = new Collision(position.x, position.y, 20.0f, 20.0f);
		AddChild(collision);
		CollisionManager::GetInstance()->AddCollision(collision);
	}
    // Set up collision detection
    collision->AddOnCollisionEnterCallback(std::bind(&Enemy::OnCollisionEnter, this, std::placeholders::_1));
	size = collision->GetSize().x;
}

void Enemy::_Update(float dt) {
	// Move the enemy in the direction
	position.x += direction.x * speed * dt;
	position.y += direction.y * speed * dt;
	if (collision)
	{
		collision->SetPosition(position - collision->GetSize() / 2.0f);
	}

    // Out of window
	int windowWidth = MainLoop::GetInstance()->GetWidth();
	int windowHeight = MainLoop::GetInstance()->GetHeight();

	float padding = 20.0f;
	if (position.x < -padding|| position.x > windowWidth + padding|| position.y < - padding || position.y > windowHeight + padding)
	{
        CollisionManager::GetInstance()->RemoveCollision(collision);
		GetParent()->RemoveChild(this);
	}
}

void Enemy::_Render() {	
    RenderManager::GetInstance()->DrawCircleV(position, size, RED);
}

void Enemy::_Destroy() {
    CollisionManager::GetInstance()->RemoveCollision(collision);
}

void Enemy::OnCollisionEnter(Collision& other) {
    if (other.GetParent()->GetType() == "Player") {
        printf("Enemy collided with Player\n");
        NotifyPlayerHit();
        CollisionManager::GetInstance()->RemoveCollision(collision);
		Remove();
    }
}
