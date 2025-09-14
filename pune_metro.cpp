#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>
#include <algorithm>
#include <memory>
#include <functional>
#include <iomanip>
#include <sstream>

constexpr double INF = std::numeric_limits<double>::infinity();

enum class LineColor { PURPLE, AQUA, RED };

struct Edge {
    int to;
    double distance;
    double time;
    LineColor line;
    
    Edge(int to, double dist, LineColor line_color, double speed_kmh = 35.0) 
        : to(to), distance(dist), line(line_color), time((dist / speed_kmh) * 60) {}
};

struct Station {
    std::string name;
    std::unordered_set<LineColor> lines;
    bool is_interchange;
    
    Station(const std::string& n) : name(n), is_interchange(false) {}
    
    void add_line(LineColor line) {
        lines.insert(line);
        is_interchange = lines.size() > 1;
    }
};

class MetroSystem {
private:
    std::unordered_map<std::string, int> station_map;
    std::vector<std::unique_ptr<Station>> stations;
    std::vector<std::vector<Edge>> adjacency_list;
    
    constexpr static double INTERCHANGE_PENALTY = 4.0;
    constexpr static double BASE_SPEED = 35.0;
    
    int add_station(const std::string& name) {
        auto it = station_map.find(name);
        if (it != station_map.end()) return it->second;
        
        int idx = stations.size();
        station_map[name] = idx;
        stations.push_back(std::make_unique<Station>(name));
        adjacency_list.resize(idx + 1);
        return idx;
    }
    
    void connect_stations(const std::string& from, const std::string& to, 
                         double distance, LineColor line) {
        int from_idx = add_station(from);
        int to_idx = add_station(to);
        
        stations[from_idx]->add_line(line);
        stations[to_idx]->add_line(line);
        
        adjacency_list[from_idx].emplace_back(to_idx, distance, line);
        adjacency_list[to_idx].emplace_back(from_idx, distance, line);
    }
    
    std::string get_line_name(LineColor line) const {
        switch(line) {
            case LineColor::PURPLE: return "Purple Line";
            case LineColor::AQUA: return "Aqua Line";
            case LineColor::RED: return "Red Line";
        }
        return "Unknown Line";
    }
    
    std::string get_line_emoji(LineColor line) const {
        switch(line) {
            case LineColor::PURPLE: return "🟣";
            case LineColor::AQUA: return "🔵";
            case LineColor::RED: return "🔴";
        }
        return "⚪";
    }

public:
    MetroSystem() { build_network(); }
    
