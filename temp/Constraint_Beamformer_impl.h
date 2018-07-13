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

#ifndef INCLUDED_BEAMFORMER_CONSTRAINT_BEAMFORMER_IMPL_H
#define INCLUDED_BEAMFORMER_CONSTRAINT_BEAMFORMER_IMPL_H

#include <beamformer/Constraint_Beamformer.h>

#include <armadillo>
using namespace arma;

namespace gr {
  namespace beamformer {

    class Constraint_Beamformer_impl : public Constraint_Beamformer
    {
     private:
      float d_norm_spacing;
      int d_num_targets;
      int d_num_ant_ele;
      int d_type;
      int d_channel;
      fcolvec d_array_loc;
      fcolvec d_weight;

     public:
      Constraint_Beamformer_impl(float norm_spacing, int num_targets, int inputs, int type, int channel);
      ~Constraint_Beamformer_impl();

      // Where all the action really happens
      void amv(cx_fcolvec& v_ii, fcolvec& array_loc, float theta);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace beamformer
} // namespace gr

#endif /* INCLUDED_BEAMFORMER_CONSTRAINT_BEAMFORMER_IMPL_H */

