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



	scrollButton = App->gui->AddGUIelement(GUItype::GUI_BUTTON, this, globalPosition, localPosition, true, true, { 432, 36, 14 , 16 }, nullptr, this->listener, true, false);
	scrollButton->globalPosition.y = globalPosition.y - scrollButton->rect.h / 2 + this->rect.h / 2;
	value = 0;

	if (this->scrollType == SCROLL_TYPE::SCROLL_FX)
	{
		
	}
	else if (this->scrollType == SCROLL_TYPE::SCROLL_MUSIC)
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
	value = -((float(-scrollButton->localPosition.x) / (float(-this->rect.w) + float(scrollButton->rect.w))) * 128);

	if (this->scrollType == SCROLL_TYPE::SCROLL_FX)
	{
		
	}
	else if (this->scrollType == SCROLL_TYPE::SCROLL_MUSIC)
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

	if (scrollButton->localPosition.x > 0)
	{
		scrollButton->localPosition.x = 0;

		scrollButton->globalPosition.x = scrollButton->parent->globalPosition.x - scrollButton->localPosition.x;
		//scrollButton->globalPosition.y = scrollButton->parent->globalPosition.y - scrollButton->localPosition.y;
	}
	else if (scrollButton->localPosition.x < (-this->rect.w + scrollButton->rect.w))
	{
		scrollButton->localPosition.x = -this->rect.w + scrollButton->rect.w;

		scrollButton->globalPosition.x = scrollButton->parent->globalPosition.x - scrollButton->localPosition.x;
		//scrollButton->globalPosition.y = scrollButton->parent->globalPosition.y - scrollButton->localPosition.y;
	}

}