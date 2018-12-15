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

#include "ocl_device_local_mem_type.h"

std::string oclDeviceLocalMemType(cl_device_local_mem_type device_local_mem_type)
{
	switch (device_local_mem_type)
	{
	case(CL_NONE):
		return "CL_NONE";
	case(CL_LOCAL):
		return "CL_LOCAL";
	case(CL_GLOBAL):
		return "CL_GLOBAL";
	default:
		return "CL_UNKNOWN_LOCAL_MEM_TYPE";
	}
}
