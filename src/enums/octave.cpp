#include "octave.hpp"

Octave::Octave(const enum_t octave) noexcept
  : m_octave(octave)
{}

Octave::Octave(const int octave) noexcept
  : m_octave(static_cast<enum_t>(octave))
{}

Octave::operator int() const noexcept
{
  return static_cast<int>(m_octave);
}
