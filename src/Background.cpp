#include "Background.hpp"

Background::Background(const string& path, float opacity) : Assets(path), opacity(opacity), scale(1.0f, 1.0f) {}

bool Background::load()
{
    if (!texture.loadFromFile(path)) {
        cerr << "Erreur : impossible de charger l'image " << path << endl;
        loaded = false;
        return false;
    }
    sprite.setTexture(texture);
    sprite.setColor(Color(255, 255, 255, static_cast<Uint8>(opacity)));
    loaded = true;
    return true;
}

void Background::render(RenderWindow& window)
{
    if (!loaded)
        return;
    window.draw(sprite);
}

void Background::setOpacity(float newOpacity)
{
    opacity = newOpacity;
    if (opacity < 0)
        opacity = 0;
    if (opacity > 255)
        opacity = 255;
    sprite.setColor(Color(255, 255, 255, static_cast<Uint8>(opacity)));
}

void Background::setScale(float scaleX, float scaleY)
{
    scale.x = scaleX;
    scale.y = scaleY;
    sprite.setScale(scale);
}

void Background::fitToWindow(int windowWidth, int windowHeight)
{
    Vector2u textureSize;
    float scaleX;
    float scaleY;
    if (!loaded)
        return;
    textureSize = texture.getSize();
    scaleX = static_cast<float>(windowWidth) / textureSize.x;
    scaleY = static_cast<float>(windowHeight) / textureSize.y;
    setScale(scaleX, scaleY);
}