#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>
#include <SFML/System/Vector3.hpp>

class Audio {
public:
	Audio();
	~Audio();

};

class Music {
public:
	sf::Music music;
	std::string _src;
	Music();
	Music(std::string src);
	~Music();

	void play();
	void stop();
	void rewind();
	void pause();
	void unpause();
	void volume(float vol);
	bool isPlaying();
	sf::Vector3f getPos();
	sf::Time getTimePos();
	//fadeout
};

class Channel {
public:
	Channel();
	~Channel();

};

class Sound {
public:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	std::string _src;

	Sound(std::string src);
	~Sound();

	void play();
	void stop();
	void volume(float vol);
	//fadeout
};

class StreamingSound {
public:
	StreamingSound();
	~StreamingSound();

};
#endif