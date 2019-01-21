#pragma once
#include <string>
#include <vector>
#include <list>
#include <memory>

//!
//! \brief  Класс узла для \link RadixTree \endlink
//!
class RadixNode{
public:
    RadixNode();
    RadixNode(std::string newText, bool end = true);
    RadixNode(const RadixNode& other);
    RadixNode(RadixNode&& other);

    std::string text;
    bool is_end;
    std::list<std::unique_ptr<RadixNode>> children;

    RadixNode &operator = (RadixNode &&other);
};


//!
//! \brief Базисное дерево
//!
class RadixTree{
    std::unique_ptr<RadixNode> _head; //!< Головной узел с данными

    void add(RadixNode &node, const std::string &text);
    inline void pushChild(RadixNode &node, const std::string &text);

public:
    RadixTree();

    void add(const std::string &text);
    void remove(const std::string &text);
    void printTree(void);
    void printMinP(void);
    bool find(const std::string &text);

    static void remove(RadixNode &node, const std::string::const_iterator &begin, const std::string::const_iterator &end);
    static void printTree(const RadixNode &node, std::string fill);
    static void printMinP(const RadixNode &node, std::string nickname, std::string minP);
    static bool find(RadixNode &node, const std::string::const_iterator &begin, const std::string::const_iterator &end);

};

bool replaceSubString(std::string &str, const std::string &subString, const std::string &newSubString);
