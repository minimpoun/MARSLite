#pragma once

#include "Common.h"
#include "Source/Utility/ResourceManager.hpp"
#include "Public/GUI/Styles.hpp"

enum class EVisibility
{
	VisibleWithHitDetection,
	VisibilityWithoutHitDetection,
	Hidden,
};

/*
 * The Widget acts as a base class for all User Interface elements
 * The Widget contains all of the code to allow the Canvas to draw the UI to the screen
 * A Widget can not be drawn to the screen by itself, it's just
 * the base class for the actual UI elements; like a button or a image.
 *
 * Some elements can contain child widgets. For example, a button can contain
 * a Text widget. Or a Panel can contain a several buttons which each contain their own children.
 * The Widget base class doesn't know about it's children. You can't do anything like this:
 *
 * Widget->GetChildren();
 *
 * You CAN however do, Button->GetParent();
 *
 * The sub-elements will know about it's children (ex: Button->GetChild(); ).
 *
 * Some elements are not actually drawn to the screen, they simply exist to act as a container.
 * These elements are classed as "Container Widgets", as they do not actually get rendered.
 *
 * The Canvas doesn't treat a Container Widget any different from a Standard Widget other than it's
 * ignored during Draw().
 *
 */
class Widget
{
public:
	
	Widget();
	virtual ~Widget();

	virtual void SetName(const String& Name);
	virtual void SetStyle(Style NewStyle);
	virtual void Draw(sf::RenderTarget* Target);
	virtual void Update(const sf::Vector2f& MousePos);
	
	const String& GetName() const { return Name; }
	
	virtual void SetVisibility(EVisibility NewVis);
	EVisibility GetVisibility() const { return CurrentVisibility; }
	
protected:
	
	String Name;

private:

	EVisibility CurrentVisibility;

};