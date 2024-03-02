#ifndef FUNCTIONALSEQUENCE_HPP
#define FUNCTIONALSEQUENCE_HPP

#include <cstdint>

/**
 * @brief Functional sequences used to build a chordal harmonisation of a scale based on voice
 * leading. For example, `sequence_375F` means that when building the next chord in the scale, the
 * voices must move like this: F -> 3, 3 -> 7, 5 -> 5, 7 -> F (i.e., the fundamental of the starting
 * chord goes to the third of the next chord, the third of the starting chord goes to the seventh of
 * the next chord, and so on).
 */
class FunctionalSequence
{
public:
  enum class enum_t
  {
    sequence_F35_F53,
    sequence_F35_3F5,

  delimiter_thirds, // Used in `getSize` to separate the three-notes sequences from the four-notes sequences

    sequence_F357_F375,
    sequence_F357_357F,
    sequence_F357_375F,
    sequence_F357_73F5,

    sequence_F347_347F,

  delimiter_fourths, // Similar

    sequence_F3467_67F34,

  delimiter_fifths, // Similar

  delimiter_sixths, // Similar

    sequence_F234567_465273F,

  delimiter_sevenths // Similar
  };

  explicit FunctionalSequence(const enum_t sequence) noexcept;

  /**
   * @brief returns the number of notes of which a sequence is composed. For example, `sequence_F53`
   * is composed of three notes, whereas `sequence_375F` is composed of four notes.
   **/
  size_t getSize(void) const noexcept;

  operator enum_t() const noexcept;

private:
  enum_t m_sequence;
};

#endif // FUNCTIONALSEQUENCE_HPP