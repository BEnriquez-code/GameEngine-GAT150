#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"
#include "Json.h"
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

    //read/show the data from the json file
    rapidjson::Document document;
    json::Load("Data/data.json", document);

    std::string name = "Izak";
    int age = 19;
	float speed = 10.0f;
    bool isAlive = true;
	Vector2 position{ 0.0f, 0.0f };
	Vector3 color{ 1.0f, 1.0f, 1.0f };


    // load the json data from a file
    std::string buffer;
    if (ReadTextFile("Data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        if (json::Load("Data/data.json", document))
        {
            // read the age data (int) from the json
            int age;
            json::Read(document, "age", age);
            // show the age data
            std::cout << age << std::endl;
        }
    }

    // read the json data
    nu::json::Read(document, "name", name);
    nu::json::Read(document, "age", age);
    nu::json::Read(document, "speed", speed);
    nu::json::Read(document, "isAlive", isAlive);
    nu::json::Read(document, "position", position);
    nu::json::Read(document, "color", color);


    // show the data
    std::cout << name << " " << age << " " << speed << " " << isAlive << std::endl;
    std::cout << position.x << " " << position.y << std::endl;
    std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;

    //Intialization
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	auto particleTexture = Resources().Get<Texture>("Textures/particle.png", Engine::Get().GetRenderer());
	Engine::Get().GetPS().SetTexture(particleTexture);
        

    Scene scene;
    
    
    Engine::Get().GetAudio().AddSound("test", "Audio/test.wav");
    Engine::Get().GetAudio().AddSound("thrust", "Audio/thrust.wav");
    Engine::Get().GetAudio().AddSound("mario", "Audio/mario.mp3");
    Engine::Get().GetAudio().AddSound("hee-hee", "Audio/hee-hee.mp3");
    Engine::Get().GetAudio().AddSound("bass", "Audio/bass.wav");
    Engine::Get().GetAudio().AddSound("background", "Audio/background_music.ogg");
			
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
       
        game.Update(Engine::Get().GetTime().GetDeltaTime(), mouseLinePoints);
        scene.Update(Engine::Get().GetTime().GetDeltaTime());

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