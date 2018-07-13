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


#ifndef INCLUDED_BEAMFORMER_CONSTRAINT_BEAMFORMER_H
#define INCLUDED_BEAMFORMER_CONSTRAINT_BEAMFORMER_H

#include <beamformer/api.h>
#include <gnuradio/block.h>
#include <armadillo>

namespace gr {
  namespace beamformer {

    /*!
     * \brief <+description of block+>
     * \ingroup beamformer
     *
     */
    class BEAMFORMER_API Constraint_Beamformer : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<Constraint_Beamformer> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of beamformer::Constraint_Beamformer.
       *
       * To avoid accidental use of raw pointers, beamformer::Constraint_Beamformer's
       * constructor is in a private implementation
       * class. beamformer::Constraint_Beamformer::make is the public interface for
       * creating new instances.
       */
      static sptr make(arma::cx_fmat corr, int bf_type, int channel, int num_targets, float norm_spacing, int num_ant_ele);
    };

  } // namespace beamformer
} // namespace gr

#endif /* INCLUDED_BEAMFORMER_CONSTRAINT_BEAMFORMER_H */
