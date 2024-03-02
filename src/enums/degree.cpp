#include "degree.hpp"

Degree::Degree (const enum_t degree) noexcept
  : m_degree(degree)
{}

Degree::Degree (const int degree) noexcept
  : m_degree(static_cast<enum_t>(degree - 1)) // Must be zero-based
{}

Degree::operator size_t() const noexcept
{
  return static_cast<size_t>(m_degree);
}

Degree Degree::operator+(const int increment)
{
  return Degree(static_cast<enum_t>( ( static_cast<int>(m_degree) + increment ) % static_cast<int>(enum_t::how_many) ));
}

Degree Degree::operator-(const int increment)
{
  return Degree(static_cast<enum_t>( ( static_cast<int>(m_degree) - increment) % static_cast<int>(enum_t::how_many) ) );
}

Degree& Degree::operator+=(const int increment)
{
  m_degree = static_cast<enum_t>( ( ( static_cast<int>(m_degree) ) + increment ) % static_cast<int>(enum_t::how_many) );
  return *this;
}

Degree& Degree::operator-=(const int increment)
{
  *this += -increment;
  return *this;
}