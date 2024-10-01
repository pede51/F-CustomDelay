/* ------------------------------------------------------------
name: "TimeStretch2"
Code generated with Faust 2.75.7 (https://faust.grame.fr)
Compilation options: -lang cpp -rui -nvi -ct 1 -cn _TimeStretch2 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___TimeStretch2_H__
#define  ___TimeStretch2_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _TimeStretch2
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif


struct _TimeStretch2 final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fVslider0;
	float fRec1[2];
	FAUSTFLOAT fVslider1;
	float fRec2[2];
	float fConst3;
	float fRec0[2];
	int IOTA0;
	float fVec0[262144];
	float fConst4;
	
	_TimeStretch2() {
	}
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -rui -nvi -ct 1 -cn _TimeStretch2 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.1.0");
		m->declare("filename", "TimeStretch2.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.0");
		m->declare("name", "TimeStretch2");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "1.4.1");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
	}

	static constexpr int getStaticNumInputs() {
		return 1;
	}
	static constexpr int getStaticNumOutputs() {
		return 2;
	}
	int getNumInputs() {
		return 1;
	}
	int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 1.0f / fConst0;
		fConst4 = fConst0 + 1.0f;
	}
	
	void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(5e+03f);
		fVslider1 = FAUSTFLOAT(0.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec0[l2] = 0.0f;
		}
		IOTA0 = 0;
		for (int l3 = 0; l3 < 262144; l3 = l3 + 1) {
			fVec0[l3] = 0.0f;
		}
	}
	
	void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	_TimeStretch2* clone() {
		return new _TimeStretch2();
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("TimeStretch2");
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->addVerticalSlider("chunk", &fVslider0, FAUSTFLOAT(5e+03f), FAUSTFLOAT(5e+03f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->addVerticalSlider("pitch", &fVslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * float(int(std::max<float>(5e+03f, std::min<float>(1e+04f, float(fVslider0)))));
		float fSlow1 = fConst1 * std::max<float>(-12.0f, std::min<float>(12.0f, float(fVslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec1[0] = fSlow0 + fConst2 * fRec1[1];
			fRec2[0] = fSlow1 + fConst2 * fRec2[1];
			float fTemp0 = fRec0[1] + fConst3 * std::max<float>(1.0f, fConst0 * (std::pow(2.0f, 0.083333336f * fRec2[0]) / fRec1[0]));
			fRec0[0] = fTemp0 - std::floor(fTemp0);
			float fTemp1 = 1.0f - fRec0[0];
			float fTemp2 = std::min<float>(fConst0, std::max<float>(0.0f, fRec1[0] * fTemp1));
			float fTemp3 = std::floor(fTemp2);
			float fTemp4 = float(input0[i0]);
			fVec0[IOTA0 & 262143] = fTemp4;
			int iTemp5 = int(fTemp2);
			float fTemp6 = 4.0f * fTemp1 * (1.0f - std::cos(6.2831855f * fRec0[0])) * ((fTemp2 - fTemp3) * fVec0[(IOTA0 - int(std::min<float>(fConst4, float(std::max<int>(0, iTemp5 + 1))))) & 262143] + fVec0[(IOTA0 - int(std::min<float>(fConst4, float(std::max<int>(0, iTemp5))))) & 262143] * (fTemp3 + (1.0f - fTemp2)));
			output0[i0] = FAUSTFLOAT(fTemp6);
			output1[i0] = FAUSTFLOAT(fTemp6);
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			IOTA0 = IOTA0 + 1;
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "TimeStretch2.dsp"
	#define FAUST_CLASS_NAME "_TimeStretch2"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -rui -nvi -ct 1 -cn _TimeStretch2 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDVERTICALSLIDER("chunk", fVslider0, 5e+03f, 5e+03f, 1e+04f, 1.0f);
	FAUST_ADDVERTICALSLIDER("pitch", fVslider1, 0.0f, -12.0f, 12.0f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(VERTICALSLIDER, chunk, "chunk", fVslider0, 5e+03f, 5e+03f, 1e+04f, 1.0f) \
		p(VERTICALSLIDER, pitch, "pitch", fVslider1, 0.0f, -12.0f, 12.0f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif
