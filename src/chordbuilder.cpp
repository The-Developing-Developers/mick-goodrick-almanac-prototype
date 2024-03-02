#include "chordbuilder.hpp"
#include "constants.hpp"
#include "interval.hpp"

const std::map<ChordBuilder::Cycle_enum, std::string> ChordBuilder::m_enumToString
{
  {Cycle_enum::bySeconds, "By Seconds"},
  {Cycle_enum::byThirds, "By Thirds"},
  {Cycle_enum::byFourths, "By Fourths"},
  {Cycle_enum::byFifths, "By Fifths"},
  {Cycle_enum::bySixths, "By Sixths"},
  {Cycle_enum::bySevenths, "By Sevenths"}
};


Chord ChordBuilder::harmoniseScaleDegree(const Scale& scale, const Degree& degree, size_t numOfNotesInChord, const Interval& intervalBetweenNotes)
{
  // TODO: inserire sanity check su `degree` (da 1 a 7 compresi)? `std::vector` solleva già un'eccezione in caso di indicizzazione sbagliata
  std::vector<Note> tempChord;
  size_t index = degree;

  for (size_t i = 0; i != numOfNotesInChord; ++i)
  {
    Note currentNote(scale.getNoteInScale(index));
    currentNote.setFunction((i * intervalBetweenNotes % Constants::numOfNotesInHeptatonicScale) + 1);
    tempChord.push_back(currentNote);
    index = (index + intervalBetweenNotes) % scale.getScaleSize();
  }

  return tempChord;
}


/**
 * @brief Sequences of intervals used in the Almanac to build a Melodic Strand Replication Procedure
 * for a certain scale and cycle. They correct sequence is selected based on the user's choice when
 * calling `harmoniseScaleUsingMsrp`, and it is used to build the Melodic Strand Replication Procedure.
 */
namespace IntervallicSequences
{
  // const std::array<Interval, Constants::numOfNotesInQuadriad> sequence_2222{Interval(Interval::enum_t::second), Interval(Interval::enum_t::second),  Interval(Interval::enum_t::second),  Interval(Interval::enum_t::second)}; // TODO: questa sequenza porta a una periodicità di una sola nota nella costruzione dell'MSRP!
  const std::array<Interval, Constants::numOfNotesInQuadriad> sequence_1117{Interval(Interval::enum_t::unison), Interval(Interval::enum_t::unison),   Interval(Interval::enum_t::unison),   Interval(Interval::enum_t::seventh)};
  const std::array<Interval, Constants::numOfNotesInQuadriad> sequence_1177{Interval(Interval::enum_t::unison), Interval(Interval::enum_t::unison),   Interval(Interval::enum_t::seventh),   Interval(Interval::enum_t::seventh)};
  const std::array<Interval, Constants::numOfNotesInQuadriad> sequence_1777{Interval(Interval::enum_t::unison), Interval(Interval::enum_t::seventh),  Interval(Interval::enum_t::seventh),  Interval(Interval::enum_t::seventh)};

  const std::array<Interval, Constants::numOfNotesInTriad> sequence_445 {Interval(Interval::enum_t::fourth), Interval(Interval::enum_t::fourth),  Interval(Interval::enum_t::fifth)};
  const std::array<Interval, Constants::numOfNotesInTriad> sequence_677 {Interval(Interval::enum_t::sixth),  Interval(Interval::enum_t::seventh), Interval(Interval::enum_t::seventh)};
  // Insert here other patterns from the Almanac
};


/**
 * @brief These sequences describe how a note should move to the next chord, in a context of functional voice leading. For example, `sequence_F35_3F5` means that the
 **/
namespace FunctionalSequences
{
  const std::array<Note::Function, Constants::numOfNotesInHeptatonicScale> sequence_F35_F53 {Note::Function::fundamental, Note::Function::none, Note::Function::fifth,        Note::Function::none,         Note::Function::third,        Note::Function::none,   Note::Function::none};
  const std::array<Note::Function, Constants::numOfNotesInHeptatonicScale> sequence_F35_3F5 {Note::Function::third,       Note::Function::none, Note::Function::fundamental,  Note::Function::none,         Note::Function::fifth,        Note::Function::none,   Note::Function::none};

