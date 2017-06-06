/*!
  nyaml
  --
  A very very loose yaml implimentation.

  todo
  --
  I'd like to get STL out of the header

  Copyright: public-domain
*/
#ifndef NYAML_INCLUDED_EE4C9622_B507_4F22_A19A_C6547F8AEF1B
#define NYAML_INCLUDED_EE4C9622_B507_4F22_A19A_C6547F8AEF1B


#include <string>
#include <vector>


// -------------------------------------------------------- [ NYAML Config ] --


// #define NYAML_DEUBG_PARSER_OUTPUT // for testing
// #define NYAML_DEBUG_NODE_OUTPUT // for testing
#define NYAML_INDENT_SIZE 2


#ifndef LIB_NS_NAME
#define LIB_NS_NAME lib
#endif


// ----------------------------------------------------- [ NAYML Interface ] --


namespace LIB_NS_NAME {
namespace nyaml {


class node
{
public:

  node*         get_parent() const;
  void          set_parent(node* set_parent);
  void          set_name(const std::string &str);
  std::string   get_name() const;
  void          set_value(const std::string &str);
  std::string   get_value() const;
  size_t        get_number_of_children() const;
  void          add_child();
  node*         get_child(const int i) const;
  node&         operator[](const char *name); // Will create node if not found.
  node&         operator[](const int i);      // Will create node(s) if not found.
  node&         operator=(const std::string &new_value);

private:

  std::string       name   = "";
  std::string       value  = "";
  node*             parent = nullptr;
  mutable std::vector<node> children;

};


/*
  Parse nyaml data.
*/
node
parse(const char *data);

/*
  export nyaml data to a string.
*/
std::string
export_to_string(const node &export_node);


} // ns
} // ns


#endif // inc guard



#ifdef LIB_NYAML_IMPL


#include <assert.h>
#include <stdio.h>


// ---------------------------------------------------------- [ NYAML Impl ] --


