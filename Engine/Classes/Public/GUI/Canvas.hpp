#pragma once

#include <Common.h>

#include "Styles.hpp"

#include "Classes/Public/GUI/Button.h"

class Canvas
{
public:
	
	Canvas();
	~Canvas();
	
	template<typename T, typename S>
	T* CreateWidget(String WidgetName, S InStyle);
	
	bool SetWidgetPosition(String Widget, sf::Vector2f NewPos);
	bool SetWidgetVisibility(String Widget, EVisibility NewVisibility);
	
	Widget* GetWidget(const String&) const;
	
	void DrawCanvas(sf::RenderTarget* Target);

	void RefreshWidgets(const sf::Vector2f& MousePos);
	
private:
	
	std::map<String, Widget*> Widgets;

};

template<typename T, typename S>
T* Canvas::CreateWidget(String WidgetName, S InStyle)
{
	T* Widget = new T();
	if (Widget)
	{
		Widget->SetName(WidgetName);
		Widget->SetStyle(InStyle);
		Widgets.emplace(WidgetName, Widget);
		return Widget;
	}
	
	return nullptr;
}