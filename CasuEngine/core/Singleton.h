#pragma once  
#include <memory>  

template<typename T>  
class Singleton  
{  
public:  
   static T* GetInstance()  
   {  
       if (!instance)  
       {  
           instance.reset(new T());  
       }  
       return instance.get();  
   }  

   static void DestroyInstance()  
   {  
       instance.reset();  
   }  

protected:  
   static std::unique_ptr<T> instance; // Pointer to the singleton instance  
};  

// Definition of the static member  
template<typename T>  
std::unique_ptr<T> Singleton<T>::instance = nullptr;
