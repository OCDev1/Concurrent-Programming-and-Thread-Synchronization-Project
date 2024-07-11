#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include "BoundedBuffer.h"
#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    std::ifstream config_file(argv[1]);
    if (!config_file) {
        std::cerr << "Error opening configuration file." << std::endl;
        return 1;
    }

    std::vector<int> producer_products;
    std::vector<int> producer_queue_sizes;
    int co_editor_queue_size;
    
    std::string line;
    while (std::getline(config_file, line)) {
        if (line.find("PRODUCER") != std::string::npos) {
            std::getline(config_file, line);
            producer_products.push_back(std::stoi(line));
            std::getline(config_file, line);
            size_t pos = line.find("=");
            producer_queue_sizes.push_back(std::stoi(line.substr(pos + 1)));
        } else if (line.find("Co-Editor queue size") != std::string::npos) {
            size_t pos = line.find("=");
            co_editor_queue_size = std::stoi(line.substr(pos + 1)));
        }
    }

    int num_producers = producer_products.size();
    std::vector<BoundedBuffer*> producer_queues;
    for (int i = 0; i < num_producers; ++i) {
        producer_queues.push_back(new BoundedBuffer(producer_queue_sizes[i]));
    }
    BoundedBuffer sports_queue(co_editor_queue_size);
    BoundedBuffer news_queue(co_editor_queue_size);
    BoundedBuffer weather_queue(co_editor_queue_size);
    BoundedBuffer screen_manager_queue(co_editor_queue_size);

    std::vector<std::thread> producers;
    for (int i = 0; i < num_producers; ++i) {
        Producer prod(i + 1, producer_products[i], *producer_queues[i]);
        producers.push_back(std::thread(&Producer::produce, prod));
    }

    Dispatcher dispatcher(producer_queues, sports_queue, news_queue, weather_queue);
    std::thread dispatcher_thread(&Dispatcher::dispatch, dispatcher);

    CoEditor sports_editor(sports_queue, screen_manager_queue);
    CoEditor news_editor(news_queue, screen_manager_queue);
    CoEditor weather_editor(weather_queue, screen_manager_queue);

    std::thread sports_editor_thread(&CoEditor::edit, sports_editor);
    std::thread news_editor_thread(&CoEditor::edit, news_editor);
    std::thread weather_editor_thread(&CoEditor::edit, weather_editor);

    ScreenManager screen_manager(screen_manager_queue);
    std::thread screen_manager_thread(&ScreenManager::display, screen_manager);

    for (auto& prod : producers) {
        prod.join();
    }
    dispatcher_thread.join();
    sports_editor_thread.join();
    news_editor_thread.join();
    weather_editor_thread.join();
    screen_manager_thread.join();

    for (auto queue : producer_queues) {
        delete queue;
    }

    return 0;
}
