#include "constants.hpp"
#include "note.hpp"

/**
 * @brief In case an altered `Note` is created using this constructor, the alteration(s) is (are) always treated as sharps for simplicity
 * (the correct alteration type can only be deduced if a context is provided, such as a diatonic scale).
 */
Note::Note(const int midiPitch) noexcept
  : m_basePitch (midiPitch % Constants::numOfSemitonesInOctave)
  , m_alteration(Alteration::enum_t::natural)
  , m_finalPitch(m_basePitch)
  , m_midiPitch (midiPitch)
  , m_functionInChord(Function::none)
  , m_octave    (midiPitch / Constants::numOfSemitonesInOctave)
{
  switch (m_finalPitch)
  {
    case static_cast<int>(ChromaticPitch::enum_t::D_Flat):
    case static_cast<int>(ChromaticPitch::enum_t::E_Flat):
    case static_cast<int>(ChromaticPitch::enum_t::G_Flat):
    case static_cast<int>(ChromaticPitch::enum_t::A_Flat):
    case static_cast<int>(ChromaticPitch::enum_t::B_Flat):
      m_basePitch  = m_finalPitch - 1; // for example, the base pitch of a Bb is an A, because here Bb is interpreted as an A#
      m_alteration = Alteration::enum_t::sharp; // The alteration is always considered to be a sharp
      break;

    default:
      // Nothing else to do; everything has been already assigned
      break;
  }
}


Note::Note(const NaturalNote &basePitch, const Alteration &alteration, const Octave& octave) noexcept
  : m_basePitch (basePitch)
  , m_alteration(alteration)
  , m_finalPitch((basePitch + alteration < 0 ? basePitch + alteration + Constants::numOfSemitonesInOctave : basePitch + alteration) % Constants::numOfSemitonesInOctave) // This way, a Cbb or a B## is correctly assigned
  , m_midiPitch (basePitch + octave * Constants::numOfSemitonesInOctave + alteration) // This way, a B## is correctly assigned
  , m_octave    (m_midiPitch / Constants::numOfSemitonesInOctave)
{}


NaturalNote Note::getBasePitch(void) const noexcept
{
  return m_basePitch;
}


Alteration Note::getAlteration(void) const noexcept
{
  return m_alteration;
}


ChromaticPitch Note::getFinalPitch(void) const noexcept
{
  return m_finalPitch;
}


int Note::getMidiPitch(void) const noexcept
{
  return m_midiPitch;
}


Octave Note::getOctave(void) const noexcept
{
  return m_octave;
}


Note::Function Note::getFunction(void) const noexcept
{
  return m_functionInChord;
}


std::string Note::getName(void) const noexcept
{
  return m_name;
}



void Note::setBasePitch(const NaturalNote& basePitch) noexcept
{
  m_basePitch = basePitch;
}


void Note::setBasePitchAndRecalculate(const NaturalNote& basePitch) noexcept
{
  m_basePitch   = basePitch;
  m_alteration  = Alteration::enum_t::natural;
  m_finalPitch  = basePitch;
  m_midiPitch   = m_octave * Constants::numOfSemitonesInOctave + basePitch;
  // Octave does not change
}


void Note::setAlteration(const Alteration& alteration) noexcept
{
  m_alteration = alteration;
}


void Note::setAlterationAndRecalculate(const Alteration& alteration) noexcept
{
  const int difference  = alteration - m_alteration;
  m_alteration          = alteration;
  int tempFinalPitch    = m_finalPitch + difference;
  if (tempFinalPitch < 0)
    tempFinalPitch     += Constants::numOfSemitonesInOctave;
  tempFinalPitch       %= Constants::numOfSemitonesInOctave;
  m_finalPitch          = tempFinalPitch;
  m_midiPitch          += difference; // TODO: attenzione: l'altezza MIDI può solo stare nell'intervallo [0, 127]
  m_octave              = Octave(m_midiPitch / Constants::numOfSemitonesInOctave);
}


void Note::setFinalPitch(const ChromaticPitch& finalPitch) noexcept
{
  m_finalPitch = finalPitch;
}


void Note::setFinalPitchAndRecalculate(const ChromaticPitch& finalPitch) noexcept
{
  // TODO: valutare se questa funzione serve realmente. In caso servisse, occorre memorizzare
  // l'ottava originale della nota piuttosto che quella attuale. Quella attuale si può sempre
  // ricavare facilmente mediante l'altezza MIDI; quella originale serve per calcolare delle
  // modifiche a note inusuali, come ad esempio Cbb5 (che è in realtà un A#4), oppure B##4 (che
  // è in realtà un C#5).
}


void Note::setMidiPitch(const int midiPitch) noexcept
{
  m_midiPitch = midiPitch;
}


void Note::setMidiPitchAndRecalculate(const int midiPitch) noexcept
{
  m_midiPitch   = midiPitch;
  m_octave      = Octave(midiPitch / Constants::numOfSemitonesInOctave);
  m_finalPitch  = midiPitch % Constants::numOfSemitonesInOctave;
  switch (m_finalPitch)
  {
    case static_cast<int>(ChromaticPitch::enum_t::D_Flat):
    case static_cast<int>(ChromaticPitch::enum_t::E_Flat):
    case static_cast<int>(ChromaticPitch::enum_t::G_Flat):
    case static_cast<int>(ChromaticPitch::enum_t::A_Flat):
    case static_cast<int>(ChromaticPitch::enum_t::B_Flat):
      m_basePitch  = m_finalPitch - 1; // for example, the base pitch of a Bb is an A, because here Bb is interpreted as an A#
      m_alteration = Alteration::enum_t::sharp; // The alteration is always considered to be a sharp
      break;

    default:
      m_alteration = Alteration(Alteration::enum_t::natural);
      m_basePitch  = m_finalPitch;
      break;
  }
}


void Note::setOctave(const Octave& octave) noexcept
{
  m_octave = octave;
}


void Note::setOctaveAndRecalculate(const Octave& octave) noexcept
{
  // TODO: per implementare correttamente questa funzione, occorre memorizzare in `m_octave`
  // l'ottava originale della nota, non quella attuale, che si ricava facilmente mediante l'altezza
  // MIDI. Quella originale serve per calcolare delle modifiche a note inusuali, come ad esempio
  // Cbb5 (che è in realtà un A#4), oppure B##4 (che è in realtà un C#5).
  int difference  = octave - m_octave;
  m_midiPitch    += Constants::numOfSemitonesInOctave * difference;
  m_octave        = octave;
}


void Note::setFunction(const Function& function) noexcept
{
  m_functionInChord = function;
}


void Note::setFunction(const int function) noexcept
{
  m_functionInChord = static_cast<Function>(function - 1);
}


void Note::setName(const std::string& name)
{
  m_name = name;
}


Note::operator int() const noexcept
{
  return static_cast<int>(getFinalPitch());
}
