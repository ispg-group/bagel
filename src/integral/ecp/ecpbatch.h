//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: ecpbatch.h
// Copyright (C) 2014 Quantum Simulation Technologies, Inc.
//
// Author: Hai-Anh Le <anh@u.northwestern.edu>
// Maintainer: QSimulate
//
// This file is part of the BAGEL package.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//


#ifndef __SRC_INTEGRAL_ECP_ECPBATCH_H
#define __SRC_INTEGRAL_ECP_ECPBATCH_H

#include <src/util/parallel/resources.h>
#include <src/molecule/molecule.h>
#include <src/integral/integral.h>
#include <src/integral/ecp/angularbatch.h>

namespace bagel {

class ECPBatch : public Integral {
  protected:

    int max_iter_;
    double integral_thresh_;

    std::array<std::shared_ptr<const Shell>,2> basisinfo_;
    std::shared_ptr<const Molecule> mol_;

    bool spherical_;

    double* data_;

    int ang0_, ang1_, cont0_, cont1_;
    int asize_final_, asize_;
    bool swap01_;
    size_t size_alloc_;
    double* stack_save_;

    bool allocated_here_;
    std::shared_ptr<StackMem> stack_;

    void common_init();
    void get_data(double* intermediate, double* data);

  public:
    ECPBatch(const std::array<std::shared_ptr<const Shell>,2>& info, const std::shared_ptr<const Molecule> mol,
                   std::shared_ptr<StackMem> = nullptr);
    ~ECPBatch();

    double* data() { return data_; }
    virtual double* data(const int i) override { assert(i == 0); return data_; }

    bool swap01() const { return swap01_; }

    void compute() override;

};

}

#endif

