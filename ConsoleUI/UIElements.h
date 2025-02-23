
#ifndef BUTTON_H

#define BUTTON_H

#pragma region Export

#ifdef UI_CONTROLS_EXPORT
#define UI_CONTROLS_API __declspec(dllexport)
#else
#define UI_CONTROLS_API __declspec(dllimport)
#endif

#pragma endregion

#include"../ConsoleUI/Shapes.h"
#include"../ConsoleUI/console_graphics.h"
#include<vector>

namespace ui_controls
{
	struct UIElement;

	typedef void (*callback)(UIElement* elem);

	struct Focusable
	{	
		void virtual Focus() = 0;

		void virtual UnFocus() = 0;

		bool IsFocused();

		callback& getCallback();

	private:
		bool m_focus;
		callback m_onFocus;
		shapes::Shape* m_focusShape;//We will replace the current shape with this.
	};

	struct UIElement
	{
		UIElement(shapes::Shape* shape, COORD position);

		shapes::Shape*& getShape();			
		COORD& getPosition();

		virtual void Draw(graphics::ConsoleGraphics* graphics, COORD position) = 0;

	private:
		COORD m_position;
		shapes::Shape* m_shape;		
	};
	
	struct UI_CONTROLS_API Button : public UIElement, public Focusable
	{
		char*& getContent();	

		void Draw(graphics::ConsoleGraphics* graphics, COORD position) override;

		void Focus() override;

		void UnFocus() override;

	private:
		char* m_content;		
	};

	struct UI_CONTROLS_API View : public UIElement
	{
		void Draw(graphics::ConsoleGraphics* graphics, COORD position) override;

	private:
		std::vector<UIElement*> m_ui_elements;		
	};
}

#endif // !BUTTON_H




