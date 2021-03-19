#
# Copyright (C) [2020] Futurewei Technologies, Inc.
#
# FORCE-RISCV is licensed under the Apache License, Version 2.0
#  (the "License"); you may not use this file except in compliance
#  with the License.  You may obtain a copy of the License at
#
#  http://www.apache.org/licenses/LICENSE-2.0
#
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES
# OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
# See the License for the specific language governing permissions and
# limitations under the License.
#
from Constraint import ConstraintSet

from base.Sequence import Sequence
from riscv.EnvRISCV import EnvRISCV
from riscv.EnvRISCV import GlobalInitSeqRISCV
from riscv.GenThreadRISCV import GenThreadRISCV


#  This class partitions the threads using the same chip strategy.
class ThreadPartitionGlobalInitSeq(GlobalInitSeqRISCV):
    def setupThreadGroup(self):
        self.partitionThreadGroup("SameChip")


# This test verifies the same chip partition strategy. This test assumes
# exactly 2 chips are used. We expect all threads in a given thread group to
# belong to the same chip.
class MainSequence(Sequence):
    def generate(self, **kargs):
        thread_groups = self.queryThreadGroup()
        if len(thread_groups) != 2:
            self.error(
                "Unexpected thread group count; Expected=%d, Actual=%d"
                % (2, len(thread_groups))
            )

        total_thread_count = self.getThreadNumber()
        for thread_group in thread_groups:
            thread_constr = ConstraintSet(thread_group[2])

            if thread_constr.size() != (total_thread_count // 2):
                self.error(
                    "Unexpected group thread count; Expected=%d, Actual=%d"
                    % ((total_thread_count // 2), thread_constr.size())
                )

        for thread_id in range(total_thread_count // 2):
            group_id = self.getThreadGroupId(thread_id)

            if group_id != 0:
                self.error(
                    "Unexpected thread group ID; Expected=%d, Actual=%d"
                    % (0, group_id)
                )

        for thread_id in range(total_thread_count // 2, total_thread_count):
            group_id = self.getThreadGroupId(thread_id)

            if group_id != 1:
                self.error(
                    "Unexpected thread group ID; Expected=%d, Actual=%d"
                    % (0, group_id)
                )

        free_threads = self.getFreeThreads()
        if len(free_threads) != 0:
            self.error(
                "Unexpected free thread count; Expected=%d, Actual=%d"
                % (0, len(free_threads))
            )


GlobalInitialSequenceClass = ThreadPartitionGlobalInitSeq
MainSequenceClass = MainSequence
GenThreadClass = GenThreadRISCV
EnvClass = EnvRISCV
