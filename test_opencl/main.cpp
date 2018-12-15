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

#include <iostream>
#include <string>
#include "ocl_error_codes.h"
#include "ocl_device_fp_config.h"
#include "ocl_device_mem_cache_type.h"
#include "ocl_device_local_mem_type.h"
#include "ocl_device_partition_property.h"
#include "ocl_device_affinity_domain.h"
#include "ocl_command_queue_properties.h"
#include "ocl_device_type.h"


void print_error_report(cl_int error_code)
{
	std::cout << "(" << __FILE__ << ", " << __LINE__ << ")";
	std::cout << " OpenCL error: " << oclErrorString(error_code) << ".\n";
}


int main()
{
	cl_uint num_platforms;
	cl_int error_code = clGetPlatformIDs(0, nullptr, &num_platforms);
	if (error_code != CL_SUCCESS)
	{
		print_error_report(error_code);
		return 0;
	}
	std::cout << num_platforms << " OpenCL platforms detected.\n\n\n";

	cl_platform_id* platforms = new cl_platform_id[num_platforms];
	error_code = clGetPlatformIDs(num_platforms, platforms, nullptr);
	if (error_code != CL_SUCCESS)
	{
		delete[] platforms;
		print_error_report(error_code);
		return 0;
	}

	for (cl_uint platform_indx = 0; platform_indx < num_platforms; platform_indx++)
	{
		std::cout << "Platform: " << platform_indx << ".\n";

		size_t param_value_size;
		error_code = clGetPlatformInfo(platforms[platform_indx], CL_PLATFORM_PROFILE, 0, nullptr, &param_value_size);
		if (error_code != CL_SUCCESS)
		{
			delete[] platforms;
			print_error_report(error_code);
			return 0;
		}

		char* platform_profile = new char[param_value_size];
		error_code = clGetPlatformInfo(platforms[platform_indx], CL_PLATFORM_PROFILE, param_value_size,
			platform_profile, nullptr);
		if (error_code != CL_SUCCESS)
		{
			delete[] platforms;
			delete[] platform_profile;
			print_error_report(error_code);
			return 0;
		}
		std::cout << "Platform profile: " << platform_profile << ".\n";
		delete[] platform_profile;

		error_code = clGetPlatformInfo(platforms[platform_indx], CL_PLATFORM_VERSION, 0, nullptr, &param_value_size);
		if (error_code != CL_SUCCESS)
		{
			delete[] platforms;
			print_error_report(error_code);
			return 0;
		}

		char* platform_version = new char[param_value_size];
		error_code = clGetPlatformInfo(platforms[platform_indx], CL_PLATFORM_VERSION, param_value_size,
			platform_version, nullptr);
		if (error_code != CL_SUCCESS)
		{
			delete[] platforms;
			delete[] platform_version;
			print_error_report(error_code);
			return 0;
		}
		std::cout << "Platform version: " << platform_version << ".\n";
		delete[] platform_version;

		error_code = clGetPlatformInfo(platforms[platform_indx], CL_PLATFORM_NAME, 0, nullptr, &param_value_size);
		if (error_code != CL_SUCCESS)
		{
			delete[] platforms;
			print_error_report(error_code);
			return 0;
		}

		char* platform_name = new char[param_value_size];
		error_code = clGetPlatformInfo(platforms[platform_indx], CL_PLATFORM_NAME, param_value_size,
			platform_name, nullptr);
		if (error_code != CL_SUCCESS)
		{
			delete[] platforms;
			delete[] platform_name;
			print_error_report(error_code);
			return 0;
		}
		std::cout << "Platform name: " << platform_name << ".\n";
		delete[] platform_name;

		error_code = clGetPlatformInfo(platforms[platform_indx], CL_PLATFORM_VENDOR, 0, nullptr, &param_value_size);
		if (error_code != CL_SUCCESS)
		{
			delete[] platforms;
			print_error_report(error_code);
			return 0;
		}

		char* platform_vendor = new char[param_value_size];
		error_code = clGetPlatformInfo(platforms[platform_indx], CL_PLATFORM_VENDOR, param_value_size,
			platform_vendor, nullptr);
		if (error_code != CL_SUCCESS)
		{
			delete[] platforms;
			delete[] platform_vendor;
			print_error_report(error_code);
			return 0;
		}
		std::cout << "Platform vendor: " << platform_vendor << ".\n";
		delete[] platform_vendor;


		error_code = clGetPlatformInfo(platforms[platform_indx], CL_PLATFORM_EXTENSIONS, 0, nullptr, &param_value_size);
		if (error_code != CL_SUCCESS)
		{
			delete[] platforms;
			print_error_report(error_code);
			return 0;
		}

		char* platform_extensions = new char[param_value_size];
		error_code = clGetPlatformInfo(platforms[platform_indx], CL_PLATFORM_EXTENSIONS, param_value_size,
			platform_extensions, nullptr);
		if (error_code != CL_SUCCESS)
		{
			delete[] platforms;
			delete[] platform_extensions;
			print_error_report(error_code);
			return 0;
		}
		std::cout << "Platform extensions: " << platform_extensions << ".\n";
		delete[] platform_extensions;

		cl_uint num_devices;
		cl_int error_code = clGetDeviceIDs(platforms[platform_indx], CL_DEVICE_TYPE_ALL, 0, nullptr, &num_devices);
		if (error_code != CL_SUCCESS)
		{
			delete[] platforms;
			print_error_report(error_code);
			return 0;
		}
		std::cout << num_devices << " OpenCL devices detected.\n\n";

		cl_device_id* devices = new cl_device_id[num_devices];
		error_code = clGetDeviceIDs(platforms[platform_indx], CL_DEVICE_TYPE_ALL, num_devices, devices, nullptr);
		if (error_code != CL_SUCCESS)
		{
			delete[] platforms;
			delete[] devices;
			print_error_report(error_code);
			return 0;
		}

		for (cl_uint device_indx = 0; device_indx < num_devices; device_indx++)
		{
			std::cout << "Device: " << device_indx << ".\n";

			cl_uint device_address_bits;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_ADDRESS_BITS, sizeof(cl_uint),
				&device_address_bits, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device address bits: " << device_address_bits << ".\n";

			cl_bool device_available;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_AVAILABLE, sizeof(cl_bool), &device_available, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device available: " << ((device_available) ? "YES" : "NO") << ".\n";

			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_BUILT_IN_KERNELS, 0, nullptr, &param_value_size);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}

			char* device_builtin_kernels = new char[param_value_size];
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_BUILT_IN_KERNELS, param_value_size,
				device_builtin_kernels, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				delete[] device_builtin_kernels;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device built-in kernels: " << device_builtin_kernels << ".\n";
			delete[] device_builtin_kernels;

			cl_bool device_compiler_available;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_COMPILER_AVAILABLE, sizeof(cl_bool),
				&device_compiler_available, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device available: " << ((device_compiler_available) ? "YES" : "NO") << ".\n";

			cl_device_fp_config device_double_fp_config;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_DOUBLE_FP_CONFIG, sizeof(cl_device_fp_config),
				&device_double_fp_config, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device double FP config: " << oclDeviceFPConfig(device_double_fp_config) << ".\n";

			cl_bool device_little_endian;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_ENDIAN_LITTLE, sizeof(cl_bool), &device_little_endian, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device little endian: " << ((device_little_endian) ? "YES" : "NO") << ".\n";

			cl_bool device_error_correction_support;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_ERROR_CORRECTION_SUPPORT, sizeof(cl_bool),
				&device_error_correction_support, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device error correction support: " << ((device_error_correction_support) ? "YES" : "NO") << ".\n";

			cl_device_exec_capabilities device_exec_capabilities;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_EXECUTION_CAPABILITIES, sizeof(cl_device_exec_capabilities),
				&device_exec_capabilities, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device execution capabilities: " << ((device_exec_capabilities) ? "CL_EXEC_NATIVE_KERNEL" :
				"CL_EXEC_KERNEL") << ".\n";

			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_EXTENSIONS, 0, nullptr, &param_value_size);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}

			char* device_extensions = new char[param_value_size];
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_EXTENSIONS, param_value_size,
				device_extensions, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				delete[] device_extensions;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device extensions: " << device_extensions << ".\n";
			delete[] device_extensions;

			cl_ulong device_global_mem_cache_size;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(cl_ulong),
				&device_global_mem_cache_size, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device global memory cache size (bytes): " << device_global_mem_cache_size << ".\n";

			cl_device_mem_cache_type device_global_mem_cache_type;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, sizeof(cl_device_mem_cache_type),
				&device_global_mem_cache_type, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device global memory cache type: " << oclDeviceMemCacheType(device_global_mem_cache_type) << ".\n";

			cl_uint device_global_mem_cacheline_size;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, sizeof(cl_uint),
				&device_global_mem_cacheline_size, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device global memory cache line size (bytes): " << device_global_mem_cacheline_size << ".\n";

			cl_ulong device_global_mem_size;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong),
				&device_global_mem_size, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device global memory size (bytes): " << device_global_mem_size << ".\n";

			cl_bool device_host_unified_memory;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_HOST_UNIFIED_MEMORY, sizeof(cl_bool),
				&device_host_unified_memory, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device-host unified memory: " << ((device_host_unified_memory) ? "YES" : "NO") << ".\n";

			cl_bool device_image_support;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_IMAGE_SUPPORT, sizeof(cl_bool),
				&device_image_support, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device image support: " << ((device_image_support) ? "YES" : "NO") << ".\n";

			size_t device_image2d_max_height;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_IMAGE2D_MAX_HEIGHT, sizeof(size_t),
				&device_image2d_max_height, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device image2D maximum height: " << device_image2d_max_height << ".\n";

			size_t device_image2d_max_width;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_IMAGE2D_MAX_WIDTH, sizeof(size_t),
				&device_image2d_max_width, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device image2D maximum width: " << device_image2d_max_width << ".\n";

			size_t device_image3d_max_depth;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_IMAGE3D_MAX_DEPTH, sizeof(size_t),
				&device_image3d_max_depth, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device image3D maximum depth: " << device_image3d_max_depth << ".\n";

			size_t device_image3d_max_height;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_IMAGE3D_MAX_HEIGHT, sizeof(size_t),
				&device_image3d_max_height, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device image3D maximum height: " << device_image3d_max_height << ".\n";

			size_t device_image3d_max_width;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_IMAGE3D_MAX_WIDTH, sizeof(size_t),
				&device_image3d_max_width, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device image3D maximum width: " << device_image3d_max_width << ".\n";

			size_t device_image_max_buffer_size;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_IMAGE_MAX_BUFFER_SIZE, sizeof(size_t),
				&device_image_max_buffer_size, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device image maximum buffer size (pixels): " << device_image_max_buffer_size << ".\n";

			size_t device_image_max_array_size;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_IMAGE_MAX_ARRAY_SIZE, sizeof(size_t),
				&device_image_max_array_size, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device image maximum array size (images): " << device_image_max_array_size << ".\n";

			cl_bool device_linker_available;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_LINKER_AVAILABLE, sizeof(cl_bool),
				&device_linker_available, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device linker available: " << ((device_linker_available) ? "YES" : "NO") << ".\n";

			cl_ulong device_local_mem_size;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong),
				&device_local_mem_size, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device local memory size (bytes): " << device_local_mem_size << ".\n";

			cl_device_local_mem_type device_local_mem_type;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_LOCAL_MEM_TYPE, sizeof(cl_device_local_mem_type),
				&device_local_mem_type, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device local memory type: " << oclDeviceLocalMemType(device_local_mem_type) << ".\n";

			cl_uint device_max_clock_freq;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint),
				&device_max_clock_freq, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device maximum clock frequency (MHz): " << device_max_clock_freq << ".\n";

			cl_uint device_max_compute_units;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint),
				&device_max_compute_units, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device maximum num of parallel compute units: " << device_max_compute_units << ".\n";

			cl_uint device_max_constant_args;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MAX_CONSTANT_ARGS, sizeof(cl_uint),
				&device_max_constant_args, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device max num of const args: " << device_max_constant_args << ".\n";

			cl_ulong device_max_constant_buffer_size;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(cl_ulong),
				&device_max_constant_buffer_size, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device max const buffer size (bytes): " << device_max_constant_buffer_size << ".\n";

			cl_ulong device_max_mem_alloc_size;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(cl_ulong),
				&device_max_mem_alloc_size, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device max size of memory object allocation (bytes): " << device_max_mem_alloc_size << ".\n";

			size_t device_max_parameter_size;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MAX_PARAMETER_SIZE, sizeof(size_t),
				&device_max_parameter_size, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device max parameter size (bytes): " << device_max_parameter_size << ".\n";

			cl_uint device_max_read_image_args;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MAX_READ_IMAGE_ARGS, sizeof(cl_uint),
				&device_max_read_image_args, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Max number of simultaneous image objects read by a kernel: " <<
				device_max_read_image_args << ".\n";

			cl_uint device_max_samplers;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MAX_SAMPLERS, sizeof(cl_uint),
				&device_max_samplers, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device max samplers: " << device_max_samplers << ".\n";

			size_t device_max_work_group_size;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t),
				&device_max_work_group_size, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device max work-group size: " << device_max_work_group_size << ".\n";

			cl_uint device_max_work_item_dimensions;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint),
				&device_max_work_item_dimensions, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device max work-item dimensions: " << device_max_work_item_dimensions << ".\n";
			
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MAX_WORK_ITEM_SIZES, 0, nullptr, &param_value_size);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}

			size_t* device_max_work_item_sizes = new size_t[param_value_size / sizeof(size_t)];
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MAX_WORK_ITEM_SIZES, param_value_size,
				device_max_work_item_sizes, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				delete[] device_max_work_item_sizes;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device max work-item sizes: ";

			for (size_t work_item_indx = 0; work_item_indx < param_value_size / sizeof(size_t); work_item_indx++)
				std::cout << device_max_work_item_sizes[work_item_indx] << ",";

			std::cout << "\b.\n";

			delete[] device_max_work_item_sizes;

			cl_uint device_max_write_image_args;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MAX_WRITE_IMAGE_ARGS, sizeof(cl_uint),
				&device_max_write_image_args, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device max write image args: " << device_max_write_image_args << ".\n";

			cl_uint device_mem_base_addr_align;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MEM_BASE_ADDR_ALIGN, sizeof(cl_uint),
				&device_mem_base_addr_align, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device mem base addr align (bits): " << device_mem_base_addr_align << ".\n";

			cl_uint device_min_data_type_align_size;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE, sizeof(cl_uint),
				&device_min_data_type_align_size, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device min data type align size (bytes): " << device_min_data_type_align_size << ".\n";

			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_NAME, 0, nullptr, &param_value_size);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}

			char* device_name = new char[param_value_size];
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_NAME, param_value_size, device_name, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				delete[] device_name;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device name: " << device_name << ".\n";
			delete[] device_name;

			cl_uint device_native_vector_width_char;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR, sizeof(cl_uint),
				&device_native_vector_width_char, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device native vector width of char: " << device_native_vector_width_char << ".\n";

			cl_uint device_native_vector_width_short;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT, sizeof(cl_uint),
				&device_native_vector_width_short, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device native vector width of short: " << device_native_vector_width_short << ".\n";

			cl_uint device_native_vector_width_int;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_NATIVE_VECTOR_WIDTH_INT, sizeof(cl_uint),
				&device_native_vector_width_int, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device native vector width of int: " << device_native_vector_width_int << ".\n";

			cl_uint device_native_vector_width_long;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG, sizeof(cl_uint),
				&device_native_vector_width_long, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device native vector width of long: " << device_native_vector_width_long << ".\n";

			cl_uint device_native_vector_width_float;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT, sizeof(cl_uint),
				&device_native_vector_width_float, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device native vector width of float: " << device_native_vector_width_float << ".\n";

			cl_uint device_native_vector_width_double;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE, sizeof(cl_uint),
				&device_native_vector_width_double, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device native vector width of double: " << device_native_vector_width_double << ".\n";

			cl_uint device_native_vector_width_half;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF, sizeof(cl_uint),
				&device_native_vector_width_half, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device native vector width of half: " << device_native_vector_width_half << ".\n";

			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_OPENCL_C_VERSION, 0, nullptr, &param_value_size);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}

			char* device_opencl_c_version = new char[param_value_size];
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_OPENCL_C_VERSION, param_value_size,
				device_opencl_c_version, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				delete[] device_opencl_c_version;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device OpenCL C version: " << device_opencl_c_version << ".\n";
			delete[] device_opencl_c_version;

			cl_device_id device_parent_device;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PARENT_DEVICE, sizeof(cl_device_id),
				&device_parent_device, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device has parent device: " << ((device_parent_device != NULL) ? "YES" : "NO") << ".\n";

			cl_uint device_partition_max_sub_devices;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PARTITION_MAX_SUB_DEVICES, sizeof(cl_uint),
				&device_partition_max_sub_devices, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device partition max sub-devices: " << device_partition_max_sub_devices << ".\n";

			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PARTITION_PROPERTIES, 0, nullptr, &param_value_size);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}

			cl_device_partition_property* device_partition_properties =
				new cl_device_partition_property[param_value_size / sizeof(cl_device_partition_property)];
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PARTITION_PROPERTIES, param_value_size,
				device_partition_properties, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				delete[] device_partition_properties;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device partition properties: ";

			for (size_t device_partition_prop_indx = 0; device_partition_prop_indx < param_value_size / sizeof(cl_device_partition_property);
				device_partition_prop_indx++)
				std::cout << oclDevicePartitionProperty(device_partition_properties[device_partition_prop_indx]) << ",";

			std::cout << "\b.\n";

			delete[] device_partition_properties;

			cl_device_affinity_domain device_partition_affinity_domain;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PARTITION_AFFINITY_DOMAIN, sizeof(cl_device_affinity_domain),
				&device_partition_affinity_domain, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device partition affinity domain: " << oclDeviceAffinityDomain(device_partition_affinity_domain) << ".\n";

			cl_uint device_preferred_vector_width_char;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, sizeof(cl_uint),
				&device_preferred_vector_width_char, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device preferred vector width of char: " << device_preferred_vector_width_char << ".\n";

			cl_uint device_preferred_vector_width_short;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, sizeof(cl_uint),
				&device_preferred_vector_width_short, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device preferred vector width of short: " << device_preferred_vector_width_short << ".\n";

			cl_uint device_preferred_vector_width_int;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, sizeof(cl_uint),
				&device_preferred_vector_width_int, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device preferred vector width of int: " << device_preferred_vector_width_int << ".\n";

			cl_uint device_preferred_vector_width_long;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, sizeof(cl_uint),
				&device_preferred_vector_width_long, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device preferred vector width of long: " << device_preferred_vector_width_long << ".\n";

			cl_uint device_preferred_vector_width_float;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, sizeof(cl_uint),
				&device_preferred_vector_width_float, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device preferred vector width of float: " << device_preferred_vector_width_float << ".\n";

			cl_uint device_preferred_vector_width_double;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, sizeof(cl_uint),
				&device_preferred_vector_width_double, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device preferred vector width of double: " << device_preferred_vector_width_double << ".\n";

			cl_uint device_preferred_vector_width_half;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF, sizeof(cl_uint),
				&device_preferred_vector_width_half, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device preferred vector width of half: " << device_preferred_vector_width_half << ".\n";

			size_t device_printf_buffer_size;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PRINTF_BUFFER_SIZE, sizeof(size_t),
				&device_printf_buffer_size, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device printf buffer size (bytes): " << device_printf_buffer_size << ".\n";

			cl_bool device_preferred_interop_user_sync;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PREFERRED_INTEROP_USER_SYNC, sizeof(cl_bool),
				&device_preferred_interop_user_sync, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device preferred interop user sync: " << ((device_preferred_interop_user_sync) ? "YES" : "NO") << ".\n";

			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PROFILE, 0, nullptr, &param_value_size);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}

			char* device_profile = new char[param_value_size];
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PROFILE, param_value_size,
				device_profile, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				delete[] device_profile;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device profile: " << device_profile << ".\n";
			delete[] device_profile;

			size_t device_profiling_timer_resolution;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_PROFILING_TIMER_RESOLUTION, sizeof(size_t),
				&device_profiling_timer_resolution, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device profiling timer resolution (ns): " << device_profiling_timer_resolution << ".\n";

			cl_command_queue_properties device_command_queue_properties;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_QUEUE_PROPERTIES, sizeof(cl_command_queue_properties),
				&device_command_queue_properties, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device command queue properties: " << oclDeviceCommandQueueProperties(device_command_queue_properties) << ".\n";

			cl_uint device_reference_count;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_REFERENCE_COUNT, sizeof(cl_uint),
				&device_reference_count, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device reference count: " << device_reference_count << ".\n";

			cl_device_fp_config device_single_fp_config;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_SINGLE_FP_CONFIG, sizeof(cl_device_fp_config),
				&device_single_fp_config, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device single FP config: " << oclDeviceFPConfig(device_single_fp_config) << ".\n";

			cl_device_type device_type;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_TYPE, sizeof(cl_device_type),
				&device_type, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device type: " << oclDeviceType(device_type) << ".\n";

			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_VENDOR, 0, nullptr, &param_value_size);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}

			char* device_vendor = new char[param_value_size];
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_VENDOR, param_value_size,
				device_vendor, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				delete[] device_vendor;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device vendor: " << device_vendor << ".\n";
			delete[] device_vendor;

			cl_uint device_vendor_id;
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_VENDOR_ID, sizeof(cl_uint),
				&device_vendor_id, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device vendor ID: " << device_vendor_id << ".\n";

			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_VERSION, 0, nullptr, &param_value_size);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}

			char* device_version = new char[param_value_size];
			error_code = clGetDeviceInfo(devices[device_indx], CL_DEVICE_VERSION, param_value_size,
				device_version, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				delete[] device_version;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Device version: " << device_version << ".\n";
			delete[] device_version;

			error_code = clGetDeviceInfo(devices[device_indx], CL_DRIVER_VERSION, 0, nullptr, &param_value_size);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				print_error_report(error_code);
				return 0;
			}

			char* driver_version = new char[param_value_size];
			error_code = clGetDeviceInfo(devices[device_indx], CL_DRIVER_VERSION, param_value_size,
				driver_version, nullptr);
			if (error_code != CL_SUCCESS)
			{
				delete[] platforms;
				delete[] devices;
				delete[] driver_version;
				print_error_report(error_code);
				return 0;
			}
			std::cout << "Driver version: " << driver_version << ".\n";
			delete[] driver_version;

			std::cout << "\n";
		}

		delete[] devices;
		std::cout << "\n";
	}

	delete[] platforms;
	return 0;
}
