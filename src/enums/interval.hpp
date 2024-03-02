#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <cstddef> // size_t
#include <map>
#include <string>

/**
 * @brief To create an `Interval`, either use the internal enumerative (`enum_t`), or specify it as
 * an integer, where 1 = unison, 2 = second, etc.
 */
class Interval
{
public:
  enum class enum_t
  {
    unison  = 0,
    second,
    third,
    fourth,
    fifth,
    sixth,
    seventh,

    how_many
  };

  explicit Interval(const enum_t interval = enum_t::unison) noexcept;
  explicit Interval(const int    interval) noexcept; // 1 = unison; 2 = second, etc.

  operator size_t() const noexcept;

  Interval& operator=(const enum_t interval) noexcept;
  Interval& operator=(const int    interval) noexcept;

  Interval& operator+=(const int increment);
  Interval& operator-=(const int increment);

  static const std::string getIntervalAsString(const enum_t interval);
  static const std::map<enum_t, std::string> &getMap(void);

private:
  enum_t m_interval;
  static const std::map<enum_t, std::string> m_enumToString; // Serve per poter automatizzare l'inizializzazione dei valori della combo box nel constructor di `MainWindow`
};

#endif // INTERVAL_HPP