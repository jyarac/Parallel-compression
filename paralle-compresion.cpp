%%writefile compressImage.cpp
#include <iostream>
#include <vector>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <omp.h>
#include <chrono>

int num threads = 1;

//Funcion lectura de obtencion de frames
std::vector<std::string> getAllFilePaths() {
    std::vector<std::string> filePaths;
    std::filesystem::directory_iterator end_itr;

    for (std::filesystem::directory_iterator itr("./input/"); itr != end_itr; ++itr) {
        if (std::filesystem::is_regular_file(itr->path())) {
            filePaths.push_back(itr->path().string());
        }
    }

    return filePaths;
}


//Función de compresión de una unica imágen
void compressImage(const std::string& inputPath, const std::string& outputPath) {
    // Load the input image
    cv::Mat inputImage = cv::imread(inputPath, cv::IMREAD_UNCHANGED);

    if (inputImage.empty()) {
        std::cerr << "Could not open or find the image: " << inputPath << std::endl;
        return;
    }

    // Resize to 360p
    cv::Size newSize(640, 360);
    cv::resize(inputImage, inputImage, newSize, cv::INTER_AREA);

    // Save the compressed image
    cv::imwrite(outputPath, inputImage);

    std::cout << "Image compressed and saved at: " << outputPath << std::endl;
}

void main{
    std::vector<std::string> files = getAllFilePaths();
    //create a pragma parallel for loop to iterate over the files
    //start chrono timer to measure time
    auto start = std::chrono::high_resolution_clock::now();
    if (num_threads == 1){
        for (int i = 0; i < files.size(); i++) {
            std::string inputPath = files[i];
            std::string outputPath = "output/" + std::to_string(i) + ".jpg";
            compressImage(inputPath, outputPath);
        }
    }
    else{
        #pragma omp parallel for num_threads(num_threads){
            for (int i = 0; i < files.size(); i++) {
                std::string inputPath = files[i];
                std::string outputPath = "output/" + std::to_string(i) + ".jpg";
                compressImage(inputPath, outputPath);
            }
        }
    }
    //stop chrono timer
    auto stop = std::chrono::high_resolution_clock::now();
    //print time
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " seconds" << std::endl;
    //print number of threads
    std::cout << "Number of threads: " << num_threads << std::endl;
}