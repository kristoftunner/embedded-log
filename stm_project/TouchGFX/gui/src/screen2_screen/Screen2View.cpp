#include <gui/screen2_screen/Screen2View.hpp>

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::updateVal(unsigned int newValue)
{
	Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", newValue);
	textArea1.resizeToCurrentText();
	textArea1.invalidate();
}
