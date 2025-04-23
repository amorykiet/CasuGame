#include "core/raylib_cpp.h"
#include "core/EntityManager.h"
#include "Circle.h"
#include "core/GameLoop.h"

int main() {

	Circle* circle = new Circle(RVector2(30, 30), 20, raylib::Color::Red());

	EntityManager::GetInstance()->AddEntity(circle);
    
	GameLoop::GetInstance()->Run();

    return 0;
}