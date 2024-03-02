#ifndef CHROMATICPITCH_HPP
#define CHROMATICPITCH_HPP

/**
 * @brief Each pitch of the chromatic scale is assigned a unique value, starting from C = 0
 */
struct ChromaticPitch
{
  enum class enum_t
  {
    C       = 0,
    C_Sharp = 1,
    D_Flat  = 1,
    D       = 2,
    D_Sharp = 3,
    E_Flat  = 3,
    E       = 4,
    F       = 5,
    F_Sharp = 6,
    G_Flat  = 6,
    G       = 7,
    G_Sharp = 8,
    A_Flat  = 8,
    A       = 9,
    A_Sharp = 10,
    B_Flat  = 10,
    B       = 11
  };

  explicit ChromaticPitch(const enum_t pitch = enum_t::C) noexcept;
  explicit ChromaticPitch(const int    pitch) noexcept; // This constructor is useful when dealing with arithmetic operations involving pitches and alterations

  operator int() const noexcept;
  ChromaticPitch& operator=(const int    pitch) noexcept;
  ChromaticPitch& operator=(const enum_t pitch) noexcept;

  enum_t m_pitch;
};

#endif // CHROMATICPITCH_HPP