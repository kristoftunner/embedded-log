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

void Screen1View::updateCellStatus(unsigned int temp, unsigned int capacity, unsigned int voltage)
{
	Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%u", capacity);
	Unicode::snprintf(textArea2_1Buffer, TEXTAREA2_1_SIZE, "%u", voltage);
	Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%d", temp);
	textArea2.resizeToCurrentText();
	textArea3.resizeToCurrentText();
	textArea2_1.resizeToCurrentText();
	this->invalidate();
}
