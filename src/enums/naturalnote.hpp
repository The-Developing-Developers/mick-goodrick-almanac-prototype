#ifndef NATURALNOTE_HPP
#define NATURALNOTE_HPP

#include <map>
#include <string>

/**
 * @brief The numeric values of the entries reflect the values defined in class `ChromaticPitch`.
 */
class NaturalNote
{
public:
  enum class enum_t
  {
    C = 0,
    D = 2,
    E = 4,
    F = 5,
    G = 7,
    A = 9,
    B = 11
  };

  NaturalNote(const enum_t pitch = enum_t::C) noexcept;
  NaturalNote(const int    pitch) noexcept; // This constructor is useful when dealing with arithmetic operations involving pitches and alterations

  operator int() const noexcept;
  NaturalNote& operator=(const int    pitch) noexcept;
  NaturalNote& operator=(const enum_t pitch) noexcept;

  static const std::map<enum_t, std::string> &getMap(void);
  static const std::string getNoteAsString(const enum_t naturalNote);

private:
  enum_t m_pitch;
  static const std::map<enum_t, std::string> m_enumToString;
};

#endif // NATURALNOTE_HPP