#include "Classes/Public/GUI/Canvas.hpp"
#include "Classes/Public/GUI/Widget.h"
#include "Classes/Public/GUI/Button.h"

Canvas::Canvas()
{
	LOG("Test")
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
	}
}

Widget* Canvas::GetWidget(const String&) const
{
	auto It = Widgets.begin();
	return It != Widgets.end() ? It->second : nullptr;
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