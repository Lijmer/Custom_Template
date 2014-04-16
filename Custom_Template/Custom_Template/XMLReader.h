#pragma once
#ifndef __INCLUDED_XML_READER_H
#define __INCLUDED_XML_READER_H

#include <string>
#include <vector>

namespace ff
{

  class XMLTree
  {
  public:
    XMLTree(const std::string &filePath);
    ~XMLTree() { delete m_root; }


    struct Node
    {
      Node(Node *parent)
      :m_parent(parent)
      {

      }
      ~Node()
      {
        for(auto &i : m_childeren)
          delete i;
      }

      Node* FindChild(const std::string &name);


      std::string m_name;
      std::string m_data;

      Node* m_parent;
      std::vector<Node*> m_childeren;
    } *m_root;
  };


  void LoadXMLFile(const std::string &filePath, std::string &out_data);
}

#endif
