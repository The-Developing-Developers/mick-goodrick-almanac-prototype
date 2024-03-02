#ifndef DEGREE_HPP
#define DEGREE_HPP

#include <cstddef> // size_t

// TODO: Degree e Interval sono estremamente simili. Unirli in una classe unica?
/**
 * @brief To create a `Degree`, either use the internal enumerative (`enum_t`), or specify it as an
 * integer, where 1 = first, 2 = second, etc.
 */
struct Degree
{
  enum class enum_t
  {
    first = 0,
    second,
    third,
    fourth,
    fifth,
    sixth,
    seventh,

    how_many
  };

  explicit Degree(const enum_t degree) noexcept;
  explicit Degree(const int    degree) noexcept;

  operator size_t() const noexcept; // Useful to index `Scale`s, which are vectors of `Note`s

  Degree  operator+(const int increment);
  Degree  operator-(const int increment);

  Degree& operator+=(const int increment);
  Degree& operator-=(const int increment);

  enum_t m_degree;
};

#endif // DEGREE_HPP