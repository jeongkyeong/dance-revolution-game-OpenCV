//#include <iostream>
#include <math.h>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML/Audio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <SFML/System/Vector2.hpp>
#include "Audio.h"

using namespace cv;

//#include "Song.h"
#include "Input.h"


#include "Scene.h"


Scene::Scene(int Resource, sf::RenderWindow &screen, input Input, int BeatsPerBoard = 2) : _screen(screen)
{

	//_notes = new std::vector < std::pair<int, int>>;
	Music *_music = new Music("../Ressources/ClintEastwood.ogg");
	_music->play();

	//parameter type is int in temporary
	//not use any Resource

	_input = Input;
	//_song = __song;

	downLeft.loadFromFile("../Ressources/DownLeft.png");
	downRight.loadFromFile("../Ressources/DownRight.png");
	upLeft.loadFromFile("../Ressources/UpLeft.png");
	upRight.loadFromFile("../Ressources/UpRight.png");

	downLeftActive.loadFromFile("../Ressources/DownLeftActive.png");
	downRightActive.loadFromFile("../Ressources/DownRightActive.png");
	upLeftActive.loadFromFile("../Ressources/UpLeftActive.png");
	upRightActive.loadFromFile("../Ressources/UpRightActive.png");

	center.loadFromFile("../Ressources/Center.png");
	glow.loadFromFile("../Ressources/Glow.png");

	//ALL IMAGES HAVE SAME HEIGHT AND WIDTH
	constants.SPRITE_SIZE = glow.getSize().x;

	beatsPerBoard = BeatsPerBoard;

	backgroundColor[3] = { 0 };
	score = 0;

	font.loadFromFile("../Ressources/font.ttf");

	for (int i = 0; i < 4; i++) {
		opacityGlow[i] = 0;
	}

	calculateCenterTargetsDistance();

	constants.SQRT_2 = sqrt(2);

	float targetsHypotenuse = sqrt((2 * centerTargetsDistance - constants.SPRITE_SIZE)*(centerTargetsDistance - constants.SPRITE_SIZE));

	arrowTimeRelation = beatsPerBoard / targetsHypotenuse;

	//_song.play();

	//run();//call main loop
}

Scene::~Scene() {}

////////////////////////////////
void Scene::blitAlpha(sf::Texture source, int x, int y, int opacity) {



	/*
	temp = pygame.Surface((source.get_width(), source.get_height())).convert()
	temp.blit(self.screen, (-x, -y))
	temp.blit(source, (0, 0))
	temp.set_alpha(opacity)
	self.screen.blit(temp, location)
	*/

}

void Scene::handleNotes(sf::Clock clock) {
	sf::Time T1 = clock.getElapsedTime();
	int nbr = T1.asSeconds();
	if ((nbr % 3) == 1) {
		_notes.push_back(std::make_pair(std::make_pair(200, 200), 0));
	}
	renderNote(clock);
	/*
	sf::Time pos = _song.getPlayingOffset(); //pos = self.song.getPosition()
	int track = _song.getChannelCount(); //track = self.song.track
	sf::Time period = _song.getDuration(); //period = self.song.period
	sf::Time delay; //delay = self.song.delay

	for (vector<string>::iterator it = event.begin(); it != event.end(); ++it){
	sf::Time delta = time - pos + delay + sceneClock.asMicroseconds; //screenDelay
	delta = delta / period;
	renderNote(number, delta);

	}
	*/
	/*
	for time, event in track.getUnplayedNotes(pos - delay - self.screenDelay - period * 2 , pos - delay - self.screenDelay + period * self.beatsPerBoard):
	delta = time - pos + delay + self.screenDelay
	delta = delta / period
	self.renderNote(event.number, delta)
	*/
}


/*sf::Vector2u normalize(const sf::Vector2u& source)
{
float length = sqrt((source.x * source.x) + (source.y * source.y));
if (length != 0)
return sf::Vector2u(source.x / length, source.y / length);
else
return source;
}*/

