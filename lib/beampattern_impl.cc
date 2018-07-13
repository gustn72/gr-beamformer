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
#include "beampattern_impl.h"

#define COPY_MEM false  // Do not copy matrices into separate memory
#define FIX_SIZE true   // Keep dimensions of matrices constant

namespace gr {
  namespace beamformer {

    beampattern::sptr
    beampattern::make(float norm_spacing, int num_targets, int num_ant_ele, int pspectrum_len)
    {
      return gnuradio::get_initial_sptr
        (new beampattern_impl(norm_spacing, num_targets, num_ant_ele, pspectrum_len));
    }

    /*
     * The private constructor
     */
    beampattern_impl::beampattern_impl(float norm_spacing, int num_targets, int num_ant_ele, int pspectrum_len)
      : gr::sync_block("beampattern",
              gr::io_signature::make(1, 1, sizeof(gr_complex)*num_ant_ele),
              gr::io_signature::make(1, 1, sizeof(float)*pspectrum_len)),
        d_norm_spacing(norm_spacing),
        d_num_targets(num_targets),
        d_num_ant_ele(num_ant_ele),
        d_pspectrum_len(pspectrum_len)
    {
      // form antenna array locations centered around zero and normalize
        d_array_loc = fcolvec(d_num_ant_ele, fill::zeros);
        for (int nn = 0; nn < d_num_ant_ele; nn++)
        {
            d_array_loc(nn) = d_norm_spacing*(d_num_ant_ele-1-nn);
        }

        // form theta vector
        d_theta = new float[d_pspectrum_len];
        d_theta[0] = 0.0;
        float theta_prev = 0.0, theta;
        for (int ii = 1; ii < d_pspectrum_len; ii++)
        {
          theta = theta_prev+180.0/d_pspectrum_len;
          theta_prev = theta;
          d_theta[ii] = datum::pi*theta/180.0;
        }

        // form array response matrix
        cx_fcolvec vii_temp(d_num_ant_ele, fill::zeros);
        d_vii_matrix = cx_fmat(d_num_ant_ele,d_pspectrum_len);
        d_vii_matrix_trans = cx_fmat(d_pspectrum_len,d_num_ant_ele);
        for (int ii = 0; ii < d_pspectrum_len; ii++)
        {
          // generate array manifold vector for each theta
          amv(vii_temp, d_array_loc, d_theta[ii]);
          // add as column to matrix
          d_vii_matrix.col(ii) = vii_temp;
        }
        // save transposed copy
        d_vii_matrix_trans = trans(d_vii_matrix);
    }

    /*
     * Our virtual destructor.
     */
    beampattern_impl::~beampattern_impl()
    {
    }

    // array manifold vector generating function
    void beampattern_impl::amv(cx_fcolvec& v_ii, fcolvec& array_loc, float theta)
    {
        // sqrt(-1)
        const gr_complex i = gr_complex(0.0, 1.0);
        // array manifold vector
        v_ii = exp(i*(-1.0*2*datum::pi*cos(theta)*array_loc));
    }

    int
    beampattern_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        float *out = (float *) output_items[0];

        for (int item = 0; item < noutput_items; item++)
        {
          // make input pointer into matrix pointer
          cx_fvec in_vec(in+item*d_num_ant_ele*1, d_num_ant_ele);
          fvec out_vec(out+item*d_pspectrum_len, d_pspectrum_len, COPY_MEM, FIX_SIZE);

          // determine pseudo-spectrum for each value of theta in [0.0, 180.0)
          cx_frowvec weight_temp;
          weight_temp = in_vec.t();
          gr_complex Q_temp;

          for (int ii = 0; ii < d_pspectrum_len; ii++)
          {
            Q_temp = as_scalar(weight_temp*d_vii_matrix.col(ii));
            out_vec(ii) = sqrt(Q_temp.real()*Q_temp.real()+Q_temp.imag()*Q_temp.imag());
          }
  }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace beamformer */
} /* namespace gr */
