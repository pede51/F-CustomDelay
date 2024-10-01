#pragma once

// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace script_fx1_impl
{
// ==============================| Node & Parameter type declarations |==============================

DECLARE_PARAMETER_RANGE_SKEW(dry_wet_mixer_c0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using dry_wet_mixer_c0 = parameter::from0To1<core::gain<NV>, 
                                             0, 
                                             dry_wet_mixer_c0Range>;

template <int NV> using dry_wet_mixer_c1 = dry_wet_mixer_c0<NV>;

template <int NV>
using dry_wet_mixer_multimod = parameter::list<dry_wet_mixer_c0<NV>, dry_wet_mixer_c1<NV>>;

template <int NV>
using dry_wet_mixer_t = control::xfader<dry_wet_mixer_multimod<NV>, 
                                        faders::linear>;

template <int NV>
using dry_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, dry_wet_mixer_t<NV>>, 
                                    core::gain<NV>>;

template <int NV>
using tempo_sync_t = wrap::mod<parameter::plain<core::fix_delay, 0>, 
                               control::tempo_sync<NV>>;
using stereo_cable = cable::block<2>;

namespace feedback_delay1_t_parameters
{
}

template <int NV>
using feedback_delay1_t_ = container::chain<parameter::plain<routing::receive<stereo_cable>, 0>, 
                                            wrap::fix<2, routing::receive<stereo_cable>>, 
                                            core::fix_delay, 
                                            routing::send<stereo_cable>, 
                                            project::TimeStretch2<NV>>;

template <int NV>
using feedback_delay1_t = wrap::fix_block<32, feedback_delay1_t_<NV>>;

template <int NV> using dry_wet_mixer2_c0 = dry_wet_mixer_c0<NV>;

template <int NV> using dry_wet_mixer2_c1 = dry_wet_mixer_c0<NV>;

template <int NV>
using dry_wet_mixer2_multimod = parameter::list<dry_wet_mixer2_c0<NV>, dry_wet_mixer2_c1<NV>>;

template <int NV>
using dry_wet_mixer2_t = control::xfader<dry_wet_mixer2_multimod<NV>, 
                                         faders::linear>;

template <int NV>
using dry_path2_t = container::chain<parameter::empty, 
                                     wrap::fix<2, dry_wet_mixer2_t<NV>>, 
                                     core::gain<NV>>;

template <int NV>
using wet_path2_t = container::chain<parameter::empty, 
                                     wrap::fix<2, project::TimeStretch2<NV>>, 
                                     core::gain<NV>>;

namespace dry_wet3_t_parameters
{
}

template <int NV>
using dry_wet3_t = container::split<parameter::plain<script_fx1_impl::dry_wet_mixer2_t<NV>, 0>, 
                                    wrap::fix<2, dry_path2_t<NV>>, 
                                    wet_path2_t<NV>>;

template <int NV> using dry_wet_mixer3_c0 = dry_wet_mixer_c0<NV>;

template <int NV> using dry_wet_mixer3_c1 = dry_wet_mixer_c0<NV>;

template <int NV>
using dry_wet_mixer3_multimod = parameter::list<dry_wet_mixer3_c0<NV>, dry_wet_mixer3_c1<NV>>;

template <int NV>
using dry_wet_mixer3_t = control::xfader<dry_wet_mixer3_multimod<NV>, 
                                         faders::linear>;

template <int NV>
using dry_path3_t = container::chain<parameter::empty, 
                                     wrap::fix<2, dry_wet_mixer3_t<NV>>, 
                                     core::gain<NV>>;

template <int NV>
using wet_path3_t = container::chain<parameter::empty, 
                                     wrap::fix<2, core::gain<NV>>, 
                                     fx::reverb>;

namespace dry_wet4_t_parameters
{
}

template <int NV>
using dry_wet4_t = container::split<parameter::plain<script_fx1_impl::dry_wet_mixer3_t<NV>, 0>, 
                                    wrap::fix<2, dry_path3_t<NV>>, 
                                    wet_path3_t<NV>>;

template <int NV>
using wet_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, core::gain<NV>>, 
                                    tempo_sync_t<NV>, 
                                    feedback_delay1_t<NV>, 
                                    dry_wet3_t<NV>, 
                                    dry_wet4_t<NV>>;

namespace dry_wet1_t_parameters
{
}

template <int NV>
using dry_wet1_t = container::split<parameter::plain<script_fx1_impl::dry_wet_mixer_t<NV>, 0>, 
                                    wrap::fix<2, dry_path_t<NV>>, 
                                    wet_path_t<NV>>;

namespace script_fx1_t_parameters
{
// Parameter list for script_fx1_impl::script_fx1_t ------------------------------------------------

template <int NV>
using TempoScript = parameter::plain<script_fx1_impl::tempo_sync_t<NV>, 
                                     0>;
template <int NV>
using DryWetScript = parameter::plain<script_fx1_impl::dry_wet1_t<NV>, 
                                      0>;
template <int NV>
using FeedbackScript = parameter::plain<script_fx1_impl::feedback_delay1_t<NV>, 
                                        0>;
template <int NV>
using PitchScript = parameter::plain<project::TimeStretch2<NV>, 
                                     1>;
template <int NV>
using ChunkScript = parameter::plain<project::TimeStretch2<NV>, 
                                     0>;
template <int NV>
using PitchScript2 = parameter::plain<script_fx1_impl::dry_wet3_t<NV>, 
                                      0>;
template <int NV>
using ReverbScript = parameter::plain<script_fx1_impl::dry_wet4_t<NV>, 
                                      0>;
template <int NV>
using GainScript = parameter::plain<core::gain<NV>, 0>;
template <int NV>
using script_fx1_t_plist = parameter::list<TempoScript<NV>, 
                                           DryWetScript<NV>, 
                                           FeedbackScript<NV>, 
                                           PitchScript<NV>, 
                                           ChunkScript<NV>, 
                                           PitchScript2<NV>, 
                                           ReverbScript<NV>, 
                                           GainScript<NV>>;
}

template <int NV>
using script_fx1_t_ = container::chain<script_fx1_t_parameters::script_fx1_t_plist<NV>, 
                                       wrap::fix<2, core::gain<NV>>, 
                                       dry_wet1_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public script_fx1_impl::script_fx1_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(script_fx1);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(152)
		{
			0x005B, 0x0000, 0x5400, 0x6D65, 0x6F70, 0x6353, 0x6972, 0x7470, 
            0x0000, 0x0000, 0x0000, 0x9000, 0x0041, 0x4000, 0x0041, 0x8000, 
            0x003F, 0x8000, 0x5B3F, 0x0001, 0x0000, 0x7244, 0x5779, 0x7465, 
            0x6353, 0x6972, 0x7470, 0x0000, 0x0000, 0x0000, 0x8000, 0xA63F, 
            0xB718, 0x003E, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0002, 0x0000, 
            0x6546, 0x6465, 0x6162, 0x6B63, 0x6353, 0x6972, 0x7470, 0x0000, 
            0x0000, 0x0000, 0x8000, 0xBC3F, 0x4896, 0x003F, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0003, 0x0000, 0x6950, 0x6374, 0x5368, 0x7263, 
            0x7069, 0x0074, 0x0000, 0xC140, 0x0000, 0x4140, 0x0000, 0x4140, 
            0x0000, 0x3F80, 0xCCCD, 0x3DCC, 0x045B, 0x0000, 0x4300, 0x7568, 
            0x6B6E, 0x6353, 0x6972, 0x7470, 0x0000, 0x9C40, 0x0045, 0x1C40, 
            0x0046, 0x1898, 0x0046, 0x8000, 0x003F, 0x8000, 0x5B3F, 0x0005, 
            0x0000, 0x6950, 0x6374, 0x5368, 0x7263, 0x7069, 0x3274, 0x0000, 
            0x0000, 0x0000, 0x8000, 0x673F, 0xEB8F, 0x003E, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0006, 0x0000, 0x6552, 0x6576, 0x6272, 0x6353, 
            0x6972, 0x7470, 0x0000, 0x0000, 0x0000, 0x8000, 0xBC3F, 0xAD57, 
            0x003E, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0007, 0x0000, 0x6147, 
            0x6E69, 0x6353, 0x6972, 0x7470, 0x0000, 0xC800, 0x00C2, 0xC000, 
            0x3141, 0x4CCD, 0x3E3E, 0xAD83, 0xCD40, 0xCCCC, 0x003D, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& gain = this->getT(0);                                           // core::gain<NV>
		auto& dry_wet1 = this->getT(1);                                       // script_fx1_impl::dry_wet1_t<NV>
		auto& dry_path = this->getT(1).getT(0);                               // script_fx1_impl::dry_path_t<NV>
		auto& dry_wet_mixer = this->getT(1).getT(0).getT(0);                  // script_fx1_impl::dry_wet_mixer_t<NV>
		auto& dry_gain = this->getT(1).getT(0).getT(1);                       // core::gain<NV>
		auto& wet_path = this->getT(1).getT(1);                               // script_fx1_impl::wet_path_t<NV>
		auto& wet_gain = this->getT(1).getT(1).getT(0);                       // core::gain<NV>
		auto& tempo_sync = this->getT(1).getT(1).getT(1);                     // script_fx1_impl::tempo_sync_t<NV>
		auto& feedback_delay1 = this->getT(1).getT(1).getT(2);                // script_fx1_impl::feedback_delay1_t<NV>
		auto& fb_out = this->getT(1).getT(1).getT(2).getT(0);                 // routing::receive<stereo_cable>
		auto& delay = this->getT(1).getT(1).getT(2).getT(1);                  // core::fix_delay
		auto& fb_in = this->getT(1).getT(1).getT(2).getT(2);                  // routing::send<stereo_cable>
		auto& faust = this->getT(1).getT(1).getT(2).getT(3);                  // project::TimeStretch2<NV>
		auto& dry_wet3 = this->getT(1).getT(1).getT(3);                       // script_fx1_impl::dry_wet3_t<NV>
		auto& dry_path2 = this->getT(1).getT(1).getT(3).getT(0);              // script_fx1_impl::dry_path2_t<NV>
		auto& dry_wet_mixer2 = this->getT(1).getT(1).getT(3).getT(0).getT(0); // script_fx1_impl::dry_wet_mixer2_t<NV>
		auto& dry_gain2 = this->getT(1).getT(1).getT(3).getT(0).getT(1);      // core::gain<NV>
		auto& wet_path2 = this->getT(1).getT(1).getT(3).getT(1);              // script_fx1_impl::wet_path2_t<NV>
		auto& faust2 = this->getT(1).getT(1).getT(3).getT(1).getT(0);         // project::TimeStretch2<NV>
		auto& wet_gain2 = this->getT(1).getT(1).getT(3).getT(1).getT(1);      // core::gain<NV>
		auto& dry_wet4 = this->getT(1).getT(1).getT(4);                       // script_fx1_impl::dry_wet4_t<NV>
		auto& dry_path3 = this->getT(1).getT(1).getT(4).getT(0);              // script_fx1_impl::dry_path3_t<NV>
		auto& dry_wet_mixer3 = this->getT(1).getT(1).getT(4).getT(0).getT(0); // script_fx1_impl::dry_wet_mixer3_t<NV>
		auto& dry_gain3 = this->getT(1).getT(1).getT(4).getT(0).getT(1);      // core::gain<NV>
		auto& wet_path3 = this->getT(1).getT(1).getT(4).getT(1);              // script_fx1_impl::wet_path3_t<NV>
		auto& wet_gain3 = this->getT(1).getT(1).getT(4).getT(1).getT(0);      // core::gain<NV>
		auto& reverb = this->getT(1).getT(1).getT(4).getT(1).getT(1);         // fx::reverb
		
		// Parameter Connections -------------------------------------------------------------------
		
		feedback_delay1.getParameterT(0).connectT(0, fb_out);  // Feedback -> fb_out::Feedback
		dry_wet3.getParameterT(0).connectT(0, dry_wet_mixer2); // DryWet -> dry_wet_mixer2::Value
		dry_wet4.getParameterT(0).connectT(0, dry_wet_mixer3); // DryWet -> dry_wet_mixer3::Value
		dry_wet1.getParameterT(0).connectT(0, dry_wet_mixer);  // DryWet -> dry_wet_mixer::Value
		this->getParameterT(0).connectT(0, tempo_sync);        // TempoScript -> tempo_sync::Tempo
		
		this->getParameterT(1).connectT(0, dry_wet1); // DryWetScript -> dry_wet1::DryWet
		
		this->getParameterT(2).connectT(0, feedback_delay1); // FeedbackScript -> feedback_delay1::Feedback
		
		this->getParameterT(3).connectT(0, faust); // PitchScript -> faust::pitch
		
		this->getParameterT(4).connectT(0, faust); // ChunkScript -> faust::chunk
		
		this->getParameterT(5).connectT(0, dry_wet3); // PitchScript2 -> dry_wet3::DryWet
		
		this->getParameterT(6).connectT(0, dry_wet4); // ReverbScript -> dry_wet4::DryWet
		
		this->getParameterT(7).connectT(0, gain); // GainScript -> gain::Gain
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& dry_wet_mixer_p = dry_wet_mixer.getWrappedObject().getParameter();
		dry_wet_mixer_p.getParameterT(0).connectT(0, dry_gain); // dry_wet_mixer -> dry_gain::Gain
		dry_wet_mixer_p.getParameterT(1).connectT(0, wet_gain); // dry_wet_mixer -> wet_gain::Gain
		tempo_sync.getParameter().connectT(0, delay);           // tempo_sync -> delay::DelayTime
		auto& dry_wet_mixer2_p = dry_wet_mixer2.getWrappedObject().getParameter();
		dry_wet_mixer2_p.getParameterT(0).connectT(0, dry_gain2); // dry_wet_mixer2 -> dry_gain2::Gain
		dry_wet_mixer2_p.getParameterT(1).connectT(0, wet_gain2); // dry_wet_mixer2 -> wet_gain2::Gain
		auto& dry_wet_mixer3_p = dry_wet_mixer3.getWrappedObject().getParameter();
		dry_wet_mixer3_p.getParameterT(0).connectT(0, dry_gain3); // dry_wet_mixer3 -> dry_gain3::Gain
		dry_wet_mixer3_p.getParameterT(1).connectT(0, wet_gain3); // dry_wet_mixer3 -> wet_gain3::Gain
		
		// Send Connections ------------------------------------------------------------------------
		
		fb_in.connect(fb_out);
		
		// Default Values --------------------------------------------------------------------------
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // dry_wet1::DryWet is automated
		
		; // dry_wet_mixer::Value is automated
		
		;                               // dry_gain::Gain is automated
		dry_gain.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                               // wet_gain::Gain is automated
		wet_gain.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                  // tempo_sync::Tempo is automated
		tempo_sync.setParameterT(1, 1.);   // control::tempo_sync::Multiplier
		tempo_sync.setParameterT(2, 1.);   // control::tempo_sync::Enabled
		tempo_sync.setParameterT(3, 104.); // control::tempo_sync::UnsyncedTime
		
		; // feedback_delay1::Feedback is automated
		
		; // fb_out::Feedback is automated
		
		;                              // delay::DelayTime is automated
		delay.setParameterT(1, 1024.); // core::fix_delay::FadeTime
		
		; // faust::chunk is automated
		; // faust::pitch is automated
		
		; // dry_wet3::DryWet is automated
		
		; // dry_wet_mixer2::Value is automated
		
		;                                // dry_gain2::Gain is automated
		dry_gain2.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
		faust2.setParameterT(0, 8196.); // core::faust::chunk
		faust2.setParameterT(1, 12.);   // core::faust::pitch
		
		;                                // wet_gain2::Gain is automated
		wet_gain2.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // dry_wet4::DryWet is automated
		
		; // dry_wet_mixer3::Value is automated
		
		;                                // dry_gain3::Gain is automated
		dry_gain3.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain3.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                // wet_gain3::Gain is automated
		wet_gain3.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain3.setParameterT(2, 0.);  // core::gain::ResetValue
		
		reverb.setParameterT(0, 0.5);    // fx::reverb::Damping
		reverb.setParameterT(1, 0.5);    // fx::reverb::Width
		reverb.setParameterT(2, 0.6587); // fx::reverb::Size
		
		this->setParameterT(0, 12.);
		this->setParameterT(1, 0.35761);
		this->setParameterT(2, 0.78355);
		this->setParameterT(3, 12.);
		this->setParameterT(4, 9766.);
		this->setParameterT(5, 0.460078);
		this->setParameterT(6, 0.33856);
		this->setParameterT(7, 0.200001);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool isProcessingHiseEvent() { return true; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return false; };
};
}

#undef getT
#undef connectT
#undef setParameterT
#undef setParameterWT
#undef getParameterT
// ======================================| Public Definition |======================================

namespace project
{
// polyphonic template declaration

template <int NV>
using script_fx1 = wrap::node<script_fx1_impl::instance<NV>>;
}


