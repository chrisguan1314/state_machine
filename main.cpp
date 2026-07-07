#include "random.h"
#include "cat.h"
#include "singleton.h"
#include "state_machine_base.h"
#include "avp_cruising_state_machine.h"
#include "state_machine_manage.h"
#include "threadsafe_stack.h"
#include "threadsafe_queue.h"
#include "custom_queue.h"
#include "param_manager\param_manager.h"
#include "structure\concurrent\ring_buffer.h"
#include "structure\pool\thread_pool.h"
#include "structure\base\point6d.h"
#include "structure\algorithm\perception\obstacle.h"
#include "structure\concurrent\spsc_queue.h"



#include <vector>
#include <algorithm>
#include <random>
#include <memory>
#include <iostream>
#include <functional>
#include <filesystem>


const uint32_t MIN_VALUE = 0;
const uint32_t MAX_VALUE = 100;

void deleting(uint32_t * p)
{
    delete p; 
    std::cout << "delete p!!" << std::endl;
}

template <typename T>
class MyAllocator 
{
public:
    using value_type = T;

    MyAllocator() = default;

    template <typename U>
    MyAllocator(const MyAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) 
    {
        std::cout << "Allocating " << n * sizeof(value_type) << " bytes." << std::endl;
        return static_cast<T*>(::operator new(n * sizeof(value_type)));
    }

    void deallocate(value_type* p, std::size_t) 
    {
        std::cout << "Deallocating memory." << std::endl;
        ::operator delete(p);
    }
};

int add(int a, int b)
{
    return (a + b);
}
concurrent::SpscQueue<uint32_t> q;

