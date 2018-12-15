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

#include "ocl_device_partition_property.h"

std::string oclDevicePartitionProperty(cl_device_partition_property device_partition_property)
{
	switch (device_partition_property)
	{
	case(CL_DEVICE_PARTITION_EQUALLY) :
		return "CL_DEVICE_PARTITION_EQUALLY";
	case(CL_DEVICE_PARTITION_BY_COUNTS):
		return "CL_DEVICE_PARTITION_BY_COUNTS";
	case(CL_DEVICE_PARTITION_BY_COUNTS_LIST_END):
		return "CL_DEVICE_PARTITION_BY_COUNTS_LIST_END";
	case(CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN):
		return "CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN";
	default:
		return "CL_DEVICE_PARTITION_UNKNOWN";;
	}
}
