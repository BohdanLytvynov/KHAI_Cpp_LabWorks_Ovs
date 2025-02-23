#include "pch.h"
#include "UIElements.h"
#include <tchar.h>

ui_controls::Focusable::Focusable(callback& onFocusCallback, callback& onUnFocus,
	shapes::Shape* focusShape)
{
	m_onUnFocus = onUnFocus;
	m_focusShape = focusShape;
	m_onFocus = onFocusCallback;
	m_focus = false;
}

void ui_controls::Focusable::Focus()
{
	m_focus = true;
}

void ui_controls::Focusable::UnFocus()
{
	m_focus = false;
}

bool ui_controls::Focusable::IsFocused()
{
	return m_focus;
}

ui_controls::callback& ui_controls::Focusable::getFocusCallback()
{
	return m_onFocus;
}

ui_controls::callback& ui_controls::Focusable::getUnFocusCallback()
{
	return m_onUnFocus;
}

shapes::Shape*& ui_controls::Focusable::getFocusShape()
{
	return m_focusShape;
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

COORD& ui_controls::UIElement::getActualPosition()
{
	return m_actualPosition;
}

ui_controls::Button::Button(shapes::Shape* shapeOfButton, COORD position,
	LPTSTR content, WORD contentColor,
	callback& onSelected,
	callback& onUnSelect,
	callback& onFocusCallback,
	callback& onUnfocusCallback,
	shapes::Shape* focusShape,
	shapes::Shape* selectShape)
	:UIElement(shapeOfButton, position), Focusable(onFocusCallback, onUnfocusCallback, focusShape),
	Selectable(onSelected, onUnSelect, selectShape), ContentContainer(content, contentColor)
{
	
}

void ui_controls::Button::Draw(graphics::ConsoleGraphics* graphics, COORD position)
{
	auto shape = this->getShape();
	DrawButtonWithContent(graphics, position, shape);
}

void ui_controls::Button::DrawButtonWithContent(
	graphics::ConsoleGraphics* graphics, 
	COORD position, shapes::Shape* shapeToDraw)
{	
	graphics->Draw(shapeToDraw, position);
	auto content = this->getContent();
	auto contentColor = this->getContentColor();
	int content_position_x = shapeToDraw->getWidth() / 2 - _tcslen(content) / 2;
	int content_position_y = shapeToDraw->getHeight() / 2;
	auto io = graphics->getConsoleIOModule();
	io->Print(content,
		Build_COORD(position.X + content_position_x, position.Y + content_position_y),
		contentColor);
}

void ui_controls::Button::Focus()
{
	Focusable::Focus();

	this->getFocusCallback()(this);
}

void ui_controls::Button::UnFocus()
{
	Focusable::UnFocus();

	this->getUnFocusCallback()(this);
}

void ui_controls::Button::Select()
{
	Selectable::Select();

	this->getSelectCallBack()(this);
}

void ui_controls::Button::UnSelect()
{
	Selectable::UnSelect();

	this->getUnselectCallback()(this);
}

ui_controls::View::View(const char* name, shapes::Shape* shape, COORD position)
	:UIElement(shape, position)
{
	m_name = name;
}

void ui_controls::View::Draw(graphics::ConsoleGraphics* graphics, COORD position)
{		
	for (auto& elem : m_ui_elements)
	{		
		COORD actual_position = position + elem->getPosition();
		elem->getActualPosition() = actual_position;
		elem->Draw(graphics, actual_position);
	}
}

const char* ui_controls::View::getName()
{
	return m_name;
}

ui_controls::Selectable::Selectable(callback& onSelected, callback& onUnSelect,
	shapes::Shape* selectShape)
{
	m_unSelect = onUnSelect;
	m_selectShape = selectShape;
	m_onSelected = onSelected;
	m_selected = false;
}

void ui_controls::Selectable::Select()
{
	m_selected = true;
}

void ui_controls::Selectable::UnSelect()
{
	m_selected = false;
}

bool ui_controls::Selectable::IsSelected()
{
	return m_selected;
}

ui_controls::callback& ui_controls::Selectable::getSelectCallBack()
{
	return m_onSelected;
}

ui_controls::callback& ui_controls::Selectable::getUnselectCallback()
{
	return m_unSelect;
}

shapes::Shape*& ui_controls::Selectable::getSelectShape()
{
	return m_selectShape;
}

