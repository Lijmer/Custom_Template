#pragma once
#ifndef __INCLUDED_XML_READER_H
#define __INCLUDED_XML_READER_H
#include "API.h"
#include <string>
#include <vector>

namespace ff
{

  class XMLTree
  {
  public:
    INPUT_API XMLTree(const std::string &filePath);
    INPUT_API ~XMLTree() { delete m_root; }


    struct Node
    {
      INPUT_API Node(Node *parent)
      :m_parent(parent)
      {

      }
      INPUT_API ~Node()
      {
        for(auto &i : m_childeren)
          delete i;
      }

      INPUT_API Node* FindChild(const std::string &name);


      std::string m_name;
      std::string m_data;

      Node* m_parent;
      std::vector<Node*> m_childeren;
    } *m_root;
  };


  void LoadXMLFile(const std::string &filePath, std::string &out_data);
}

#endif
