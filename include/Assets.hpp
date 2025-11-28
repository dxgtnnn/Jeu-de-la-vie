#pragma once

#include "Cell.hpp"

class Assets {
    protected:
        string path;
        bool loaded;

    public:
        Assets(const string& path);
        virtual ~Assets() = default;
        virtual bool load() = 0;
        virtual void render(RenderWindow& window) = 0;
        bool isLoaded() const;
        string getPath() const;
};