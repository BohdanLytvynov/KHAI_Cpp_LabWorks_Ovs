#include "pch.h"
#include "UIElements.h"

bool ui_controls::Focusable::IsFocused()
{
	return m_focus;
}

ui_controls::callback& ui_controls::Focusable::getCallback()
{
	return m_onFocus;
}

ui_controls::UIElement::UIElement(shapes::Shape* shape, COORD position)
{
	m_shape = shape;
	m_position = position;
}

shapes::Shape*& ui_controls::UIElement::getShape()
{
	return m_shape;
}

COORD& ui_controls::UIElement::getPosition()
{
	return m_position;
}

char*& ui_controls::Button::getContent()
{
	return m_content;
}

void ui_controls::Button::Draw(graphics::ConsoleGraphics* graphics, COORD position)
{
	auto shape = this->getShape();
	graphics->Draw(shape, position);

	int content_position_x = shape->getWidth() / 2 - std::strlen(m_content) / 2;
	int content_position_y = shape->getHeight() / 2;

	//SetConsoleCursorPosition(Build_COORD(position.X + content_position_x, position.Y + content_position_y));
}

void ui_controls::Button::Focus()
{

}

void ui_controls::Button::UnFocus()
{

}

void ui_controls::View::Draw(graphics::ConsoleGraphics* graphics, COORD position)
{		
	for (auto& elem : m_ui_elements)
	{		
		COORD actual_position = position + elem->getPosition();

		elem->Draw(graphics, actual_position);
	}
}
