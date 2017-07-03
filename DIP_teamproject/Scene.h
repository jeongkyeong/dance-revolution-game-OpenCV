#ifndef SCENE_H
#define SCENE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>
#include "Constants.h"
#include "MidiParserIP.h"
#include "Input.h"

using namespace cv;
using namespace std;
class Scene {
protected:


public:
	Song _song;
	Music _music;
	sf::RenderWindow &_screen;
	input _input;
	int beatsPerBoard;
	std::vector<std::pair<std::pair<int, int>, int>> _notes;

	sf::Texture downLeft;
	sf::Texture downRight;
	sf::Texture upLeft;
	sf::Texture upRight;

	sf::Texture downLeftActive;
	sf::Texture downRightActive;
	sf::Texture upLeftActive;
	sf::Texture upRightActive;

	sf::Texture center;
	sf::Texture glow;

	sf::Sprite sprite1, sprite2, sprite3, sprite4;

	int score;
	float centerTargetsDistance;

	sf::Font font;
	sf::Time sceneClock;
	sf::Sprite sprite;
	sf::Image image;
	Constants constants;
	float arrowTimeRelation;

	int opacityGlow[4];
	int backgroundColor[3];
public:


public:
	Scene(int Resource, sf::RenderWindow &Screen, input Input, int BeatsPerBoard);
	//Scene();
	~Scene();
	void blitAlpha(sf::Texture source, int x, int y, int opacity); // def blitAlpha(self, source, location, opacity):
	void handleNotes(sf::Clock clock); // def handleNotes(self):
	void renderNote(sf::Clock clock); // def renderNote(self, number, delta):
	void calculateCenterTargetsDistance(); // def calculateCenterTargetsDistance(self):
	void renderCenterTargets(); // def renderCenterTargets(self) :
	void renderCornerTargets(); // def renderCornerTargets(self):
	void renderWebCam(); // def renderWebCam(self):
	void render(sf::Clock clock); // def render(self):
	void renderGlow(); // def renderGlow(self):
	void fadeGlow(); // def fadeGlow(self):
	void handleRequiredNotes(vector<string> notes); // def handleRequiredNotes(self, notes):
	void renderScore(); // def renderScore(self):
	void updateScore(); // def updateScore(self):
	void run(input in, sf::Clock clock); // def run(self):
};

#endif