#include "Node.h"
#include "MainLoop.h"
#include "SceneTree.h"
#include "core/raylib_cpp.h"

class Bullet : public Node {
public:
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


class Player : public Node {
public:
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
		
		//Remove a bullet
		if (RKeyboard::IsKeyPressed(KEY_S))
		{
			Bullet* bullet = dynamic_cast<Bullet*>(GetNode("Something/Bullet"));
			if (bullet)
			{
				RemoveChild(bullet);
			}
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
    }

	void _Render() override {
		DrawCircleV(position, 10.0f, RColor::Red());
	}

private:
	RVector2 position;
};

int main() {

	Scene* scene  = new Scene();
	scene->SetName("MainScene");

	Player* player = new Player();
	player->SetPosition(RVector2(100, 100));

	Node* something = new Node();
	something->SetName("Something");

	scene->AddChild(player);
	player->AddChild(something);

	SceneTree::GetInstance()->AddScene(scene);

	//Run the main loop
	MainLoop::GetInstance()->Run();
}