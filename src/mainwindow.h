#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "interval.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class MainWindow; // This forward declaration is used to declare the `ui` pointer below without the need to import the whole `ui_mainwindow.h` header
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
   MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void printHarmonisation(void);
  void onIntervalChanged(void);
  void onNumOfNotesChanged(void);

private:
  Ui::MainWindow   *ui;

  // The following variables need to be data members (i.e. persistent) because they is used to perform calculations on the initial functional sequence
  Interval          m_interval;
  int               m_numOfNotes;
  std::vector<int>  m_initialFunctionalSequence;

  void initialiseComboBoxes(void);
  void calculateInitialSequence(void);
};

#endif // MAINWINDOW_H