  const std::array<Note::Function, Constants::numOfNotesInHeptatonicScale> sequence_F357_F375 {Note::Function::fundamental, Note::Function::none, Note::Function::third,        Note::Function::none,         Note::Function::seventh,      Note::Function::none,   Note::Function::fifth};
  const std::array<Note::Function, Constants::numOfNotesInHeptatonicScale> sequence_F357_375F {Note::Function::third,       Note::Function::none, Note::Function::seventh,      Note::Function::none,         Note::Function::fifth,        Note::Function::none,   Note::Function::fundamental};
  const std::array<Note::Function, Constants::numOfNotesInHeptatonicScale> sequence_F357_73F5 {Note::Function::seventh,     Note::Function::none, Note::Function::third,        Note::Function::none,         Note::Function::fundamental,  Note::Function::none,   Note::Function::fifth};
  const std::array<Note::Function, Constants::numOfNotesInHeptatonicScale> sequence_F357_357F {Note::Function::third,       Note::Function::none, Note::Function::fifth,        Note::Function::none,         Note::Function::seventh,      Note::Function::none,   Note::Function::fundamental};
  const std::array<Note::Function, Constants::numOfNotesInHeptatonicScale> sequence_F347_347F {Note::Function::third,       Note::Function::none, Note::Function::fourth,       Note::Function::seventh,      Note::Function::none,         Note::Function::none,   Note::Function::fundamental};

  const std::array<Note::Function, Constants::numOfNotesInHeptatonicScale> sequence_F3467_67F34 {Note::Function::sixth,       Note::Function::none, Note::Function::seventh,      Note::Function::fundamental,  Note::Function::none,         Note::Function::third,  Note::Function::fourth};

  const std::array<Note::Function, Constants::numOfNotesInHeptatonicScale> sequence_F234567_465273F {Note::Function::fourth, Note::Function::sixth, Note::Function::fifth,      Note::Function::second,  Note::Function::seventh, Note::Function::third,  Note::Function::fundamental};
  // Insert here other patterns from the Almanac
};


/**
 * @brief Used to determine the correct sequence of the patterns (A-B-C or A-C-B) derived from the
 * Melodic Strand Replication Procedure.
 */
enum class msrpType_enum
{
  type_135_ABC,
  type_153_ACB,

  type_1357_ABCD,
  type_1537_ACBD,
  type_1753_ADCB,

  undetermined
};


const std::map<ChordBuilder::Cycle_enum, std::string>& ChordBuilder::getMap(void)
{
  return m_enumToString;
}


const std::string ChordBuilder::getCycleTypeAsString(const ChordBuilder::Cycle_enum cycle)
{
  return m_enumToString.at(cycle);
}


std::vector<Chord> ChordBuilder::functionalHarmony(const Scale& scale, const size_t numOfNotesInChord, const std::array<Note::Function, Constants::numOfNotesInHeptatonicScale> &sequence, const ChordBuilder::Cycle_enum& cycle, const Interval& interval)
{
  std::vector<Chord>  baseHarmonisation;

  // Build (by thirds) the `baseHarmonisation` of the scale, either by triads or quadriads depending on `numOfNotesInChord, with the
  // specified `cycle` and standard functional voicing (F-3-5 or F-3-5-7) for all chords; used later to build the `finalHarmonisation`.
  for (size_t i = 0; i != Constants::numOfNotesInHeptatonicScale; ++i)
  {
    const size_t degree = 1 + ((i * static_cast<size_t>(cycle)) % (Constants::numOfNotesInHeptatonicScale)); // The degree to be harmonised is calculated based on the specified `cycle`, but also considering the usual modulo 7 (there are only seven degrees in a heptatonic scale), and the fact that the starting degree must always be `1` (the first degree).
    baseHarmonisation.push_back(harmoniseScaleDegree(scale, Degree(degree), numOfNotesInChord, interval));
  }

  std::vector<Chord> finalHarmonisation; // It will be built from the `baseHarmonisation`, based on the `sequence` type
  finalHarmonisation.push_back(baseHarmonisation[0]); // The first chord of the `finalHarmonisation` does not need to be modified (it is always in the form F-3-5 or F-3-5-7)
  completeFinalHarmonisation(baseHarmonisation, finalHarmonisation, sequence); // Build the remaining chords in `finalHarmonisation`

  return finalHarmonisation;
}