    void build_network() {
        const auto purple = LineColor::PURPLE;
        const auto aqua = LineColor::AQUA;
        const auto red = LineColor::RED;
        
        connect_stations("PCMC Bhavan", "Sant Tukaram Nagar", 3.3, purple);
        connect_stations("Sant Tukaram Nagar", "Nashik Phata", 2.0, purple);
        connect_stations("Nashik Phata", "Kasarwadi", 1.8, purple);
        connect_stations("Kasarwadi", "Phugewadi", 1.2, purple);
        connect_stations("Phugewadi", "Dapodi", 1.5, purple);
        connect_stations("Dapodi", "Bopodi", 1.4, purple);
        connect_stations("Bopodi", "Khadki", 1.3, purple);
        connect_stations("Khadki", "Range Hills", 1.2, purple);
        connect_stations("Range Hills", "Shivaji Nagar", 2.8, purple);
        connect_stations("Shivaji Nagar", "Civil Court", 1.4, purple);
        connect_stations("Civil Court", "Kasba Peth", 1.2, purple);
        connect_stations("Kasba Peth", "Mandai", 1.0, purple);
        connect_stations("Mandai", "Swargate", 1.5, purple);
        
        connect_stations("Vanaz", "Anand Nagar", 1.0, aqua);
        connect_stations("Anand Nagar", "Ideal Colony", 1.1, aqua);
        connect_stations("Ideal Colony", "Nal Stop", 1.2, aqua);
        connect_stations("Nal Stop", "Garware College", 1.4, aqua);
        connect_stations("Garware College", "Deccan Gymkhana", 1.0, aqua);
        connect_stations("Deccan Gymkhana", "Chhatrapati Sambhaji Udyan", 0.9, aqua);
        connect_stations("Chhatrapati Sambhaji Udyan", "PMC Bhavan", 0.8, aqua);
        connect_stations("PMC Bhavan", "Civil Court", 1.1, aqua);
        connect_stations("Civil Court", "Mangalwar Peth", 1.0, aqua);
        connect_stations("Mangalwar Peth", "Pune Railway Station", 1.2, aqua);
        connect_stations("Pune Railway Station", "Ruby Hall Clinic", 1.0, aqua);
        connect_stations("Ruby Hall Clinic", "Bund Garden", 1.1, aqua);
        connect_stations("Bund Garden", "Yerawada", 1.0, aqua);
        connect_stations("Yerawada", "Kalyani Nagar", 0.9, aqua);
        connect_stations("Kalyani Nagar", "Ramwadi", 1.2, aqua);
        
        connect_stations("Megapolis Circle", "Quadron", 1.5, red);
        connect_stations("Quadron", "Infosys Phase II", 1.8, red);
        connect_stations("Infosys Phase II", "Dollar", 1.3, red);
        connect_stations("Dollar", "RBI", 1.2, red);
        connect_stations("RBI", "Rajiv Gandhi IT Park", 1.4, red);
        connect_stations("Rajiv Gandhi IT Park", "EON IT Park", 1.1, red);
        connect_stations("EON IT Park", "Kamnagar", 1.6, red);
        connect_stations("Kamnagar", "Laxmi Nagar", 1.3, red);
        connect_stations("Laxmi Nagar", "Balewadi Phata", 1.2, red);
        connect_stations("Balewadi Phata", "Baner Gaon", 1.4, red);
        connect_stations("Baner Gaon", "Baner", 1.0, red);
        connect_stations("Baner", "Indian Agricultural Research Institute", 1.5, red);
        connect_stations("Indian Agricultural Research Institute", "Sakal Nagar", 1.3, red);
        connect_stations("Sakal Nagar", "Savitribai Phule Pune University", 1.1, red);
        connect_stations("Savitribai Phule Pune University", "Reserve Bank of India", 1.2, red);
        connect_stations("Reserve Bank of India", "Agriculture College", 1.4, red);
        connect_stations("Agriculture College", "Shivaji Nagar", 1.6, red);
        connect_stations("Shivaji Nagar", "Civil Court", 1.4, red);
    }
    
    struct PathResult {
        std::vector<int> path;
        std::vector<LineColor> path_lines;
        double total_distance;
        double total_time;
        int interchanges;
        bool found;
        std::vector<std::pair<std::string, LineColor>> detailed_route;
        
        PathResult() : total_distance(0), total_time(0), interchanges(0), found(false) {}
    };
    
