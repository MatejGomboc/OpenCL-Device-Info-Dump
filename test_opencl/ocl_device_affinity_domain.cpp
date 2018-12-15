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

#include "ocl_device_affinity_domain.h"

std::string oclDeviceAffinityDomain(cl_device_affinity_domain device_affinity_domain)
{
	std::string affinity_domain_string = "";

	if (CL_DEVICE_AFFINITY_DOMAIN_NUMA & device_affinity_domain)
		affinity_domain_string += "CL_DEVICE_AFFINITY_DOMAIN_NUMA ";
	else if (CL_DEVICE_AFFINITY_DOMAIN_L4_CACHE & device_affinity_domain)
		affinity_domain_string += "CL_DEVICE_AFFINITY_DOMAIN_L4_CACHE ";
	else if (CL_DEVICE_AFFINITY_DOMAIN_L3_CACHE & device_affinity_domain)
		affinity_domain_string += "CL_DEVICE_AFFINITY_DOMAIN_L3_CACHE ";
	else if (CL_DEVICE_AFFINITY_DOMAIN_L2_CACHE & device_affinity_domain)
		affinity_domain_string += "CL_DEVICE_AFFINITY_DOMAIN_L2_CACHE ";
	else if (CL_DEVICE_AFFINITY_DOMAIN_L1_CACHE & device_affinity_domain)
		affinity_domain_string += "CL_DEVICE_AFFINITY_DOMAIN_L1_CACHE ";
	else if (CL_DEVICE_AFFINITY_DOMAIN_NEXT_PARTITIONABLE & device_affinity_domain)
		affinity_domain_string += "CL_DEVICE_AFFINITY_DOMAIN_NEXT_PARTITIONABLE ";

	if (affinity_domain_string.length() > 0)
		affinity_domain_string.erase(affinity_domain_string.length() - 1, 1);

	return affinity_domain_string;
}
