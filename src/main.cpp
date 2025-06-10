#include <iostream>
#include <string>
#include "view.h"
#include "controller.h"
#include "AnsiPrint.h"
#include "gameObjectFactory.h"
#include <ctime>
/**
 * Print my id
 * */
void
PrintMyID(std::string studId) {

    std::string str = "ID: " + studId;
    std::cout << AnsiPrint(str.c_str(),YELLOW,RED, true, true) << std::endl << std::endl;
}



int main(){
    // TODO 
    // Integrate the Simple MVC Pattern to run the program.
	
	srand(time(0));
	View view;
	Controller controller(view);

	GameObject* player = GameObjectFactory::createPlayer({10,10});
	controller.addGameObject(player,true);

	controller.addGameObject(GameObjectFactory::createBOMBPlayer({15,2}));
	controller.addGameObject(GameObjectFactory::createBOMBPlayer({6,5}));
	controller.addGameObject(GameObjectFactory::createBOMBPlayer({6,9}));
	controller.addGameObject(GameObjectFactory::createAPPLEPlayer({4,5}));
	controller.addGameObject(GameObjectFactory::createAPPLEPlayer({2,18}));
	controller.addGameObject(GameObjectFactory::createAPPLEPlayer({15,15}));
	controller.addGameObject(GameObjectFactory::createAPPLEPlayer({1,9}));
	controller.addGameObject(GameObjectFactory::createAPPLEPlayer({4,12}));
	controller.addGameObject(GameObjectFactory::createAPPLEPlayer({10,5}));
	controller.addGameObject(GameObjectFactory::createAPPLEPlayer({7,4}));

	controller.run();	

    // TODO
    // change to your student ID.
    PrintMyID("113703003");

	return 0;
}