void Scene::renderNote(sf::Clock clock) {
	float d = clock.restart().asSeconds() * 60;
	float d2 = d / constants.SQRT_2;

	sf::Time animationTime;
	int frameTime = 50;
	animationTime += clock.getElapsedTime();
	/*for (std::vector<std::pair<std::pair<int, int>, int>>::iterator it = _notes.begin(); it != _notes.end(); ++it) {
	sf::Sprite sprite;

	switch (it->second) {
	case 0:
	sprite.setTexture(upLeft);
	sprite.setPosition(it->first.first, it->first.second);
	sf::Vector2f temp;
	temp = normalize(temp);
	float velocity = 1.5f;
	sf::Vector2u direction = normalize(sprite.getPosition() - sprite1.getPosition());
	sprite.move(d * direction);
	_screen.draw(sprite);
	//screen.blit(upLeft,(d2,d2))
	case 1:
	sprite.setTexture(upRight);
	sprite.setPosition(constants.SCREEN_WIDTH - d2 - constants.SPRITE_SIZE, d2);
	_screen.draw(sprite);
	//screen.blit(upRight, (constants.SCREEN_WIDTH - d2 - constants.SPRITE_SIZE, d2));
	case 2:
	sprite.setTexture(downLeft);
	sprite.setPosition(d2, constants.SCREEN_HEIGHT - d2 - constants.SPRITE_SIZE);
	_screen.draw(sprite);
	//screen.blit(downLeft, (d2, constants.SCREEN_HEIGHT - d2 - constants.SPRITE_SIZE));
	case 3:
	sprite.setTexture(downRight);
	sprite.setPosition(constants.SCREEN_WIDTH - d2 - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - d2 - constants.SPRITE_SIZE);
	_screen.draw(sprite);
	//screen.blit(downRight, (constants.SCREEN_WIDTH - d2 - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - d2 - constants.SPRITE_SIZE));
	}
	}
	*/
}

void Scene::calculateCenterTargetsDistance() {
	if (constants.SCREEN_HEIGHT / 2 > constants.SCREEN_WIDTH / 2) {
		centerTargetsDistance = constants.SCREEN_WIDTH / 2;
	}
	else {
		centerTargetsDistance = constants.SCREEN_HEIGHT / 2;
	}
}

void Scene::renderCenterTargets() {

	sprite1.setTexture(center);
	sprite1.setPosition(centerTargetsDistance - constants.SPRITE_SIZE, centerTargetsDistance - constants.SPRITE_SIZE);
	_screen.draw(sprite1);
	//screen.blit(center, (centerTargetsDistance - constants.SPRITE_SIZE, centerTargetsDistance - constants.SPRITE_SIZE));

	sprite2.setTexture(center);
	sprite2.setPosition(constants.SCREEN_WIDTH - centerTargetsDistance, centerTargetsDistance - constants.SPRITE_SIZE);
	_screen.draw(sprite2);
	//screen.blit(center, (constants.SCREEN_WIDTH - centerTargetsDistance, centerTargetsDistance - constants.SPRITE_SIZE));

	sprite3.setTexture(center);
	sprite3.setPosition(centerTargetsDistance - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - centerTargetsDistance);
	_screen.draw(sprite3);
	//screen.blit(center, (centerTargetsDistance - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - centerTargetsDistance));

	sprite4.setTexture(center);
	sprite4.setPosition(constants.SCREEN_WIDTH - centerTargetsDistance, constants.SCREEN_HEIGHT - centerTargetsDistance);
	_screen.draw(sprite4);
	//screen.blit(center, (constants.SCREEN_WIDTH - centerTargetsDistance, constants.SCREEN_HEIGHT - centerTargetsDistance));

}

void Scene::renderCornerTargets() {

	sf::Sprite sprite0, sprite1, sprite2, sprite3;

	if (_input.isActive(0)) {
		sprite0.setTexture(upLeftActive);
		sprite0.setPosition(0, 0);
		_screen.draw(sprite0);
		//screen.blit(upLeftActive, (0, 0));
	}
	else {
		sprite0.setTexture(upLeft);
		sprite0.setPosition(0, 0);
		_screen.draw(sprite0);
		//screen.blit(upLeft, (0, 0));
	}

	if (_input.isActive(1)) {
		sprite1.setTexture(upRightActive);
		sprite1.setPosition(constants.SCREEN_WIDTH - constants.SPRITE_SIZE, 0);
		_screen.draw(sprite1);
		//screen.blit(upRightActive, (constants.SCREEN_WIDTH - constants.SPRITE_SIZE, 0));
	}
	else {
		sprite1.setTexture(upRight);
		sprite1.setPosition(constants.SCREEN_WIDTH - constants.SPRITE_SIZE, 0);
		_screen.draw(sprite1);
		//screen.blit(upRight, (constants.SCREEN_WIDTH - constants.SPRITE_SIZE, 0));
	}


	if (_input.isActive(2)) {
		sprite2.setTexture(downLeftActive);
		sprite2.setPosition(0, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE);
		_screen.draw(sprite2);
		//screen.blit(downLeftActive, (0, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE));
	}
	else {
		sprite2.setTexture(downLeft);
		sprite2.setPosition(0, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE);
		_screen.draw(sprite2);
		//screen.blit(downLeft, (0, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE));
	}


	if (_input.isActive(3)) {
		sprite3.setTexture(downRightActive);
		sprite3.setPosition(constants.SCREEN_WIDTH - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE);
		_screen.draw(sprite3);
		//screen.blit(downRightActive, (constants.SCREEN_WIDTH - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE));
	}
	else {
		sprite3.setTexture(downRight);
		sprite3.setPosition(constants.SCREEN_WIDTH - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE);
		_screen.draw(sprite3);
		//screen.blit(downRight, (constants.SCREEN_WIDTH - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE));
	}

}