    PathResult find_optimal_path(const std::string& start, const std::string& end, 
                                bool minimize_time = true) {
        PathResult result;
        
        auto start_it = station_map.find(start);
        auto end_it = station_map.find(end);
        
        if (start_it == station_map.end() || end_it == station_map.end()) {
            return result;
        }
        
        int start_idx = start_it->second;
        int end_idx = end_it->second;
        
        if (start_idx == end_idx) {
            result.path = {start_idx};
            result.path_lines = {};
            result.found = true;
            return result;
        }
        
        using State = std::tuple<double, int, LineColor>;
        std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
        
        std::vector<std::vector<double>> cost(stations.size(), 
            std::vector<double>(3, INF));
        std::vector<std::vector<int>> parent(stations.size(), 
            std::vector<int>(3, -1));
        std::vector<std::vector<LineColor>> parent_line(stations.size(), 
            std::vector<LineColor>(3));
        
        for (const auto& edge : adjacency_list[start_idx]) {
            int line_idx = static_cast<int>(edge.line);
            double edge_cost = minimize_time ? edge.time : edge.distance;
            cost[start_idx][line_idx] = 0.0;
            pq.emplace(edge_cost, edge.to, edge.line);
            cost[edge.to][line_idx] = edge_cost;
            parent[edge.to][line_idx] = start_idx;
            parent_line[edge.to][line_idx] = edge.line;
        }
        
        while (!pq.empty()) {
            auto [current_cost, current_idx, current_line] = pq.top();
            pq.pop();
            
            int line_idx = static_cast<int>(current_line);
            if (current_cost > cost[current_idx][line_idx]) continue;
            
            for (const auto& edge : adjacency_list[current_idx]) {
                double edge_cost = minimize_time ? edge.time : edge.distance;
                double interchange_cost = 0.0;
                
                if (current_line != edge.line) {
                    interchange_cost = minimize_time ? INTERCHANGE_PENALTY : 0.5;
                }
                
                double new_cost = current_cost + edge_cost + interchange_cost;
                int next_line_idx = static_cast<int>(edge.line);
                
                if (new_cost < cost[edge.to][next_line_idx]) {
                    cost[edge.to][next_line_idx] = new_cost;
                    parent[edge.to][next_line_idx] = current_idx;
                    parent_line[edge.to][next_line_idx] = current_line;
                    pq.emplace(new_cost, edge.to, edge.line);
                }
            }
        }
        
        double min_cost = INF;
        LineColor best_line;
        for (int i = 0; i < 3; ++i) {
            if (cost[end_idx][i] < min_cost) {
                min_cost = cost[end_idx][i];
                best_line = static_cast<LineColor>(i);
            }
        }
        
        if (min_cost == INF) return result;
        
        std::vector<int> path;
        std::vector<LineColor> path_lines;
        
        int current = end_idx;
        LineColor current_line = best_line;
        
        while (current != start_idx) {
            path.push_back(current);
            path_lines.push_back(current_line);
            
            int line_idx = static_cast<int>(current_line);
            int next = parent[current][line_idx];
            current_line = parent_line[current][line_idx];
            current = next;
        }
        
        path.push_back(start_idx);
        std::reverse(path.begin(), path.end());
        std::reverse(path_lines.begin(), path_lines.end());
        
        result.path = path;
        result.path_lines = path_lines;
        result.found = true;
        
        double total_dist = 0, total_time = 0;
        int interchanges = 0;
        
        for (size_t i = 0; i < path.size() - 1; ++i) {
            const auto& edges = adjacency_list[path[i]];
            auto edge_it = std::find_if(edges.begin(), edges.end(),
                [&](const Edge& e) { return e.to == path[i + 1]; });
            
            if (edge_it != edges.end()) {
                total_dist += edge_it->distance;
                total_time += edge_it->time;
                
                if (i > 0 && path_lines[i-1] != edge_it->line) {
                    interchanges++;
                }
            }
        }
        
        result.total_distance = total_dist;
        result.total_time = total_time + (interchanges * INTERCHANGE_PENALTY);
        result.interchanges = interchanges;
        
        return result;
    }
    
    void display_path(const PathResult& result) const {
        if (!result.found) {
            std::cout << "❌ No route found between specified stations.\n";
            return;
        }
        
        std::cout << "\n" << std::string(70, '=') << "\n";
        std::cout << "🚇 OPTIMAL ROUTE FOUND\n";
        std::cout << std::string(70, '=') << "\n\n";
        
        LineColor current_line;
        bool first_station = true;
        
        for (size_t i = 0; i < result.path.size(); ++i) {
            const auto& station = stations[result.path[i]];
            
            if (i < result.path.size() - 1) {
                const auto& edges = adjacency_list[result.path[i]];
                auto edge_it = std::find_if(edges.begin(), edges.end(),
                    [&](const Edge& e) { return e.to == result.path[i + 1]; });
                
                if (edge_it != edges.end()) {
                    if (first_station || current_line != edge_it->line) {
                        if (!first_station) {
                            std::cout << "\n   🔄 INTERCHANGE → " 
                                      << get_line_emoji(edge_it->line) << " " 
                                      << get_line_name(edge_it->line) << "\n\n";
                        } else {
                            std::cout << "🚀 Board " << get_line_emoji(edge_it->line) 
                                      << " " << get_line_name(edge_it->line) << "\n\n";
                        }
                        current_line = edge_it->line;
                        first_station = false;
                    }
                }
            }
            
            std::cout << get_line_emoji(current_line) << " " 
                      << std::setw(2) << (i + 1) << ". " << station->name;
            
            if (station->is_interchange) {
                std::cout << " 🔄";
            }
            std::cout << "\n";
            
            if (i < result.path.size() - 1) {
                std::cout << "     |\n";
            }
        }
        
        std::cout << "\n" << std::string(70, '=') << "\n";
        std::cout << "📊 JOURNEY SUMMARY\n";
        std::cout << std::string(70, '=') << "\n";
        std::cout << "🗺️  Total Distance: " << std::fixed << std::setprecision(1) 
                  << result.total_distance << " km\n";
        std::cout << "⏱️  Estimated Time: " << std::fixed << std::setprecision(0) 
                  << result.total_time << " minutes\n";
        std::cout << "🚉 Total Stations: " << result.path.size() << "\n";
        std::cout << "🔄 Interchanges: " << result.interchanges << "\n";
        
        if (result.interchanges > 0) {
            std::cout << "💡 Tip: Allow extra 2-3 minutes for each interchange\n";
        }
        
        std::cout << std::string(70, '=') << "\n";
    }
    
