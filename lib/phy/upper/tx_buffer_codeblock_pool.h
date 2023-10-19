/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once
#include "tx_buffer_impl.h"
#include "srsran/adt/concurrent_queue.h"
#include "srsran/adt/static_vector.h"
#include "srsran/phy/upper/codeblock_metadata.h"
#include "srsran/phy/upper/tx_buffer_pool.h"
#include "srsran/phy/upper/unique_tx_buffer.h"
#include "srsran/support/error_handling.h"
#include "srsran/support/math_utils.h"

namespace srsran {

/// Manages a transmit codeblock buffer pool.
class tx_buffer_codeblock_pool
{
private:
  using codeblock_identifier_list =
      concurrent_queue<unsigned, concurrent_queue_policy::lockfree_mpmc, concurrent_queue_wait_policy::non_blocking>;

  /// Stores all codeblock entries.
  std::vector<dynamic_bit_buffer> data;
  /// List containing the free codeblocks identifiers.
  codeblock_identifier_list free_list;

public:
  /// Default CB identifier for unreserved codeblocks.
  static constexpr unsigned UNRESERVED_CB_ID = UINT32_MAX;

  /// \brief Creates a transmit buffer codeblock pool.
  /// \param[in] nof_codeblocks     The maximum number of codeblocks.
  /// \param[in] max_codeblock_size The maximum codeblock size.
  /// \param[in] external_data      Set to true to indicate that bits are not stored in the buffer.
  tx_buffer_codeblock_pool(unsigned nof_codeblocks, unsigned max_codeblock_size, bool external_data) :
    free_list(nof_codeblocks)
  {
    data.resize(nof_codeblocks);
    unsigned cb_id = 0;
    for (dynamic_bit_buffer& e : data) {
      e.resize(external_data ? 0 : max_codeblock_size);
      while (!free_list.try_push(cb_id++)) {
      }
    }
  }

  /// \brief Reserves a codeblock buffer.
  /// \return The codeblock identifier in the pool if it is reserved successfully. Otherwise, \c UNRESERVED_CB_ID
  unsigned reserve()
  {
    // Try to get an available codeblock.
    optional<unsigned> id = free_list.try_pop();

    // If the pop was not successful, return an unreserved identifier.
    if (!id.has_value()) {
      return UNRESERVED_CB_ID;
    }

    return id.value();
  }

  /// \brief Frees a codeblock buffer.
  /// \param[in] cb_id Codeblock identifier in the pool.
  void free(unsigned cb_id)
  {
    // Skip if the codeblock identifier is equal to the unreserved identifier.
    if (cb_id == UNRESERVED_CB_ID) {
      return;
    }

    // Push codeblock identifier back in the pool.
    while (!free_list.try_push(cb_id)) {
    }
  }

  /// \brief Gets a read-write codeblock bit buffer.
  /// \param[in] cb_id Codeblock identifier.
  /// \return A bit buffer with the codeblock buffer.
  bit_buffer& get_data(unsigned cb_id)
  {
    srsran_assert(
        cb_id < data.size(), "Codeblock identifier (i.e., {}) exceeds the pool size (i.e., {}).", cb_id, data.size());
    return data[cb_id];
  }

  /// \brief Gets a read-only codeblock bit buffer.
  /// \param[in] cb_id Codeblock identifier.
  /// \return A bit buffer with the codeblock buffer.
  const bit_buffer& get_data(unsigned cb_id) const
  {
    srsran_assert(
        cb_id < data.size(), "Codeblock identifier (i.e., {}) exceeds the pool size (i.e., {}).", cb_id, data.size());
    return data[cb_id];
  }
};

} // namespace srsran
