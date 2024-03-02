#include "naturalnote.hpp"

const std::map<NaturalNote::enum_t, std::string> NaturalNote::m_enumToString
{
  {NaturalNote::enum_t::C, "C"},
  {NaturalNote::enum_t::D, "D"},
  {NaturalNote::enum_t::E, "E"},
  {NaturalNote::enum_t::F, "F"},
  {NaturalNote::enum_t::G, "G"},
  {NaturalNote::enum_t::A, "A"},
  {NaturalNote::enum_t::B, "B"}
};


NaturalNote::NaturalNote(const enum_t pitch) noexcept
  : m_pitch(pitch)
{}

// This constructor is useful when dealing with arithmetic operations involving pitches and alterations

NaturalNote::NaturalNote(const int pitch) noexcept
  : m_pitch(static_cast<enum_t>(pitch))
{}


NaturalNote::operator int() const noexcept
{
  return static_cast<int>(m_pitch);
}


NaturalNote& NaturalNote::operator=(const int pitch) noexcept
{
  m_pitch = static_cast<enum_t>(pitch);
  return *this;
}


NaturalNote& NaturalNote::operator=(const enum_t pitch) noexcept
{
  m_pitch = pitch;
  return *this;
}


const std::map<NaturalNote::enum_t, std::string> &NaturalNote::getMap(void)
{
  return m_enumToString;
}


const std::string NaturalNote::getNoteAsString(const NaturalNote::enum_t naturalNote)
{
  return m_enumToString.at(naturalNote);
}
