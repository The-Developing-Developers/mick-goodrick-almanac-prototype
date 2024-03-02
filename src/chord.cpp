#include <iostream>
#include <algorithm>
#include "chord.hpp"

Chord::Chord(const std::initializer_list<Note>& notes)
  : m_notes(notes)
{}

Chord::Chord(const std::vector<Note>& notes)
  : m_notes(notes)
{}

Chord& Chord::push_back(const Note& note)
{
  m_notes.push_back(note);
  return *this;
}

void Chord::clear(void)
{
  m_notes.clear();
}

size_t Chord::getSize(void) const noexcept
{
  return m_notes.size();
}

Note Chord::getNote(const Degree& degree) const noexcept
{
  return m_notes.at(degree);
}

Note Chord::getNote(const int index_zero_based) const noexcept
{
  return m_notes.at(index_zero_based);
}

Note Chord::getNote(const Note::Function& function) const noexcept
{
  for (const auto &note : m_notes)
  {
    if (note.getFunction() == function)
      return note;
  }

  return Note(12); // TODO: aggiungere un default constructor a Note per gestire il caso di `Note` non trovata?
}

std::string Chord::printChord(void) const
{
  std::string result("Chord notes:\n");

  int counter = m_notes.size();
  for (auto it = m_notes.crbegin(); it != m_notes.crend(); ++it)
  {
    result = result + "  - Note #" + std::to_string(counter) + ": " + std::to_string(*it) + ' ' + it->getName() + '\n';
    --counter;
  }

  return result;
}
