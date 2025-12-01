#include "Music.hpp"

BgMusic::BgMusic(const string& path, float volume) : Assets(path), volume(volume), isPlaying(false) {}

BgMusic::~BgMusic()
{
    if (isPlaying)
        music.stop();
}

bool BgMusic::load()
{
    if (!music.openFromFile(path)) {
        cerr << "Erreur : impossible de charger la musique " << path << endl;
        loaded = false;
        return false;
    }
    music.setVolume(volume);
    loaded = true;
    return true;
}

void BgMusic::render(RenderWindow& window)
{
    (void)window;
}

void BgMusic::play()
{
    if (!loaded)
        return;
    music.play();
    isPlaying = true;
}

void BgMusic::pause()
{
    if (!loaded)
        return;
    music.pause();
    isPlaying = false;
}

void BgMusic::stop()
{
    if (!loaded)
        return;
    music.stop();
    isPlaying = false;
}

void BgMusic::setVolume(float newVolume)
{
    volume = newVolume;
    if (volume < 0)
        volume = 0;
    if (volume > 100)
        volume = 100;
    music.setVolume(volume);
}

void BgMusic::setLoop(bool loop)
{
    if (!loaded)
        return;
    music.setLoop(loop);
}

bool BgMusic::getIsPlaying() const
{
    return isPlaying;
}