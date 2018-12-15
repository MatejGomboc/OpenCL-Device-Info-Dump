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

#include "ocl_device_type.h"

std::string oclDeviceType(cl_device_type device_type)
{
	std::string device_type_string = "";

	if (CL_DEVICE_TYPE_DEFAULT & device_type)
		device_type_string += "CL_DEVICE_TYPE_DEFAULT ";
	else if (CL_DEVICE_TYPE_CPU & device_type)
		device_type_string += "CL_DEVICE_TYPE_CPU ";
	else if (CL_DEVICE_TYPE_GPU & device_type)
		device_type_string += "CL_DEVICE_TYPE_GPU ";
	else if (CL_DEVICE_TYPE_ACCELERATOR & device_type)
		device_type_string += "CL_DEVICE_TYPE_ACCELERATOR ";
	else if (CL_DEVICE_TYPE_CUSTOM & device_type)
		device_type_string += "CL_DEVICE_TYPE_CUSTOM ";
	else if (CL_DEVICE_TYPE_ALL & device_type)
		device_type_string += "CL_DEVICE_TYPE_ALL ";

	if (device_type_string.length() > 0)
		device_type_string.erase(device_type_string.length() - 1, 1);

	return device_type_string;
}
