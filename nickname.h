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
    std::list<std::shared_ptr<RadixNode>> children;
};

//!
//! \brief Базисное дерево
//!
class RadixTree{
    std::shared_ptr<RadixNode> _head; //!< Головной узел с данными

    void add(std::shared_ptr<RadixNode> &node, const std::string &text);
    inline void pushChild(std::shared_ptr<RadixNode> &node, const std::string &text);

public:
    RadixTree();

    void add(const std::string &text);
    void remove(const std::string &text);
    void printTree(void);
    void printMinP(void);
    bool find(const std::string &text);

    static void remove(std::shared_ptr<RadixNode> &node, const std::string::const_iterator &begin, const std::string::const_iterator &end);
    static void printTree(const std::shared_ptr<RadixNode> &node, std::string fill);
    static void printMinP(const std::shared_ptr<RadixNode> &node, std::string nickname, std::string minP);
    static bool find(std::shared_ptr<RadixNode> &node, const std::string::const_iterator &begin, const std::string::const_iterator &end);

};

bool replaceSubString(std::string &str, const std::string &subString, const std::string &newSubString);
