#include "Classes/Public/GUI/Canvas.hpp"
#include "Classes/Public/GUI/Widget.h"
#include "Classes/Public/GUI/Button.h"

Canvas::Canvas()
{
	LOG("Canvas Created")
}

Canvas::~Canvas()
{
	auto It = Widgets.begin();
	for (; It != Widgets.end(); ++It)
	{
		LOG("Deleting Widget")
		delete It->second;
	}
}

bool Canvas::SetWidgetPosition(String Widget, sf::Vector2f NewPos)
{
	return true;
}

bool Canvas::SetWidgetVisibility(String Widget, EVisibility NewVisibility)
{
	auto It = Widgets.find(Widget);
	if (It != Widgets.end())
	{
		It->second->SetVisibility(NewVisibility);
		return true;
	}
	
	return false;
}

Widget* Canvas::GetWidget(const String& Name) const
{
	auto It = Widgets.begin();
	for (; It != Widgets.end(); ++It)
	{
		if (It->first == Name)
		{
			return It->second;
		}
	}
	
	FMT_LOG("Canvas does not contain %s", Name.c_str())
	return nullptr;
}

void Canvas::DrawCanvas(sf::RenderTarget* Target)
{
	auto It = Widgets.begin();
	for (; It != Widgets.end(); ++It)
	{
		if (It->second && It->second->GetVisibility() != EVisibility::Hidden)
		{
			It->second->Draw(Target);
		}
	}
}

/*
 * @TODO(Chrisr): Find a better way of doing this
 */
void Canvas::RefreshWidgets(const sf::Vector2f& MousePos)
{
	auto It = Widgets.begin();
	for (; It != Widgets.end(); ++It)
	{
		if (It->second && It->second->GetVisibility() != EVisibility::Hidden)
		{
			It->second->Update(MousePos);
		}
	}
}

bool Canvas::IsValid(Widget* In) const
{
	return IsValid(In->GetName());
}

bool Canvas::IsValid(const String& In) const
{
	auto It = Widgets.find(In);
	return It != Widgets.end() && It->second;
	
}