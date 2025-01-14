// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include "common/status.h"
#include "exec/schema_scanner.h"
namespace doris {

class SchemaBackendsScanner : public SchemaScanner {
public:
    SchemaBackendsScanner();
    ~SchemaBackendsScanner() override = default;

    Status start(RuntimeState* state) override;
    Status get_next_block(vectorized::Block* block, bool* eos) override;

private:
    Status _fill_block_impl(vectorized::Block* block);
    Status _fetch_backends_info();
    Status _set_col_name_to_type();

    // column_name -> type, set by _set_col_name_to_type()
    std::unordered_map<std::string, PrimitiveType> _col_name_to_type;
    static std::vector<SchemaScanner::ColumnDesc> _s_tbls_columns;

    std::vector<TRow> _batch_data;
};
} // namespace doris