std::vector<Chord> ChordBuilder::harmoniseScaleUsingMsrp(const Scale& scale, const IntervallicSequence_enum& sequence)
{
  std::vector<Chord> resultVec;
  std::vector<Interval> sequence_type; // It can be a sequence of three or four notes, depending on the type of harmonisation (triad or quadriad)
  std::vector<Note> msrp; // Melodic Strand Replication Procedure
  std::vector<std::vector<Note>> patterns; // The patterns that constitute a MSRP are stored here. A vector is used to manage both MSRPs built from triads (three patterns) and MSRPs built from quadriads (four patterns)
  msrpType_enum msrpType = msrpType_enum::undetermined;
  msrp.push_back(scale.getNoteInScale(Degree(Degree::enum_t::first))); // First note is inserted here for simplicity and convenience

  // Prepare the `sequence_type` based on the user's choice
  switch (sequence)
  {
    case IntervallicSequence_enum::sequence_1117:
      for (size_t i = 0; i != Constants::numOfNotesInQuadriad; ++i)
        sequence_type.push_back(IntervallicSequences::sequence_1117[i]);
      break;

    case IntervallicSequence_enum::sequence_1177:
      for (size_t i = 0; i != Constants::numOfNotesInQuadriad; ++i)
        sequence_type.push_back(IntervallicSequences::sequence_1177[i]);
      break;

    case IntervallicSequence_enum::sequence_1777:
      for (size_t i = 0; i != Constants::numOfNotesInQuadriad; ++i)
        sequence_type.push_back(IntervallicSequences::sequence_1777[i]);
      break;

    case IntervallicSequence_enum::sequence_445:
      for (size_t i = 0; i != Constants::numOfNotesInTriad; ++i)
        sequence_type.push_back(IntervallicSequences::sequence_445[i]);
      break;

    case IntervallicSequence_enum::sequence_677:
      for (size_t i = 0; i != Constants::numOfNotesInTriad; ++i)
        sequence_type.push_back(IntervallicSequences::sequence_677[i]);
      break;

    default:
      break;
  }

  // Build the MSRP by applying the `sequence_type` to the specified `scale`. The MSRP is composed
  // of `numOfNotesInHeptatonicScale` times the number of notes in the chord (triad, quadriad etc.) `Note`s.
  // For example, a MSRP built on a heptatonic scale harmonised by triads is composed of 7 * 3 = 21
  // `Note`s. The 22nd `Note` is just the repetition of the first one.
  int index = 0;

  for (size_t i = 0; i != Constants::numOfNotesInHeptatonicScale; ++i)
  {
    for (size_t j = 0; j != sequence_type.size(); ++j) // Automatically manages sequences of three intervals (for triads) and four intervals (for quadriads)
      msrp.push_back(scale.getNoteInScale((index += sequence_type[j]) % Constants::numOfNotesInHeptatonicScale));
  }

  // Now that the MSRP is ready, the patterns can be built from the MSRP. Pattern A is built with
  // notes [0, 7) of the MSRP; pattern B is built with notes [7, 14) of the MSRP, and so on. This
  // loop automatically manages patterns arising from triads (three patterns) as well as patterns
  // arising from quadriads (four patterns).
  index = 0;
  for (size_t i = 0; i != sequence_type.size(); ++i)
  {
    const auto begin = msrp.cbegin() + index;
    index += Constants::numOfNotesInHeptatonicScale;
    const auto end   = msrp.cbegin() + index;
    patterns.emplace_back(std::vector<Note>(begin, end));
  }

  // By analysing the starting `Note` of Pattern B, it is possible to determine whether the sequence
  // of Patterns is A-B-C (i.e. 1-3-5) or A-C-B (i.e. 1-5-3). If the starting `Note` is the third
  // degree of `scale`, then Pattern B starts with the third degree, therefore the sequence is A-B-C
  // (i.e. 1-3-5). Analogous reasoning if the starting note is the fifth degree of `scale`. Same for
  // quadriads, which have four patterns. The first note of the MSRP (and, as a consequence, of
  // Pattern A) is always the tonic, therefore Pattern A does not need to be inspected.
  constexpr size_t pattern_A_idx = 0;
  constexpr size_t pattern_B_idx = 1;
  constexpr size_t pattern_C_idx = 2;
  constexpr size_t pattern_D_idx = 3;
  constexpr size_t pattern_firstNote_idx = 0;
  switch (patterns.size())
  {
    case 3: // Triads
      if (patterns[pattern_B_idx][pattern_firstNote_idx] == scale.getNoteInScale(Degree(Degree::enum_t::third))) // to compare whether two `Note`s are equal, the internal conversion operator to `int` is used
        msrpType = msrpType_enum::type_135_ABC;
      else if (patterns[pattern_B_idx][pattern_firstNote_idx] == scale.getNoteInScale(Degree(Degree::enum_t::fifth)))
        msrpType = msrpType_enum::type_153_ACB;
      break;

    case 4: // Quadriads
      if (    patterns[pattern_B_idx][pattern_firstNote_idx] == scale.getNoteInScale(Degree(Degree::enum_t::third))
          &&  patterns[pattern_C_idx][pattern_firstNote_idx] == scale.getNoteInScale(Degree(Degree::enum_t::fifth))
          &&  patterns[pattern_D_idx][pattern_firstNote_idx] == scale.getNoteInScale(Degree(Degree::enum_t::seventh)))
        msrpType = msrpType_enum::type_1357_ABCD;

      else if (     patterns[pattern_B_idx][pattern_firstNote_idx] == scale.getNoteInScale(Degree(Degree::enum_t::fifth))
                &&  patterns[pattern_C_idx][pattern_firstNote_idx] == scale.getNoteInScale(Degree(Degree::enum_t::third))
                &&  patterns[pattern_D_idx][pattern_firstNote_idx] == scale.getNoteInScale(Degree(Degree::enum_t::seventh)))
        msrpType = msrpType_enum::type_1537_ACBD;

      else if (     patterns[pattern_B_idx][pattern_firstNote_idx] == scale.getNoteInScale(Degree(Degree::enum_t::seventh))
                &&  patterns[pattern_C_idx][pattern_firstNote_idx] == scale.getNoteInScale(Degree(Degree::enum_t::fifth))
                &&  patterns[pattern_D_idx][pattern_firstNote_idx] == scale.getNoteInScale(Degree(Degree::enum_t::third)))
        msrpType = msrpType_enum::type_1753_ADCB;
      break;

    default:
      break;
  }

  // Build the resulting vector of chords based on the determined patterns sequence (A-B-C or A-C-B
  // for triads, or A-B-C-D, A-C-B-D, etc. for quadriads)
  switch (msrpType)
  {
    case msrpType_enum::type_135_ABC:
      for (size_t i = 0; i != Constants::numOfNotesInHeptatonicScale; ++i)
        resultVec.push_back(Chord({patterns[pattern_A_idx][i], patterns[pattern_B_idx][i], patterns[pattern_C_idx][i]}));
      break;

    case msrpType_enum::type_153_ACB:
      for (size_t i = 0; i != Constants::numOfNotesInHeptatonicScale; ++i)
        resultVec.push_back(Chord({patterns[pattern_A_idx][i], patterns[pattern_C_idx][i], patterns[pattern_B_idx][i]}));
      break;

    case msrpType_enum::type_1357_ABCD:
      for (size_t i = 0; i != Constants::numOfNotesInHeptatonicScale; ++i)
        resultVec.push_back(Chord({patterns[pattern_A_idx][i], patterns[pattern_B_idx][i], patterns[pattern_C_idx][i], patterns[pattern_D_idx][i]}));
      break;

    case msrpType_enum::type_1537_ACBD:
      for (size_t i = 0; i != Constants::numOfNotesInHeptatonicScale; ++i)
        resultVec.push_back(Chord({patterns[pattern_A_idx][i], patterns[pattern_C_idx][i], patterns[pattern_B_idx][i], patterns[pattern_D_idx][i]}));
      break;

    case msrpType_enum::type_1753_ADCB:
      for (size_t i = 0; i != Constants::numOfNotesInHeptatonicScale; ++i)
        resultVec.push_back(Chord({patterns[pattern_A_idx][i], patterns[pattern_D_idx][i], patterns[pattern_C_idx][i], patterns[pattern_B_idx][i]}));
      break;

    default:
      break;
  }

  return resultVec;
}

