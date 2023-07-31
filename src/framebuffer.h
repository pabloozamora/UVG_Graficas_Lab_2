#pragma once
#include "color.h"
#include "vertex2.h"
#include <vector>
#include <SDL.h>

void clear(const Color&);

void point(const Vertex2, const Color);

void renderBuffer(SDL_Renderer*);

void createFrameBuffer();

void renderGame(SDL_Renderer*);

void updateGame(SDL_Renderer*);