#include <ctime>
#include <iostream>
#include <string>
#include <list>
#include <array>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>
#include <string>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_net.h>

using namespace std;
#define MAX_PACKET 0xFF
#define MAX_SOCKETS 0x10

typedef struct {
	int in_use;
	int questing;
	uint8_t amt_wood;
	uint32_t timer_wood;
} Client;

int next_ind = 0;
TCPsocket server_socket;
Client clients[MAX_SOCKETS];
SDLNet_SocketSet socket_set;
TCPsocket sockets[MAX_SOCKETS];
IPaddress ip;

void CloseSocket(int index) {
	if(sockets[index] == NULL) {
		fprintf(stderr, "ER: Attempted to delete a NULL socket.\n");
		return;
	}

	if(SDLNet_TCP_DelSocket(socket_set, sockets[index]) == -1) {
		fprintf(stderr, "ER: SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
		exit(-1);
	}

	memset(&clients[index], 0x00, sizeof(Client));
	SDLNet_TCP_Close(sockets[index]);
	sockets[index] = NULL;
}
int AcceptSocket(int index) {
	if(sockets[index]) {
		fprintf(stderr, "ER: Overriding socket at index %d.\n", index);
		CloseSocket(index);
	}

	sockets[index] = SDLNet_TCP_Accept(server_socket);
	if(sockets[index] == NULL) return 0;

	clients[index].in_use = 1;
	if(SDLNet_TCP_AddSocket(socket_set, sockets[index]) == -1) {
		fprintf(stderr, "ER: SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
		exit(-1);
	}

	return 1;
}

int main()
{
    cout << "Hello world!" << endl;
    // NETWORK CODE
    if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_EVENTS) != 0) {
        fprintf(stderr, "ER: SDL_Init: %s\n", SDL_GetError());
        exit(-1);
    }

    if(SDLNet_Init() == -1) {
        fprintf(stderr, "ER: SDLNet_Init: %s\n", SDLNet_GetError());
        exit(-1);
    }

    if(SDLNet_ResolveHost(&ip, NULL, 8099) == -1) {
        fprintf(stderr, "ER: SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(-1);
    }

    server_socket = SDLNet_TCP_Open(&ip);
    if(server_socket == NULL) {
        fprintf(stderr, "ER: SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        exit(-1);
    }

    socket_set = SDLNet_AllocSocketSet(MAX_SOCKETS+1);
    if(socket_set == NULL) {
        fprintf(stderr, "ER: SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
        exit(-1);
    }

    if(SDLNet_TCP_AddSocket(socket_set, server_socket) == -1) {
        fprintf(stderr, "ER: SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
        exit(-1);
    }

    int running = 1;
    while(running) {
        int num_rdy = SDLNet_CheckSockets(socket_set, 1000);

        if(num_rdy <= 0)
        {
            int ind;
            for(ind=0; ind<MAX_SOCKETS; ++ind)
            {
                if(!clients[ind].in_use) continue;
                clients[ind].amt_wood += 4;
            }
            // NOTE: none of the sockets are ready
        } else {
            // NOTE: some number of the sockets are ready
            if(SDLNet_SocketReady(server_socket)) {
                int got_socket = AcceptSocket(next_ind);
                if(!got_socket) {
                    num_rdy--;
                    continue;
                }

                // NOTE: get a new index
                int chk_count;
                for(chk_count=0; chk_count<MAX_SOCKETS; ++chk_count) {
                    if(sockets[(next_ind+chk_count)%MAX_SOCKETS] == NULL) break;
                }

                next_ind = (next_ind+chk_count)%MAX_SOCKETS;
                printf("DB: new connection (next_ind = %d)\n", next_ind);

                num_rdy--;
            }
int ind;
for(ind=0; (ind<MAX_SOCKETS) && num_rdy; ++ind) {
	if(sockets[ind] == NULL) continue;
	if(!SDLNet_SocketReady(sockets[ind])) continue;

	uint8_t* data;
	uint16_t flag;
	uint16_t length;

	data = RecvData(ind, &length, &flag);
	if(data == NULL) {
		num_rdy--;
		continue;
	}

	switch(flag) {
		case FLAG_WOOD_UPDATE: {
			uint16_t offset = 0;
			uint8_t send_data[MAX_PACKET];

			memcpy(send_data+offset, &clients[ind].amt_wood, sizeof(uint8_t));
			offset += sizeof(uint8_t);

			SendData(ind, send_data, offset, FLAG_WOOD_UPDATE);
		} break;

		case FLAG_QUIT: {
			running = 0;
			printf("DB: shutdown by client id: %d\n", ind);
		} break;
	}

	free(data);
	num_rdy--;
}
        }
    }

    // NET CODE QUIT CODE
    if(SDLNet_TCP_DelSocket(socket_set, server_socket) == -1) {
        fprintf(stderr, "ER: SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
        exit(-1);
    } SDLNet_TCP_Close(server_socket);

    int i;
    for(i=0; i<MAX_SOCKETS; ++i) {
        if(sockets[i] == NULL) continue;
        CloseSocket(i);
    }

    SDLNet_FreeSocketSet(socket_set);
    // NET CODE END
    SDL_Quit();

    return 0;
}
