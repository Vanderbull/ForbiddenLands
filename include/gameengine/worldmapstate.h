#ifndef WORLDMAPSTATE_H
#define WORLDMAPSTATE_H

#include <SDL2/SDL.h>
#include "gamestate.h"
#include "classes/worldmap.h"

class CWorldMapState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CWorldMapState* Instance() {
		return &m_WorldMapState;
	}

    bool IsButtonReleased(const Uint32 uButton)
    {
        return ((SDL_BUTTON(uButton) & m_uCurrentMouseState)==0)&&((SDL_BUTTON(uButton) & m_uPreviousMouseState)!=0);
    }

protected:
	CWorldMapState() { }

private:
	static CWorldMapState m_WorldMapState;

	WorldMap World;

	//int map[20][25];

    /// Information about the state of the mouse
    int m_iCurrentCoordX;
    int m_iCurrentCoordY;
    Uint32 m_uCurrentMouseState;

    int m_iPreviousCoordX;
    int m_iPreviousCoordY;
    Uint32 m_uPreviousMouseState;

    ///information about the state of thw wheel
    Sint32 m_iWheelX;
    Sint32 m_iWheelY;

    // Sweden
    SDL_Rect Kustenstad{0,0,128,128};
    SDL_Rect Vallentuna{256,0,128,128};
    SDL_Rect Mora{512,0,128,128};
    //Danmark
    SDL_Rect Marlmo{0,256,128,128};
    SDL_Rect Saeby{256,256,128,128};
    SDL_Rect Odense{512,256,128,128};
    SDL_Rect Zealfort{768,256,128,128};
    //Norway
    SDL_Rect Trollheim{0,512,128,128};
    SDL_Rect Trondeland{256,512,128,128};
    SDL_Rect Aerendal{512,512,128,128};
    //Finland
    SDL_Rect Kiiri{0,768,128,128};
    SDL_Rect Kamilarvi{256,768,128,128};
    SDL_Rect Muoni{512,768,128,128};

    SDL_Rect water_x_rect = { 0,0, 1920, 1080 };
    SDL_Rect water_x_rect2 = { -1919,0, 1920, 1080 };

    SDL_Rect water_y_rect = { 0,0, 1920, 1080 };
    SDL_Rect water_y_rect2 = { 0,-1079, 1920, 1080 };

    SDL_Rect Point_Of_Interest[10];

    float Noise_Map[10][33];

    int SCREEN_WIDTH = 640;
    int SCREEN_HEIGHT = 480;
    int CELL_SIZE = 20;
    int GRID_WIDTH= SCREEN_WIDTH / CELL_SIZE;
    int GRID_HEIGHT = SCREEN_HEIGHT / CELL_SIZE;

    enum CellType
    {
        WATER,
        LAND,
        POI
    };

    CellType grid[34][10] = {
        {WATER,WATER,WATER,WATER,WATER,WATER,LAND,WATER,WATER,WATER},
        {WATER,WATER,WATER,WATER,LAND,LAND,LAND,LAND,LAND,WATER},
        {WATER,WATER,WATER,WATER,LAND,LAND,LAND,LAND,LAND,WATER},
        {WATER,WATER,WATER,WATER,LAND,LAND,LAND,LAND,LAND,WATER},
        {WATER,WATER,WATER,WATER,LAND,LAND,LAND,LAND,LAND,WATER},
        {WATER,WATER,WATER,LAND,LAND,LAND,LAND,LAND,LAND,WATER},
        {WATER,WATER,WATER,LAND,LAND,LAND,LAND,LAND,LAND,LAND},
        {WATER,WATER,LAND,LAND,LAND,LAND,LAND,LAND,LAND,LAND},
        {WATER,WATER,LAND,LAND,LAND,LAND,LAND,LAND,LAND,LAND},
        {WATER,WATER,LAND,LAND,LAND,LAND,LAND,LAND,LAND,WATER},
        {WATER,WATER,LAND,LAND,LAND,LAND,LAND,LAND,WATER,WATER},
        {WATER,WATER,LAND,LAND,LAND,LAND,LAND,LAND,LAND,WATER},
        {WATER,WATER,LAND,LAND,LAND,LAND,LAND,LAND,LAND,WATER},
        {WATER,LAND,LAND,LAND,LAND,LAND,LAND,LAND,WATER,WATER},
        {WATER,LAND,LAND,LAND,LAND,LAND,LAND,LAND,WATER,WATER},
        {WATER,LAND,LAND,LAND,LAND,LAND,LAND,WATER,WATER,WATER},
        {WATER,LAND,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER},
        {WATER,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER,WATER},
        {WATER,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER,WATER},
        {WATER,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER,WATER},
        {WATER,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER,WATER},
        {WATER,LAND,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER},
        {LAND,LAND,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER},
        {LAND,LAND,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER},
        {LAND,LAND,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER},
        {LAND,LAND,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER},
        {LAND,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER,WATER},
        {LAND,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER,WATER},
        {LAND,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER,WATER},
        {LAND,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER,WATER},
        {WATER,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER,WATER},
        {WATER,LAND,LAND,LAND,LAND,WATER,WATER,WATER,WATER,WATER},
        {WATER,LAND,LAND,LAND,WATER,WATER,WATER,WATER,WATER,WATER},
        {WATER,LAND,LAND,WATER,WATER,WATER,WATER,WATER,WATER,WATER}
    };

