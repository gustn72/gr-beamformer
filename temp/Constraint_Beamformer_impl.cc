/* -*- c++ -*- */
/* 
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "Constraint_Beamformer_impl.h"

namespace gr {
  namespace beamformer {

	Constraint_Beamformer::sptr
	Constraint_Beamformer::make(float norm_spacing, int num_targets, int inputs, int type, int channel)
	{
	  return gnuradio::get_initial_sptr
		(new Constraint_Beamformer_impl(norm_spacing, num_targets, inputs, type, channel));
	}

	/*
	 * The private constructor
	 */
	Constraint_Beamformer_impl::Constraint_Beamformer_impl(float norm_spacing, int num_targets, int inputs, int type, int channel)
	  : gr::block("Constraint_Beamformer",
			  gr::io_signature::make(1, 1, sizeof(<+ITYPE+>)),
			  gr::io_signature::make(<+MIN_OUT+>, <+MAX_OUT+>, sizeof(<+OTYPE+>)))
	{}

	/*
	 * Our virtual destructor.
	 */
	Constraint_Beamformer_impl::~Constraint_Beamformer_impl()
	{
	}

	// array manifold vector generating function
	void Constraint_Beamformer_impl::amv(cx_fcolvec& v_ii, fcolvec& array_loc, float theta)
	{
		// sqrt(-1)
		const gr_complex i = gr_complex(0.0, 1.0);
  		// array manifold vector
	  	v_ii = exp(i*(-1.0*2*datum::pi*cos(theta)*array_loc));
	}

	int
	Constraint_Beamformer_impl::general_work (int noutput_items,
					   gr_vector_int &ninput_items,
					   gr_vector_const_void_star &input_items,
					   gr_vector_void_star &output_items)
	{
	  const <+ITYPE+> *in = (const <+ITYPE+> *) input_items[0];
	  <+OTYPE+> *out = (<+OTYPE+> *) output_items[0];

	  // Do <+signal processing+>
	  // Tell runtime system how many input items we consumed on
	  // each input stream.
	  consume_each (noutput_items);

	  // Tell runtime system how many output items we produced.
	  return noutput_items;
	}

  } /* namespace beamformer */
} /* namespace gr */

