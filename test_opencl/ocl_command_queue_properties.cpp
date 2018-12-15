/* Copyright (C) 2018 Matej Gomboc

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program. If not, see http://www.gnu.org/licenses/. */

#include "ocl_command_queue_properties.h"

std::string oclDeviceCommandQueueProperties(cl_command_queue_properties command_queue_properties)
{
	std::string command_queue_properties_string = "";

	if (CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE & command_queue_properties)
		command_queue_properties_string += "CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE ";
	else if (CL_QUEUE_PROFILING_ENABLE & command_queue_properties)
		command_queue_properties_string += "CL_QUEUE_PROFILING_ENABLE ";

	if (command_queue_properties_string.length() > 0)
		command_queue_properties_string.erase(command_queue_properties_string.length() - 1, 1);

	return command_queue_properties_string;
}
