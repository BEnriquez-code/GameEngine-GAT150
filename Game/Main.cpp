#include "Engine.h"
#include "SpaceGame/Player.h"
#include "SpaceGame/Enemy.h"
#include "SpaceGame/Assets.h"
#include "SpaceGame/Bullet.h"
#include "SpaceGame/SpaceGame.h"
#include "SpriteGame/SpriteGame.h"
#include "Serialization/Json.h"
#include <fmod.hpp>

#include "SDL3/SDL.h"   
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <random>
#include <fstream>

using namespace std;
using namespace nu;


int main() {
    SetWorkingDirectory("Assets");
   
    //Intialization
    Engine::Get().Initialize();

    SpriteGame game;
    game.Initialize();

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	auto particleTexture = Resources().Get<Texture>("Textures/particle.png", Engine::Get().GetRenderer());
	Engine::Get().GetPS().SetTexture(particleTexture);
        

    Scene scene;
			
    Engine::Get().GetAudio().PlaySound("background");  

    vector<Vector2> mouseLinePoints;   
   
	//MAIN LOOP
    bool quit = false;
    while (!quit) {
		//Update
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                    quit = true;
			}
        }


        Engine::Get().Update();
       
        //game.Update(Engine::Get().GetTime().GetDeltaTime(), mouseLinePoints);
        game.Update(Engine::Get().GetTime().GetDeltaTime());

        if (Engine::Get().GetInput().GetButtonDown(Input::MouseButton::Left)) {
			Vector2 v = Engine::Get().GetInput().GetMousePosition();
            if (mouseLinePoints.empty()) {
                mouseLinePoints.push_back(v);
            }
            else{
                float distance = (v - mouseLinePoints.back()).Length();

                if (distance > 10.0f) {
                    mouseLinePoints.push_back(v);
                }
            }
            
		}

        if (Engine::Get().GetInput().GetButtonDown(Input::MouseButton::Right)) {
            if (!mouseLinePoints.empty())mouseLinePoints.pop_back();
		} 

        //Render
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

            
        game.Draw(Engine::Get().GetRenderer());

        for (int i = 0; i < (int)mouseLinePoints.size() - 1; i++) {
            Engine::Get().GetRenderer().SetColor(1.0f, 1.0f, 1.0f);
            Engine::Get().GetRenderer().DrawLine(mouseLinePoints[i].x, mouseLinePoints[i].y, mouseLinePoints[i + 1].x, mouseLinePoints[i + 1].y);
        }
               
        Engine::Get().GetRenderer().Present();
    }
    game.Shutdown();
    Engine::Get().Shutdown();

    return 0;
}