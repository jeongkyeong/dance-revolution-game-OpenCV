#include "Audio.h"


Audio::Audio() {}
Audio::~Audio() {}

/*********** MUSIC **************/

Music::Music(std::string src) {
	_src = src;
	music.openFromFile(src);
}
Music::Music() {}

Music::~Music() {}

void Music::play() {
	music.play();
}

void Music::stop() {
	music.stop();
}

void Music::pause() {
	music.pause();
}

void Music::unpause() {
	music.play();
}

bool Music::isPlaying() {
	if (music.getStatus() == sf::Music::Playing)
		return true;
	return false;
}

sf::Vector3f Music::getPos() {
	return music.getPosition();
}

//sf::Time Music::getTimePos() {
//	music.getPlayingOffset();
//}


void Music::volume(float vol) {
	music.setVolume(vol);
}

void Music::rewind() {
	music.stop();
	music.setPlayingOffset(sf::seconds(0));
	music.play();
}

/*********** CHANNEL **************/

Channel::Channel() {}
Channel::~Channel() {}

/*********** SOUND **************/

Sound::Sound(std::string src) {
	_src = src;
	buffer.loadFromFile(src);
	sound.setBuffer(buffer);
}

Sound::~Sound() {}

void Sound::play() {
	sound.play();
}

void Sound::stop() {
	sound.stop();
}

void Sound::volume(float vol) {
	sound.setVolume(vol);
}


/*********** STREAMING SOUND **************/

StreamingSound::StreamingSound() {}
StreamingSound::~StreamingSound() {}