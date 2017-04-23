#include "MenuState.h"

#include <iostream>

using namespace std;

const string MenuState::s_menuID = "MENU";

void MenuState::update(){

}

void MenuState::render(){

}

bool MenuState::onEnter(){
	cout << "Entering MenuState" << endl;

	return true;
}

bool MenuState::onExit(){
	cout << "Exiting MenuState" << endl;

	return true;
}
