#include "distanceinsemitones.hpp"

DistanceInSemitones::DistanceInSemitones (enum_t distance) noexcept
  : m_distance(distance)
{}

DistanceInSemitones::DistanceInSemitones (int distance) noexcept
  : m_distance(static_cast<enum_t>(distance))
{}

DistanceInSemitones::operator int() const noexcept
{
  return static_cast<int>(m_distance);
}