#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"
#include "createcharacterstate.h"
#include "loadmenustate.h"
#include "savemenustate.h"
#include "menustate.h"
#include "gameoverstate.h"

CGameoverState CGameoverState::m_GameoverState;

void CGameoverState::Init()
{
	SDL_Log("CGameoverState Init\n");
}

void CGameoverState::Cleanup()
{
	SDL_Log("CGameoverState Cleanup\n");
}

void CGameoverState::Pause()
{
	SDL_Log("CGameoverState Pause\n");
}

void CGameoverState::Resume()
{
	SDL_Log("CGameoverState Resume\n");
}

void CGameoverState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CGameoverState HandleEvents\n");

	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
            case SDL_MOUSEMOTION:
            {
                SDL_GetMouseState( &mousePosition.x, &mousePosition.y );
            } break;
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						game->ChangeState(CMenuState::Instance());
						break;
				} break;
		}
	}
}

void CGameoverState::Update(CGameEngine* game)
{
    SDL_Log("CGameoverState Update\n");

    game->SActor.PlayerCoordinate = {15,1,0};
    game->SActor.PlayerLastCoordinate = {15,1,0};
    game->SActor.hitpoints_current = 10;
    game->SActor.hitpoints_max = 10;
    game->number_of_enemies = 1;

std::random_device rd;


            int z = 0;
        for(int x = 0; x < 16; x++)
            for(int y = 0; y < 16; y++)
            {
                game->random_events[x][y][z] = rd();//dice();
            }

    //std::fill( &game->random_events[0][0], &game->random_events[16][0], game->myrandom() );

//    std::cout << "Array3D of floats with val = 2.f:.....\n";
//    {
//        //float histogram3D[2][4][28];    // 3d array of floats
//        game->fill_3D_array(game->random_events, 0);// initialize with 2.f
//        game->print_3D_array(game->random_events);
//    }

//   std::cout << "\n\nArray3D of Integers with default val:.....\n";
//   {
//      int histogram3D[2][4][28];   // 3d array of integers
//      game->fill_3D_array(game->random_events);  // no val specified: default val
//      game->print_3D_array(game->random_events);
//   }

//    game->random_events[16][16] =  {
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()},
//    {game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom(),game->myrandom()}
//    };
}

void CGameoverState::Draw(CGameEngine* game)
{
    SDL_Log("CGameoverState Draw\n");

    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);
    game->RenderTextWrapped("The second key belief of Norsemen is that the time of one's death is determined by fate and is chosen by the Norns at the time of one's birth. Therefore, nothing one did could change the moment of one's death. However, what one did up until that moment was strictly one's own doing. Therefore, one ought to make the very best of every moment of life, because the worst that could happen would be death, and the best that could happen would be fame and an enhancement to one's reputation. Since one couldn't effect the time of one's own death, which was predestined anyway, there was nothing to lose and everything to gain by being bold and adventurous.", game->Black, game->current.w / 3 + 200,game->current.h / 3,24,1520);
}
