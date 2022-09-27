#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <stdbool.h>

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600

int main() {
    Uint32 sdl_flags = SDL_INIT_EVERYTHING;
    if (SDL_Init(sdl_flags) != 0) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    Uint32 img_flag = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP;
    if ((IMG_Init(img_flag) & img_flag) != img_flag) {
        fprintf(stderr, "Initializing IMG error: %s\n", IMG_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window       = NULL;
    SDL_Surface *screen      = NULL;
    SDL_Renderer *g_renderer = NULL;
    SDL_Texture *texture     = NULL;
    Mix_Music *music         = NULL;

    window = SDL_CreateWindow(
        "Music",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL
    );
    if (window == NULL) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Delay(100);

    screen = SDL_GetWindowSurface(window);
    g_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    screen = IMG_Load("image/flag-ukrainyi.png");
    if (screen == NULL) {
        fprintf(stderr, "Load image error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    texture = SDL_CreateTextureFromSurface(g_renderer, screen);

    SDL_FreeSurface(screen);

    SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);

    SDL_RenderClear(g_renderer);
    SDL_RenderCopy(g_renderer, texture, NULL, NULL);
    SDL_RenderPresent(g_renderer);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    music = Mix_LoadMUS("music/gimn-ukrainyi.wav");
    if (music == NULL) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    Mix_PlayMusic(music, 1);

    bool is_cancel = false;
    while (!is_cancel) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type){
                case SDL_QUIT:
                    is_cancel = true;
                    break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyTexture(texture);
    SDL_Quit();

    return EXIT_SUCCESS;
}
