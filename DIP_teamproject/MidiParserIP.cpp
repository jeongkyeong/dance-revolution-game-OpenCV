
#include "MidiParserIP.h"

SongInfo::SongInfo() {

}

SongInfo::~SongInfo() {

}


Event::Event() {

}

Event::~Event() {

}

Tempo::Tempo() {

}

Tempo::~Tempo() {

}

TextEvent::TextEvent() {

}

TextEvent::~TextEvent() {

}

PictureEvent::PictureEvent() {

}

PictureEvent::~PictureEvent() {

}

Track::Track() {

}

Track::~Track() {

}

void Track::addEvent(string time, Event event) {

}
/*
std::vector<Event> Track::getEvents(string startTime, string endTime) {
	
}

std::vector<Event> Track::getUnplayedNotes(string startTime, string endTime) {

}

std::vector<Event> Track::getNotes(string startTime, string endTime) {
	
}

std::vector<Event> Track::getAllEvents(void) {
	
}
*/
void Track::reset() {

}

Song::Song() {};

Song::Song(std::string infoFileName, std::string songTrackName, std::string notefileName) {
	this->info = "TEST"; //TODO
	this->playing = false;
	this->start = 0;
	this->noteFileName = notefileName;
	this->bpm = "TEST"; // TODO
	this->period = 0;
	this->delay = 3.13; // TODO
}

Song::~Song() {

}

MidiReader::MidiReader() {

}

MidiReader::~MidiReader() {

}
