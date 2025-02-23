
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
#include "framework.h"

namespace ui_controls
{
	template<class TContent>
	struct ContentContainer
	{
		ContentContainer(TContent content, WORD contentColor)
		{
			m_content = content;
			m_contentColor = contentColor;
		}

		TContent& getContent()
		{
			return m_content;
		}

		WORD& getContentColor()
		{
			return m_contentColor;
		}
	private:
		TContent m_content;
		WORD m_contentColor;
	};

	struct UIElement;

	typedef void (*callback)(UIElement* elem);
	
	struct Selectable
	{
		Selectable(callback& onSelected, 
			callback& onUnSelect, 
			shapes::Shape* slecetShape = nullptr);

		void virtual Select();

		void virtual UnSelect();

		bool IsSelected();

		callback& getSelectCallBack();
		callback& getUnselectCallback();

		shapes::Shape*& getSelectShape();

	private:
		bool m_selected;
		callback m_onSelected;
		callback m_unSelect;
		shapes::Shape* m_selectShape;
	};

	struct Focusable
	{	
		Focusable(callback& onFocusCallback, 
			callback& onUnfocus, 
			shapes::Shape* focusShape = nullptr);

		void virtual Focus();

		void virtual UnFocus();

		bool IsFocused();

		callback& getFocusCallback();

		callback& getUnFocusCallback();

		shapes::Shape*& getFocusShape();

	private:
		bool m_focus;
		callback m_onFocus;
		callback m_onUnFocus;
		shapes::Shape* m_focusShape;//We will replace the current shape with this.	
	};

	struct UIElement
	{
		UIElement(shapes::Shape* shape, COORD position);

		shapes::Shape*& getShape();			
		COORD& getPosition();
		COORD& getActualPosition();

		virtual void Draw(graphics::ConsoleGraphics* graphics, COORD position) = 0;

	private:
		COORD m_position;
		COORD m_actualPosition;
		shapes::Shape* m_shape;		
	};
	
	struct Button : 
		public UIElement, 
		public Focusable, 
		public Selectable,
		public ContentContainer<LPTSTR>
	{		
		Button(shapes::Shape* shapeOfButton, COORD position,
			LPTSTR content, WORD contentColor,
			callback& onSelected,
			callback& onUnSelect,
			callback& onFocusCallback,
			callback& onUnFocusCallback,
			shapes::Shape* focusShape = nullptr,  
			shapes::Shape* slecetShape = nullptr);

		void Draw(graphics::ConsoleGraphics* graphics, COORD position) override;

		void Focus() override;

		void UnFocus() override;

		void Select() override;

		void UnSelect() override;

	private:
		void DrawButtonWithContent(graphics::ConsoleGraphics* graphics,
			COORD position, shapes::Shape* shapeToDraw);
	};

	struct UI_CONTROLS_API View : public UIElement
	{
		View(const char* name, shapes::Shape* shape, COORD position);

		void Draw(graphics::ConsoleGraphics* graphics, COORD position) override;

		const char* getName();

	private:
		std::vector<UIElement*> m_ui_elements;	
		const char* m_name;
	};
}

#endif // !BUTTON_H




