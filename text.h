#ifndef TEXT_H
#define TEXT_H

using namespace std;
SDL_Texture* createText(SDL_Renderer* ren, TTF_Font* font, const string& text, SDL_Color textColor, SDL_Color outlineColor) {

    TTF_SetFontOutline(font, 20);
        SDL_Surface* outlineSur = TTF_RenderText_Blended(font, text.c_str(), outlineColor);

    SDL_Texture* outlineTex = SDL_CreateTextureFromSurface(ren, outlineSur);
    SDL_FreeSurface(outlineSur);

    TTF_SetFontOutline(font, 1);
    SDL_Surface* textSur = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* textTex = SDL_CreateTextureFromSurface(ren, textSur);
    SDL_FreeSurface(textSur);
    SDL_DestroyTexture(outlineTex);
    return textTex;
}

#endif // TEXT_H
