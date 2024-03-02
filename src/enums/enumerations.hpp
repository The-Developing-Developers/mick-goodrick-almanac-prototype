#ifndef ENUMERATIONS_HPP
#define ENUMERATIONS_HPP

// TODO: valutare se può essere vantaggioso utilizzare questo namespace come collettore di tutti i tipi dati enumerati (`Alteration`,
// `ChromaticPitch`, ecc.) anziché tenerli in files separati.
// TODO: ha più senso trasformare questo namespace in una classe? La mappa `naturalNotesToQString` diventerebbe un membro `static`, così
// come già stato fatto per diverse altre classi che in realtà incapsulano un enumerativo (ad esempio, `Alteration`).
namespace Enumerations
{
  enum class MidiNotes
  {
    B_59      = 59,
    C_60      = 60,
    Cs_Db_61  = 61,
    D_62      = 62,
    Ds_Eb_63  = 63,
    E_64      = 64,
    F_65      = 65,
    Fs_Gb_66  = 66,
    G_67      = 67,
    Gs_Ab_68  = 68,
    A_69      = 69,
    As_Bb_70  = 70,
    B_71      = 71,
    C_72      = 72
  };

  enum class Octave
  {
    Octave_0 = 0,
    Octave_1 = 1,
    Octave_2 = 2,
    Octave_3 = 3,
    Octave_4 = 4,
    Octave_5 = 5,
    Octave_6 = 6,
    Octave_7 = 7,
    Octave_8 = 8
  };
};

#endif // ENUMERATIONS_HPP
