#include <memory>
#include <iostream>

template<typename T>
class SharedSingletonBase 
{
public:
    using DataType = T;
    using DataTypeSPtr = std::shared_ptr<T>;
protected:
    SharedSingletonBase() = default;
    virtual ~SharedSingletonBase() = default;

public:
    SharedSingletonBase(const SharedSingletonBase&) = delete;
    SharedSingletonBase& operator=(const SharedSingletonBase&) = delete;

    // 返回shared_ptr值，支持外部拷贝保存多份
    static DataTypeSPtr GetInstance() 
    {
        static DataTypeSPtr instance = std::make_shared<DataType>();
        return instance;
    }
};

class SharedSingletonDerived : public SharedSingletonBase<SharedSingletonDerived> 
{
private: 
    // 关键：构造函数私有，禁止外部new
    SharedSingletonDerived() = default;
    // 允许基类访问私有构造
    friend SharedSingletonBase<SharedSingletonDerived>;
public:
    void loadConfig() 
    {
        std::cout << "loadConfig" << std::endl;
    }
};