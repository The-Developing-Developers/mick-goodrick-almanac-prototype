#ifndef CHORD_HPP
#define CHORD_HPP

#include <vector>
#include <string>
#include "note.hpp"

// TODO: ci sono alcune cose in comune con la classe `Scale`. Serve una superclasse?
class Chord
{
public:
  Chord(void) = default;
  Chord(const std::initializer_list<Note>& notes);
  Chord(const std::vector<Note>&           notes);

  Chord& push_back(const Note& note);
  void   clear    (void);

  size_t  getSize(void)                                   const noexcept;
  Note    getNote(const Degree&         degree)           const noexcept;
  Note    getNote(const int             index_zero_based) const noexcept;
  Note    getNote(const Note::Function& function)         const noexcept;

  std::string printChord(void) const;

private:
  std::vector<Note> m_notes;

#ifndef NDEBUG
  friend class Test_Chord_Constructors_Test; // See test source file for info
#endif // NDEBUG
};

#endif // CHORD_HPP