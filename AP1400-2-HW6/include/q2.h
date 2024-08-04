#ifndef Q2_H
#define Q2_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
namespace q2 {

    struct Patient
    {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };
    std::vector<Patient> read_file(const std::string & filename) {
        std::vector<Patient> result;
        std::ifstream ifs(filename);
        if (!ifs.is_open()) {
            std::cerr << "failed to open the file. " << std::endl;
        }
        std::string line;
        std::getline(ifs, line);
        std::getline(ifs, line);
        while(std::getline(ifs, line)) {
            std::istringstream iss(line);
            std::string cell;
            std::string first_name; std::string last_name;
            size_t age, smokes, area_q, alkhol;
            std::getline(iss, cell, ',');
            if (!cell.ends_with(' ')) {
                first_name = cell + ' ';
            } else {first_name = cell;}
            std::getline(iss, cell, ',');
            last_name = cell;
            std::getline(iss, cell, ',');
            age = std::stoi(cell);
            std::getline(iss, cell, ',');
            smokes = std::stoi(cell);
            std::getline(iss, cell, ',');
            area_q = std::stoi(cell);
            std::getline(iss, cell, ',');
            alkhol = std::stoi(cell);
            Patient patient{first_name+last_name, age, smokes, area_q, alkhol};
            result.push_back(patient);
        }
        return result;
    }

    void sort(std::vector<Patient>& patients) {
        auto greater = [](Patient p1, Patient p2) {
            return (p1.age*3 + p1.smokes*5 + p1.area_q*2 + p1.alkhol*4) > (p2.age*3 + p2.smokes*5 + p2.area_q*2 + p2.alkhol*4);
        };

        std::sort(patients.begin(), patients.end(), greater);
    }
}



#endif //Q2_H