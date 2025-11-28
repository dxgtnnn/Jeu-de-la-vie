#pragma once

#include "Assets.hpp"

class Background : public Assets {
    private:
        Texture texture;
        Sprite sprite;
        float opacity;
        Vector2f scale;

    public:
        Background(const string& path, float opacity = 255.0f);
        ~Background() = default;
        bool load() override;
        void render(RenderWindow& window) override;
        void setOpacity(float opacity);
        void setScale(float scaleX, float scaleY);
        void fitToWindow(int windowWidth, int windowHeight);
};