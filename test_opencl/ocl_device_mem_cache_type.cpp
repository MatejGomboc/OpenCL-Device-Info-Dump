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

#include "ocl_device_mem_cache_type.h"

std::string oclDeviceMemCacheType(cl_device_mem_cache_type device_mem_cache_type)
{
	switch (device_mem_cache_type)
	{
	case(CL_NONE):
		return "CL_NONE";
	case(CL_READ_ONLY_CACHE):
		return "CL_READ_ONLY_CACHE";
	case(CL_READ_WRITE_CACHE):
		return "CL_READ_WRITE_CACHE";
	default:
		return "CL_UNKNOWN_CACHE_TYPE";
	}
}