    void display_network_stats() const {
        std::cout << "\n🚇 PUNE METRO NETWORK STATISTICS\n";
        std::cout << std::string(50, '=') << "\n";
        std::cout << "Total Stations: " << stations.size() << "\n";
        
        int purple_count = 0, aqua_count = 0, red_count = 0, interchange_count = 0;
        
        for (const auto& station : stations) {
            if (station->lines.count(LineColor::PURPLE)) purple_count++;
            if (station->lines.count(LineColor::AQUA)) aqua_count++;
            if (station->lines.count(LineColor::RED)) red_count++;
            if (station->is_interchange) interchange_count++;
        }
        
        std::cout << "🟣 Purple Line: " << purple_count << " stations\n";
        std::cout << "🔵 Aqua Line: " << aqua_count << " stations\n";
        std::cout << "🔴 Red Line: " << red_count << " stations\n";
        std::cout << "🔄 Interchange Stations: " << interchange_count << "\n";
        std::cout << std::string(50, '=') << "\n\n";
    }
    
    std::vector<std::string> get_all_stations() const {
        std::vector<std::string> stations_list;
        stations_list.reserve(stations.size());
        
        for (const auto& [name, idx] : station_map) {
            stations_list.push_back(name);
        }
        
        std::sort(stations_list.begin(), stations_list.end());
        return stations_list;
    }
    
    std::vector<std::string> get_stations_by_line(LineColor line) const {
        std::vector<std::string> line_stations;
        
        for (const auto& station : stations) {
            if (station->lines.count(line)) {
                line_stations.push_back(station->name);
            }
        }
        
        std::sort(line_stations.begin(), line_stations.end());
        return line_stations;
    }
    
    std::vector<std::string> search_stations(const std::string& query) const {
        std::vector<std::string> matches;
        std::string lower_query = query;
        std::transform(lower_query.begin(), lower_query.end(), 
                      lower_query.begin(), ::tolower);
        
        for (const auto& [name, idx] : station_map) {
            std::string lower_name = name;
            std::transform(lower_name.begin(), lower_name.end(), 
                          lower_name.begin(), ::tolower);
            
            if (lower_name.find(lower_query) != std::string::npos) {
                matches.push_back(name);
            }
        }
        
        std::sort(matches.begin(), matches.end());
        return matches;
    }
    
    PathResult find_alternative_route(const std::string& start, const std::string& end) {
        auto primary = find_optimal_path(start, end, true);
        if (!primary.found || primary.interchanges == 0) return primary;
        
        auto distance_optimized = find_optimal_path(start, end, false);
        
        if (distance_optimized.found && 
            distance_optimized.interchanges < primary.interchanges) {
            return distance_optimized;
        }
        
        return primary;
    }
};

class UserInterface {
private:
    MetroSystem& metro;
    
    void display_stations_by_line() const {
        std::cout << "\n📍 STATIONS BY LINE\n";
        std::cout << std::string(60, '=') << "\n";
        
        auto purple_stations = metro.get_stations_by_line(LineColor::PURPLE);
        std::cout << "🟣 Purple Line (" << purple_stations.size() << " stations):\n";
        for (size_t i = 0; i < purple_stations.size(); ++i) {
            std::cout << "   " << std::setw(2) << (i + 1) << ". " << purple_stations[i] << "\n";
        }
        
        auto aqua_stations = metro.get_stations_by_line(LineColor::AQUA);
        std::cout << "\n🔵 Aqua Line (" << aqua_stations.size() << " stations):\n";
        for (size_t i = 0; i < aqua_stations.size(); ++i) {
            std::cout << "   " << std::setw(2) << (i + 1) << ". " << aqua_stations[i] << "\n";
        }
        
        auto red_stations = metro.get_stations_by_line(LineColor::RED);
        std::cout << "\n🔴 Red Line (" << red_stations.size() << " stations):\n";
        for (size_t i = 0; i < red_stations.size(); ++i) {
            std::cout << "   " << std::setw(2) << (i + 1) << ". " << red_stations[i] << "\n";
        }
        std::cout << "\n";
    }
    
    void display_all_stations() const {
        auto stations = metro.get_all_stations();
        std::cout << "\n📍 ALL STATIONS (" << stations.size() << " total):\n";
        std::cout << std::string(50, '-') << "\n";
        
        for (size_t i = 0; i < stations.size(); ++i) {
            std::cout << std::setw(2) << (i + 1) << ". " << stations[i] << "\n";
        }
        std::cout << "\n";
    }
    
