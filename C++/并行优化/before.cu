#include <cuda_runtime.h>
#include <iostream>
#include <chrono>

#define N 1024  // 定义矩阵的大小

__global__ void matrixMulKernel(float *A, float *B, float *C, int width) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < width && col < width) {
        float value = 0.0f;
        for (int k = 0; k < width; k++) {
            value += A[row * width + k] * B[k * width + col];
        }
        C[row * width + col] = value;
    }
}

void matrixMultiplication(float *h_A, float *h_B, float *h_C, int width) {
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
    dim3 blockSize(16, 16);
    dim3 gridSize((width + blockSize.x - 1) / blockSize.x, (width + blockSize.y - 1) / blockSize.y);

    // 启动核函数
    matrixMulKernel<<<gridSize, blockSize>>>(d_A, d_B, d_C, width);

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

    // 计时优化前的矩阵乘法
    auto start = std::chrono::high_resolution_clock::now();
    matrixMultiplication(h_A, h_B, h_C, width);
    auto stop = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float, std::milli> duration = stop - start;
    std::cout << "Time before optimization: " << duration.count() << " ms" << std::endl;

    // 清理
    delete[] h_A;
    delete[] h_B;
    delete[] h_C;

    return 0;
}