#ifndef CHORDBUILDER_HPP
#define CHORDBUILDER_HPP

#include <array>
#include <map>
#include <vector>
#include <string>

#include "constants.hpp"
#include "chord.hpp"
#include "degree.hpp"
#include "functionalsequence.hpp"
#include "interval.hpp"
#include "scale.hpp"

class ChordBuilder
{
public:
  // TODO: c'è bisogno di trasformarlo in classe?
  enum class Cycle_enum
  {
    bySeconds = 1,
    byThirds,
    byFourths,
    byFifths,
    bySixths,
    bySevenths
  };

  // TODO: c'è bisogno di trasformarlo in classe?
  enum class IntervallicSequence_enum
  {
    sequence_1117,
    sequence_1177, // Vol. 1, page 48 (originally a 1122). TODO: attenzione: nel libro è applicato a un ciclo di quarte!
    sequence_1777, // Vol. 1, page 39 (originally a 1222)

    sequence_445,
    sequence_677 // Vol. 1, page 15 (originally a 322)
  };

  /**
   * @brief Builds the chord by intervals of third starting from the specified degree.
   *
   * @param scale The scale on which the chord has to be built.
   * @param degree The degree of the scale on which the chord has to be built.
   * @param numOfNotesInChord How many notes the chord should have.
   * @param intervalBetweenNotes The interval between the notes of the chord (use dedicated enumerative in `Interval`).
   **/
  static Chord harmoniseScaleDegree (const Scale& scale, const Degree& degree, size_t numOfNotesInChord, const Interval& intervalBetweenNotes);

  /**
   * @brief Determines MSRP using the specified `scale` and `sequence`, builds harmonisation and
   * returns a vector of `Chord`s.
   */
  static std::vector<Chord> harmoniseScaleUsingMsrp (const Scale& scale, const IntervallicSequence_enum& sequence);

  /**
   * @brief Harmonises the given scale according to the specified sequence.
   *
   * @param scale The scale to be harmonised.
   * @param sequence The required sequence (for example, 3F75 means that the fundamental goes to the third, the third goes to the fundamental etc.)
   * @param cycle The required harmonisation cycle (for example, in C major, `byThirds` means that the first chord is Cmaj7, the second is Em7, the third is G7, etc.)
   **/
  static std::vector<Chord> functionalHarmony(const Scale& scale, const size_t numOfNotesInChord, const std::array<Note::Function, Constants::numOfNotesInHeptatonicScale> &sequence, const Cycle_enum& cycle = Cycle_enum::bySeconds, const Interval& interval = Interval(Interval::enum_t::third));

  static const std::map<Cycle_enum, std::string>& getMap(void);
  static const std::string getCycleTypeAsString(const Cycle_enum cycle);

private:
  static void completeFinalHarmonisation(const std::vector<Chord> &baseHarmonisation, std::vector<Chord> &finalHarmonisation, const std::array<Note::Function, Constants::numOfNotesInHeptatonicScale> &functionalSequence);
  static const std::map<Cycle_enum, std::string> m_enumToString; // Serve per poter automatizzare l'inizializzazione dei valori della combo box nel constructor di `MainWindow`
};

#endif // CHORDBUILDER_HPP