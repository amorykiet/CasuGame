#include "Node.h"
#include "MainLoop.h"
#include "SceneTree.h"
#include "core/raylib_cpp.h"

class Bullet : public Node {
public:

	virtual void SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) override {
		element->SetAttribute("direction", direction);
		element->SetAttribute("position_x", position.x);
		element->SetAttribute("position_y", position.y);
		Node::SerializeToXML(element, doc);
	}

	virtual void DeserializeFromXML(tinyxml2::XMLElement* element) override {
		element->QueryIntAttribute("direction", &direction);
		element->QueryFloatAttribute("position_x", &position.x);
		element->QueryFloatAttribute("position_y", &position.y);
		Node::DeserializeFromXML(element);
	}

	void SetPosition(RVector2 pos) {
		position = pos;
	}
	void _Update(float delta) override {
		position.x += 10.0f * direction * delta;
	}
	void _Render() override {
		DrawCircleV(position, 5.0f, RColor::Blue());
	}

	void ChangeDirection() {
		direction *= -1;
	}

private:
	RVector2 position;
	int direction = 1;
};

REGISTER_NODE_CLASS(Bullet);

class Player : public Node {
public:

	virtual void SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) override {
		element->SetAttribute("position_x", position.x);
		element->SetAttribute("position_y", position.y);
		Node::SerializeToXML(element, doc);
	}

	virtual void DeserializeFromXML(tinyxml2::XMLElement* element) override {
		element->QueryFloatAttribute("position_x", &position.x);
		element->QueryFloatAttribute("position_y", &position.y);
		Node::DeserializeFromXML(element);
	}

	void SetPosition(RVector2 pos) {
		position = pos;
	}

    void _Update(float delta) override {  
		
		//Fire a bullet
		if (RKeyboard::IsKeyPressed(KEY_SPACE))
		{
			Bullet* bullet = new Bullet();
			bullet->SetPosition(position);

			GetNode("Something")->AddChild(bullet);
		}


	   // Move the node
       if (RKeyboard::IsKeyDown(KEY_LEFT))
       {
           position.x -= 100.0f * delta;
       }
	   else if (RKeyboard::IsKeyDown(KEY_RIGHT))
	   {
		   position.x += 100.0f * delta;
	   }
	   else if (RKeyboard::IsKeyDown(KEY_UP))
	   {
		   position.y -= 100.0f * delta;
	   }
	   else if (RKeyboard::IsKeyDown(KEY_DOWN))
	   {
		   position.y += 100.0f * delta;
	   }


	   //Test save scene
	   if (RKeyboard::IsKeyPressed(KEY_S))
	   {
		   printf("Saving scene\n");
		   SceneTree::GetInstance()->SaveCurrentSceneToXML("scene.config");
	   }
    }

	void _Render() override {
		DrawCircleV(position, 10.0f, RColor::Red());
	}

private:
	RVector2 position;
};

REGISTER_NODE_CLASS(Player);

int main() {

	if (SceneTree::GetInstance()->LoadSceneFromXML(GAME_SCENE_FILE)) {
		printf("Scene loaded successfully\n");
	}
	else
	{
		printf("Failed to load scene\n");
		printf("Creating a new scene manually\n");

		Scene* scene = new Scene();
		scene->SetName("MainScene");

		Player* player = new Player();
		player->SetPosition(RVector2(100, 100));

		Node* something = new Node();
		something->SetName("Something");

		scene->AddChild(player);
		player->AddChild(something);

		SceneTree::GetInstance()->AddScene(scene);
	}

	//Run the main loop
	MainLoop::GetInstance()->Run();
}