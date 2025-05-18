#include "Node.h"
#include "MainLoop.h"
#include "SceneTree.h"
#include "core/Color.h"
#include "engine/manager/InputManager.h"
#include "engine/manager/AudioManager.h"
#include "engine/manager/RenderManager.h"
#include "engine/manager/CollisionManager.h"
#include "vld.h"


/// A simple player class that inherits from Node
class Player : public Node {
public:
	virtual void SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) override {
		element->SetAttribute("x", position.x);
		element->SetAttribute("y", position.y);
		Node::SerializeToXML(element, doc);
	}

	virtual void DeserializeFromXML(tinyxml2::XMLElement* element) override {
		element->QueryFloatAttribute("x", &position.x);
		element->QueryFloatAttribute("y", &position.y);
		Node::DeserializeFromXML(element);
	}

	virtual void _Ready() override {
		if (HasChild("Collision"))
		{
			collision = dynamic_cast<Collision*>(GetNode("Collision"));
			CollisionManager::GetInstance()->AddCollision(collision);
		}
	}

	virtual void _Update(float dt) override {
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

	virtual void _Render() override {
		RenderManager::GetInstance()->DrawCircleV(position, 20, BLUE);
		if (collision)
		{
			RenderManager::GetInstance()->DrawRectangleLinesV(collision->GetPosition(), collision->GetSize(), RED);
		}
	}

	virtual void _Destroy() override {
		CollisionManager::GetInstance()->RemoveCollision(collision);
	}

private:
	RVector2 position;
	Collision* collision;
};
REGISTER_NODE_CLASS(Player);

/// A simple box class that inherits from Node
class Box : public Node {

public:
	virtual void SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) override {
		Node::SerializeToXML(element, doc);
	}
	virtual void DeserializeFromXML(tinyxml2::XMLElement* element) override {
		Node::DeserializeFromXML(element);
	}

	virtual void _Ready() override {
		if (HasChild("Collision"))
		{
			collision = dynamic_cast<Collision*>(GetNode("Collision"));
			CollisionManager::GetInstance()->AddCollision(collision);
		}

		// Set up collision detection
		collision->AddOnCollisionEnterCallback(std::bind(&Box::OnCollisionEnter, this, std::placeholders::_1));
	}

	virtual void _Update(float dt) override {
	}

	virtual void _Render() override {
		if (collision)
		{
			RenderManager::GetInstance()->DrawRectangleLinesV(collision->GetPosition(), collision->GetSize(), YELLOW);
		}
	}

	virtual void _Destroy() override {
		CollisionManager::GetInstance()->RemoveCollision(collision);
	}

	void OnCollisionEnter(Collision& other) {
		if (other.GetParent()->GetName() == "Player") {
			printf("Box collided with Player\n");
			// destroy this box
			CollisionManager::GetInstance()->RemoveCollision(collision);
			GetParent()->RemoveChild(this);// must have better way:)
		}
	}

private:
	Collision* collision;
};
REGISTER_NODE_CLASS(Box);

class World : public Node {
public:
	virtual void SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) override {
		Node::SerializeToXML(element, doc);
	}

	virtual void DeserializeFromXML(tinyxml2::XMLElement* element) override {
		Node::DeserializeFromXML(element);
	}

	virtual void _Update(float dt) override {
		if (InputManager::GetInstance()->IsKeyPressed(KEY_SPACE))
		{
			SceneTree::GetInstance()->SaveCurrentSceneToXML(GAME_SCENE_FILE);
		}

		if (InputManager::GetInstance()->IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			RVector2 mousePos = InputManager::GetInstance()->GetMousePosition();
			Box* box = new Box();
			Collision* collision = new Collision(mousePos.x, mousePos.y, 40, 40);
			box->AddChild(collision);
			AddChild(box);
		}
	}
};
REGISTER_NODE_CLASS(World);

int main() {
	if (SceneTree::GetInstance()->LoadSceneFromXML(GAME_SCENE_FILE))
	{
		MainLoop::GetInstance()->Run();
	}
	else {

		Scene* scene = new Scene();
		scene->SetName("MainScene");

		World* world = new World();
		Player* player = new Player();
		Box* box = new Box();

		Collision* playerCollision = new Collision(0, 0, 40, 40);
		Collision* boxCollision = new Collision(200, 200, 40, 40);

		player->AddChild(playerCollision);
		box->AddChild(boxCollision);
		world->AddChild(player);
		world->AddChild(box);
		scene->AddChild(world);

		SceneTree::GetInstance()->AddScene(scene);
		//Run the main loop
		MainLoop::GetInstance()->Run();
	}

}