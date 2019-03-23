
#include <Classes/Public/GUI/Widget.h>


Widget::Widget()
{
	CurrentVisibility = EVisibility::VisibleWithHitDetection;
}

Widget::~Widget()
{

}

void Widget::SetName(const String& Name)
{

}

void Widget::Draw(sf::RenderTarget* Target)
{

}

void Widget::SetStyle(Style NewStyle)
{

}

void Widget::Update(const sf::Vector2f& MousePos)
{

}

void Widget::SetVisibility(EVisibility NewVis)
{
	CurrentVisibility = NewVis;
}