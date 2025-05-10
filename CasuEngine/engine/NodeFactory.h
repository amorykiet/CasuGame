#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <stdexcept>

class Node;

class NodeFactory {
public:
    // Register a class with its creation function
    static void Register(const std::string& className, std::function<Node* ()> creator) {
        GetRegistry()[className] = creator;
    }

    // Create an object by class name
    static Node* Create(const std::string& className) {
        auto it = GetRegistry().find(className);
        if (it != GetRegistry().end()) {
            return it->second(); // Call the creation function
        }
        throw std::runtime_error("Class not registered: " + className);
    }

private:
    // Registry to store class name and creation function pairs
    static std::unordered_map<std::string, std::function<Node* ()>>& GetRegistry() {
        static std::unordered_map<std::string, std::function<Node* ()>> registry;
        return registry;
    }
};

#define REGISTER_NODE_CLASS(className) \
    static bool _registered_##className = []() { \
        NodeFactory::Register(#className, []() { return new className(); }); \
        return true; \
    }()