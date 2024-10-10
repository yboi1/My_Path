#include <cuda_runtime.h>
#include <iostream>
#include <chrono>

#define N 1024  // 定义矩阵的大小
#define TILE_WIDTH 16  // 定义共享内存块的大小

__global__ void matrixMulSharedKernel(float *A, float *B, float *C, int width) {
    __shared__ float shared_A[TILE_WIDTH][TILE_WIDTH];
    __shared__ float shared_B[TILE_WIDTH][TILE_WIDTH];

    int bx = blockIdx.x;
    int by = blockIdx.y;
    int tx = threadIdx.x;
    int ty = threadIdx.y;

    int row = by * TILE_WIDTH + ty;
    int col = bx * TILE_WIDTH + tx;

    float value = 0.0f;

    // 分块加载矩阵到共享内存
    for (int m = 0; m < (width + TILE_WIDTH - 1) / TILE_WIDTH; ++m) {
        if (row < width && m * TILE_WIDTH + tx < width)
            shared_A[ty][tx] = A[row * width + m * TILE_WIDTH + tx];
        else
            shared_A[ty][tx] = 0.0;

        if (col < width && m * TILE_WIDTH + ty < width)
            shared_B[ty][tx] = B[(m * TILE_WIDTH + ty) * width + col];
        else
            shared_B[ty][tx] = 0.0;

        __syncthreads();

        // 计算当前块的矩阵乘积
        for (int k = 0; k < TILE_WIDTH; ++k) {
            value += shared_A[ty][k] * shared_B[k][tx];
        }

        __syncthreads();
    }

    if (row < width && col < width) {
        C[row * width + col] = value;
    }
}

void matrixMultiplicationShared(float *h_A, float *h_B, float *h_C, int width) {
    int size = width * width * sizeof(float);
    float *d_A, *d_B, *d_C;

    // 分配设备内存
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    // 拷贝数据到设备
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // 定义线程块和网格
    dim3 blockSize(TILE_WIDTH, TILE_WIDTH);
    dim3 gridSize((width + TILE_WIDTH - 1) / TILE_WIDTH, (width + TILE_WIDTH - 1) / TILE_WIDTH);

    // 启动核函数
    matrixMulSharedKernel<<<gridSize, blockSize>>>(d_A, d_B, d_C, width);

    // 拷贝结果回主机
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    // 释放设备内存
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}

int main() {
    int width = N;
    int size = width * width;
    float *h_A = new float[size];
    float *h_B = new float[size];
    float *h_C = new float[size];

    // 初始化矩阵
    for (int i = 0; i < size; i++) {
        h_A[i] = 1.0f;
        h_B[i] = 1.0f;
    }

    // 计时优化后的矩阵乘法
    auto start = std::chrono::high_resolution_clock::now();
    matrixMultiplicationShared(h_A, h_B, h_C, width);
    auto stop = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float, std::milli> duration = stop - start;
    std::cout << "Time after optimization: " << duration.count() << " ms" << std::endl;

    // 清理
    delete[] h_A;
    delete[] h_B;
    delete[] h_C;

    return 0;
}