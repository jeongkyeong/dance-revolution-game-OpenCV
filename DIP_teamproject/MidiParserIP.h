#ifndef MIDIPARSERIP_H
#define MIDIPARSERIP_H

#include <iostream>
#include <vector>

using namespace std;

class SongInfo {
public:
	string songName;
	string fileName;
	string info;
	string name;
	string artist;
	string delay;

	/**void setSongName(string songName);
	void setFileName(string songName);
	void setInfo(string songName);
	void setName(string songName);
	void setArtist(string songName);
	void setDelay(string songName);

	string getSongName(void);
	string getFileName(void);
	string getInfo(void);
	string getName(void);
	string getArtist(void);
	string getDelay(void);**/

	SongInfo();
	~SongInfo();
};

class Event {
public:
	string number;
	bool played;
	string special;
	string tappable;
	Event();
	~Event();
};

class Tempo {
public:
	string bmp;
	Tempo();
	~Tempo();
};

class TextEvent {
public:
	string text;
	TextEvent();
	~TextEvent();
};

class PictureEvent {
public:
	string fileName;
	PictureEvent();
	~PictureEvent();
};

class Track {
public:
	std::vector<Event> events;
	std::vector<Event> allEvents;

	void addEvent(string time, Event event);
	std::vector<Event> getEvents(string startTime, string endTime);
	std::vector<Event> getUnplayedNotes(string startTime, string endTime);
	std::vector<Event> getNotes(string startTime, string endTime);
	std::vector<Event> getAllEvents(void);
	void reset();

	Track();
	~Track();
};

class Song {
public:
	string info;
	bool playing;
	double start;
	string noteFileName;
	string bpm;
	int period;
	double delay;
	Track track;

	string Music; // todo
	Song();
	Song(std::string infoFileName, std::string songTrackName, std::string notefileName);
	~Song();

	void setBpm(string bpm);
	void play(double start);
	void pause();
	void unpause();
	void setBackgroundVolume(double volume);
	void stop();
	void fadeout(double time);
	double getPostition();
	bool isPlaying();
	string getBeat();
	void update(string ticks); //todo
	Track getTrack();
};

class MidiReader {
public:
	Song song;
	std::vector<int> heldNotes;
	std::vector<int> velocity;
	int ticksPerBeat;
	std::vector<int> tempoMakers;


	MidiReader();
	~MidiReader();
};

#endif