namespace LIB_NS_NAME {
namespace nyaml {


node*
node::get_parent() const
{
  return parent;
}

void
node::set_parent(node* set_parent)
{
  parent = set_parent;
}

void
node::set_name(const std::string &str)
{
  name = str;
}

std::string
node::get_name() const
{
  return name;
}

void
node::set_value(const std::string &str)
{
  value = str;
}

std::string
node::get_value() const
{
  return value;
}

size_t
node::get_number_of_children() const
{
  return children.size();
}

void
node::add_child()
{
  children.emplace_back(node());
  children.back().set_parent(this);
}

node*
node::get_child(const int i) const
{
  if(children.empty())
  {
    return nullptr;
  }

  if(i == -1)
  {
    return &children.back();
  }

  if(i > children.size())
  {
    return nullptr;
  }

  return &children[i];
}

node&
node::operator[](const char *name)
{
  // Search children
  for(auto &child : children)
  {
    if(strcmp(child.name.c_str(), name) == 0)
    {
      return child;
    }
  }

  children.emplace_back(node());
  children.back().name = name;

  return children.back();
}


node&
node::operator[](const int i)
{
  auto parent = get_parent();
  assert(parent);

  auto name = get_name();

  unsigned int children_found = 0;
  for(unsigned int c = 0; c < parent->get_number_of_children(); ++c)
  {
    if(parent->get_child(c)->get_name() == name)
    {
      if(children_found == i)
      {
        #ifdef NYAML_DEBUG_NODE_OUTPUT
        printf("return_child...\n");
        #endif

        return *parent->get_child(c);
      }
      else
      {
        #ifdef NYAML_DEBUG_NODE_OUTPUT
        printf("found_child...\n");
        #endif

        ++children_found;
      }
    }
  }

  // We we didn't find one, we will pad out the values
  const unsigned int pad_out = (i + 1) - children_found;

  #ifdef NYAML_DEBUG_NODE_OUTPUT
  printf("children to add %d\n", pad_out);
  #endif

  for(unsigned int c = 0; c < pad_out; ++c)
  {
    #ifdef NYAML_DEBUG_NODE_OUTPUT
    printf("add_child...\n");
    #endif

    parent->add_child();
    parent->get_child(-1)->set_name(name);
    parent->get_child(-1)->set_value("");
  }

  auto return_node = parent->get_child(-1);
  assert(return_node);

  #ifdef NYAML_DEBUG_NODE_OUTPUT
  printf("return_new_child...\n");
  #endif

  return *return_node;
}

node&
node::operator=(const std::string &new_value)
{
  value = new_value;
  return *this;
}

node
parse(const char *data)
{
  #ifdef NYAML_DEUBG_PARSER_OUTPUT
  printf("parsing nyaml\n");
  printf("-------------\n");
  #endif

  enum class parser_state
  {
    whitespace,
    comment,
    key,
    value,
  };

  parser_state curr_parser_state = parser_state::whitespace;

  int curr_index = 0;
  int array_index = -1;

  std::string curr_buffer = "";

  int curr_indent = 0;
  int last_indent = 0;

  node root_node;
  node *curr_node = &root_node;

  while(data[curr_index] != '\0')
  {
    /*
      Removes trailing and prefixing spaces from a string.
    */
    auto trim_string = [](const std::string &str) -> std::string
    {
      const auto beg = str.find_first_not_of(" ");
      const auto end = str.find_last_not_of(" ");

      if (beg == std::string::npos)
      {
        return "";
      }

      return str.substr(beg, end - beg + 1);
    };

    const char curr_char = data[curr_index];

    /*
      Check for indents.
      We need to know the indents so we can navigate the tree.
    */
    if(curr_parser_state == parser_state::whitespace
      && (curr_char == '\t' || curr_char == ' '))
    {
      // If tab
      if(curr_char == '\t')
      {
        #ifdef NYAML_DEUBG_PARSER_OUTPUT
        printf("->");
        #endif

        ++curr_indent;
        ++curr_index;

        continue;
      }

      // Peekahead to see if its spaces.
      bool is_indent = true;
      for(uint32_t i = 1; i < NYAML_INDENT_SIZE; ++i)
      {
        if(data[curr_index + i] != ' ')
        {
          is_indent = false;
          break;
        }
      }

      if(is_indent)
      {
        #ifdef NYAML_DEUBG_PARSER_OUTPUT
        printf(">");
        #endif

        ++curr_indent;
        curr_index += NYAML_INDENT_SIZE;

        continue;
      }
    }

    /*
      New line
      New line will push the current data into the tree.
    */
    if(curr_char == '\n')
    {
      #ifdef NYAML_DEUBG_PARSER_OUTPUT
      printf("[end]\n");
      #endif

      curr_indent = 0;
      ++curr_index;
      if(!curr_buffer.empty())
      {
        curr_node->set_value(trim_string(curr_buffer));
      }

      curr_buffer = "";
      curr_parser_state = parser_state::whitespace;

      continue;
    }

    /*
      Key:value
      Flips the parser mode from key to value.
    */
    if(curr_char == ':' && curr_parser_state == parser_state::key)
    {
      #ifdef NYAML_DEUBG_PARSER_OUTPUT
      printf(":");
      #endif

      curr_parser_state = parser_state::value;
      ++curr_index;

      curr_node->set_name(trim_string(curr_buffer));
      curr_buffer = "";

      continue;
    }

    /*
      Comments
      We ignore comments
    */
    if(curr_char == '#' && curr_parser_state == parser_state::whitespace)
    {
      #ifdef NYAML_DEUBG_PARSER_OUTPUT
      printf("#");
      #endif

      ++curr_index;
      curr_parser_state = parser_state::comment;

      continue;
    }

    if(curr_parser_state == parser_state::comment)
    {
      #ifdef NYAML_DEUBG_PARSER_OUTPUT
      printf("#");
      #endif

      ++curr_index;

      continue;
    }

    /*
      Get data
      If we are still in whitespace mode and got this far we need to collect
      the data, this is just to be sure we ahve the correct node.
    */
    if(curr_parser_state == parser_state::whitespace)
    {
      curr_parser_state = parser_state::key;

      if(curr_indent > 0)
      {
        // Going down
        if(curr_indent > last_indent)
        {
          #ifdef NYAML_DEUBG_PARSER_OUTPUT
          printf("[add child to %s]", curr_node->get_name().c_str());
          #endif

          curr_node->add_child();
          curr_node = curr_node->get_child(-1);
          assert(curr_node);
        }
        // up
        else if(last_indent > curr_indent)
        {
          #ifdef NYAML_DEUBG_PARSER_OUTPUT
          printf("[find parent - ");
          #endif

          auto up_by = last_indent - curr_indent + 1;

          while(up_by > 0)
          {
            curr_node = curr_node->get_parent();
            up_by--;
          }

          #ifdef NYAML_DEUBG_PARSER_OUTPUT
          printf("%s]", curr_node->get_name().c_str());
          #endif

          curr_node->add_child();
          curr_node = curr_node->get_child(-1);

          assert(curr_node);
        }
        // Same level
        else
        {
          #ifdef NYAML_DEUBG_PARSER_OUTPUT
          printf("[find parent + add child]");
          #endif

          curr_node = curr_node->get_parent();
          assert(curr_node);

          auto parent = curr_node;

          curr_node->add_child();
          curr_node = curr_node->get_child(-1);
          assert(curr_node);
        }

        #ifdef NYAML_DEUBG_PARSER_OUTPUT
        printf("[reset indent]");
        #endif

        last_indent = curr_indent;
        curr_indent = 0;
      }
    }

    #ifdef NYAML_DEUBG_PARSER_OUTPUT
    printf("+");
    #endif

    ++curr_index;
    const char buff[2] = {curr_char, '\0'};
    curr_buffer.append(std::string(buff));
  }

  return root_node;
}


namespace detail {

void
print(std::string &output, const node *expor_node, int indent)
{
  for(int i = 0; i < (NYAML_INDENT_SIZE * indent); ++i)
  {
    output.append(" ");
  }

  output.append(expor_node->get_name());
  output.append(": ");
  output.append(expor_node->get_value());
  output.append("\n");

  for(int c = 0; c < expor_node->get_number_of_children(); ++c)
  {
    print(output, expor_node->get_child(c), indent + 1);
  }
}

} // ns detail


std::string
export_to_string(const node &expor_node)
{
  std::string output;
  detail::print(output, &expor_node, 0);

  return output;
}

} // ns
} // ns

#endif // impl guard
