#pragma once

#include "structure.h"

#include <vector>
#include <string>
#include <stdint.h>
#include <map>
#include <memory>
#include <filesystem>
#include <type_traits>
#include <fstream>
#include <shared_mutex>
// #include <nlohmann/json.hpp>

using json = nlohmann::json;

// ...

using MapID = uint64_t;
using FloorID = int8_t;
using MapName = std::string;
using CreateTime = uint64_t;
using MapIDList = std::vector<uint64_t>;

enum class MapType : uint8_t
{
    UNKNOWN_0,
    SELF_BUILT_MAP_1,
    OFFICIAL_MAP_2,
    PARK2PARK_MAP_3,
    SHARED_MAP_4
};


class MapBaseInfo
{
private:
    MapID id_{0};
    MapName name_{""};
    CreateTime time_{0};
    MapType type_{MapType::UNKNOWN_0};
    double distance_{0.0};
    uint64_t size_{0};
    std::vector<Point3D<double>> path_;
    std::vector<FloorID> floor_ids_;
};

class MapSemanticInfo
{

};

class MapInfo
{
private:
    MapBaseInfo base_info_;
    std::map<FloorID, MapSemanticInfo> semantic_info_;
};

/** 
*这里有一个问题，就是地图管理模块是是要作为一个独立模块
*还是要作为AVP的一个子模块，理论上，这里的地图包括：
*用户自建图、官方地图、众包地图以及车位到车位地图

*我现在想的是后端应该有一个专门与各种地图打交道的MapManager模块
*主要功能时给其他子模块提供地图管理相关接口
*然后每个APP内部应该还有一个地图管理子模块，通过调用相关接口来完成相关地图操作
**/

class MapManager
{
public:
    using MapInfoSPtr = std::shared_ptr<MapInfo>;
private:
    std::string base_path_;
    std::string self_built_map_path_;
    std::string official_map_path_;
    std::string park2park_map_path_;
    std::string shared_map_path_;
public:
    const MapInfoSPtr& LoadSelfBuiltMapList() const
    {
        for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(std::filesystem::path(base_path_ + self_built_map_path_))) 
        {
            if (entry.is_regular_file() && entry.path().extension() == ".json") 
            {
                std::ifstream f(entry.path().c_str());
                // json data = json::parse(f);
            }
        }
        return std::make_shared<MapInfo>();
    }
    const MapInfoSPtr& LoadOfficialMapList() const
    {
        return std::make_shared<MapInfo>();
    }
    const MapInfoSPtr& LoadPark2ParkMapList() const
    {
        return std::make_shared<MapInfo>();
    }
    const MapInfoSPtr& LoadSharedMapList() const
    {
        return std::make_shared<MapInfo>();
    }
public:
    bool DeleteSelfBuiltMap(MapID id)
    {
        return true;
    }
    bool DeleteOfficialMap(MapID id)
    {
        return true;
    }
    bool DeletePark2ParkMap(MapID id)
    {
        return true;
    }
    bool DeleteSharedMap(MapID id)
    {
        return true;
    }
    bool DeleteMap(MapType type, MapID id)
    {
        switch (type)
        {
            case MapType::SELF_BUILT_MAP_1:
            {
                return DeleteSelfBuiltMap(id);
            }
            case MapType::OFFICIAL_MAP_2:
            {
                return DeleteOfficialMap(id);
            }
            case MapType::PARK2PARK_MAP_3:
            {
                return DeletePark2ParkMap(id);
            }
            case MapType::SHARED_MAP_4:
            {
                return DeleteSharedMap(id);
            }
            default:
            {
                return false;
            }
        }
    }
public:
    template <typename T, typename = typename std::enable_if_t<std::is_same_v<std::decay_t<T>, std::string>>>
    MapManager(T&& base_path, T&& self_built_map_path, T&& official_map_path, T&& park2park_map_path, T&& shared_map_path) :
    base_path_(std::forward<T>(base_path)),
    self_built_map_path_(std::forward<T>(self_built_map_path)),
    official_map_path_(std::forward<T>(official_map_path)),
    park2park_map_path_(std::forward<T>(park2park_map_path)),
    shared_map_path_(std::forward<T>(shared_map_path))
    {
        std::filesystem::path base_directory = base_path_;
        std::filesystem::path self_built_map_directory = base_path_ + self_built_map_path_;
        std::filesystem::path official_map_directory = base_path_ + official_map_path_;
        std::filesystem::path park2park_map_directory = base_path_ + park2park_map_path_;
        std::filesystem::path shared_map_directory = base_path_ + shared_map_path_;

        if (std::filesystem::exists(base_directory) && std::filesystem::is_directory(base_directory))
        {
            if (std::filesystem::exists(self_built_map_directory) && std::filesystem::is_directory(self_built_map_directory))
            {
                std::cout << "self-built map path : " << self_built_map_directory.c_str() << std::endl;
            }
            else
            {
                std::filesystem::create_directory(self_built_map_directory);
            }
            if (std::filesystem::exists(official_map_directory) && std::filesystem::is_directory(official_map_directory))
            {
                std::cout << "official map path : " << official_map_directory.c_str() << std::endl;
            }
            else
            {
                std::filesystem::create_directory(official_map_directory);
            }
            if (std::filesystem::exists(park2park_map_directory) && std::filesystem::is_directory(park2park_map_directory))
            {
                std::cout << "park2park map path : " << park2park_map_directory.c_str() << std::endl;
            }
            else
            {
                std::filesystem::create_directory(park2park_map_directory);
            }
            if (std::filesystem::exists(shared_map_directory) && std::filesystem::is_directory(shared_map_directory))
            {
                std::cout << "shared map path : " << shared_map_directory.c_str() << std::endl;
            }
            else
            {
                std::filesystem::create_directory(shared_map_directory);
            }
        }
        else
        {
            std::filesystem::create_directory(base_directory);
        }
    }
};

class AvpMapManager
{
public:
    static const uint8_t MAX_SIZE = 20;
private:
    std::string storage_path_;
    std::vector<MapInfo> map_info_list_;
    std::shared_mutex rw_mtx_;
public:
    AvpMapManager(const std::string& path) : storage_path_(path)
    {
        // 这里需要判断该地图存储路径
    }
public:
    bool LoadMapList()
    {
        std::shared_lock<std::shared_mutex> lck(rw_mtx_);
        return true;
    }
    bool AddMap(MapID id);  
    bool DeleteMap(MapID id);
    bool DeleteMap(MapIDList ids);
    bool RenameMap(MapID id);
};