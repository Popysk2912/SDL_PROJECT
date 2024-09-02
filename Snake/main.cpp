#include <SDL2/SDL.h>
#include <vector>

// Размеры окна и сетки
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int GRID_SIZE = 20;

struct Point {
    int x, y;
};

class Snake {
public:
    Snake() {
        body.push_back({ 5, 5 });
    }

    void move() {
        for (int i = body.size() - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }
        body[0].x += direction.x;
        body[0].y += direction.y;
    }

    void grow(int count)
    {
        for(int i = 0; i < count; i++)
            body.push_back(body.back());
    }

    void setDirection(int x, int y) 
    {
        direction.x = x;
        direction.y = y;
    }

    Point getDirection()
    {
        return direction;
    }

    Point getHead() {
        return body[0];
    }

    void render(SDL_Renderer* renderer) {
        for (int i = 0; i < body.size(); i++) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
            if(i == 0 )
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
            SDL_Rect rect = { body[i].x * GRID_SIZE, body[i].y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
            SDL_RenderFillRect(renderer, &rect);
        }
    }

private:
    std::vector<Point> body;
    Point direction = { 1, 0 };  // По умолчанию змейка движется вправо
};

class Food {
public:
    Food() {
        position = { GRID_SIZE, GRID_SIZE};
    }

    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect rect = { position.x * GRID_SIZE, position.y * GRID_SIZE, GRID_SIZE, GRID_SIZE };
        SDL_RenderFillRect(renderer, &rect);
    }

    Point getPosition() {
        return position;
    }

    void respawn() {
        // Простое перезапуск еды (можно улучшить, чтобы избегать змейки)
        position.x = (rand() % (WINDOW_WIDTH / GRID_SIZE));
        position.y = (rand() % (WINDOW_HEIGHT / GRID_SIZE));
    }

private:
    Point position;
};

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    Snake snake;
    Food food;

    bool running = true;
    SDL_Event event;
    int speed = 100; 

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (snake.getDirection().y == 1) break;
                    snake.setDirection(0, -1);
                    break;
                case SDLK_DOWN:
                    if (snake.getDirection().y == -1) break;
                    snake.setDirection(0, 1);
                    break;
                case SDLK_LEFT:
                    if (snake.getDirection().x == 1) break;
                    snake.setDirection(-1, 0);
                    break;
                case SDLK_RIGHT:
                    if (snake.getDirection().x == -1) break;
                    snake.setDirection(1, 0);
                    break;
                }
            }
        }

        snake.move();

        if (snake.getHead().x == food.getPosition().x && snake.getHead().y == food.getPosition().y) {
            snake.grow(10);
            food.respawn();
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        
        food.render(renderer);
        snake.render(renderer);

        
        SDL_RenderPresent(renderer);

        SDL_Delay(speed); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
