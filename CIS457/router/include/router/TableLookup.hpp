#ifndef ROUTER_TABLE_LOOKUP_HPP
#define ROUTER_TABLE_LOOKUP_HPP

#include <string>
#include <unordered_map>

namespace router {
  class TableLookup {
  public:
    explicit TableLookup(const std::string&);
    std::string get_route(const std::string);
		std::string get_hop_device(const std::string);
    std::unordered_map<std::string, std::string> prefix_interface_table;
    std::unordered_map<std::string, std::string> hop_device_table;
  };
} // namespace router

#endif
