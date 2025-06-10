#include <iostream>
#include <ctime>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include <algorithm>

#include "environment.h"
#include "controller.h"
#include "gameObjectFactory.h"
#include "RPSGameObject.h"


Controller::Controller(View& view) : _view(view){
}

void Controller::run() {
    // initial setup
    std::cin.tie(0);
    std::ios::sync_with_stdio(0);
    configure_terminal();

    // init state
    int input = -1;
    clock_t start, end;
	int count=0;
	bool islose = false;
    
    // Main loop
    while (true) {
        start = clock();
        // game loop goes here
        input = read_input();

        // ESC to exit program
        if(input==27)break;

        this->handleInput(input);

        _view.resetLatest();
        for(GameObject* obj : _objs) 
        {
			if(obj != _player){
				auto* change_obj = dynamic_cast<RPSGameObject*>(obj);
				if(!change_obj) continue;
				if(change_obj->getType() != APPLE)
            		change_obj->update();
			}
            _view.updateGameObject(obj,_player);
			
        }

		//I add something here
		for(size_t i=0 ; i<_objs.size() ; ++i){
			for(size_t j=i+1 ; j<_objs.size() ; ++j){
				auto* A_objs = dynamic_cast<RPSGameObject*>(_objs[i]);
				if(!A_objs) continue;
				auto* B_objs = dynamic_cast<RPSGameObject*>(_objs[j]);
				if(!B_objs) continue;
				if (A_objs->intersect(B_objs)) {
					A_objs->onCollision(B_objs,count,islose);
					B_objs->onCollision(A_objs,count,islose);
				}
			}
		}

		this->cleanUpObjects();
		
		int appleNumber=0;
		for(size_t i=0 ; i<_objs.size() ; ++i){
			auto* findApple_objs = dynamic_cast<RPSGameObject*>(_objs[i]);
			if(findApple_objs->getType() == APPLE) appleNumber++;
		}

		//print
		if(islose || count>=4){
			_view.resetLatest();
			for(GameObject* obj : _objs) _view.updateGameObject(obj,_player);
			_view.render();
		}
		//print apple number
		std::cout << "You have " << count << " apple."<<"\n";

		if(islose){
			std::cout << "You are lose!" << "\n";
			break;
		}
		
		if( count+appleNumber<4){
			std::cout << "You are lose! There is not enough apples." << "\n";
			break;
		}

		if( count>=4 ){
			std::cout << "You are win!" << "\n";
			break;
		}

        _view.render();


        end = clock();

        // frame rate normalization
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        if (time_taken > SPF) continue;
        int frameDelay = int((SPF - time_taken) * 300); // 0.1 seconds
        if(frameDelay > 0) std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay)); // frame delay
    }

}



void Controller::handleInput(int keyInput){

    // If there is no input, do nothing.
    if(keyInput==-1 || !_player)return;
    

    // TODO 
    // handle key events.

	switch(keyInput){
		case 'w':_player->moveBy(0,-1); break;
		case 's':_player->moveBy(0,1); 	break;
		case 'a':_player->moveBy(-1,0); break;
		case 'd':_player->moveBy(1,0); 	break;
		case 9:switchPlayer(); 		break;
	}

	Position p = _player->getPosition();
	if (p.x() < 0) p.x() = 0;
	if (p.x() >= GAME_WINDOW_WIDTH)  p.x() = GAME_WINDOW_WIDTH - 1;
	if (p.y() < 0) p.y() = 0;
	if (p.y() >= GAME_WINDOW_HEIGHT) p.y() = GAME_WINDOW_HEIGHT - 1;
	_player->setPosition(p);
}

void Controller::switchPlayer(){

}

void Controller::update(){

}

void Controller::cleanUpObjects(){
	_objs.erase(
		std::remove_if(_objs.begin(),_objs.end(),
			[](GameObject* obj){
				auto* changed_obj = dynamic_cast<RPSGameObject*>(obj);
				if(changed_obj->toBeDeleted){
					delete changed_obj;
					return true;
				}
				return false;
			}),
		_objs.end()
	);
}

void Controller::addGameObject(GameObject* obj,bool isPlayer){
	_objs.push_back(obj);
	if(isPlayer) _player = obj;
}

void reset_terminal() {
    printf("\e[m"); // reset color changes
    printf("\e[?25h"); // show cursor
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

// terminal initial configuration setup
void configure_terminal() {
    tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios; // save it to be able to reset on exit
    
    new_termios.c_lflag &= ~(ICANON | ECHO); // turn off echo + non-canonical mode
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    printf("\e[?25l"); // hide cursor
    std::atexit(reset_terminal);
}


int read_input() {
    fflush(stdout);
   	char buf[4096]; // maximum input buffer
	int n = read(STDIN_FILENO, buf, sizeof(buf));
    return n > 0 ? buf[n - 1] : -1;
}
