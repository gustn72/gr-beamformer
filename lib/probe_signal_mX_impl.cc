/* -*- c++ -*- */
/*
 * Copyright 2005,2010,2012-2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "probe_signal_mX_impl.h"

namespace gr {
namespace beamformer {

probe_signal_mX::sptr
probe_signal_mX::make(int col,int row)
{
        return gnuradio::get_initial_sptr
                       (new probe_signal_mX_impl(col,row));
}

probe_signal_mX_impl::probe_signal_mX_impl(int col,int row)
        : gr::sync_block("Probe Signal Matrix",
                         gr::io_signature::make(1, 1, col*row*sizeof(std::complex< float > )),
                         gr::io_signature::make(0, 0, 0)),
        d_level(col,std::vector<std::complex< float > >(row)),
        d_col(col),
        d_row(row)
        {

        }



probe_signal_mX_impl::~probe_signal_mX_impl()
{
}

int
probe_signal_mX_impl::work(int noutput_items,
                           gr_vector_const_void_star &input_items,
                           gr_vector_void_star &output_items)
{
        const std::complex< float >  *in = (const std::complex< float >  *)input_items[0];

        for(int i=0; i<d_col; i++)
        {
                for(int j=0; j<d_row; j++)
                {
                        d_level[i][j] = in[(noutput_items-1)*d_row*d_col+d_col*i+j];
                }
        }
        return noutput_items;
}
}   /* namespace blocks */
} /* namespace gr */
