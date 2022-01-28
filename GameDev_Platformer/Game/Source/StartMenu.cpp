#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "StartMenu.h"
#include "App.h"
#include "GuiManager.h"
#include "LevelManagement.h"
#include "ModuleFonts.h"
#include "Defs.h"
#include "Log.h"

StartMenu::StartMenu(bool isActive) : Module(isActive)
{
	name.Create("start_menu");
}

// Destructor
StartMenu::~StartMenu()
{}

// Called before render is available
bool StartMenu::Awake()
{
	LOG("Loading Start Scene");
	bool ret = true;


	return ret;
}

// Called before the first frame
bool StartMenu::Start()
{
	img = app->tex->Load("Assets/Spritesx16/StartTitle.png");

	SDL_Rect r;
	r.w = 160;
	r.h = 40;

	r.x = (app->win->GetWidth() / 2);
	r.y = (app->win->GetHeight() / 2);
	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	startButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "abcd",0, { (app->win->GetWidth() / 2)-85 , (app->win->GetHeight() / 2) - 75, 170, 60 }, this);
	startButton->texture = app->tex->Load("Assets/Spritesx16/GUI.png"); //load background button texture
	startButton->normalRec = { 172,1,170,60 }; // set background rect

	settingsButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Settings",0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2), 170, 60 }, this);
	settingsButton->texture = app->tex->Load("Assets/Spritesx16/GUI.png");
	settingsButton->normalRec = { 343,1,170,60 };

	loadButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Load",0, { (app->win->GetWidth() / 2)-85 , (app->win->GetHeight() / 2) + 75, 170, 60 }, this);
	loadButton->texture = app->tex->Load("Assets/Spritesx16/GUI.png");
	loadButton->normalRec = { 514,1,170,60 };
	loadButton->disabledRec = { 514,62,170,60 };

	if (!app->IsASavedGame())
		loadButton->state = GuiControlState::DISABLED;


	exitButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Exit", 0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2) + 150, 170, 60 }, this);
	exitButton->texture = app->tex->Load("Assets/Spritesx16/GUI.png");
	exitButton->normalRec = { 172,62,170,60 };
	exitButton->disabledRec = { 172,62,170,60 };



	sliderTest = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 4, "", 0, { (app->win->GetWidth() / 2) - 425 , (app->win->GetHeight() / 2) + 75, 170, 10 }, this, { (app->win->GetWidth() / 2) - 425 , (app->win->GetHeight() / 2) +70, 10, 15 });


	return true;
}

// Called each loop iteration
bool StartMenu::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool StartMenu::Update(float dt)
{
	rect.x = 0;
	rect.y = 0;
	rect.w = 1280;
	rect.h = 480;
	if (img != nullptr && active)
		app->render->DrawTexture(img, 0, 0, &rect, 1.0f, 0.0f, 1, 1, 1, SDL_FLIP_NONE);
	return true;
}

// Called each loop iteration
bool StartMenu::PostUpdate()
{
	bool ret = true;

	//Draw GUI
	app->guiManager->Draw();

	return ret;
}

// Called before quitting
bool StartMenu::CleanUp()
{
	LOG("Freeing scene main menu ");
	img = nullptr;

	return true;
}

bool StartMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	if (control->id == startButton->id)
	{
		app->levelManagement->gameState = LevelManagement::SCENE1;

	}
	else if (control->id == exitButton->id)
	{
		app->exit = true;
	}


	return true;
}
