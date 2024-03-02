#include "chromaticpitch.hpp"

ChromaticPitch::ChromaticPitch(const enum_t pitch) noexcept
  : m_pitch(pitch)
{}

// This constructor is useful when dealing with arithmetic operations involving pitches and alterations
ChromaticPitch::ChromaticPitch(const int pitch) noexcept
  : m_pitch(static_cast<enum_t>(pitch))
{}

ChromaticPitch::operator int() const noexcept
{
  return static_cast<int>(m_pitch);
}

ChromaticPitch& ChromaticPitch::operator=(const int pitch) noexcept
{
  m_pitch = static_cast<enum_t>(pitch);
  return *this;
}

ChromaticPitch& ChromaticPitch::operator=(const enum_t pitch) noexcept
{
  m_pitch = pitch;
  return *this;
}
