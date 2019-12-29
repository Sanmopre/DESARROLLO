#include "j1GUIscrollBar.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Audio.h"


j1GUIscrollBar::j1GUIscrollBar(SCROLL_TYPE scrollTypeInput) {

	this->type = GUItype::GUI_SCROLLBAR;
	scrollType = scrollTypeInput;
}

j1GUIscrollBar::~j1GUIscrollBar() {

}


bool j1GUIscrollBar::Awake(pugi::xml_node&)
{

	return true;
}


bool j1GUIscrollBar::Start()
{



	scrollButton = App->gui->AddGUIelement(GUItype::GUI_BUTTON, this, Map_Position, Inside_Position, true, true, { 432, 36, 14 , 16 }, nullptr, this->listener, true, false);
	scrollButton->Map_Position.y = Map_Position.y - scrollButton->rect.h / 2 + this->rect.h / 2;
	value = 0;

	 if (this->scrollType == SCROLL_TYPE::SCROLL_MUSIC)
	{

	}

	return true;
}

bool j1GUIscrollBar::PreUpdate()
{

	scrollButton->enabled = enabled;
	above = OnAbove();

	return true;
}

bool j1GUIscrollBar::Update(float dt)
{
	if (interactable) {
		if (above)
		{
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
				OnClick();
		}
	}

	return true;
}

bool j1GUIscrollBar::PostUpdate()
{
	ScrollLimits();
	value = -((float(-scrollButton->Inside_Position.x) / (float(-this->rect.w) + float(scrollButton->rect.w))) * 128);

	if (this->scrollType == SCROLL_TYPE::SCROLL_MUSIC)
	{
		
	}

	if (enabled)
		Draw();

	return true;
}



bool j1GUIscrollBar::CleanUp()
{
	return true;
}


void j1GUIscrollBar::ScrollLimits() {

	if (scrollButton->Inside_Position.x > 0)
	{
		scrollButton->Inside_Position.x = 0;

		scrollButton->Map_Position.x = scrollButton->parent->Map_Position.x - scrollButton->Inside_Position.x;

	}
	else if (scrollButton->Inside_Position.x < (-this->rect.w + scrollButton->rect.w))
	{
		scrollButton->Inside_Position.x = -this->rect.w + scrollButton->rect.w;

		scrollButton->Map_Position.x = scrollButton->parent->Map_Position.x - scrollButton->Inside_Position.x;
		
	}

}