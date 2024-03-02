#ifndef ALTERATION_HPP
#define ALTERATION_HPP

#include <map>
#include <string>

class Alteration
{
public:
  enum class enum_t
  {
    doubleFlat  = -2,
    flat        = -1,
    natural     =  0,
    sharp       =  1,
    doubleSharp =  2
  };

  Alteration(const enum_t alteration = enum_t::natural) noexcept;
  Alteration(const int    alteration) noexcept;

  operator int() const noexcept;
  Alteration& operator=(const enum_t alteration) noexcept;
  Alteration& operator=(const int    alteration) noexcept;

  static const std::string getAlterationAsString(const enum_t alteration);
  static const std::map<enum_t, std::string> &getMap(void);

private:
  enum_t m_alteration;
  static const std::map<enum_t, std::string> m_enumToString; // Serve per poter automatizzare l'inizializzazione dei valori della combo box nel constructor di `MainWindow`
};

#endif // ALTERATION_HPP
