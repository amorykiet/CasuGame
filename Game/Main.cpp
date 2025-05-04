#include "Node.h"
#include "MainLoop.h"
#include "SceneTree.h"
#include "core/raylib_cpp.h"

class MyNode : public Node {
public:
	void SetPosition(RVector2 pos) {
		position = pos;
	}


    void _Update(float delta) override {  

	   // Check for key press to add a child node
       if (RKeyboard::IsKeyPressed(KEY_S))  
       {  
           MyNode* node = new MyNode();  
           node->SetName("MyNode1");  
           node->SetPosition(RVector2(30.0f, 100.0f));  
           AddChild(node);  
       }  

	   // Check for key press to remove a child node
       if (RKeyboard::IsKeyPressed(KEY_D))  
       {  
           Node* child = nullptr;  
           for (auto& c : m_childs)
           {  
               if (c->GetName() == "MyNode1")  
               {  
                   child = c;  
                   break;  
               }  
           }  
           if (child)  
           {  
               RemoveChild(child);  
           }  
       } 

	   // Auto move the node to the right
       position.x += 10.0f * delta;
       
	   // Move the node to the left
       if (RKeyboard::IsKeyPressed(KEY_A))
       {
           position.x -= 10.0f;
       }
    }

	void _Render() override {
		DrawCircleV(position, 10.0f, RColor::Red());
	}

private:
	RVector2 position;
};



int main() {

	//Create scene tree
    //  MyNode
    //  |--node1
	//  |  |--node3
	//  |--node2
	MyNode* node = new MyNode();
	node->SetName("MyNode");
	node->SetPosition(RVector2(30.0f, 50.0f));

	Node* node1 = new Node();
	node1->SetName("node1");
	Node* node2 = new Node();
	node2->SetName("node2");
	Node* node3 = new Node();
	node3->SetName("node3");

	node->AddChild(node1);
	node->AddChild(node2);
	node1->AddChild(node3);

	SceneTree::GetInstance()->AddScene(node);

	//Run the main loop
	MainLoop::GetInstance()->Run();
}