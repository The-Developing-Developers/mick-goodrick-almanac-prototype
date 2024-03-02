#ifndef OCTAVE_HPP
#define OCTAVE_HPP

/**
 * @brief
 */
struct Octave
{
  enum class enum_t
  {
    first  = 1,
    second,
    third,
    fourth,
    fifth,
    sixth,
    seventh,
    eighth,

    how_many
  };

  explicit Octave(const enum_t octave) noexcept;
  explicit Octave(const int    octave) noexcept;

  operator int() const noexcept;

  enum_t m_octave;
};

#endif // OCTAVE_HPP