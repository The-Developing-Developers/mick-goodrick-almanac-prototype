#ifndef DISTANCE_HPP
#define DISTANCE_HPP

// TODO: questa classe è una dipendenza di `ScaleBuilder`. Riassorbirla?
/**
 * @brief Useful to compute the composition of various musical scales
 */
struct DistanceInSemitones
{
  enum class enum_t
  {
    Semitone    = 1,
    Tone        = 2,
    ToneAndHalf = 3
  };

  explicit DistanceInSemitones(const enum_t distance) noexcept;
  explicit DistanceInSemitones(const int    distance) noexcept;

  operator int() const noexcept;

  enum_t m_distance;
};

#endif // DISTANCE_HPP