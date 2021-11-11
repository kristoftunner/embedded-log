/*
 * NectiveButtonController.hpp
 *
 *  Created on: Nov 10, 2021
 *      Author: krist
 */

#ifndef NECTIVEBUTTONCONTROLLER_HPP_
#define NECTIVEBUTTONCONTROLLER_HPP_


#include <platform/driver/button/ButtonController.hpp>

class NectiveButtonController : public touchgfx::ButtonController
{
	virtual void init();
	virtual bool sample(uint8_t& key);

};


#endif /* NECTIVEBUTTONCONTROLLER_HPP_ */
