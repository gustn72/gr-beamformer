/* -*- c++ -*- */

#define BEAMFORMER_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "beamformer_swig_doc.i"

%{
#include "beamformer/beampattern.h"
#include "beamformer/Constraint_Beamformer.h"
%}

%include "beamformer/beampattern.h"
GR_SWIG_BLOCK_MAGIC2(beamformer, beampattern);
%include "beamformer/Constraint_Beamformer.h"
GR_SWIG_BLOCK_MAGIC2(beamformer, Constraint_Beamformer);
