#ifndef VARIANT_INCLUDED_6C2D38D4_4EDE_4AFD_BC5F_9C90464DC681
#define VARIANT_INCLUDED_6C2D38D4_4EDE_4AFD_BC5F_9C90464DC681


#include <type_traits>


namespace util {


/*!
  This is a simplistic variant class.
  util::variant<int, float, std::string> my_var;
  my_var.set<float>(1.234f);
  my_var.get<float>();
*/
template<typename... Ts>
class variant
{
public:

  explicit variant()
  {

  }


  template<typename T, typename... Args>
  void set(Args&&... args)
  {
    new (&m_data) T(std::forward<Args>(args)...);
  }


  template<typename T>
  const T& get() const
  {
    return *reinterpret_cast<const T*>(&m_data);
  }

  template<typename T>
  T& get()
  {
    return *reinterpret_cast<T*>(&m_data);
  }


private:

  typename std::aligned_union<0, Ts...>::type m_data;

}; // class


} // ns


#endif // inc guard