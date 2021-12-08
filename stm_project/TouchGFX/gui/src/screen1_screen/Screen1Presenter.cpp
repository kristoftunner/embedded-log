#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::setCellStatus(unsigned int temperature, unsigned int capacity, unsigned int voltage, unsigned int cellIndex)
{
	view.updateCellStatus(temperature,capacity,voltage,cellIndex);
}