void Scene::renderWebCam() {
	sf::Image frame = _input.getCurrentFrameAsImage(); //From input
	sf::Texture textureFrame; //convert to texture type for draw on the screen
	textureFrame.loadFromImage(frame);

	sf::Sprite sprite;
	sprite.setTexture(textureFrame);
	sprite.setPosition(0, 0);
	//sprite.setTextureRect(sf::IntRect(constants.SCREEN_WIDTH, 0, -constants.SCREEN_WIDTH, constants.SCREEN_HEIGHT));
	//sprite.scale(-1.f, 1.f);
	_screen.draw(sprite);
	//_screen.display();
	//screen.blit(frame, (0, 0));
}

void Scene::render(sf::Clock clock) {
	renderWebCam();
	renderCornerTargets();
	//handleNotes(clock);
	renderCenterTargets();
	renderGlow();
	fadeGlow();
	renderScore();
}

void Scene::renderGlow() {

	blitAlpha(glow, 0, 0, opacityGlow[0]);
	blitAlpha(glow, constants.SCREEN_WIDTH - constants.SPRITE_SIZE, 0, opacityGlow[1]);
	blitAlpha(glow, 0, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE, opacityGlow[2]);
	blitAlpha(glow, constants.SCREEN_WIDTH - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE, opacityGlow[3]);

}

void Scene::fadeGlow() {

	for (int i = 0; i < 4; i++) {
		if (opacityGlow[i] > 0) {
			opacityGlow[i] -= constants.GLOW_FADE;
		}
	}
}

void Scene::handleRequiredNotes(vector<string> notes) {

	bool arrows[4] = { false, false, false, false };
	/*
	for (vector<string>::iterator it = notes.begin(); it != notes.end(); ++it) {
	if (_input.toggled(notes.number)){
	if (arrows[notes.number] == false){
	score += 50;
	notes.played = true;
	arrows[notes.number] = true;
	opacityGlow[notes.number] = sf::Color(255);
	}
	}
	}
	*/
	///done
	/*
	arrows = [False, False, False, False]
	for time, note in notes:
	if self.input.toggled(note.number):
	if arrows[note.number] == False:
	self.score += 50
	note.played = True
	arrows[note.number] = True
	self.opacityGlow[note.number] = 255
	*/
}

void Scene::renderScore() {
	sf::Text textScore;
	textScore.setFont(font);
	textScore.setString(std::to_string(score));

	float length = textScore.getCharacterSize();
	textScore.setPosition(((float)(constants.SCREEN_WIDTH) / 2 - length / 2), 0);
	_screen.draw(textScore);
	//screen.blit(textScore, (constants.SCREEN_WIDTH / 2 - (score).length / 2, 0));

}

void Scene::updateScore() {
	/*
	sf::Time pos = _song.getPlayingOffset(); //pos = self.song.getPosition()
	int track = _song.getChannelCount(); //track = self.song.track
	sf::Time period = _song.getDuration(); //period = self.song.period
	sf::Time delay; //delay = self.song.delay
	sf::Time margin; //margin = period * 0.5

	*/

	/*

	requiredNotes = track.getNotes(pos - delay - self.screenDelay - margin, pos - delay - self.screenDelay + margin)
	update = [True, True, True, True]

	for time, event in requiredNotes:
	update[event.number] = False

	self.input.adapt(update)
	requiredNotes = track.getUnplayedNotes(pos - delay - self.screenDelay - margin, pos - delay - self.screenDelay + margin)
	self.handleRequiredNotes(requiredNotes)
	*/
}

void Scene::run(input in, sf::Clock clock) {
	_input = in;
	//_screen.draw(sceneClock.asMicroseconds);   //self.screenDelay = self.sceneClock.tick()
	//self.screen.fill(self.backgroundColor)
	//updateScore();
	render(clock);
	_screen.display(); //	pygame.display.flip()

}

