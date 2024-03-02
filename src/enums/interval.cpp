#include "interval.hpp"

const std::map<Interval::enum_t, std::string> Interval::m_enumToString
{
  {enum_t::unison,  "Unison"},
  {enum_t::second,  "Second"},
  {enum_t::third,   "Third"},
  {enum_t::fourth,  "Fourth"},
  {enum_t::fifth,   "Fifth"},
  {enum_t::sixth,   "Sixth"},
  {enum_t::seventh, "Seventh"}
};


Interval::Interval(const enum_t interval) noexcept
  : m_interval(interval)
{}


Interval::Interval(const int interval) noexcept
  : m_interval(static_cast<enum_t>(interval - 1)) // Must be zero-based
{}


Interval::operator size_t() const noexcept
{
  return static_cast<size_t>(m_interval);
}


Interval& Interval::operator=(const enum_t interval) noexcept
{
  m_interval = interval;
  return *this;
}


Interval& Interval::operator=(const int interval) noexcept
{
  m_interval = static_cast<enum_t>(interval);
  return *this;
}


Interval& Interval::operator+=(const int increment)
{
  m_interval = static_cast<enum_t>( ( ( static_cast<int>(m_interval) ) + increment ) % static_cast<int>(enum_t::how_many) );
  return *this;
}


Interval& Interval::operator-=(const int increment)
{
  *this += -increment;
  return *this;
}


const std::map<Interval::enum_t, std::string> &Interval::getMap(void)
{
  return m_enumToString;
}


const std::string Interval::getIntervalAsString(const Interval::enum_t interval)
{
  return m_enumToString.at(interval);
}