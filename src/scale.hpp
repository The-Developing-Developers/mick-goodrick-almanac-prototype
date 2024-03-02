#ifndef SCALE_HPP
#define SCALE_HPP

#include <map>
#include <string>
#include <vector>

class Degree;
class Note;
class DistanceInSemitones;

/**
 * @brief Build a scale by passing as arguments the fundamental note and the type of scale to be built.
 */
class Scale
{
public:
  enum class ScaleType
  {
    Major = 0,
    Minor_Natural,
    Minor_Harmonic,
    Minor_Melodic,
    Minor_Pentatonic,

    Dorian,
    Phrygian,
    Lydian,
    Mixolydian,
    Locrian,

    Hexatonic
  };

  Scale(const Note& fundamental, const ScaleType& scaleType);

  Note        getNoteInScale      (const Degree& degree)           const;
  Note        getNoteInScale      (const int     index_zero_based) const;
  size_t      getScaleSize        (void)                           const;
  ScaleType   getScaleType        (void)                           const noexcept;

  static const std::string getScaleTypeAsString(const ScaleType scaleType);
  static const std::map<ScaleType, std::string>& getMap(void);

  void printScale(void); // TODO: debug

private:
  ScaleType         m_scaleType;
  std::vector<Note> m_notes;

  static const std::map<ScaleType, std::string> m_enumToString;

  void assignNoteName(Note& note);
  void composeHeptatonicScale(const Note& fundamental, const std::vector<DistanceInSemitones>& scaleStructure);

#ifndef NDEBUG
  friend class Test_Scale_Constructors_Test;  // See test source file for info
  friend class Test_Scale_Methods_Test;       // See test source file for info
#endif // NDEBUG
};

#endif // SCALE_HPP