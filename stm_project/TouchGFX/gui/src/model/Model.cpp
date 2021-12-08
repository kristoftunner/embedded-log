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

Model::Model() : modelListener(0)
{
}

void Model::tick()
{
	tesla_handler teslaData;
	uint16_t index;
	osStatus_t stat = osOK;
	stat = osMessageQueueGet(guiQueueHandle, &teslaData, 0, 0);
	if(stat == osOK)
	{
		index = aHandler->cellNumber;
		switch(aHandler->appState)
		{
		case state_cellStatusDisplay:
			modelListener->setCellStatus(teslaData.cellTemps[index], teslaData.cellCapacities[index], teslaData.cellVoltages[index],index);
			break;
		case state_chargerStatDisplay:
			break;
		}
	}
}
