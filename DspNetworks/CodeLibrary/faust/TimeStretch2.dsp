import("stdfaust.lib");

// Number of voices for polyphony
nVoices = 8;

// Controls
grnSize = vslider("chunk[style:knob]", 5000, 5000, 10000, 1) : int : si.smoo;
grnPitch = vslider("pitch[style:knob]", 0, -12, 12, 0.1) : si.smoo;
grnDensity = vslider("density[style:knob]", 4, 1, 8, 1) : int;  // Number of overlapping grains
grnDecay = vslider("decay[style:knob]", 2, 0.1, 5, 0.1);  // Decay time in seconds

// Hanning window function
hanning(x) = 0.5 - 0.5 * cos(x * 2.0 * ma.PI);

// Grain frequency calculation
grnFreq(pitch) = max(1, ma.SR / (grnSize / pow(2, (pitch / 12))));

// Safe phase accumulator
safePhase(freq) = (+(freq/ma.SR) : ma.frac) ~ _;

// Grain generator for a single voice
grainGen(input, pitch) = (
    ramp * envelope * grain
)
with {
    phase = safePhase(grnFreq(grnPitch));  // Use grnPitch directly
    ramp = 1 - phase;
    envelope = 1;  // Continuous trigger
    delayTime = min(ma.SR, max(0, grnSize * ramp));
    grain = de.fdelay(ma.SR, delayTime, input) * hanning(phase);
};

// Polyphonic grain generator
polyGrainGen(input) = sum(i, nVoices, 
    grainGen(input, grnPitch + (no.noise * 0.1))
);

// Main process
process = _ : polyGrainGen <: _, _;