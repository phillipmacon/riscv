//
// Copyright (C) [2020] Futurewei Technologies, Inc.
//
// FORCE-RISCV is licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
// FIT FOR A PARTICULAR PURPOSE.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include <lest/lest.hpp>

#include <Constraint.h>
#include <GenException.h>
#include <Log.h>

using text = std::string;
using namespace std;
using namespace Force;

#undef CASE
#define CASE( name ) lest_CASE( specification(), name )

extern lest::tests & specification();

CASE( "Bug tests" ) {

  // put the issue being debugged here
  SETUP( "Bug test 1 setup" )  {

    SECTION("Bug test 1: test on ApplyConstraintSet") {
      ConstraintSet constr_set("0x7ff00004-0x80100000");
      ConstraintSet apply_constr_set5("0x0-0x12ffffff,0x1300f000-0x161fffff,0x16201000-0x21ffffff,0x22100000-0x7fffffff,0x80000004-0x8005d527,0x8005d530-0x9bffffff,0x9e000000-0xa2ffffff,0xa3010001-0xffffffffff");
      constr_set.ApplyConstraintSet(apply_constr_set5);
      EXPECT(constr_set.ToSimpleString() == "0x7ff00004-0x7fffffff,0x80000004-0x8005d527,0x8005d530-0x80100000");
      EXPECT(constr_set.Size() == constr_set.CalculateSize());
    }

    SECTION("Bug test 2: test on ApplyConstraintSet") {
      ConstraintSet constr_set("0x7ff01008-0x80101004");
      ConstraintSet apply_constr_set("0x0-0x12ffffff,0x1300f000-0x161fffff,0x16201000-0x21ffffff,0x22100000-0x3effffff,0x3f07fffc-0x3fffffff,0x50000000-0x5fffffff,0x64000000-0x80000fff,0x80001008-0x8003f2e7,0x8003f2f0-0x8007eec3,0x8007eec8-0x9bffffff,0x9e000000-0xa2ffffff,0xa3010001-0xffffffffff");
      constr_set.ApplyConstraintSet(apply_constr_set);
      EXPECT(constr_set.ToSimpleString() == "0x7ff01008-0x80000fff,0x80001008-0x8003f2e7,0x8003f2f0-0x8007eec3,0x8007eec8-0x80101004");
      EXPECT(constr_set.Size() == constr_set.CalculateSize());
    }

    SECTION("Bug test 3: test on ApplyConstraintSet") {
      ConstraintSet constr_set("0x0-0x15,0x17-0x1f");
      ConstraintSet apply_constr_set("0x1d,0x1f");
      constr_set.ApplyConstraintSet(apply_constr_set);
      EXPECT(constr_set.ToSimpleString() == "0x1d,0x1f");
      EXPECT(constr_set.Size() == constr_set.CalculateSize());
    }

    SECTION("Bug test 4 extended: test on ApplyConstraintSet") {
      ConstraintSet constr_set("0x0-0x15,0x17-0x21");
      ConstraintSet apply_constr_set("0x1d,0x1f,0x21");
      constr_set.ApplyConstraintSet(apply_constr_set);
      EXPECT(constr_set.ToSimpleString() == "0x1d,0x1f,0x21");
      EXPECT(constr_set.Size() == constr_set.CalculateSize());
    }
    
    SECTION("Bug test 5: test on ApplyConstraintSet") {
      ConstraintSet constr_set("0x0-0x10,0x12-0x1f");
      ConstraintSet apply_constr_set("0x5,0x13,0x16,0x1d");
      constr_set.ApplyConstraintSet(apply_constr_set);
      EXPECT(constr_set.ToSimpleString() == "0x5,0x13,0x16,0x1d");
      EXPECT(constr_set.Size() == constr_set.CalculateSize());
    }

    SECTION("Bug test 6: test on ApplyConstraintSet") {
      ConstraintSet constr_set("0x0-0x7fff,0xffff8000-0xffffffff");
      ConstraintSet apply_constr_set("0x8-0xf,0x28-0x31,0x33-0x37,0x39-0x77,0x88-0x8f,0x98-0xcf,0xd8-0xe3,0xe6-0x197,0x1a0-0x1cf,0x1e0-0x27f,0x290-0x7d9,0x7db-0x107f,0x1082-0x2def,0x2df4-0x2e45,0x2e48-0x2e4f,0x2e58-0x2ef7,0x2f08-0x2f23,0x2f2c-0x30d7,0x30e8-0x41a3,0x41ac-0x41cf,0x41d8-0xde39,0xde3b-0x1ffffff,0x2000008-0x6105a0f,0x6105a20-0x12b1f593,0x12b1f595-0x12ffffff,0x1300f000-0x1307ffff,0x130b0000-0x161fffff,0x16201000-0x17deaf57,0x17deaf5c-0x21ffffff,0x22100000-0x3effffff,0x3f07fffc-0x3fffffff,0x50000000-0x5fffffff,0x800010a8-0x80001147,0x80001150-0x8683cfcb,0x8683d004-0x8c41d133,0x8c41d284-0x8c455643,0x8c455684-0x900479c3,0x900479c6-0x915ed51f,0x915ed524-0x9bffffff,0x9e000000-0xa2ffffff,0xa3010001-0xb251ffff,0xb2520004-0xb252007f,0xb2520084-0xb25200ff,0xb2520104-0xb252017f,0xb2520184-0xb25201ff,0xb2520204-0xb252027f,0xb2520284-0xb25202ff,0xb2520304-0xb252037f,0xb2520384-0xb25203ff,0xb2520404-0xb252047f,0xb2520484-0xb25204ff,0xb2520504-0xb252057f,0xb2520584-0xb25205ff,0xb2520604-0xb252067f,0xb2520684-0xb25206ff,0xb2520704-0xb25207ff,0xb252087a-0xb25208ff,0xb252110c-0xb2521113,0xb25221c0-0xb2fa96db,0xb2fa96e0-0xb2fa96ff,0xb2fa9708-0xc0365127,0xc0365130-0xd44794c7,0xd44794cc-0xd480cbcf,0xd480cbd4-0xd480cc2b,0xd480cc34-0xe2fa96ff,0xe2fa9702-0xf90afe17,0xf90afe20-0xf90afe77,0xf90afe80-0xffe4a1ff,0xffe4a208-0xfff1b226,0xfff1b228-0xffffa62f,0xffffa640-0xffffda86,0xffffda88-0xffffffbb,0xffffffc4-0xffffffcb,0xffffffe0-0x17d8b1023,0x17d8b1028-0x17fffffff,0x180000008-0x239636a8f,0x239636a94-0x2aea70923,0x2aea70928-0x79bc2f9bf,0x79bc2f9c8-0x13996f485f,0x13996f4864-0x13bb2fa917,0x13bb2fa919-0x13bb2fa96f,0x13bb2fa974-0x170d32d7ff,0x170d32d804-0x19a1c71a4b,0x19a1c71a50-0x19a1c71a8b,0x19a1c71a8e-0x3026635b73,0x3026635b7c-0x3316b3446f,0x3316b34478-0x3316b3447b,0x3316b34484-0x3350986a67,0x3350986a70-0x3350986aff,0x3350986b08-0x366259efe5,0x366259efe8-0x47012a59f8,0x47012a59fa-0x4c5bd0d30f,0x4c5bd0d318-0x4fea52899b,0x4fea5289a0-0x52cb422125,0x52cb422128-0x6224c86b1b,0x6224c86bc4-0x6224d019bf,0x6224d019c4-0x62273ad01f,0x62273ad048-0x62273fe27b,0x62273fe290-0x670aef913d,0x670aef9140-0x6c95a7ccaf,0x6c95a7ccb8-0x797eeb1c91,0x797eeb1c94-0x8ed947f89d,0x8ed947f8a0-0x976f4d8b79,0x976f4d8b7b-0xb6a65b409b,0xb6a65b409d-0xe7070f0da5,0xe7070f0da8-0xead6864cb7,0xead68650b8-0xf54a09a62f,0xf54a09a638-0xf54a09afc2,0xf54a09afc4-0xffffffffff");

      constr_set.ApplyConstraintSet(apply_constr_set);
      EXPECT(constr_set.ToSimpleString() == "0x8-0xf,0x28-0x31,0x33-0x37,0x39-0x77,0x88-0x8f,0x98-0xcf,0xd8-0xe3,0xe6-0x197,0x1a0-0x1cf,0x1e0-0x27f,0x290-0x7d9,0x7db-0x107f,0x1082-0x2def,0x2df4-0x2e45,0x2e48-0x2e4f,0x2e58-0x2ef7,0x2f08-0x2f23,0x2f2c-0x30d7,0x30e8-0x41a3,0x41ac-0x41cf,0x41d8-0x7fff,0xffff8000-0xffffa62f,0xffffa640-0xffffda86,0xffffda88-0xffffffbb,0xffffffc4-0xffffffcb,0xffffffe0-0xffffffff");
      EXPECT(constr_set.Size() == constr_set.CalculateSize());
    }

    SECTION("Bug test 7: test on MergeConstraintSet") {
      ConstraintSet constr_set1("0x12");
      ConstraintSet constr_set2("0x11-0x13");
      constr_set1.MergeConstraintSet(constr_set2);
      
      EXPECT(constr_set1.Size() == 3u);
    }

    SECTION("Bug test 8: test on AlignWithSize") {
      //ConstraintSet constr_set("0xfffffffffffffc30-0xfffffffffffffef2,0xffffffffffffff03-0xffffffffffffff65,0xffffffffffffff6e-0xffffffffffffff8b,0xfffffffffffffffe-0xffffffffffffffff");
      ConstraintSet constr_set("0xfffffffffffffc30-0xfffffffffffffef2,0xffffffffffffff03-0xffffffffffffff65,0xffffffffffffff6e-0xffffffffffffff8b,0xffffffffffffffac,0xffffffffffffffae-0xffffffffffffffbe,0xffffffffffffffc0-0xffffffffffffffc2,0xffffffffffffffc4-0xffffffffffffffd5,0xffffffffffffffd7-0xffffffffffffffd9,0xfffffffffffffff2-0xfffffffffffffffb,0xfffffffffffffffe-0xffffffffffffffff");
      constr_set.AlignWithSize(0xfffffffffffffff0ull, 16);
      EXPECT(constr_set.ToSimpleString() == "0xfffffffffffffc30-0xfffffffffffffee0,0xffffffffffffff10-0xffffffffffffff50,0xffffffffffffff70");
    }

  }

}