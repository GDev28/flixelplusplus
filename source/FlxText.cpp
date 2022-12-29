#include "flixel++/FlxText.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxAssets.hpp"

Flx::Text::Text(float x, float y, const std::string& text)
    : Flx::Sprite::Sprite(x,y)
{
    auto ttf = TTF_RenderText_Solid(Flx::Assets::defaultFont, text.c_str(), {255,255,255,255});
    graphic = Flx::Graphic::loadFromSurface(ttf);
    updatePosition();
}

Flx::Text::~Text()
{
}