/**
 * @brief completes the `finalHarmonisation`. The `baseHarmonisation` is the usual, standard harmonisation (by thirds or fourths)
 * of a heptatonic scale. `finalHarmonisation` is the harmonisation of the same scale by using the specified `functionalSequence`.
 **/
void ChordBuilder::completeFinalHarmonisation(const std::vector<Chord> &baseHarmonisation, std::vector<Chord> &finalHarmonisation, const std::array<Note::Function, Constants::numOfNotesInHeptatonicScale> &functionalSequence)
{
  const     size_t numOfNotesInChord  = baseHarmonisation[0].getSize();
  constexpr size_t numOfChordsToBuild = Constants::numOfNotesInHeptatonicScale; // TODO: il numero di note della scala andrà moltiplicato per il numero di voci nell'accordo meno il numero di voci che restano ferme (da verificare).

  for (size_t i = 0; i != numOfChordsToBuild; ++i)
  {
    Chord nextChord;
    const Chord currentChord(finalHarmonisation[i]);
    const size_t nextChordInBaseHarmonisation_idx = (i + 1) % Constants::numOfNotesInHeptatonicScale; // modulo because the eighth chord is identical to the first one

    for (size_t j = 0; j != numOfNotesInChord; ++j)
    {
      // For example: if the first note of the currently analysed chord (`currentChord`) in `finalHarmonisation` is the
      // fundamental, the first note of the `nextChord` must be (functionally) whatever is contained in `functionalSequence[0])`
      if (currentChord.getNote(j).getFunction() == Note::Function::fundamental)
        nextChord.push_back(Note(baseHarmonisation[nextChordInBaseHarmonisation_idx].getNote(functionalSequence[0])));
      else if (currentChord.getNote(j).getFunction() == Note::Function::second)
        nextChord.push_back(Note(baseHarmonisation[nextChordInBaseHarmonisation_idx].getNote(functionalSequence[1])));
      else if (currentChord.getNote(j).getFunction() == Note::Function::third)
        nextChord.push_back(Note(baseHarmonisation[nextChordInBaseHarmonisation_idx].getNote(functionalSequence[2])));
      else if (currentChord.getNote(j).getFunction() == Note::Function::fourth)
        nextChord.push_back(Note(baseHarmonisation[nextChordInBaseHarmonisation_idx].getNote(functionalSequence[3])));
      else if (currentChord.getNote(j).getFunction() == Note::Function::fifth)
        nextChord.push_back(Note(baseHarmonisation[nextChordInBaseHarmonisation_idx].getNote(functionalSequence[4])));
      else if (currentChord.getNote(j).getFunction() == Note::Function::sixth)
        nextChord.push_back(Note(baseHarmonisation[nextChordInBaseHarmonisation_idx].getNote(functionalSequence[5])));
      else if (currentChord.getNote(j).getFunction() == Note::Function::seventh)
        nextChord.push_back(Note(baseHarmonisation[nextChordInBaseHarmonisation_idx].getNote(functionalSequence[6])));
    }

    finalHarmonisation.push_back(nextChord);
  }
}