//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: main.cc
// Copyright (C) 2009 Quantum Simulation Technologies, Inc.
//
// Author: Toru Shiozaki <shiozaki@qsimulate.com>
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

#include <iostream>
#include <string>
#include <src/bagel.h>
#include <src/global.h>
#include <src/util/exception.h>
#include <src/util/parallel/mpi_interface.h>
#include <src/util/parallel/resources.h>

using namespace std;
using namespace bagel;

enum PROGRAM_EXIT {
    PROGRAM_EXIT_SUCCESS   = 0,
    PROGRAM_EXIT_EXCEPTION = 1
};

int main(int argc, char** argv) {
  try {
    if (argc == 2) {
      const string input = argv[1];
      run_bagel_from_input(input);
    } else if (argc == 3 && string(argv[1]) == "-i") {
      const string input = argv[2];
      run_bagel_from_json(input);
    } else if (argc == 1) {
      cout << "ERROR: no input file provided" << endl;
      return PROGRAM_EXIT_EXCEPTION;
    } else {
      cout << "ERROR: Unexpected command line arguments" << endl;
      return PROGRAM_EXIT_EXCEPTION;
    }
  } catch (const Termination& e) {
    cout << "  -- Termination requested --" << endl;
    cout << "  message: " << e.what() << endl;
    print_footer();
    return PROGRAM_EXIT_EXCEPTION;
  } catch (const exception& e) {
    if (resources__)
      resources__->proc()->cout_on();
    if (mpi__ && mpi__->size() > 1)
      cout << "  ERROR ON MPI PROCESS " << mpi__->rank() << ": EXCEPTION RAISED:  " << e.what() << endl;
    else
      cout << "  ERROR: EXCEPTION RAISED:  " << e.what() << endl;
    if (resources__)
      resources__->proc()->cout_off();
    return PROGRAM_EXIT_EXCEPTION;
  } catch (...) {
    throw;
  }
  return PROGRAM_EXIT_SUCCESS;
}
