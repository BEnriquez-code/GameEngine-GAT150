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
#include <random>

using namespace std;
using namespace nu;

class Object {
public:
    Object() { cout << "constructor\n"; }
    ~Object() { cout << "destructor\n"; }

    Object(const Object& object) { cout << "copy\n"; }
    Object& operator= (const Object& object) { cout << "copy assign\n"; return *this; }
};

uint32_t seed = 1234;

uint32_t RNG() {
	seed = (seed * 1103515245) + 12345;
    return seed;
}

int main() {
    /*
    //rand()
    for (size_t i = 0; i < 10; i++) cout << RNG() << " ";
    cout << endl;
    
	seed = 1234;

    for (size_t i = 0; i < 10; i++)cout << RNG() << " ";
    cout << endl;

    //srand((unsigned int)time(nullptr));
    SeedRandom((unsigned int)time(nullptr));
    for (size_t i = 0; i < 10; i++)cout << rand() << " ";
    cout << endl;

    //random<>
    random_device randomDevice;
    cout << randomDevice.min() << endl;
    cout << randomDevice.max() << endl;
    cout << randomDevice.entropy() << endl;

	std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> dist(0,20);

	for (size_t i = 0; i < 10; i++)cout << dist(generator) << " ";
	cout << endl;

	std::uniform_real_distribution<float> distReal(-10.0f, 20.0f);
    for (size_t i = 0; i < 10; i++)cout << distReal(generator) << " ";

    return 0;
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
    */

    SetWorkingDirectory("Assets");

    //Intialization
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	SetWorkingDirectory("Textures");
    
        

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
        //Engine::Get().GetRenderer().DrawTexture(*Resources().Get<Texture>("potato.jpg", Engine::Get().GetRenderer()), 30, 30, 45.0f);

		game.Draw(Engine::Get().GetRenderer());
        
        Engine::Get().GetRenderer().Present();
    }
    game.Shutdown();
    Engine::Get().Shutdown();

    return 0;
}