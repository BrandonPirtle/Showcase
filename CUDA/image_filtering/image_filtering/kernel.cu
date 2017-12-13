#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include "CImg.h"
using namespace cimg_library;

#define MIN(a,b) ((a < b) ? a : b)
#define MAX(a,b) ((a > b) ? a : b)

cudaError_t redFilterCUDA(const char *fname);
cudaError_t greenFilterCUDA(const char *fname);
cudaError_t blueFilterCUDA(const char *fname);
cudaError_t yellowFilterCUDA(const char *fname);
cudaError_t magentaFilterCUDA(const char *fname);
cudaError_t cyanFilterCUDA(const char *fname);
cudaError_t grayscaleLightnessCUDA(const char *fname);
cudaError_t grayscaleAverageCUDA(const char *fname);
cudaError_t grayscaleLuminosityRCUDA(const char *fname);
cudaError_t grayscaleLuminosityGCUDA(const char *fname);
cudaError_t grayscaleLuminosityBCUDA(const char *fname);

/* Color filters should be applied to grayscaled images.
	It is possible to create a grayscale image and then apply the filter. */

__global__ void redFilterKernel(unsigned char *img, int w, int h)
{
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x >= w || y >= h) return;

	img[(y + h) * w + x] = 0;
	img[(y + h + h) * w + x] = 0;
}

__global__ void greenFilterKernel(unsigned char *img, int w, int h)
{
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x >= w || y >= h) return;

	img[y * w + x] = 0;
	img[(y + h + h) * w + x] = 0;
}

__global__ void blueFilterKernel(unsigned char *img, int w, int h)
{
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x >= w || y >= h) return;

	img[y * w + x] = 0;
	img[(y + h) * w + x] = 0;
}

__global__ void yellowFilterKernel(unsigned char *img, int w, int h)
{
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x >= w || y >= h) return;

	img[(y + h + h) * w + x] = 0;
}

__global__ void magentaFilterKernel(unsigned char *img, int w, int h)
{
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x >= w || y >= h) return;

	img[(y + h) * w + x] = 0;
}

__global__ void cyanFilterKernel(unsigned char *img, int w, int h)
{
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x >= w || y >= h) return;

	img[y * w + x] = 0;
}

__global__ void grayscaleLightnessKernel(unsigned char *img, int w, int h) {
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x >= w || y >= h) return;

	int R = img[y * w + x];
	int G = img[(y + h) * w + x];
	int B = img[(y + h + h) * w + x];

	int gray = (MAX(R, MAX(G, B)) + MIN(R, MIN(G, B))) / 2;

	img[y * w + x] = img[(y + h) * w + x] = img[(y + h + h) * w + x] = gray;
}

__global__ void grayscaleAverageKernel(unsigned char *img, int w, int h) {
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x >= w || y >= h) return;

	// R, G, B values for pixel are assigned average of said R, G, B values;
	img[y * w + x] = img[(y + h) * w + x] = img[(y + h + h) * w + x]
		= (img[y * w + x] + img[(y + h) * w + x] + img[(y + h + h) * w + x]) / 3;
}

/* General Luminosity:
	(0.21 R + 0.72 G + 0.07 B) / 3
	(people are more sensitive to green) */

__global__ void grayscaleLuminosityRKernel(unsigned char *img, int w, int h) {
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x >= w || y >= h) return;

	// R, G, B values for pixel are assigned scaled average of said R, G, B values;
	img[y * w + x] = img[(y + h) * w + x] = img[(y + h + h) * w + x]
		= (img[y * w + x] * 0.72 + img[(y + h) * w + x] * 0.21 + img[(y + h + h) * w + x] * 0.07) / 3;
}

__global__ void grayscaleLuminosityGKernel(unsigned char *img, int w, int h) {
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x >= w || y >= h) return;

	// R, G, B values for pixel are assigned scaled average of said R, G, B values;
	img[y * w + x] = img[(y + h) * w + x] = img[(y + h + h) * w + x]
		= (img[y * w + x] * 0.21 + img[(y + h) * w + x] * 0.72 + img[(y + h + h) * w + x] * 0.07) / 3;
}

__global__ void grayscaleLuminosityBKernel(unsigned char *img, int w, int h) {
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x >= w || y >= h) return;

	// R, G, B values for pixel are assigned scaled average of said R, G, B values;
	img[y * w + x] = img[(y + h) * w + x] = img[(y + h + h) * w + x]
		= (img[y * w + x] * 0.07 + img[(y + h) * w + x] * 0.21 + img[(y + h + h) * w + x] * 0.72) / 3;
}

int checkFunctionCudaSuccess(cudaError_t status, char *func)
{
	int rc = 0;
	if (status != cudaSuccess)
	{
		fprintf(stderr, "%s failed!", func);
		rc = 1;
	}
	return rc;
}

