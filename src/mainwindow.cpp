#include <QMetaType>
#include <QVariant>
#include <QPixmap>

#include "chordbuilder.hpp"
#include "enumerations.hpp"
#include "note.hpp"
#include "scale.hpp"

#include "mainwindow.h"
#include "./ui_mainwindow.h"

// Q_DECLARE_METATYPE(Alteration::enum_t); // TODO: in questo specifico esempio non serve, ma se `Alteration::enum_t` fosse usato in qualche segnale, sarebbe necessario riabilitare questa riga

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // TODO: it should centre the number inside the `QTextEdit`, but it does not work
  ui->textEdit_initialSeq_1->setAlignment(Qt::AlignCenter);
  ui->textEdit_initialSeq_2->setAlignment(Qt::AlignCenter);
  ui->textEdit_initialSeq_3->setAlignment(Qt::AlignCenter);
  ui->textEdit_initialSeq_4->setAlignment(Qt::AlignCenter);
  ui->textEdit_initialSeq_5->setAlignment(Qt::AlignCenter);
  ui->textEdit_initialSeq_6->setAlignment(Qt::AlignCenter);
  ui->textEdit_initialSeq_7->setAlignment(Qt::AlignCenter);

  // Set arrow pictures connecting the starting sequence to the desired sequence
  QPixmap pic("://img/downArrow.png");
  ui->img_1->setPixmap(pic);
  ui->img_2->setPixmap(pic);
  ui->img_3->setPixmap(pic);
  ui->img_4->setPixmap(pic);
  ui->img_5->setPixmap(pic);
  ui->img_6->setPixmap(pic);
  ui->img_7->setPixmap(pic);

  initialiseComboBoxes();

  connect(ui->pushButton,           &QPushButton::clicked,            this, &MainWindow::printHarmonisation);
  connect(ui->comboBox_numOfNotes,  &QComboBox::currentIndexChanged,  this, &MainWindow::onNumOfNotesChanged);
  connect(ui->comboBox_interval,    &QComboBox::currentIndexChanged,  this, &MainWindow::onIntervalChanged);

  calculateInitialSequence();
}


MainWindow::~MainWindow(void)
{
  delete ui;
}


void MainWindow::initialiseComboBoxes(void)
{
  int index;

  // Fundamental note combo box
  for (const auto& [key, string] : NaturalNote::getMap())
  {
    ui->comboBox_fundamental->addItem(QString::fromStdString(string), QVariant::fromValue(key)); // Riempimento automatico dei valori della combo box mediante la mappa dichiarata in `Alteration` usando un ranged for loop con structured binding
  }
  // Set fundamental default value
  index = ui->comboBox_fundamental->findText(QString::fromStdString(NaturalNote::getNoteAsString(NaturalNote::enum_t::C)));
  if (index != -1)
    ui->comboBox_fundamental->setCurrentIndex(index);


  // Alteration combo box
  for (const auto& [key, string] : Alteration::getMap())
  {
    ui->comboBox_alteration->addItem(QString::fromStdString(string), QVariant::fromValue(key));
  }
  // Set alteration default value
  index = ui->comboBox_alteration->findText(QString::fromStdString(Alteration::getAlterationAsString(Alteration::enum_t::natural)));
  if (index != -1)
    ui->comboBox_alteration->setCurrentIndex(index);


  // Scale type combo box
  for (const auto& [key, string] : Scale::getMap())
  {
    ui->comboBox_scaleType->addItem(QString::fromStdString(string), QVariant::fromValue(key));
  }
  // Set scale type default value
  index = ui->comboBox_scaleType->findText(QString::fromStdString(Scale::getScaleTypeAsString(Scale::ScaleType::Major)));
  if (index != -1)
    ui->comboBox_scaleType->setCurrentIndex(index);


  // Number of notes per chord combo box
  constexpr size_t minNumOfNotes = 2;
  constexpr size_t maxNumOfNotes = 7;
  for (size_t i = minNumOfNotes; i <= maxNumOfNotes; ++i)
  {
    ui->comboBox_numOfNotes->addItem(QString::number(i), QVariant(i));
  }
  // Set number of notes per chord default value
  index = ui->comboBox_numOfNotes->findText("4");
  if (index != -1)
    ui->comboBox_numOfNotes->setCurrentIndex(index);


  // Cycle combo box
  for (const auto& [key, string] : ChordBuilder::getMap())
  {
    ui->comboBox_cycle->addItem(QString::fromStdString(string), QVariant::fromValue(key));
  }
  // Set cycle default value
  index = ui->comboBox_cycle->findText(QString::fromStdString(ChordBuilder::getCycleTypeAsString(ChordBuilder::Cycle_enum::bySeconds)));
  if (index != -1)
    ui->comboBox_cycle->setCurrentIndex(index);


  // Interval combo box
  for (const auto& [key, string] : Interval::getMap())
  {
    ui->comboBox_interval->addItem(QString::fromStdString(string), QVariant::fromValue(key));
  }
  // Set interval default value
  index = ui->comboBox_interval->findText(QString::fromStdString(Interval::getIntervalAsString(Interval::enum_t::third)));
  if (index != -1)
    ui->comboBox_interval->setCurrentIndex(index);

  onNumOfNotesChanged();
  onIntervalChanged();
}


