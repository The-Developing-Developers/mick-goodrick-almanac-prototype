#include "alteration.hpp"

const std::map<Alteration::enum_t, std::string> Alteration::m_enumToString
{
  {enum_t::doubleFlat, "Double Flat"},
  {enum_t::flat, "Flat"},
  {enum_t::natural, "Natural"},
  {enum_t::sharp, "Sharp"},
  {enum_t::doubleSharp, "Double Sharp"}
};


Alteration::Alteration(const enum_t alteration) noexcept
  : m_alteration(alteration)
{}


Alteration::Alteration(const int alteration) noexcept
  : m_alteration(static_cast<enum_t>(alteration))
{}


Alteration::operator int() const noexcept
{
  return static_cast<int>(m_alteration);
}


Alteration& Alteration::operator=(const enum_t alteration) noexcept
{
  m_alteration = alteration;
  return *this;
}


Alteration& Alteration::operator=(const int alteration) noexcept
{
  m_alteration = static_cast<enum_t>(alteration);
  return *this;
}


const std::map<Alteration::enum_t, std::string> &Alteration::getMap(void)
{
  return m_enumToString;
}


const std::string Alteration::getAlterationAsString(const Alteration::enum_t alteration)
{
  return m_enumToString.at(alteration);
}