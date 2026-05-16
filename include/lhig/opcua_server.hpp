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

#ifndef LHIG_OPCUA_SERVER_HPP
#define LHIG_OPCUA_SERVER_HPP

#include <atomic>
#include <open62541/types.h> // Include for UA_NodeId
#include <thread>

struct UA_Server; // Forward declaration

namespace lhig {

class OpcuaServer {
public:
  OpcuaServer();
  ~OpcuaServer();

  void start();
  void stop();
  void updateVoltage(double voltage);

private:
  void runLoop();
  void createVoltageNode();

  UA_Server *server_;
  volatile bool running_;
  std::thread server_thread_;
  UA_NodeId voltageNodeId_;
};

} // namespace lhig

#endif // LHIG_OPCUA_SERVER_HPP
