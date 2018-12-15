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

#include "ocl_device_fp_config.h"

std::string oclDeviceFPConfig(cl_device_fp_config device_fp_config)
{
	std::string config_string = "";

	if (CL_FP_DENORM & device_fp_config)
		config_string += "CL_FP_DENORM ";
	else if (CL_FP_INF_NAN & device_fp_config)
		config_string += "CL_FP_INF_NAN ";
	else if (CL_FP_ROUND_TO_NEAREST & device_fp_config)
		config_string += "CL_FP_ROUND_TO_NEAREST ";
	else if (CL_FP_ROUND_TO_ZERO & device_fp_config)
		config_string += "CL_FP_ROUND_TO_ZERO ";
	else if (CL_FP_ROUND_TO_INF & device_fp_config)
		config_string += "CL_FP_ROUND_TO_INF ";
	else if (CL_FP_FMA & device_fp_config)
		config_string += "CL_FP_FMA ";
	else if (CL_FP_SOFT_FLOAT & device_fp_config)
		config_string += "CL_FP_SOFT_FLOAT ";
	else if (CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT & device_fp_config)
		config_string += "CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT ";

	if (config_string.length() > 0)
		config_string.erase(config_string.length() - 1, 1);

	return config_string;
}
