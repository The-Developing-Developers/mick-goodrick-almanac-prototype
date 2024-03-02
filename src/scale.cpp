#include <iostream>
#include <map>
#include <algorithm>

#include "constants.hpp"
#include "degree.hpp"
#include "distanceinsemitones.hpp"
#include "note.hpp"
#include "scale.hpp"

const std::map<Scale::ScaleType, std::string> Scale::m_enumToString
{
  {ScaleType::Major, "Major"},
  {ScaleType::Minor_Natural, "Minor Natural"},
  {ScaleType::Minor_Harmonic, "Minor Harmonic"},
  {ScaleType::Minor_Melodic, "Minor Melodic"},
  {ScaleType::Minor_Pentatonic, "Minor Pentatonic"},

  {ScaleType::Dorian, "Dorian"},
  {ScaleType::Phrygian, "Phrygian"},
  {ScaleType::Lydian, "Lydian"},
  {ScaleType::Mixolydian, "Mixolydian"},
  {ScaleType::Locrian, "Locrian"},

  {ScaleType::Hexatonic, "Hexatonic"}
};

/**
 * @brief The composition of various musical scales is described here in terms of intervals between the notes of the scales
 */
namespace ScaleComposition
{
  const std::vector<DistanceInSemitones> m_majorScaleComposition
  {
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone)
  };

  const std::vector<DistanceInSemitones> m_minorNaturalScaleComposition
  {
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone)
  };

  const std::vector<DistanceInSemitones> m_minorHarmonicScaleComposition
  {
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone),
    DistanceInSemitones(DistanceInSemitones::enum_t::ToneAndHalf)
  };

  const std::vector<DistanceInSemitones> m_minorMelodicScaleComposition
  {
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone)
  };

  const std::vector<DistanceInSemitones> m_minorPentatonicScaleComposition
  {
    DistanceInSemitones(DistanceInSemitones::enum_t::ToneAndHalf),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::ToneAndHalf)
  };

  const std::vector<DistanceInSemitones> m_hexatonicScaleComposition
  {
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone)
  };

  const std::vector<DistanceInSemitones> m_dorianScaleComposition
  {
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone)
  };

  const std::vector<DistanceInSemitones> m_phrygianScaleComposition
  {
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone)
  };

  const std::vector<DistanceInSemitones> m_lydianScaleComposition
  {
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone)
  };

  const std::vector<DistanceInSemitones> m_mixolydianScaleComposition
  {
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone)
  };

  const std::vector<DistanceInSemitones> m_locrianScaleComposition
  {
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Semitone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
    DistanceInSemitones(DistanceInSemitones::enum_t::Tone),
  };
};

// Needed to calculate the base name of the next note when creating heptatonic scales
const std::vector<NaturalNote> baseNames
{
  NaturalNote(NaturalNote::enum_t::C),
  NaturalNote(NaturalNote::enum_t::D),
  NaturalNote(NaturalNote::enum_t::E),
  NaturalNote(NaturalNote::enum_t::F),
  NaturalNote(NaturalNote::enum_t::G),
  NaturalNote(NaturalNote::enum_t::A),
  NaturalNote(NaturalNote::enum_t::B)
};

const std::map<NaturalNote, std::string> chromaticPitchToString
{
  {baseNames[0], std::string("C")},
  {baseNames[1], std::string("D")},
  {baseNames[2], std::string("E")},
  {baseNames[3], std::string("F")},
  {baseNames[4], std::string("G")},
  {baseNames[5], std::string("A")},
  {baseNames[6], std::string("B")}
};


Scale::Scale(const Note& fundamental, const ScaleType& scaleType)
  : m_scaleType(scaleType)
{
  // Determine the scale type and its intervallic composition
  switch (scaleType)
  {
    case Scale::ScaleType::Major:
      composeHeptatonicScale(fundamental, ScaleComposition::m_majorScaleComposition);
      break;

    case Scale::ScaleType::Minor_Natural:
      composeHeptatonicScale(fundamental, ScaleComposition::m_minorNaturalScaleComposition);
      break;

    case Scale::ScaleType::Minor_Harmonic:
      composeHeptatonicScale(fundamental, ScaleComposition::m_minorHarmonicScaleComposition);
      break;

    case Scale::ScaleType::Minor_Melodic:
      composeHeptatonicScale(fundamental, ScaleComposition::m_minorMelodicScaleComposition);
      break;

    case Scale::ScaleType::Dorian:
      composeHeptatonicScale(fundamental, ScaleComposition::m_dorianScaleComposition);
      break;

    case Scale::ScaleType::Phrygian:
      composeHeptatonicScale(fundamental, ScaleComposition::m_phrygianScaleComposition);
      break;

    case Scale::ScaleType::Lydian:
      composeHeptatonicScale(fundamental, ScaleComposition::m_lydianScaleComposition);
      break;

    case Scale::ScaleType::Mixolydian:
      composeHeptatonicScale(fundamental, ScaleComposition::m_mixolydianScaleComposition);
      break;

    case Scale::ScaleType::Locrian:
      composeHeptatonicScale(fundamental, ScaleComposition::m_locrianScaleComposition);
      break;

    case Scale::ScaleType::Minor_Pentatonic:
      // TODO: da implementare
      // composePentatonicScale(fundamental, ScaleComposition::m_minorPentatonicScaleComposition);
      throw std::runtime_error("Scale::ScaleType not yet implemented");
      break;

    case Scale::ScaleType::Hexatonic:
      // TODO: da implementare
      // composeHexatonicScale(fundamental, ScaleComposition::m_hexatonicScaleComposition;
      throw std::runtime_error("Scale::ScaleType not yet implemented");
      break;

    default:
      throw std::runtime_error("Scale::ScaleType not recognised");
      break;
  }
}

