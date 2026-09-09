# 🚇 Pune Metro Route Planner

This is a C++ console application that provides a route planning service for a simulated Pune Metro network. The system uses a graph-based algorithm to find the optimal path between two stations.

# ✨ Features

__Optimal Route Calculation:__  Finds the most time-efficient route between any two stations.

__Alternative Route Suggestions:__ Suggests a secondary route that may have fewer interchanges.

__Network Data:__ Displays detailed statistics, including the number of stations per line and all interchange points.

__Interactive Interface:__ Provides a menu-driven console interface for easy navigation and use.

__Station Search:__ Allows users to find stations using partial or misspelled names.

# 🛠️ Technical Details
The application models the metro network as a graph where stations are nodes and the tracks connecting them are edges.

The core of the pathfinding is a modified Dijkstra's algorithm. The algorithm calculates a "cost" for each path, which is a combination of the travel time and a penalty applied for each line change. This approach ensures the most efficient route is found, balancing speed with the inconvenience of transfers.

# 🗺️ The Metro Network
The simulated network includes three lines based on the Pune Metro:

🟣 __Purple Line:__ PCMC Bhavan to Swargate

🔵 __Aqua Line:__ Vanaz to Ramwadi

🔴 __Red Line:__ Megapolis Circle to Civil Court

The network includes key interchange stations like Civil Court and Shivaji Nagar to facilitate travel between lines.
