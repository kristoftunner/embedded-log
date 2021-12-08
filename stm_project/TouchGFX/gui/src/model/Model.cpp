#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "cmsis_os2.h"
#include "main.h"
#include "teslactrl.h"
#include "app.h"

extern "C" osMessageQueueId_t guiQueueHandle;
extern "C" app_state appState;

Model::Model() : modelListener(0)
{
}

void Model::tick()
{
	tesla_handler temp;
	osStatus_t stat = osOK;
	stat = osMessageQueueGet(guiQueueHandle, &temp, 0, 0);
	if(stat == osOK)
	{
		switch(appState)
		{
		case state_cellStatusDisplay:
			modelListener->setCellStatus(temp.cellTemps[0], temp.cellCapacities[0], temp.cellVoltages[0]);
			break;
		case state_chargerStatDisplay:
			break;
		}
	}
}