/**
 * @brief All the notes in a heptatonic scale must have a different, increasing base name. No two
 * names can be repeated.
 **/
void Scale::composeHeptatonicScale(const Note& fundamental, const std::vector<DistanceInSemitones>& scaleStructure)
{
  Note fundamental_copy(fundamental); // This copy is not necessary. It is used to keep the function signature with a reference to `const` for both parameters
  assignNoteName(fundamental_copy);
  m_notes.push_back(fundamental_copy); // The fundamental must be inserted before the `for` loop, because it is the basis for the construction of the remaining notes

  for (int i = 0; i != Constants::numOfNotesInHeptatonicScale - 1; ++i) // `- 1` to skip the fundamental, because it is already in the vector
  {
    const Note& prevNote(m_notes[i]);
    auto prevNoteBaseNameIter = std::find(baseNames.cbegin(), baseNames.cend(), prevNote.getBasePitch()); // Find previous note's base name
    auto currNoteBaseNameIter = prevNoteBaseNameIter + 1; // Find current note's base name based on the previous one
    if (currNoteBaseNameIter == baseNames.cend())
      currNoteBaseNameIter = baseNames.cbegin(); // Wrap around base name if necessary
    const int currNoteBasePitch   = *currNoteBaseNameIter;
    const int currNoteFinalPitch  = (prevNote.getFinalPitch() + scaleStructure[i]) % Constants::numOfSemitonesInOctave; // Wrap around final pitch if necessary
    int alteration_temp = currNoteFinalPitch - currNoteBasePitch;

    // This hack is necessary for unusual scales, such as Bbb, where the passage from BBb to Cb is
    // problematic, because when calculating Cb, `currNoteFinalPitch - currNoteBasePitch` (i.e. the
    // number of alterations) gives `11`, since `currNoteBasePitch` for Cb has just wrapped around
    // from `11` (Bbb, previous note) to `0` (Cb, current note). Therefore, the wrapping-around must
    // be removed. Something analogous happens between A# and B#, but with the opposite sign.
    constexpr int maxNumOfAllowedAlterations = 3; // Arbitrarily chosen
    if (alteration_temp > maxNumOfAllowedAlterations)
      alteration_temp -= Constants::numOfSemitonesInOctave;
    else if (alteration_temp < -maxNumOfAllowedAlterations)
      alteration_temp += Constants::numOfSemitonesInOctave;

    Alteration currNoteAlteration = Alteration(alteration_temp);
    Note currNote(NaturalNote(currNoteBasePitch), Alteration(currNoteAlteration), Octave(prevNote.getOctave())); // Now the alteration and base pitch of the currently analysed note are known, and can be set
    assignNoteName(currNote);
    m_notes.push_back(currNote);
  }
}

void Scale::assignNoteName(Note& note)
{
  std::string tempString;
  tempString = chromaticPitchToString.at(note.getBasePitch()); // Assign note's base name
  const int numOfAlterations = std::abs(note.getAlteration());

  // Assign note's alterations, if any
  for (int i = 0; i != numOfAlterations; ++i)
  {
    if (note.getAlteration() < 0)
      tempString.push_back('b');
    else
      tempString.push_back('#');
  }

  note.setName(tempString);
}

Note Scale::getNoteInScale(const Degree& degree) const
{
  return m_notes.at(degree);
}

Note Scale::getNoteInScale(const int index_zero_based) const
{
  return m_notes.at(index_zero_based);
}

const std::map<Scale::ScaleType, std::string>& Scale::getMap(void)
{
  return m_enumToString;
}

// TODO: debug
void Scale::printScale(void)
{
  std::cout << "Scale type: ";
  switch (m_scaleType)
  {
    case Scale::ScaleType::Major:
      std::cout << "Major\n";
      break;

    case Scale::ScaleType::Minor_Natural:
      std::cout << "Minor Natural\n";
      break;

    case Scale::ScaleType::Minor_Harmonic:
      std::cout << "Minor Harmonic\n";
      break;

    case Scale::ScaleType::Minor_Melodic:
      std::cout << "Minor Melodic\n";
      break;

    case Scale::ScaleType::Dorian:
      std::cout << "Dorian\n";
      break;

    case Scale::ScaleType::Phrygian:
      std::cout << "Phrygian\n";
      break;

    case Scale::ScaleType::Lydian:
      std::cout << "Lydian\n";
      break;

    case Scale::ScaleType::Mixolydian:
      std::cout << "Mixolydian\n";
      break;

    case Scale::ScaleType::Locrian:
      std::cout << "Locrian\n";
      break;

    case Scale::ScaleType::Minor_Pentatonic:
      std::cout << "Minor Pentatonic\n";
      break;

    case Scale::ScaleType::Hexatonic:
      std::cout << "Hexatonic\n";
      break;

    default:
      std::cerr << "Scale not recognised\n";
      break;
  }

  std::cout << "Pitches:\n\t";

  for (const auto& note : m_notes)
    std::cout << note << '\t';
  std::cout << "\n\t";
  for (const auto& note : m_notes)
    std::cout << note.getName() << '\t';
  std::cout << '\n';
}

size_t Scale::getScaleSize(void) const
{
  return m_notes.size();
}

Scale::ScaleType Scale::getScaleType(void) const noexcept
{
  return m_scaleType;
}

const std::string Scale::getScaleTypeAsString(const Scale::ScaleType scaleType)
{
  return m_enumToString.at(scaleType);
}