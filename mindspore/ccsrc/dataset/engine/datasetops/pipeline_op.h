/**
 * Copyright 2019 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef DATASET_ENGINE_DATASETOPS_PIPELINE_OP_H_
#define DATASET_ENGINE_DATASETOPS_PIPELINE_OP_H_

#include <memory>
#include <vector>
#include "dataset/engine/datasetops/dataset_op.h"

namespace mindspore {
namespace dataset {
// forward declare
class ExecutionTree;

class DataBuffer;

class PipelineOp : public DatasetOp {
 public:
  // Constructor
  // @param op_connector_size - size of the output connector
  // @return Builder setter method returns reference to the builder.
  // @param sampler - The sampler for the op
  explicit PipelineOp(int32_t op_connector_size, std::shared_ptr<Sampler> sampler = nullptr);

  // Destructor
  ~PipelineOp() = default;

  // A print method typically used for debugging
  // @param out - The output stream to write output to
  // @param show_all - A bool to control if you want to show all info or just a summary
  void Print(std::ostream &out, bool show_all) const override;

  // << Stream output operator overload
  // @notes This allows you to write the debug print info using stream operators
  // @param out - reference to the output stream being overloaded
  // @param po - reference to the PipelineOp to display
  // @return - the output stream must be returned
  friend std::ostream &operator<<(std::ostream &out, const PipelineOp &po) {
    po.Print(out, false);
    return out;
  }

  // Getter
  // @return The number of workers inside this op.  Pipeline ops only have a single worker.
  int32_t num_workers() const override { return 1; }

  // Getter
  // @return the number of threads consuming from the previous Connector
  int32_t num_consumers() const override { return 1; }

  // Getter
  // @return The number of threads that push data to the output connector
  int32_t num_producers() const override { return 1; }

  // During tree prepare phase, operators may have specific pre-operations to perform depending on
  // their role.
  // @notes Derived versions of this function should always call it's superclass version first
  // before providing their own implementations.
  Status PrepareNodePreAction() override {
    // Run common code from super class before adding PipelineOp specific logic
    return (DatasetOp::PrepareNodePreAction());
  }

  // During tree prepare phase, operators may have specific post-operations to perform depending on
  // their role.
  // @notes Derived versions of this function should always call it's superclass version first
  // before providing their own implementations.
  Status PrepareNodePostAction() override {
    // Run common code from super class before adding PipelineOp specific logic
    return (DatasetOp::PrepareNodePostAction());
  }

 protected:
  // *******************************************************************************
  // I'm predicting there will be common arguments or functionality for pipeline ops,
  // just not sure yet what those are.  perhaps this intermediate class between
  // DatasetOp and the actual ops is not needed at all?
  // For example, if there's no common code for all of the non-parallel ops, then
  // they can just inherit from DatasetOp directly and we can put this class into the
  // trash.
};
}  // namespace dataset
}  // namespace mindspore

#endif  // DATASET_ENGINE_DATASETOPS_PIPELINE_OP_H_