void MainWindow::printHarmonisation(void)
{
  // Here we determine which indices of the `functionalSequence` will be used later. For example, if we harmonise a C major scale with a
  // tetrad of fifths, we will have C, G, D, A, which functionally correspond to F, 5, 2, 6. In ascending order, we obtain F256. This means
  // that, in order to generate the `functionalSequence`, we only need to use the indices corresponding to the fundamental, the second, the
  // fifth, and the sixth note of the chord, i.e. indices 0, 1, 4, 5. These indices will be used to populate `functionalSequence` with the
  // functional intervals specified by the user.

  std::vector<size_t> functionalSequence_indices; // Used to initialise the `functionalSequence`

  for (const char function : m_initialFunctionalSequence) // `m_initialFunctionalSequence` is calculated in `calculateInitialSequence`
  {
    if (function == 1)
      functionalSequence_indices.push_back(0);
    else if (function == 2)
      functionalSequence_indices.push_back(1);
    else if (function == 3)
      functionalSequence_indices.push_back(2);
    else if (function == 4)
      functionalSequence_indices.push_back(3);
    else if (function == 5)
      functionalSequence_indices.push_back(4);
    else if (function == 6)
      functionalSequence_indices.push_back(5);
    else if (function == 7)
      functionalSequence_indices.push_back(6);
    else
      throw std::runtime_error("completeFinalHarmonisation: could not find note (triads)");
  }

  // Here the user's choice of functional intervals is applied. For example, given the F256 starting chord (see above), if the user
  // specifies a functional sequence of 562F (captured as a string in `user_voicing`), this means that the fundamental of a chord goes to
  // the fifth of the next chord, the second goes to the sixth, the fifth goes to the second, and the sixth goes to the fundamental.
  // Therefore, `functionalSequence` is only modified using the `functionalSequence_indices` that have been determined earlier.

  std::array<Note::Function, Constants::numOfNotesInHeptatonicScale> functionalSequence
  {
    Note::Function::none,
    Note::Function::none,
    Note::Function::none,
    Note::Function::none,
    Note::Function::none,
    Note::Function::none,
    Note::Function::none
  };

  constexpr size_t numOfQTextEdits = 7;

  const std::array<QComboBox*, numOfQTextEdits> comboBoxDesired_array // Helper container to manage all the `QComboBox`es of the desired sequences at once
  {
    ui->comboBoxDesired_1,
    ui->comboBoxDesired_2,
    ui->comboBoxDesired_3,
    ui->comboBoxDesired_4,
    ui->comboBoxDesired_5,
    ui->comboBoxDesired_6,
    ui->comboBoxDesired_7
  };

  // Initialise `functionalSequence` with the indices determined earlier, by reading the values of the "Desired Sequence" combo boxes
  for (size_t i = 0; i != m_numOfNotes; ++i)
  {
    if (comboBoxDesired_array[i]->itemData(comboBoxDesired_array[i]->currentIndex()) == QString("1"))
      functionalSequence[functionalSequence_indices[i]] = Note::Function::fundamental;
    else if (comboBoxDesired_array[i]->itemData(comboBoxDesired_array[i]->currentIndex()) == QString("2"))
      functionalSequence[functionalSequence_indices[i]] = Note::Function::second;
    else if (comboBoxDesired_array[i]->itemData(comboBoxDesired_array[i]->currentIndex()) == QString("3"))
      functionalSequence[functionalSequence_indices[i]] = Note::Function::third;
    else if (comboBoxDesired_array[i]->itemData(comboBoxDesired_array[i]->currentIndex()) == QString("4"))
      functionalSequence[functionalSequence_indices[i]] = Note::Function::fourth;
    else if (comboBoxDesired_array[i]->itemData(comboBoxDesired_array[i]->currentIndex()) == QString("5"))
      functionalSequence[functionalSequence_indices[i]] = Note::Function::fifth;
    else if (comboBoxDesired_array[i]->itemData(comboBoxDesired_array[i]->currentIndex()) == QString("6"))
      functionalSequence[functionalSequence_indices[i]] = Note::Function::sixth;
    else if (comboBoxDesired_array[i]->itemData(comboBoxDesired_array[i]->currentIndex()) == QString("7"))
      functionalSequence[functionalSequence_indices[i]] = Note::Function::seventh;
    else
      throw std::runtime_error("completeFinalHarmonisation: could not find note (triads)");
  }

  const NaturalNote              fundamental = ui->comboBox_fundamental->itemData(ui->comboBox_fundamental ->currentIndex()).value<NaturalNote::enum_t>(); // Conversione da `QVariant` al tipo sottostante (`NaturalNote::enum_t` in questo caso)
  const Alteration               alteration  = ui->comboBox_alteration ->itemData(ui->comboBox_alteration  ->currentIndex()).value<Alteration::enum_t>();
  const Scale::ScaleType         scaleType   = ui->comboBox_scaleType  ->itemData(ui->comboBox_scaleType   ->currentIndex()).value<Scale::ScaleType>();
  const ChordBuilder::Cycle_enum cycle       = ui->comboBox_cycle      ->itemData(ui->comboBox_cycle       ->currentIndex()).value<ChordBuilder::Cycle_enum>();

  Scale scale(Note(fundamental, alteration), scaleType);
  auto harmonisation = ChordBuilder::functionalHarmony(scale, m_numOfNotes, functionalSequence, cycle, m_interval);

  QString result;

  for (const auto & chord : harmonisation)
  {
    result += QString::fromStdString(chord.printChord());
  }

  ui->textEdit->setText(result);
}


