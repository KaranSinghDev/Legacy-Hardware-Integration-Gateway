// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Karan Singh
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Affero General Public License for more details.
//
// You should have received a copy of the License along with this
// program. If not, see <https://www.gnu.org/licenses/>.

#ifndef LHIG_LEGACY_CLIENT_HPP
#define LHIG_LEGACY_CLIENT_HPP

#include <string>

namespace lhig {

class LegacyClient {
public:
  LegacyClient(const std::string &host, int port);
  ~LegacyClient();

  bool connect();
  void disconnect();
  std::string sendCommand(const std::string &command);

  // NEW: Allow main loop to check connection state
  bool isConnected() const;

private:
  std::string host_;
  int port_;
  int sock_fd_;
  bool is_connected_;
};

} // namespace lhig

#endif // LHIG_LEGACY_CLIENT_HPP
