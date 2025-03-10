// Element.hpp
#pragma once
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <string>
#include <vector>
#include <map>
#include <variant>

using namespace emscripten;

// Forward declaration
class Element;

// Props can be different types
using PropValue = std::variant<
    std::string,
    int,
    double,
    bool,
    val // for functions and complex objects
    >;

using Props = std::map<std::string, PropValue>;
using Children = std::vector<Element>;

class Element
{
public:
    std::string type;
    Props props;
    Children children;
    bool isTextNode;
    std::string textContent;

    // Regular element constructor
    Element(const std::string &t, const Props &p = {}, const Children &c = {})
        : type(t), props(p), children(c), isTextNode(false) {}

    // Text node constructor
    static Element createTextNode(const std::string &content)
    {
        Element e("", {}, {});
        e.isTextNode = true;
        e.textContent = content;
        return e;
    }

    val toReactElement(const val &React) const
    {
        if (isTextNode)
        {
            return val(textContent); // Just return the text content directly
        }

        // Convert props to JavaScript object
        val jsProps = val::object();
        for (const auto &[key, value] : props)
        {
            std::visit([&](const auto &v)
                       { jsProps.set(key, v); }, value);
        }

        // Convert children to array of React elements
        std::vector<val> jsChildren;
        for (const auto &child : children)
        {
            jsChildren.push_back(child.toReactElement(React));
        }

        // Call React.createElement with our converted arguments
        if (jsChildren.empty())
        {
            return React.call<val>("createElement", type, jsProps);
        }
        else if (jsChildren.size() == 1)
        {
            return React.call<val>("createElement", type, jsProps, jsChildren[0]);
        }
        else
        {
            val childrenArray = val::array();
            for (size_t i = 0; i < jsChildren.size(); i++)
            {
                childrenArray.set(i, jsChildren[i]);
            }
            return React.call<val>("createElement", type, jsProps, childrenArray);
        }
    }
};

// Helper function to create elements
template <typename... Args>
Element h(const std::string &type, const Props &props = {}, Args &&...children)
{
    return Element(type, props, {std::forward<Args>(children)...});
}

// Helper function for text nodes
Element text(const std::string &content)
{
    return Element::createTextNode(content);
}

EMSCRIPTEN_BINDINGS(CSX_module)
{
    class_<Element>("Element")
        .constructor<std::string, Props, Children>()
        .property("type", &Element::type)
        .property("props", &Element::props)
        .property("children", &Element::children)
        .function("toReactElement", &Element::toReactElement);
}