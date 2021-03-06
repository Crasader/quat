#include "Game.h"

#include "Theme.h"

#include "themes/RankTheme.h"

namespace QUAT {

Game::Game() {
	this->user = new User();

	// Initialize the vector of themes
	this->themes = new std::map<std::string, Theme *>();

	// Create the default rank theme and add it to our map of themes
	(*this->themes)[std::string("RANK")] = new RankTheme();

	// Sets the game's theme to be RANK (this is just a placeholder)
	this->setTheme(new std::string("RANK"));

	// Update the theme to reflect the user's current rank
	// This, too, can be moved at some point. It probably should not be in
	// the constructor. 
	this->theme->update(this);
}

bool Game::canLoadFromLocal() {
  string path = this->getSaveFileName();
  return cocos2d::FileUtils::getInstance()->isFileExist(path);
}


User * Game::getUser() {
	return this->user;
}

GameState * Game::getState() {
	return this->user->getGameState();
}

Puzzle * Game::getPuzzle() {
	return this->user->getGameState()->getPuzzle();
}

Blitzer * Game::getBlitzer() {
	return this->user->getGameState()->getBlitzer();
}

std::string Game::getSaveFileName() {
  string path = cocos2d::FileUtils::getInstance()->getWritablePath();
  return std::string(path + "save.quat");
}
void Game::loadFromLocal() {
  string path = this->getSaveFileName();
  ifstream input(path);
  
  // Initialize a quat stream
  QuatStream inStream(&input);
  this->user->serialize(inStream);

  input.close();
}

Theme * Game::getTheme() {
	return this->theme;
}

void Game::updateTheme() {
	this->theme->update(this);
}

void Game::setTheme(std::string * themeName) {
	this->theme = (*this->themes)[*themeName];
}


void Game::saveToLocal() {
  string path = this->getSaveFileName();
  ofstream output(path);
  
  // Initialize a quat stream
  QuatStream outStream(&output);
  this->user->serialize(outStream);

  output.close();
}

void Game::update(float secs) {
  this->user->update(secs);
}

}
