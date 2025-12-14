#pragma once

#include "Assets.hpp"

class BgMusic : public Assets {
    private:
        sf::Music music;
        float volume;
        bool isPlaying;

    public:
        BgMusic(const string& path, float volume = 50.0f);
        ~BgMusic();
        bool load() override;
        void render(RenderWindow& window) override;
        void play();
        void pause();
        void stop();
        void setVolume(float volume);
        void setLoop(bool loop);
        bool getIsPlaying() const;
};
