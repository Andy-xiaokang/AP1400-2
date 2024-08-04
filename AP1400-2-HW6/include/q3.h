#ifndef Q3_H
#define Q3_H

#include <string>
#include <queue>
#include <fstream>
#include <regex>
#include <sstream>

namespace q3 {
    using std::string; using std::priority_queue;
    using std::endl;

    struct Flight
    {
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
    };

    auto compare = [] (const Flight & f1, const Flight & f2) {
        return f1.duration + f1.connection_times + f1.price*3 > f2.duration + f2.connection_times + f2.price*3;
    };

    size_t parse_time(const string& time_str) {
        std::regex pattern("(\\d+)h(\\d+m)?");
        std::smatch match;
        size_t total_minutes = 0;
        if (std::regex_match(time_str, match, pattern)) {
            int hours = std::stoi(match[1]);
            int minutes = match[2].matched ? std::stoi(match[2]) : 0;
            total_minutes =  hours * 60 + minutes;
        }
        return total_minutes;
    }

    size_t parse_connection_time(const string& times_str) {
        std::istringstream iss(times_str);
        string time;
        size_t total = 0;
        while (std::getline(iss, time, ',')) {
            total += parse_time(time);
        }
        return total;
    }

    priority_queue<Flight, std::vector<Flight>, decltype(compare)> gather_flights(const string& filename) {
        priority_queue<Flight, std::vector<Flight>, decltype(compare)> flightPQ;
        std::ifstream ifs(filename);
        if (!ifs.is_open()) {
            std::cerr << "can't open the file" << endl;
        }
        std::string line;
        std::regex pattern("flight_number:(\\w+) - duration:(\\d+h\\d*m?) - connections:(\\d+) - connection_times:([\\dhm,]*) - price:(\\d+)");
        while (std::getline(ifs, line)) {
            string flight_number;
            size_t duration = 0;
            size_t connections = 0;
            size_t connection_times = 0;
            size_t price = 0;
            std::smatch match;
            if (std::regex_search(line, match, pattern)) {
                flight_number = match[1];
                duration = parse_time(match[2]);
                connections = std::stoul(match[3]);
                std::cout << match[4] << endl;
                connection_times = parse_connection_time(match[4]);
                price = std::stoul(match[5]);
            }
            flightPQ.push({flight_number, duration, connections, connection_times, price});
        }
        return flightPQ;
    }
}
#endif //Q3_H