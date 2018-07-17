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


#ifndef INCLUDED_BEAMFORMER_PROBE_SIGNAL_MX_H
#define INCLUDED_BEAMFORMER_PROBE_SIGNAL_MX_H

#include <vector>
#include <beamformer/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace beamformer {

    /*!
     * \brief <+description of block+>
     * \ingroup beamformer
     *
     */
    class BEAMFORMER_API probe_signal_mX : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<probe_signal_mX> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of beamformer::probe_signal_mX.
       *
       * To avoid accidental use of raw pointers, beamformer::probe_signal_mX's
       * constructor is in a private implementation
       * class. beamformer::probe_signal_mX::make is the public interface for
       * creating new instances.
       */
      static sptr make(int col,int row);
      virtual std::vector<std::vector<std::complex< float > > > level() const = 0;
    };

  } // namespace beamformer
} // namespace gr

#endif /* INCLUDED_BEAMFORMER_PROBE_SIGNAL_MX_H */
