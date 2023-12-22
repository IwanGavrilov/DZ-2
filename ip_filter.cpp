#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

/*
функции компаратор
compare_descending - сортирует по убыванию
compare_ascending - сортирует по возрастанию
*/
int compare_descending (std::vector<std::string> v1, std::vector<std::string> v2) {
    int out_value = 0;
    if (std::stoi(v1.at(0)) == std::stoi(v2.at(0))) {
        if (std::stoi(v1.at(1)) == std::stoi(v2.at(1))) {
            if (std::stoi(v1.at(2)) == std::stoi(v2.at(2))) {
                if (std::stoi(v1.at(3)) == std::stoi(v2.at(3))) out_value = 0;
                if (std::stoi(v1.at(3)) > std::stoi(v2.at(3))) out_value = 1;
            }
            if (std::stoi(v1.at(2)) > std::stoi(v2.at(2))) out_value = 1;
        }
        if (std::stoi(v1.at(1)) > std::stoi(v2.at(1))) out_value = 1;
        //out_value = 0;
    }

    if (std::stoi(v1.at(0)) > std::stoi(v2.at(0))) out_value = 1;
    return out_value;
}
int compare_ascending (std::vector<std::string> v1, std::vector<std::string> v2) {
    int out_value = 0;
    if (std::stoi(v1.at(0)) == std::stoi(v2.at(0))) {
        if (std::stoi(v1.at(1)) == std::stoi(v2.at(1))) {
            if (std::stoi(v1.at(2)) == std::stoi(v2.at(2))) {
                if (std::stoi(v1.at(3)) == std::stoi(v2.at(3))) out_value = 0;
                if (std::stoi(v1.at(3)) < std::stoi(v2.at(3))) out_value = 1;
            }
            if (std::stoi(v1.at(2)) < std::stoi(v2.at(2))) out_value = 1;
        }
        if (std::stoi(v1.at(1)) < std::stoi(v2.at(1))) out_value = 1;
        //out_value = 0;
    }

    if (std::stoi(v1.at(0)) < std::stoi(v2.at(0))) out_value = 1;
    return out_value;
}
/*
функция сортировки
ip_pool - список IP-адресов
order - порядок сортировки (1 - по возрастанию, 2 - по убыванию)
*/
std::vector<std::vector<std::string>> sort_ip_pool(const std::vector<std::vector<std::string>> &ip_pool, int order){
    std::vector<std::vector<std::string>> out_ip_pool = ip_pool;
    try
    {
        switch (order)
        {
        case 1:
            // сортируем по возрастанию
            std::sort(out_ip_pool.begin(), out_ip_pool.end(), compare_ascending);
            break;
        case 2:
            // сортируем по убыванию
            std::sort(out_ip_pool.begin(), out_ip_pool.end(), compare_descending);
            break;
        default:
            // если задан неверный флаг сортировки (order <> 1 или 2), выводим данные без изменения
            break;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return out_ip_pool;
}

/*
печать IP-адреса
ip_pool - ссылка на пул IP-адресов
*/
void print_ip(const std::vector<std::vector<std::string>> & ip_pool){
    for (auto iter_ip = ip_pool.cbegin(); iter_ip != ip_pool.cend(); ++iter_ip) {
        for (auto part = iter_ip->cbegin(); part != iter_ip->cend(); ++part){
            if (part != iter_ip->cbegin()){
                std::cout << ".";
            }
            std::cout << *part;
        }
        std::cout << std::endl;
    }
}

/* 
фильтрация IP адресов
ip_pool - список IP-адресов
nOktet - первый октет IP-адреса
*/
std::vector<std::vector<std::string>> filter(std::vector<std::vector<std::string> > ip_pool, int nOktet) {
    std::vector<std::vector<std::string>> out_ip_pool;
    if (nOktet < 0) {
        return out_ip_pool;
    }
    for (auto iter_ip = ip_pool.cbegin(); iter_ip != ip_pool.cend(); ++iter_ip){
        if (std::stoi(iter_ip->at(0)) == nOktet) {
            out_ip_pool.push_back(*iter_ip);
        };
    }
    return out_ip_pool;
}

/* 
фильтрация IP адресов
ip_pool - список IP-адресов
nFirstOktet - первый октет IP-адреса
nSecondOktet - второй октет IP-адреса
*/
std::vector<std::vector<std::string>> filter(std::vector<std::vector<std::string> > ip_pool, int nFirstOktet, int nSecondOktet) {
    std::vector<std::vector<std::string>> out_ip_pool;
    if (nFirstOktet < 0 || nSecondOktet < 0) {
        return out_ip_pool;;
    }
    for (auto iter_ip = ip_pool.cbegin(); iter_ip != ip_pool.cend(); ++iter_ip){
        if (std::stoi(iter_ip->at(0)) == nFirstOktet && std::stoi(iter_ip->at(1)) == nSecondOktet) {
            out_ip_pool.push_back(*iter_ip);
        };
    }
    return out_ip_pool;
}

/* 
фильтрация IP адресов
ip_pool - список IP-адресов
nOktet - любой октет IP-адреса
*/
std::vector<std::vector<std::string>> filterany(std::vector<std::vector<std::string> > ip_pool, int nOktet) {
    std::vector<std::vector<std::string>> out_ip_pool;
    if (nOktet < 0) {
        return out_ip_pool;
    }
    for (auto iter_ip = ip_pool.cbegin(); iter_ip != ip_pool.cend(); ++iter_ip){
        if (std::stoi(iter_ip->at(0)) == nOktet || std::stoi(iter_ip->at(1)) == nOktet || 
            std::stoi(iter_ip->at(2)) == nOktet || std::stoi(iter_ip->at(3)) == nOktet) {
            out_ip_pool.push_back(*iter_ip);
        };
    }
    return out_ip_pool;
}
//int main(int argc, char const *argv[])
int main()
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;
        std::cout << "Укажите полный путь к файлу с данными, или нажмите Enter" << std::endl;
        std::string s_file_path = "";
        std::getline(std::cin, s_file_path);
        // если задан файл с данными, то читаем его
        // если не казан, то читаем стандартный ввод. окончание ввода фраза "Ok" или "ok"
        if (s_file_path != "") {
            std::ifstream io(s_file_path);
            if (io.is_open()) {
                std::string s_line;
                // читаем файл построчно
                while(std::getline(io, s_line))
                {
                    std::vector<std::string> v = split(s_line, '\t');
                    ip_pool.push_back(split(v.at(0), '.'));
                }
                io.close();
            }
        }
        else {
            std::cout << "Введите IP-адреса или наберите Ок для отмены ввода" << std::endl;
            for(std::string line; std::getline(std::cin, line);)
            {
                if (line == "ok" || line == "Ok" || line == "OK") { break; }    // все данные введены. выходим из цикла
                std::vector<std::string> v = split(line, '\t');
                ip_pool.push_back(split(v.at(0), '.'));
            }
        }

        // список IP-адресов пустой. Нечего делать. Завершаем работу
        if (ip_pool.empty()) {
            std::cout << "Список IP-адресов пуст" << std::endl;
            return 0;
        }

        std::cout << "--------sort--------" << std::endl;
        // TODO reverse lexicographically sort
        std::vector<std::vector<std::string>> ip_pool_sort = sort_ip_pool(ip_pool, 2);
        if (!ip_pool_sort.empty()) {
            print_ip(ip_pool_sort);
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        std::cout << "--------first--------" << std::endl;
        // TODO filter by first byte and output
        std::vector<std::vector<std::string>> filtered_ip_pool;
        filtered_ip_pool = filter(ip_pool, 1);
        if (!filtered_ip_pool.empty()) {
            print_ip(filtered_ip_pool);
        }
        filtered_ip_pool.clear();
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        std::cout << "--------first and second--------" << std::endl;
        // TODO filter by first and second bytes and output
        filtered_ip_pool = filter(ip_pool, 46, 70);
        if (!filtered_ip_pool.empty()) {
            print_ip(filtered_ip_pool);
        }
        filtered_ip_pool.clear();

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        std::cout << "--------any--------" << std::endl;
        // TODO filter by any byte and output
        filtered_ip_pool = filterany(ip_pool, 46);
        if (!filtered_ip_pool.empty()) {
            print_ip(filtered_ip_pool);
        }
        filtered_ip_pool.clear();

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
