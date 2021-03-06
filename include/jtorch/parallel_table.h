//
//  parallel_table.h
//
//  Created by Jonathan Tompson on 4/8/13.
//

#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "jcl/math/int_types.h"
#include "jtorch/torch_stage.h"

namespace jtorch {

class ParallelTable : public TorchStage {
 public:
  // Constructor / Destructor
  ParallelTable();
  ~ParallelTable() override;

  TorchStageType type() const override { return PARALLEL_TABLE_STAGE; }
  std::string name() const override { return "ParallelTable"; }
  void forwardProp(std::shared_ptr<TorchData> input) override;

  void add(std::unique_ptr<TorchStage> stage);  // Memory is transferred
  const uint32_t size() const;

  uint32_t numBanks() const;

  TorchStage* get(const uint32_t i);

  static std::unique_ptr<TorchStage> loadFromFile(std::ifstream& file);

 protected:
  std::vector<std::unique_ptr<TorchStage>> network_;

  void initOutput();

  // Non-copyable, non-assignable.
  ParallelTable(const ParallelTable&) = delete;
  ParallelTable& operator=(const ParallelTable&) = delete;
};

};  // namespace jtorch
