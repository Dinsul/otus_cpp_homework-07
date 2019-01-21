#include "nickname.h"
#include <algorithm>
#include <iostream>

RadixTree::RadixTree() : _head(std::make_unique<RadixNode>("", false))
{}

void RadixTree::add(const std::string &text)
{
    if (_head->text.empty() && _head->children.empty())
    {
        _head = std::make_unique<RadixNode>(text);
    }
    else
    {
        add(*_head, text);
    }
}

void RadixTree::add(RadixNode &node, const std::string &text)
{
    decltype(std::mismatch(node.text.begin(), node.text.end(), text.begin(), text.end())) res;

    if (node.text.empty())
    {
        pushChild(node, text);

        return;
    }
    else if(node.text == text)
    {
        node.is_end = true;
        return;
    }
    else if (node.text.size() > text.size())
    {
        res = std::mismatch(node.text.begin(), node.text.begin() + text.size(), text.begin(), text.end());
    }
    else
    {
        res = std::mismatch(node.text.begin(), node.text.end(), text.begin(), text.end());
    }

    if (res.first != node.text.end())
    {
        RadixNode nNode{std::string{res.first, node.text.end()}};

        nNode.children.swap(node.children);
        nNode.is_end = node.is_end;

        node.children.emplace_back(std::make_unique<RadixNode>(nNode));

        node.is_end = false;
    }

    node.text = std::string{node.text.begin(), res.first};

    if (res.second != text.end())
    {
        pushChild(node, std::string{res.second, text.end()});
    }
    else
    {
        node.is_end = true;
    }
}

void RadixTree::pushChild(RadixNode &node, const std::string &text)
{
    for (auto child = node.children.begin(); child != node.children.end(); ++child)
    {
        auto firstChar  = (*child)->text.begin();
        auto secondChar = text.begin();

        //В UTF-8 считаем октеты первого символа
//        unsigned char firstByte = *firstChar;
//        while (firstByte & 128
//               && firstChar  != child->text.end()
//               && secondChar != text.end()
//               )
//        {
//            firstByte <<= 1;
//            ++firstChar;
//            ++secondChar;
//        }

        if (*firstChar == *secondChar)
        {
            add(**child, text);

            return;
        }
    }

    node.children.emplace_back(std::make_unique<RadixNode>(text));
}

void RadixTree::remove(const std::string &text)
{
    remove(*_head, text.begin(), text.end());
}

void RadixTree::remove(RadixNode &node, const std::string::const_iterator &begin, const std::string::const_iterator &end)
{
    auto res = std::mismatch(node.text.begin(), node.text.end(), begin, end);

    if (res.first == node.text.end())
    {
        if (res.second == end)
        {
            node.is_end = false;
        }

        for (auto child = node.children.begin(); child != node.children.end();  ++child)
        {
            if ((*child)->text[0] == res.second[0])
            {
                remove(**child, res.second, end);

                if (!(*child)->is_end)
                {
                    if ((*child)->children.size() == 1)
                    {
                        auto subChildren = (*child)->children.end();

                        (*subChildren)->text = (*child)->text + (*subChildren)->text;
                        node.children.emplace_back(std::make_unique<RadixNode>(**subChildren));
                        node.children.remove(*child);
                    }
                    else if ((*child)->children.empty())
                    {
                        node.children.remove(*child);
                    }

                    return;
                }
            }
            else if (res.second == end && node.children.size() == 1)
            {
                (*child)->text = node.text + (*child)->text;

                node = std::move(**child);

                child->reset();

                return;
            }
        }
    }

    return;
}

void RadixTree::printMinP()
{
    printMinP(*_head, "", "");
}

void RadixTree::printMinP(const RadixNode &node, std::string nickname, std::string minP)
{
    nickname.append(node.text);

    if (node.children.empty())
    {
        auto end = node.text.begin();

        //В UTF-8 считаем октеты первого символа
//        unsigned char firstChar = *end;
//        do
//        {
//            ++end;

//            if (firstChar & 128)
//            {
//                firstChar <<= 1;
//            }
//            else
//            {
//                break;
//            }
//        }
//        while (end != node.text.end());

        minP.append(node.text.begin(), ++end);
    }
    else
    {
        minP.append(node.text);
    }

    if (node.is_end)
    {
        std::cout << nickname << " " << minP << std::endl;
    }

    for (auto child = node.children.begin(); child != node.children.end();  ++child)
    {
        printMinP(**child, nickname, minP);
    }
}

void RadixTree::printTree()
{
    printTree(*_head, "");
    std::cout << std::endl;
}

void RadixTree::printTree(const RadixNode &node, std::string fill)
{
    std::cout << fill << node.text << (node.is_end ? "$" : "") << "\n";

    replaceSubString(fill, "├", "│");
    replaceSubString(fill, "└", " ");

    std::string addedStr;

    auto rabit = node.children.begin();
    ++rabit;

    for (auto child = node.children.begin(); child != node.children.end();  ++child)
    {
        if (rabit == node.children.end())
        {
            addedStr =  " └";
        }
        else
        {
            ++rabit;
            addedStr = " ├";
        }

        printTree(**child, fill + addedStr);
    }
}

bool RadixTree::find(const std::string &text)
{
    return find(*_head, text.begin(), text.end());
}

bool RadixTree::find(RadixNode &node, const std::string::const_iterator &begin, const std::string::const_iterator &end)
{
    auto res = std::mismatch(node.text.begin(), node.text.end(), begin, end);

    if (res.first == node.text.end())
    {
        if (res.second == end)
        {
            return node.is_end;
        }

        for (auto child = node.children.begin(); child != node.children.end();  ++child)
        {
            if ((*child)->text[0] == res.second[0])
            {
                return find(**child, res.second, end);
            }
        }
    }

    return false;
}

RadixNode::RadixNode() : text(""), is_end(false)
{}

RadixNode::RadixNode(std::string newText, bool end) : text(newText), is_end(end)
{}

RadixNode::RadixNode(const RadixNode &other) :
    text(other.text),
    is_end(other.is_end)
{
    for (auto child = other.children.begin(); child != other.children.end();  ++child)
    {
        children.emplace_back(std::make_unique<RadixNode>(**child));
    }
}

RadixNode::RadixNode(RadixNode &&other) : text(std::move(other.text)), is_end(other.is_end), children(std::move(other.children))
{}
//RadixNode::RadixNode(RadixNode &&other)
//{
//    this->is_end = other.is_end;
//    this->text.swap(other.text);
//    this->children.swap(other.children);
//}

RadixNode &RadixNode::operator =(RadixNode &&other)
{
    this->is_end = other.is_end;
    this->text.swap(other.text);
    this->children.swap(other.children);

    return *this;
}


bool replaceSubString(std::string &str, const std::string &subString, const std::string &newSubString)
{
    auto pos = std::find_end(str.begin(), str.end(), subString.begin(), subString.end());

    if (pos != str.end())
    {
        str.insert(str.erase(pos, pos + subString.length()), newSubString.begin(), newSubString.end());

        return true;
    }

    return false;
}