void MainWindow::onIntervalChanged(void)
{
  m_interval = ui->comboBox_interval->itemData(ui->comboBox_interval->currentIndex()).value<Interval::enum_t>();
  calculateInitialSequence();
}


void MainWindow::onNumOfNotesChanged(void)
{
  m_numOfNotes = (ui->comboBox_numOfNotes->currentText()).toInt();
  calculateInitialSequence();
}


/**
 * @brief Called at start-up, and every time some critical data are changed (i.e., data that can influence the composition of the initial
 * sequence).
 **/
void MainWindow::calculateInitialSequence(void)
{
  constexpr size_t numOfQTextEdits = 7;

  const std::array<QTextEdit*, numOfQTextEdits> textEditInitial_array // Helper container to manage all the `QTextEdit`s of the initial sequences at once
  {
    ui->textEdit_initialSeq_1,
    ui->textEdit_initialSeq_2,
    ui->textEdit_initialSeq_3,
    ui->textEdit_initialSeq_4,
    ui->textEdit_initialSeq_5,
    ui->textEdit_initialSeq_6,
    ui->textEdit_initialSeq_7
  };

  const std::array<QComboBox*, numOfQTextEdits> comboBoxDesired_array // Helper container to manage all the `QComboBox`es of the desired sequences at once
  {
    ui->comboBoxDesired_1,
    ui->comboBoxDesired_2,
    ui->comboBoxDesired_3,
    ui->comboBoxDesired_4,
    ui->comboBoxDesired_5,
    ui->comboBoxDesired_6,
    ui->comboBoxDesired_7
  };

  for (auto textEdit : textEditInitial_array)
    textEdit->clear();

  for (auto comboBox : comboBoxDesired_array)
    comboBox->clear();

  // Enable only the "desired sequence" combo boxes corresponding to a valid initial sequence number, and disable all the others
  for (size_t i = 0; i != m_numOfNotes; ++i)
  {
    comboBoxDesired_array[i]->setEnabled(true);
  }

  for (size_t i = m_numOfNotes; i != numOfQTextEdits; ++i)
    comboBoxDesired_array[i]->setEnabled(false);

  // Preparing the initial functional sequence, initially as a vector of integers (`m_initialFunctionalSequence`) for ease of calculation,
  // and later converted into a string (`initialFunctionalSequence_str`) to determine the `functionalSequence`. For example, if we harmonise
  // a C major scale with a tetrad of fifths, we will have C, G, D, A, which functionally correspond to 1, 5, 2, 6, later converted to
  // string as "F526". Sorting in ascending order, we obtain "F256" for ease of reading.

  m_initialFunctionalSequence.clear();

  int currentNoteFunction_int = 1; // `1` is the fundamental. The initial functional sequence always starts from the fundamental
  m_initialFunctionalSequence.push_back(currentNoteFunction_int);

  for (size_t i = 1; i != m_numOfNotes; ++i)
  {
    currentNoteFunction_int += m_interval;
    if (currentNoteFunction_int > 7)
      currentNoteFunction_int -= 7;
    m_initialFunctionalSequence.push_back(currentNoteFunction_int);
  }

  std::sort(m_initialFunctionalSequence.begin(), m_initialFunctionalSequence.end()); // Sorted because it is easier to read

  for (size_t i = 0; i != m_numOfNotes; ++i)
  {
    textEditInitial_array[i]->setPlainText(QString::number(m_initialFunctionalSequence[i])); // Display calculated initial sequence in the `QTextEdit`s, one function for each `QTextEdit`
    for (size_t j = 0; j != m_numOfNotes; ++j)
    {
      comboBoxDesired_array[i]->addItem(QString::number(m_initialFunctionalSequence[j]), QVariant(m_initialFunctionalSequence[j])); // Populate available `QComboBox`es only with allowed functions
    }
  }
}