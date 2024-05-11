#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex expectation;

void railwayStation(int& time, int& inNumberTrain)
{ 
    std::this_thread::sleep_for(std::chrono::seconds(time));
    int current = 0;
    std::string command;
    while (command != "depart") {        
        
        if (expectation.try_lock())
        {
            std::cout << "Train number " << inNumberTrain << " arrived at the station." << std::endl;            

            do {
                std::cout << "Enter the \"depart\"command for the train to depart:\n";
                std::cin >> command;

            } while (command != "depart");

            std::cout << "Train number " << inNumberTrain << " left for the station." << std::endl;
            expectation.unlock();
        }
        else
        {
            if (current == 0) 
            {
                std::cout << "Train number " << inNumberTrain << " is waiting for the station to become free. " << std::endl;
            }            
            std::this_thread::sleep_for(std::chrono::seconds(1));           
        }
        ++current;
    }   
}

int main()
{
    int travelTime[3];
    int numberTrain[3];

    for (int i = 0; i < 3; ++i)
    {
        std::cout << "Enter time for train " << i + 1 << " :";
        //std::cin >> travelTime[i];
        travelTime[i] = 2;
        numberTrain[i] = i + 1;
    }
    std::cout << std::endl;
    std::thread train1(railwayStation, std::ref(travelTime[0]), std::ref(numberTrain[0]));
    std::thread train2(railwayStation, std::ref(travelTime[1]), std::ref(numberTrain[1]));
    std::thread train3(railwayStation, std::ref(travelTime[2]), std::ref(numberTrain[2]));

    train1.join();    
    train2.join();
    train3.join();
   
    return 0;
}