int main(int argc, char *argv[])
{
	cudaError_t cudaStatus;

    // Adds red filter in parallel
    cudaStatus = redFilterCUDA(argv[1]);
	if (checkFunctionCudaSuccess(cudaStatus, "redFilterCUDA"))
	{
		return 1;
	}

	// Adds green filter in parallel
	cudaStatus = greenFilterCUDA(argv[1]);
	if (checkFunctionCudaSuccess(cudaStatus, "greenFilterCUDA"))
	{
		return 1;
	}

	// Adds blue filter in parallel
	cudaStatus = blueFilterCUDA(argv[1]);
	if (checkFunctionCudaSuccess(cudaStatus, "blueFilterCUDA"))
	{
		return 1;
	}

	// Adds yellow filter in parallel
	cudaStatus = yellowFilterCUDA(argv[1]);
	if (checkFunctionCudaSuccess(cudaStatus, "yellowFilterCUDA"))
	{
		return 1;
	}

	// Adds magenta filter in parallel
	cudaStatus = magentaFilterCUDA(argv[1]);
	if (checkFunctionCudaSuccess(cudaStatus, "magentaFilterCUDA"))
	{
		return 1;
	}

	// Adds cyan filter in parallel
	cudaStatus = cyanFilterCUDA(argv[1]);
	if (checkFunctionCudaSuccess(cudaStatus, "cyanFilterCUDA"))
	{
		return 1;
	}

	// Turn image grayscale using Lightness method in parallel
	cudaStatus = grayscaleLightnessCUDA(argv[1]);
	if (checkFunctionCudaSuccess(cudaStatus, "grayscaleLightnessCUDA"))
	{
		return 1;
	}

	// Turn image grayscale using Average method in parallel
	cudaStatus = grayscaleAverageCUDA(argv[1]);
	if (checkFunctionCudaSuccess(cudaStatus, "grayscaleAverageCUDA"))
	{
		return 1;
	}

	// Turn image grayscale using Luminosity R method in parallel
	cudaStatus = grayscaleLuminosityRCUDA(argv[1]);
	if (checkFunctionCudaSuccess(cudaStatus, "grayscaleLuminosityRCUDA"))
	{
		return 1;
	}

	// Turn image grayscale using Luminosity G method in parallel
	cudaStatus = grayscaleLuminosityGCUDA(argv[1]);
	if (checkFunctionCudaSuccess(cudaStatus, "grayscaleLuminosityGCUDA"))
	{
		return 1;
	}

	// Turn image grayscale using Luminosity B method in parallel
	cudaStatus = grayscaleLuminosityBCUDA(argv[1]);
	if (checkFunctionCudaSuccess(cudaStatus, "grayscaleLuminosityBCUDA"))
	{
		return 1;
	}

    // cudaDeviceReset must be called before exiting in order for profiling and
    // tracing tools such as Nsight and Visual Profiler to show complete traces.
    cudaStatus = cudaDeviceReset();
    if (cudaStatus != cudaSuccess)
	{
        fprintf(stderr, "cudaDeviceReset failed!");
        return 1;
    }

	return 0;
}

