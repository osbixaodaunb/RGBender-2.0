#include "PlayState.h"

#include <string>
#include <iostream>

using namespace std;

const string PlayState::s_playID = "PLAY";

void PlayState::update(){

}

void PlayState::render(){

}

bool PlayState::onEnter(){
	cout <<	"Entering PlayState" << endl;
	return true;
}

bool PlayState::onExit(){
	cout << "Exiting PlayState" << endl;	
	return false;
}