    std::string get_station_input(const std::string& prompt) {
        std::string input;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);
            
            if (input.empty()) {
                std::cout << "❌ Please enter a station name.\n";
                continue;
            }
            
            auto matches = metro.search_stations(input);
            if (matches.empty()) {
                std::cout << "❌ No stations found matching '" << input << "'\n";
                std::cout << "💡 Type 'list' to see all stations or try a partial name.\n";
                if (input == "list") {
                    display_all_stations();
                }
                continue;
            }
            
            if (matches.size() == 1) {
                return matches[0];
            }
            
            if (std::find(matches.begin(), matches.end(), input) != matches.end()) {
                return input;
            }
            
            std::cout << "🔍 Multiple matches found:\n";
            for (size_t i = 0; i < matches.size(); ++i) {
                std::cout << "   " << (i + 1) << ". " << matches[i] << "\n";
            }
            
            int choice;
            std::cout << "Select station (1-" << matches.size() << ") or 0 to search again: ";
            if (std::cin >> choice) {
                std::cin.ignore();
                if (choice == 0) continue;
                if (choice >= 1 && choice <= static_cast<int>(matches.size())) {
                    return matches[choice - 1];
                }
            }
            
            std::cin.clear();
            std::cin.ignore();
            std::cout << "❌ Invalid selection.\n";
        }
    }

public:
    UserInterface(MetroSystem& ms) : metro(ms) {}
    
    void run() {
        std::cout << "🚇 PUNE METRO - INTELLIGENT ROUTE PLANNER\n";
        std::cout << std::string(70, '=') << "\n";
        std::cout << "Welcome to the most advanced Pune Metro route planning system!\n\n";
        
        while (true) {
            std::cout << "🎯 MAIN MENU:\n";
            std::cout << "1. 🗺️  Find Optimal Route\n";
            std::cout << "2. 🔄 Find Alternative Route\n";
            std::cout << "3. 📋 View All Stations\n";
            std::cout << "4. 🚇 View Stations by Line\n";
            std::cout << "5. 📊 Network Statistics\n";
            std::cout << "6. ❌ Exit\n\n";
            std::cout << "Choose option (1-6): ";
            
            int choice;
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "❌ Invalid input. Please try again.\n\n";
                continue;
            }
            std::cin.ignore();
            
            switch (choice) {
                case 1: {
                    std::cout << "\n🗺️  ROUTE PLANNING\n";
                    std::cout << std::string(30, '-') << "\n";
                    
                    std::string start = get_station_input("🚀 From Station: ");
                    std::string end = get_station_input("🎯 To Station: ");
                    
                    if (start == end) {
                        std::cout << "😊 You're already at your destination!\n\n";
                        break;
                    }
                    
                    auto result = metro.find_optimal_path(start, end, true);
                    metro.display_path(result);
                    
                    std::cout << "\nPress Enter to continue...";
                    std::cin.get();
                    break;
                }
                case 2: {
                    std::cout << "\n🔄 ALTERNATIVE ROUTE PLANNING\n";
                    std::cout << std::string(35, '-') << "\n";
                    
                    std::string start = get_station_input("🚀 From Station: ");
                    std::string end = get_station_input("🎯 To Station: ");
                    
                    auto result = metro.find_alternative_route(start, end);
                    std::cout << "\n🔄 Finding best alternative route...\n";
                    metro.display_path(result);
                    
                    std::cout << "\nPress Enter to continue...";
                    std::cin.get();
                    break;
                }
                case 3:
                    display_all_stations();
                    std::cout << "Press Enter to continue...";
                    std::cin.get();
                    break;
                case 4:
                    display_stations_by_line();
                    std::cout << "Press Enter to continue...";
                    std::cin.get();
                    break;
                case 5:
                    metro.display_network_stats();
                    std::cout << "Press Enter to continue...";
                    std::cin.get();
                    break;
                case 6:
                    std::cout << "🙏 Thank you for using Pune Metro Route Planner!\n";
                    std::cout << "🚇 Safe travels on the metro! 🚇\n";
                    return;
                default:
                    std::cout << "❌ Invalid option. Please choose 1-6.\n\n";
            }
        }
    }
};

int main() {
    try {
        MetroSystem pune_metro;
        UserInterface ui(pune_metro);
        ui.run();
    } catch (const std::exception& e) {
        std::cerr << "💥 Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}