cudaError_t redFilterCUDA(const char *fname)
{
	CImg<unsigned char> src(fname);
	int w = src.width();
	int h = src.height();
	unsigned long s = src.size();
	unsigned char *src_ptr = src.data();
	unsigned char *src_kptr;
	
    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaError_t cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

	// Allocate GPU buffers for three vectors (two input, one output).
    cudaStatus = cudaMalloc((void**)&src_kptr, s);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(src_kptr, src_ptr, s, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	// Launch kernel for 256 blocks and a multitude of threads based on image size.
	dim3 blkDim(16, 16, 1);
	dim3 grdDim((w + 15) / 16, (h + 15) / 16, 1);
	redFilterKernel<<<grdDim, blkDim>>>(src_kptr, w, h);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "redFilterKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching redFilterKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(src_ptr, src_kptr, s, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	src.save("./images/redFilter.bmp");

Error:
    cudaFree(src_kptr);

	return cudaStatus;
}

cudaError_t greenFilterCUDA(const char *fname)
{
	CImg<unsigned char> src(fname);
	int w = src.width();
	int h = src.height();
	unsigned long s = src.size();
	unsigned char *src_ptr = src.data();
	unsigned char *src_kptr;
	
    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaError_t cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

	// Allocate GPU buffers for three vectors (two input, one output).
    cudaStatus = cudaMalloc((void**)&src_kptr, s);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(src_kptr, src_ptr, s, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	// Launch kernel for 256 blocks and a multitude of threads based on image size.
	dim3 blkDim(16, 16, 1);
	dim3 grdDim((w + 15) / 16, (h + 15) / 16, 1);
	greenFilterKernel<<<grdDim, blkDim>>>(src_kptr, w, h);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "greenFilterKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching redFilterKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(src_ptr, src_kptr, s, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	src.save("./images/greenFilter.bmp");

Error:
    cudaFree(src_kptr);

	return cudaStatus;
}

cudaError_t blueFilterCUDA(const char *fname)
{
	CImg<unsigned char> src(fname);
	int w = src.width();
	int h = src.height();
	unsigned long s = src.size();
	unsigned char *src_ptr = src.data();
	unsigned char *src_kptr;
	
    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaError_t cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

	// Allocate GPU buffers for three vectors (two input, one output).
    cudaStatus = cudaMalloc((void**)&src_kptr, s);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(src_kptr, src_ptr, s, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	// Launch kernel for 256 blocks and a multitude of threads based on image size.
	dim3 blkDim(16, 16, 1);
	dim3 grdDim((w + 15) / 16, (h + 15) / 16, 1);
	blueFilterKernel<<<grdDim, blkDim>>>(src_kptr, w, h);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "blueFilterKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching blueFilterKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(src_ptr, src_kptr, s, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	src.save("./images/blueFilter.bmp");

Error:
    cudaFree(src_kptr);

	return cudaStatus;
}

cudaError_t yellowFilterCUDA(const char *fname)
{
	CImg<unsigned char> src(fname);
	int w = src.width();
	int h = src.height();
	unsigned long s = src.size();
	unsigned char *src_ptr = src.data();
	unsigned char *src_kptr;
	
    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaError_t cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

	// Allocate GPU buffers for three vectors (two input, one output).
    cudaStatus = cudaMalloc((void**)&src_kptr, s);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(src_kptr, src_ptr, s, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	// Launch kernel for 256 blocks and a multitude of threads based on image size.
	dim3 blkDim(16, 16, 1);
	dim3 grdDim((w + 15) / 16, (h + 15) / 16, 1);
	yellowFilterKernel<<<grdDim, blkDim>>>(src_kptr, w, h);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "yellowFilterKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching yellowFilterKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(src_ptr, src_kptr, s, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	src.save("./images/yellowFilter.bmp");

Error:
    cudaFree(src_kptr);

	return cudaStatus;
}

cudaError_t magentaFilterCUDA(const char *fname)
{
	CImg<unsigned char> src(fname);
	int w = src.width();
	int h = src.height();
	unsigned long s = src.size();
	unsigned char *src_ptr = src.data();
	unsigned char *src_kptr;
	
    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaError_t cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

	// Allocate GPU buffers for three vectors (two input, one output).
    cudaStatus = cudaMalloc((void**)&src_kptr, s);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(src_kptr, src_ptr, s, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	// Launch kernel for 256 blocks and a multitude of threads based on image size.
	dim3 blkDim(16, 16, 1);
	dim3 grdDim((w + 15) / 16, (h + 15) / 16, 1);
	magentaFilterKernel<<<grdDim, blkDim>>>(src_kptr, w, h);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "magentaFilterKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching magentaFilterKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(src_ptr, src_kptr, s, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	src.save("./images/magentaFilter.bmp");

Error:
    cudaFree(src_kptr);

	return cudaStatus;
}

cudaError_t cyanFilterCUDA(const char *fname)
{
	CImg<unsigned char> src(fname);
	int w = src.width();
	int h = src.height();
	unsigned long s = src.size();
	unsigned char *src_ptr = src.data();
	unsigned char *src_kptr;
	
    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaError_t cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

	// Allocate GPU buffers for three vectors (two input, one output).
    cudaStatus = cudaMalloc((void**)&src_kptr, s);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(src_kptr, src_ptr, s, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	// Launch kernel for 256 blocks and a multitude of threads based on image size.
	dim3 blkDim(16, 16, 1);
	dim3 grdDim((w + 15) / 16, (h + 15) / 16, 1);
	cyanFilterKernel<<<grdDim, blkDim>>>(src_kptr, w, h);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cyanFilterKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching cyanFilterKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(src_ptr, src_kptr, s, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	src.save("./images/cyanFilter.bmp");

Error:
    cudaFree(src_kptr);

	return cudaStatus;
}

// Helper function for using CUDA to turn an image grayscale using Lightness method in parallel.
cudaError_t grayscaleLightnessCUDA(const char *fname)
{
	CImg<unsigned char> src(fname);
	int w = src.width();
	int h = src.height();
	unsigned long s = src.size();
	unsigned char *src_ptr = src.data();
	unsigned char *src_kptr;
	
    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaError_t cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

	// Allocate GPU buffers for three vectors (two input, one output).
    cudaStatus = cudaMalloc((void**)&src_kptr, s);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(src_kptr, src_ptr, s, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	// Launch kernel for 256 blocks and a multitude of threads based on image size.
	dim3 blkDim(16, 16, 1);
	dim3 grdDim((w + 15) / 16, (h + 15) / 16, 1);
	grayscaleLightnessKernel<<<grdDim, blkDim>>>(src_kptr, w, h);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "grayscaleLightnessKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching removeRKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(src_ptr, src_kptr, s, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	src.save("./images/grayscaleLightness.bmp");

Error:
    cudaFree(src_kptr);

	return cudaStatus;
}

// Helper function for using CUDA to turn an image grayscale using Average method in parallel.
cudaError_t grayscaleAverageCUDA(const char *fname)
{
	CImg<unsigned char> src(fname);
	int w = src.width();
	int h = src.height();
	unsigned long s = src.size();
	unsigned char *src_ptr = src.data();
	unsigned char *src_kptr;
	
    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaError_t cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

	// Allocate GPU buffers for three vectors (two input, one output).
    cudaStatus = cudaMalloc((void**)&src_kptr, s);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(src_kptr, src_ptr, s, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	// Launch kernel for 256 blocks and a multitude of threads based on image size.
	dim3 blkDim(16, 16, 1);
	dim3 grdDim((w + 15) / 16, (h + 15) / 16, 1);
	grayscaleAverageKernel<<<grdDim, blkDim>>>(src_kptr, w, h);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "grayscaleAverageKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching removeRKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(src_ptr, src_kptr, s, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	src.save("./images/grayscaleAverage.bmp");

Error:
    cudaFree(src_kptr);

	return cudaStatus;
}

// Helper function for using CUDA to turn an image grayscale using Luminosity R method in parallel.
cudaError_t grayscaleLuminosityRCUDA(const char *fname)
{
	CImg<unsigned char> src(fname);
	int w = src.width();
	int h = src.height();
	unsigned long s = src.size();
	unsigned char *src_ptr = src.data();
	unsigned char *src_kptr;
	
    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaError_t cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

	// Allocate GPU buffers for three vectors (two input, one output).
    cudaStatus = cudaMalloc((void**)&src_kptr, s);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(src_kptr, src_ptr, s, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	// Launch kernel for 256 blocks and a multitude of threads based on image size.
	dim3 blkDim(16, 16, 1);
	dim3 grdDim((w + 15) / 16, (h + 15) / 16, 1);
	grayscaleLuminosityRKernel<<<grdDim, blkDim>>>(src_kptr, w, h);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "grayscaleLuminosityRKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching removeRKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(src_ptr, src_kptr, s, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	src.save("./images/grayscaleLuminosityR.bmp");

Error:
    cudaFree(src_kptr);

	return cudaStatus;
}

// Helper function for using CUDA to turn an image grayscale using Luminosity G method in parallel.
cudaError_t grayscaleLuminosityGCUDA(const char *fname)
{
	CImg<unsigned char> src(fname);
	int w = src.width();
	int h = src.height();
	unsigned long s = src.size();
	unsigned char *src_ptr = src.data();
	unsigned char *src_kptr;
	
    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaError_t cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

	// Allocate GPU buffers for three vectors (two input, one output).
    cudaStatus = cudaMalloc((void**)&src_kptr, s);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(src_kptr, src_ptr, s, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	// Launch kernel for 256 blocks and a multitude of threads based on image size.
	dim3 blkDim(16, 16, 1);
	dim3 grdDim((w + 15) / 16, (h + 15) / 16, 1);
	grayscaleLuminosityGKernel<<<grdDim, blkDim>>>(src_kptr, w, h);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "grayscaleLuminosityGKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching removeRKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(src_ptr, src_kptr, s, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	src.save("./images/grayscaleLuminosityG.bmp");

Error:
    cudaFree(src_kptr);

	return cudaStatus;
}

// Helper function for using CUDA to turn an image grayscale using Luminosity B method in parallel.
cudaError_t grayscaleLuminosityBCUDA(const char *fname)
{
	CImg<unsigned char> src(fname);
	int w = src.width();
	int h = src.height();
	unsigned long s = src.size();
	unsigned char *src_ptr = src.data();
	unsigned char *src_kptr;
	
    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaError_t cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

	// Allocate GPU buffers for three vectors (two input, one output).
    cudaStatus = cudaMalloc((void**)&src_kptr, s);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(src_kptr, src_ptr, s, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	// Launch kernel for 256 blocks and a multitude of threads based on image size.
	dim3 blkDim(16, 16, 1);
	dim3 grdDim((w + 15) / 16, (h + 15) / 16, 1);
	grayscaleLuminosityBKernel<<<grdDim, blkDim>>>(src_kptr, w, h);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "grayscaleLuminosityBKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching removeRKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(src_ptr, src_kptr, s, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

	src.save("./images/grayscaleLuminosityB.bmp");

Error:
    cudaFree(src_kptr);

	return cudaStatus;
}
