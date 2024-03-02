#include "functionalsequence.hpp"

FunctionalSequence::FunctionalSequence(const enum_t sequence) noexcept
  : m_sequence(sequence)
{}

size_t FunctionalSequence::getSize(void) const noexcept
{
  if (m_sequence < enum_t::delimiter_thirds)
    return 3;
  else if (m_sequence < enum_t::delimiter_fourths)
    return 4;
  else if (m_sequence < enum_t::delimiter_fifths)
    return 5;
  else if (m_sequence < enum_t::delimiter_sixths)
    return 6;
  else if (m_sequence < enum_t::delimiter_sevenths)
    return 7;
  else
    return 0;
}

FunctionalSequence::operator enum_t() const noexcept
{
  return m_sequence;
}