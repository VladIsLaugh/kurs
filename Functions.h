//---------------------------------------------------------------------------

#ifndef FunctionsH
#define FunctionsH
#include "Patient.h"
#include "Registry.h"
#include <vector>

void sortByPressure(vector<CPatient> &, int, int, bool);
void sortByPulse(vector<CPatient> &, int, int, bool);
void showDonors(TStringGrid*, vector<CPatient>);
void showRecipients(TStringGrid*, vector<CPatient>);
//---------------------------------------------------------------------------
#endif
