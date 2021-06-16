// Copyright 2005-2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the 'License');
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an 'AS IS' BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// See www.openfst.org for extensive documentation on this weighted
// finite-state transducer library.
//
// Tests if two Far files contains isomorphic (key,fst) pairs.

#include <string>

#include <fst/flags.h>
#include <fst/extensions/far/farscript.h>
#include <fst/extensions/far/getters.h>

DECLARE_string(begin_key);
DECLARE_string(end_key);
DECLARE_double(delta);

int farisomorphic_main(int argc, char **argv) {
  namespace s = fst::script;

  std::string usage = "Compares the FSTs in two FST archives for isomorphism.";
  usage += "\n\n  Usage:";
  usage += argv[0];
  usage += " in1.far in2.far\n";
  usage += "  Flags: begin_key end_key";

  std::set_new_handler(FailedNewHandler);
  SET_FLAGS(usage.c_str(), &argc, &argv, true);
  s::ExpandArgs(argc, argv, &argc, &argv);

  if (argc != 3) {
    ShowUsage();
    return 1;
  }

  const auto arc_type = s::LoadArcTypeFromFar(argv[1]);
  if (arc_type.empty()) return 1;

  bool result = s::FarIsomorphic(argv[1], argv[2], arc_type, FLAGS_delta,
                                 FLAGS_begin_key, FLAGS_end_key);

  if (!result) VLOG(1) << "FARs are not isomorphic.";

  return result ? 0 : 2;
}
