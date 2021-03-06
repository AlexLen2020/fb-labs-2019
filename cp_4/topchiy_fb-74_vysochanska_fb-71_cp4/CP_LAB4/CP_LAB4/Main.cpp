#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<ctime>
#include <string>
using namespace std;

bool LFSRoneTact(vector<bool>, vector<bool>& ); // One tact of linear feedback shift register
int LFSR(vector<bool>, vector<bool>& , vector<bool>& , string);
int GetAutoCorCoef(vector<bool> Sequence, int Step); // Auto correlation Coefficient 
void GetAutoCorCoef(vector<bool> Sequence);
void PolynomialType(int PolyDegree, int Period);

void initNgramMap( vector<bool> Sequence, int NgramSize, string FilePath);

int main() {
	//-------------- First polynomial -----------
	vector<bool> CoefP1 = { 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0 };
	vector<bool> InitialStateP1(CoefP1.size(), 0);
	InitialStateP1.back() = 1; // //Initial state of register for impulse function
	vector<bool> SequenceP1; // Generated sequence

	//-------------- Second polynomial ----------
	vector<bool> CoefP2 = { 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0 };
	vector<bool> InitialStateP2(CoefP2.size(), 0);
	InitialStateP2.back() = 1; // //Initial state of register for impulse function
	vector<bool> SequenceP2; // Generated sequence

	// First LFSR
	int PeriodP1;
	PeriodP1 = LFSR(CoefP1, InitialStateP1, SequenceP1, "..\\..\\Generated Sequence Var.18 P1.txt");
	cout << PeriodP1 << endl;
	// Second LFSR
	int PeriodP2;
	PeriodP2 = LFSR(CoefP2, InitialStateP2, SequenceP2, "..\\..\\Generated Sequence Var.18 P2.txt");
	cout << PeriodP2 << endl;
	
	GetAutoCorCoef(SequenceP1);
	GetAutoCorCoef(SequenceP2);
	
	PolynomialType(CoefP1.size(), PeriodP1);
	PolynomialType(CoefP2.size(), PeriodP2);

	for (int i = 2; i < 6; i++) {
		initNgramMap(SequenceP1, i, "..\\..\\NgramsP1\\" + to_string(i) + "gram Map.txt");
	}
	for (int i = 2; i < 6; i++) {
		initNgramMap(SequenceP2, i, "..\\..\\NgramsP2\\" + to_string(i) + "gram Map.txt");
	}
	
	
	system("pause");
	return 0;
}
bool LFSRoneTact(vector<bool>FeedbackCoef, vector<bool>& Register) {
	bool ShiftedBit = 0; // First bit of register, that will be shifted
	bool GeneratedBit; // Bit generated by LFSR in one tact
	ShiftedBit = Register[0];
	int Sum = 0; // Sum of composition Feedback[i] and Register[i]
	for (int i = 0; i < Register.size(); i++) {
		if (FeedbackCoef[i] != 0) {
			Sum += FeedbackCoef[i] * Register[i];
		}
	}
	GeneratedBit = Sum % 2;
	//Bits swaping 
	for (int i = 0; i < Register.size() - 1; i++) {
		Register[i] = Register[i + 1];
	}
	Register.back() = GeneratedBit;
	return ShiftedBit;
}
int LFSR(vector<bool>FeedbackCoef, vector<bool>& InitialState, vector<bool>& Sequence, string FilePath) {
	ofstream fout(FilePath);
	vector<bool> Register;
	int Period = 0;
	Register = InitialState;
	bool TempBool;
	do {
		Period++;
		TempBool = LFSRoneTact(FeedbackCoef, Register);
		fout << TempBool;
		Sequence.push_back(TempBool);
		//if (Period % 100000 == 0) cout << Period << " ";
	} while (Register != InitialState);
	return Period;
}

int GetAutoCorCoef(vector<bool> Sequence, int Step) {
	int ACF = 0;
	for (int i = 0; i < Sequence.size(); i++) {
		ACF += (Sequence[i] + Sequence[(i + Step) % Sequence.size()]) % 2;
	}
	return ACF;
}
void GetAutoCorCoef(vector<bool> Sequence) {
	for (int i = 1; i < 11; i++) {
		cout << "AutoCorCoef d = " << i << " : " << GetAutoCorCoef(Sequence, i) << endl;
	}
	cout << endl;
}

void PolynomialType(int PolyDegree, int Period) {
	if (Period == pow(2, PolyDegree) - 1) {
		cout << "Polynomial is primitive" << endl;
	}
	else if(pow(2, PolyDegree) - 1 % Period == 0){
		cout << "Polynomial isn't primitive and not reducible" << endl;
	}
	else {
		cout << "Polynomial isn't primitive, but reducible" << endl;
	}
}

void initNgramMap(vector<bool> Sequence, int NgramSize, string FilePath) {
	ofstream fout(FilePath);
	map<string, double> Map;
	string TempNgram;
	bool TempBool;
	double Amount = 0;
	for (int i = 0; i < Sequence.size(); i += 1 + NgramSize) {
		for (int j = 0; j < NgramSize; j++) {
			TempBool = Sequence[(i + j) % Sequence.size()];
			TempNgram += to_string(TempBool);
		}
		if (Map.count(TempNgram)) {
			Amount++;
			Map.at(TempNgram)++;
		}
		else {
			Amount++;
			Map.emplace(TempNgram, 1);
		}
		TempNgram.clear();
	}
	for (auto it = Map.cbegin(); it != Map.cend(); it++) {
		fout << it->first << "	" << it->second / Amount << endl;
	}
}