
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <SFML/Window.hpp>
#include "Audio.h"
#include "Constants.h"
//#include "constants.h"
//#include "Input.h"
//#include "MidiParserIP.h"
#include "Scene.h"
//#include "Resource.h"
//#include "MidiFile.h"
//#include "Options.h"
//#include <iostream>

using namespace cv;
using namespace std;

Constants constants;

void run() {
	input in = input(false, constants);

	sf::RenderWindow window(sf::VideoMode(constants.SCREEN_WIDTH, constants.SCREEN_HEIGHT), "DanceCV");

	Scene *sc = new Scene(2, window, in, 2);

	//int Resource, sf::Music Song, sf::RenderWindow Screen, int Input, int BeatsPerBoard
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//window.clear(sf::Color::Black);
		in.run();
		sc->run(in, clock);
		//window.display();

	}
}

int main()
{
	run();
	return 0;
}