int debug_array[33][10] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
    {20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
    {30, 31, 32, 33, 34, 35, 36, 37, 38, 39},
    {40, 41, 42, 43, 44, 45, 46, 47, 48, 49},
    {50, 51, 52, 53, 54, 55, 56, 57, 58, 59},
    {60, 61, 62, 63, 64, 65, 66, 67, 68, 69},
    {70, 71, 72, 73, 74, 75, 76, 77, 78, 79},
    {80, 81, 82, 83, 84, 85, 86, 87, 88, 89},
    {90, 91, 92, 93, 94, 95, 96, 97, 98, 99},
    {100, 101, 102, 103, 104, 105, 106, 107, 108, 109},
    {110, 111, 112, 113, 114, 115, 116, 117, 118, 119},
    {120, 121, 122, 123, 124, 125, 126, 127, 128, 129},
    {130, 131, 132, 133, 134, 135, 136, 137, 138, 139},
    {140, 141, 142, 143, 144, 145, 146, 147, 148, 149},
    {150, 151, 152, 153, 154, 155, 156, 157, 158, 159},
    {160, 161, 162, 163, 164, 165, 166, 167, 168, 169},
    {170, 171, 172, 173, 174, 175, 176, 177, 178, 179},
    {180, 181, 182, 183, 184, 185, 186, 187, 188, 189},
    {190, 191, 192, 193, 194, 195, 196, 197, 198, 199},
    {200, 201, 202, 203, 204, 205, 206, 207, 108, 209},
    {210, 211, 212, 213, 214, 215, 216, 217, 218, 219},
    {220, 221, 222, 223, 224, 225, 226, 227, 228, 229},
    {230, 231, 232, 233, 234, 235, 236, 237 ,238, 239},
    {240, 241, 242, 243, 244, 245, 246, 247, 248, 249},
    {250, 251, 252, 253, 254, 255, 256, 257, 258, 259},
    {260, 261, 262, 263, 264, 265, 266, 267, 268, 269},
    {270, 271, 272, 273, 274, 275, 276, 277, 278, 279},
    {280, 281, 282, 283, 284, 285, 286, 287, 288, 289},
    {290, 291, 292, 293, 294, 295, 296, 297, 298, 299},
    {300, 301, 302, 303, 304, 305, 306, 307, 308, 309},
    {310, 311, 312, 313, 314, 315, 316, 317, 318, 319},
    {320, 321, 322, 323, 324, 325, 326, 327, 328, 329}
    };

int debug_array_2[10][34] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34},
    {34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67},
    {68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101},
    {102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135},
    {136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169},
    {170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203},
    {204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237},
    {237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270},
    {271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303},
    {304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335},
    };

};

#endif
