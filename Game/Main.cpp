#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"

#include <fmod.hpp>

#include "SDL3/SDL.h"
#include <iostream>
#include <vector>
#include <map>
#include <memory>

using namespace std;
using namespace nu;

class Object {
public:
    Object() { cout << "constructor\n"; }
    ~Object() { cout << "destructor\n"; }

    Object(const Object& object) { cout << "copy\n"; }
    Object& operator= (const Object& object) { cout << "copy assign\n"; return *this; }
};


int main() {
    cout << "=============Unique Pointer Test=============\n";
    {
		unique_ptr<Object>objectA = make_unique<Object>();
		cout << objectA.get() << endl;
        unique_ptr<Object>objectB;

		objectB = move(objectA);
        cout << objectB.get() << endl;
    }

    cout << "=============Shared Pointer Test=============\n";
    shared_ptr<Object> objectC;
    {
		shared_ptr<Object> objectA = make_shared<Object>();
		cout << objectA.get() << endl;
		cout << objectA.use_count() << endl;

        auto objectB = objectA;

		cout << objectB.get() << endl;
		cout << objectB.use_count() << endl;

		cout << objectC.get() << endl;
		cout << objectC.use_count() << endl;
    }
	cout << objectC.use_count() << endl;

    //return 0;


    SetWorkingDirectory("Assets");

    //Intialization
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	SetWorkingDirectory("Textures");
    //texture->Load("potato.jpg", Engine::Get().GetRenderer());
        

    Scene scene;
    
    SetWorkingDirectory("Audio");
    
    Engine::Get().GetAudio().AddSound("test", "test.wav");
    Engine::Get().GetAudio().AddSound("thrust", "thrust.wav");
    Engine::Get().GetAudio().AddSound("mario", "mario.mp3");
    Engine::Get().GetAudio().AddSound("hee-hee", "hee-hee.mp3");
    Engine::Get().GetAudio().AddSound("bass", "bass.wav");
    Engine::Get().GetAudio().AddSound("background", "background_music.ogg");

			
    Engine::Get().GetAudio().PlaySound("background");

    SetWorkingDirectory("Fonts");
    

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

        for (int i = 0; i< (int)mouseLinePoints.size() - 1; i++) {
            Engine::Get().GetRenderer().SetColor(1.0f, 1.0f, 1.0f);
            Engine::Get().GetRenderer().DrawLine(mouseLinePoints[i].x, mouseLinePoints[i].y, mouseLinePoints[i+1].x, mouseLinePoints[i+1].y);
        }
       

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());
        // TODO:: get engine renderer.DrawTexture(...get() texture pointer..., 30, 30);
        Engine::Get().GetRenderer().DrawTexture(*Resources().Get<Texture>("potato.jpg", Engine::Get().GetRenderer()), 30, 30, 45.0f);

		game.Draw(Engine::Get().GetRenderer());
        
        Engine::Get().GetRenderer().Present();
    }
    game.Shutdown();
    Engine::Get().Shutdown();

    return 0;
}