void AddData()
{
    for (std::size_t i = 0; i < 5; ++i)
    {
        q.push(i + 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
void ReadData()
{
    while (true)
    {
        if (!q.empty())
        {
            auto x = q.pop();
            if (x.has_value())
            {
                std::cout << *x << std::endl;
                std::this_thread::sleep_for(std::chrono::microseconds(10));
            }
            else
            {
                std::cout << "It's Empty!" << std::endl; 
            }
        }
        else
        {
            std::this_thread::yield();
        }
    }
}

int main()
{
    // auto o1 = std::make_unique<structure::perception::Obstacle<double>>();
    // o1->GetTimestamp();

    // if (auto param_manager = std::make_unique<ParamManager>(std::filesystem::current_path()))
    // {
    //     param_manager->SetUp();
    //     param_manager->Receiver();
    // }

    // ThreadPool thread_pool(10);

    // concurrent::ring_buffer<uint32_t> ring_buffer;
    // ring_buffer.try_push_for(10, std::chrono::milliseconds(10));
    // std::cout << "size : " << ring_buffer.size() << std::endl;
    // std::cout << "capacity : " << ring_buffer.capacity() << std::endl;
    // ring_buffer.try_pop_for(std::chrono::milliseconds(10));
    // std::cout << "size : " << ring_buffer.size() << std::endl;
    // std::cout << "capacity : " << ring_buffer.capacity() << std::endl;
    
    // std::unordered_map<int, int> myMap;

    // // 输出初始的桶数量和负载因子
    // std::cout << "Initial bucket count: " << myMap.bucket_count() << std::endl;
    // std::cout << "Max bucket count: " << myMap.max_bucket_count() << std::endl;
    // std::cout << "Initial load factor: " << myMap.load_factor() << std::endl;
    // std::cout << "Max load factor: " << myMap.max_load_factor() << std::endl;


    // // 插入元素
    // for (int i = 0; i < 4; ++i) 
    // {
    //     myMap[i] = i * 2;
    //     std::cout << "After inserting " << i << ": ";
    //     std::cout << "Bucket count: " << myMap.bucket_count() << ", ";
    //     std::cout << "Load factor: " << myMap.load_factor() << std::endl;
    // }

    // auto fn = myMap.hash_function();

    // std::cout << "3 : " << fn (3) << std::endl;
    // std::cout << "6 : " << fn (6) << std::endl;
    // std::cout << "-10000 : " << fn (-10000) << std::endl;
    // std::shared_ptr<uint32_t> ptr = std::allocate_shared<uint32_t>(MyAllocator<uint32_t>(), 42);
    // std::cout << *ptr << std::endl;

    // if (std::unique_ptr<StateMachineManager> sm_manager = std::make_unique<StateMachineManager>(""))
    // {
    //     sm_manager->Init();
    // }
    // std::function<int(int, int)> func = std::plus<int>();
    // // std::bind
    // std::function<int(int)> func1 = std::bind(func, 2, std::placeholders::_1);
    // std::cout << func(1, 2) << std::endl;
    // std::cout << func1(2) << std::endl;

    // Point2D<double> p1(1, 2);
    // std::cout << p1.DistOfChebyshev(Point2D<double>(2, 1)) << std::endl;
    
    // custom_queue<uint32_t> s1;
    // s1.push(32);   
    // s1.push(64);  
    // while (true)
    // {
    //     auto x = s1.try_pop();
    //     if (x)
    //     {
    //         std::cout << *x << std::endl;
    //     }
    //     else
    //     {
    //         break;;
    //     }
    // }

    // SharedSingletonDerived::GetInstance()->loadConfig();

    std::thread t1(&AddData);
    std::thread t2(&AddData);
    std::thread t3(&AddData);
    std::thread t5(&AddData);
    std::thread t4(&ReadData);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    // std::vector<Animal> v;
    // v.push_back(Animal());
    // std::cout << "111" << std::endl;
    // Animal animal;
    // animal.SetName(std::string("guan"));
    // std::cout << "Animale name : " << animal.GetAge() << std::endl;
    // if (std::unique_ptr<Cat> animal = std::make_unique<Cat>())
    // {
    //     animal->Eatting();
    // }
    // void (*function_point)(uint32_t * p) = deleting; // &可以省略
    // auto uptr_deletor = [x = 10LL, y = 20LL](uint32_t * p)
    // { 
    //     delete p; 
    //     std::cout << "x : " << x << std::endl;
    //     std::cout << "delete p!" << std::endl;
    // };

    // {
    //     std::unique_ptr<uint32_t, decltype(function_point)> uptr(new uint32_t(10), function_point);
    //     std::shared_ptr<uint32_t> sptr = std::make_shared<uint32_t>(10);
    //     uint32_t * p = new uint32_t(10);

    //     std::cout << "uptr size : " << sizeof(uptr) << std::endl;
    //     std::cout << "sptr size : " << sizeof(sptr) << std::endl;
    //     std::cout << "p size : " << sizeof(p) << std::endl;
    // }
    

    // uint32_t * p = nullptr;
    // p = new uint32_t(10);
    // std::cout << "p : " << *p << std::endl;
    // // 这里对c-style array进行初始化需要用统一初始化（大括号初始化），而不能用小括号
    // // 如果不用大括号进行统一初始化，则编译器就会进行随机初始化，也就有可能会引发未定义行为
    // // 如果没有对c-style数组进行初始化，则在使用该数组之前必须对其进行赋值；
    // p = new uint32_t[10]{(uint32_t)0U};
    // // for (std::size_t i = 0; i < 10; ++i)
    // // {
    // //     p[i] = 1;
    // // }
    // std::for_each(p, p + 10, [](auto x){ std::cout << x << " "; });
    // std::cout << std::endl;
    // // for (std::size_t i = 0; i < 10; ++i)
    // // {
    // //     std::cout << p[i] << " ";
    // // }
    // // 如果到此结束，则会发生内存泄漏，因为在堆区创建的对象p并没有进行回收(析构)
    // // 
    // delete p[];
    
    // const uint32_t target = GenRandamNumber(MIN_VALUE, MAX_VALUE);
    // std::cout << "Please enter a number between " << MIN_VALUE << " - " << MAX_VALUE << " : " << std::endl;
    // std::string value;
    // std::cin >> value;
    // while (true)
    // {
    //     try
    //     {
    //         if (value == "q")
    //         {
    //             std::cout << "Exit!" << std::endl;
    //             break;
    //         }
    //         uint32_t number = std::stoi(value);
    //         if (number == target)
    //         {
    //             std::cout << "The value is matched : " << number << std::endl;
    //             break;
    //         }
    //         else if (std::stoi(value) > target)
    //         {
    //             std::cout << "The value is larger, please continue to enter" << std::endl;
    //             std::cin >> value;
    //         }
    //         else
    //         {
    //             std::cout << "The value is smaller, please continue to enter" << std::endl;
    //             std::cin >> value;
    //         }
    //     }
    //     catch(const std::exception& e)
    //     {
    //         std::cerr << "Invalid number : " << value << std::endl;
    //         break;
    //     }
    // }
    
    return 0;
}
