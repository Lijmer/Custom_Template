#include "XMLReader.h"

#include <fstream>
#include <vector>

namespace ff
{
  //TODO Refactor this spaghetti code.
  XMLTree::XMLTree(const std::string &filepath)
  {
    std::string data;
    LoadXMLFile(filepath, data);


    Node* currentNode = nullptr;
    std::string keyData;

    for(auto i = data.begin(), end = data.end(); i != end; ++i)
    {
      if(*i == '<')
      {
        if(*(i + 1) == '/')      //closing tag
        {
          //TODO add verification closing tag is the same as the opening tag.
          while(*++i != '>');
          
          currentNode->m_data = keyData;
          keyData = "";
          currentNode = currentNode->m_parent;
        }
        else if(*(i + 1) == '?') //XML info tag
        {
          for(auto j = i + 2; j != end; ++j)
          {
            if(*j == '?' && *(j + 1) == '>')
            {
              i = j + 1;
              break;
            }
          }
        }
        else                    //opening tag
        {
          std::string newKeyName;
          for(auto j = i + 1; j != end; ++j)
          {
            if(*j != '>')
              newKeyName += *j;
            else
            {
              i = j;
              break;
            }
          }

          if(currentNode == nullptr)
            currentNode = m_root = new Node(currentNode);
          else
          {
            Node *newNode = new Node(currentNode);
            currentNode->m_childeren.push_back(newNode);
            currentNode = newNode;
          }

          currentNode->m_name = newKeyName;
          currentNode->m_data = "";
        }
      }
      else //there is data in this key.
      {
        if(currentNode == nullptr)
          continue;
        else
          keyData += *i;
      }
    }
  }


  XMLTree::Node* XMLTree::Node::FindChild(const std::string &name)
  {
    for(auto &i : m_childeren)
    {
      if(i->m_name == name)
        return i;
    }
    return nullptr;
  }

  void LoadXMLFile(const std::string &filePath, std::string &out_data)
  {
    std::ifstream file(filePath);
    if(!file.is_open())
    {
      printf("File doesn't exist\n");
      return;
    }

    std::string line;
    while(std::getline(file, line))
    {
      for(auto i = line.begin(); i != line.end();)
      {
        //TODO use the <?xml ?> tags here and don't put them in the output.
        //TODO remove comments.
        //TODO add more characters that have to be ignored.
        switch(*i)
        {
        case ' ':
        case '\t':
        case '\n':
        case '\r':
        case '\v':
          i = line.erase(i);
          break;

        default:
          ++i;
          break;
        }
      }
      out_data += line;
    }
  }
}
