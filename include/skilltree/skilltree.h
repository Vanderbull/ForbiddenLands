#ifndef SKILLTREE_H
#define SKILLTREE_H

void skilltree()
{
}

void skill_list()
{
    SDL_Rect background = {0,0,current.w, current.h - 300 };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &background);
    RenderText("Combat arts", White, 20, 100,50);
    RenderText("Strength", White, 20, 150,40);
    RenderText("Blunt", White, 20, 200,30);
    RenderText("Blade", White, 20, 225,30);
    RenderText("Hand to hand", White, 20, 250,30);

    RenderText("Thief arts", White, 420, 100,50);
    RenderText("Dexterity", White, 420, 150,40);
    RenderText("Climb walls", White, 420, 200,30);
    RenderText("Find traps", White, 420, 225,30);
    RenderText("Hear noise", White, 420, 250,30);
    RenderText("Hide in shadows", White, 420, 275,30);
    RenderText("Move quietly", White, 420, 300,30);
    RenderText("Open locks", White, 420, 325,30);
    RenderText("Pick pocket", White, 420, 350,30);
    RenderText("Read language", White, 420, 375,30);
}

#endif
