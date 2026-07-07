#pragma once

#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include <queue>
#include <atomic>
#include <type_traits>
#include <filesystem>

#include "public_param\public_param.h"
#include "function_param\function_param.h"
#include "algorithm_param\algorithm_param.h"
#include "..\structure\concurrent\msg_queue.h"
#include "..\structure\concurrent\thread_guard.h"

using namespace std::chrono;
namespace fs = std::filesystem;

enum class ParamType : uint8_t
{
    NONE_0,
};
struct ModifyRequest
{
public:
    ParamType type_;
    double value_;
public:
    ModifyRequest(ParamType type = ParamType::NONE_0, double value = 0.0) : type_(type), value_(value)
    {

    }
};

class ParamManager final
{ 
public: 
    using thread_guard = concurrent::thread_guard;  
    using msg_queue = concurrent::msg_queue<ModifyRequest>;
private:
    std::atomic<bool> stop_flag_{false};
    fs::path param_path_;
    std::shared_ptr<PublicParam> public_param_{nullptr};
    std::shared_ptr<FunctionParam> function_param_{nullptr};
    std::shared_ptr<AlgorithmParam> algorithm_param_{nullptr};
    msg_queue msg_queue_;
    std::unique_ptr<thread_guard> rcv_trd_{nullptr};
    std::unique_ptr<thread_guard> pub_trd_{nullptr};
    
public:
    template <typename T, typename = typename std::enable_if_t<std::is_same_v<std::decay_t<T>, fs::path>>>
    ParamManager(T && path) : 
    param_path_(std::forward<T>(path)),
    public_param_(std::make_shared<PublicParam>(param_path_/fs::path("public"))),
    function_param_(std::make_shared<FunctionParam>(param_path_/fs::path("function"))),
    algorithm_param_(std::make_shared<AlgorithmParam>(param_path_/fs::path("algorithm")))
    {
        std::cout << "stop_flag_ : " << stop_flag_.load() << std::endl;
        if (fs::exists(param_path_) && fs::is_directory(param_path_))
        {
            std::cout << "Param Path : " << param_path_ << std::endl;
            if (public_param_)
            {
                std::cout << "Succeed to Create PublicParam!!!" << std::endl;
            }
            else
            {
                std::cout << "Failed to Create PublicParam!!!" << std::endl;
            }
            if (function_param_)
            {
                std::cout << "Succeed to Create FunctionParam!!!" << std::endl;
            }
            else
            {
                std::cout << "Failed to Create FunctionParam!!!" << std::endl;
            }
            if (algorithm_param_)
            {
                std::cout << "Succeed to Create AlgorithmParam!!!" << std::endl;
            }
            else
            {
                std::cout << "Failed to Create AlgorithmParam!!!" << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid Param Path : " << param_path_ << std::endl;
        }
    }
    ~ParamManager()
    {
    }
    ParamManager(const ParamManager&) = delete;
    ParamManager& operator=(const ParamManager&) = delete;
    ParamManager(ParamManager &&) = delete;
    ParamManager& operator=(ParamManager&&) = delete;
public: 
    std::shared_ptr<PublicParam> GetPublicParam() const noexcept
    {
        return public_param_;
    }
    std::shared_ptr<FunctionParam> GetFunctionParam() const noexcept
    {
        return function_param_;
    }
    std::shared_ptr<AlgorithmParam> GetAlgorithmParam() const noexcept
    {
        return algorithm_param_;
    }
    void SetUp()
    {
        InitReadersAndWriters();
        if (rcv_trd_ = std::make_unique<thread_guard>(&ParamManager::HandleReceiver, this))
        {
            std::cout << "Succeed to Create Receiver Thread of ParamManager!" << std::endl;
        }
        else
        {
            std::cout << "Failed to Create Receiver Thread of ParamManager!" << std::endl;
        }
    }
    void InitReadersAndWriters()
    {

    }
    bool ModifyParam(ModifyRequest rqst)
    {
        return ModifyParamInBuffer();
        
    }
    bool ModifyParamInBuffer()
    {
        return ModifyParamInFile();
    }
    bool ModifyParamInFile()
    {
        return true;
    }
    void SendPublicParam()
    {

    }
    void SendFunctionParam()
    {

    }
    void SendAlgorithm()
    {

    }
    void HandleReceiver()
    {
        while (true)
        {
            if (stop_flag_.load())
            {
                return ;
            }
            auto rqst = msg_queue_.wait_pop();
            std::cout << "pop data" << std::endl;
            if (ModifyParam(*rqst))
            {
                SendPublicParam();
                SendFunctionParam();
                SendAlgorithm();
            }
            else
            {
                std::cout << "Failed Modify Param!!!" << std::endl;
            }
        }
    }
    void Receiver()
    {
        msg_queue_.push(ModifyRequest());
        std::cout << "push data" << std::endl;
    }
};