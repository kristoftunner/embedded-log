#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::updateVal(unsigned int newValue)
{
	Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", newValue);
	textArea1.resizeToCurrentText();
	textArea1.invalidate();
}
