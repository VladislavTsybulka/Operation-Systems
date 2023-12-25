#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>

class Action {
public:
    virtual double perform(double a, double b) = 0;
};

class AdditionAction : public Action {
public:
    double perform(double a, double b) override {
        return a + b;
    }
};

class MultiplicationAction : public Action {
public:
    double perform(double a, double b) override {
        return a * b;
    }
};

class SumOfSquaresAction : public Action {
public:
    double perform(double a, double b) override {
        return (a * a) + (b * b);
    }
};

class FileProcessor {
private:
    std::string filename;
    Action* action;
    double result;

public:
    FileProcessor(const std::string& filename, Action* action) : filename(filename), action(action), result(0.0) {}

    double getResult() const {
        return result;
    }

    void process() {
        std::ifstream file(filename);
        if (file.is_open()) {
            double a, b;
            file >> a >> b;
            file.close();

            result = action->perform(a, b);
        }
        else {
            std::cerr << "Failed to open file: " << filename << std::endl;
        }
    }
};

void processFiles(const std::vector<std::string>& filenames, Action* action, std::vector<FileProcessor>& processors, std::mutex& mutex) {
    for (const auto& filename : filenames) {
        FileProcessor processor(filename, action);
        processor.process();

        std::lock_guard<std::mutex> lock(mutex);
        processors.push_back(std::move(processor));
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    std::string directory;
    int numThreads, n;

    std::cout << "Введите абсолютный путь к директории: ";
    std::cin >> directory;

    std::cout << "Введите количество потоков: ";
    std::cin >> numThreads;

    std::cout << "Введите количество обрабатываемых файлов: ";
    std::cin >> n;

    std::vector<std::string> filenames;
    for (int i = 1; i <= n; ++i) {
        filenames.push_back(directory + "/in_" + std::to_string(i) + ".dat");
    }

    std::vector<Action*> actions = { new AdditionAction(), new MultiplicationAction(), new SumOfSquaresAction() };

    std::vector<FileProcessor> processors;
    std::mutex mutex;

    std::vector<std::thread> threads;
    int numFilesPerThread = filenames.size() / numThreads;
    int remainingFiles = filenames.size() % numThreads;
    int start = 0;

    for (int i = 0; i < numThreads; ++i) {
        int numFiles = numFilesPerThread + (i < remainingFiles ? 1 : 0);
        std::vector<std::string> threadFilenames(filenames.begin() + start, filenames.begin() + start + numFiles);

        threads.push_back(std::thread(processFiles, threadFilenames, actions[i % actions.size()], std::ref(processors), std::ref(mutex)));

        start += numFiles;
    }

    for (std::thread& thread : threads) {
        thread.join();
    }

    double totalResult = 0.0;
    for (const FileProcessor& processor : processors) {
        totalResult += processor.getResult();
    }

    std::ofstream outputFile(directory + "/out.dat");
    if (outputFile.is_open()) {
        outputFile << totalResult << std::endl;
        outputFile.close();
        std::cout << "Результат записан в " << directory << "/out.dat" << std::endl;
    }
    else {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
    }

    for (Action* action : actions) {
        delete action;
    }

    return 0;
}
