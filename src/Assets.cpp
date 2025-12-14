#include "Assets.hpp"

Assets::Assets(const string &path) : path(path), loaded(false) {}

bool Assets::isLoaded() const
{
    return loaded;
}

string Assets::getPath() const
{
    return path;
}
