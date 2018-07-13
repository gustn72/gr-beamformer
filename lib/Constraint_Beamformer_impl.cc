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

#define COPY_MEM false  // Do not copy matrices into separate memory
#define FIX_SIZE true   // Keep dimensions of matrices constant

namespace gr {
  namespace beamformer {

    Constraint_Beamformer::sptr
    Constraint_Beamformer::make(cx_fmat corr, int bf_type, int channel, int num_targets, float norm_spacing, int num_ant_ele)
    {
      return gnuradio::get_initial_sptr
        (new Constraint_Beamformer_impl(corr, bf_type, channel, num_targets, norm_spacing, num_ant_ele));
    }

    /*
     * The private constructor
     */
    Constraint_Beamformer_impl::Constraint_Beamformer_impl(cx_fmat corr, int bf_type, int channel, int num_targets, float norm_spacing, int num_ant_ele)
      : gr::block("Constraint_Beamformer",
              gr::io_signature::make(num_targets, num_targets, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)*num_ant_ele)),
              d_corr(corr),
              d_bf_type(bf_type),
              d_channel(channel),
              d_num_targets(num_targets),
              d_norm_spacing(norm_spacing),
              d_num_ant_ele(num_ant_ele)
    {
      // form antenna array locations centered around zero and normalize
      d_array_loc = fcolvec(d_num_ant_ele, fill::zeros);
      for (int nn = 0; nn < d_num_ant_ele; nn++)
      {
          d_array_loc(nn) = d_norm_spacing*(d_num_ant_ele-1-nn);
      }
    }

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
      const float *in = (const float *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
      cx_fcolvec temp_amv;

      // mat(ptr_aux_mem, n_rows, n_cols, copy_aux_mem = true, strict = false)
      cx_fvec out_vec(out+d_num_ant_ele, d_num_ant_ele, COPY_MEM, FIX_SIZE); //

      if(d_bf_type) //bf_type == 1 -> LCMV Beamformer
      {
        if(d_channel>d_num_targets)
        {
          std::cout<<"Choose the channel between 1-"<<d_num_targets<<std::endl;
          amv(temp_amv, d_array_loc, in[d_num_targets-1]);
          out_vec = inv(d_corr)*temp_amv/(temp_amv.t()*inv(d_corr)*temp_amv);
        }
        else if(d_channel<1)
        {
          std::cout<<"Choose the channel between 1-"<<d_num_targets<<std::endl;
          amv(temp_amv, d_array_loc, in[0]);
          out_vec = inv(d_corr)*temp_amv/(temp_amv.t()*inv(d_corr)*temp_amv);
        }
        else
        {
          amv(temp_amv, d_array_loc, in[d_channel-1]);
          out_vec = inv(d_corr)*temp_amv/(temp_amv.t()*inv(d_corr)*temp_amv);
        }
      }
      else //bf_type == 0 -> Conventional Beamformer
      {
        if(d_channel>d_num_targets)
        {
          std::cout<<"Choose the channel between 1-"<<d_num_targets<<std::endl;
          amv(temp_amv, d_array_loc, in[d_num_targets-1]);
          out_vec = temp_amv/sqrtmat(temp_amv.t()*temp_amv);
        }
        else if(d_channel<1)
        {
          std::cout<<"Choose the channel between 1-"<<d_num_targets<<std::endl;
          amv(temp_amv, d_array_loc, in[0]);
          out_vec = temp_amv/sqrtmat(temp_amv.t()*temp_amv);
        }
        else
        {
          amv(temp_amv, d_array_loc, in[d_channel-1]);
          out_vec = temp_amv/sqrtmat(temp_amv.t()*temp_amv);
        }

      }
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace beamformer */
} /* namespace gr */
