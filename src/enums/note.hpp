#ifndef NOTE_HPP
#define NOTE_HPP

#include <string>
#include "alteration.hpp"
#include "chromaticpitch.hpp"
#include "degree.hpp"
#include "naturalnote.hpp"
#include "octave.hpp"

class Note
{
public:
  enum class Function
  {
    fundamental = 0,
    second,
    third,
    fourth,
    fifth,
    sixth,
    seventh,

    none
  };

  explicit Note(const int midiPitch) noexcept;
  explicit Note(const NaturalNote& basePitch, const Alteration& alteration, const Octave& octave = Octave(Octave::enum_t::fifth)) noexcept;

  NaturalNote     getBasePitch (void) const noexcept;
  Alteration      getAlteration(void) const noexcept;
  ChromaticPitch  getFinalPitch(void) const noexcept;
  int             getMidiPitch (void) const noexcept;
  Octave          getOctave    (void) const noexcept;
  Function        getFunction  (void) const noexcept;
  std::string     getName      (void) const noexcept;

  // TODO: è il caso di offrire un solo metodo `transpose` anziché tutti questi setter?
  // TODO: oppure rimuovere tutti i setter e imporre che, al bisogno, una `Note` venga sovrascritta da un'altra `Note`, dal momento che i membri dati sono semplici valori integrali?
  void  setBasePitch                (const NaturalNote&     basePitch)  noexcept;
  void  setBasePitchAndRecalculate  (const NaturalNote&     basePitch)  noexcept;
  void  setAlteration               (const Alteration&      alteration) noexcept;
  void  setAlterationAndRecalculate (const Alteration&      alteration) noexcept; // New alteration is calculated as a difference with respect to the previous one. Also works with unusual notes such as Cbb or B##.
  void  setFinalPitch               (const ChromaticPitch&  finalPitch) noexcept;
  void  setFinalPitchAndRecalculate (const ChromaticPitch&  finalPitch) noexcept;
  void  setMidiPitch                (const int              midiPitch)  noexcept;
  void  setMidiPitchAndRecalculate  (const int              midiPitch)  noexcept; // When changing the MIDI pitch of a note, if the final pitch is an altered note, the alteration is always interpreted as a sharp
  void  setOctave                   (const Octave&          octave)     noexcept;
  void  setOctaveAndRecalculate     (const Octave&          octave)     noexcept; // Octave transposition and recalculation.
  void  setFunction                 (const Function&        function)   noexcept;
  void  setFunction                 (const int              function)   noexcept; // 1 = fundamental; 2 = second; etc.
  void  setName                     (const std::string&     name);

  operator int() const noexcept;

private:
  NaturalNote     m_basePitch;   // Between 0 and 11; must only contain unaltered notes
  Alteration      m_alteration;  // Usually between -2 (double flat) and +2 (double sharp), but it could theoretically go even further
  ChromaticPitch  m_finalPitch;  // Between 0 and 11; the result of the sum between m_basePitch and m_alteration
  int             m_midiPitch;   // Between 0 and 127; MIDI absolute pitch
  Octave          m_octave;      // TODO: implementare ==> Note's original octave; stays the same even in case of alteration (for example, B#5 is enharmonically C6, but `m_octave` stays 5)
  Function        m_functionInChord; // The function of the note in the chord, if any (i.e. fundamental, third, fifth etc.)
  std::string     m_name;        // Note's name as a string // TODO: vale la pena di usare invece un array con numero massimo di caratteri?

#ifndef NDEBUG
  friend class Test_Note_Constructor_1_Test; // See test source file for info
  friend class Test_Note_Constructor_2_Test;
  friend class Test_Note_setBasePitch_Test;
#endif // NDEBUG
};

#endif // NOTE_HPP