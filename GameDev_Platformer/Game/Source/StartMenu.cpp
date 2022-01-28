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


	settingsPanel = new GuiPanel(false);
	settingsPanel->bounds = {510,0,266 ,382};
	settingsPanel->position = { (app->win->GetWidth() *40 /100) ,(app->win->GetWidth() *5 / 100) };
	volumeSlider = (GuiSlider*) settingsPanel->CreateGuiControl(GuiControlType::SLIDER, 5, "Volume", 0, { (settingsPanel->position.x +147), (settingsPanel->position.y +99), 83, 8 }, this, { (settingsPanel->position.x + 147), (settingsPanel->position.y +99), 6, 10 });
	fxSlider = (GuiSlider*)settingsPanel->CreateGuiControl(GuiControlType::SLIDER, 6, "Fx", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 167), 83, 8 }, this, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 167), 6, 10 });
	
	vsyncCheckbox = (GuiToggle*)settingsPanel->CreateGuiControl(GuiControlType::CHECKBOX, 7, "vsync", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 231), 22, 22 }, this);
	
	fullScreenCheckbox = (GuiToggle*)settingsPanel->CreateGuiControl(GuiControlType::CHECKBOX, 8, "fullScreen", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 295), 22, 22 }, this);

	fullScreenCheckbox = (GuiToggle*)settingsPanel->CreateGuiControl(GuiControlType::CHECKBOX, 9, "fullScreen", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 295), 22, 22 }, this);

	closePanelBttn = (GuiButton*)settingsPanel->CreateGuiControl(GuiControlType::BUTTON, 10, "fullScreen", 0, { (settingsPanel->position.x + 23), (settingsPanel->position.y + 20), 22, 22 }, this);
	closePanelBttn->normalRec = { 66,240,22,22 };
	closePanelBttn->selectedRec = { 66,240,22,22 };
	closePanelBttn->disabledRec = { 66,240,22,22 };
	closePanelBttn->focusedRec = { 66,240,22,22 };
	closePanelBttn->pressedRec = { 66,240,22,22 };

	return true;
}

// Called each loop iteration
bool StartMenu::PreUpdate()
{
	settingsPanel->PreUpdate();
	return true;
}

// Called each loop iteration
bool StartMenu::Update(float dt)
{
	settingsPanel->Update(dt);
	return true;
}

// Called each loop iteration
bool StartMenu::PostUpdate()
{
	bool ret = true;
	rect.x = 0;
	rect.y = 0;
	rect.w = 1280;
	rect.h = 480;
	if (img != nullptr && active)
		app->render->DrawTexture(img, 0, 0, &rect, 1.0f, 0.0f, 1, 1, 1, SDL_FLIP_NONE);
	//Draw GUI
	app->guiManager->Draw();
	settingsPanel->Draw();

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
	else if (control->id == settingsButton->id)
	{
		settingsPanel->Active = true;
	}
	else if (control->id == closePanelBttn->id)
	{
		settingsPanel->Active = false;
	}


	return true;
}
